//Copyright 2023 Adam G. Smith
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

#include "anvil/compute/Image.hpp"

namespace anvil { namespace compute {

	// Image 

	Image::Image() :
		_parent(nullptr),
		_data(nullptr),
		_row_step(0u),
		_pixel_step(0u),
		_width(0u),
		_height(0u),
		_type(),
		_owned_memory(false)
	{}

	Image::~Image() {
		Deallocate();
	}

	Image::Image(const Type type, size_t width, size_t height) :
		Image()
	{
		Allocate(type, width, height, false);
	}

	Image::Image(void* data, const Type type, size_t width, size_t height, size_t row_step, size_t pixel_step) :
		_parent(nullptr),
		_data(data),
		_row_step(row_step),
		_pixel_step(pixel_step),
		_width(width),
		_height(height),
		_type(type),
		_owned_memory(false)
	{}

	Image::Image(void* data, const Type type, size_t width, size_t height, size_t row_step) :
		Image(data, type, width, height, row_step, type.GetSizeInBytes())
	{}

	Image::Image(void* data, const Type type, size_t width, size_t height) :
		Image(data, type, width, height, type.GetSizeInBytes() * width)
	{}	
	
	Image::Image(Image&& other) :
		Image()
	{
		Swap(other);
	}

	Image& Image::operator=(Image&& other) {
		Swap(other);
		return *this;
	}

	void Image::Swap(Image& other) {
		uint8_t buffer[sizeof(Image)];
		memcpy(buffer, this, sizeof(Image));
		memcpy(this, &other, sizeof(Image));
		memcpy(&other, buffer, sizeof(Image));
	}

	void Image::Allocate(Type type, size_t width, size_t height, bool allow_reinterpret, bool allow_reinterpret_as_smaller) {
		ANVIL_DEBUG_ASSERT(
			allow_reinterpret_as_smaller ? allow_reinterpret : true, 
			"anvil::compute::Image::Allocate : allow_reinterpret_as_smaller should not be true when allow_reinterpret is false"
		);

		if (allow_reinterpret && TryReinterpretAs(type, width, height, allow_reinterpret_as_smaller)) return;

		Deallocate();
		_pixel_step = type.GetSizeInBytes();
		_row_step = _pixel_step * width;
		_data = operator new(_row_step * height);
		ANVIL_RUNTIME_ASSERT(_data, "anvil::compute::Image::Allocate : Failed to allocate memory");
		_owned_memory = true;
		_width = width;
		_height = height;
		_type = type;
	}

	void Image::Deallocate() {
		if (_owned_memory) {
			if (_data) operator delete(_data);
		}
		_parent = nullptr;
		_data = nullptr;
		_width = 0u;
		_height = 0u;
	}

	bool Image::TryReinterpretAs(Type type, size_t width, size_t height, bool allow_reinterpret_as_smaller) {
		const size_t current_pixel_bytes = _type.GetSizeInBytes();
		const size_t new_pixel_bytes = type.GetSizeInBytes();

		if (_pixel_step != current_pixel_bytes) return false;

		size_t current_bytes = 0u;
		size_t new_bytes = 0u;

		if (_row_step == current_pixel_bytes * _width) {
			// Can reinterpret whole image
			current_bytes = current_pixel_bytes * _width * _height;
			new_bytes = new_pixel_bytes * width * height;
			
		} else {
			// Can only reinterpret rows
			if (height > _height) return false;
			current_bytes = current_pixel_bytes * _width;
			new_bytes = new_pixel_bytes * width;
		}

		if (current_bytes == new_bytes || (allow_reinterpret_as_smaller && current_bytes > new_bytes)) {
			_type = type;
			_width = width;
			_height = height;
			return true;
		}

		return false;
	}

	void Image::ConvertToInPlace(Type type) {
		if (_type == type) return;

		//! \todo Optimise
		if (_type.GetNumberOfChannels() == 1u) {
			for (size_t y = 0u; y < _height; ++y) {
				for (size_t x = 0u; x < _width; ++x) {
					TypedScalar tmp;
					ReadPixel(x, y, tmp);
					tmp.ConvertToInPlace(type);
					WritePixel(x, y, tmp);
				}
			}
		} else {
			for (size_t y = 0u; y < _height; ++y) {
				for (size_t x = 0u; x < _width; ++x) {
					Vector tmp;
					ReadPixel(x, y, tmp);
					tmp.ConvertToInPlace(type);
					WritePixel(x, y, tmp);
				}
			}
		}
	}

	bool Image::operator==(const Image& other) const throw() {
		if (_type != other._type || _width != other._width || _height != other._height) return false;
		if (_data == other._data) return true;

		size_t pixel_bytes = _type.GetSizeInBytes();
		if (_pixel_step == pixel_bytes && other._pixel_step == pixel_bytes) {
			const size_t row_bytes = _type.GetSizeInBytes() * _width;
			for (size_t y = 0u; y < _height; ++y) {
				if (memcmp(other.GetRowAddress(y), GetRowAddress(0), row_bytes) != 0) return false;
			}
		} else {
			for (size_t y = 0u; y < _height; ++y) {
				for (size_t x = 0u; x < _width; ++x) {
					if (memcmp(GetPixelAddress(x, y), other.GetPixelAddress(x, y), pixel_bytes) != 0) return false;
				}
			}
		}

		return true;
	}

	void Image::CopyTo(Image& other) const {
		other.Allocate(_type, _width, _height, true);

		const size_t pixel_bytes = _type.GetSizeInBytes();
		const size_t row_bytes = pixel_bytes * _width;
		if (_pixel_step == pixel_bytes) {
			for (size_t y = 0u; y < _height; ++y) memcpy(other.GetPixelAddress(0, y), GetPixelAddress(0, y), row_bytes);

		} else {
			//! \todo Optimise
			for (size_t y = 0u; y < _height; ++y) {
				for (size_t x = 0u; x < _height; ++x) {
					Vector tmp;
					ReadPixel(x, y, tmp);
					other.WritePixel(x, y, tmp);
				}
			}
		}
	}

	Image Image::GetRoi(size_t x, size_t y, size_t width, size_t height) {
		ANVIL_RUNTIME_ASSERT(width + x <= _width, "anvil::Image::GetRoi : Out of bounds on X axis");
		ANVIL_RUNTIME_ASSERT(height + y <= _height, "anvil::Image::GetRoi : Out of bounds on Y axis");
		Image tmp(GetPixelAddress(x,y), _type, width, height, _row_step, _pixel_step);
		tmp._parent = this;
		return tmp;
	}

	Image Image::GetChannel(size_t index) {
		const size_t channels = _type.GetNumberOfChannels();
		ANVIL_RUNTIME_ASSERT(index < channels, "anvil::Image::GetChannel : Index out of bounds");

		// Make a 'reference' to this image
		Image tmp = GetRoi(0u, 0u, _width, _height);

		// Move the start of the row to the correct channel
		tmp._type.SetNumberOfChannels(1u);
		tmp._data = static_cast<uint8_t*>(tmp._data) + tmp._type.GetSizeInBytes() * index;

		return tmp;
	}

	void Image::GetRoiPosition(size_t& x, size_t& y) const {
		x = 0u;
		y = 0u;

		if (!_parent) return;

		size_t byte_offset = static_cast<const uint8_t*>(_data) - static_cast<const uint8_t*>(_parent->_data);

		y = byte_offset / _row_step;
		x = (byte_offset - (_row_step * y)) / _pixel_step;
	}
}}