//Copyright 2021 Adam G. Smith
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

#include <algorithm>
#include "anvil/Core.hpp"
#include "anvil/compute/Scalar.hpp"

namespace anvil { namespace compute {


	// TypedScalar

	TypedScalar::TypedScalar() :
		_scalar(0u)
	{}

	TypedScalar::TypedScalar(const Type type) :
		_scalar(0u),
		_type(type)
	{
		_type.SetNumberOfChannels(1u);
	}

	TypedScalar::TypedScalar(const Type type, const UntypedScalar& scalar) :
		_scalar(scalar.u64),
		_type(type)
	{
		_type.SetNumberOfChannels(1u);
	}

	TypedScalar::TypedScalar(const bool value) :
		_scalar(value),
		_type(ANVIL_8BX1)
	{}

	TypedScalar::TypedScalar(const char value) :
		_scalar(value),
		_type(ANVIL_CX1)
	{}

	TypedScalar::TypedScalar(const uint8_t value) :
		_scalar(value),
		_type(ANVIL_8UX1)
	{}

	TypedScalar::TypedScalar(const uint16_t value) :
		_scalar(value),
		_type(ANVIL_16UX1)
	{}

	TypedScalar::TypedScalar(const uint32_t value) :
		_scalar(value),
		_type(ANVIL_32UX1)
	{}

	TypedScalar::TypedScalar(const uint64_t value) :
		_scalar(value),
		_type(ANVIL_64UX1)
	{}

	TypedScalar::TypedScalar(const int8_t value) :
		_scalar(value),
		_type(ANVIL_8SX1)
	{}

	TypedScalar::TypedScalar(const int16_t value) :
		_scalar(value),
		_type(ANVIL_16SX1)
	{}

	TypedScalar::TypedScalar(const int32_t value) :
		_scalar(value),
		_type(ANVIL_32SX1)
	{}

	TypedScalar::TypedScalar(const int64_t value) :
		_scalar(value),
		_type(ANVIL_64SX1)
	{}

#if ANVIL_F8_SUPPORT
	TypedScalar::TypedScalar(const float8_t value) :
		_scalar(value),
		_type(ANVIL_8FX1)
	{}
#endif

#if ANVIL_F16_SUPPORT
	TypedScalar::TypedScalar(const float16_t value) :
		_scalar(value),
		_type(ANVIL_16FX1)
	{}
#endif

	TypedScalar::TypedScalar(const float32_t value) :
		_scalar(value),
		_type(ANVIL_32FX1)
	{}

	TypedScalar::TypedScalar(const float64_t value) :
		_scalar(value),
		_type(ANVIL_64FX1)
	{}

	Type TypedScalar::GetType() const throw() {
		return _type;
	}

	void TypedScalar::SetType(Type type) throw() {
		type.SetNumberOfChannels(1u);

		if (type == _type) return;

		const TypedScalar tmp = *this;

		_type = type;
		_scalar.u64 = 0ull;

		switch (type.GetEnumeratedType()) {
		case ANVIL_8UX1:
			_scalar.u8 = tmp;
			break;
		case ANVIL_16UX1:
			_scalar.u16 = tmp;
			break;
		case ANVIL_32UX1:
			_scalar.u32 = tmp;
			break;
		case ANVIL_64UX1:
			_scalar.u64 = tmp;
			break;
		case ANVIL_8SX1:
			_scalar.s8 = tmp;
			break;
		case ANVIL_16SX1:
			_scalar.s16 = tmp;
			break;
		case ANVIL_32SX1:
			_scalar.s32 = tmp;
			break;
		case ANVIL_64SX1:
			_scalar.s64 = tmp;
			break;
#if ANVIL_F8_SUPPORT
		case ANVIL_8FX1:
			_scalar.f8 = tmp;
#endif
#if ANVIL_F16_SUPPORT
		case ANVIL_16FX1:
			_scalar.f16 = tmp;
#endif
		case ANVIL_32FX1:
			_scalar.f32 = tmp;
			break;
		case ANVIL_64FX1:
			_scalar.f64 = tmp;
			break;
		}
	}

	TypedScalar::operator uint8_t() const throw() {
		return static_cast<uint8_t>(std::min<uint64_t>(operator uint64_t(), UINT8_MAX));
	}

	TypedScalar::operator uint16_t() const throw() {
		return static_cast<uint8_t>(std::min<uint64_t>(operator uint64_t(), UINT16_MAX));
	}

	TypedScalar::operator uint32_t() const throw() {
		return static_cast<uint32_t>(std::min<uint64_t>(operator uint64_t(), UINT32_MAX));
	}

	TypedScalar::operator uint64_t() const throw() {
		switch (_type.GetEnumeratedType()) {
		case ANVIL_8UX1:
			return _scalar.u8;
		case ANVIL_16UX1:
			return _scalar.u16;
		case ANVIL_32UX1:
			return _scalar.u32;
		case ANVIL_64UX1:
			return _scalar.u64;
		case ANVIL_8SX1:
			return _scalar.s8 < 0 ? 0ull : static_cast<uint64_t>(_scalar.s8);
		case ANVIL_16SX1:
			return _scalar.s16 < 0 ? 0ull : static_cast<uint64_t>(_scalar.s16);
		case ANVIL_32SX1:
			return _scalar.s32 < 0 ? 0ull : static_cast<uint64_t>(_scalar.s32);
		case ANVIL_64SX1:
			return _scalar.s64 < 0 ? 0ull : static_cast<uint64_t>(_scalar.s64);
		case ANVIL_8BX1:
			return _scalar.b8 ? 1u : 0u;
		case ANVIL_CX1:
			return static_cast<uint64_t>(_scalar.c);
#if ANVIL_F8_SUPPORT
		case ANVIL_8FX1:
			return _scalar.s64 < 0 ? 0ull : static_cast<uint64_t>(_scalar.f8);
#endif
#if ANVIL_F16_SUPPORT
		case ANVIL_16FX1:
			return _scalar.s64 < 0 ? 0ull : static_cast<uint64_t>(_scalar.f16);
#endif
		case ANVIL_32FX1:
			return _scalar.f32 < 0.f ? 0ull : static_cast<uint64_t>(_scalar.f32);
		case ANVIL_64FX1:
			return _scalar.f64 < 0.0 ? 0ull : static_cast<uint64_t>(_scalar.f64);
		default:
			return 0;
		}
	}

	TypedScalar::operator int8_t() const throw() {
		int64_t tmp = operator int64_t();
		tmp = std::min<int64_t>(tmp, INT8_MAX);
		tmp = std::max<int64_t>(tmp, INT8_MIN);
		return static_cast<uint8_t>(tmp);
	}

	TypedScalar::operator int16_t() const throw() {
		int64_t tmp = operator int64_t();
		tmp = std::min<int64_t>(tmp, INT16_MAX);
		tmp = std::max<int64_t>(tmp, INT16_MIN);
		return static_cast<uint16_t>(tmp);
	}

	TypedScalar::operator int32_t() const throw() {
		int64_t tmp = operator int64_t();
		tmp = std::min<int64_t>(tmp, INT32_MAX);
		tmp = std::max<int64_t>(tmp, INT32_MIN);
		return static_cast<uint32_t>(tmp);
	}

	TypedScalar::operator char() const throw() {
		return static_cast<char>(static_cast<int64_t>(*this));
	}

	TypedScalar::operator bool() const throw() {
		return static_cast<int64_t>(*this) != 0;
	}

	TypedScalar::operator int64_t() const throw() {
		switch (_type.GetEnumeratedType()) {
		case ANVIL_8UX1:
			return _scalar.u8;
		case ANVIL_16UX1:
			return _scalar.u16;
		case ANVIL_32UX1:
			return _scalar.u32;
		case ANVIL_64UX1:
			return _scalar.u64 > static_cast<uint64_t>(INT64_MAX) ? INT64_MAX : static_cast<uint64_t>(_scalar.u64);
		case ANVIL_8SX1:
			return _scalar.s8;
		case ANVIL_16SX1:
			return _scalar.s16;
		case ANVIL_32SX1:
			return _scalar.s32;
		case ANVIL_64SX1:
			return _scalar.s64;
		case ANVIL_8BX1:
			return _scalar.b8 ? 1 : 0;
		case ANVIL_CX1:
			return static_cast<int64_t>(_scalar.c);
#if ANVIL_F8_SUPPORT
		case ANVIL_8FX1:
			return static_cast<int64_t>(_scalar.f8);
#endif
#if ANVIL_F16_SUPPORT
		case ANVIL_16FX1:
			return static_cast<int64_t>(_scalar.f16);
#endif
		case ANVIL_32FX1:
			return static_cast<int64_t>(_scalar.f32);
		case ANVIL_64FX1:
			return static_cast<int64_t>(_scalar.f64);
		default:
			return 0;
		}
	}

#if ANVIL_F8_SUPPORT
	TypedScalar::operator float8_t() const throw() {
		return static_cast<float8_t>(static_cast<float>(*this));
	}
#endif

#if ANVIL_F16_SUPPORT
	TypedScalar::operator float16_t() const throw() {
		return static_cast<float16_t>(static_cast<float>(*this));
	}
#endif

	TypedScalar::operator float32_t() const throw() {
		switch (_type.GetEnumeratedType()) {
		case ANVIL_8UX1:
			return _scalar.u8;
		case ANVIL_16UX1:
			return _scalar.u16;
		case ANVIL_32UX1:
			return static_cast<float32_t>(_scalar.u32);
		case ANVIL_64UX1:
			return static_cast<float32_t>(_scalar.u64);
		case ANVIL_8SX1:
			return _scalar.s8;
		case ANVIL_16SX1:
			return _scalar.s16;
		case ANVIL_32SX1:
			return static_cast<float32_t>(_scalar.s32);
		case ANVIL_64SX1:
			return static_cast<float32_t>(_scalar.s64);
		case ANVIL_8BX1:
			return _scalar.b8 ? 1.f : 0.f;
		case ANVIL_CX1:
			return static_cast<float32_t>(_scalar.c);
#if ANVIL_F8_SUPPORT
		case ANVIL_8FX1:
			return static_cast<float32_t>(_scalar.f8);
#endif
#if ANVIL_F16_SUPPORT
		case ANVIL_16FX1:
			return static_cast<float32_t>(_scalar.f16);
#endif
		case ANVIL_32FX1:
			return static_cast<float32_t>(_scalar.f32);
		case ANVIL_64FX1:
			return static_cast<float32_t>(_scalar.f64);
		default:
			return 0.f;
		}
	}

	TypedScalar::operator float64_t() const throw() {
		switch (_type.GetEnumeratedType()) {
		case ANVIL_8UX1:
			return _scalar.u8;
		case ANVIL_16UX1:
			return _scalar.u16;
		case ANVIL_32UX1:
			return _scalar.u32;
		case ANVIL_64UX1:
			return static_cast<float64_t>(_scalar.u64);
		case ANVIL_8SX1:
			return _scalar.s8;
		case ANVIL_16SX1:
			return _scalar.s16;
		case ANVIL_32SX1:
			return _scalar.s32;
		case ANVIL_64SX1:
			return static_cast<float64_t>(_scalar.s64);
#if ANVIL_F8_SUPPORT
		case ANVIL_8FX1:
			return static_cast<float64_t>(_scalar.f8);
#endif
#if ANVIL_F16_SUPPORT
		case ANVIL_16FX1:
			return static_cast<float64_t>(_scalar.f16);
#endif
		case ANVIL_32FX1:
			return static_cast<float64_t>(_scalar.f32);
		case ANVIL_64FX1:
			return _scalar.f64;
		default:
			return 0.0;
		}
	}

	TypedScalar::operator UntypedScalar() const throw() {
		return _scalar;
	}

	bool TypedScalar::operator==(const TypedScalar& other) const throw() {
		if (_type == other._type) {
			return _scalar.u64 == _scalar.u64;
		} else {
			return operator float64_t() == static_cast<float64_t>(other);
		}
	}

	bool TypedScalar::operator!=(const TypedScalar& other) const throw() {
		if (_type == other._type) {
			return _scalar.u64 != _scalar.u64;
		} else {
			return operator float64_t() != static_cast<float64_t>(other);
		}
	}

	bool TypedScalar::operator>(const TypedScalar& other) const throw() {
		return operator float64_t() > static_cast<float64_t>(other);
	}

	bool TypedScalar::operator<(const TypedScalar& other) const throw() {
		return operator float64_t() < static_cast<float64_t>(other);
	}

	bool TypedScalar::operator>=(const TypedScalar& other) const throw() {
		return operator float64_t() >= static_cast<float64_t>(other);
	}

	bool TypedScalar::operator<=(const TypedScalar& other) const throw() {
		return operator float64_t() <= static_cast<float64_t>(other);
	}

	void TypedScalar::ConvertToInPlace(Type type) {
		type.SetNumberOfChannels(1u);

		switch (type.GetEnumeratedType()) {
		case ANVIL_8UX1:
			_scalar.u8 = static_cast<uint8_t>(*this);
			break;
		case ANVIL_16UX1:
			_scalar.u16 = static_cast<uint16_t>(*this);
			break;
		case ANVIL_32UX1:
			_scalar.u32 = static_cast<uint32_t>(*this);
			break;
		case ANVIL_64UX1:
			_scalar.u64 = static_cast<uint64_t>(*this);
			break;
		case ANVIL_8SX1:
			_scalar.s8 = static_cast<int8_t>(*this);
			break;
		case ANVIL_16SX1:
			_scalar.s16 = static_cast<int16_t>(*this);
			break;
		case ANVIL_32SX1:
			_scalar.s32 = static_cast<int32_t>(*this);
			break;
		case ANVIL_64SX1:
			_scalar.s64 = static_cast<int64_t>(*this);
			break;
		case ANVIL_8FX1:
#if ANVIL_F8_SUPPORT
			_scalar.f8 = static_cast<float8_t>(*this);
#else
			throw std::runtime_error("anvil::Scalar::ConvertTo : float8_t is not supported");
#endif
			break;
		case ANVIL_16FX1:
#if ANVIL_F16_SUPPORT
			_scalar.f16 = static_cast<float16_t>(*this);
#else
			throw std::runtime_error("anvil::Scalar::ConvertTo : float16_t is not supported");
#endif
			break;
		case ANVIL_32FX1:
			_scalar.f32 = static_cast<float>(*this);
			break;
		case ANVIL_64FX1:
			_scalar.f64 = static_cast<double>(*this);
			break;
		default:
			throw std::runtime_error("anvil::Scalar::ConvertTo : Unknown type");
		}
	}

	TypedScalar TypedScalar::ConvertTo(Type type) const {
		TypedScalar tmp = *this;
		tmp.ConvertToInPlace(type);
		return tmp;
	}

}}