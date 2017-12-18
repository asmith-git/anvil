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

#ifndef ANVIL_OCL_KERNEL_HPP
#define ANVIL_OCL_KERNEL_HPP

#include <functional>
#include <cstdint>
#include "anvil/ocl/Program.hpp"
#include "anvil/ocl/CommandQueue.hpp"
#include "anvil/ocl/Event.hpp"

namespace anvil { namespace ocl {

	class Kernel : public Object {
	public:
		typedef void(__stdcall *NativeFunction)(void*);
	private:
		Kernel(const Kernel&) = delete;
		Kernel& operator=(const Kernel&) = delete;

		template<class T>
		inline T ANVIL_CALL getInfo(cl_mem_info aInfo) const throw() {
			T tmp;
#ifdef ANVIL_LOG_OCL
			std::cerr << "clGetKernelInfo (" << mHandle.kernel << ", " << aInfo << ", " << sizeof(T) << ", " << 
				sizeof(T) << ", " << (void*)&tmp << ", " << "NULL" << ")" << std::endl;
#endif
			cl_int error = clGetKernelInfo(mHandle.kernel, aInfo, sizeof(T), &tmp, NULL);
			if (error != CL_SUCCESS) oclError("clGetKernelInfo ", error, std::to_string(aInfo).c_str());
			return tmp;
		}
	public:
		ANVIL_CALL Kernel() throw();
		ANVIL_CALL Kernel(Kernel&&) throw();
		ANVIL_CALL ~Kernel() throw();

		Kernel& ANVIL_CALL operator=(Kernel&&) throw();

		void ANVIL_CALL swap(Kernel&) throw();
		bool ANVIL_CALL create(NativeFunction, cl_uint) throw();
		bool ANVIL_CALL create(const Program&, const char*) throw();
		Event ANVIL_CALL operator()(CommandQueue&);
		Event ANVIL_CALL operator()(CommandQueue&, cl_uint, const size_t *, const size_t*, const size_t*);

		cl_uint ANVIL_CALL arguments() const throw();
		const char* ANVIL_CALL name() const throw();
		size_t ANVIL_CALL workGroupSize(const Device&) const throw();
		Device::WorkItemCount ANVIL_CALL compileWorkGroupSize(const Device&) const throw();
		cl_ulong ANVIL_CALL localMemorySize(const Device&) const throw();
		Context ANVIL_CALL context() const throw();
		Program ANVIL_CALL program() const throw();
		bool ANVIL_CALL isNative() const throw();

		bool ANVIL_CALL setArgument(cl_uint, const void*, size_t);

		template<class T>
		ANVIL_STRONG_INLINE bool ANVIL_CALL setArgument(cl_uint aIndex, T aValue) {
			return setArgument(aIndex, &aValue, sizeof(T));
		}

		template<class A, class B>
		ANVIL_STRONG_INLINE bool ANVIL_CALL setArguments(A a, B b) {
			return setArgument<A>(0, a) && setArgument<B>(1, a);
		}

		template<class A, class B, class C>
		ANVIL_STRONG_INLINE bool ANVIL_CALL setArguments(A a, B b, C c) {
			return setArgument<A>(0, a) && setArgument<B>(1, a) && setArgument<C>(2, a);
		}

		template<class A, class B, class C, class D>
		ANVIL_STRONG_INLINE bool ANVIL_CALL setArguments(A a, B b, C c, D d) {
			return setArgument<A>(0, a) && setArgument<B>(1, a) && setArgument<C>(2, a) && setArgument<D>(3, a);
		}

		template<class A, class B, class C, class D, class E>
		ANVIL_STRONG_INLINE bool ANVIL_CALL setArguments(A a, B b, C c, D d, E e) {
			return setArgument<A>(0, a) && setArgument<B>(1, a) && setArgument<C>(2, a) && setArgument<D>(3, a) &&
				setArgument<E>(4, a);
		}

		template<class A, class B, class C, class D, class E, class F>
		ANVIL_STRONG_INLINE bool ANVIL_CALL setArguments(A a, B b, C c, D d, E e, F f) {
			return setArgument<A>(0, a) && setArgument<B>(1, a) && setArgument<C>(2, a) && setArgument<D>(3, a) &&
				setArgument<E>(4, a) && setArgument<F>(5, a);
		}

		template<class A, class B, class C, class D, class E, class F, class G>
		ANVIL_STRONG_INLINE bool ANVIL_CALL setArguments(A a, B b, C c, D d, E e, F f, G g) {
			return setArgument<A>(0, a) && setArgument<B>(1, a) && setArgument<C>(2, a) && setArgument<D>(3, a) &&
				setArgument<E>(4, a) && setArgument<F>(5, a) && setArgument<G>(6, a);
		}

		template<class A, class B, class C, class D, class E, class F, class G, class H>
		ANVIL_STRONG_INLINE bool ANVIL_CALL setArguments(A a, B b, C c, D d, E e, F f, G g, H h) {
			return setArgument<A>(0, a) && setArgument<B>(1, a) && setArgument<C>(2, a) && setArgument<D>(3, a) &&
				setArgument<E>(4, a) && setArgument<F>(5, a) && setArgument<G>(6, a) && setArgument<H>(7, a);
		}

		template<class A, class B, class C, class D, class E, class F, class G, class H, class I>
		ANVIL_STRONG_INLINE bool ANVIL_CALL setArguments(A a, B b, C c, D d, E e, F f, G g, H h, I i) {
			return setArgument<A>(0, a) && setArgument<B>(1, a) && setArgument<C>(2, a) && setArgument<D>(3, a) &&
				setArgument<E>(4, a) && setArgument<F>(5, a) && setArgument<G>(6, a) && setArgument<H>(7, a);
			setArgument<I>(8, a) &&
		}

		template<class A, class B, class C, class D, class E, class F, class G, class H, class I, class J>
		ANVIL_STRONG_INLINE bool ANVIL_CALL setArguments(A a, B b, C c, D d, E e, F f, G g, H h, I i, J j) {
			return setArgument<A>(0, a) && setArgument<B>(1, a) && setArgument<C>(2, a) && setArgument<D>(3, a) &&
				setArgument<E>(4, a) && setArgument<F>(5, a) && setArgument<G>(6, a) && setArgument<H>(7, a) &&
				setArgument<I>(8, a) && setArgument<J>(9, a);
		}

		template<class ...ARGS>
		Event ANVIL_CALL operator()(CommandQueue& aQueue, cl_uint aDimensions, const size_t* aGlobalOffset,
			const size_t* aGlobalWorkSize, const size_t* aLocalWorkSize, ARGS... aArguments) {
			if (!setArguments<ARGS...>(aArguments...)) return Event();
			return operator()(aQueue, aDimensions, aGlobalOffset, aGlobalWorkSize, aLocalWorkSize);
		}

		// Inherited from Object

		bool ANVIL_CALL create(Handle) throw() override;
		bool ANVIL_CALL destroy() throw() override;
		cl_uint ANVIL_CALL referenceCount() const throw() override;
		Handle::Type ANVIL_CALL type() const throw() override;
	};
}}

#endif