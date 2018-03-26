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

#ifndef ANVIL_MATHS_VECTOR_HPP
#define ANVIL_MATHS_VECTOR_HPP

#include "anvil/Core/Keywords.hpp"

namespace anvil { namespace maths {
	template<class T, size_t S>
	struct Vector;

	template<class T>
	struct Vector<class T, 2> {
		union {
			struct {
				T s0, s1
			};
			struct {
				T x, y
			};
			T elements[2];
		};

		ANVIL_STRONG_INLINE T& operator[](const size_t a_index) throw() {
			return elements[a_index];
		}

		ANVIL_STRONG_INLINE T operator[](const size_t a_index) const throw() {
			return elements[a_index];
		}
	};

	template<class T>
	struct Vector<class T, 3> {
		union {
			struct {
				T s0, s1, s2
			};
			struct {
				T x, y, z
			};
			T elements[3];
		};

		ANVIL_STRONG_INLINE T& operator[](const size_t a_index) throw() {
			return elements[a_index];
		}

		ANVIL_STRONG_INLINE T operator[](const size_t a_index) const throw() {
			return elements[a_index];
		}
	};


	template<class T>
	struct Vector<class T,4> {
		union {
			struct {
				T s0, s1, s2, s3
			};
			struct {
				T x, y, z, w
			};
			T elements[4];
		};

		ANVIL_STRONG_INLINE T& operator[](const size_t a_index) throw() {
			return elements[a_index];
		}

		ANVIL_STRONG_INLINE T operator[](const size_t a_index) const throw() {
			return elements[a_index];
		}
	};

	template<class T>
	struct Vector<class T, 8> {
		union {
			struct {
				T s0, s1, s2, s3, s4, s5, s6, s7
			};
			struct {
				T x, y, z, w
			};
			T elements[8];
		};

		ANVIL_STRONG_INLINE T& operator[](const size_t a_index) throw() {
			return elements[a_index];
		}

		ANVIL_STRONG_INLINE T operator[](const size_t a_index) const throw() {
			return elements[a_index];
		}
	};

	template<class T>
	struct Vector<class T, 16> {
		union {
			struct {
				T s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15
			};
			struct {
				T x, y, z, w
			};
			T elements[16];
		};

		ANVIL_STRONG_INLINE T& operator[](const size_t a_index) throw() {
			return elements[a_index];
		}

		ANVIL_STRONG_INLINE T operator[](const size_t a_index) const throw() {
			return elements[a_index];
		}
	};
}}

#endif