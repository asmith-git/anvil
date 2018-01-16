//Copyright 2017 Adam G. Smith
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

#ifndef ANVIL_MATHS_SCALAR_HPP
#define ANVIL_MATHS_SCALAR_HPP

#include "anvil/core/Keywords.hpp"
#include "anvil/maths/Type.hpp"

namespace anvil {


	class Scalar {
	public:
		typedef float maths_t;
		enum {
			MAX_LENGTH = 4
		};
		union {
			uint8_t u8[MAX_LENGTH];		//!< Unsigned 8 bit value.
			uint16_t u16[MAX_LENGTH];	//!< Unsigned 16 bit value.
			uint32_t u32[MAX_LENGTH];	//!< Unsigned 32 bit value.
			uint64_t u64[MAX_LENGTH];	//!< Unsigned 64 bit value.
			int8_t s8[MAX_LENGTH];		//!< Signed 8 bit value.
			int16_t s16[MAX_LENGTH];	//!< Signed 16 bit value.
			int32_t s32[MAX_LENGTH];	//!< Signed 32 bit value.
			int64_t s64[MAX_LENGTH];	//!< Signed 64 bit value.
			float32_t f32[MAX_LENGTH];	//!< Single precision floating point value.
			float64_t f64[MAX_LENGTH];	//!< Double precision floating point value.
			bool b8[MAX_LENGTH];		//!< Boolean value.x
		};
		Type type;
		uint8_t length;

		ANVIL_CALL Scalar() throw();
		Scalar ANVIL_CALL convertTo(Type) const throw();

		Scalar operator+(const Scalar&) const throw();
		Scalar operator-(const Scalar&) const throw();
		Scalar operator*(const Scalar&) const throw();
		Scalar operator/(const Scalar&) const throw();

		Scalar& operator+=(const Scalar&) throw();
		Scalar& operator-=(const Scalar&) throw();
		Scalar& operator*=(const Scalar&) throw();
		Scalar& operator/=(const Scalar&) throw();

#define ANVIL_DEF_FUNCTIONS(T)\
		ANVIL_CALL Scalar(T) throw();\
		ANVIL_CALL Scalar(const T *, size_t) throw();\
		ANVIL_CALL Scalar(Type, T) throw();\
		ANVIL_CALL Scalar(Type, const T *, size_t) throw();\
		ANVIL_CALL operator T() const throw();\
		ANVIL_CALL operator const T *() const throw();\

		ANVIL_DEF_FUNCTIONS(uint8_t)
		ANVIL_DEF_FUNCTIONS(int8_t)
		ANVIL_DEF_FUNCTIONS(uint16_t)
		ANVIL_DEF_FUNCTIONS(int16_t)
		ANVIL_DEF_FUNCTIONS(uint32_t)
		ANVIL_DEF_FUNCTIONS(int32_t)
		ANVIL_DEF_FUNCTIONS(uint64_t)
		ANVIL_DEF_FUNCTIONS(int64_t)
		ANVIL_DEF_FUNCTIONS(float32_t)
		ANVIL_DEF_FUNCTIONS(float64_t)
		ANVIL_DEF_FUNCTIONS(bool)
#undef ANVIL_DEF_FUNCTIONS
	};

	/*!
		\brief Dispatch a function call based on a primative type.
		\tparam FU8 Functor type if aType is ANVIL_8U.
		\tparam FU16 Functor type if aType is ANVIL_16U.
		\tparam FU32 Functor type if aType is ANVIL_32U.
		\tparam FU64 Functor type if aType is ANVIL_64U.
		\tparam FS8 Functor type if aType is ANVIL_8S.
		\tparam FS16 Functor type if aType is ANVIL_16S.
		\tparam FS32 Functor type if aType is ANVIL_32S.
		\tparam FS64 Functor type if aType is ANVIL_64S.
		\tparam FF32 Functor type if aType is ANVIL_32F.
		\tparam FF64 Functor type if aType is ANVIL_64F.
		\tparam FB8 Functor type if aType is ANVIL_8B.
		\param aPrimative The container for the primative value.
		\param aType The type contained in aType.
		\param fu8 Functor to call if aType is ANVIL_8U.
		\param fu16 Functor to call if aType is ANVIL_16U.
		\param fu32 Functor to call if aType is ANVIL_32U.
		\param fu64 Functor to call if aType is ANVIL_64U.
		\param fs8 Functor to call if aType is ANVIL_8S.
		\param fs16 Functor to call if aType is ANVIL_16S.
		\param fs32 Functor to call if aType is ANVIL_32S.
		\param fs64 Functor to call if aType is ANVIL_64S.
		\param ff32 Functor to call if aType is ANVIL_32F.
		\param ff64 Functor to call if aType is ANVIL_64F.
		\param fb8 Functor to call if aType is ANVIL_8B.
		\return True if one of the functors was called, otherwise false (aType is not a primative type).
	*/
	template<class FU8, class FU16, class FU32, class FU64, 
		class FS8, class FS16, class FS32, class FS64, 
		class FF32, class FF64, class FB8>
	static inline bool ANVIL_CALL dispatchByType(Scalar aValue, 
		FU8 fu8,   FS8 fs8,   FU16 fu16, FS16 fs16,
		FU32 fu32, FS32 fs32, FU64 fu64, FS64 fs64,
		FF32 ff32, FF64 ff64, FB8 fb8) {
		bool returnValue = true;
		switch (GetPrimativeType(aValue.type)) {
		case ANVIL_8U:
			fu8(aValue.u8, aValue.length);
			break;
		case ANVIL_8S:
			fs8(aValue.s8, aValue.length);
			break;
		case ANVIL_16U:
			fu16(aValue.u16, aValue.length);
			break;
		case ANVIL_16S:
			fs16(aValue.s16, aValue.length);
			break;
#ifndef ANVIL_OCV_COMPATIBILITY
		case ANVIL_32U:
			fu32(aValue.u32, aValue.length);
			break;
#endif
		case ANVIL_32S:
			fs32(aValue.s32, aValue.length);
			break;
#ifndef ANVIL_OCV_COMPATIBILITY
		case ANVIL_64U:
			fu64(aValue.u64, aValue.length);
			break;
		case ANVIL_64S:
			fs64(aValue.s64, aValue.length);
			break;
#endif
		case ANVIL_32F:
			ff32(aValue.f32, aValue.length);
			break;
		case ANVIL_64F:
			ff64(aValue.f64, aValue.length);
#ifndef ANVIL_OCV_COMPATIBILITY
		case ANVIL_8B:
			fb8(aValue.b8, aValue.length);
			break;
#endif
		default:
			returnValue = false;
			break;
		}
		return returnValue;
	}
}

#endif
