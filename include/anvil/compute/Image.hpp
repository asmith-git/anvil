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
#include <list>
#include <functional>
#include "anvil/compute/Vector.hpp"
#if ANVIL_OPENCV_SUPPORT
#include<opencv2/core/mat.hpp>
#endif

namespace anvil { namespace compute {

	/*!
	*	\class Image
	*	\brief Can represent 2D image data.
	*	\date July 2023
	*	\author Adam Smith
	*/
	class ANVIL_DLL_EXPORT Image {
	private:
		struct MemoryBlock {
			enum Mode {
				ANVIL_BLOCK,
				OCV_BLOCK
			};
			void* data;
			size_t bytes;
#if ANVIL_OPENCV_SUPPORT
			cv::Mat cv_mat;
			MemoryBlock(cv::Mat);
#endif
			uint8_t mode;

			MemoryBlock(size_t bytes);
			~MemoryBlock();
		};
		std::shared_ptr<MemoryBlock> _memory_manager;	//!< Reference counts memory allocated by this class.
		Image* _parent;			//!< The parent if this image is an ROI, otherwise null.
		void* _data;			//!< The address of pixel [0,0].
		size_t _row_step;		//!< The distance between pixel 0 of one row and pixel 0 of the next in bytes.
		size_t _pixel_step;		//!< The distance between the staring address of one pixel and the next in bytes.
		size_t _width;			//!< The size of a row in pixels.
		size_t _height;			//!< The sizeo f a column in pixels.
		Type _type;				//!< The data type of the pixels.
	public:
		Image();
		~Image();

		Image(const Type type, size_t width, size_t height);
		Image(void* data, const Type type, size_t width, size_t height);
		Image(void* data, const Type type, size_t width, size_t height, size_t row_step);
		Image(void* data, const Type type, size_t width, size_t height, size_t row_step, size_t pixel_step);

		Image(Image&& other);
		Image(const Image&) = delete;

		Image& operator=(Image&& other);
		Image& operator=(const Image&) = delete;

		void Swap(Image& other);

		/*!
		*	\brief Allocate a new image.
		*	\details Will try to re-use existing allocation if possible.
		*	\param type The data type of the pixels in the new image.
		*	\param width The number of pixels in each row.
		*	\param height The number of pixels in each column.
		*	\param force Will force allocation of a new block of memory if the current memory is shared by a parent or child image.
		*	\see Image::Deallocate
		*/
		void Allocate(Type type, size_t width, size_t height, bool force = true);

		/*!
		*	\brief Deallocate memory that was previously allocated.
		*	\details Child images will not be effected by the deallocation of a parent as the memory is reference counted.
		*	\see Image::Allocate
		*/
		void Deallocate();

		/*!
		*	\param If this image is an ROI or a channel of another image then return that image.
		*	\details This function should be called before each use of the parent to check that it hasn't been deallocated.
		*	\return The parent image or null if there isn't one
		*/
		Image* GetParent() throw();

		/*!
		*	\brief Return a child image that only references one or more adjacent channels of this image.
		*	\details Call Image::DeepCopy on the returned image if pixel stepping is not desirable.
		*	\param index The index of the first channel that should be referenced.
		*	\param count The number of adjacent channels to referenced.
		*	\return The child image.
		*	\see Image::GetChannel
		*	\see Image::GetAllChannels
		*/
		Image GetChannels(size_t index, size_t count);

		/*!
		*	\brief Return a child image that only references one channel of this image.
		*	\details Call Image::DeepCopy on the returned image if pixel stepping is not desirable.
		*	\param index The index of the channel that should be referenced.
		*	\return The child image.
		*	\see Image::GetChannels
		*	\see Image::GetAllChannels
		*/
		ANVIL_STRONG_INLINE Image GetChannel(size_t index) {
			return GetChannels(index, 1u);
		}

		/*!
		*	\brief Return child images that reference each channel of this image.
		*	\details Call Image::DeepCopy on the returned images if pixel stepping is not desirable.
		*	\return The child images, each referencing a different channel sequentially.
		*	\see Image::GetChannel
		*	\see Image::GetChannels
		*/
		std::list<Image> GetAllChannels();

		/*!
		*	\brief Return a child image that references only a region of interest (ROI) of this image.
		*	\param x The X position of the first pixel inside the ROI
		*	\param y The Y position of the tirst pixel inside the ROI
		*	\param width The number of pixels in each row of the ROI
		*	\param height The number of pixels in each column of the ROI
		*	\return The child image
		*/
		Image GetRoi(size_t x, size_t y, size_t width, size_t height);

		/*!
		*	\brief Return a child image that references only one row of this image.
		*	\details This function just calls Image::GetROI.
		*	\param y The index of the row to reference.
		*	\return The child image.
		*	\see Image::GetROI
		*	\see Image::GetCol
		*/
		ANVIL_STRONG_INLINE Image GetRow(size_t y) { 
			return GetRoi(0u, y, _width, 1u); 
		}
		
		/*!
		*	\brief Return a child image that references only one column of this image.
		*	\details This function just calls Image::GetROI.
		*	\param y The index of the column to reference.
		*	\return The child image.
		*	\see Image::GetROI
		*	\see Image::GetRow
		*/
		ANVIL_STRONG_INLINE Image GetCol(size_t x) { 
			return GetRoi(x, 0u, 1u, _height); 
		}

		/*!
		*	\brief Copy the pixels from this image into a different one.
		*	\details If the target image is a different size then it will be re-allocated.
		*	\param other The image to copy into.
		*	\see Image::DeepCopy
		*/
		void DeepCopyTo(Image& other) const;

		/*!
		*	\brief Copy all of this pixel values in this image into a new image.
		*	\return The copied image.
		*/
		inline Image DeepCopy() const {
			Image tmp;
			DeepCopyTo(tmp);
			return tmp;
		}

		/*!
		*	\brief Create a child image that references all pixels in this image.
		*	\details This function just calls Image::GetRoi.
		*	\return The child image.
		*/
		ANVIL_STRONG_INLINE Image ShallowCopy() { 
			return GetRoi(0u, 0u, _width, _height); 
		}

		/*!
		*	\param Convert the pixels in this image to a diffrent data type.
		*	\details If the new type is a different size then the image memory will be re-allocated.
		*	\param type The type to convert to.	
		*	\see Image::ConvertTo
		*/
		void ConvertToInPlace(Type type);

		/*!
		*	\param Copy and convert the pixels values of this image to a different data type.
		*	\param type The type to convert to.
		*	\return The converted image
		*	\see Image::ConvertToInPlace
		*/
		Image ConvertTo(Type type) const;

		/*!
		*	\param Try to reinterpret what the memory of this image represents without changing the values of any pixels.
		*	\details An example of how this function might be used is to reinterpret a single precision floating point image as 32-bit integer to perform a bitwise masking operation on it.
		*	\param type The data type to reinterpret the memory as.
		*	\param width The number of pixels in each row of the reinterpreted image.
		*	\param height The number of pixels in each column of the reinterpreted image.
		*	\return True if the image memory was reinterpreted successfully.
		*/
		bool TryReinterpretAs(Type type, size_t width, size_t height, bool allow_reinterpret_as_smaller = false);

		bool operator==(const Image& other) const throw();
		ANVIL_STRONG_INLINE bool operator!=(const Image& other) const throw() { return !operator==(other); }

		/*!
		*	\brief Return the data type of pixels in this image.
		*	\return The data type.
		*/
		ANVIL_STRONG_INLINE Type GetType() const throw() { return _type; }

		/*!
		*	\brief Return the width of this image.
		*	\return The number of pixels in each row.
		*/
		ANVIL_STRONG_INLINE size_t GetWidth() const throw() { return _width; }

		/*!
		*	\brief Return the height of this image.
		*	\return The number of pixels in each column.
		*/
		ANVIL_STRONG_INLINE size_t GetHeight() const throw() { return _height; }

		/*!
		*	\brief Return the row step for this image.
		*	\return The number of bytes between the start of each row.
		*	\see Image::_row_step
		*/
		ANVIL_STRONG_INLINE size_t GetRowStep() const throw() { return _row_step; }

		/*!
		*	\brief Return the pixel step for this image.
		*	\return The number of bytes between the start of each pixel.
		*	\see Image::_pixel_step
		*/
		ANVIL_STRONG_INLINE size_t GetPixelStep() const throw() { return _pixel_step; }

		/*!
		*	\brief Check if all pixel values in this image are contiguous within memory.
		*	\return True if the image is contiguous.
		*/
		ANVIL_STRONG_INLINE bool IsContiguous() const throw() {
			size_t bytes = _type.GetSizeInBytes();
			return _pixel_step == bytes && _row_step == bytes * _width;
		}

#if ANVIL_OPENCV_SUPPORT
		/*!
		*	\brief Create an image that references an OpenCV image.
		*	\param mat The image to reference.
		*/
		Image(const cv::Mat& mat);

		/*!
		*	\brief Create an OpenCV image that references this image
		*	\details Will throw an exception if the image format is not supported by OpenCV.
		*	<br/> This will be because either the image uses pixel stepping, the data type is not supported by OpenCV or there are too many channels.
		*	\bug If this image is deallocated before the returned OpenCV one then it may attempt to access invalid memory addresses.
		*	\return An OpenCV image that references this one.
		*/
		ANVIL_STRONG_INLINE operator cv::Mat() {
			ANVIL_RUNTIME_ASSERT(_pixel_step == _type.GetSizeInBytes(), "anvil::compute::Image::operator cv::Mat : OpenCV does not support pixel stepping");
			return cv::Mat((int)_height, (int)_width, _type.GetOpenCVType(), _data, _row_step);
		}
#endif

		/*!	
		*	\brief Return the address of the first pixel in this image.
		*	\return The adddress of pixel [0,0].
		*/
		ANVIL_STRONG_INLINE void* GetData() throw() { return _data; }

		/*!
		*	\brief Return the address of the first pixel in this image.
		*	\return The adddress of pixel [0,0].
		*/
		ANVIL_STRONG_INLINE const void* GetData() const throw() { return _data; }

		/*!
		*	\brief Return the address of the first pixel in a row.
		*	\param y The index of the row to get
		*	\return The adddress of pixel [0,y].
		*/
		ANVIL_STRONG_INLINE void* GetRowAddress(size_t y) {
			ANVIL_DEBUG_ASSERT(y < _height, "anvil::compute::Image::GetRowAddress : Y position is out of bounds");
			return static_cast<uint8_t*>(_data) + _row_step * y;
		}

		/*!
		*	\brief Return the address of the first pixel in a row.
		*	\param y The index of the row to get
		*	\return The adddress of pixel [0,y].
		*/
		ANVIL_STRONG_INLINE const void* GetRowAddress(size_t y) const {
			ANVIL_DEBUG_ASSERT(y < _height, "anvil::compute::Image::GetRowAddress : Y position is out of bounds");
			return static_cast<uint8_t*>(_data) + _row_step * y;
		}

		/*!
		*	\brief Return the address of a specific pixel.
		*	\param x The index of the row to get.
		*	\param y The index of the column to get.
		*	\return The adddress of pixel [x,y].
		*/
		ANVIL_STRONG_INLINE void* GetPixelAddress(size_t x, size_t y) {
			ANVIL_DEBUG_ASSERT(x < _width, "anvil::compute::Image::GetPixelAddress : X position is out of bounds");
			return static_cast<uint8_t*>(GetRowAddress(y)) + x * _pixel_step;
		}

		/*!
		*	\brief Return the address of a specific pixel.
		*	\param x The index of the row to get.
		*	\param y The index of the column to get.
		*	\return The adddress of pixel [x,y].
		*/
		ANVIL_STRONG_INLINE const void* GetPixelAddress(size_t x, size_t y) const {
			ANVIL_DEBUG_ASSERT(x < _width, "anvil::compute::Image::GetPixelAddress : X position is out of bounds");
			return static_cast<const uint8_t*>(GetRowAddress(y)) + x * _pixel_step;
		}

		/*!
		*	\brief Read the value of a pixel.
		*	\details This function will not check if the requested position is valid or if the value is the correct type.
		*	\param x The index of the row to read.
		*	\param y The index of the column to read.
		*	\param pixel The value that is read from the image.
		*	\tparam T The type to interpret the pixel data as.
		*/
		template<class T>
		inline void ReadPixel(size_t x, size_t y, T& pixel) const {
			pixel = *reinterpret_cast<T*>(const_cast<void*>(GetPixelAddress(x, y)));
		}

		template<>
		inline void ReadPixel<UntypedScalar>(size_t x, size_t y, UntypedScalar& pixel) const {
			ANVIL_DEBUG_ASSERT(_type.GetNumberOfChannels() == 1u, "anvil::Image::ReadPixel (UntypedScalar) : Type has more than one channel");
			memcpy(pixel.GetData(), GetPixelAddress(x, y), _type.GetSizeInBytes());
		}

		template<>
		inline void ReadPixel<TypedScalar>(size_t x, size_t y, TypedScalar& pixel) const {
			ReadPixel(x, y, pixel._scalar);
			pixel._type = _type;
		}

		template<>
		inline void ReadPixel<Vector>(size_t x, size_t y, Vector& pixel) const {
			memcpy(pixel.GetData(), GetPixelAddress(x, y), _type.GetSizeInBytes());
			pixel._type = _type;
		}
		
		/*!
		*	\brief Write the value of a pixel into the image.
		*	\details This function will not check if the requested position is valid or if the value is the correct type.
		*	\param x The index of the row to write.
		*	\param y The index of the column to write.
		*	\param pixel The value to write to the image.
		*	\tparam T The type to interpret the pixel data as.
		*/
		template<class T>
		inline void WritePixel(size_t x, size_t y, const T pixel) {
			ReadPixel<T>(x, y) = pixel;
		}

		template<>
		inline void WritePixel<UntypedScalar>(size_t x, size_t y, const UntypedScalar pixel) {
			memcpy(GetPixelAddress(x, y), pixel.GetData(), _type.GetSizeInBytes());
		}

		template<>
		inline void WritePixel<TypedScalar>(size_t x, size_t y, const TypedScalar pixel) {
			if (pixel._type == _type) {
				WritePixel<UntypedScalar>(x, y, pixel._scalar);
			} else {
				WritePixel<UntypedScalar>(x, y, pixel.ConvertTo(_type)._scalar);
			}
		}

		template<>
		inline void WritePixel<Vector>(size_t x, size_t y, const Vector pixel) {
			if (pixel._type == _type) {
				memcpy(GetPixelAddress(x, y), pixel.GetData(), _type.GetSizeInBytes());
			} else {
				memcpy(GetPixelAddress(x, y), pixel.ConvertTo(_type).GetData(), _type.GetSizeInBytes());
			}
		}

		/*!
		*	\brief If this image is an ROI then calculate the X and Y position within the parent image.
		*	\param x The X position of this image's pixel [0,0] with the parent image.
		*	\param y The Y position of this image's pixel [0,0] with the parent image.
		*/
		void GetRoiPosition(size_t& x, size_t& y) const;

		/*!
		*	\brief If this image is an ROI then calculate the X and Y position within another image.
		*	\detail Will throw an exception if this image is not a decendent of the one provided.
		*	\param x The X position of this image's pixel [0,0] with the parent image.
		*	\param y The Y position of this image's pixel [0,0] with the parent image.
		*/
		void GetRoiPosition(const Image& img, size_t& x, size_t& y) const;
	};
}}

#endif
