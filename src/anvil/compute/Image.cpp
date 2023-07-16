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

	Image::MemoryBlock::MemoryBlock(size_t a_bytes) :
		data(operator new (a_bytes)),
		bytes(a_bytes)
	{
		ANVIL_RUNTIME_ASSERT(data, "anvil::compute::Image::Allocate : Failed to allocate memory");
	}

	Image::MemoryBlock::~MemoryBlock() {
		if (data) {
			operator delete(data);
			data = nullptr;
			bytes = 0u;
		}
	}


	// Image 

	Image::Image() :
		_parent(nullptr),
		_data(nullptr),
		_row_step(0u),
		_pixel_step(0u),
		_width(0u),
		_height(0u),
		_type()
	{}

	Image::~Image() {
		Deallocate();
	}

	Image::Image(const Type type, size_t width, size_t height) :
		Image()
	{
		Allocate(type, width, height);
	}

	Image::Image(void* data, const Type type, size_t width, size_t height, size_t row_step, size_t pixel_step) :
		_parent(nullptr),
		_data(data),
		_row_step(row_step),
		_pixel_step(pixel_step),
		_width(width),
		_height(height),
		_type(type)
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

	void Image::Allocate(Type type, size_t width, size_t height, bool force) {
		// Check if the requested image is the same as the current one and the allocation isn't forced
		if (type == _type && _width == width && _height == height && !force) {
			return;
		}

		// If this is the only image using the memory block then don't need to worry about parent/child images
		if (_memory_manager.use_count() == 1u) {
			// If the current memory is large enough then we can re-use it efficently
			size_t pixel_bytes = type.GetSizeInBytes();
			if (_memory_manager->bytes >= pixel_bytes * width * height) {
				_parent = nullptr;
				_pixel_step = pixel_bytes;
				_row_step = _pixel_step * width;
				_data = _memory_manager->data;
				_width = width;
				_height = height;
				_type = type;
				return;
			}
		}

		// If this isn't a forced allcoation we can try to reinterpret the pixel type
		if ((!force) && _type.GetSizeInBytes() == type.GetSizeInBytes()) {
			if (TryReinterpretAs(type, width, height, true)) return;
		}

		// Otherwise we need to deallocate the current block and allocate a new one
		if (_memory_manager) {
			std::shared_ptr<MemoryBlock> tmp;
			_memory_manager.swap(tmp);
		}
		_parent = nullptr;
		_pixel_step = type.GetSizeInBytes();
		_row_step = _pixel_step * width;
		_memory_manager.reset(new MemoryBlock(_row_step * height));
		_data = _memory_manager->data;
		_width = width;
		_height = height;
		_type = type;
	}

	void Image::Deallocate() {
		if (_memory_manager) {
			std::shared_ptr<MemoryBlock> tmp;
			_memory_manager.swap(tmp);
		}
		_parent = nullptr;
		_data = nullptr;
		_width = 0u;
		_height = 0u;
	}

	bool Image::TryReinterpretAs(Type type, size_t width, size_t height, bool allow_reinterpret_as_smaller) {
		const size_t current_pixel_bytes = _type.GetSizeInBytes();
		const size_t new_pixel_bytes = type.GetSizeInBytes();

		size_t current_bytes = 0u;
		size_t new_bytes = 0u;

		if (_pixel_step != current_bytes) {
			// Can only reinterpret pixels
			current_bytes = current_pixel_bytes;
			new_bytes = new_pixel_bytes;

		} else if (_row_step != current_pixel_bytes * _width) {
			// Can only reinterpret rows
			if (height > _height) return false;
			current_bytes = current_pixel_bytes * _width;
			new_bytes = new_pixel_bytes * width;

		} else {
			// Can reinterpret whole image
			current_bytes = current_pixel_bytes * _width * _height;
			new_bytes = new_pixel_bytes * width * height;
		}

		if (current_bytes == new_bytes || (allow_reinterpret_as_smaller && current_bytes > new_bytes)) {
			_type = type;
			_width = width;
			_height = height;
			return true;
		}

		return false;
	}

	Image* Image::GetParent() throw() {
		// Check if the parent has been destroyed or reallocated
		if (_parent && (_memory_manager.use_count() <= 1 || _parent->_memory_manager != _memory_manager)) {
			_parent = nullptr;
		}

		return _parent;
	}

	void Image::ConvertToInPlace(Type type) {
		if (_type == type) return;

		if (_type.GetSizeInBytes() != type.GetSizeInBytes()) {
			Image tmp(type, _width, _height);

			//! \todo Optimise
			for (size_t y = 0u; y < _height; ++y) {
				for (size_t x = 0u; x < _width; ++x) {
					Vector pixel;
					ReadPixel(x, y, pixel);
					pixel.ConvertToInPlace(type);
					tmp.WritePixel(x, y, pixel);
				}
			}

			Swap(tmp);

		} else {
			//! \todo Optimise
			for (size_t y = 0u; y < _height; ++y) {
				for (size_t x = 0u; x < _width; ++x) {
					Vector pixel;
					ReadPixel(x, y, pixel);
					pixel.ConvertToInPlace(type);
					WritePixel(x, y, pixel);
				}
			}
		}
	}

	Image Image::ConvertTo(Type type) const {
		// Only copy the image once
		Image tmp = _type.GetSizeInBytes() == type.GetSizeInBytes() ? DeepCopy() : const_cast<Image*>(this)->ShallowCopy();
		
		// Perform conversion
		tmp.ConvertToInPlace(type);
		return tmp;
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

	void Image::DeepCopyTo(Image& other) const {
		other.Allocate(_type, _width, _height, false);

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

	Image Image::GetChannels(size_t index, size_t count) {
		const size_t channels = _type.GetNumberOfChannels();
		ANVIL_DEBUG_ASSERT(count > 0, "anvil::Image::GetChannels : Channel count cannot be 0");
		ANVIL_RUNTIME_ASSERT(index + count <= channels, "anvil::Image::GetChannels : Index out of bounds");

		Image tmp = ShallowCopy();

		// Move the start of the row to the correct channel
		tmp._type.SetNumberOfChannels(count);
		tmp._data = static_cast<uint8_t*>(tmp._data) + tmp._type.GetSizeInBytes() * index;

		return tmp;
	}

	std::list<Image> Image::GetAllChannels() {
		std::list<Image> channels;
		size_t count = _type.GetNumberOfChannels();
		for (size_t i = 0u; i < count; ++i) {
			channels.push_back(GetChannel(i));
		}
		return channels;
	}

	void Image::GetRoiPosition(size_t& x, size_t& y) const {
		x = 0u;
		y = 0u;

		if (!_parent) return;

		size_t byte_offset = static_cast<const uint8_t*>(_data) - static_cast<const uint8_t*>(_parent->_data);

		y = byte_offset / _row_step;
		x = (byte_offset - (_row_step * y)) / _pixel_step;
	}

	void Image::GetRoiPosition(const Image& img, size_t& x, size_t& y) const {
		x = 0u;
		y = 0u;

		ANVIL_RUNTIME_ASSERT(_parent != nullptr, "anvil::Image::GetRoiPosition : Image is not a decendent of the provided image");

		if (_parent == &img) {
			GetRoiPosition(x, y);
			return;
		}

		_parent->GetRoiPosition(img, x, y);

		size_t x2, y2;
		GetRoiPosition(x2, y2);

		x += x2;
		y += y2;
	}
}}