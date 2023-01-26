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
		InstructionSets CheckSupportedInstructionSets_Implement() {
			//! \todo Implement
#if ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64


			int info[4];
			__cpuid(info, 0);
			int nIds = info[0];

			__cpuid(info, 0x80000000);
			unsigned nExIds = info[0];

			enum {
				EBX = 1,
				ECX = 2,
				EDX = 3
			};

			uint64_t tmp = 0u;

#define CheckCPUID(REGISTER, BIT) ((info[REGISTER] & (1 << BIT)) != 0)

			if (nIds >= 0x00000001) {
				__cpuid(info, 0x00000001);
				if (CheckCPUID(EDX, 23)) tmp |= ASM_MMX;
				if (CheckCPUID(EDX, 25)) tmp |= ASM_SSE;
				if (CheckCPUID(EDX, 26)) tmp |= ASM_SSE2;
				if (CheckCPUID(ECX, 0)) tmp |= ASM_SSE3;

				if (CheckCPUID(ECX, 9)) tmp |= ASM_SSSE3;
				if (CheckCPUID(ECX, 19)) tmp |= ASM_SSE41;
				if (CheckCPUID(ECX, 20)) tmp |= ASM_SSE42;
				if (CheckCPUID(ECX, 25)) tmp |= ASM_AES;

				if (CheckCPUID(ECX, 12)) tmp |= ASM_FMA3;
				if (CheckCPUID(ECX, 28)) tmp |= ASM_AVX;
				if (CheckCPUID(ECX, 29)) tmp |= ASM_F16C;
				//if (CheckCPUID(ECX, 30)) tmp |= ASM_RDRAND;
			}
			if (nIds >= 0x00000007) {
				__cpuid(info, 0x00000007);
				if (CheckCPUID(EBX, 5)) tmp |= ASM_AVX2;

				if (CheckCPUID(EBX, 3)) tmp |= ASM_BMI1;
				if (CheckCPUID(EBX, 8)) tmp |= ASM_BMI2;
				if (CheckCPUID(EBX, 19)) tmp |= ASM_ADX;
				if (CheckCPUID(EBX, 29)) tmp |= ASM_SHA;
				//if (CheckCPUID(ECX, 0)) tmp |= ASM_PREFETCHWT1;

				if (CheckCPUID(EBX, 16)) tmp |= ASM_AVX512F;
				if (CheckCPUID(EBX, 28)) tmp |= ASM_AVX512CD;
				if (CheckCPUID(EBX, 26)) tmp |= ASM_AVX512PF;
				if (CheckCPUID(EBX, 27)) tmp |= ASM_AVX512ER;
				if (CheckCPUID(EBX, 31)) tmp |= ASM_AVX512VL;
				if (CheckCPUID(EBX, 30)) tmp |= ASM_AVX512BW;
				if (CheckCPUID(EBX, 17)) tmp |= ASM_AVX512DQ;
				if (CheckCPUID(EBX, 21)) tmp |= ASM_AVX512IFMA;
				if (CheckCPUID(ECX, 1)) tmp |= ASM_AVX512VBMI;
			}
			if (nExIds >= 0x80000001) {
				__cpuid(info, 0x80000001);
				//if (CheckCPUID(EDX, 29)) tmp |= ASM_X64;
				if (CheckCPUID(ECX, 5)) tmp |= ASM_ABM;
				//if (CheckCPUID(ECX, 6)) tmp |= ASM_SSE4A;
				if (CheckCPUID(ECX, 16)) tmp |= ASM_FMA4;
				if (CheckCPUID(ECX, 11)) tmp |= ASM_XOP;
			}

			ANVIL_RUNTIME_ASSERT((tmp & ANVIL_MIN_INSTRUCTION_SET) == ANVIL_MIN_INSTRUCTION_SET, "anvil::CheckSupportedInstructionSets_Implement : Minimum instruction sets are not supported");

			return static_cast<InstructionSets>(tmp);
#else
			return static_cast<InstructionSets>(ANVIL_MIN_INSTRUCTION_SET);
#endif
			
		}
	}

}