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

#ifndef ANVIL_CORE_OPERATING_SYSTEM_HPP
#define ANVIL_CORE_OPERATING_SYSTEM_HPP

// Define operating systems here
#define ANVIL_WINDOWS 0
#define ANVIL_LINUX 1
#define ANVIL_APPLE 2
#define ANVIL_BSD 3

// Detect which operating system this library is being compiled for
#if defined(_WIN32) || defined (_WIN64)
	#define ANVIL_OS ANVIL_WINDOWS
	#define ANVIL_OS_NAME "Windows" 
#elif defined(__linux__) || defined(linux) || defined(__linux)
	#define ANVIL_OS ANVIL_LINUX
	#define ANVIL_OS_NAME "Linux" 
#elif defined(__APPLE__) || defined (__MACH__)
	#define ANVIL_OS ANVIL_APPLE
	#define ANVIL_OS_NAME "Apple" 
#elif defined(__FreeBSD__)
	#define ANVIL_OS ANVIL_BSD
	#define ANVIL_OS_NAME "BSD" 
#else
	#error Could not determine OS
#endif

#endif