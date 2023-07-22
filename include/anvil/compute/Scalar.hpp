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

#ifndef ANVIL_COMPUTE_SCALAR_HPP
#define ANVIL_COMPUTE_SCALAR_HPP

#include "anvil/core/Keywords.hpp"
#include "anvil/compute/Type.hpp"
#include "anvil/compute/Arithmetic.hpp"

namespace anvil { namespace compute {

	struct UntypedScalar {
		union {
			uint8_t u8;
			uint16_t u16;
			uint32_t u32;
			uint64_t u64;
			int8_t s8;
			int16_t s16;
			int32_t s32;
			int64_t s64;
#if ANVIL_F8_SUPPORT
			float8_t f8;
#endif
#if ANVIL_F16_SUPPORT
			float16_t f16;
#endif
			float32_t f32;
			float64_t f64;
		};

		UntypedScalar() = default;
		~UntypedScalar() = default;

		ANVIL_STRONG_INLINE void* GetData() throw() { return this; }
		ANVIL_STRONG_INLINE const void* GetData() const throw() { return this; }

		ANVIL_CONSTEXPR_FN UntypedScalar(const uint8_t value) :
			u64(value)
		{}

		ANVIL_CONSTEXPR_FN UntypedScalar(const uint16_t value) :
			u64(value)
		{}

		ANVIL_CONSTEXPR_FN UntypedScalar(const uint32_t value) :
			u64(value)
		{}

		ANVIL_CONSTEXPR_FN UntypedScalar(const uint64_t value) :
			u64(value)
		{}

		ANVIL_CONSTEXPR_FN UntypedScalar(const int8_t value) :
			s64(value)
		{}

		ANVIL_CONSTEXPR_FN UntypedScalar(const int16_t value) :
			s64(value)
		{}

		ANVIL_CONSTEXPR_FN UntypedScalar(const int32_t value) :
			s64(value)
		{}

		ANVIL_CONSTEXPR_FN UntypedScalar(const int64_t value) :
			s64(value)
		{}

#if ANVIL_F8_SUPPORT
		ANVIL_CONSTEXPR_FN UntypedScalar(const float8_t value) :
			u64(0u)
		{
			f8 = value;
		}
#endif

#if ANVIL_F16_SUPPORT
		UntypedScalar(const float16_t value) :
			u64(0u)
		{
			f16 = value;
		}
#endif

		UntypedScalar(const float32_t value) :
			u64(0u)
		{
			f32 = value;
		}

		ANVIL_CONSTEXPR_FN UntypedScalar(const float64_t value) :
			f64(value)
		{}

		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN operator uint8_t() const throw() {
			return u8;
		}

		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN operator uint16_t() const throw() {
			return u16;
		}

		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN operator uint32_t() const throw() {
			return u32;
		}

		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN operator uint64_t() const throw() {
			return u64;
		}

		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN operator int8_t() const throw() {
			return s8;
		}

		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN operator int16_t() const throw() {
			return s16;
		}

		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN operator int32_t() const throw() {
			return s32;
		}

		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN operator int64_t() const throw() {
			return s64;
		}

#if ANVIL_F8_SUPPORT
		ANVIL_STRONG_INLINE operator float8_t() const throw() {
			return f8;
		}
#endif

#if ANVIL_F16_SUPPORT
		ANVIL_STRONG_INLINE operator float16_t() const throw() {
			return f16;
		}
#endif

		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN operator float32_t() const throw() {
			return f32;
		}

		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN operator float64_t() const throw() {
			return f64;
		}

		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN bool operator==(const UntypedScalar& other) const throw() {
			return u64 == other.u64;
		}

		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN bool operator!=(const UntypedScalar& other) const throw() {
			return u64 != other.u64;
		}
	};

	class Image;
	class Vector;

	class ANVIL_DLL_EXPORT TypedScalar {
	private:
		UntypedScalar _scalar;
		Type _type;
	public:
		friend Image;
		friend Vector;

		TypedScalar();
		~TypedScalar() = default;

		TypedScalar(const Type type);
		TypedScalar(const Type type, const UntypedScalar& scalar);
		TypedScalar(const uint8_t value);
		TypedScalar(const uint16_t value);
		TypedScalar(const uint32_t value);
		TypedScalar(const uint64_t value);
		TypedScalar(const int8_t value);
		TypedScalar(const int16_t value);
		TypedScalar(const int32_t value);
		TypedScalar(const int64_t value);
#if ANVIL_F8_SUPPORT
		TypedScalar(const float8_t value);
#endif
#if ANVIL_F16_SUPPORT
		TypedScalar(const float16_t value);
#endif
		TypedScalar(const float32_t value);
		TypedScalar(const float64_t value);

		ANVIL_STRONG_INLINE void* GetData() throw() { return _scalar.GetData(); }
		ANVIL_STRONG_INLINE const void* GetData() const throw() { return _scalar.GetData(); }

		ANVIL_STRONG_INLINE void ForceSetType(Type type) throw() { _type = type; }

		Type GetType() const throw();
		void SetType(Type type) throw();

		void ConvertToInPlace(Type type);
		TypedScalar ConvertTo(Type type) const;

		operator uint8_t() const throw();
		operator uint16_t() const throw();
		operator uint32_t() const throw();
		operator uint64_t() const throw();
		operator int8_t() const throw();
		operator int16_t() const throw();
		operator int32_t() const throw();
		operator int64_t() const throw();
#if ANVIL_F8_SUPPORT
		operator float8_t() const throw();
#endif
#if ANVIL_F16_SUPPORT
		operator float16_t() const throw();
#endif
		operator float32_t() const throw();
		operator float64_t() const throw();
		operator UntypedScalar() const throw();

		bool operator==(const TypedScalar& other) const throw();
		bool operator!=(const TypedScalar& other) const throw();

		bool operator>(const TypedScalar& other) const throw();
		bool operator<(const TypedScalar& other) const throw();
		bool operator>=(const TypedScalar& other) const throw();
		bool operator<=(const TypedScalar& other) const throw();
	};

	ANVIL_STRONG_INLINE TypedScalar& operator+=(TypedScalar& a, const TypedScalar& b) {
		ArithmeticOperations::GetArithmeticOperations(ANVIL_8UX1)->Add(a, b, a);
		return a;
	}

	ANVIL_STRONG_INLINE TypedScalar& operator-=(TypedScalar& a, const TypedScalar& b) {
		ArithmeticOperations::GetArithmeticOperations(ANVIL_8UX1)->Subtract(a, b, a);
		return a;
	}

	ANVIL_STRONG_INLINE TypedScalar& operator*=(TypedScalar& a, const TypedScalar& b) {
		ArithmeticOperations::GetArithmeticOperations(ANVIL_8UX1)->Multiply(a, b, a);
		return a;
	}

	ANVIL_STRONG_INLINE TypedScalar& operator/=(TypedScalar& a, const TypedScalar& b) {
		ArithmeticOperations::GetArithmeticOperations(ANVIL_8UX1)->Divide(a, b, a);
		return a;
	}

	ANVIL_STRONG_INLINE TypedScalar& operator&=(TypedScalar& a, const TypedScalar& b) {
		ArithmeticOperations::GetArithmeticOperations(ANVIL_8UX1)->And(a, b, a);
		return a;
	}

	ANVIL_STRONG_INLINE TypedScalar& operator|=(TypedScalar& a, const TypedScalar& b) {
		ArithmeticOperations::GetArithmeticOperations(ANVIL_8UX1)->Or(a, b, a);
		return a;
	}

	ANVIL_STRONG_INLINE TypedScalar& operator^=(TypedScalar& a, const TypedScalar& b) {
		ArithmeticOperations::GetArithmeticOperations(ANVIL_8UX1)->Xor(a, b, a);
		return a;
	}

	ANVIL_STRONG_INLINE TypedScalar operator+(const TypedScalar& a, const TypedScalar& b) {
		TypedScalar dst;
		ArithmeticOperations::GetArithmeticOperations(ANVIL_8UX1)->Add(a, b, dst);
		return dst;
	}

	ANVIL_STRONG_INLINE TypedScalar operator-(const TypedScalar& a, const TypedScalar& b) {
		TypedScalar dst;
		ArithmeticOperations::GetArithmeticOperations(ANVIL_8UX1)->Subtract(a, b, dst);
		return dst;
	}

	ANVIL_STRONG_INLINE TypedScalar operator*(const TypedScalar& a, const TypedScalar& b) {
		TypedScalar dst;
		ArithmeticOperations::GetArithmeticOperations(ANVIL_8UX1)->Multiply(a, b, dst);
		return dst;
	}

	ANVIL_STRONG_INLINE TypedScalar operator/(const TypedScalar& a, const TypedScalar& b) {
		TypedScalar dst;
		ArithmeticOperations::GetArithmeticOperations(ANVIL_8UX1)->Divide(a, b, dst);
		return dst;
	}

	ANVIL_STRONG_INLINE TypedScalar operator&(const TypedScalar& a, const TypedScalar& b) {
		TypedScalar dst;
		ArithmeticOperations::GetArithmeticOperations(ANVIL_8UX1)->And(a, b, dst);
		return dst;
	}

	ANVIL_STRONG_INLINE TypedScalar operator|(const TypedScalar& a, const TypedScalar& b) {
		TypedScalar dst;
		ArithmeticOperations::GetArithmeticOperations(ANVIL_8UX1)->Or(a, b, dst);
		return dst;
	}

	ANVIL_STRONG_INLINE TypedScalar operator^(const TypedScalar& a, const TypedScalar& b) {
		TypedScalar dst;
		ArithmeticOperations::GetArithmeticOperations(ANVIL_8UX1)->Xor(a, b, dst);
		return dst;
	}

	ANVIL_STRONG_INLINE TypedScalar operator~(const TypedScalar& a) {
		TypedScalar dst;
		ArithmeticOperations::GetArithmeticOperations(ANVIL_8UX1)->Not(a, dst);
		return dst;
	}
}}

#endif
