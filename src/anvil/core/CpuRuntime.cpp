//Copyright 2021 Adam G. Smith
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

#include "anvil/core/CpuRuntime.hpp"

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
	#include <immintrin.h>
	#include <intrin.h>
#endif

namespace anvil {

	namespace detail {
		InstructionSets CheckSupportedInstructionSets_Implement() throw() {
			//! \todo Implement
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
			int32_t words[4];
			__cpuid(words, 0x80000001);
			uint64_t tmp;

			if ((words[2] & (1 << 5)) != 0) tmp |= ASM_BMI1;

			return static_cast<InstructionSets>(tmp | ANVIL_MIN_INSTRUCTION_SET);
#else
			return static_cast<InstructionSets>(ANVIL_MIN_INSTRUCTION_SET);
#endif
			
		}
	}

}