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

	class KernelInterface {
	public:
		virtual ANVIL_CALL ~KernelInterface() {}
		virtual Event ANVIL_CALL execute(CommandQueue&) = 0;
	};

	class Kernel : public KernelInterface {
	private:
		enum State : uint8_t {
			INITIALISED,
			SOURCE_SET,
			BUILT
		};
		cl_kernel mKernel;
		
		Kernel(const Kernel&) = delete;
		Kernel& operator=(const Kernel&) = delete;


		template<class T>
		inline T ANVIL_CALL getInfo(cl_mem_info aInfo) const throw() {
			T tmp;
			cl_int error = clGetKernelInfo(mKernel, aInfo, sizeof(T), &tmp, NULL);
			if (error != CL_SUCCESS) oclError("clGetKernelInfo ", error);
			return tmp;
		}

		cl_context context() const throw();
		cl_program program() const throw();
	public:
		ANVIL_CALL Kernel() throw();
		ANVIL_CALL Kernel(Kernel&&) throw();
		ANVIL_CALL ~Kernel() throw();

		Kernel& ANVIL_CALL operator=(Kernel&&) throw();
		ANVIL_CALL operator bool() const throw();

		void ANVIL_CALL swap(Kernel&) throw();

		bool ANVIL_CALL create(const Program&, const char*) throw();
		bool ANVIL_CALL destroy() throw();

		cl_uint arguments() const throw();
		const char* name() const throw();

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
		Event ANVIL_CALL execute(CommandQueue& aQueue, ARGS... aArguments) {
			if(! setArguments<ARGS...>(aArguments...)) return Event();
			return execute(aQueue);
		}

		template<class ...ARGS>
		Event ANVIL_CALL operator()(CommandQueue& aQueue, ARGS... aArguments) {
			return execute<ARGS...>(aQueue, aArguments..);
		}

		// Inherited from KernelInterface
		Event ANVIL_CALL execute(CommandQueue&) override;
	};

	class NativeKernel : public KernelInterface {
	private:
		static void __stdcall execute_(void*) throw();

		NativeKernel(NativeKernel&&) = delete;
		NativeKernel(NativeKernel&) = delete;
		NativeKernel& operator=(NativeKernel&&) = delete;
		NativeKernel& operator=(NativeKernel&) = delete;
	protected:
		cl_context mContext;

		virtual void ANVIL_CALL onExecute() throw() = 0;
	public:
		ANVIL_CALL NativeKernel(Context&);
		virtual ANVIL_CALL ~NativeKernel();

		// Inherited from KernelInterface
		Event ANVIL_CALL execute(CommandQueue&) override;
	};
}}

#endif