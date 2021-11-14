//Copyright 2019 Adam G. Smith
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

#ifndef ANVIL_CORE_CPU_RUNTIME_HPP
#define ANVIL_CORE_CPU_RUNTIME_HPP

#include <cstdint>
#include "anvil/core/Cpu.hpp"
#include "anvil/core/Keywords.hpp"

namespace anvil {
	enum CpuArchitecture : uint8_t {
		CPU_UNKNOWN = ANVIL_CPU_UNKNOWN,
		CPU_X86 = ANVIL_CPU_X86,
		CPU_X86_64 = ANVIL_CPU_X86_64,
		CPU_ARM = ANVIL_CPU_ARM,
		CPU_ARM_64 = ANVIL_CPU_ARM_64
	};

	static const constexpr CpuArchitecture CPU_ARCHITECUTE = static_cast<CpuArchitecture>(ANVIL_CPU_ARCHITECTURE);

#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
	#ifndef ANVIL_MIN_INSTRUCTION_SET
		#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
			#define ANVIL_MIN_INSTRUCTION_SET (ASM_MMX | ASM_SSE | ASM_SSE2 | ASM_SSE3 | ASM_SSSE3 | ASM_SSE41 | ASM_POPCNT)
		#else
			#define ANVIL_MIN_INSTRUCTION_SET (ASM_MMX | ASM_SSE | ASM_SSE2)
		#endif
	#endif

	enum InstructionSets : uint64_t {
		ASM_MMX =		1ull << 0ull,
		ASM_SSE =		1ull << 1ull,
		ASM_SSE2 =		1ull << 2ull,
		ASM_SSE3 =		1ull << 3ull,
		ASM_SSSE3 =		1ull << 4ull,
		ASM_SSE41 =		1ull << 5ull,
		ASM_SSE42 =		1ull << 6ull,
		ASM_AVX =		1ull << 7ull,
		ASM_AVX2 =		1ull << 8ull,
		ASM_FMA3 =		1ull << 9ull,
		ASM_AVX512F =	1ull << 10ull,
		ASM_AVX512VL =	1ull << 11ull,
		ASM_AVX512BW =	1ull << 12ull,
		
		ASM_FMA =		ASM_AVX2,
		ASM_POPCNT =	ASM_SSE42,
		ASM_ABM =		ASM_POPCNT,
		ASM_BMI2 =		ASM_AVX2,
		ASM_BMI1 =		ASM_AVX2,
		ASM_LZCNT =		ASM_BMI1
	};

	static constexpr const uint64_t ASM_MINIMUM = ANVIL_MIN_INSTRUCTION_SET; // Placeholder

	namespace detail {
		InstructionSets CheckSupportedInstructionSets_Implement() throw();
	}

	static const InstructionSets SupportedInstructionSets = detail::CheckSupportedInstructionSets_Implement();

	static ANVIL_STRONG_INLINE bool AreInstructionSetSupported(const InstructionSets instruction_sets) throw() {
		return (SupportedInstructionSets & instruction_sets) == instruction_sets;
	}

#endif

}

#endif