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

	PacketInputPipe::PacketInputPipe(InputPipe& downstream_pipe) :
		_downstream_pipe(downstream_pipe),
		_buffer_read_head(0u)
	{
		read2_faster = 1;
	}

	PacketInputPipe::~PacketInputPipe() {

	}

	void PacketInputPipe::ReadNextPacket() {

		uint64_t used_bytes, packet_size;

		// Read the packet header version
		PacketHeader header;
		size_t read = _downstream_pipe.ReadBytes(&header, 1u);

		// Error checking
		if (read != 1u) throw std::runtime_error("PacketInputPipe::ReadNextPacket : Failed to read packet version");
		uint32_t version = header.v1.packet_version;
		if (version >= 3u) version = header.v3.packet_version; // Read the extended version number
		if (header.v1.packet_version == 0 || header.v1.packet_version > 3u) {
BAD_VERSION:
			throw std::runtime_error("PacketInputPipe::ReadNextPacket : Packet version is not supported");
		}

		// Read the rest of the header
		const size_t header_size = g_header_sizes[header.v1.packet_version - 1u];
		read = _downstream_pipe.ReadBytes(reinterpret_cast<uint8_t*>(&header) + 1u, header_size - 1u);

		// Allocate a temporary buffer for the data
		//! \bug Packets larger than UINT32_MAX will cause an integer overflow on the byte count

		if (version == 1u) {
			used_bytes = header.v1.used_size;
			packet_size = header.v1.packet_size;
		} else if (version == 2u) {
			used_bytes = header.v2.used_size;
			packet_size = header.v2.packet_size;
		} else if (version == 3u) {
			used_bytes = header.v3.used_size;
			packet_size = header.v3.packet_size;
		} else {
			goto BAD_VERSION; // This should never execute as version has already been checked
		}

		used_bytes += 1u;
		packet_size += 1u;

		// Align read head to start of buffer
		if (_buffer_read_head != 0u) {
			size_t bytes_in_buffer = _buffer_a.size() - _buffer_read_head;
			_buffer_b.resize(bytes_in_buffer);
			memcpy(_buffer_b.data(), _buffer_a.data() + _buffer_read_head, bytes_in_buffer);

			std::swap(_buffer_a, _buffer_b);
			_buffer_read_head = 0u;
		}

		// Make sure the buffer is big enough to stor the packet
		const size_t prev_buffer_size = _buffer_a.size();
		_buffer_a.resize(prev_buffer_size + packet_size);

		// Read the data into the buffer

		const uint64_t unused_bytes = (packet_size - header_size) - used_bytes;
		read = _downstream_pipe.ReadBytes(_buffer_a.data() + prev_buffer_size, static_cast<uint32_t>(used_bytes + unused_bytes));
		if (read != used_bytes + unused_bytes) throw std::runtime_error("PacketInputPipe::ReadNextPacket : Failed reading used packet data");

		// Remove unused bytes from the buffer
		_buffer_a.resize(prev_buffer_size + used_bytes);
	}

	size_t PacketInputPipe::ReadBytes(void* dst, const size_t bytes) {
		size_t bytes_read = 0u;
		const void* tmp = ReadBytes2(bytes, bytes_read);
		memcpy(dst, tmp, bytes_read);
		return bytes_read;
	}

	const void* PacketInputPipe::ReadBytes2(const size_t bytes_requested, size_t& bytes_actual) {
		if (bytes_requested == 0u) {
NO_DATA:
			bytes_actual = 0u;
			return nullptr;
		}

		if (_buffer_a.empty()) ReadNextPacket();
		if (_buffer_a.empty()) goto NO_DATA;

		bytes_actual = _buffer_a.size() - _buffer_read_head;
		if (bytes_actual > bytes_requested) bytes_actual = bytes_requested;

		void* address = _buffer_a.data() + _buffer_read_head;

		_buffer_read_head += bytes_actual;
		if (_buffer_read_head >= _buffer_a.size()) bytes_actual = _buffer_read_head;

		return address;
	}

	// PacketOutputPipe

	PacketOutputPipe::PacketOutputPipe(OutputPipe& downstream_pipe, const size_t packet_size, const uint8_t default_word) :
		_downstream_pipe(downstream_pipe),
		_buffer(nullptr),
		_max_packet_size(0u),
		_current_packet_size(0u),
		_default_word(default_word)
	{
		uint32_t version = PacketVersionFromSize(packet_size);
		uint32_t header_size = g_header_sizes[version];
		_max_packet_size = packet_size - header_size;
		_buffer = new uint8_t[packet_size]; // _max_packet_size + header_size
	}

	PacketOutputPipe::~PacketOutputPipe() {
		 _Flush();
		 delete[] _buffer;
		 _buffer = nullptr;
	}

	size_t PacketOutputPipe::WriteBytes(const void* src, const size_t bytes) {
		const uint32_t version = PacketVersionFromSize(_max_packet_size);
		const uint32_t header_size = g_header_sizes[version];

		//PacketHeader& header = *reinterpret_cast<PacketHeader*>(_buffer);
		uint8_t* payload = _buffer + header_size;

		const uint8_t* data = static_cast<const uint8_t*>(src);
		size_t b = bytes;

		while (b != 0u) {
			// Copy to the packet buffer
			size_t bytes_to_buffer = _max_packet_size - _current_packet_size;
			if (b < bytes_to_buffer) bytes_to_buffer = b;

			memcpy(payload + _current_packet_size, data, bytes_to_buffer);

			data += bytes_to_buffer;
			b -= bytes_to_buffer;
			_current_packet_size += bytes_to_buffer;

			// If the packet is ready then write it
			if (_current_packet_size == _max_packet_size) _Flush();
		}

		return bytes;
	}

	void PacketOutputPipe::_Flush() {
		if (_current_packet_size == 0u) return;

		const uint32_t version = PacketVersionFromSize(_max_packet_size);
		const uint32_t header_size = g_header_sizes[version];

		PacketHeader& header = *reinterpret_cast<PacketHeader*>(_buffer);
		uint8_t* payload = _buffer + header_size;

		// 'Zero' unused data in the packet
		memset(payload + _current_packet_size, _default_word, _max_packet_size - _current_packet_size);

		if (version == 1u) {
			// Create the header
			header.v1.packet_version = 1u;
			header.v1.reseved = 0u;
			header.v1.used_size = _current_packet_size - 1u;
			header.v1.packet_size = (_max_packet_size + header_size) - 1u;
		} else if (version == 2u) {
			// Create the header
			header.v2.packet_version = 2u;
			header.v2.used_size = _current_packet_size - 1u;
			header.v2.packet_size = (_max_packet_size + header_size) - 1u;
		} else if (version == 3u) {
			// Create the header
			header.v3.packet_version = 3u;
			header.v3.reseved = 0u;
			header.v3.used_size = _current_packet_size - 1u;
			header.v3.packet_size = (_max_packet_size + header_size) - 1u;
		}

		// Write the packet to the downstream pipe
		//! \bug Packets larger than UINT32_MAX will cause an integer overflow on the byte count
		_downstream_pipe.WriteBytes(_buffer, static_cast<uint32_t>(_max_packet_size + header_size));

		// Reset the state of this pipe
		_current_packet_size = 0u;
	}

	void PacketOutputPipe::Flush() {
		_Flush();
		_downstream_pipe.Flush();
	}

}}