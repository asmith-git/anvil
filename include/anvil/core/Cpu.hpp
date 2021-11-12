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

#ifndef ANVIL_CORE_CPU_HPP
#define ANVIL_CORE_CPU_HPP

// Define CPU instruction set families here
#define ANVIL_X86 0
#define ANVIL_X64 1
#define ANVIL_ARM 2
#define ANVIL_ARM_64 3

// Detect which CPU is being compiled for and define it's general purpose register size
#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64)
	#define ANVIL_ARCHITECTURE ANVIL_X64
	#define ANVIL_ARCHITECTURE_BITS 64
#elif defined(i386) || defined(__i386) || defined(__i386__) || defined(__i386__) || defined(_M_I86) || defined(_M_IX86) || defined(_X86_)
	#define ANVIL_ARCHITECTURE ANVIL_X86
	#define ANVIL_ARCHITECTURE_BITS 32
#elif defined(__aarch64__)
	#define ANVIL_ARCHITECTURE ANVIL_ARM
	#define ANVIL_ARCHITECTURE_BITS 64
#elif defined(__arm__) || defined(__thumb__) || defined(_M_ARM) || defined(_M_ARMT)
	#define ANVIL_ARCHITECTURE ANVIL_ARM
	#define ANVIL_ARCHITECTURE_BITS 32
#else
	#error Could not determine CPU architecture
#endif

#endif