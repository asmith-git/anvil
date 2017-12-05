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

#ifndef ANVIL_CORE_COMPILER_HPP
#define ANVIL_CORE_COMPILER_HPP

// Detect compiler vendor

#define ANVIL_MSVC 0
#define ANVIL_GCC 1
#define ANVIL_CLANG 2
#define ANVIL_INTEL 3

#if defined(_MSC_VER)
	#define ANVIL_COMPILER ANVIL_MSVC
#elif defined(__clang__)
	#define ANVIL_COMPILER ANVIL_CLANG
#elif defined(__GNUC__)
	#define ANVIL_COMPILER ANVIL_GCC
#elif defined(__INTEL_COMPILER)
	#define ANVIL_COMPILER ANVIL_INTEL
#else
	#error Could not determine C++ compiler vendor
#endif

// Detect C++ version

#if __cplusplus >= 199700L && __cplusplus < 201100L
	#define ANVIL_CPP_VER 1998
#elif __cplusplus >= 201100L && __cplusplus < 201400L
	#define ANVIL_CPP_VER 2011
#elif __cplusplus >= 201400L && __cplusplus < 201700L
	#define ANVIL_CPP_VER 2014
#elif __cplusplus >= 201700L
	#define ANVIL_CPP_VER 2017
#else
	#error Requires C++98 or greater
#endif

#endif