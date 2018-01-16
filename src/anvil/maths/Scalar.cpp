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

#include "anvil/maths/Scalar.hpp"
#include "anvil/maths/Vector.hpp"
#include <type_traits>
#include <cstring>

namespace anvil {

	// Scalar

	ANVIL_CALL Scalar::Scalar() throw() :
		type(ANVIL_8U),
		length(0)
	{
		for (int i = 0; i < MAX_LENGTH; ++i) u8[i] = 0;
	}

	Scalar ANVIL_CALL Scalar::convertTo(Type aType) const throw() {
		const int l = GetChannels(aType);
		const int ol = length;
		float64_t buffer[MAX_LENGTH];
		const float64_t* const conversion = *this;
		for (int i = 0; i < ol; ++i) buffer[i] = conversion[i];
		const float64_t back = buffer[ol - 1];
		for (int i = ol; i < l; ++i) buffer[i] = back;
		return Scalar(aType, buffer, length);
	}		
	
	Scalar Scalar::operator+(const Scalar& aOther) const throw() {
		return Scalar(*this) += aOther;
	}

	Scalar Scalar::operator-(const Scalar& aOther) const throw() {
		return Scalar(*this) -= aOther;
	}

	Scalar Scalar::operator*(const Scalar& aOther) const throw() {
		return Scalar(*this) *= aOther;
	}

	Scalar Scalar::operator/(const Scalar& aOther) const throw() {
		return Scalar(*this) /= aOther;
	}

	Scalar& Scalar::operator+=(const Scalar& aOther) throw() {
		Vector<maths_t, MAX_LENGTH> a;
		Vector<maths_t, MAX_LENGTH> b;
		memcpy(&a, static_cast<const maths_t*>(*this), sizeof(maths_t) * MAX_LENGTH);
		memcpy(&b, static_cast<const maths_t*>(aOther), sizeof(maths_t) * MAX_LENGTH);
		a += b;
		memcpy(f32, &a, sizeof(maths_t) * MAX_LENGTH);
		type = CreateType(EnumFromType<maths_t>::value, length);
		return *this;
	}

	Scalar& Scalar::operator-=(const Scalar& aOther) throw() {
		Vector<maths_t, MAX_LENGTH> a;
		Vector<maths_t, MAX_LENGTH> b;
		memcpy(&a, static_cast<const maths_t*>(*this), sizeof(maths_t) * MAX_LENGTH);
		memcpy(&b, static_cast<const maths_t*>(aOther), sizeof(maths_t) * MAX_LENGTH);
		a -= b;
		memcpy(f32, &a, sizeof(maths_t) * MAX_LENGTH);
		type = CreateType(EnumFromType<maths_t>::value, length);
		return *this;
	}

	Scalar& Scalar::operator*=(const Scalar& aOther) throw() {
		Vector<maths_t, MAX_LENGTH> a;
		Vector<maths_t, MAX_LENGTH> b;
		memcpy(&a, static_cast<const maths_t*>(*this), sizeof(maths_t) * MAX_LENGTH);
		memcpy(&b, static_cast<const maths_t*>(aOther), sizeof(maths_t) * MAX_LENGTH);
		a *= b;
		memcpy(f32, &a, sizeof(maths_t) * MAX_LENGTH);
		type = CreateType(EnumFromType<maths_t>::value, length);
		return *this;
	}

	Scalar& Scalar::operator/=(const Scalar& aOther) throw() {
		Vector<maths_t, MAX_LENGTH> a;
		Vector<maths_t, MAX_LENGTH> b;
		memcpy(&a, static_cast<const maths_t*>(*this), sizeof(maths_t) * MAX_LENGTH);
		memcpy(&b, static_cast<const maths_t*>(aOther), sizeof(maths_t) * MAX_LENGTH);
		a /= b;
		memcpy(f32, &a, sizeof(maths_t) * MAX_LENGTH);
		type = CreateType(EnumFromType<maths_t>::value, length);
		return *this;
	}

#ifdef ANVIL_OCV_COMPATIBILITY
	#define ANVIL_DEF_FUNCTIONS(E, T, N)\
	ANVIL_CALL Scalar::Scalar(T aValue) throw() :\
		type(E),\
		length(1)\
	{\
		N[0] = aValue;\
		for (int i = 1; i < MAX_LENGTH; ++i) N[i] = static_cast<T>(0);\
	}\
	ANVIL_CALL Scalar::Scalar(const T* aValue, size_t aLength) throw() :\
		type(E),\
		length(aLength < MAX_LENGTH ? aLength : MAX_LENGTH)\
	{\
			const int l = length;\
			for (int i = 0; i < l; ++i) N[i] = aValue[i];\
	}\
	ANVIL_CALL Scalar::Scalar(Type aType, T aValue) throw() :\
		type(aType),\
		length(1)\
	{\
		switch(GetPrimativeType(aType)) {\
		case ANVIL_8U:\
			u8[0] = static_cast<uint8_t>(aValue);\
			break;\
		case ANVIL_8S:\
			s8[0] = static_cast<int8_t>(aValue);\
			break;\
		case ANVIL_16U:\
			u16[0] = static_cast<uint16_t>(aValue);\
			break;\
		case ANVIL_16S:\
			s16[0] = static_cast<int16_t>(aValue);\
			break;\
		case ANVIL_32S:\
			s32[0] = static_cast<int32_t>(aValue);\
			break;\
		case ANVIL_32F:\
			f32[0] = static_cast<float32_t>(aValue);\
			break;\
		case ANVIL_64F:\
			f64[0] = static_cast<float64_t>(aValue);\
			break;\
		default:\
			break;\
		}\
	}\
	ANVIL_CALL Scalar::Scalar(Type aType, const T* aValue, size_t aLength) throw() :\
		type(aType),\
		length(aLength)\
	{\
		switch(GetPrimativeType(aType)) {\
		case ANVIL_8U:\
			for (int i = 0; i < aLength; ++i) u8[i] = static_cast<uint8_t>(aValue[i]);\
			break;\
		case ANVIL_8S:\
			for (int i = 0; i < aLength; ++i) s8[i] = static_cast<int8_t>(aValue[i]);\
			break;\
		case ANVIL_16U:\
			for (int i = 0; i < aLength; ++i) u16[i] = static_cast<uint16_t>(aValue[i]);\
			break;\
		case ANVIL_16S:\
			for (int i = 0; i < aLength; ++i) s16[i] = static_cast<int16_t>(aValue[i]);\
			break;\
		case ANVIL_32S:\
			for (int i = 0; i < aLength; ++i) s32[i] = static_cast<int32_t>(aValue[i]);\
			break;\
		case ANVIL_32F:\
			for (int i = 0; i < aLength; ++i) f32[i] = static_cast<float32_t>(aValue[i]);\
			break;\
		case ANVIL_64F:\
			for (int i = 0; i < aLength; ++i) f64[i] = static_cast<float64_t>(aValue[i]);\
			break;\
		default:\
			break;\
		}\
	}\
	ANVIL_CALL Scalar::operator T() const throw() {\
		switch(GetPrimativeType(type)) {\
		case ANVIL_8U:\
			return static_cast<T>(u8[0]);\
		case ANVIL_8S:\
			return static_cast<T>(s8[0]);\
		case ANVIL_16U:\
			return static_cast<T>(u16[0]);\
		case ANVIL_16S:\
			return static_cast<T>(s16[0]);\
		case ANVIL_32S:\
			return static_cast<T>(s32[0]);\
		case ANVIL_32F:\
			return static_cast<T>(f32[0]);\
		case ANVIL_64F:\
			return static_cast<T>(f64[0]);\
		default:\
			return static_cast<T>(0);\
		}\
	}\
	ANVIL_CALL Scalar::operator const T*() const throw() {\
		static T gBuffer[MAX_LENGTH];\
		const int l = length;\
		switch(GetPrimativeType(type)) {\
		case ANVIL_8U:\
			if(std::is_same<T, uint8_t>::value) return reinterpret_cast<const T*>(u8);\
			else for(int i = 0; i < l; ++i) gBuffer[i] = static_cast<T>(u8[i]);\
			break;\
		case ANVIL_8S:\
			if(std::is_same<T, int8_t>::value) return reinterpret_cast<const T*>(s8);\
			else for(int i = 0; i < l; ++i) gBuffer[i] = static_cast<T>(s8[i]);\
			break;\
		case ANVIL_16U:\
			if(std::is_same<T, uint16_t>::value) return reinterpret_cast<const T*>(u16);\
			else for(int i = 0; i < l; ++i) gBuffer[i] = static_cast<T>(u16[i]);\
			break;\
		case ANVIL_16S:\
			if(std::is_same<T, int16_t>::value) return reinterpret_cast<const T*>(s16);\
			else for(int i = 0; i < l; ++i) gBuffer[i] = static_cast<T>(s16[i]);\
			break;\
		case ANVIL_32S:\
			if(std::is_same<T, int32_t>::value) return reinterpret_cast<const T*>(s32);\
			else for(int i = 0; i < l; ++i) gBuffer[i] = static_cast<T>(s32[i]);\
			break;\
		case ANVIL_32F:\
			if(std::is_same<T, float32_t>::value) return reinterpret_cast<const T*>(f32);\
			else for(int i = 0; i < l; ++i) gBuffer[i] = static_cast<T>(f32[i]);\
			break;\
		case ANVIL_64F:\
			if(std::is_same<T, float64_t>::value) return reinterpret_cast<const T*>(f64);\
			else for(int i = 0; i < l; ++i) gBuffer[i] = static_cast<T>(f64[i]);\
			break;\
		default:\
			break;\
		}\
		return gBuffer;\
	}
#else
#define ANVIL_DEF_FUNCTIONS(E, T, N)\
	ANVIL_CALL Scalar::Scalar(T aValue) throw() :\
		type(E),\
		length(1)\
	{\
		N[0] = aValue;\
		for (int i = 1; i < MAX_LENGTH; ++i) N[i] = static_cast<T>(0);\
	}\
	ANVIL_CALL Scalar::Scalar(const T* aValue, size_t aLength) throw() :\
		type(E),\
		length(aLength < MAX_LENGTH ? aLength : MAX_LENGTH)\
	{\
			const int l = length;\
			for (int i = 0; i < l; ++i) N[i] = aValue[i];\
	}\
	ANVIL_CALL Scalar::Scalar(Type aType, T aValue) throw() :\
		type(aType),\
		length(1)\
	{\
		switch(GetPrimativeType(aType)) {\
		case ANVIL_8U:\
			u8[0] = static_cast<uint8_t>(aValue);\
			break;\
		case ANVIL_8S:\
			s8[0] = static_cast<int8_t>(aValue);\
			break;\
		case ANVIL_16U:\
			u16[0] = static_cast<uint16_t>(aValue);\
			break;\
		case ANVIL_16S:\
			s16[0] = static_cast<int16_t>(aValue);\
			break;\
		case ANVIL_32U:\
			u32[0] = static_cast<uint32_t>(aValue);\
			break;\
		case ANVIL_32S:\
			s32[0] = static_cast<int32_t>(aValue);\
			break;\
		case ANVIL_64U:\
			u64[0] = static_cast<uint64_t>(aValue);\
			break;\
		case ANVIL_64S:\
			s64[0] = static_cast<int64_t>(aValue);\
			break;\
		case ANVIL_32F:\
			f32[0] = static_cast<float32_t>(aValue);\
			break;\
		case ANVIL_64F:\
			f64[0] = static_cast<float64_t>(aValue);\
			break;\
		case ANVIL_8B:\
			b8[0] = static_cast<bool>(aValue);\
			break;\
		default:\
			break;\
		}\
	}\
	ANVIL_CALL Scalar::Scalar(Type aType, const T* aValue, size_t aLength) throw() :\
		type(aType),\
		length(aLength)\
	{\
		switch(GetPrimativeType(aType)) {\
		case ANVIL_8U:\
			for (int i = 0; i < aLength; ++i) u8[i] = static_cast<uint8_t>(aValue[i]);\
			break;\
		case ANVIL_8S:\
			for (int i = 0; i < aLength; ++i) s8[i] = static_cast<int8_t>(aValue[i]);\
			break;\
		case ANVIL_16U:\
			for (int i = 0; i < aLength; ++i) u16[i] = static_cast<uint16_t>(aValue[i]);\
			break;\
		case ANVIL_16S:\
			for (int i = 0; i < aLength; ++i) s16[i] = static_cast<int16_t>(aValue[i]);\
			break;\
		case ANVIL_32U:\
			for (int i = 0; i < aLength; ++i) u32[i] = static_cast<uint32_t>(aValue[i]);\
			break;\
		case ANVIL_32S:\
			for (int i = 0; i < aLength; ++i) s32[i] = static_cast<int32_t>(aValue[i]);\
			break;\
		case ANVIL_64U:\
			for (int i = 0; i < aLength; ++i) u64[i] = static_cast<uint64_t>(aValue[i]);\
			break;\
		case ANVIL_64S:\
			for (int i = 0; i < aLength; ++i) s64[i] = static_cast<int64_t>(aValue[i]);\
			break;\
		case ANVIL_32F:\
			for (int i = 0; i < aLength; ++i) f32[i] = static_cast<float32_t>(aValue[i]);\
			break;\
		case ANVIL_64F:\
			for (int i = 0; i < aLength; ++i) f64[i] = static_cast<float64_t>(aValue[i]);\
			break;\
		case ANVIL_8B:\
			for (int i = 0; i < aLength; ++i) b8[i] = static_cast<bool>(aValue[i]);\
			break;\
		default:\
			break;\
		}\
	}\
	ANVIL_CALL Scalar::operator T() const throw() {\
		switch(GetPrimativeType(type)) {\
		case ANVIL_8U:\
			return static_cast<T>(u8[0]);\
		case ANVIL_8S:\
			return static_cast<T>(s8[0]);\
		case ANVIL_16U:\
			return static_cast<T>(u16[0]);\
		case ANVIL_16S:\
			return static_cast<T>(s16[0]);\
		case ANVIL_32U:\
			return static_cast<T>(u32[0]);\
		case ANVIL_32S:\
			return static_cast<T>(s32[0]);\
		case ANVIL_64U:\
			return static_cast<T>(u64[0]);\
		case ANVIL_64S:\
			return static_cast<T>(s64[0]);\
		case ANVIL_32F:\
			return static_cast<T>(f32[0]);\
		case ANVIL_64F:\
			return static_cast<T>(f64[0]);\
		case ANVIL_8B:\
			return static_cast<T>(b8[0]);\
		default:\
			return static_cast<T>(0);\
		}\
	}\
	ANVIL_CALL Scalar::operator const T*() const throw() {\
		static T gBuffer[MAX_LENGTH];\
		const int l = length;\
		switch(GetPrimativeType(type)) {\
		case ANVIL_8U:\
			if(std::is_same<T, uint8_t>::value) return reinterpret_cast<const T*>(u8);\
			else for(int i = 0; i < l; ++i) gBuffer[i] = static_cast<T>(u8[i]);\
			break;\
		case ANVIL_8S:\
			if(std::is_same<T, int8_t>::value) return reinterpret_cast<const T*>(s8);\
			else for(int i = 0; i < l; ++i) gBuffer[i] = static_cast<T>(s8[i]);\
			break;\
		case ANVIL_16U:\
			if(std::is_same<T, uint16_t>::value) return reinterpret_cast<const T*>(u16);\
			else for(int i = 0; i < l; ++i) gBuffer[i] = static_cast<T>(u16[i]);\
			break;\
		case ANVIL_16S:\
			if(std::is_same<T, int16_t>::value) return reinterpret_cast<const T*>(s16);\
			else for(int i = 0; i < l; ++i) gBuffer[i] = static_cast<T>(s16[i]);\
			break;\
		case ANVIL_32U:\
			if(std::is_same<T, uint32_t>::value) return reinterpret_cast<const T*>(u32);\
			else for(int i = 0; i < l; ++i) gBuffer[i] = static_cast<T>(u32[i]);\
			break;\
		case ANVIL_32S:\
			if(std::is_same<T, int32_t>::value) return reinterpret_cast<const T*>(s32);\
			else for(int i = 0; i < l; ++i) gBuffer[i] = static_cast<T>(s32[i]);\
			break;\
		case ANVIL_64U:\
			if(std::is_same<T, uint64_t>::value) return reinterpret_cast<const T*>(u64);\
			else for(int i = 0; i < l; ++i) gBuffer[i] = static_cast<T>(u64[i]);\
			break;\
		case ANVIL_64S:\
			if(std::is_same<T, int64_t>::value) return reinterpret_cast<const T*>(s64);\
			else for(int i = 0; i < l; ++i) gBuffer[i] = static_cast<T>(s64[i]);\
			break;\
		case ANVIL_32F:\
			if(std::is_same<T, float32_t>::value) return reinterpret_cast<const T*>(f32);\
			else for(int i = 0; i < l; ++i) gBuffer[i] = static_cast<T>(f32[i]);\
			break;\
		case ANVIL_64F:\
			if(std::is_same<T, float64_t>::value) return reinterpret_cast<const T*>(f64);\
			else for(int i = 0; i < l; ++i) gBuffer[i] = static_cast<T>(f64[i]);\
			break;\
		case ANVIL_8B:\
			if(std::is_same<T, bool>::value) return reinterpret_cast<const T*>(b8);\
			else for(int i = 0; i < l; ++i) gBuffer[i] = static_cast<T>(b8[i]);\
			break;\
		default:\
			break;\
		}\
		return gBuffer;\
	}
#endif

	ANVIL_DEF_FUNCTIONS(ANVIL_8U, uint8_t, u8)
	ANVIL_DEF_FUNCTIONS(ANVIL_8S, int8_t, s8)
	ANVIL_DEF_FUNCTIONS(ANVIL_16U, uint16_t, u16)
	ANVIL_DEF_FUNCTIONS(ANVIL_16S, int16_t, s16)
#ifndef ANVIL_OCV_COMPATIBILITY
	ANVIL_DEF_FUNCTIONS(ANVIL_32U, uint32_t, u32)
#endif
	ANVIL_DEF_FUNCTIONS(ANVIL_32S, int32_t, s32)
#ifndef ANVIL_OCV_COMPATIBILITY
	ANVIL_DEF_FUNCTIONS(ANVIL_64U, uint64_t, u64)
	ANVIL_DEF_FUNCTIONS(ANVIL_64S, int64_t, s64)
#endif
	ANVIL_DEF_FUNCTIONS(ANVIL_32F, float32_t, f32)
	ANVIL_DEF_FUNCTIONS(ANVIL_64F, float64_t, f64)
#ifndef ANVIL_OCV_COMPATIBILITY
	ANVIL_DEF_FUNCTIONS(ANVIL_8B, bool, b8)
#endif
#undef ANVIL_DEF_FUNCTIONS

}