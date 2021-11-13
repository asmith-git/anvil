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

#include "anvil/core/Scalar.hpp"
#include <algorithm>

namespace anvil {


	// TypedScalar

	TypedScalar::TypedScalar() :
		_scalar(0u)
	{}

	TypedScalar::TypedScalar(const Type type) :
		_scalar(0u),
		_type(type)
	{}

	TypedScalar::TypedScalar(const Type type, const UntypedScalar& scalar) :
		_scalar(scalar.u64),
		_type(type)
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

	void TypedScalar::SetType(const Type type) throw() {
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
		case ANVIL_32FX1:
			return _scalar.f32 < 0.f ? 0ull : static_cast<uint64_t>(_scalar.f32);
		case ANVIL_64FX1:
			return _scalar.f64 < 0.0 ? 0ull : static_cast<uint64_t>(_scalar.f64);
		}
	}

	TypedScalar::operator int8_t() const throw() {
		int64_t tmp = operator int64_t();
		tmp = std::min<uint64_t>(tmp, INT8_MAX);
		tmp = std::max<uint64_t>(tmp, INT8_MIN);
		return static_cast<uint8_t>(tmp);
	}

	TypedScalar::operator int16_t() const throw() {
		int64_t tmp = operator int64_t();
		tmp = std::min<uint64_t>(tmp, INT16_MAX);
		tmp = std::max<uint64_t>(tmp, INT16_MIN);
		return static_cast<uint16_t>(tmp);
	}

	TypedScalar::operator int32_t() const throw() {
		int64_t tmp = operator int64_t();
		tmp = std::min<uint64_t>(tmp, INT32_MAX);
		tmp = std::max<uint64_t>(tmp, INT32_MIN);
		return static_cast<uint32_t>(tmp);
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
		case ANVIL_32FX1:
			return static_cast<int64_t>(_scalar.f32);
		case ANVIL_64FX1:
			return static_cast<int64_t>(_scalar.f64);
		}
	}

	TypedScalar::operator float32_t() const throw() {
		switch (_type.GetEnumeratedType()) {
		case ANVIL_8UX1:
			return _scalar.u8;
		case ANVIL_16UX1:
			return _scalar.u16;
		case ANVIL_32UX1:
			return _scalar.u32;
		case ANVIL_64UX1:
			return static_cast<float32_t>(_scalar.u64);
		case ANVIL_8SX1:
			return _scalar.s8;
		case ANVIL_16SX1:
			return _scalar.s16;
		case ANVIL_32SX1:
			return _scalar.s32;
		case ANVIL_64SX1:
			return static_cast<float32_t>(_scalar.s64);
		case ANVIL_32FX1:
			return static_cast<float32_t>(_scalar.f32);
		case ANVIL_64FX1:
			return static_cast<float32_t>(_scalar.f64);
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
		case ANVIL_32FX1:
			return static_cast<float64_t>(_scalar.f32);
		case ANVIL_64FX1:
			return _scalar.f64;
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
}