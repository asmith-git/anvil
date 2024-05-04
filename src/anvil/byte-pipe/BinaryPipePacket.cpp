//Copyright 2019 Adam G. Smith
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

#include "anvil/byte-pipe/BytePipePacket.hpp"

namespace anvil { namespace BytePipe {

	static uint32_t PacketVersionFromSize(const uint64_t size) {
		if (size < 32766u) {
			return 2u;
		} else if (size > UINT16_MAX + 1u) {
			return 3u;
		} else {
			return 1u;
		}
	}

	static ANVIL_CONSTEXPR_VAR const uint8_t g_header_sizes[] = {
		sizeof(PacketHeaderVersion1),
		sizeof(PacketHeaderVersion2),
		sizeof(PacketHeaderVersion3)
	};

	// PacketInputPipe

	PacketInputPipe::PacketInputPipe(InputPipe& downstream_pipe, int timeout_ms) :
		_downstream_pipe(downstream_pipe),
		_payload(nullptr),
		_payload_capacity(0u),
		_payload_bytes(0u),
		_payload_read_head(0u),
		_timeout_ms(timeout_ms)
	{

	}

	PacketInputPipe::~PacketInputPipe() 
	{
		if (_payload != nullptr) delete[] _payload;
	}

	void* PacketInputPipe::ReadNextPacket(size_t& bytes_actual)
	{
		const size_t bytes_requested = bytes_actual;

		if (bytes_requested == 0u) 
		{
		NO_DATA:
			bytes_actual = 0u;
			return nullptr;
		}

		if (_payload_read_head >= _payload_bytes) ReadNextPacket2();
		if (_payload_bytes == 0u) goto NO_DATA;

		bytes_actual = _payload_bytes - _payload_read_head;
		if (bytes_actual > bytes_requested) bytes_actual = bytes_requested;

		void* address = _payload + _payload_read_head;
		_payload_read_head += bytes_actual;

		return address;
	}

	void PacketInputPipe::ReadNextPacket2() 
	{
		enum { _timeout_ms = -1 };
		size_t throwaway = 0u;
		size_t packet_size = 0u;

		// Read the packet header version
		PacketHeader header;
		_downstream_pipe.ForceReadBytes(&header, 1u, throwaway, _timeout_ms);

		// Error checking
		uint32_t version = header.v1.packet_version;
		if (version >= 3u) version = header.v3.packet_version; // Read the extended version number
		if (header.v1.packet_version == 0 || header.v1.packet_version > 3u) {
		BAD_VERSION:
			throw std::runtime_error("PacketInputPipe::ReadNextPacket : Packet version is not supported");
		}

		// Read the rest of the header
		const size_t header_size = g_header_sizes[version - 1u];
		_downstream_pipe.ForceReadBytes(reinterpret_cast<uint8_t*>(&header) + 1u, header_size - 1u, throwaway, _timeout_ms);

		if (version == 1u) {
			_payload_bytes = header.v1.payload_size + 1u;
			packet_size = header.v1.packet_size + 1u;
		} else if (version == 2u) {
			_payload_bytes = header.v2.payload_size + 1u;
			packet_size = header.v2.packet_size + 1u;
		} else if (version == 3u) {
			_payload_bytes = header.v3.payload_size + 1u;
			packet_size = header.v3.packet_size + 1u;
		} else {
			goto BAD_VERSION; // This should never execute as version has already been checked
		}

		if (_payload == nullptr) {
			_payload = new uint8_t[packet_size];
			_payload_capacity = packet_size;

		} else if (_payload_capacity < packet_size) {
			delete[] _payload;
			_payload = new uint8_t[packet_size];
			_payload_capacity = packet_size;
		}
		
		if(_payload == nullptr) throw std::runtime_error("PacketInputPipe::ReadNextPacket : Failed to allocate payload buffer");

		_downstream_pipe.ForceReadBytes(_payload, packet_size - header_size, throwaway, _timeout_ms);
		_payload_read_head = 0u;
	}

	// PacketOutputPipe

	PacketOutputPipe::PacketOutputPipe(OutputPipe& downstream_pipe, const size_t packet_size, bool fixed_sized_packets) :
		_downstream_pipe(downstream_pipe),
		_payload(nullptr),
		_current_packet_size(0u),
		_fixed_size_packets(fixed_sized_packets)
	{
		_packet_size = packet_size;
		if (_packet_size <= sizeof(PacketHeaderVersion1)) _packet_size = sizeof(PacketHeaderVersion1) + 1u;

		_version = PacketVersionFromSize(_packet_size);
		_header_size = g_header_sizes[_version - 1u];
		_max_payload_size = _packet_size - _header_size;
		_payload = new uint8_t[_max_payload_size];
	}

	PacketOutputPipe::~PacketOutputPipe() {
		_Flush(_payload, _current_packet_size);
		 delete[] _payload;
		 _payload = nullptr;
	}

	void PacketOutputPipe::WriteBytesInternal(const void* src, const size_t bytes) {
		const uint8_t* data = static_cast<const uint8_t*>(src);
		size_t b = bytes;


		while (b > 0) {
			// If there is data buffered in the current packet
			if (_current_packet_size > 0) {
WRITE_TO_BUFFER:
				// Copy to the packet buffer
				size_t bytes_to_buffer = _max_payload_size - _current_packet_size;
				if (b < bytes_to_buffer) bytes_to_buffer = b;

				memcpy(_payload + _current_packet_size, data, bytes_to_buffer);

				data += bytes_to_buffer;
				b -= bytes_to_buffer;
				_current_packet_size += bytes_to_buffer;

				// If the packet is full then write it
				if (_current_packet_size == _max_payload_size) _Flush(_payload, _current_packet_size);

			} else {
				// If the input data is larger than a packet
				if (b > _max_payload_size) {
					// Send packet directly from input memory
					_Flush(data, _max_payload_size);
					data += _max_payload_size;
					b -= _max_payload_size;

				} else {
					goto WRITE_TO_BUFFER;
				}
			}
		}
	}

	size_t PacketOutputPipe::WriteBytes(const void* src, const size_t bytes) {
		WriteBytesInternal(src, bytes);
		return bytes;
	}

	#pragma warning( disable : 4100) // timeout_ms is not used, name is retained to improve code readability
	void PacketOutputPipe::WriteBytes(const void** src, const size_t* bytes, const size_t count, int timeout_ms) {
		for (size_t i = 0; i < count; ++i) WriteBytesInternal(src[i], bytes[i]);
	}

	void PacketOutputPipe::_Flush(const void* buffer, size_t bytes_in_buffer) {
		if (bytes_in_buffer == 0u) return;

		const size_t packet_size = (_fixed_size_packets ? _packet_size : bytes_in_buffer + _header_size);
		if (bytes_in_buffer + _header_size > packet_size) throw std::runtime_error("PacketOutputPipe::_Flush : Packet is too large");

		PacketHeader header;
		if (_version == 1u) {
			// Create the header
			header.v1.packet_version = 1u;
			header.v1.reseved = 0u;
			header.v1.payload_size = bytes_in_buffer - 1u;
			header.v1.packet_size = packet_size - 1u;
			ANVIL_RUNTIME_ASSERT(_header_size == sizeof(PacketHeaderVersion1), "PacketOutputPipe::_Flush : Header size is wrong");
		} else if (_version == 2u) {
			// Create the header
			header.v2.packet_version = 2u;
			header.v2.payload_size = bytes_in_buffer - 1u;
			header.v2.packet_size = packet_size - 1u;
			ANVIL_RUNTIME_ASSERT(_header_size == sizeof(PacketHeaderVersion2), "PacketOutputPipe::_Flush : Header size is wrong");
		} else if (_version == 3u) {
			// Create the header
			header.v3.packet_version = 3u;
			header.v3.reseved = 0u;
			header.v3.payload_size = bytes_in_buffer - 1u;
			header.v3.packet_size = packet_size - 1u;
			ANVIL_RUNTIME_ASSERT(_header_size == sizeof(PacketHeaderVersion3), "PacketOutputPipe::_Flush : Header size is wrong");
		}

		// Write the packet to the downstream pipe
		const void* addresses[3] = { &header, buffer, nullptr };
		size_t bytes_to_write[3] = { _header_size, bytes_in_buffer, 0u };

		bytes_to_write[2] = packet_size - (bytes_in_buffer + _header_size);
		if (bytes_to_write[2] > 0) {
			addresses[2] = _malloca(bytes_to_write[2]);
			ANVIL_RUNTIME_ASSERT(addresses[2] != nullptr, "PacketOutputPipe::_Flush : Failed to allocate padding");
			memset(const_cast<void*>(addresses[2]), 0, bytes_to_write[2]);
		}

		_downstream_pipe.WriteBytes(addresses, bytes_to_write, 3);

		if (addresses[2] != nullptr) _freea(const_cast<void*>(addresses[2]));


		// Reset the state of this pipe
		if(buffer == _payload) _current_packet_size = 0u;
	}

	void PacketOutputPipe::Flush() {
		_Flush(_payload, _current_packet_size);
		_downstream_pipe.Flush();
	}

}}