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


// Define a compiler here
#define ANVIL_MSVC 0
#define ANVIL_GCC 1
#define ANVIL_CLANG 2
#define ANVIL_INTEL 3

// Detect which compiler is running
#if defined(_MSC_VER)
	#define ANVIL_COMPILER ANVIL_MSVC
	#define ANVIL_COMPILER_VER _MSC_VER 
	#define ANVIL_COMPILER_NAME "MSVC" 
#elif defined(__clang__)
	#define ANVIL_COMPILER ANVIL_CLANG
	#define ANVIL_COMPILER_VER (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel_)
	#define ANVIL_COMPILER_NAME "Clang" 
#elif defined(__GNUC__)
	#define ANVIL_COMPILER ANVIL_GCC
	#define ANVIL_COMPILER_VER (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
	#define ANVIL_COMPILER_NAME "GCC" 
#elif defined(__INTEL_COMPILER)
	#define ANVIL_COMPILER ANVIL_INTEL
	#define ANVIL_COMPILER_VER __INTEL_COMPILER_BUILD_DATE
	#define ANVIL_COMPILER_NAME "Intel" 
#else
	#error Could not determine C++ compiler vendor
#endif

// Detect which C++ standard is being compiled
#if ANVIL_COMPILER == ANVIL_MSVC
	#if ANVIL_COMPILER_VER >= 1910 
		#define ANVIL_CPP_VER 2014
	#elif ANVIL_COMPILER_VER >= 1900 
		#define ANVIL_CPP_VER 2011
	#endif
#endif


#ifndef ANVIL_CPP_VER
	#if __cplusplus >= 199700L && __cplusplus < 201100L
		#define ANVIL_CPP_VER 1998
	#elif __cplusplus >= 201100L && __cplusplus < 201400L
		#define ANVIL_CPP_VER 2011
	#elif __cplusplus >= 201400L && __cplusplus < 201700L
		#define ANVIL_CPP_VER 2014
	#elif __cplusplus >= 201700L
		#define ANVIL_CPP_VER 2017
	#elif __cplusplus >= 202002L
		#define ANVIL_CPP_VER 2020
	#else
		#error Requires C++98 or greater
	#endif
#endif

#endif