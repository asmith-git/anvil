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

	#define ANVIL_ASM_MMX (1ull << 0ull)
	#define ANVIL_ASM_SSE (1ull << 1ull)
	#define ANVIL_ASM_SSE2 (1ull << 2ull)
	#define ANVIL_ASM_SSE3 (1ull << 3ull)
	#define ANVIL_ASM_SSSE3 (1ull << 4ull)
	#define ANVIL_ASM_SSE41 (1ull << 5ull)
	#define ANVIL_ASM_SSE42 (1ull << 6ull)
	#define ANVIL_ASM_AVX (1ull << 7ull)
	#define ANVIL_ASM_AVX2 (1ull << 8ull)
	#define ANVIL_ASM_FMA3 (1ull << 9ull)
	#define ANVIL_ASM_AVX512F (1ull << 10ull)
	#define ANVIL_ASM_AVX512VL (1ull << 11ull)
	#define ANVIL_ASM_AVX512BW (1ull << 12ull)
	#define ANVIL_ASM_AVX512CD (1ull << 13ull)
	#define ANVIL_ASM_AVX512PF (1ull << 14ull)
	#define ANVIL_ASM_AVX512ER (1ull << 15ull)
	#define ANVIL_ASM_AVX512DQ (1ull << 16ull)
	#define ANVIL_ASM_AVX512IFMA (1ull << 17ull)
	#define ANVIL_ASM_AVX512VBMI (1ull << 18ull)

	#define ANVIL_ASM_POPCNT (1ull << 54ull)
	#define ANVIL_ASM_F16C (1ull << 55ull)
	#define ANVIL_ASM_AES (1ull << 56ull)
	#define ANVIL_ASM_SHA (1ull << 57ull)
	#define ANVIL_ASM_ADX (1ull << 58ull)
	#define ANVIL_ASM_XOP (1ull << 59ull)
	#define ANVIL_ASM_FMA4 (1ull << 60ull)
	#define ANVIL_ASM_ABM (1ull << 61ull)
	#define ANVIL_ASM_BMI1 (1ull << 62ull)
	#define ANVIL_ASM_BMI2 (1ull << 63ull)

	enum InstructionSets : uint64_t {
		ASM_MMX =			ANVIL_ASM_MMX,
		ASM_SSE =			ANVIL_ASM_SSE,
		ASM_SSE2 =			ANVIL_ASM_SSE2,
		ASM_SSE3 =			ANVIL_ASM_SSE3,
		ASM_SSSE3 =			ANVIL_ASM_SSSE3,
		ASM_SSE41 =			ANVIL_ASM_SSE41,
		ASM_SSE42 =			ANVIL_ASM_SSE42,
		ASM_AVX =			ANVIL_ASM_AVX,
		ASM_AVX2 =			ANVIL_ASM_AVX2,
		ASM_FMA3 =			ANVIL_ASM_FMA3,
		ASM_AVX512F =		ANVIL_ASM_AVX512F,
		ASM_AVX512VL =		ANVIL_ASM_AVX512VL,
		ASM_AVX512BW =		ANVIL_ASM_AVX512BW,
		ASM_AVX512CD =		ANVIL_ASM_AVX512CD,
		ASM_AVX512PF =		ANVIL_ASM_AVX512PF,
		ASM_AVX512ER =		ANVIL_ASM_AVX512ER,
		ASM_AVX512DQ =		ANVIL_ASM_AVX512DQ,
		ASM_AVX512IFMA =	ANVIL_ASM_AVX512IFMA,
		ASM_AVX512VBMI =	ANVIL_ASM_AVX512VBMI,

		ASM_POPCNT =		ANVIL_ASM_POPCNT,
		ASM_F16C =			ANVIL_ASM_F16C,
		ASM_AES =			ANVIL_ASM_AES,
		ASM_SHA =			ANVIL_ASM_SHA,
		ASM_ADX =			ANVIL_ASM_ADX,
		ASM_XOP =			ANVIL_ASM_XOP,
		ASM_FMA4 =			ANVIL_ASM_FMA4,
		ASM_ABM =			ANVIL_ASM_ABM,
		ASM_BMI1 =			ANVIL_ASM_BMI1,
		ASM_BMI2 =			ANVIL_ASM_BMI2
	};
			
	#ifndef ANVIL_MIN_INSTRUCTION_SET
		#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
			#define ANVIL_MIN_INSTRUCTION_SET (ANVIL_ASM_MMX | ANVIL_ASM_SSE | ANVIL_ASM_SSE2 | ANVIL_ASM_SSE3 | ANVIL_ASM_SSSE3 | ANVIL_ASM_SSE41 | ANVIL_ASM_POPCNT)
		#else
			#define ANVIL_MIN_INSTRUCTION_SET (ANVIL_ASM_MMX | ANVIL_ASM_SSE | ANVIL_ASM_SSE2)
		#endif
	#endif

	namespace detail {
		ANVIL_DLL_EXPORT InstructionSets CheckSupportedInstructionSets_Implement();
	}

	static const InstructionSets SupportedInstructionSets = detail::CheckSupportedInstructionSets_Implement();

	static ANVIL_STRONG_INLINE bool AreInstructionSetSupported(const InstructionSets instruction_sets) throw() {
		return (SupportedInstructionSets & instruction_sets) == instruction_sets;
	}

#endif

}

#endif