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

#ifndef ANVIL_CORE_KEYWORDS_HPP
#define ANVIL_CORE_KEYWORDS_HPP

#include "anvil/core/Compiler.hpp"
#include "anvil/core/Cpu.hpp"
#include <cstdint>
#include <stdexcept>

// Strongest inlining hint available in the compiler
#if ANVIL_COMPILER == ANVIL_MSVC
	#define ANVIL_STRONG_INLINE __forceinline
#elif ANVIL_COMPILER == ANVIL_GCC || ANVIL_COMPILER == ANVIL_CLANG
	#define ANVIL_STRONG_INLINE __attribute__((always_inline))
#else
	#define ANVIL_STRONG_INLINE inline
#endif

// Pointer overlap restriction
#if ANVIL_COMPILER == ANVIL_MSVC
	#define ANVIL_RESTRICT __restrict
#elif ANVIL_COMPILER == ANVIL_GCC || ANVIL_COMPILER == ANVIL_CLANG
	#define ANVIL_RESTRICT __restrict__
#else
	#define ANVIL_RESTRICT
#endif

// Support for C++ standards older than C++11
#if ANVIL_CPP_VER >= 2011
	#define ANVIL_CONSTEXPR_VAR constexpr
	#define ANVIL_CONSTEXPR_FN constexpr
	#define ANVIL_CONSTEXPR_CLA constexpr
	#define ANVIL_ALIGN(x) alignas(x)
	#define ANVIL_THREAD_LOCAL thread_local
#else
	#define ANVIL_CONSTEXPR_VAR 
	#define ANVIL_CONSTEXPR_FN inline
	#define ANVIL_CONSTEXPR_CLA

	#if ANVIL_COMPILER == ANVIL_MSVC
		#define ANVIL_ALIGN(x) __declspec(align(x))
		#define ANVIL_THREAD_LOCAL __declspec(thread)
	#else
		#define ANVIL_THREAD_LOCAL //! \todo Thread local on non-microsoft compilers
		#define ANVIL_ALIGN(x)
	#endif
#endif

// Default calling convention
#ifndef ANVIL_CALL
	#define ANVIL_CALL
#endif

// If a different compile-time assert hasn't already been specified then use C++'s static_assert
#ifndef ANVIL_COMPILETIME_ASSERT
	#define ANVIL_COMPILETIME_ASSERT(predicate, message) static_assert(predicate, message)
#endif

// If a different run-time assert hasn't already been specified then throw an exception
#ifndef ANVIL_RUNTIME_ASSERT
	#define ANVIL_RUNTIME_ASSERT(predicate, message) if(! (predicate)) throw std::runtime_error(message);
#endif

namespace anvil {
	// Define floating point types in the same style as stdint.h
	typedef float float32_t;
	typedef double float64_t;

	// Define CPU native words
#if ANVIL_CPU_ARCHITECTURE_BITS == 8
	typedef int8_t NativeSigned;
	typedef uint8_t NativeUnsigned;
#elif ANVIL_CPU_ARCHITECTURE_BITS == 16
	typedef int16_t NativeSigned;
	typedef uint16_t NativeUnsigned;
#elif ANVIL_CPU_ARCHITECTURE_BITS == 32
	typedef int32_t NativeSigned;
	typedef uint32_t NativeUnsigned;
#elif ANVIL_CPU_ARCHITECTURE_BITS >= 64
	typedef int64_t NativeSigned;
	typedef uint64_t NativeUnsigned;
#endif

	static_assert(sizeof(intptr_t) == sizeof(NativeSigned), "Definition of intptr_t does not match the detected native word size");
	static_assert(sizeof(uintptr_t) == sizeof(NativeUnsigned), "Definition of intptr_t does not match the detected native word size");

	template<class T_OUT, class T_IN>
	static ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_FN T_OUT ANVIL_CALL numeric_reinterpret_cast(const T_IN value) {
		ANVIL_COMPILETIME_ASSERT(sizeof(T_OUT) == sizeof(T_IN), "anvil::numeric_reinterpret_cast : Types must be the same size");
		return *reinterpret_cast<const T_OUT*>(&value);
	}
}

#endif