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

	Vector::Vector() :
		_type(),
		_values{}
	{}

	Vector::Vector(Type type) :
		_type(type),
		_values{}
	{}

	Vector::Vector(UntypedScalar value, Type type) :
		Vector(type)
	{
		const size_t size = type.GetPrimitiveSizeInBytes();
		const size_t count = type.GetNumberOfChannels();
		uint8_t* tmp = _values;
		for (size_t i = 0u; i < count; ++i) {
			memcpy(tmp, value.GetData(), size);
			tmp += size;
		}
	}

	void Vector::ConvertToInPlace(Type type) {
		if (_type == type) return;

		//! \todo Optimise
		const size_t s = Size();
		Vector tmp(type);
		TypedScalar scalar;
		for (size_t i = 0; i < s; ++i) {
			Read(i, scalar);
			scalar.ConvertToInPlace(type);
			tmp.Write(i, scalar._scalar);
		}

		*this = tmp;
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

	void Vector::Read(size_t i, UntypedScalar& value) const {
		const size_t bytes = _type.GetPrimitiveSizeInBytes();
		memcpy(value.GetData(), _values + i * bytes, bytes);
	}

	void Vector::Write(size_t i, UntypedScalar value) {
		const size_t bytes = _type.GetPrimitiveSizeInBytes();
		memcpy(_values + i * bytes, value.GetData(), bytes);
	}

}}