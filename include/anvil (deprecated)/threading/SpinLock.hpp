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

#ifndef ANVIL_THREADING_THEAD_POOL_HPP
#define ANVIL_THREADING_THEAD_POOL_HPP

#include <atomic>
#include "anvil/core/Keywords.hpp"

namespace anvil {
	class SpinLock {
	private:
		std::atomic_flag lock_;
	public:
		ANVIL_STRONG_INLINE bool ANVIL_CALL try_lock() throw() {
			return !lock_.test_and_set(std::memory_order_acquire);
		}

		ANVIL_STRONG_INLINE int ANVIL_CALL lock() throw() {
			int count = 0;
			while (lock_.test_and_set(std::memory_order_acquire)) ++count;
			return count;
		}

		ANVIL_STRONG_INLINE void ANVIL_CALL unlock() throw() {
			lock_.clear(std::memory_order_release);
		}
	};
}

#endif