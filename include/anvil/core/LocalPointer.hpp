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
	template<class T, size_t BYTES>
	class _LocalPointer {
	private:
		uint8_t _local_memory[BYTES]; //!< Local memory for allocations
		bool _is_allocated;				//!< True if something is currently allocated in _local_memory
	public:
		typedef T element_type;
		typedef element_type* pointer;
		typedef const element_type* const_pointer;

		typedef _LocalPointer<element_type, BYTES> this_t;

		_LocalPointer(this_t&&) = delete;
		_LocalPointer(const this_t&) = delete;
		this_t& operator=(this_t&&) = delete;
		this_t& operator=(const this_t&) = delete;

		_LocalPointer() :
			_local_memory{},
			_is_allocated(false)
		{}

		~_LocalPointer() {
			Deallocate();
		}

		template<class ...PARAMS>
		_LocalPointer(PARAMS... params) :
			_LocalPointer()
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
			static_assert(sizeof(NEW_T) <= BYTES, "anvil::_LocalPointer::Allocate : Not enough memory to allocate class");

			Deallocate();
			new(_local_memory) NEW_T();
			_is_allocated = true;
		}

		template<class NEW_T = element_type, class ...PARAMS>
		inline void reset(PARAMS... params) {
			// Compile-time safety checks
			static_assert(std::is_same<element_type, NEW_T>::value || std::is_base_of<element_type, NEW_T>::value, "anvil::LocalPointer::Allocate : class is not allowed");
			static_assert(sizeof(NEW_T) <= BYTES, "anvil::_LocalPointer::Allocate : Not enough memory to allocate class");

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
			ANVIL_DEBUG_ASSERT(_is_allocated, "anvil::_LocalPointer::get : Pointer is not allocated");
			return *get();
		}

		inline const element_type& operator*() const {
			ANVIL_DEBUG_ASSERT(_is_allocated, "anvil::_LocalPointer::get : Pointer is not allocated");
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

	template<class PTR>
	class _LocalPointerWrapper {
	private:
		PTR _ptr;
	public:
		typedef typename PTR::element_type element_type;
		typedef PTR smart_pointer_type;
		typedef element_type* pointer;
		typedef const element_type* const_pointer;

		typedef _LocalPointerWrapper<PTR> this_t;

		_LocalPointerWrapper(this_t&&) = delete;
		_LocalPointerWrapper(const this_t&) = delete;
		this_t& operator=(this_t&&) = delete;
		this_t& operator=(const this_t&) = delete;

		_LocalPointerWrapper() :
			_ptr()
		{}

		~_LocalPointerWrapper() {
			Deallocate();
		}

		_LocalPointerWrapper(smart_pointer_type other) :
			_LocalPointerWrapper()
		{
			_ptr.swap(other);
		}

		template<class ...PARAMS>
		_LocalPointerWrapper(PARAMS... params) :
			_ptr(new element_type(params...))
		{
			
		}

		inline void Deallocate() {
			smart_pointer_type tmp;
			_ptr.swap(tmp);
		}

		template<class NEW_T = element_type>
		inline smart_pointer_type reset() {
			// Compile-time safety checks
			static_assert(std::is_same<element_type, NEW_T>::value || std::is_base_of<element_type, NEW_T>::value, "anvil::_LocalPointerWrapper::Allocate : class is not allowed");

			smart_pointer_type tmp(static_cast<element_type*>(new NEW_T()));
			_ptr.swap(tmp);
			return std::move(tmp);
		}

		template<class NEW_T = element_type, class ...PARAMS>
		inline smart_pointer_type reset(PARAMS... params) {
			// Compile-time safety checks
			static_assert(std::is_same<element_type, NEW_T>::value || std::is_base_of<element_type, NEW_T>::value, "anvil::_LocalPointerWrapper::Allocate : class is not allowed");

			smart_pointer_type tmp(static_cast<element_type*>(new NEW_T(params...)));
			_ptr.swap(tmp);
			return std::move(tmp);
		}

		inline element_type* get() {
			return _ptr.get();
		}

		inline const element_type* get() const {
			return _ptr.get();
		}

		inline smart_pointer_type release() {
			smart_pointer_type tmp;
			_ptr.swap(tmp);
			return std::move(tmp);
		}

		inline operator bool() const {
			return static_cast<bool>(_ptr);
		}

		inline element_type* operator->() {
			return _ptr.get();
		}

		inline const element_type* operator->() const {
			return _ptr.get();
		}

		inline element_type& operator*() {
			return *_ptr.get();
		}

		inline const element_type& operator*() const {
			return *_ptr.get();
		}

		inline bool operator!=(const void* other) const {
			return other == nullptr ? _ptr : this != other;
		}

		inline bool operator==(const void* other) const {
			return !operator!=(other);
		}

		inline bool operator==(const this_t& other) const {
			return _ptr == other._ptr;
		}

		inline bool operator!=(const this_t& other) const {
			return _ptr != other._ptr;
		}
	};

	template<class T, size_t BYTES = sizeof(T)>
	struct LocalPointerImplementationSelector {
		typedef _LocalPointer<T, BYTES> type;
	};

	template<class T, size_t BYTES>
	struct LocalPointerImplementationSelector<std::shared_ptr<T>, BYTES> {
		typedef _LocalPointerWrapper<std::shared_ptr<T>> type;
	};

	template<class T, size_t BYTES>
	struct LocalPointerImplementationSelector<std::unique_ptr<T>, BYTES> {
		typedef _LocalPointerWrapper<std::unique_ptr<T>> type;
	};

	template<class T, size_t BYTES = sizeof(T)>
	using LocalPointer = typename LocalPointerImplementationSelector<T, BYTES>::type;

	/*!
	*	\brief Acts like std::unique_ptr but uses local placement allocations.
	*	\details Use if you need to avoid overheads of heap memory allocation.
	*	\tparam T The type to allocate.
	*	\tparam BYTES The number of bytes to reserve to allocate. Increase from the default value if sub-classes of T are required.
	*/
	template<class T, size_t BYTES = sizeof(T)>
	class DynamicPointer {
	private:
		enum AllocationType : uint8_t
		{
			NOT_ALLOCATED = 0,
			ALLOCATED_LOCALLY = 1,
			ALLOCATED_ON_HEAP = 2
		};
		uint8_t _local_memory[BYTES];		//!< Local memory for allocations
		AllocationType _allocation_type;	//!< What is allocated in _local_memory
	public:
		typedef T element_type;
		typedef element_type* pointer;
		typedef const element_type* const_pointer;

		typedef DynamicPointer<element_type, BYTES> this_t;

		DynamicPointer(this_t&&) = delete;
		DynamicPointer(const this_t&) = delete;
		this_t& operator=(this_t&&) = delete;
		this_t& operator=(const this_t&) = delete;

		DynamicPointer() :
			_local_memory{},
			_allocation_type(NOT_ALLOCATED)
		{}

		~DynamicPointer() {
			Deallocate();
		}

		template<class ...PARAMS>
		DynamicPointer(PARAMS... params) :
			DynamicPointer()
		{
			reset<element_type>(params...);
		}

		void Deallocate() {
			if (_allocation_type == ALLOCATED_LOCALLY) {
				reinterpret_cast<element_type*>(_local_memory)->~T();
			} else if (_allocation_type == ALLOCATED_ON_HEAP) {
				(**reinterpret_cast<element_type**>(_local_memory)).~T();
			}
			_allocation_type = NOT_ALLOCATED;
		}

		template<class NEW_T = element_type>
		inline std::enable_if<std::is_default_constructible<NEW_T>::value, void>::type reset() {
			// Compile-time safety checks
			static_assert(std::is_same<element_type, NEW_T>::value || std::is_base_of<element_type, NEW_T>::value, "anvil::LocalPointer::Allocate : class is not allowed");

			Deallocate();
			if (sizeof(NEW_T) <= BYTES) {
				new(_local_memory) NEW_T();
				_allocation_type = ALLOCATED_LOCALLY;
			} else {
				new(_local_memory) element_type*(new NEW_T());
				_allocation_type = ALLOCATED_ON_HEAP;
			}
		}

		template<class NEW_T = element_type, class ...PARAMS>
		inline void reset(PARAMS... params) {
			// Compile-time safety checks
			static_assert(std::is_same<element_type, NEW_T>::value || std::is_base_of<element_type, NEW_T>::value, "anvil::LocalPointer::Allocate : class is not allowed");

			Deallocate();
			if (sizeof(NEW_T) <= BYTES) {
				new(_local_memory) NEW_T(params...);
				_allocation_type = ALLOCATED_LOCALLY;
			} else {
				new(_local_memory) element_type* (new NEW_T(params...));
				_allocation_type = ALLOCATED_ON_HEAP;
			}
		}

		inline element_type* get() {
			return _allocation_type == ALLOCATED_LOCALLY ? reinterpret_cast<element_type*>(_local_memory) :
				_allocation_type == ALLOCATED_ON_HEAP ? *reinterpret_cast<element_type**>(_local_memory) :
				nullptr;
		}

		inline const element_type* get() const {
			return _allocation_type == ALLOCATED_LOCALLY ? reinterpret_cast<element_type*>(_local_memory) :
				_allocation_type == ALLOCATED_ON_HEAP ? *reinterpret_cast<element_type**>(_local_memory) :
				nullptr;
		}

		inline void release() {
			Deallocate();
		}

		inline operator bool() const {
			return _allocation_type;
		}

		inline element_type* operator->() {
			return get();
		}

		inline const element_type* operator->() const {
			return get();
		}

		inline element_type& operator*() {
			ANVIL_DEBUG_ASSERT(_allocation_type, "anvil::DynamicPointer::get : Pointer is not allocated");
			return *get();
		}

		inline const element_type& operator*() const {
			ANVIL_DEBUG_ASSERT(_allocation_type, "anvil::DynamicPointer::get : Pointer is not allocated");
			return *get();
		}

		inline bool operator!=(const void* other) const {
			return other == nullptr ? _allocation_type != NOT_ALLOCATED : this != other;
		}

		inline bool operator==(const void* other) const {
			return !operator!=(other);
		}

		inline bool operator==(const this_t& other) const {
			return _allocation_type != NOT_ALLOCATED ? this == &other : other._allocation_type == NOT_ALLOCATED;
		}

		inline bool operator!=(const this_t& other) const {
			return !operator==(other);
		}
	};

	template<class T, size_t BYTES = sizeof(T)>
	using LocalPtr = LocalPointer<T, BYTES>;

	template<class T, size_t BYTES = sizeof(T)>
	using local_ptr = LocalPointer<T, BYTES>;

	template<class T, size_t BYTES = sizeof(T)>
	using DynamicPtr = DynamicPointer<T, BYTES>;

	template<class T, size_t BYTES = sizeof(T)>
	using dynamic_ptr = DynamicPointer<T, BYTES>;

}

#endif