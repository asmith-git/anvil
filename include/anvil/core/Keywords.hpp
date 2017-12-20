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

// Define keywords

#if ANVIL_COMPILER == ANVIL_MSVC
	#define ANVIL_STRONG_INLINE __forceinline
	#define ANVIL_RESTRICT __restrict
#elif defined(ANVIL_GCC_COMPATIBILITY)
	#define ANVIL_STRONG_INLINE __attribute__((always_inline))
	#define ANVIL_RESTRICT __restrict__
#else
	#define ANVIL_STRONG_INLINE inline
	#define ANVIL_RESTRICT
#endif

#if ANVIL_CPP_VER >= 2011
	#define ANVIL_CONSTEXPR_VAR constexpr
	#define ANVIL_CONSTEXPR_FN constexpr
	#define ANVIL_CONSTEXPR_CLA constexpr
#else
	#define ANVIL_CONSTEXPR_VAR 
	#define ANVIL_CONSTEXPR_FN inline
	#define ANVIL_CONSTEXPR_CLA
#endif

#ifndef ANVIL_CALL
	#define ANVIL_CALL
#endif

#ifndef ANVIL_COMPILETIME_ASSERT
	#define ANVIL_COMPILETIME_ASSERT(predicate, message) static_assert(predicate, message)
#endif

#ifndef ANVIL_RUNTIME_ASSERT
	#define ANVIL_RUNTIME_ASSERT(predicate, message) if(! (predicate)) throw std::runtime_error(message);
#endif

// Define types

typedef float float32_t;
typedef double float64_t;

#endif