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

#include "anvil/core/Allocator.hpp"

namespace anvil {

	static AllocatorCPP g_default_allocator;
	static Allocator* g_default_allocator_override = nullptr;

	// Allocator

	Allocator* Allocator::GetDefaultAllocator() {
		return g_default_allocator_override ? g_default_allocator_override : &g_default_allocator;
	}

	void Allocator::SetDefaultAllocator(Allocator* allocator) {
		g_default_allocator_override = allocator;
	}

	Allocator::Allocator() {

	}

	Allocator::~Allocator() {

	}

	// AllocatorC

	AllocatorC::AllocatorC() {

	}

	AllocatorC::~AllocatorC() {

	}

	void* AllocatorC::Allocate(size_t bytes) {
		return malloc(bytes);
	}

	void AllocatorC::Deallocate(void* address) {
		if (address) free(address);
	}


	// AllocatorCPP

	AllocatorCPP::AllocatorCPP() {

	}

	AllocatorCPP::~AllocatorCPP() {

	}

	void* AllocatorCPP::Allocate(size_t bytes) {
		return operator new(bytes);
	}

	void AllocatorCPP::Deallocate(void* address) {
		if (address) operator delete(address);
	}

}