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

#if ANVIL_OPENCV_SUPPORT
	Image::MemoryBlock::MemoryBlock(cv::Mat mat) :
		data(nullptr),
		bytes(0u),
		cv_mat(mat),
		mode(OCV_BLOCK)
	{}
#endif

	Image::MemoryBlock::MemoryBlock(size_t a_bytes) :
		data(Image::GetAllocator()->Allocate(a_bytes)),
		bytes(a_bytes),
		mode(ANVIL_BLOCK)
	{
		ANVIL_RUNTIME_ASSERT(data, "anvil::compute::Image::Allocate : Failed to allocate memory");
	}

	Image::MemoryBlock::~MemoryBlock() {
		if (data) {
			Image::GetAllocator()->Deallocate(data);
			data = nullptr;
			bytes = 0u;
		}
	}


	// Image 	
	
	static Allocator* g_image_allocator_override = nullptr;

	Allocator* Image::GetAllocator() {
		return g_image_allocator_override ? g_image_allocator_override : Allocator::GetDefaultAllocator();
	}

	void Image::SetAllocator(Allocator* allocator) {
		g_image_allocator_override = allocator;
	}

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
	
	Image::Image(Image& other) :
		Image()
	{
		Image tmp = other.ShallowCopy();
		Swap(tmp);
	}

#if ANVIL_OPENCV_SUPPORT
	Image::Image(const cv::Mat& mat) :
		Image(mat.data, Type::FromOpenCVType(mat.type()), (size_t)mat.cols, (size_t)mat.rows, (size_t)mat.step1())
	{
		_memory_manager.reset(new MemoryBlock(mat));
	}
#endif

	Image& Image::operator=(Image&& other) {
		Swap(other);
		return *this;
	}

	Image& Image::operator=(Image& other) {
		Deallocate();
		Swap(other);
		return *this;
	}

	void Image::Swap(Image& other) {
		std::swap(_memory_manager, other._memory_manager);
		std::swap(_parent, other._parent);
		std::swap(_data, other._data);
		std::swap(_row_step, other._row_step);
		std::swap(_pixel_step, other._pixel_step);
		std::swap(_width, other._width);
		std::swap(_height, other._height);
	}

	uint32_t Image::Allocate(Type type, size_t width, size_t height, uint32_t flags) {

		// Check if the requested image is the same as the current one and the allocation isn't forced
		if (type == _type && _width == width && _height == height && (flags & ALLOW_REINTERPRET)) {
			return REINTERPRETED;
		}

		// If this is the only image using the memory block then don't need to worry about parent/child images
		if (_memory_manager.use_count() == 1u && _memory_manager->mode == MemoryBlock::ANVIL_BLOCK && (flags && ALLOW_REALLOCATE)) {
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
				return REALLOCATED;// Technically a reinterpretation but should be treated by external code as a reallocation
			}
		}

		// If this isn't a forced allcoation we can try to reinterpret the pixel type
		if ((flags & ALLOW_REINTERPRET) && _type.GetSizeInBytes() == type.GetSizeInBytes()) {
			if (ReinterpretAsInPlace(type, width, height, ALLOW_REINTERPRET) & REINTERPRETED) {
				return REINTERPRETED;
			}
		}

		// Otherwise we need to deallocate the current block and allocate a new one
		if (flags & ALLOW_REALLOCATE) {
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
			return REALLOCATED;
		}

		throw std::runtime_error("anvil::compute::Image::Allocate : Failed to allocate image");
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

	uint32_t Image::ReinterpretAsInPlace(Type type, size_t width, size_t height, uint32_t flags) {
		const size_t current_pixel_bytes = _type.GetSizeInBytes();
		const size_t new_pixel_bytes = type.GetSizeInBytes();

		if(flags & ALLOW_REINTERPRET) {
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

			if (current_bytes == new_bytes || (current_bytes > new_bytes)) {
				_type = type;
				_width = width;
				_height = height;
				return REINTERPRETED;
			}
		}

		if ((flags & ALLOW_REALLOCATE) && new_pixel_bytes >= current_pixel_bytes) {
			//! \todo Optimise
			Image tmp(type, width, height);
			for (size_t y = 0u; y < _height; ++y) {
				for (size_t x = 0u; x < _width; ++x) {
					const void* this_pixel = GetPixelAddress(x, y);
					void* new_pixel = tmp.GetPixelAddress(x, y);
					memcpy(new_pixel, this_pixel, current_pixel_bytes);
					memset(static_cast<uint8_t*>(new_pixel) + current_pixel_bytes, 0, current_pixel_bytes - new_pixel_bytes);
				}
			}
			Swap(tmp);
			return REALLOCATED;
		}

		return 0u;
	}
	
	Image Image::ReinterpretAs(Type type, size_t width, size_t height, uint32_t flags, uint32_t* flags_out) {
		Image tmp = ShallowCopy();
		flags = tmp.ReinterpretAsInPlace(type, width, height, flags);
		if (flags_out) *flags_out = flags;
		return tmp;
	}

	Image Image::ReinterpretAs(Type type, size_t width, size_t height, uint32_t flags, uint32_t* flags_out) const {
		ANVIL_RUNTIME_ASSERT(flags == ALLOW_REALLOCATE, "anvil::compute::Image::ReinterpretAs : ALLOW_REALLOCATE is the only flag allowed for a const image")

		Image tmp = const_cast<Image*>(this)->ShallowCopy();
		flags = tmp.ReinterpretAsInPlace(type, width, height, flags);

		if ((flags & REALLOCATED) == 0) {
			tmp = tmp.DeepCopy();
			flags = REALLOCATED;
		}

		if (flags_out) *flags_out = flags;
		return tmp;
	}

	Image* Image::GetParent() throw() {
		// Check if the parent has been destroyed or reallocated
		if (_parent && (_memory_manager.use_count() <= 1 || _parent->_memory_manager != _memory_manager)) {
			_parent = nullptr;
		}

		return _parent;
	}

	uint32_t Image::ConvertToInPlace(Type type, uint32_t flags) {
		if (_type == type) return REINTERPRETED;

		if (ReinterpretAsInPlace(type, _width, _height, flags & ALLOW_REINTERPRET)) {
			//! \todo Optimise
			const Type previous_type = type;
			for (size_t y = 0u; y < _height; ++y) {
				for (size_t x = 0u; x < _width; ++x) {
					Vector pixel;
					ReadPixel(x, y, pixel.GetData());
					pixel.ForceSetType(previous_type);
					pixel.ConvertToInPlace(type);
					WritePixel(x, y, pixel.GetData());
				}
			}
			return REINTERPRETED;
		}

		if (flags & ALLOW_REALLOCATE) {
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
			return REALLOCATED;
		}

		throw std::runtime_error("anvil::compute::Image::ConvertToInPlace : Failed to convert image");
	}

	Image Image::ConvertTo(Type type, uint32_t flags, uint32_t* flags_out) {
		if (type == _type) return ShallowCopy();

		Image tmp = ShallowCopy();
		
		// Perform conversion
		flags = tmp.ConvertToInPlace(type, flags);
		if (flags_out) *flags_out = flags;
		return tmp;
	}

	Image Image::ConvertTo(Type type, uint32_t flags, uint32_t* flags_out) const {
		ANVIL_RUNTIME_ASSERT(flags == ALLOW_REALLOCATE, "anvil::compute::Image::ConvertTo : ALLOW_REALLOCATE is the only flag allowed for a const image")
		if (type == _type) return DeepCopy();

		Image tmp = const_cast<Image*>(this)->ShallowCopy();

		// Perform conversion
		flags = tmp.ConvertToInPlace(type, flags);

		if ((flags & REALLOCATED) == 0) {
			tmp = tmp.DeepCopy();
			flags = REALLOCATED;
		}

		if (flags_out) *flags_out = flags;
		return tmp;
	}

	uint32_t Image::TransposeInPlace(uint32_t flags) {

		if ((_width <= 1u || _height <= 1u) && (flags & ALLOW_REINTERPRET)) {
			if (ReinterpretAsInPlace(_type, _height, _width, ALLOW_REINTERPRET) & ALLOW_REINTERPRET) return REINTERPRETED;
		}

		//! \todo Optimise
		Image tmp(_type, _height, _width);
		for (size_t y = 0u; y < _height; ++y) {
			for (size_t x = 0u; x < _width; ++x) {
				tmp.WritePixel(y, x, GetPixelAddress(x, y));
			}
		}
		if (flags & ALLOW_REALLOCATE) {
			Swap(tmp);
			return REALLOCATED;
		}

		if (flags & ALLOW_REINTERPRET) {
			if (ReinterpretAsInPlace(_type, _height, _width, ALLOW_REINTERPRET) & ALLOW_REINTERPRET) {
				// Copy pixels back to this image
				//! \todo Optimise
				for (size_t y = 0u; y < _height; ++y) {
					for (size_t x = 0u; x < _width; ++x) {
						WritePixel(y, x, tmp.GetPixelAddress(x, y));
					}
				}
				return REINTERPRETED;
			}
		}

		throw std::runtime_error("anvil::compute::Image::TransposeInPlace : Failed to transpose image");
	}

	Image Image::Transpose(uint32_t flags, uint32_t* flags_out) {
		Image tmp = ShallowCopy();
		flags = tmp.TransposeInPlace(flags);
		if (flags_out) *flags_out = flags;
		return tmp;
	}

	Image Image::Transpose(uint32_t flags, uint32_t* flags_out) const {
		ANVIL_RUNTIME_ASSERT(flags == ALLOW_REALLOCATE, "anvil::compute::Image::Transpose : ALLOW_REALLOCATE is the only flag permitted on a const image");
		Image tmp = const_cast<Image*>(this)->ShallowCopy();
		flags = tmp.TransposeInPlace(flags);

		if ((flags & REALLOCATED) == 0) {
			tmp = tmp.DeepCopy();
			flags = REALLOCATED;
		}

		if (flags_out) *flags_out = flags;
		return tmp;
	}

	bool Image::operator==(const Image& other) const throw() {
		if (_type != other._type || _width != other._width || _height != other._height) return false;
		if (_data == other._data) return true;

		size_t pixel_bytes = _type.GetSizeInBytes();
		if (IsContiguous() && other.IsContiguous()) {
			const size_t img_bytes = _type.GetSizeInBytes() * _width * _height;
			if (memcmp(other.GetData(), GetData(), img_bytes) != 0) return false;

		} else if (IsRowContiguous() && other.IsRowContiguous()) {
			const size_t row_bytes = _type.GetSizeInBytes() * _width;
			for (size_t y = 0u; y < _height; ++y) {
				if (memcmp(other.GetRowAddress(y), GetRowAddress(y), row_bytes) != 0) return false;
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
		other.Allocate(_type, _width, _height, ALLOW_REALLOCATE | ALLOW_REINTERPRET);

		if (IsRowContiguous() && other.IsRowContiguous()) {
			const size_t pixel_bytes = _type.GetSizeInBytes();
			const size_t row_bytes = pixel_bytes * _width;
			for (size_t y = 0u; y < _height; ++y) memcpy(other.GetRowAddress(y), GetRowAddress(y), row_bytes);

		} else {
			//! \todo Optimise
			for (size_t y = 0u; y < _height; ++y) {
				for (size_t x = 0u; x < _height; ++x) {
					other.WritePixel(x, y, GetPixelAddress(x, y));
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

	std::list<Image> Image::GetAllChannels() const {
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