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

#ifndef ANVIL_CORE_CONSTANTS_HPP
#define ANVIL_CORE_CONSTANTS_HPP

#include <stdint>
#include <type_traits>

namespace anvil {

	/*!
	\brief Compare two constant values.
	\tparam T The type of the values.
	\tparam A_ The first value.
	\tparam B_ The second value.
	\tparam ENABLE Internal use only (Avoids division by 0 error).
	*/
	template<class T, T A_, T B_, class ENABLE = void>
	struct ConstantOperation;

	template<class T, T A_, T B_>
	struct ConstantOperation<T, A_, B_, typename std::enable_if<B_ != 0>::type> {
		enum : T {
			A = A_,                 //!< The first value.
			B = B_,                 //!< The second value.
			min = A < B ? A : B,    //!< The smaller value.
			max = A > B ? A : B,    //!< The larger value.
			add = A + B,    		//!< A added to B.
			sub = A - B,    		//!< B subtracted from A.
			mul = A * B,    		//!< A multiplied by B.
			div = A / B,    		//!< A divided by B.
			and = A & B,    		//!< Bitwise A AND B.
			or = A | B,    		    //!< Bitwise A OR B.
			xor = A ^ B,    		//!< Bitwise A XOR B.
			rshift = A >> B,    	//!< A right shifted by B.
			lshift = A << B    		//!< A left shifted by B.
		};

		enum {
			eq = A == B,            //!< 1 if A is equal to B, else 0.
			ne = A != B,            //!< 1 if A is not equal to B, else 0.
			lt = A < B,             //!< 1 if A is less than B, else 0.
			gt = A > B,             //!< 1 if A is greater than B, else 0.
			le = A <= B,            //!< 1 if A is greater than or equal to B, else 0.
			ge = A >= B             //!< 1 if A is less than or equal to B, else 0.
		};
	};

	template<class T, T A_, T B_>
	struct ConstantOperation<T, A_, B_, typename std::enable_if<B_ == 0>::type> {
		enum : T {
			A = A_,
			B = 0,
			min = A < B ? A : B,
			max = A > B ? A : B,
			add = A,
			sub = A,
			mul = 0,
			div = 0,
			and = 0,
			or = A,
			xor = A,
			rshift = A,
			lshift = A
		};

		enum {
			eq = A == B,
			ne = A != B,
			lt = A < B,
			gt = A > B,
			le = A <= B,
			ge = A >= B
		};
	};
	/*!
	\brief Calculate an integer power in compile time.
	\tparam VALUE The operand value.
	\tparam EXPONENT The exponent value.
	*/
	template <int VALUE, int EXPONENT>
	struct ConstantPower {
		enum {
			value = VALUE * ConstantPower<VALUE, EXPONENT - 1>::value	//!< The resulting value.
		};
	};

	template <int VALUE>
	struct ConstantPower<VALUE, 0> {
		enum {
			value = 1
		};
	};

	/*!
	\brief Create a bitmask in compile time.
	\tparam T The container type for the mask.
	\tparam BITS The number of bits to set in the mask.
	*/
	template<class T, size_t BITS>
	struct ConstantBitmask {
		enum : T {
			value = (ConstantBitmask<T, BITS - 1>::value << static_cast<T>(1)) | static_cast<T>(1)	//!< The resulting value.
		};
	};

	template<class T>
	struct ConstantBitmask<T, 1> {
		enum : T {
			value = 1
		};
	};

	/*!
	\brief Create a popcount (number of 1's) in compile time.
	\tparam VAL The value to count.
	*/
	template<int64_t VAL>
	struct ConstantPopcount {
		enum {
			value = (VAL & 1) + ConstantPopcount<ConstantOperation<int64_t, VAL, 1>::rshift>::value	//!< The resulting value.
		};
	};

	template<>
	struct ConstantPopcount<0> {
		enum {
			value = 0
		};
	};
}


#define ANVIL_CMPEQ(a,b)  (anvil::ConstantOperation<decltype(a), a, b>::eq)
#define ANVIL_CMPNE(a,b)  (anvil::ConstantOperation<decltype(a), a, b>::ne)
#define ANVIL_CMPLT(a,b)  (anvil::ConstantOperation<decltype(a), a, b>::lt)
#define ANVIL_CMPGT(a,b)  (anvil::ConstantOperation<decltype(a), a, b>::gt)
#define ANVIL_CMPLE(a,b)  (anvil::ConstantOperation<decltype(a), a, b>::le)
#define ANVIL_CMPGE(a,b)  (anvil::ConstantOperation<decltype(a), a, b>::ge)
#define ANVIL_CMPMIN(a,b) (anvil::ConstantOperation<decltype(a), a, b>::min)
#define ANVIL_CMPMAX(a,b) (anvil::ConstantOperation<decltype(a), a, b>::max)

#endif