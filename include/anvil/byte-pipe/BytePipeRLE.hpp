//Copyright 2021 Adam G. Smith
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//http ://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.

#ifndef ANVIL_LUTILS_BYTEPIPE_RLE_HPP
#define ANVIL_LUTILS_BYTEPIPE_RLE_HPP

#include <iostream>
#include "anvil/byte-pipe/BytePipeReader.hpp"
#include "anvil/byte-pipe/BytePipeWriter.hpp"
#include "anvil/core/Common.hpp"

namespace anvil { namespace BytePipe {

	/*!
		\page RLE (Run-length encoding)
		\details
		The RLE encoder / decoder pipes have two template types, LengthWord and DataWord.
		DataWord controls the size of the words that the RLE algorithm looks at, this can be 1, 2, 4 or 8 bytes.
		Length word determines the maximum number of words that can be in each RLE block.
		The last bit of the length word is reserved to signal which mode the block in.
		A 1 signals that the block only stores one word, but in the original data there
		were N copies of it in total.
		A 0 signals that there are N words in the block that do not have any special
		encoding.
	*/

	template<class LengthWord = uint16_t, class DataWord = uint8_t>
	class RLEEncoderPipe final : public OutputPipe {
	public:
		enum : LengthWord {
			LENGTH_BITS = sizeof(LengthWord) * 8,
			RLE_FLAG = 1ull << (LENGTH_BITS - 1),
			MAX_BYTES_IN_BLOCK = (anvil::ConstantPower<2, LENGTH_BITS>::value - 1) >> 1,
			MAX_RLE_LENGTH = MAX_BYTES_IN_BLOCK//MAX_BYTES_IN_BLOCK / sizeof(DataWord)
		};
	private:
		static_assert(std::is_unsigned<LengthWord>::value, "LengthWord must be an unsigned integer");
		static_assert(std::is_unsigned<DataWord>::value, "DataWord must be an unsigned integer");

		OutputPipe& _output;
		uint8_t* _byte_buffer;
		size_t _byte_buffer_capacity;
		union {
			LengthWord _bytes_in_buffer;	//!< In RLE mode this is the number of words in the repeat, otherwise the number of bytes buffered
			LengthWord _rle_length;			//!< In RLE mode this is the number of words in the repeat, otherwise the number of bytes buffered
		};
		bool _rle_mode;

		void ReserveBuffer(size_t bytes) {
			if (bytes > _byte_buffer_capacity) {
				if (bytes - _byte_buffer_capacity < 1024) bytes = _byte_buffer_capacity + 1024;
				if (bytes > MAX_BYTES_IN_BLOCK) bytes = MAX_BYTES_IN_BLOCK;
				
				uint8_t* new_buffer = new uint8_t[bytes];
				if (new_buffer == nullptr) throw std::runtime_error("anvil::BytePipe::RLEEncoderPipe : Failed to allocate buffer");

				if (_byte_buffer) {
					memcpy(new_buffer, _byte_buffer, _byte_buffer_capacity);
					delete[] _byte_buffer;
				}
				_byte_buffer = new_buffer;
				_byte_buffer_capacity = bytes;
			}
		}

		inline DataWord& GetCurrentWord() {
			return *reinterpret_cast<DataWord*>(_byte_buffer);
		}

		void _WriteToOutput(const void* src, size_t size)
		{
			//! \bug Does not handle timeout correctly
			size_t bytes_written = size;
			_output.WriteBytes(src, bytes_written, -1);
			if (bytes_written != size) throw std::runtime_error("RLEEncoderPipe::_WriteToOutput : Failed to write all bytes to the downstream pipe");
		}

		bool _Flush(int timeout_ms) {
			if (_bytes_in_buffer > 0u) {
				LengthWord len = _bytes_in_buffer;

				if (_rle_mode) {

					// Write the block
					len |= RLE_FLAG;

					// Combine the write into one call
					uint8_t block[sizeof(LengthWord) + sizeof(DataWord)];
					LengthWord& len2 = *reinterpret_cast<LengthWord*>(block);
					DataWord& word2 = *reinterpret_cast<DataWord*>(block + sizeof(LengthWord));
					len2 = len;
					word2 = GetCurrentWord();
					_WriteToOutput(block, sizeof(LengthWord) + sizeof(DataWord));
				} else {

					// Write the buffer
					_WriteToOutput(&len, sizeof(LengthWord));
					_WriteToOutput(_byte_buffer, _bytes_in_buffer);
				}

				// Reset the encoder state
				_bytes_in_buffer = 0u;
				_rle_mode = false;
				return true;
			}

			return false;
		}

		void NewRLEBlock(const DataWord word) {
			//! \bug Does not handle timeout correctly
			DataWord& current = GetCurrentWord();
			if (_rle_mode) {
				if (_rle_length > 0 && current != word) _Flush(100);
			} else if (_bytes_in_buffer > 0) {
				_Flush(100);
			}
			_rle_mode = true;
			_rle_length = 1u;
			current = word;
		}

		void WriteWordsRLE(const DataWord word, size_t count) {
			while (count > 0u) {
				size_t to_add = MAX_RLE_LENGTH - _rle_length;
				if (to_add > count) to_add = count;

				_rle_length += static_cast<LengthWord>(to_add);

				count -= to_add;
				if (_rle_length == MAX_RLE_LENGTH) {
					//! \bug Does not handle timeout correctly
					_Flush(1000);
					// Force into RLE mode
					if (count > 0) {
						NewRLEBlock(word);
						--count;
					}
				}
			}
		}

		void WriteWordsNonRLE(const DataWord* words, size_t count) {

			while (count > 0) {
				size_t to_add = (MAX_BYTES_IN_BLOCK - _bytes_in_buffer) / sizeof(DataWord);
				if (to_add > count) to_add = count;

				if (to_add == 0) {
					//! \bug Does not handle timeout correctly
					_Flush(1000);
				} else {
					memcpy(_byte_buffer + _bytes_in_buffer, words, to_add * sizeof(DataWord));
					_bytes_in_buffer += static_cast<LengthWord>(to_add * sizeof(DataWord));
				}

				count -= to_add;
				words += to_add;
			}
		}

		void WriteWords(const DataWord* words, size_t count) {
			while (count > 0u) {
				DataWord w = *words;
				if (_rle_mode) {
					if (_rle_length > 0) {
						if (GetCurrentWord() == w) {
RLE:
							size_t rle_words = 1u;

							for (size_t i = 1u; i < count; ++i) {
								if (words[i] == w) ++rle_words;
								else break;
							}

							WriteWordsRLE(w, rle_words);
							words += rle_words;
							count -= rle_words;
						} else {
							//! \bug Does not handle timeout correctly
							_Flush(1000);
							goto NON_RLE;
						}
					} else {
						goto RLE;
					}
				} else {
NON_RLE:
					size_t rle_block_length = 0u;
					DataWord previous_word = _bytes_in_buffer < sizeof(DataWord) ? 0 : *(reinterpret_cast<DataWord*>(_byte_buffer + _bytes_in_buffer) - 1);
					size_t non_rle_words = 0u;
					for (size_t i = 0u; i < count; ++i) {
						DataWord this_word = words[i];
						if (non_rle_words > 0 && this_word == previous_word) {
							rle_block_length = 2u;
							--non_rle_words;
							break;
						}
						previous_word = this_word;
						++non_rle_words;
					}

					if (non_rle_words) {
						WriteWordsNonRLE(words, non_rle_words);
						words += non_rle_words;
						count -= non_rle_words;
					}

					if (rle_block_length) {
						NewRLEBlock(previous_word);
						++_rle_length;
						words += rle_block_length;
						count -= rle_block_length;
					}
				}
			}
		}

		//void WriteWord8(const uint64_t word) {
		//	if ANVIL_CONSTEXPR_VAR (std::is_same<DataWord, uint8_t>::value) {

		//		// If all words are the same
		//		uint64_t w1 = word & 255ull;
		//		uint64_t w2 = (word >> 8ull) & 255ull;
		//		uint64_t w3 = (word >> 16ull) & 255ull;
		//		uint64_t w4 = (word >> 24ull) & 255ull;
		//		uint64_t w5 = (word >> 32ull) & 255ull;
		//		uint64_t w6 = (word >> 40ull) & 255ull;
		//		uint64_t w7 = (word >> 48ull) & 255ull;
		//		uint64_t w8 = word >> 56ull;

		//		uint64_t mask_w2 = w2 ^ w1;
		//		uint64_t mask_w3 = w3 ^ w1;
		//		uint64_t mask_w4 = w4 ^ w1;
		//		uint64_t mask_w5 = w5 ^ w1;
		//		uint64_t mask_w6 = w6 ^ w1;
		//		uint64_t mask_w7 = w7 ^ w1;
		//		uint64_t mask_w8 = w8 ^ w1;

		//		mask_w3 |= mask_w4;
		//		mask_w5 |= mask_w6;
		//		mask_w7 |= mask_w8;
		//		
		//		mask_w3 |= mask_w5 | mask_w7;

		//		if (mask_w3 == 0u) {
		//			// If the currently block isn't repeating or is repeating a different word then flush it
		//			if (_bytes_in_buffer > 0u) {
		//				if (_rle_mode) {
		//					if (w1 != GetCurrentWord()) {
		//						// Flush the current block
		//						_Flush();
		//					}
		//				} else {
		//					if (_bytes_in_buffer == sizeof(DataWord)) {
		//						// Act as if this was an RLE block
		//						_rle_length = 1;
		//						_rle_mode = true; 
		//						if (w1 != GetCurrentWord()) {
		//							// Flush the current block
		//							_Flush();
		//						}
		//					} else {
		//						// Flush the current block
		//						_Flush();
		//					}
		//				}
		//			}

		//			_rle_mode = true;
		//			GetCurrentWord() = static_cast<DataWord>(w1);
		//			if (_rle_length < MAX_RLE_LENGTH - 8u) {
		//				// Add all 4 words to the block at once
		//				_rle_length += 8u;
		//			} else {
		//				// Add the words individually
		//				WriteWordRLE(static_cast<DataWord>(w1));
		//				WriteWordRLE(static_cast<DataWord>(w2));
		//				WriteWordRLE(static_cast<DataWord>(w3));
		//				WriteWordRLE(static_cast<DataWord>(w4));
		//				WriteWordRLE(static_cast<DataWord>(w5));
		//				WriteWordRLE(static_cast<DataWord>(w6));
		//				WriteWordRLE(static_cast<DataWord>(w7));
		//				WriteWordRLE(static_cast<DataWord>(w8));
		//			}
		//			return;
		//		}

		//		// Add the words individually
		//		WriteWord(static_cast<DataWord>(w1));
		//		WriteWord(static_cast<DataWord>(w2));
		//		WriteWord(static_cast<DataWord>(w3));
		//		WriteWord(static_cast<DataWord>(w4));
		//		WriteWord(static_cast<DataWord>(w5));
		//		WriteWord(static_cast<DataWord>(w6));
		//		WriteWord(static_cast<DataWord>(w7));
		//		WriteWord(static_cast<DataWord>(w8));
		//	} else {
		//		throw std::runtime_error("RLEEncoderPipe::WriteWord8 : Only implemented for 1 byte words");
		//	}
		//}

		void WriteBytesInternal(const void* src, const size_t bytes) {
			size_t words = bytes / sizeof(DataWord);
			const DataWord* wordPtr = static_cast<const DataWord*>(src);

			ReserveBuffer((_rle_mode ? 0 : _bytes_in_buffer) + bytes);
			WriteWords(wordPtr, words);

			src = wordPtr + words;

			size_t remaining_bytes = bytes - (bytes / sizeof(DataWord)) * sizeof(DataWord);
			if (remaining_bytes > 0) {
				//! \bug Does not handle timeout correctly
				if (_rle_mode || _bytes_in_buffer + remaining_bytes > MAX_BYTES_IN_BLOCK) _Flush(-1);
				memcpy(_byte_buffer + _bytes_in_buffer, src, remaining_bytes);
				_bytes_in_buffer += static_cast<LengthWord>(remaining_bytes);
			}
		}
	protected:

		#pragma warning( disable : 4100) // timeout_ms is not used, name is retained to improve code readability
		virtual std::future_status WriteBytesVirtual(const void* src, size_t& bytes, int timeout_ms) final
		{
			//! \bug Does not handle timeout correctly
			WriteBytesInternal(src, bytes);
			return std::future_status::ready;
		}


		virtual std::future_status FlushVirtual(int timeout_ms) final
		{
			//! \bug Does not handle timeout correctly
			if (_Flush(timeout_ms)) return _output.Flush(timeout_ms);
			return std::future_status::ready;
		}

	public:
		RLEEncoderPipe(OutputPipe& output) :
			_output(output),
			_byte_buffer(nullptr),
			_byte_buffer_capacity(0u),
			_bytes_in_buffer(0u),
			_rle_mode(false)
		{}

		~RLEEncoderPipe() {
			if (_Flush(1000)) _output.Flush(1000);
			if (_byte_buffer) {
				delete[] _byte_buffer;
				_byte_buffer = nullptr;
			}
		}
	};

	

	template<class LengthWord = uint16_t, class DataWord = uint8_t>
	class RLEDecoderPipe final : public InputPipe {
	public:
		enum : LengthWord {
			LENGTH_BITS = RLEEncoderPipe<LengthWord, DataWord>::LENGTH_BITS,
			RLE_FLAG = RLEEncoderPipe<LengthWord, DataWord>::RLE_FLAG,
			MAX_BYTES_IN_BLOCK = RLEEncoderPipe<LengthWord, DataWord>::MAX_BYTES_IN_BLOCK,
			MAX_RLE_LENGTH = RLEEncoderPipe<LengthWord, DataWord>::MAX_RLE_LENGTH
		};
	private:
		static_assert(std::is_unsigned<LengthWord>::value, "LengthWord must be an unsigned integer");
		static_assert(std::is_unsigned<DataWord>::value, "DataWord must be an unsigned integer");

		InputPipe& _input;
		std::vector<uint8_t> _byte_buffer;
		int _timeout_ms;
		size_t _buffer_read_head;
		LengthWord _repeat_length;
		DataWord _repeat_word;

		inline bool InRepeatMode() const 
		{
			return _repeat_length > 0;
		}

		inline size_t BytesInBuffer() const 
		{
			return _byte_buffer.size() - _buffer_read_head;
		}

		void BufferCurrentRepeat() 
		{
			const uint8_t* u8 = reinterpret_cast<uint8_t*>(&_repeat_word);
			for (LengthWord i = 0; i < _repeat_length; ++i) {
				//! \todo Optimise writing multiple bytes to the buffer
				for (size_t j = 0u; j < sizeof(DataWord); ++j) {
					_byte_buffer.push_back(u8[j]);
				}
			}
			_repeat_length = 0;
			_repeat_word = 0;
		}

		void ReadNextBlock() {
			// Can't read block when in repeat mode
			if (InRepeatMode()) BufferCurrentRepeat();

			// Reset the buffer
			if (_buffer_read_head == _byte_buffer.size()) {
				_byte_buffer.clear();
				_buffer_read_head = 0u;
			}

			// Read the length of the block
			LengthWord len = 0u;
			size_t throwaway = 0u;
			_input.ForceReadBytes(&len, sizeof(LengthWord), throwaway, _timeout_ms);

			// If the block is repeated word
			if (len & RLE_FLAG) 
			{
				len &= ~RLE_FLAG;
				_repeat_length = len;
				
				// Read the word
				_repeat_word = 0u;
				_input.ForceReadBytes(&_repeat_word, sizeof(DataWord), throwaway, _timeout_ms);

				// If there is data in the buffer then this repeat needs to be added to it
				if (BytesInBuffer() > 0) BufferCurrentRepeat();
			} 
			else 
			{
				size_t offset = _byte_buffer.size();
				_byte_buffer.resize(offset + len);
				_input.ForceReadBytes(_byte_buffer.data() + offset, len, throwaway, _timeout_ms);
			}
		}

	protected:
		virtual void* ReadNextPacket(size_t& bytes) final 
		{
			// Try to fill the buffer with enough data
			if (InRepeatMode()) BufferCurrentRepeat();

			while (BytesInBuffer() < bytes) //! \bug Possible infinite loop
			{ 
				ReadNextBlock();
				if (InRepeatMode()) BufferCurrentRepeat();
			}

			// Update the current read position
			bytes = BytesInBuffer();
			uint8_t* read_head = _byte_buffer.data() + _buffer_read_head;
			_buffer_read_head += bytes;
			return read_head;
		}

	public:
		RLEDecoderPipe(InputPipe& input, int timeout_ms = -1) :
			_input(input),
			_timeout_ms(timeout_ms),
			_repeat_word(0u),
			_buffer_read_head(0u),
			_repeat_length(0u)
		{
			_byte_buffer.reserve(MAX_BYTES_IN_BLOCK > (UINT16_MAX >> 1) ? (UINT16_MAX >> 1) : MAX_BYTES_IN_BLOCK);
		}

		~RLEDecoderPipe() {

		}
	};

}}

#endif
