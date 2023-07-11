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
	private:
		static_assert(std::is_unsigned<LengthWord>::value, "LengthWord must be an unsigned integer");
		static_assert(std::is_unsigned<DataWord>::value, "DataWord must be an unsigned integer");

		enum : LengthWord {
			RLE_FLAG = 1 << (sizeof(LengthWord) * 8 - 1),
			MAX_RLE_LENGTH = static_cast<LengthWord>(-1) >> 1
		};

		OutputPipe& _output;
		DataWord* _buffer;
		DataWord _current_word;
		LengthWord _length;
		bool _rle_mode;

		bool _Flush() {
			if (_length > 0u) {
				LengthWord len = _length;
				if (_rle_mode) {
					// Write the block
					len |= RLE_FLAG;

					// Combine the write into one call
					uint8_t mem[sizeof(LengthWord) + sizeof(DataWord)];
					*reinterpret_cast<LengthWord*>(mem) = len;
					*reinterpret_cast<DataWord*>(mem + sizeof(LengthWord)) = _current_word;
					_output.WriteBytes(mem, sizeof(LengthWord) + sizeof(DataWord));
				} else {
					// Write the buffer
					_output.WriteBytes(&len, sizeof(LengthWord));
					_output.WriteBytes(_buffer, _length * sizeof(DataWord));
				}

				// Reset the encoder state
				_current_word = 0u;
				_length = 0u;
				_rle_mode = false;
				return true;
			}

			return false;
		}

		void WriteWordRLE(const DataWord word) {
			// If the current RLE block is full then flush the data
			if (_length == MAX_RLE_LENGTH) {
NEW_BLOCK:
				_Flush();
				// Flush the current block and write as aif it was a non-repeating block
				WriteWordNonRLE(word);
				return;
			}
			
			if (_length == 0u) {
				// Start a new repeating block
				_current_word = word;
				_length = 1u;
				_rle_mode = true;
			} else if (word == _current_word) {
				// Add the word to the repeat
				++_length;
			} else {
				goto NEW_BLOCK;
			}
		}

		void WriteWordNonRLE(const DataWord word) {
			// If the current RLE block is full then flush the data
			if (_length == MAX_RLE_LENGTH) _Flush();

			if (_length >= 8u) {
				// If the word is the same as the last word in the buffer

				DataWord cmp1 = word ^ _buffer[_length - 1u];
				DataWord cmp2 = word ^ _buffer[_length - 2u];
				DataWord cmp3 = word ^ _buffer[_length - 3u];
				DataWord cmp4 = word ^ _buffer[_length - 4u];
				DataWord cmp5 = word ^ _buffer[_length - 5u];
				DataWord cmp6 = word ^ _buffer[_length - 6u];
				DataWord cmp7 = word ^ _buffer[_length - 7u];
				cmp1 |= cmp2;
				cmp3 |= cmp4;
				cmp5 |= cmp6;
				cmp1 |= cmp3;
				cmp5 |= cmp7;
				cmp1 |= cmp5;

				if (cmp1 == 0) {
					// Flush the current block except for the last word
					_length -= 7u;
					_Flush();

					// Start a new RLE block
					_current_word = word;
					_length = 8u;
					_rle_mode = true;
					return;
				}
			}

			// Add word to buffer
			_buffer[_length++] = word;
		}

		void WriteWord(const DataWord word) {
			// If the current block is repeating
			if (_rle_mode) {
				WriteWordRLE(word);
			} else {
				WriteWordNonRLE(word);
			}
		}

		void WriteWord4(const uint32_t word) {
			if ANVIL_CONSTEXPR_VAR (std::is_same<DataWord, uint8_t>::value) {

				uint32_t w1 = word & 255u;
				uint32_t w2 = (word >> 8u) & 255u;
				uint32_t w3 = (word >> 16u) & 255u;
				uint32_t w4 = word >> 24u;

				w2 ^= w1;
				w3 ^= w1;
				w4 ^= w1;

				w1 = w2 | w3 | w4;

				// If all words are the same
				if (w1 == 0u) {
					// If the currently block isn't repeating or is repeating a different word then flush it
					if (_length > 0u) {
						if (_rle_mode) {
							if (w1 != _current_word) {
								// Flush the current block
								_Flush();
							}
						} else {
							// Flush the current block
							_Flush();
						}
					}

					_rle_mode = true;
					_current_word = static_cast<DataWord>(w1);
					if (_length < MAX_RLE_LENGTH - 4u) {
						// Add all 4 words to the block at once
						_length += 4u;
					} else {
						// Add the words individually
						WriteWordRLE(static_cast<DataWord>(w1));
						WriteWordRLE(static_cast<DataWord>(w2));
						WriteWordRLE(static_cast<DataWord>(w3));
						WriteWordRLE(static_cast<DataWord>(w4));
					}
					return;
				}

				// Add the words individually
				WriteWord(static_cast<DataWord>(w1));
				WriteWord(static_cast<DataWord>(w2));
				WriteWord(static_cast<DataWord>(w3));
				WriteWord(static_cast<DataWord>(w4));
			} else {
				throw std::runtime_error("RLEEncoderPipe::WriteWord4 : Only implemented for 1 byte words");
			}
		}

		void WriteWord8(const uint64_t word) {
			if ANVIL_CONSTEXPR_VAR (std::is_same<DataWord, uint8_t>::value) {

				// If all words are the same
				uint64_t w1 = word & 255ull;
				uint64_t w2 = (word >> 8ull) & 255ull;
				uint64_t w3 = (word >> 16ull) & 255ull;
				uint64_t w4 = (word >> 24ull) & 255ull;
				uint64_t w5 = (word >> 32ull) & 255ull;
				uint64_t w6 = (word >> 40ull) & 255ull;
				uint64_t w7 = (word >> 48ull) & 255ull;
				uint64_t w8 = word >> 56ull;

				w2 ^= w1;
				w3 ^= w1;
				w4 ^= w1;
				w5 ^= w1;
				w6 ^= w1;
				w7 ^= w1;
				w8 ^= w1;

				w3 |= w4;
				w5 |= w6;
				w7 |= w8;
				
				w1 = w3 | w5 | w7;

				if (w1 == 0u) {
					// If the currently block isn't repeating or is repeating a different word then flush it
					if (_length > 0u) {
						if (_rle_mode) {
							if (w1 != _current_word) {
								// Flush the current block
								_Flush();
							}
						} else {
							// Flush the current block
							_Flush();
						}
					}

					_rle_mode = true;
					_current_word = static_cast<DataWord>(w1);
					if (_length < MAX_RLE_LENGTH - 8u) {
						// Add all 4 words to the block at once
						_length += 8u;
					} else {
						// Add the words individually
						WriteWordRLE(static_cast<DataWord>(w1));
						WriteWordRLE(static_cast<DataWord>(w2));
						WriteWordRLE(static_cast<DataWord>(w3));
						WriteWordRLE(static_cast<DataWord>(w4));
						WriteWordRLE(static_cast<DataWord>(w5));
						WriteWordRLE(static_cast<DataWord>(w6));
						WriteWordRLE(static_cast<DataWord>(w7));
						WriteWordRLE(static_cast<DataWord>(w8));
					}
					return;
				}

				// Add the words individually
				WriteWord(static_cast<DataWord>(w1));
				WriteWord(static_cast<DataWord>(w2));
				WriteWord(static_cast<DataWord>(w3));
				WriteWord(static_cast<DataWord>(w4));
				WriteWord(static_cast<DataWord>(w5));
				WriteWord(static_cast<DataWord>(w6));
				WriteWord(static_cast<DataWord>(w7));
				WriteWord(static_cast<DataWord>(w8));
			} else {
				throw std::runtime_error("RLEEncoderPipe::WriteWord8 : Only implemented for 1 byte words");
			}
		}

		void WriteBytesInternal(const void* src, const size_t bytes) {
			size_t words = bytes / sizeof(DataWord);
			if (words * sizeof(DataWord) != bytes) throw std::runtime_error("RLEEncoderPipe::WriteBytes : Byte count is not divisible by the word size");

			const DataWord* wordPtr = static_cast<const DataWord*>(src);


			// Optimise memory reads for 1 byte data
			if ANVIL_CONSTEXPR_VAR (std::is_same<DataWord, uint8_t>::value) {
				if ANVIL_CONSTEXPR_VAR(sizeof(intptr_t) >= 8u) {
					while (words >= 8u) {
						WriteWord8(*reinterpret_cast<const uint64_t*>(wordPtr));
						wordPtr += 8u;
						words -= 8u;
					}
				} else {
					while (words >= 4u) {
						WriteWord4(*reinterpret_cast<const uint32_t*>(wordPtr));
						wordPtr += 4u;
						words -= 4u;
					}
				}
			}

			for (size_t i = 0; i < words; ++i) {
				WriteWord(wordPtr[i]);
			}
		}
	public:
		RLEEncoderPipe(OutputPipe& output) :
			_output(output),
			_buffer(new DataWord[MAX_RLE_LENGTH]),
			_current_word(0u),
			_length(0u),
			_rle_mode(false)
		{}

		~RLEEncoderPipe() {
			if (_Flush()) _output.Flush();
			delete[] _buffer;
			_buffer = nullptr;
		}


		size_t WriteBytes(const void* src, const size_t bytes) final {
			WriteBytesInternal(src, bytes);
			return bytes;
		}

		#pragma warning( disable : 4100) // timeout_ms is not used, name is retained to improve code readability
		void WriteBytes(const void** src, const size_t* bytes_requested, const size_t count, int timeout_ms = -1) final {
			for (size_t i = 0u; i < count; ++i) WriteBytesInternal(src[i], bytes_requested[i]);
		}

		void Flush() final {
			if (_Flush()) _output.Flush();
		}
	};

	

	template<class LengthWord = uint16_t, class DataWord = uint8_t>
	class RLEDecoderPipe final : public InputPipe {
	private:
		static_assert(std::is_unsigned<LengthWord>::value, "LengthWord must be an unsigned integer");
		static_assert(std::is_unsigned<DataWord>::value, "DataWord must be an unsigned integer");

		enum : LengthWord {
			RLE_FLAG = 1 << (sizeof(LengthWord) * 8 - 1),
			MAX_RLE_LENGTH = static_cast<LengthWord>(-1) >> 1
		};

		InputPipe& _input;
		DataWord* _buffer;
		int _timeout_ms;
		LengthWord _buffer_read_head;
		LengthWord _length;
		DataWord _repeat_word;
		bool _rle_mode;

		void ReadNextBlock() {
			// Reset the buffer
			if (_length != 0u) throw std::runtime_error("RLEDecoderPipe::ReadNextBlock : Buffer was not empty when trying to read new block");
			_buffer_read_head = 0u;

			// Read the length of the block
			LengthWord len = 0u;
			uint32_t bytes_read = sizeof(LengthWord);
			_input.ReadBytesFast(&len, sizeof(LengthWord), _timeout_ms);

			// If the block is repeated word
			if (len & RLE_FLAG) {
				len &= ~RLE_FLAG;
				_length = len;

				_rle_mode = true;
				read2_faster = 0;
				_repeat_word = 0u;
				
				// Read the word
				bytes_read = sizeof(DataWord);
				_input.ReadBytesFast(&_repeat_word, bytes_read, _timeout_ms);
			} else {
				_length = len;
				_rle_mode = false;
				read2_faster = 1;
				bytes_read = _length * sizeof(DataWord);
				_input.ReadBytesFast(_buffer, bytes_read, _timeout_ms);
			}
		}
	public:
		RLEDecoderPipe(InputPipe& input, int timeout_ms = -1) :
			_input(input),
			_buffer(new DataWord[MAX_RLE_LENGTH]),
			_timeout_ms(timeout_ms),
			_repeat_word(0u),
			_buffer_read_head(0u),
			_length(0u),
			_rle_mode(false)
		{}

		~RLEDecoderPipe() {
			delete[] _buffer;
			_buffer = nullptr;
		}


		size_t ReadBytes(void* dst, const size_t bytes) final{
			size_t words = bytes / sizeof(DataWord);
			if (words * sizeof(DataWord) != bytes) throw std::runtime_error("RLEDecoderPipe::ReadBytes : Byte count is not divisible by the word size");

			DataWord* wordPtr = static_cast<DataWord*>(dst);
			size_t wordsToRead = 0u;

			while (words != 0u) {
				if (_length == 0u) ReadNextBlock();
				wordsToRead = words < _length ? words : _length;

				if (_rle_mode) {
					if ANVIL_CONSTEXPR_VAR(sizeof(DataWord) == 1) {
						memset(wordPtr, _repeat_word, wordsToRead);
					} else {
						for (uint32_t i = 0u; i < wordsToRead; ++i) wordPtr[i] = _repeat_word;
					}
				} else {
					memcpy(wordPtr, _buffer + _buffer_read_head, sizeof(DataWord) * wordsToRead);
					_buffer_read_head += wordsToRead;
				}

				_length -= wordsToRead;
				words -= wordsToRead;
				wordPtr += wordsToRead;
			}

			if (_length == 0) read2_faster = 0;

			return bytes;
		}

		const void* ReadBytes2(const size_t bytes_requested, size_t& bytes_actual) final {
			if (bytes_requested == 0u) {
				bytes_actual = 0u;
				return nullptr;
			}

			size_t words = bytes_requested / sizeof(DataWord);
			if (words * sizeof(DataWord) != bytes_requested) throw std::runtime_error("RLEDecoderPipe::ReadBytes : Byte count is not divisible by the word size");

			size_t wordsToRead = 0u;

			void* address = nullptr;

			if (_length == 0u) ReadNextBlock();
			wordsToRead = words < _length ? words : _length;

			if (_rle_mode) {
				address = &_repeat_word;
				wordsToRead = 1;
			} else {
				address = _buffer + _buffer_read_head;
				_buffer_read_head += wordsToRead;
			}

			bytes_actual = sizeof(DataWord) * wordsToRead;

			_length -= wordsToRead;
			if (_length == 0) read2_faster = 0;

			return address;
		}

		size_t GetBufferSize() const final {
			return _length * sizeof(DataWord);
		}
	};

}}

#endif
