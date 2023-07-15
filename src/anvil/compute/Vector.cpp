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

#include <algorithm>
#include "anvil/Core.hpp"
#include "anvil/compute/Vector.hpp"

namespace anvil { namespace compute {

	// Vector

	Vector::Vector() {

	}

	Vector::Vector(const Type type) :
		_type(type)
	{}

	void Vector::ConvertToInPlace(Type type) {
		if (_type == type) return;

		//! \todo Optimise
		const size_t s = Size();
		for (size_t i = 0; i < s; ++i) {
			UntypedScalar& tmp = operator[](i);
			tmp = TypedScalar(_type, tmp).ConvertTo(type);
		}
		_type = type;
	}

	Vector Vector::ConvertTo(Type type) const {
		Vector tmp = *this;
		tmp.ConvertToInPlace(type);
		return tmp;
	}

	bool Vector::operator==(const Vector& other) const throw() {
		if (_type != other._type) return false;
		return memcmp(_values, other._values, _type.GetSizeInBytes()) == 0;
	}

	bool Vector::operator!=(const Vector& other) const throw() {
		if (_type != other._type) return true;
		return memcmp(_values, other._values, _type.GetSizeInBytes()) != 0;
	}

	UntypedScalar& Vector::operator[](const size_t i) {
		return *reinterpret_cast<UntypedScalar*>(_values + i * _type.GetPrimitiveSizeInBytes()); 
	}

	TypedScalar Vector::operator[](const size_t i) const {
		return TypedScalar(_type, *reinterpret_cast<const UntypedScalar*>(_values + i * _type.GetPrimitiveSizeInBytes()));
	}

}}