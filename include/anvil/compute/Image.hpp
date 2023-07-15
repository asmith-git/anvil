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

#ifndef ANVIL_COMPUTE_IMAGE_HPP
#define ANVIL_COMPUTE_IMAGE_HPP

#include <memory>
#include "anvil/compute/Vector.hpp"
#if ANVIL_OPENCV_SUPPORT
#include<opencv2/core/mat.hpp>
#endif

namespace anvil { namespace compute {

	class ANVIL_DLL_EXPORT Image {
	private:
		void* _data;
		size_t _step;
		size_t _width;
		size_t _height;
		Type _type;
		bool _owned_memory;
	public:
		Image();
		~Image();

		Image(const Type type, size_t width, size_t height);
		Image(void* data, const Type type, size_t width, size_t height);
		Image(void* data, const Type type, size_t width, size_t height, size_t step);

		Image(Image&& other);
		Image(const Image&) = delete;

		Image& operator=(Image&& other);
		Image& operator=(const Image&) = delete;

		void Swap(Image& other);

		void Allocate(Type type, size_t width, size_t height, bool allow_reinterpret = true);
		void Deallocate();

		void CopyTo(Image& other) const;

		ANVIL_STRONG_INLINE Image Copy() const {
			Image tmp;
			CopyTo(tmp);
			return tmp;
		}

		void ConvertToInPlace(Type type);

		ANVIL_STRONG_INLINE Image ConvertTo(Type type) const {
			Image tmp = Copy();
			tmp.ConvertToInPlace(type);
			return tmp;
		}

		bool TryReinterpretAs(Type type, size_t width, size_t height);

		ANVIL_STRONG_INLINE bool TryReinterpretAs(Type type) {
			return TryReinterpretAs(type, _width, _height);
		}

		ANVIL_STRONG_INLINE void ReinterpretAs(Type type, size_t width, size_t height) { 
			ANVIL_RUNTIME_ASSERT(TryReinterpretAs(type, width, height), "anvil::Image::ReinterpretAs : Could not reinterpret image"); 
		}

		ANVIL_STRONG_INLINE void ReinterpretAs(Type type) {
			ReinterpretAs(type, _width, _height);
		}

		bool operator==(const Image& other) const throw();
		ANVIL_STRONG_INLINE bool operator!=(const Image& other) const throw() { return !operator==(other); }

		ANVIL_STRONG_INLINE Type GetType() const throw() { return _type; }

		ANVIL_STRONG_INLINE bool IsContiguous() const throw() {
			return _step == _type.GetSizeInBytes() * _width;
		}

#if ANVIL_OPENCV_SUPPORT
		Image(const cv::Mat& mat) :
			Image(mat.data, Type::FromOpenCVType(mat.type()), (size_t) mat.cols, (size_t) mat.rows, (size_t) mat.step1())
		{}

		ANVIL_STRONG_INLINE operator cv::Mat() {
			return cv::Mat((int)_height, (int)_width, _type.GetOpenCVType(), _data, _step);
		}
#endif

		ANVIL_STRONG_INLINE void* GetData() throw() { return _data; }
		ANVIL_STRONG_INLINE const void* GetData() const throw() { return _data; }

		ANVIL_STRONG_INLINE void* GetPixelAddress(size_t x, size_t y) {
			ANVIL_DEBUG_ASSERT(x < _width, "X position is out of bounds");
			ANVIL_DEBUG_ASSERT(y < _height, "Y position is out of bounds");
			return static_cast<uint8_t*>(_data) + _step * y + x * _type.GetSizeInBytes();
		}

		ANVIL_STRONG_INLINE const void* GetPixelAddress(size_t x, size_t y) const {
			ANVIL_DEBUG_ASSERT(x < _width, "X position is out of bounds");
			ANVIL_DEBUG_ASSERT(y < _height, "Y position is out of bounds");
			return static_cast<const uint8_t*>(_data) + _step * y + x * _type.GetSizeInBytes();
		}

		template<class T>
		ANVIL_STRONG_INLINE void ReadPixel(size_t x, size_t y, T& pixel) const {
			pixel = *reinterpret_cast<T*>(const_cast<void*>(GetPixelAddress(x, y)));
		}

		template<>
		ANVIL_STRONG_INLINE void ReadPixel<UntypedScalar>(size_t x, size_t y, UntypedScalar& pixel) const {
			ANVIL_DEBUG_ASSERT(_type.GetNumberOfChannels() == 1u, "anvil::Image::ReadPixel (UntypedScalar) : Type has more than one channel");
			memcpy(pixel.GetData(), GetPixelAddress(x, y), _type.GetSizeInBytes());
		}

		template<>
		ANVIL_STRONG_INLINE void ReadPixel<TypedScalar>(size_t x, size_t y, TypedScalar& pixel) const {
			ReadPixel(x, y, pixel._scalar);
			pixel._type = _type;
		}

		template<>
		ANVIL_STRONG_INLINE void ReadPixel<Vector>(size_t x, size_t y, Vector& pixel) const {
			memcpy(pixel.GetData(), GetPixelAddress(x, y), _type.GetSizeInBytes());
			pixel._type = _type;
		}

		template<class T>
		ANVIL_STRONG_INLINE void WritePixel(size_t x, size_t y, const T pixel) {
			ReadPixel<T>(x, y) = pixel;
		}

		template<>
		ANVIL_STRONG_INLINE void WritePixel<UntypedScalar>(size_t x, size_t y, const UntypedScalar pixel) {
			memcpy(GetPixelAddress(x, y), pixel.GetData(), _type.GetSizeInBytes());
		}

		template<>
		ANVIL_STRONG_INLINE void WritePixel<TypedScalar>(size_t x, size_t y, const TypedScalar pixel) {
			if (pixel._type == _type) {
				WritePixel<UntypedScalar>(x, y, pixel._scalar);
			} else {
				WritePixel<UntypedScalar>(x, y, pixel.ConvertTo(_type)._scalar);
			}
		}

		template<>
		ANVIL_STRONG_INLINE void WritePixel<Vector>(size_t x, size_t y, const Vector pixel) {
			if (pixel._type == _type) {
				memcpy(GetPixelAddress(x, y), pixel.GetData(), _type.GetSizeInBytes());
			} else {
				memcpy(GetPixelAddress(x, y), pixel.ConvertTo(_type).GetData(), _type.GetSizeInBytes());
			}
		}
	};
}}

#endif
