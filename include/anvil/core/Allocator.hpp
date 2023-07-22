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

#ifndef ANVIL_ALLOCATOR_HPP
#define ANVIL_ALLOCATOR_HPP

#include "anvil/core/Keywords.hpp"

namespace anvil { 
	
	class ANVIL_DLL_EXPORT Allocator {
	public:
		static Allocator* GetDefaultAllocator();
		static void SetDefaultAllocator(Allocator* allocator);

		Allocator();
		virtual ~Allocator();

		virtual void* Allocate(size_t bytes) = 0;
		virtual void Deallocate(void* address) = 0;
	};

	/*!
	*	\brief Allocates memory calling malloc and free.
	*/
	class ANVIL_DLL_EXPORT AllocatorC final : public Allocator {
	public:
		AllocatorC();
		virtual ~AllocatorC();

		void* Allocate(size_t bytes) final;
		void Deallocate(void* address) final;
	};

	/*!
	*	\brief Allocates memory calling operator new and delete
	*/
	class ANVIL_DLL_EXPORT AllocatorCPP final : public Allocator {
	public:
		AllocatorCPP();
		virtual ~AllocatorCPP();

		void* Allocate(size_t bytes) final;
		void Deallocate(void* address) final;
	};


}

#endif
