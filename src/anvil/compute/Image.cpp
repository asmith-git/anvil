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
		_data(nullptr),
		_step(0u),
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

	Image::Image(void* data, const Type type, size_t width, size_t height, size_t step) :
		_data(data),
		_step(step),
		_width(width),
		_height(height),
		_type(type),
		_owned_memory(false)
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

	void Image::Allocate(Type type, size_t width, size_t height, bool allow_reinterpret) {
		if (allow_reinterpret && TryReinterpretAs(type, width, height)) return;

		Deallocate();
		_data = operator new(type.GetPrimitiveSizeInBytes() * width * height);
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
		_data = nullptr;
		_width = 0u;
		_height = 0u;
	}

	bool Image::TryReinterpretAs(Type type, size_t width, size_t height) {
		const size_t current_pixel_bytes = _type.GetSizeInBytes();
		const size_t new_pixel_bytes = type.GetSizeInBytes();

		// If 
		if (_step == current_pixel_bytes * _width) {
			// Can reinterpret whole image
			if (current_pixel_bytes * _width * _height == new_pixel_bytes * width * height) {
				_type = type;
				_width = width;
				_height = height;
				return true;
			}
		} else {
			// Can only reinterpret rows
			if (current_pixel_bytes * _width == new_pixel_bytes * width && _height == height) {
				_type = type;
				_width = width;
				_height = height;
				return true;
			}
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

		const size_t row_bytes = _type.GetSizeInBytes() * _width;
		for (size_t y = 0u; y < _height; ++y) {
			if (memcmp(other.GetPixelAddress(0, y), GetPixelAddress(0, y), row_bytes) != 0) return false;
		}

		return true;
	}

	void Image::CopyTo(Image& other) const {
		other.Allocate(_type, _width, _height, true);

		const size_t row_bytes = _type.GetSizeInBytes() * _width;
		for (size_t y = 0u; y < _height; ++y) memcpy(other.GetPixelAddress(0, y), GetPixelAddress(0, y), row_bytes);
	}
}}