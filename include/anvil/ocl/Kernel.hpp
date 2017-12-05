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

#include <cstdint>
#include "anvil/ocl/Program.hpp"
#include "anvil/ocl/CommandQueue.hpp"
#include "anvil/ocl/Event.hpp"

namespace anvil { namespace ocl {

	class Kernel {
	private:
		enum State : uint8_t {
			INITIALISED,
			SOURCE_SET,
			BUILT
		};
		const Program& mProgram;
		cl_kernel mKernel;
		
		Kernel(Kernel&&) = delete;
		Kernel(const Kernel&) = delete;
		Kernel& operator=(Kernel&&) = delete;
		Kernel& operator=(const Kernel&) = delete;
	public:
		ANVIL_CALL Kernel(const Program&, const char*);
		ANVIL_CALL ~Kernel();

		void ANVIL_CALL setArg(cl_uint, const void*, size_t);
		Event ANVIL_CALL execute(CommandQueue&);

		template<class T>
		ANVIL_STRONG_INLINE void ANVIL_CALL setArg(cl_uint aIndex, T aValue) {
			setArg(aIndex, &aValue, sizeof(T));
		}

		template<class A, class B>
		ANVIL_STRONG_INLINE void ANVIL_CALL setArgs(A a, B b) {
			setArg<A>(0, a); setArg<B>(1, a);
		}

		template<class A, class B, class C>
		ANVIL_STRONG_INLINE void ANVIL_CALL setArgs(A a, B b, C c) {
			setArg<A>(0, a); setArg<B>(1, a); setArg<C>(2, a);
		}

		template<class A, class B, class C, class D>
		ANVIL_STRONG_INLINE void ANVIL_CALL setArgs(A a, B b, C c, D d) {
			setArg<A>(0, a); setArg<B>(1, a); setArg<C>(2, a); setArg<D>(3, a);
		}

		template<class A, class B, class C, class D, class E>
		ANVIL_STRONG_INLINE void ANVIL_CALL setArgs(A a, B b, C c, D d, E e) {
			setArg<A>(0, a); setArg<B>(1, a); setArg<C>(2, a); setArg<D>(3, a);
			setArg<E>(4, a);
		}

		template<class A, class B, class C, class D, class E, class F>
		ANVIL_STRONG_INLINE void ANVIL_CALL setArgs(A a, B b, C c, D d, E e, F f) {
			setArg<A>(0, a); setArg<B>(1, a); setArg<C>(2, a); setArg<D>(3, a);
			setArg<E>(4, a); setArg<F>(5, a);
		}

		template<class A, class B, class C, class D, class E, class F, class G>
		ANVIL_STRONG_INLINE void ANVIL_CALL setArgs(A a, B b, C c, D d, E e, F f, G g) {
			setArg<A>(0, a); setArg<B>(1, a); setArg<C>(2, a); setArg<D>(3, a);
			setArg<E>(4, a); setArg<F>(5, a); setArg<G>(6, a);
		}

		template<class A, class B, class C, class D, class E, class F, class G, class H>
		ANVIL_STRONG_INLINE void ANVIL_CALL setArgs(A a, B b, C c, D d, E e, F f, G g, H h) {
			setArg<A>(0, a); setArg<B>(1, a); setArg<C>(2, a); setArg<D>(3, a);
			setArg<E>(4, a); setArg<F>(5, a); setArg<G>(6, a); setArg<H>(7, a);
		}

		template<class A, class B, class C, class D, class E, class F, class G, class H, class I>
		ANVIL_STRONG_INLINE void ANVIL_CALL setArgs(A a, B b, C c, D d, E e, F f, G g, H h, I i) {
			setArg<A>(0, a); setArg<B>(1, a); setArg<C>(2, a); setArg<D>(3, a);
			setArg<E>(4, a); setArg<F>(5, a); setArg<G>(6, a); setArg<H>(7, a);
			setArg<I>(8, a);
		}

		template<class A, class B, class C, class D, class E, class F, class G, class H, class I, class J>
		ANVIL_STRONG_INLINE void ANVIL_CALL setArgs(A a, B b, C c, D d, E e, F f, G g, H h, I i, J j) {
			setArg<A>(0, a); setArg<B>(1, a); setArg<C>(2, a); setArg<D>(3, a);
			setArg<E>(4, a); setArg<F>(5, a); setArg<G>(6, a); setArg<H>(7, a);
			setArg<I>(8, a); setArg<J>(9, a);
		}

		template<class ...ARGS>
		Event execute(CommandQueue& aQueue, ARGS... aArgs) {
			setArgs<ARGS...>(aArgs...);
			return execute(aQueue);
		}
	};
}}

#endif