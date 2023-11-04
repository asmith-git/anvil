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

#ifndef ANVIL_CORE_LOCAL_PTR_HPP
#define ANVIL_CORE_LOCAL_PTR_HPP

#include <cstring>
#include <type_traits>
#include "anvil/core/Keywords.hpp"

namespace anvil {

	/*!
	*	\brief Acts like std::unique_ptr but uses local placement allocations.
	*	\details Use if you need to avoid overheads of heap memory allocation.
	*	\tparam T The type to allocate.
	*	\tparam BYTES The number of bytes to reserve to allocate. Increase from the default value if sub-classes of T are required.
	*/
	template<class T, size_t BYTES = sizeof(T), bool MOVABLE = std::is_move_assignable<T>::value && std::is_default_constructible<T>::value>
	class LocalPointer;

	template<class T, size_t BYTES>
	class LocalPointer<T, BYTES, true> {
	private:
		uint8_t _local_memory[BYTES];	//!< Local memory for allocations
		bool _is_allocated;				//!< True if something is currently allocated in _local_memory
	public:
		typedef T element_type;
		typedef element_type* pointer;
		typedef const element_type* const_pointer;

		typedef LocalPointer<element_type, BYTES> this_t;

		LocalPointer(this_t&&) = delete;
		LocalPointer(const this_t&) = delete;

		LocalPointer() :
			_local_memory{},
			_is_allocated(false)
		{}

		~LocalPointer() {
			Deallocate();
		}

		template<class ...PARAMS>
		LocalPointer(PARAMS... params) :
			LocalPointer()
		{
			reset<element_type>(params...);
		}

		template<class T2 = element_type>
		this_t& operator=(const this_t& other) {
			if (other._is_allocated) {
				if (_is_allocated) {
					*get() = *other;
				} else {
					reset<T2>(*other);
				}
			} else {
				Deallocate();
			}
			return *this;
		}

		template<class T2 = element_type>
		this_t& operator=(this_t&& other) {
			if (other._is_allocated) {
				if (_is_allocated) {
					*get() = std::move(*other);
				} else {
					reset<T2>(std::move(*other));
				}
			} else {
				Deallocate();
			}
			return *this;
		}

		void Deallocate() {
			if (_is_allocated) {
				reinterpret_cast<element_type*>(_local_memory)->~T();
				_is_allocated = false;
			}
		}

		template<class NEW_T = element_type>
		inline std::enable_if<std::is_default_constructible<NEW_T>::value, void>::type reset() {
			// Compile-time safety checks
			static_assert(std::is_same<element_type, NEW_T>::value || std::is_base_of<element_type, NEW_T>::value, "anvil::LocalPointer::Allocate : class is not allowed");
			static_assert(sizeof(NEW_T) <= BYTES, "anvil::LocalPointer::Allocate : Not enough memory to allocate class");

			Deallocate();
			new(_local_memory) NEW_T();
			_is_allocated = true;
		}

		template<class NEW_T, class ...PARAMS>
		inline void reset(PARAMS... params) {
			// Compile-time safety checks
			static_assert(std::is_same<element_type, NEW_T>::value || std::is_base_of<element_type, NEW_T>::value, "anvil::LocalPointer::Allocate : class is not allowed");
			static_assert(sizeof(NEW_T) <= BYTES, "anvil::LocalPointer::Allocate : Not enough memory to allocate class");

			Deallocate();
			new(_local_memory) NEW_T(params...);
			_is_allocated = true;
		}

		inline element_type* get() {
			return _is_allocated ? reinterpret_cast<element_type*>(_local_memory) : nullptr;
		}

		inline const element_type* get() const {
			return _is_allocated ? reinterpret_cast<const element_type*>(_local_memory) : nullptr;
		}

		inline element_type release() {
			element_type tmp = std::move(*get());
			Deallocate();
			return tmp;
		}

		inline operator bool() const {
			return _is_allocated;
		}

		inline element_type* operator->() {
			return get();
		}

		inline const element_type* operator->() const {
			return get();
		}

		inline element_type& operator*() {
			ANVIL_DEBUG_ASSERT(_is_allocated, "anvil::LocalPointer::get : Pointer is not allocated");
			return *get();
		}

		inline const element_type& operator*() const {
			ANVIL_DEBUG_ASSERT(_is_allocated, "anvil::LocalPointer::get : Pointer is not allocated");
			return *get();
		}

		inline bool operator!=(const void* other) const {
			return other == nullptr ? _is_allocated : this != other;
		}

		inline bool operator==(const void* other) const {
			return !operator!=(other);
		}

		inline bool operator==(const this_t& other) const {
			return _is_allocated ? this == &other : !other._is_allocated;
		}

		inline bool operator!=(const this_t& other) const {
			return !operator==(other);
		}
	};


	template<class T, size_t BYTES>
	class LocalPointer<T, BYTES, false> {
	private:
		uint8_t _local_memory[BYTES]; //!< Local memory for allocations
		bool _is_allocated;				//!< True if something is currently allocated in _local_memory
	public:
		typedef T element_type;
		typedef element_type* pointer;
		typedef const element_type* const_pointer;

		typedef LocalPointer<element_type, BYTES> this_t;

		LocalPointer(this_t&&) = delete;
		LocalPointer(const this_t&) = delete;
		this_t& operator=(this_t&&) = delete;
		this_t& operator=(const this_t&) = delete;

		LocalPointer() :
			_local_memory{},
			_is_allocated(false)
		{}

		~LocalPointer() {
			Deallocate();
		}

		template<class ...PARAMS>
		LocalPointer(PARAMS... params) :
			LocalPointer()
		{
			reset<element_type>(params...);
		}

		void Deallocate() {
			if (_is_allocated) {
				reinterpret_cast<element_type*>(_local_memory)->~T();
				_is_allocated = false;
			}
		}

		template<class NEW_T = element_type>
		inline std::enable_if<std::is_default_constructible<NEW_T>::value, void>::type reset() {
			// Compile-time safety checks
			static_assert(std::is_same<element_type, NEW_T>::value || std::is_base_of<element_type, NEW_T>::value, "anvil::LocalPointer::Allocate : class is not allowed");
			static_assert(sizeof(NEW_T) <= BYTES, "anvil::LocalPointer::Allocate : Not enough memory to allocate class");

			Deallocate();
			new(_local_memory) NEW_T();
			_is_allocated = true;
		}

		template<class NEW_T, class ...PARAMS>
		inline void reset(PARAMS... params) {
			// Compile-time safety checks
			static_assert(std::is_same<element_type, NEW_T>::value || std::is_base_of<element_type, NEW_T>::value, "anvil::LocalPointer::Allocate : class is not allowed");
			static_assert(sizeof(NEW_T) <= BYTES, "anvil::LocalPointer::Allocate : Not enough memory to allocate class");

			Deallocate();
			new(_local_memory) NEW_T(params...);
			_is_allocated = true;
		}

		inline element_type* get() {
			return _is_allocated ? reinterpret_cast<element_type*>(_local_memory) : nullptr;
		}

		inline const element_type* get() const {
			return _is_allocated ? reinterpret_cast<const element_type*>(_local_memory) : nullptr;
		}

		template<class T2 = element_type>
		inline void release() {
			Deallocate();
		}

		inline operator bool() const {
			return _is_allocated;
		}

		inline element_type* operator->() {
			return get();
		}

		inline const element_type* operator->() const {
			return get();
		}

		inline element_type& operator*() {
			ANVIL_DEBUG_ASSERT(_is_allocated, "anvil::LocalPointer::get : Pointer is not allocated");
			return *get();
		}

		inline const element_type& operator*() const {
			ANVIL_DEBUG_ASSERT(_is_allocated, "anvil::LocalPointer::get : Pointer is not allocated");
			return *get();
		}

		inline bool operator!=(const void* other) const {
			return other == nullptr ? _is_allocated : this != other;
		}

		inline bool operator==(const void* other) const {
			return !operator!=(other);
		}

		inline bool operator==(const this_t& other) const {
			return _is_allocated ? this == &other : !other._is_allocated;
		}

		inline bool operator!=(const this_t& other) const {
			return !operator==(other);
		}
	};

	template<class T, size_t BYTES = sizeof(T)>
	using LocalPtr = LocalPointer<T, BYTES>;

	template<class T, size_t BYTES = sizeof(T)>
	using local_ptr = LocalPointer<T, BYTES>;

}

#endif