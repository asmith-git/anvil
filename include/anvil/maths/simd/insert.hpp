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

// -- f64 --

#define _simd_f64x2_extract_x1_safe(X,I) (reinterpret_cast<const _simd_f64x2*>(&X)[I])
#ifdef _simd_f64x2_extract_x1_
#define _simd_f64x2_extract_x1(X,I) _simd_f64x2_extract_x1_(X,I)
#define _simd_f64x2__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_extract_x1_instruction_set>()
#else
#define _simd_f64x2_extract_x1(X,I) _simd_f64x2_extract_x1_safe(X,I)
#define _simd_f64x2__extract_x1_enable() true
#endif _simd_f64x2_extract_x1_

#define _simd_f64x2_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_f64x2*>(&X)[I] = Y)
#ifdef _simd_f64x2_insert_x1_
#define _simd_f64x2_insert_x1(X,I,Y) _simd_f64x2_insert_x1_(X,I,Y)
#define _simd_f64x2__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_insert_x1_instruction_set>()
#else
#define _simd_f64x2_insert_x1(X,I,Y) _simd_f64x2_insert_x1_safe(X,I,Y)
#define _simd_f64x2__insert_x1_enable() true
#endif _simd_f64x2_insert_x1_

#define _simd_f64x2_extract_x4_safe(X,I) _simd_f64x2_insert_x2_safe(_simd_f64x2_fill_undefined_safe(),0,X)
#ifdef _simd_f64x2_extract_x4_
#define _simd_f64x2_extract_x4(X,I) _simd_f64x2_extract_x4_(X,I)
#define _simd_f64x2__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_extract_x4_instruction_set>()
#else
#define _simd_f64x2_extract_x4(X,I) _simd_f64x2_extract_x4_safe(X,I)
#define _simd_f64x2__extract_x4_enable() true
#endif _simd_f64x2_extract_x4_

#define _simd_f64x2_insert_x4_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_f64x1) * 4)
#ifdef _simd_f64x2_insert_x4_
#define _simd_f64x2_insert_x4(X,I,Y) _simd_f64x2_insert_x4_(X,I,Y)
#define _simd_f64x2__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_insert_x4_instruction_set>()
#else
#define _simd_f64x2_insert_x4(X,I,Y) _simd_f64x2_insert_x4_safe(X,I,Y)
#define _simd_f64x2__insert_x4_enable() true
#endif _simd_f64x2_insert_x4_

#define _simd_f64x2_extract_x8_safe(X,I) _simd_f64x2_insert_x2_safe(_simd_f64x2_fill_undefined_safe(),0,X)
#ifdef _simd_f64x2_extract_x8_
#define _simd_f64x2_extract_x8(X,I) _simd_f64x2_extract_x8_(X,I)
#define _simd_f64x2__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_extract_x8_instruction_set>()
#else
#define _simd_f64x2_extract_x8(X,I) _simd_f64x2_extract_x8_safe(X,I)
#define _simd_f64x2__extract_x8_enable() true
#endif _simd_f64x2_extract_x8_

#define _simd_f64x2_insert_x8_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_f64x1) * 8)
#ifdef _simd_f64x2_insert_x8_
#define _simd_f64x2_insert_x8(X,I,Y) _simd_f64x2_insert_x8_(X,I,Y)
#define _simd_f64x2__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_insert_x8_instruction_set>()
#else
#define _simd_f64x2_insert_x8(X,I,Y) _simd_f64x2_insert_x8_safe(X,I,Y)
#define _simd_f64x2__insert_x8_enable() true
#endif _simd_f64x2_insert_x8_

#define _simd_f64x2_extract_x16_safe(X,I) _simd_f64x2_insert_x2_safe(_simd_f64x2_fill_undefined_safe(),0,X)
#ifdef _simd_f64x2_extract_x16_
#define _simd_f64x2_extract_x16(X,I) _simd_f64x2_extract_x16_(X,I)
#define _simd_f64x2__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_extract_x16_instruction_set>()
#else
#define _simd_f64x2_extract_x16(X,I) _simd_f64x2_extract_x16_safe(X,I)
#define _simd_f64x2__extract_x16_enable() true
#endif _simd_f64x2_extract_x16_

#define _simd_f64x2_insert_x16_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_f64x1) * 16)
#ifdef _simd_f64x2_insert_x16_
#define _simd_f64x2_insert_x16(X,I,Y) _simd_f64x2_insert_x16_(X,I,Y)
#define _simd_f64x2__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_insert_x16_instruction_set>()
#else
#define _simd_f64x2_insert_x16(X,I,Y) _simd_f64x2_insert_x16_safe(X,I,Y)
#define _simd_f64x2__insert_x16_enable() true
#endif _simd_f64x2_insert_x16_

#define _simd_f64x2_extract_x32_safe(X,I) _simd_f64x2_insert_x2_safe(_simd_f64x2_fill_undefined_safe(),0,X)
#ifdef _simd_f64x2_extract_x32_
#define _simd_f64x2_extract_x32(X,I) _simd_f64x2_extract_x32_(X,I)
#define _simd_f64x2__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_extract_x32_instruction_set>()
#else
#define _simd_f64x2_extract_x32(X,I) _simd_f64x2_extract_x32_safe(X,I)
#define _simd_f64x2__extract_x32_enable() true
#endif _simd_f64x2_extract_x32_

#define _simd_f64x2_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_f64x1) * 32)
#ifdef _simd_f64x2_insert_x32_
#define _simd_f64x2_insert_x32(X,I,Y) _simd_f64x2_insert_x32_(X,I,Y)
#define _simd_f64x2__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_insert_x32_instruction_set>()
#else
#define _simd_f64x2_insert_x32(X,I,Y) _simd_f64x2_insert_x32_safe(X,I,Y)
#define _simd_f64x2__insert_x32_enable() true
#endif _simd_f64x2_insert_x32_

#define _simd_f64x2_extract_x64_safe(X,I) _simd_f64x2_insert_x2_safe(_simd_f64x2_fill_undefined_safe(),0,X)
#ifdef _simd_f64x2_extract_x64_
#define _simd_f64x2_extract_x64(X,I) _simd_f64x2_extract_x64_(X,I)
#define _simd_f64x2__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_extract_x64_instruction_set>()
#else
#define _simd_f64x2_extract_x64(X,I) _simd_f64x2_extract_x64_safe(X,I)
#define _simd_f64x2__extract_x64_enable() true
#endif _simd_f64x2_extract_x64_

#define _simd_f64x2_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_f64x1) * 64)
#ifdef _simd_f64x2_insert_x64_
#define _simd_f64x2_insert_x64(X,I,Y) _simd_f64x2_insert_x64_(X,I,Y)
#define _simd_f64x2__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_insert_x64_instruction_set>()
#else
#define _simd_f64x2_insert_x64(X,I,Y) _simd_f64x2_insert_x64_safe(X,I,Y)
#define _simd_f64x2__insert_x64_enable() true
#endif _simd_f64x2_insert_x64_

#define _simd_f64x2_extract_safe(X,I) _simd_f64x2_extract_x1_safe(X,I)
#define _simd_f64x2_extract(X,I) _simd_f64x2_extract_x1(X,I)
#define _simd_f64x2_extract_enable() _simd_f64x2_extract_x1_enable()

#define _simd_f64x2_insert_safe(X,I,Y) _simd_f64x2_insert_x1_safe(X,I,Y)
#define _simd_f64x2_insert(X,I,Y) _simd_f64x2_insert_x1(X,I,Y)
#define _simd_f64x2_insert_enable() _simd_f64x2_insert_x1_enable()

//#ifndef _simd_f64x2_splitlo
//	#define _simd_f64x2_splitlo(X) _simd_f64x1_extract_x1(X,0)
//	#define _simd_f64x2_splitlo_enable() _simd_f64x1_extract_x1_enable()
//#endif

//#ifndef _simd_f64x2_splithi
//	#define _simd_f64x2_splithi(X) _simd_f64x1_extract_x1(X,1)
//	#define _simd_f64x2_splithi_enable() _simd_f64x1_extract_x1_enable()
//#endif

//#ifndef _simd_f64x2_combine
//	#define _simd_f64x2_combine(X,Y) _simd_f64x2_insert_x1(_simd_f64x2_insert_x1(_simd_f64x2_fill_undefined(), 0, X), 1, Y)
//	#define _simd_f64x2_combine_enable() (_simd_f64x2_insert_x1_enable() && _simd_f64x2_fill_undefined_enable())
//#endif

#define _simd_f64x4_extract_x1_safe(X,I) (reinterpret_cast<const _simd_f64x4*>(&X)[I])
#ifdef _simd_f64x4_extract_x1_
#define _simd_f64x4_extract_x1(X,I) _simd_f64x4_extract_x1_(X,I)
#define _simd_f64x4__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_extract_x1_instruction_set>()
#else
#define _simd_f64x4_extract_x1(X,I) _simd_f64x4_extract_x1_safe(X,I)
#define _simd_f64x4__extract_x1_enable() true
#endif _simd_f64x4_extract_x1_

#define _simd_f64x4_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_f64x4*>(&X)[I] = Y)
#ifdef _simd_f64x4_insert_x1_
#define _simd_f64x4_insert_x1(X,I,Y) _simd_f64x4_insert_x1_(X,I,Y)
#define _simd_f64x4__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_insert_x1_instruction_set>()
#else
#define _simd_f64x4_insert_x1(X,I,Y) _simd_f64x4_insert_x1_safe(X,I,Y)
#define _simd_f64x4__insert_x1_enable() true
#endif _simd_f64x4_insert_x1_

#define _simd_f64x4_extract_x2_safe(X,I) (reinterpret_cast<const _simd_f64x4*>(&X)[I])
#ifdef _simd_f64x4_extract_x2_
#define _simd_f64x4_extract_x2(X,I) _simd_f64x4_extract_x2_(X,I)
#define _simd_f64x4__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_extract_x2_instruction_set>()
#else
#define _simd_f64x4_extract_x2(X,I) _simd_f64x4_extract_x2_safe(X,I)
#define _simd_f64x4__extract_x2_enable() true
#endif _simd_f64x4_extract_x2_

#define _simd_f64x4_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_f64x4*>(&X)[I] = Y)
#ifdef _simd_f64x4_insert_x2_
#define _simd_f64x4_insert_x2(X,I,Y) _simd_f64x4_insert_x2_(X,I,Y)
#define _simd_f64x4__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_insert_x2_instruction_set>()
#else
#define _simd_f64x4_insert_x2(X,I,Y) _simd_f64x4_insert_x2_safe(X,I,Y)
#define _simd_f64x4__insert_x2_enable() true
#endif _simd_f64x4_insert_x2_

#define _simd_f64x4_extract_x8_safe(X,I) _simd_f64x4_insert_x4_safe(_simd_f64x4_fill_undefined_safe(),0,X)
#ifdef _simd_f64x4_extract_x8_
#define _simd_f64x4_extract_x8(X,I) _simd_f64x4_extract_x8_(X,I)
#define _simd_f64x4__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_extract_x8_instruction_set>()
#else
#define _simd_f64x4_extract_x8(X,I) _simd_f64x4_extract_x8_safe(X,I)
#define _simd_f64x4__extract_x8_enable() true
#endif _simd_f64x4_extract_x8_

#define _simd_f64x4_insert_x8_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_f64x1) * 8)
#ifdef _simd_f64x4_insert_x8_
#define _simd_f64x4_insert_x8(X,I,Y) _simd_f64x4_insert_x8_(X,I,Y)
#define _simd_f64x4__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_insert_x8_instruction_set>()
#else
#define _simd_f64x4_insert_x8(X,I,Y) _simd_f64x4_insert_x8_safe(X,I,Y)
#define _simd_f64x4__insert_x8_enable() true
#endif _simd_f64x4_insert_x8_

#define _simd_f64x4_extract_x16_safe(X,I) _simd_f64x4_insert_x4_safe(_simd_f64x4_fill_undefined_safe(),0,X)
#ifdef _simd_f64x4_extract_x16_
#define _simd_f64x4_extract_x16(X,I) _simd_f64x4_extract_x16_(X,I)
#define _simd_f64x4__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_extract_x16_instruction_set>()
#else
#define _simd_f64x4_extract_x16(X,I) _simd_f64x4_extract_x16_safe(X,I)
#define _simd_f64x4__extract_x16_enable() true
#endif _simd_f64x4_extract_x16_

#define _simd_f64x4_insert_x16_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_f64x1) * 16)
#ifdef _simd_f64x4_insert_x16_
#define _simd_f64x4_insert_x16(X,I,Y) _simd_f64x4_insert_x16_(X,I,Y)
#define _simd_f64x4__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_insert_x16_instruction_set>()
#else
#define _simd_f64x4_insert_x16(X,I,Y) _simd_f64x4_insert_x16_safe(X,I,Y)
#define _simd_f64x4__insert_x16_enable() true
#endif _simd_f64x4_insert_x16_

#define _simd_f64x4_extract_x32_safe(X,I) _simd_f64x4_insert_x4_safe(_simd_f64x4_fill_undefined_safe(),0,X)
#ifdef _simd_f64x4_extract_x32_
#define _simd_f64x4_extract_x32(X,I) _simd_f64x4_extract_x32_(X,I)
#define _simd_f64x4__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_extract_x32_instruction_set>()
#else
#define _simd_f64x4_extract_x32(X,I) _simd_f64x4_extract_x32_safe(X,I)
#define _simd_f64x4__extract_x32_enable() true
#endif _simd_f64x4_extract_x32_

#define _simd_f64x4_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_f64x1) * 32)
#ifdef _simd_f64x4_insert_x32_
#define _simd_f64x4_insert_x32(X,I,Y) _simd_f64x4_insert_x32_(X,I,Y)
#define _simd_f64x4__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_insert_x32_instruction_set>()
#else
#define _simd_f64x4_insert_x32(X,I,Y) _simd_f64x4_insert_x32_safe(X,I,Y)
#define _simd_f64x4__insert_x32_enable() true
#endif _simd_f64x4_insert_x32_

#define _simd_f64x4_extract_x64_safe(X,I) _simd_f64x4_insert_x4_safe(_simd_f64x4_fill_undefined_safe(),0,X)
#ifdef _simd_f64x4_extract_x64_
#define _simd_f64x4_extract_x64(X,I) _simd_f64x4_extract_x64_(X,I)
#define _simd_f64x4__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_extract_x64_instruction_set>()
#else
#define _simd_f64x4_extract_x64(X,I) _simd_f64x4_extract_x64_safe(X,I)
#define _simd_f64x4__extract_x64_enable() true
#endif _simd_f64x4_extract_x64_

#define _simd_f64x4_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_f64x1) * 64)
#ifdef _simd_f64x4_insert_x64_
#define _simd_f64x4_insert_x64(X,I,Y) _simd_f64x4_insert_x64_(X,I,Y)
#define _simd_f64x4__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_insert_x64_instruction_set>()
#else
#define _simd_f64x4_insert_x64(X,I,Y) _simd_f64x4_insert_x64_safe(X,I,Y)
#define _simd_f64x4__insert_x64_enable() true
#endif _simd_f64x4_insert_x64_

#define _simd_f64x4_extract_safe(X,I) _simd_f64x4_extract_x1_safe(X,I)
#define _simd_f64x4_extract(X,I) _simd_f64x4_extract_x1(X,I)
#define _simd_f64x4_extract_enable() _simd_f64x4_extract_x1_enable()

#define _simd_f64x4_insert_safe(X,I,Y) _simd_f64x4_insert_x1_safe(X,I,Y)
#define _simd_f64x4_insert(X,I,Y) _simd_f64x4_insert_x1(X,I,Y)
#define _simd_f64x4_insert_enable() _simd_f64x4_insert_x1_enable()

//#ifndef _simd_f64x4_splitlo
//	#define _simd_f64x4_splitlo(X) _simd_f64x2_extract_x2(X,0)
//	#define _simd_f64x4_splitlo_enable() _simd_f64x2_extract_x2_enable()
//#endif

//#ifndef _simd_f64x4_splithi
//	#define _simd_f64x4_splithi(X) _simd_f64x2_extract_x2(X,1)
//	#define _simd_f64x4_splithi_enable() _simd_f64x2_extract_x2_enable()
//#endif

//#ifndef _simd_f64x4_combine
//	#define _simd_f64x4_combine(X,Y) _simd_f64x4_insert_x2(_simd_f64x4_insert_x2(_simd_f64x4_fill_undefined(), 0, X), 1, Y)
//	#define _simd_f64x4_combine_enable() (_simd_f64x4_insert_x2_enable() && _simd_f64x4_fill_undefined_enable())
//#endif

#define _simd_f64x8_extract_x1_safe(X,I) (reinterpret_cast<const _simd_f64x8*>(&X)[I])
#ifdef _simd_f64x8_extract_x1_
#define _simd_f64x8_extract_x1(X,I) _simd_f64x8_extract_x1_(X,I)
#define _simd_f64x8__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_extract_x1_instruction_set>()
#else
#define _simd_f64x8_extract_x1(X,I) _simd_f64x8_extract_x1_safe(X,I)
#define _simd_f64x8__extract_x1_enable() true
#endif _simd_f64x8_extract_x1_

#define _simd_f64x8_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_f64x8*>(&X)[I] = Y)
#ifdef _simd_f64x8_insert_x1_
#define _simd_f64x8_insert_x1(X,I,Y) _simd_f64x8_insert_x1_(X,I,Y)
#define _simd_f64x8__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_insert_x1_instruction_set>()
#else
#define _simd_f64x8_insert_x1(X,I,Y) _simd_f64x8_insert_x1_safe(X,I,Y)
#define _simd_f64x8__insert_x1_enable() true
#endif _simd_f64x8_insert_x1_

#define _simd_f64x8_extract_x2_safe(X,I) (reinterpret_cast<const _simd_f64x8*>(&X)[I])
#ifdef _simd_f64x8_extract_x2_
#define _simd_f64x8_extract_x2(X,I) _simd_f64x8_extract_x2_(X,I)
#define _simd_f64x8__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_extract_x2_instruction_set>()
#else
#define _simd_f64x8_extract_x2(X,I) _simd_f64x8_extract_x2_safe(X,I)
#define _simd_f64x8__extract_x2_enable() true
#endif _simd_f64x8_extract_x2_

#define _simd_f64x8_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_f64x8*>(&X)[I] = Y)
#ifdef _simd_f64x8_insert_x2_
#define _simd_f64x8_insert_x2(X,I,Y) _simd_f64x8_insert_x2_(X,I,Y)
#define _simd_f64x8__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_insert_x2_instruction_set>()
#else
#define _simd_f64x8_insert_x2(X,I,Y) _simd_f64x8_insert_x2_safe(X,I,Y)
#define _simd_f64x8__insert_x2_enable() true
#endif _simd_f64x8_insert_x2_

#define _simd_f64x8_extract_x4_safe(X,I) (reinterpret_cast<const _simd_f64x8*>(&X)[I])
#ifdef _simd_f64x8_extract_x4_
#define _simd_f64x8_extract_x4(X,I) _simd_f64x8_extract_x4_(X,I)
#define _simd_f64x8__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_extract_x4_instruction_set>()
#else
#define _simd_f64x8_extract_x4(X,I) _simd_f64x8_extract_x4_safe(X,I)
#define _simd_f64x8__extract_x4_enable() true
#endif _simd_f64x8_extract_x4_

#define _simd_f64x8_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_f64x8*>(&X)[I] = Y)
#ifdef _simd_f64x8_insert_x4_
#define _simd_f64x8_insert_x4(X,I,Y) _simd_f64x8_insert_x4_(X,I,Y)
#define _simd_f64x8__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_insert_x4_instruction_set>()
#else
#define _simd_f64x8_insert_x4(X,I,Y) _simd_f64x8_insert_x4_safe(X,I,Y)
#define _simd_f64x8__insert_x4_enable() true
#endif _simd_f64x8_insert_x4_

#define _simd_f64x8_extract_x16_safe(X,I) _simd_f64x8_insert_x8_safe(_simd_f64x8_fill_undefined_safe(),0,X)
#ifdef _simd_f64x8_extract_x16_
#define _simd_f64x8_extract_x16(X,I) _simd_f64x8_extract_x16_(X,I)
#define _simd_f64x8__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_extract_x16_instruction_set>()
#else
#define _simd_f64x8_extract_x16(X,I) _simd_f64x8_extract_x16_safe(X,I)
#define _simd_f64x8__extract_x16_enable() true
#endif _simd_f64x8_extract_x16_

#define _simd_f64x8_insert_x16_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_f64x1) * 16)
#ifdef _simd_f64x8_insert_x16_
#define _simd_f64x8_insert_x16(X,I,Y) _simd_f64x8_insert_x16_(X,I,Y)
#define _simd_f64x8__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_insert_x16_instruction_set>()
#else
#define _simd_f64x8_insert_x16(X,I,Y) _simd_f64x8_insert_x16_safe(X,I,Y)
#define _simd_f64x8__insert_x16_enable() true
#endif _simd_f64x8_insert_x16_

#define _simd_f64x8_extract_x32_safe(X,I) _simd_f64x8_insert_x8_safe(_simd_f64x8_fill_undefined_safe(),0,X)
#ifdef _simd_f64x8_extract_x32_
#define _simd_f64x8_extract_x32(X,I) _simd_f64x8_extract_x32_(X,I)
#define _simd_f64x8__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_extract_x32_instruction_set>()
#else
#define _simd_f64x8_extract_x32(X,I) _simd_f64x8_extract_x32_safe(X,I)
#define _simd_f64x8__extract_x32_enable() true
#endif _simd_f64x8_extract_x32_

#define _simd_f64x8_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_f64x1) * 32)
#ifdef _simd_f64x8_insert_x32_
#define _simd_f64x8_insert_x32(X,I,Y) _simd_f64x8_insert_x32_(X,I,Y)
#define _simd_f64x8__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_insert_x32_instruction_set>()
#else
#define _simd_f64x8_insert_x32(X,I,Y) _simd_f64x8_insert_x32_safe(X,I,Y)
#define _simd_f64x8__insert_x32_enable() true
#endif _simd_f64x8_insert_x32_

#define _simd_f64x8_extract_x64_safe(X,I) _simd_f64x8_insert_x8_safe(_simd_f64x8_fill_undefined_safe(),0,X)
#ifdef _simd_f64x8_extract_x64_
#define _simd_f64x8_extract_x64(X,I) _simd_f64x8_extract_x64_(X,I)
#define _simd_f64x8__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_extract_x64_instruction_set>()
#else
#define _simd_f64x8_extract_x64(X,I) _simd_f64x8_extract_x64_safe(X,I)
#define _simd_f64x8__extract_x64_enable() true
#endif _simd_f64x8_extract_x64_

#define _simd_f64x8_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_f64x1) * 64)
#ifdef _simd_f64x8_insert_x64_
#define _simd_f64x8_insert_x64(X,I,Y) _simd_f64x8_insert_x64_(X,I,Y)
#define _simd_f64x8__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_insert_x64_instruction_set>()
#else
#define _simd_f64x8_insert_x64(X,I,Y) _simd_f64x8_insert_x64_safe(X,I,Y)
#define _simd_f64x8__insert_x64_enable() true
#endif _simd_f64x8_insert_x64_

#define _simd_f64x8_extract_safe(X,I) _simd_f64x8_extract_x1_safe(X,I)
#define _simd_f64x8_extract(X,I) _simd_f64x8_extract_x1(X,I)
#define _simd_f64x8_extract_enable() _simd_f64x8_extract_x1_enable()

#define _simd_f64x8_insert_safe(X,I,Y) _simd_f64x8_insert_x1_safe(X,I,Y)
#define _simd_f64x8_insert(X,I,Y) _simd_f64x8_insert_x1(X,I,Y)
#define _simd_f64x8_insert_enable() _simd_f64x8_insert_x1_enable()

//#ifndef _simd_f64x8_splitlo
//	#define _simd_f64x8_splitlo(X) _simd_f64x4_extract_x4(X,0)
//	#define _simd_f64x8_splitlo_enable() _simd_f64x4_extract_x4_enable()
//#endif

//#ifndef _simd_f64x8_splithi
//	#define _simd_f64x8_splithi(X) _simd_f64x4_extract_x4(X,1)
//	#define _simd_f64x8_splithi_enable() _simd_f64x4_extract_x4_enable()
//#endif

//#ifndef _simd_f64x8_combine
//	#define _simd_f64x8_combine(X,Y) _simd_f64x8_insert_x4(_simd_f64x8_insert_x4(_simd_f64x8_fill_undefined(), 0, X), 1, Y)
//	#define _simd_f64x8_combine_enable() (_simd_f64x8_insert_x4_enable() && _simd_f64x8_fill_undefined_enable())
//#endif

#define _simd_f64x16_extract_x1_safe(X,I) (reinterpret_cast<const _simd_f64x16*>(&X)[I])
#ifdef _simd_f64x16_extract_x1_
#define _simd_f64x16_extract_x1(X,I) _simd_f64x16_extract_x1_(X,I)
#define _simd_f64x16__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_extract_x1_instruction_set>()
#else
#define _simd_f64x16_extract_x1(X,I) _simd_f64x16_extract_x1_safe(X,I)
#define _simd_f64x16__extract_x1_enable() true
#endif _simd_f64x16_extract_x1_

#define _simd_f64x16_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_f64x16*>(&X)[I] = Y)
#ifdef _simd_f64x16_insert_x1_
#define _simd_f64x16_insert_x1(X,I,Y) _simd_f64x16_insert_x1_(X,I,Y)
#define _simd_f64x16__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_insert_x1_instruction_set>()
#else
#define _simd_f64x16_insert_x1(X,I,Y) _simd_f64x16_insert_x1_safe(X,I,Y)
#define _simd_f64x16__insert_x1_enable() true
#endif _simd_f64x16_insert_x1_

#define _simd_f64x16_extract_x2_safe(X,I) (reinterpret_cast<const _simd_f64x16*>(&X)[I])
#ifdef _simd_f64x16_extract_x2_
#define _simd_f64x16_extract_x2(X,I) _simd_f64x16_extract_x2_(X,I)
#define _simd_f64x16__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_extract_x2_instruction_set>()
#else
#define _simd_f64x16_extract_x2(X,I) _simd_f64x16_extract_x2_safe(X,I)
#define _simd_f64x16__extract_x2_enable() true
#endif _simd_f64x16_extract_x2_

#define _simd_f64x16_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_f64x16*>(&X)[I] = Y)
#ifdef _simd_f64x16_insert_x2_
#define _simd_f64x16_insert_x2(X,I,Y) _simd_f64x16_insert_x2_(X,I,Y)
#define _simd_f64x16__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_insert_x2_instruction_set>()
#else
#define _simd_f64x16_insert_x2(X,I,Y) _simd_f64x16_insert_x2_safe(X,I,Y)
#define _simd_f64x16__insert_x2_enable() true
#endif _simd_f64x16_insert_x2_

#define _simd_f64x16_extract_x4_safe(X,I) (reinterpret_cast<const _simd_f64x16*>(&X)[I])
#ifdef _simd_f64x16_extract_x4_
#define _simd_f64x16_extract_x4(X,I) _simd_f64x16_extract_x4_(X,I)
#define _simd_f64x16__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_extract_x4_instruction_set>()
#else
#define _simd_f64x16_extract_x4(X,I) _simd_f64x16_extract_x4_safe(X,I)
#define _simd_f64x16__extract_x4_enable() true
#endif _simd_f64x16_extract_x4_

#define _simd_f64x16_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_f64x16*>(&X)[I] = Y)
#ifdef _simd_f64x16_insert_x4_
#define _simd_f64x16_insert_x4(X,I,Y) _simd_f64x16_insert_x4_(X,I,Y)
#define _simd_f64x16__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_insert_x4_instruction_set>()
#else
#define _simd_f64x16_insert_x4(X,I,Y) _simd_f64x16_insert_x4_safe(X,I,Y)
#define _simd_f64x16__insert_x4_enable() true
#endif _simd_f64x16_insert_x4_

#define _simd_f64x16_extract_x8_safe(X,I) (reinterpret_cast<const _simd_f64x16*>(&X)[I])
#ifdef _simd_f64x16_extract_x8_
#define _simd_f64x16_extract_x8(X,I) _simd_f64x16_extract_x8_(X,I)
#define _simd_f64x16__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_extract_x8_instruction_set>()
#else
#define _simd_f64x16_extract_x8(X,I) _simd_f64x16_extract_x8_safe(X,I)
#define _simd_f64x16__extract_x8_enable() true
#endif _simd_f64x16_extract_x8_

#define _simd_f64x16_insert_x8_safe(X,I,Y) (reinterpret_cast<_simd_f64x16*>(&X)[I] = Y)
#ifdef _simd_f64x16_insert_x8_
#define _simd_f64x16_insert_x8(X,I,Y) _simd_f64x16_insert_x8_(X,I,Y)
#define _simd_f64x16__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_insert_x8_instruction_set>()
#else
#define _simd_f64x16_insert_x8(X,I,Y) _simd_f64x16_insert_x8_safe(X,I,Y)
#define _simd_f64x16__insert_x8_enable() true
#endif _simd_f64x16_insert_x8_

#define _simd_f64x16_extract_x32_safe(X,I) _simd_f64x16_insert_x16_safe(_simd_f64x16_fill_undefined_safe(),0,X)
#ifdef _simd_f64x16_extract_x32_
#define _simd_f64x16_extract_x32(X,I) _simd_f64x16_extract_x32_(X,I)
#define _simd_f64x16__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_extract_x32_instruction_set>()
#else
#define _simd_f64x16_extract_x32(X,I) _simd_f64x16_extract_x32_safe(X,I)
#define _simd_f64x16__extract_x32_enable() true
#endif _simd_f64x16_extract_x32_

#define _simd_f64x16_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_f64x1) * 32)
#ifdef _simd_f64x16_insert_x32_
#define _simd_f64x16_insert_x32(X,I,Y) _simd_f64x16_insert_x32_(X,I,Y)
#define _simd_f64x16__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_insert_x32_instruction_set>()
#else
#define _simd_f64x16_insert_x32(X,I,Y) _simd_f64x16_insert_x32_safe(X,I,Y)
#define _simd_f64x16__insert_x32_enable() true
#endif _simd_f64x16_insert_x32_

#define _simd_f64x16_extract_x64_safe(X,I) _simd_f64x16_insert_x16_safe(_simd_f64x16_fill_undefined_safe(),0,X)
#ifdef _simd_f64x16_extract_x64_
#define _simd_f64x16_extract_x64(X,I) _simd_f64x16_extract_x64_(X,I)
#define _simd_f64x16__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_extract_x64_instruction_set>()
#else
#define _simd_f64x16_extract_x64(X,I) _simd_f64x16_extract_x64_safe(X,I)
#define _simd_f64x16__extract_x64_enable() true
#endif _simd_f64x16_extract_x64_

#define _simd_f64x16_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_f64x1) * 64)
#ifdef _simd_f64x16_insert_x64_
#define _simd_f64x16_insert_x64(X,I,Y) _simd_f64x16_insert_x64_(X,I,Y)
#define _simd_f64x16__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_insert_x64_instruction_set>()
#else
#define _simd_f64x16_insert_x64(X,I,Y) _simd_f64x16_insert_x64_safe(X,I,Y)
#define _simd_f64x16__insert_x64_enable() true
#endif _simd_f64x16_insert_x64_

#define _simd_f64x16_extract_safe(X,I) _simd_f64x16_extract_x1_safe(X,I)
#define _simd_f64x16_extract(X,I) _simd_f64x16_extract_x1(X,I)
#define _simd_f64x16_extract_enable() _simd_f64x16_extract_x1_enable()

#define _simd_f64x16_insert_safe(X,I,Y) _simd_f64x16_insert_x1_safe(X,I,Y)
#define _simd_f64x16_insert(X,I,Y) _simd_f64x16_insert_x1(X,I,Y)
#define _simd_f64x16_insert_enable() _simd_f64x16_insert_x1_enable()

//#ifndef _simd_f64x16_splitlo
//	#define _simd_f64x16_splitlo(X) _simd_f64x8_extract_x8(X,0)
//	#define _simd_f64x16_splitlo_enable() _simd_f64x8_extract_x8_enable()
//#endif

//#ifndef _simd_f64x16_splithi
//	#define _simd_f64x16_splithi(X) _simd_f64x8_extract_x8(X,1)
//	#define _simd_f64x16_splithi_enable() _simd_f64x8_extract_x8_enable()
//#endif

//#ifndef _simd_f64x16_combine
//	#define _simd_f64x16_combine(X,Y) _simd_f64x16_insert_x8(_simd_f64x16_insert_x8(_simd_f64x16_fill_undefined(), 0, X), 1, Y)
//	#define _simd_f64x16_combine_enable() (_simd_f64x16_insert_x8_enable() && _simd_f64x16_fill_undefined_enable())
//#endif

#define _simd_f64x32_extract_x1_safe(X,I) (reinterpret_cast<const _simd_f64x32*>(&X)[I])
#ifdef _simd_f64x32_extract_x1_
#define _simd_f64x32_extract_x1(X,I) _simd_f64x32_extract_x1_(X,I)
#define _simd_f64x32__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_extract_x1_instruction_set>()
#else
#define _simd_f64x32_extract_x1(X,I) _simd_f64x32_extract_x1_safe(X,I)
#define _simd_f64x32__extract_x1_enable() true
#endif _simd_f64x32_extract_x1_

#define _simd_f64x32_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_f64x32*>(&X)[I] = Y)
#ifdef _simd_f64x32_insert_x1_
#define _simd_f64x32_insert_x1(X,I,Y) _simd_f64x32_insert_x1_(X,I,Y)
#define _simd_f64x32__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_insert_x1_instruction_set>()
#else
#define _simd_f64x32_insert_x1(X,I,Y) _simd_f64x32_insert_x1_safe(X,I,Y)
#define _simd_f64x32__insert_x1_enable() true
#endif _simd_f64x32_insert_x1_

#define _simd_f64x32_extract_x2_safe(X,I) (reinterpret_cast<const _simd_f64x32*>(&X)[I])
#ifdef _simd_f64x32_extract_x2_
#define _simd_f64x32_extract_x2(X,I) _simd_f64x32_extract_x2_(X,I)
#define _simd_f64x32__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_extract_x2_instruction_set>()
#else
#define _simd_f64x32_extract_x2(X,I) _simd_f64x32_extract_x2_safe(X,I)
#define _simd_f64x32__extract_x2_enable() true
#endif _simd_f64x32_extract_x2_

#define _simd_f64x32_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_f64x32*>(&X)[I] = Y)
#ifdef _simd_f64x32_insert_x2_
#define _simd_f64x32_insert_x2(X,I,Y) _simd_f64x32_insert_x2_(X,I,Y)
#define _simd_f64x32__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_insert_x2_instruction_set>()
#else
#define _simd_f64x32_insert_x2(X,I,Y) _simd_f64x32_insert_x2_safe(X,I,Y)
#define _simd_f64x32__insert_x2_enable() true
#endif _simd_f64x32_insert_x2_

#define _simd_f64x32_extract_x4_safe(X,I) (reinterpret_cast<const _simd_f64x32*>(&X)[I])
#ifdef _simd_f64x32_extract_x4_
#define _simd_f64x32_extract_x4(X,I) _simd_f64x32_extract_x4_(X,I)
#define _simd_f64x32__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_extract_x4_instruction_set>()
#else
#define _simd_f64x32_extract_x4(X,I) _simd_f64x32_extract_x4_safe(X,I)
#define _simd_f64x32__extract_x4_enable() true
#endif _simd_f64x32_extract_x4_

#define _simd_f64x32_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_f64x32*>(&X)[I] = Y)
#ifdef _simd_f64x32_insert_x4_
#define _simd_f64x32_insert_x4(X,I,Y) _simd_f64x32_insert_x4_(X,I,Y)
#define _simd_f64x32__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_insert_x4_instruction_set>()
#else
#define _simd_f64x32_insert_x4(X,I,Y) _simd_f64x32_insert_x4_safe(X,I,Y)
#define _simd_f64x32__insert_x4_enable() true
#endif _simd_f64x32_insert_x4_

#define _simd_f64x32_extract_x8_safe(X,I) (reinterpret_cast<const _simd_f64x32*>(&X)[I])
#ifdef _simd_f64x32_extract_x8_
#define _simd_f64x32_extract_x8(X,I) _simd_f64x32_extract_x8_(X,I)
#define _simd_f64x32__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_extract_x8_instruction_set>()
#else
#define _simd_f64x32_extract_x8(X,I) _simd_f64x32_extract_x8_safe(X,I)
#define _simd_f64x32__extract_x8_enable() true
#endif _simd_f64x32_extract_x8_

#define _simd_f64x32_insert_x8_safe(X,I,Y) (reinterpret_cast<_simd_f64x32*>(&X)[I] = Y)
#ifdef _simd_f64x32_insert_x8_
#define _simd_f64x32_insert_x8(X,I,Y) _simd_f64x32_insert_x8_(X,I,Y)
#define _simd_f64x32__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_insert_x8_instruction_set>()
#else
#define _simd_f64x32_insert_x8(X,I,Y) _simd_f64x32_insert_x8_safe(X,I,Y)
#define _simd_f64x32__insert_x8_enable() true
#endif _simd_f64x32_insert_x8_

#define _simd_f64x32_extract_x16_safe(X,I) (reinterpret_cast<const _simd_f64x32*>(&X)[I])
#ifdef _simd_f64x32_extract_x16_
#define _simd_f64x32_extract_x16(X,I) _simd_f64x32_extract_x16_(X,I)
#define _simd_f64x32__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_extract_x16_instruction_set>()
#else
#define _simd_f64x32_extract_x16(X,I) _simd_f64x32_extract_x16_safe(X,I)
#define _simd_f64x32__extract_x16_enable() true
#endif _simd_f64x32_extract_x16_

#define _simd_f64x32_insert_x16_safe(X,I,Y) (reinterpret_cast<_simd_f64x32*>(&X)[I] = Y)
#ifdef _simd_f64x32_insert_x16_
#define _simd_f64x32_insert_x16(X,I,Y) _simd_f64x32_insert_x16_(X,I,Y)
#define _simd_f64x32__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_insert_x16_instruction_set>()
#else
#define _simd_f64x32_insert_x16(X,I,Y) _simd_f64x32_insert_x16_safe(X,I,Y)
#define _simd_f64x32__insert_x16_enable() true
#endif _simd_f64x32_insert_x16_

#define _simd_f64x32_extract_x64_safe(X,I) _simd_f64x32_insert_x32_safe(_simd_f64x32_fill_undefined_safe(),0,X)
#ifdef _simd_f64x32_extract_x64_
#define _simd_f64x32_extract_x64(X,I) _simd_f64x32_extract_x64_(X,I)
#define _simd_f64x32__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_extract_x64_instruction_set>()
#else
#define _simd_f64x32_extract_x64(X,I) _simd_f64x32_extract_x64_safe(X,I)
#define _simd_f64x32__extract_x64_enable() true
#endif _simd_f64x32_extract_x64_

#define _simd_f64x32_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_f64x1) * 64)
#ifdef _simd_f64x32_insert_x64_
#define _simd_f64x32_insert_x64(X,I,Y) _simd_f64x32_insert_x64_(X,I,Y)
#define _simd_f64x32__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_insert_x64_instruction_set>()
#else
#define _simd_f64x32_insert_x64(X,I,Y) _simd_f64x32_insert_x64_safe(X,I,Y)
#define _simd_f64x32__insert_x64_enable() true
#endif _simd_f64x32_insert_x64_

#define _simd_f64x32_extract_safe(X,I) _simd_f64x32_extract_x1_safe(X,I)
#define _simd_f64x32_extract(X,I) _simd_f64x32_extract_x1(X,I)
#define _simd_f64x32_extract_enable() _simd_f64x32_extract_x1_enable()

#define _simd_f64x32_insert_safe(X,I,Y) _simd_f64x32_insert_x1_safe(X,I,Y)
#define _simd_f64x32_insert(X,I,Y) _simd_f64x32_insert_x1(X,I,Y)
#define _simd_f64x32_insert_enable() _simd_f64x32_insert_x1_enable()

//#ifndef _simd_f64x32_splitlo
//	#define _simd_f64x32_splitlo(X) _simd_f64x16_extract_x16(X,0)
//	#define _simd_f64x32_splitlo_enable() _simd_f64x16_extract_x16_enable()
//#endif

//#ifndef _simd_f64x32_splithi
//	#define _simd_f64x32_splithi(X) _simd_f64x16_extract_x16(X,1)
//	#define _simd_f64x32_splithi_enable() _simd_f64x16_extract_x16_enable()
//#endif

//#ifndef _simd_f64x32_combine
//	#define _simd_f64x32_combine(X,Y) _simd_f64x32_insert_x16(_simd_f64x32_insert_x16(_simd_f64x32_fill_undefined(), 0, X), 1, Y)
//	#define _simd_f64x32_combine_enable() (_simd_f64x32_insert_x16_enable() && _simd_f64x32_fill_undefined_enable())
//#endif

#define _simd_f64x64_extract_x1_safe(X,I) (reinterpret_cast<const _simd_f64x64*>(&X)[I])
#ifdef _simd_f64x64_extract_x1_
#define _simd_f64x64_extract_x1(X,I) _simd_f64x64_extract_x1_(X,I)
#define _simd_f64x64__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_extract_x1_instruction_set>()
#else
#define _simd_f64x64_extract_x1(X,I) _simd_f64x64_extract_x1_safe(X,I)
#define _simd_f64x64__extract_x1_enable() true
#endif _simd_f64x64_extract_x1_

#define _simd_f64x64_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_f64x64*>(&X)[I] = Y)
#ifdef _simd_f64x64_insert_x1_
#define _simd_f64x64_insert_x1(X,I,Y) _simd_f64x64_insert_x1_(X,I,Y)
#define _simd_f64x64__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_insert_x1_instruction_set>()
#else
#define _simd_f64x64_insert_x1(X,I,Y) _simd_f64x64_insert_x1_safe(X,I,Y)
#define _simd_f64x64__insert_x1_enable() true
#endif _simd_f64x64_insert_x1_

#define _simd_f64x64_extract_x2_safe(X,I) (reinterpret_cast<const _simd_f64x64*>(&X)[I])
#ifdef _simd_f64x64_extract_x2_
#define _simd_f64x64_extract_x2(X,I) _simd_f64x64_extract_x2_(X,I)
#define _simd_f64x64__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_extract_x2_instruction_set>()
#else
#define _simd_f64x64_extract_x2(X,I) _simd_f64x64_extract_x2_safe(X,I)
#define _simd_f64x64__extract_x2_enable() true
#endif _simd_f64x64_extract_x2_

#define _simd_f64x64_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_f64x64*>(&X)[I] = Y)
#ifdef _simd_f64x64_insert_x2_
#define _simd_f64x64_insert_x2(X,I,Y) _simd_f64x64_insert_x2_(X,I,Y)
#define _simd_f64x64__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_insert_x2_instruction_set>()
#else
#define _simd_f64x64_insert_x2(X,I,Y) _simd_f64x64_insert_x2_safe(X,I,Y)
#define _simd_f64x64__insert_x2_enable() true
#endif _simd_f64x64_insert_x2_

#define _simd_f64x64_extract_x4_safe(X,I) (reinterpret_cast<const _simd_f64x64*>(&X)[I])
#ifdef _simd_f64x64_extract_x4_
#define _simd_f64x64_extract_x4(X,I) _simd_f64x64_extract_x4_(X,I)
#define _simd_f64x64__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_extract_x4_instruction_set>()
#else
#define _simd_f64x64_extract_x4(X,I) _simd_f64x64_extract_x4_safe(X,I)
#define _simd_f64x64__extract_x4_enable() true
#endif _simd_f64x64_extract_x4_

#define _simd_f64x64_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_f64x64*>(&X)[I] = Y)
#ifdef _simd_f64x64_insert_x4_
#define _simd_f64x64_insert_x4(X,I,Y) _simd_f64x64_insert_x4_(X,I,Y)
#define _simd_f64x64__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_insert_x4_instruction_set>()
#else
#define _simd_f64x64_insert_x4(X,I,Y) _simd_f64x64_insert_x4_safe(X,I,Y)
#define _simd_f64x64__insert_x4_enable() true
#endif _simd_f64x64_insert_x4_

#define _simd_f64x64_extract_x8_safe(X,I) (reinterpret_cast<const _simd_f64x64*>(&X)[I])
#ifdef _simd_f64x64_extract_x8_
#define _simd_f64x64_extract_x8(X,I) _simd_f64x64_extract_x8_(X,I)
#define _simd_f64x64__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_extract_x8_instruction_set>()
#else
#define _simd_f64x64_extract_x8(X,I) _simd_f64x64_extract_x8_safe(X,I)
#define _simd_f64x64__extract_x8_enable() true
#endif _simd_f64x64_extract_x8_

#define _simd_f64x64_insert_x8_safe(X,I,Y) (reinterpret_cast<_simd_f64x64*>(&X)[I] = Y)
#ifdef _simd_f64x64_insert_x8_
#define _simd_f64x64_insert_x8(X,I,Y) _simd_f64x64_insert_x8_(X,I,Y)
#define _simd_f64x64__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_insert_x8_instruction_set>()
#else
#define _simd_f64x64_insert_x8(X,I,Y) _simd_f64x64_insert_x8_safe(X,I,Y)
#define _simd_f64x64__insert_x8_enable() true
#endif _simd_f64x64_insert_x8_

#define _simd_f64x64_extract_x16_safe(X,I) (reinterpret_cast<const _simd_f64x64*>(&X)[I])
#ifdef _simd_f64x64_extract_x16_
#define _simd_f64x64_extract_x16(X,I) _simd_f64x64_extract_x16_(X,I)
#define _simd_f64x64__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_extract_x16_instruction_set>()
#else
#define _simd_f64x64_extract_x16(X,I) _simd_f64x64_extract_x16_safe(X,I)
#define _simd_f64x64__extract_x16_enable() true
#endif _simd_f64x64_extract_x16_

#define _simd_f64x64_insert_x16_safe(X,I,Y) (reinterpret_cast<_simd_f64x64*>(&X)[I] = Y)
#ifdef _simd_f64x64_insert_x16_
#define _simd_f64x64_insert_x16(X,I,Y) _simd_f64x64_insert_x16_(X,I,Y)
#define _simd_f64x64__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_insert_x16_instruction_set>()
#else
#define _simd_f64x64_insert_x16(X,I,Y) _simd_f64x64_insert_x16_safe(X,I,Y)
#define _simd_f64x64__insert_x16_enable() true
#endif _simd_f64x64_insert_x16_

#define _simd_f64x64_extract_x32_safe(X,I) (reinterpret_cast<const _simd_f64x64*>(&X)[I])
#ifdef _simd_f64x64_extract_x32_
#define _simd_f64x64_extract_x32(X,I) _simd_f64x64_extract_x32_(X,I)
#define _simd_f64x64__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_extract_x32_instruction_set>()
#else
#define _simd_f64x64_extract_x32(X,I) _simd_f64x64_extract_x32_safe(X,I)
#define _simd_f64x64__extract_x32_enable() true
#endif _simd_f64x64_extract_x32_

#define _simd_f64x64_insert_x32_safe(X,I,Y) (reinterpret_cast<_simd_f64x64*>(&X)[I] = Y)
#ifdef _simd_f64x64_insert_x32_
#define _simd_f64x64_insert_x32(X,I,Y) _simd_f64x64_insert_x32_(X,I,Y)
#define _simd_f64x64__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_insert_x32_instruction_set>()
#else
#define _simd_f64x64_insert_x32(X,I,Y) _simd_f64x64_insert_x32_safe(X,I,Y)
#define _simd_f64x64__insert_x32_enable() true
#endif _simd_f64x64_insert_x32_

#define _simd_f64x64_extract_safe(X,I) _simd_f64x64_extract_x1_safe(X,I)
#define _simd_f64x64_extract(X,I) _simd_f64x64_extract_x1(X,I)
#define _simd_f64x64_extract_enable() _simd_f64x64_extract_x1_enable()

#define _simd_f64x64_insert_safe(X,I,Y) _simd_f64x64_insert_x1_safe(X,I,Y)
#define _simd_f64x64_insert(X,I,Y) _simd_f64x64_insert_x1(X,I,Y)
#define _simd_f64x64_insert_enable() _simd_f64x64_insert_x1_enable()

//#ifndef _simd_f64x64_splitlo
//	#define _simd_f64x64_splitlo(X) _simd_f64x32_extract_x32(X,0)
//	#define _simd_f64x64_splitlo_enable() _simd_f64x32_extract_x32_enable()
//#endif

//#ifndef _simd_f64x64_splithi
//	#define _simd_f64x64_splithi(X) _simd_f64x32_extract_x32(X,1)
//	#define _simd_f64x64_splithi_enable() _simd_f64x32_extract_x32_enable()
//#endif

//#ifndef _simd_f64x64_combine
//	#define _simd_f64x64_combine(X,Y) _simd_f64x64_insert_x32(_simd_f64x64_insert_x32(_simd_f64x64_fill_undefined(), 0, X), 1, Y)
//	#define _simd_f64x64_combine_enable() (_simd_f64x64_insert_x32_enable() && _simd_f64x64_fill_undefined_enable())
//#endif

// -- f32 --

#define _simd_f32x2_extract_x1_safe(X,I) (reinterpret_cast<const _simd_f32x2*>(&X)[I])
#ifdef _simd_f32x2_extract_x1_
#define _simd_f32x2_extract_x1(X,I) _simd_f32x2_extract_x1_(X,I)
#define _simd_f32x2__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_extract_x1_instruction_set>()
#else
#define _simd_f32x2_extract_x1(X,I) _simd_f32x2_extract_x1_safe(X,I)
#define _simd_f32x2__extract_x1_enable() true
#endif _simd_f32x2_extract_x1_

#define _simd_f32x2_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_f32x2*>(&X)[I] = Y)
#ifdef _simd_f32x2_insert_x1_
#define _simd_f32x2_insert_x1(X,I,Y) _simd_f32x2_insert_x1_(X,I,Y)
#define _simd_f32x2__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_insert_x1_instruction_set>()
#else
#define _simd_f32x2_insert_x1(X,I,Y) _simd_f32x2_insert_x1_safe(X,I,Y)
#define _simd_f32x2__insert_x1_enable() true
#endif _simd_f32x2_insert_x1_

#define _simd_f32x2_extract_x4_safe(X,I) _simd_f32x2_insert_x2_safe(_simd_f32x2_fill_undefined_safe(),0,X)
#ifdef _simd_f32x2_extract_x4_
#define _simd_f32x2_extract_x4(X,I) _simd_f32x2_extract_x4_(X,I)
#define _simd_f32x2__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_extract_x4_instruction_set>()
#else
#define _simd_f32x2_extract_x4(X,I) _simd_f32x2_extract_x4_safe(X,I)
#define _simd_f32x2__extract_x4_enable() true
#endif _simd_f32x2_extract_x4_

#define _simd_f32x2_insert_x4_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_f32x1) * 4)
#ifdef _simd_f32x2_insert_x4_
#define _simd_f32x2_insert_x4(X,I,Y) _simd_f32x2_insert_x4_(X,I,Y)
#define _simd_f32x2__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_insert_x4_instruction_set>()
#else
#define _simd_f32x2_insert_x4(X,I,Y) _simd_f32x2_insert_x4_safe(X,I,Y)
#define _simd_f32x2__insert_x4_enable() true
#endif _simd_f32x2_insert_x4_

#define _simd_f32x2_extract_x8_safe(X,I) _simd_f32x2_insert_x2_safe(_simd_f32x2_fill_undefined_safe(),0,X)
#ifdef _simd_f32x2_extract_x8_
#define _simd_f32x2_extract_x8(X,I) _simd_f32x2_extract_x8_(X,I)
#define _simd_f32x2__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_extract_x8_instruction_set>()
#else
#define _simd_f32x2_extract_x8(X,I) _simd_f32x2_extract_x8_safe(X,I)
#define _simd_f32x2__extract_x8_enable() true
#endif _simd_f32x2_extract_x8_

#define _simd_f32x2_insert_x8_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_f32x1) * 8)
#ifdef _simd_f32x2_insert_x8_
#define _simd_f32x2_insert_x8(X,I,Y) _simd_f32x2_insert_x8_(X,I,Y)
#define _simd_f32x2__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_insert_x8_instruction_set>()
#else
#define _simd_f32x2_insert_x8(X,I,Y) _simd_f32x2_insert_x8_safe(X,I,Y)
#define _simd_f32x2__insert_x8_enable() true
#endif _simd_f32x2_insert_x8_

#define _simd_f32x2_extract_x16_safe(X,I) _simd_f32x2_insert_x2_safe(_simd_f32x2_fill_undefined_safe(),0,X)
#ifdef _simd_f32x2_extract_x16_
#define _simd_f32x2_extract_x16(X,I) _simd_f32x2_extract_x16_(X,I)
#define _simd_f32x2__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_extract_x16_instruction_set>()
#else
#define _simd_f32x2_extract_x16(X,I) _simd_f32x2_extract_x16_safe(X,I)
#define _simd_f32x2__extract_x16_enable() true
#endif _simd_f32x2_extract_x16_

#define _simd_f32x2_insert_x16_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_f32x1) * 16)
#ifdef _simd_f32x2_insert_x16_
#define _simd_f32x2_insert_x16(X,I,Y) _simd_f32x2_insert_x16_(X,I,Y)
#define _simd_f32x2__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_insert_x16_instruction_set>()
#else
#define _simd_f32x2_insert_x16(X,I,Y) _simd_f32x2_insert_x16_safe(X,I,Y)
#define _simd_f32x2__insert_x16_enable() true
#endif _simd_f32x2_insert_x16_

#define _simd_f32x2_extract_x32_safe(X,I) _simd_f32x2_insert_x2_safe(_simd_f32x2_fill_undefined_safe(),0,X)
#ifdef _simd_f32x2_extract_x32_
#define _simd_f32x2_extract_x32(X,I) _simd_f32x2_extract_x32_(X,I)
#define _simd_f32x2__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_extract_x32_instruction_set>()
#else
#define _simd_f32x2_extract_x32(X,I) _simd_f32x2_extract_x32_safe(X,I)
#define _simd_f32x2__extract_x32_enable() true
#endif _simd_f32x2_extract_x32_

#define _simd_f32x2_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_f32x1) * 32)
#ifdef _simd_f32x2_insert_x32_
#define _simd_f32x2_insert_x32(X,I,Y) _simd_f32x2_insert_x32_(X,I,Y)
#define _simd_f32x2__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_insert_x32_instruction_set>()
#else
#define _simd_f32x2_insert_x32(X,I,Y) _simd_f32x2_insert_x32_safe(X,I,Y)
#define _simd_f32x2__insert_x32_enable() true
#endif _simd_f32x2_insert_x32_

#define _simd_f32x2_extract_x64_safe(X,I) _simd_f32x2_insert_x2_safe(_simd_f32x2_fill_undefined_safe(),0,X)
#ifdef _simd_f32x2_extract_x64_
#define _simd_f32x2_extract_x64(X,I) _simd_f32x2_extract_x64_(X,I)
#define _simd_f32x2__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_extract_x64_instruction_set>()
#else
#define _simd_f32x2_extract_x64(X,I) _simd_f32x2_extract_x64_safe(X,I)
#define _simd_f32x2__extract_x64_enable() true
#endif _simd_f32x2_extract_x64_

#define _simd_f32x2_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_f32x1) * 64)
#ifdef _simd_f32x2_insert_x64_
#define _simd_f32x2_insert_x64(X,I,Y) _simd_f32x2_insert_x64_(X,I,Y)
#define _simd_f32x2__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_insert_x64_instruction_set>()
#else
#define _simd_f32x2_insert_x64(X,I,Y) _simd_f32x2_insert_x64_safe(X,I,Y)
#define _simd_f32x2__insert_x64_enable() true
#endif _simd_f32x2_insert_x64_

#define _simd_f32x2_extract_safe(X,I) _simd_f32x2_extract_x1_safe(X,I)
#define _simd_f32x2_extract(X,I) _simd_f32x2_extract_x1(X,I)
#define _simd_f32x2_extract_enable() _simd_f32x2_extract_x1_enable()

#define _simd_f32x2_insert_safe(X,I,Y) _simd_f32x2_insert_x1_safe(X,I,Y)
#define _simd_f32x2_insert(X,I,Y) _simd_f32x2_insert_x1(X,I,Y)
#define _simd_f32x2_insert_enable() _simd_f32x2_insert_x1_enable()

//#ifndef _simd_f32x2_splitlo
//	#define _simd_f32x2_splitlo(X) _simd_f32x1_extract_x1(X,0)
//	#define _simd_f32x2_splitlo_enable() _simd_f32x1_extract_x1_enable()
//#endif

//#ifndef _simd_f32x2_splithi
//	#define _simd_f32x2_splithi(X) _simd_f32x1_extract_x1(X,1)
//	#define _simd_f32x2_splithi_enable() _simd_f32x1_extract_x1_enable()
//#endif

//#ifndef _simd_f32x2_combine
//	#define _simd_f32x2_combine(X,Y) _simd_f32x2_insert_x1(_simd_f32x2_insert_x1(_simd_f32x2_fill_undefined(), 0, X), 1, Y)
//	#define _simd_f32x2_combine_enable() (_simd_f32x2_insert_x1_enable() && _simd_f32x2_fill_undefined_enable())
//#endif

#define _simd_f32x4_extract_x1_safe(X,I) (reinterpret_cast<const _simd_f32x4*>(&X)[I])
#ifdef _simd_f32x4_extract_x1_
#define _simd_f32x4_extract_x1(X,I) _simd_f32x4_extract_x1_(X,I)
#define _simd_f32x4__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_extract_x1_instruction_set>()
#else
#define _simd_f32x4_extract_x1(X,I) _simd_f32x4_extract_x1_safe(X,I)
#define _simd_f32x4__extract_x1_enable() true
#endif _simd_f32x4_extract_x1_

#define _simd_f32x4_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_f32x4*>(&X)[I] = Y)
#ifdef _simd_f32x4_insert_x1_
#define _simd_f32x4_insert_x1(X,I,Y) _simd_f32x4_insert_x1_(X,I,Y)
#define _simd_f32x4__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_insert_x1_instruction_set>()
#else
#define _simd_f32x4_insert_x1(X,I,Y) _simd_f32x4_insert_x1_safe(X,I,Y)
#define _simd_f32x4__insert_x1_enable() true
#endif _simd_f32x4_insert_x1_

#define _simd_f32x4_extract_x2_safe(X,I) (reinterpret_cast<const _simd_f32x4*>(&X)[I])
#ifdef _simd_f32x4_extract_x2_
#define _simd_f32x4_extract_x2(X,I) _simd_f32x4_extract_x2_(X,I)
#define _simd_f32x4__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_extract_x2_instruction_set>()
#else
#define _simd_f32x4_extract_x2(X,I) _simd_f32x4_extract_x2_safe(X,I)
#define _simd_f32x4__extract_x2_enable() true
#endif _simd_f32x4_extract_x2_

#define _simd_f32x4_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_f32x4*>(&X)[I] = Y)
#ifdef _simd_f32x4_insert_x2_
#define _simd_f32x4_insert_x2(X,I,Y) _simd_f32x4_insert_x2_(X,I,Y)
#define _simd_f32x4__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_insert_x2_instruction_set>()
#else
#define _simd_f32x4_insert_x2(X,I,Y) _simd_f32x4_insert_x2_safe(X,I,Y)
#define _simd_f32x4__insert_x2_enable() true
#endif _simd_f32x4_insert_x2_

#define _simd_f32x4_extract_x8_safe(X,I) _simd_f32x4_insert_x4_safe(_simd_f32x4_fill_undefined_safe(),0,X)
#ifdef _simd_f32x4_extract_x8_
#define _simd_f32x4_extract_x8(X,I) _simd_f32x4_extract_x8_(X,I)
#define _simd_f32x4__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_extract_x8_instruction_set>()
#else
#define _simd_f32x4_extract_x8(X,I) _simd_f32x4_extract_x8_safe(X,I)
#define _simd_f32x4__extract_x8_enable() true
#endif _simd_f32x4_extract_x8_

#define _simd_f32x4_insert_x8_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_f32x1) * 8)
#ifdef _simd_f32x4_insert_x8_
#define _simd_f32x4_insert_x8(X,I,Y) _simd_f32x4_insert_x8_(X,I,Y)
#define _simd_f32x4__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_insert_x8_instruction_set>()
#else
#define _simd_f32x4_insert_x8(X,I,Y) _simd_f32x4_insert_x8_safe(X,I,Y)
#define _simd_f32x4__insert_x8_enable() true
#endif _simd_f32x4_insert_x8_

#define _simd_f32x4_extract_x16_safe(X,I) _simd_f32x4_insert_x4_safe(_simd_f32x4_fill_undefined_safe(),0,X)
#ifdef _simd_f32x4_extract_x16_
#define _simd_f32x4_extract_x16(X,I) _simd_f32x4_extract_x16_(X,I)
#define _simd_f32x4__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_extract_x16_instruction_set>()
#else
#define _simd_f32x4_extract_x16(X,I) _simd_f32x4_extract_x16_safe(X,I)
#define _simd_f32x4__extract_x16_enable() true
#endif _simd_f32x4_extract_x16_

#define _simd_f32x4_insert_x16_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_f32x1) * 16)
#ifdef _simd_f32x4_insert_x16_
#define _simd_f32x4_insert_x16(X,I,Y) _simd_f32x4_insert_x16_(X,I,Y)
#define _simd_f32x4__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_insert_x16_instruction_set>()
#else
#define _simd_f32x4_insert_x16(X,I,Y) _simd_f32x4_insert_x16_safe(X,I,Y)
#define _simd_f32x4__insert_x16_enable() true
#endif _simd_f32x4_insert_x16_

#define _simd_f32x4_extract_x32_safe(X,I) _simd_f32x4_insert_x4_safe(_simd_f32x4_fill_undefined_safe(),0,X)
#ifdef _simd_f32x4_extract_x32_
#define _simd_f32x4_extract_x32(X,I) _simd_f32x4_extract_x32_(X,I)
#define _simd_f32x4__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_extract_x32_instruction_set>()
#else
#define _simd_f32x4_extract_x32(X,I) _simd_f32x4_extract_x32_safe(X,I)
#define _simd_f32x4__extract_x32_enable() true
#endif _simd_f32x4_extract_x32_

#define _simd_f32x4_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_f32x1) * 32)
#ifdef _simd_f32x4_insert_x32_
#define _simd_f32x4_insert_x32(X,I,Y) _simd_f32x4_insert_x32_(X,I,Y)
#define _simd_f32x4__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_insert_x32_instruction_set>()
#else
#define _simd_f32x4_insert_x32(X,I,Y) _simd_f32x4_insert_x32_safe(X,I,Y)
#define _simd_f32x4__insert_x32_enable() true
#endif _simd_f32x4_insert_x32_

#define _simd_f32x4_extract_x64_safe(X,I) _simd_f32x4_insert_x4_safe(_simd_f32x4_fill_undefined_safe(),0,X)
#ifdef _simd_f32x4_extract_x64_
#define _simd_f32x4_extract_x64(X,I) _simd_f32x4_extract_x64_(X,I)
#define _simd_f32x4__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_extract_x64_instruction_set>()
#else
#define _simd_f32x4_extract_x64(X,I) _simd_f32x4_extract_x64_safe(X,I)
#define _simd_f32x4__extract_x64_enable() true
#endif _simd_f32x4_extract_x64_

#define _simd_f32x4_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_f32x1) * 64)
#ifdef _simd_f32x4_insert_x64_
#define _simd_f32x4_insert_x64(X,I,Y) _simd_f32x4_insert_x64_(X,I,Y)
#define _simd_f32x4__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_insert_x64_instruction_set>()
#else
#define _simd_f32x4_insert_x64(X,I,Y) _simd_f32x4_insert_x64_safe(X,I,Y)
#define _simd_f32x4__insert_x64_enable() true
#endif _simd_f32x4_insert_x64_

#define _simd_f32x4_extract_safe(X,I) _simd_f32x4_extract_x1_safe(X,I)
#define _simd_f32x4_extract(X,I) _simd_f32x4_extract_x1(X,I)
#define _simd_f32x4_extract_enable() _simd_f32x4_extract_x1_enable()

#define _simd_f32x4_insert_safe(X,I,Y) _simd_f32x4_insert_x1_safe(X,I,Y)
#define _simd_f32x4_insert(X,I,Y) _simd_f32x4_insert_x1(X,I,Y)
#define _simd_f32x4_insert_enable() _simd_f32x4_insert_x1_enable()

//#ifndef _simd_f32x4_splitlo
//	#define _simd_f32x4_splitlo(X) _simd_f32x2_extract_x2(X,0)
//	#define _simd_f32x4_splitlo_enable() _simd_f32x2_extract_x2_enable()
//#endif

//#ifndef _simd_f32x4_splithi
//	#define _simd_f32x4_splithi(X) _simd_f32x2_extract_x2(X,1)
//	#define _simd_f32x4_splithi_enable() _simd_f32x2_extract_x2_enable()
//#endif

//#ifndef _simd_f32x4_combine
//	#define _simd_f32x4_combine(X,Y) _simd_f32x4_insert_x2(_simd_f32x4_insert_x2(_simd_f32x4_fill_undefined(), 0, X), 1, Y)
//	#define _simd_f32x4_combine_enable() (_simd_f32x4_insert_x2_enable() && _simd_f32x4_fill_undefined_enable())
//#endif

#define _simd_f32x8_extract_x1_safe(X,I) (reinterpret_cast<const _simd_f32x8*>(&X)[I])
#ifdef _simd_f32x8_extract_x1_
#define _simd_f32x8_extract_x1(X,I) _simd_f32x8_extract_x1_(X,I)
#define _simd_f32x8__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_extract_x1_instruction_set>()
#else
#define _simd_f32x8_extract_x1(X,I) _simd_f32x8_extract_x1_safe(X,I)
#define _simd_f32x8__extract_x1_enable() true
#endif _simd_f32x8_extract_x1_

#define _simd_f32x8_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_f32x8*>(&X)[I] = Y)
#ifdef _simd_f32x8_insert_x1_
#define _simd_f32x8_insert_x1(X,I,Y) _simd_f32x8_insert_x1_(X,I,Y)
#define _simd_f32x8__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_insert_x1_instruction_set>()
#else
#define _simd_f32x8_insert_x1(X,I,Y) _simd_f32x8_insert_x1_safe(X,I,Y)
#define _simd_f32x8__insert_x1_enable() true
#endif _simd_f32x8_insert_x1_

#define _simd_f32x8_extract_x2_safe(X,I) (reinterpret_cast<const _simd_f32x8*>(&X)[I])
#ifdef _simd_f32x8_extract_x2_
#define _simd_f32x8_extract_x2(X,I) _simd_f32x8_extract_x2_(X,I)
#define _simd_f32x8__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_extract_x2_instruction_set>()
#else
#define _simd_f32x8_extract_x2(X,I) _simd_f32x8_extract_x2_safe(X,I)
#define _simd_f32x8__extract_x2_enable() true
#endif _simd_f32x8_extract_x2_

#define _simd_f32x8_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_f32x8*>(&X)[I] = Y)
#ifdef _simd_f32x8_insert_x2_
#define _simd_f32x8_insert_x2(X,I,Y) _simd_f32x8_insert_x2_(X,I,Y)
#define _simd_f32x8__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_insert_x2_instruction_set>()
#else
#define _simd_f32x8_insert_x2(X,I,Y) _simd_f32x8_insert_x2_safe(X,I,Y)
#define _simd_f32x8__insert_x2_enable() true
#endif _simd_f32x8_insert_x2_

#define _simd_f32x8_extract_x4_safe(X,I) (reinterpret_cast<const _simd_f32x8*>(&X)[I])
#ifdef _simd_f32x8_extract_x4_
#define _simd_f32x8_extract_x4(X,I) _simd_f32x8_extract_x4_(X,I)
#define _simd_f32x8__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_extract_x4_instruction_set>()
#else
#define _simd_f32x8_extract_x4(X,I) _simd_f32x8_extract_x4_safe(X,I)
#define _simd_f32x8__extract_x4_enable() true
#endif _simd_f32x8_extract_x4_

#define _simd_f32x8_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_f32x8*>(&X)[I] = Y)
#ifdef _simd_f32x8_insert_x4_
#define _simd_f32x8_insert_x4(X,I,Y) _simd_f32x8_insert_x4_(X,I,Y)
#define _simd_f32x8__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_insert_x4_instruction_set>()
#else
#define _simd_f32x8_insert_x4(X,I,Y) _simd_f32x8_insert_x4_safe(X,I,Y)
#define _simd_f32x8__insert_x4_enable() true
#endif _simd_f32x8_insert_x4_

#define _simd_f32x8_extract_x16_safe(X,I) _simd_f32x8_insert_x8_safe(_simd_f32x8_fill_undefined_safe(),0,X)
#ifdef _simd_f32x8_extract_x16_
#define _simd_f32x8_extract_x16(X,I) _simd_f32x8_extract_x16_(X,I)
#define _simd_f32x8__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_extract_x16_instruction_set>()
#else
#define _simd_f32x8_extract_x16(X,I) _simd_f32x8_extract_x16_safe(X,I)
#define _simd_f32x8__extract_x16_enable() true
#endif _simd_f32x8_extract_x16_

#define _simd_f32x8_insert_x16_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_f32x1) * 16)
#ifdef _simd_f32x8_insert_x16_
#define _simd_f32x8_insert_x16(X,I,Y) _simd_f32x8_insert_x16_(X,I,Y)
#define _simd_f32x8__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_insert_x16_instruction_set>()
#else
#define _simd_f32x8_insert_x16(X,I,Y) _simd_f32x8_insert_x16_safe(X,I,Y)
#define _simd_f32x8__insert_x16_enable() true
#endif _simd_f32x8_insert_x16_

#define _simd_f32x8_extract_x32_safe(X,I) _simd_f32x8_insert_x8_safe(_simd_f32x8_fill_undefined_safe(),0,X)
#ifdef _simd_f32x8_extract_x32_
#define _simd_f32x8_extract_x32(X,I) _simd_f32x8_extract_x32_(X,I)
#define _simd_f32x8__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_extract_x32_instruction_set>()
#else
#define _simd_f32x8_extract_x32(X,I) _simd_f32x8_extract_x32_safe(X,I)
#define _simd_f32x8__extract_x32_enable() true
#endif _simd_f32x8_extract_x32_

#define _simd_f32x8_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_f32x1) * 32)
#ifdef _simd_f32x8_insert_x32_
#define _simd_f32x8_insert_x32(X,I,Y) _simd_f32x8_insert_x32_(X,I,Y)
#define _simd_f32x8__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_insert_x32_instruction_set>()
#else
#define _simd_f32x8_insert_x32(X,I,Y) _simd_f32x8_insert_x32_safe(X,I,Y)
#define _simd_f32x8__insert_x32_enable() true
#endif _simd_f32x8_insert_x32_

#define _simd_f32x8_extract_x64_safe(X,I) _simd_f32x8_insert_x8_safe(_simd_f32x8_fill_undefined_safe(),0,X)
#ifdef _simd_f32x8_extract_x64_
#define _simd_f32x8_extract_x64(X,I) _simd_f32x8_extract_x64_(X,I)
#define _simd_f32x8__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_extract_x64_instruction_set>()
#else
#define _simd_f32x8_extract_x64(X,I) _simd_f32x8_extract_x64_safe(X,I)
#define _simd_f32x8__extract_x64_enable() true
#endif _simd_f32x8_extract_x64_

#define _simd_f32x8_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_f32x1) * 64)
#ifdef _simd_f32x8_insert_x64_
#define _simd_f32x8_insert_x64(X,I,Y) _simd_f32x8_insert_x64_(X,I,Y)
#define _simd_f32x8__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_insert_x64_instruction_set>()
#else
#define _simd_f32x8_insert_x64(X,I,Y) _simd_f32x8_insert_x64_safe(X,I,Y)
#define _simd_f32x8__insert_x64_enable() true
#endif _simd_f32x8_insert_x64_

#define _simd_f32x8_extract_safe(X,I) _simd_f32x8_extract_x1_safe(X,I)
#define _simd_f32x8_extract(X,I) _simd_f32x8_extract_x1(X,I)
#define _simd_f32x8_extract_enable() _simd_f32x8_extract_x1_enable()

#define _simd_f32x8_insert_safe(X,I,Y) _simd_f32x8_insert_x1_safe(X,I,Y)
#define _simd_f32x8_insert(X,I,Y) _simd_f32x8_insert_x1(X,I,Y)
#define _simd_f32x8_insert_enable() _simd_f32x8_insert_x1_enable()

//#ifndef _simd_f32x8_splitlo
//	#define _simd_f32x8_splitlo(X) _simd_f32x4_extract_x4(X,0)
//	#define _simd_f32x8_splitlo_enable() _simd_f32x4_extract_x4_enable()
//#endif

//#ifndef _simd_f32x8_splithi
//	#define _simd_f32x8_splithi(X) _simd_f32x4_extract_x4(X,1)
//	#define _simd_f32x8_splithi_enable() _simd_f32x4_extract_x4_enable()
//#endif

//#ifndef _simd_f32x8_combine
//	#define _simd_f32x8_combine(X,Y) _simd_f32x8_insert_x4(_simd_f32x8_insert_x4(_simd_f32x8_fill_undefined(), 0, X), 1, Y)
//	#define _simd_f32x8_combine_enable() (_simd_f32x8_insert_x4_enable() && _simd_f32x8_fill_undefined_enable())
//#endif

#define _simd_f32x16_extract_x1_safe(X,I) (reinterpret_cast<const _simd_f32x16*>(&X)[I])
#ifdef _simd_f32x16_extract_x1_
#define _simd_f32x16_extract_x1(X,I) _simd_f32x16_extract_x1_(X,I)
#define _simd_f32x16__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_extract_x1_instruction_set>()
#else
#define _simd_f32x16_extract_x1(X,I) _simd_f32x16_extract_x1_safe(X,I)
#define _simd_f32x16__extract_x1_enable() true
#endif _simd_f32x16_extract_x1_

#define _simd_f32x16_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_f32x16*>(&X)[I] = Y)
#ifdef _simd_f32x16_insert_x1_
#define _simd_f32x16_insert_x1(X,I,Y) _simd_f32x16_insert_x1_(X,I,Y)
#define _simd_f32x16__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_insert_x1_instruction_set>()
#else
#define _simd_f32x16_insert_x1(X,I,Y) _simd_f32x16_insert_x1_safe(X,I,Y)
#define _simd_f32x16__insert_x1_enable() true
#endif _simd_f32x16_insert_x1_

#define _simd_f32x16_extract_x2_safe(X,I) (reinterpret_cast<const _simd_f32x16*>(&X)[I])
#ifdef _simd_f32x16_extract_x2_
#define _simd_f32x16_extract_x2(X,I) _simd_f32x16_extract_x2_(X,I)
#define _simd_f32x16__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_extract_x2_instruction_set>()
#else
#define _simd_f32x16_extract_x2(X,I) _simd_f32x16_extract_x2_safe(X,I)
#define _simd_f32x16__extract_x2_enable() true
#endif _simd_f32x16_extract_x2_

#define _simd_f32x16_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_f32x16*>(&X)[I] = Y)
#ifdef _simd_f32x16_insert_x2_
#define _simd_f32x16_insert_x2(X,I,Y) _simd_f32x16_insert_x2_(X,I,Y)
#define _simd_f32x16__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_insert_x2_instruction_set>()
#else
#define _simd_f32x16_insert_x2(X,I,Y) _simd_f32x16_insert_x2_safe(X,I,Y)
#define _simd_f32x16__insert_x2_enable() true
#endif _simd_f32x16_insert_x2_

#define _simd_f32x16_extract_x4_safe(X,I) (reinterpret_cast<const _simd_f32x16*>(&X)[I])
#ifdef _simd_f32x16_extract_x4_
#define _simd_f32x16_extract_x4(X,I) _simd_f32x16_extract_x4_(X,I)
#define _simd_f32x16__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_extract_x4_instruction_set>()
#else
#define _simd_f32x16_extract_x4(X,I) _simd_f32x16_extract_x4_safe(X,I)
#define _simd_f32x16__extract_x4_enable() true
#endif _simd_f32x16_extract_x4_

#define _simd_f32x16_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_f32x16*>(&X)[I] = Y)
#ifdef _simd_f32x16_insert_x4_
#define _simd_f32x16_insert_x4(X,I,Y) _simd_f32x16_insert_x4_(X,I,Y)
#define _simd_f32x16__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_insert_x4_instruction_set>()
#else
#define _simd_f32x16_insert_x4(X,I,Y) _simd_f32x16_insert_x4_safe(X,I,Y)
#define _simd_f32x16__insert_x4_enable() true
#endif _simd_f32x16_insert_x4_

#define _simd_f32x16_extract_x8_safe(X,I) (reinterpret_cast<const _simd_f32x16*>(&X)[I])
#ifdef _simd_f32x16_extract_x8_
#define _simd_f32x16_extract_x8(X,I) _simd_f32x16_extract_x8_(X,I)
#define _simd_f32x16__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_extract_x8_instruction_set>()
#else
#define _simd_f32x16_extract_x8(X,I) _simd_f32x16_extract_x8_safe(X,I)
#define _simd_f32x16__extract_x8_enable() true
#endif _simd_f32x16_extract_x8_

#define _simd_f32x16_insert_x8_safe(X,I,Y) (reinterpret_cast<_simd_f32x16*>(&X)[I] = Y)
#ifdef _simd_f32x16_insert_x8_
#define _simd_f32x16_insert_x8(X,I,Y) _simd_f32x16_insert_x8_(X,I,Y)
#define _simd_f32x16__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_insert_x8_instruction_set>()
#else
#define _simd_f32x16_insert_x8(X,I,Y) _simd_f32x16_insert_x8_safe(X,I,Y)
#define _simd_f32x16__insert_x8_enable() true
#endif _simd_f32x16_insert_x8_

#define _simd_f32x16_extract_x32_safe(X,I) _simd_f32x16_insert_x16_safe(_simd_f32x16_fill_undefined_safe(),0,X)
#ifdef _simd_f32x16_extract_x32_
#define _simd_f32x16_extract_x32(X,I) _simd_f32x16_extract_x32_(X,I)
#define _simd_f32x16__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_extract_x32_instruction_set>()
#else
#define _simd_f32x16_extract_x32(X,I) _simd_f32x16_extract_x32_safe(X,I)
#define _simd_f32x16__extract_x32_enable() true
#endif _simd_f32x16_extract_x32_

#define _simd_f32x16_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_f32x1) * 32)
#ifdef _simd_f32x16_insert_x32_
#define _simd_f32x16_insert_x32(X,I,Y) _simd_f32x16_insert_x32_(X,I,Y)
#define _simd_f32x16__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_insert_x32_instruction_set>()
#else
#define _simd_f32x16_insert_x32(X,I,Y) _simd_f32x16_insert_x32_safe(X,I,Y)
#define _simd_f32x16__insert_x32_enable() true
#endif _simd_f32x16_insert_x32_

#define _simd_f32x16_extract_x64_safe(X,I) _simd_f32x16_insert_x16_safe(_simd_f32x16_fill_undefined_safe(),0,X)
#ifdef _simd_f32x16_extract_x64_
#define _simd_f32x16_extract_x64(X,I) _simd_f32x16_extract_x64_(X,I)
#define _simd_f32x16__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_extract_x64_instruction_set>()
#else
#define _simd_f32x16_extract_x64(X,I) _simd_f32x16_extract_x64_safe(X,I)
#define _simd_f32x16__extract_x64_enable() true
#endif _simd_f32x16_extract_x64_

#define _simd_f32x16_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_f32x1) * 64)
#ifdef _simd_f32x16_insert_x64_
#define _simd_f32x16_insert_x64(X,I,Y) _simd_f32x16_insert_x64_(X,I,Y)
#define _simd_f32x16__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_insert_x64_instruction_set>()
#else
#define _simd_f32x16_insert_x64(X,I,Y) _simd_f32x16_insert_x64_safe(X,I,Y)
#define _simd_f32x16__insert_x64_enable() true
#endif _simd_f32x16_insert_x64_

#define _simd_f32x16_extract_safe(X,I) _simd_f32x16_extract_x1_safe(X,I)
#define _simd_f32x16_extract(X,I) _simd_f32x16_extract_x1(X,I)
#define _simd_f32x16_extract_enable() _simd_f32x16_extract_x1_enable()

#define _simd_f32x16_insert_safe(X,I,Y) _simd_f32x16_insert_x1_safe(X,I,Y)
#define _simd_f32x16_insert(X,I,Y) _simd_f32x16_insert_x1(X,I,Y)
#define _simd_f32x16_insert_enable() _simd_f32x16_insert_x1_enable()

//#ifndef _simd_f32x16_splitlo
//	#define _simd_f32x16_splitlo(X) _simd_f32x8_extract_x8(X,0)
//	#define _simd_f32x16_splitlo_enable() _simd_f32x8_extract_x8_enable()
//#endif

//#ifndef _simd_f32x16_splithi
//	#define _simd_f32x16_splithi(X) _simd_f32x8_extract_x8(X,1)
//	#define _simd_f32x16_splithi_enable() _simd_f32x8_extract_x8_enable()
//#endif

//#ifndef _simd_f32x16_combine
//	#define _simd_f32x16_combine(X,Y) _simd_f32x16_insert_x8(_simd_f32x16_insert_x8(_simd_f32x16_fill_undefined(), 0, X), 1, Y)
//	#define _simd_f32x16_combine_enable() (_simd_f32x16_insert_x8_enable() && _simd_f32x16_fill_undefined_enable())
//#endif

#define _simd_f32x32_extract_x1_safe(X,I) (reinterpret_cast<const _simd_f32x32*>(&X)[I])
#ifdef _simd_f32x32_extract_x1_
#define _simd_f32x32_extract_x1(X,I) _simd_f32x32_extract_x1_(X,I)
#define _simd_f32x32__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_extract_x1_instruction_set>()
#else
#define _simd_f32x32_extract_x1(X,I) _simd_f32x32_extract_x1_safe(X,I)
#define _simd_f32x32__extract_x1_enable() true
#endif _simd_f32x32_extract_x1_

#define _simd_f32x32_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_f32x32*>(&X)[I] = Y)
#ifdef _simd_f32x32_insert_x1_
#define _simd_f32x32_insert_x1(X,I,Y) _simd_f32x32_insert_x1_(X,I,Y)
#define _simd_f32x32__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_insert_x1_instruction_set>()
#else
#define _simd_f32x32_insert_x1(X,I,Y) _simd_f32x32_insert_x1_safe(X,I,Y)
#define _simd_f32x32__insert_x1_enable() true
#endif _simd_f32x32_insert_x1_

#define _simd_f32x32_extract_x2_safe(X,I) (reinterpret_cast<const _simd_f32x32*>(&X)[I])
#ifdef _simd_f32x32_extract_x2_
#define _simd_f32x32_extract_x2(X,I) _simd_f32x32_extract_x2_(X,I)
#define _simd_f32x32__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_extract_x2_instruction_set>()
#else
#define _simd_f32x32_extract_x2(X,I) _simd_f32x32_extract_x2_safe(X,I)
#define _simd_f32x32__extract_x2_enable() true
#endif _simd_f32x32_extract_x2_

#define _simd_f32x32_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_f32x32*>(&X)[I] = Y)
#ifdef _simd_f32x32_insert_x2_
#define _simd_f32x32_insert_x2(X,I,Y) _simd_f32x32_insert_x2_(X,I,Y)
#define _simd_f32x32__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_insert_x2_instruction_set>()
#else
#define _simd_f32x32_insert_x2(X,I,Y) _simd_f32x32_insert_x2_safe(X,I,Y)
#define _simd_f32x32__insert_x2_enable() true
#endif _simd_f32x32_insert_x2_

#define _simd_f32x32_extract_x4_safe(X,I) (reinterpret_cast<const _simd_f32x32*>(&X)[I])
#ifdef _simd_f32x32_extract_x4_
#define _simd_f32x32_extract_x4(X,I) _simd_f32x32_extract_x4_(X,I)
#define _simd_f32x32__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_extract_x4_instruction_set>()
#else
#define _simd_f32x32_extract_x4(X,I) _simd_f32x32_extract_x4_safe(X,I)
#define _simd_f32x32__extract_x4_enable() true
#endif _simd_f32x32_extract_x4_

#define _simd_f32x32_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_f32x32*>(&X)[I] = Y)
#ifdef _simd_f32x32_insert_x4_
#define _simd_f32x32_insert_x4(X,I,Y) _simd_f32x32_insert_x4_(X,I,Y)
#define _simd_f32x32__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_insert_x4_instruction_set>()
#else
#define _simd_f32x32_insert_x4(X,I,Y) _simd_f32x32_insert_x4_safe(X,I,Y)
#define _simd_f32x32__insert_x4_enable() true
#endif _simd_f32x32_insert_x4_

#define _simd_f32x32_extract_x8_safe(X,I) (reinterpret_cast<const _simd_f32x32*>(&X)[I])
#ifdef _simd_f32x32_extract_x8_
#define _simd_f32x32_extract_x8(X,I) _simd_f32x32_extract_x8_(X,I)
#define _simd_f32x32__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_extract_x8_instruction_set>()
#else
#define _simd_f32x32_extract_x8(X,I) _simd_f32x32_extract_x8_safe(X,I)
#define _simd_f32x32__extract_x8_enable() true
#endif _simd_f32x32_extract_x8_

#define _simd_f32x32_insert_x8_safe(X,I,Y) (reinterpret_cast<_simd_f32x32*>(&X)[I] = Y)
#ifdef _simd_f32x32_insert_x8_
#define _simd_f32x32_insert_x8(X,I,Y) _simd_f32x32_insert_x8_(X,I,Y)
#define _simd_f32x32__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_insert_x8_instruction_set>()
#else
#define _simd_f32x32_insert_x8(X,I,Y) _simd_f32x32_insert_x8_safe(X,I,Y)
#define _simd_f32x32__insert_x8_enable() true
#endif _simd_f32x32_insert_x8_

#define _simd_f32x32_extract_x16_safe(X,I) (reinterpret_cast<const _simd_f32x32*>(&X)[I])
#ifdef _simd_f32x32_extract_x16_
#define _simd_f32x32_extract_x16(X,I) _simd_f32x32_extract_x16_(X,I)
#define _simd_f32x32__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_extract_x16_instruction_set>()
#else
#define _simd_f32x32_extract_x16(X,I) _simd_f32x32_extract_x16_safe(X,I)
#define _simd_f32x32__extract_x16_enable() true
#endif _simd_f32x32_extract_x16_

#define _simd_f32x32_insert_x16_safe(X,I,Y) (reinterpret_cast<_simd_f32x32*>(&X)[I] = Y)
#ifdef _simd_f32x32_insert_x16_
#define _simd_f32x32_insert_x16(X,I,Y) _simd_f32x32_insert_x16_(X,I,Y)
#define _simd_f32x32__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_insert_x16_instruction_set>()
#else
#define _simd_f32x32_insert_x16(X,I,Y) _simd_f32x32_insert_x16_safe(X,I,Y)
#define _simd_f32x32__insert_x16_enable() true
#endif _simd_f32x32_insert_x16_

#define _simd_f32x32_extract_x64_safe(X,I) _simd_f32x32_insert_x32_safe(_simd_f32x32_fill_undefined_safe(),0,X)
#ifdef _simd_f32x32_extract_x64_
#define _simd_f32x32_extract_x64(X,I) _simd_f32x32_extract_x64_(X,I)
#define _simd_f32x32__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_extract_x64_instruction_set>()
#else
#define _simd_f32x32_extract_x64(X,I) _simd_f32x32_extract_x64_safe(X,I)
#define _simd_f32x32__extract_x64_enable() true
#endif _simd_f32x32_extract_x64_

#define _simd_f32x32_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_f32x1) * 64)
#ifdef _simd_f32x32_insert_x64_
#define _simd_f32x32_insert_x64(X,I,Y) _simd_f32x32_insert_x64_(X,I,Y)
#define _simd_f32x32__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_insert_x64_instruction_set>()
#else
#define _simd_f32x32_insert_x64(X,I,Y) _simd_f32x32_insert_x64_safe(X,I,Y)
#define _simd_f32x32__insert_x64_enable() true
#endif _simd_f32x32_insert_x64_

#define _simd_f32x32_extract_safe(X,I) _simd_f32x32_extract_x1_safe(X,I)
#define _simd_f32x32_extract(X,I) _simd_f32x32_extract_x1(X,I)
#define _simd_f32x32_extract_enable() _simd_f32x32_extract_x1_enable()

#define _simd_f32x32_insert_safe(X,I,Y) _simd_f32x32_insert_x1_safe(X,I,Y)
#define _simd_f32x32_insert(X,I,Y) _simd_f32x32_insert_x1(X,I,Y)
#define _simd_f32x32_insert_enable() _simd_f32x32_insert_x1_enable()

//#ifndef _simd_f32x32_splitlo
//	#define _simd_f32x32_splitlo(X) _simd_f32x16_extract_x16(X,0)
//	#define _simd_f32x32_splitlo_enable() _simd_f32x16_extract_x16_enable()
//#endif

//#ifndef _simd_f32x32_splithi
//	#define _simd_f32x32_splithi(X) _simd_f32x16_extract_x16(X,1)
//	#define _simd_f32x32_splithi_enable() _simd_f32x16_extract_x16_enable()
//#endif

//#ifndef _simd_f32x32_combine
//	#define _simd_f32x32_combine(X,Y) _simd_f32x32_insert_x16(_simd_f32x32_insert_x16(_simd_f32x32_fill_undefined(), 0, X), 1, Y)
//	#define _simd_f32x32_combine_enable() (_simd_f32x32_insert_x16_enable() && _simd_f32x32_fill_undefined_enable())
//#endif

#define _simd_f32x64_extract_x1_safe(X,I) (reinterpret_cast<const _simd_f32x64*>(&X)[I])
#ifdef _simd_f32x64_extract_x1_
#define _simd_f32x64_extract_x1(X,I) _simd_f32x64_extract_x1_(X,I)
#define _simd_f32x64__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_extract_x1_instruction_set>()
#else
#define _simd_f32x64_extract_x1(X,I) _simd_f32x64_extract_x1_safe(X,I)
#define _simd_f32x64__extract_x1_enable() true
#endif _simd_f32x64_extract_x1_

#define _simd_f32x64_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_f32x64*>(&X)[I] = Y)
#ifdef _simd_f32x64_insert_x1_
#define _simd_f32x64_insert_x1(X,I,Y) _simd_f32x64_insert_x1_(X,I,Y)
#define _simd_f32x64__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_insert_x1_instruction_set>()
#else
#define _simd_f32x64_insert_x1(X,I,Y) _simd_f32x64_insert_x1_safe(X,I,Y)
#define _simd_f32x64__insert_x1_enable() true
#endif _simd_f32x64_insert_x1_

#define _simd_f32x64_extract_x2_safe(X,I) (reinterpret_cast<const _simd_f32x64*>(&X)[I])
#ifdef _simd_f32x64_extract_x2_
#define _simd_f32x64_extract_x2(X,I) _simd_f32x64_extract_x2_(X,I)
#define _simd_f32x64__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_extract_x2_instruction_set>()
#else
#define _simd_f32x64_extract_x2(X,I) _simd_f32x64_extract_x2_safe(X,I)
#define _simd_f32x64__extract_x2_enable() true
#endif _simd_f32x64_extract_x2_

#define _simd_f32x64_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_f32x64*>(&X)[I] = Y)
#ifdef _simd_f32x64_insert_x2_
#define _simd_f32x64_insert_x2(X,I,Y) _simd_f32x64_insert_x2_(X,I,Y)
#define _simd_f32x64__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_insert_x2_instruction_set>()
#else
#define _simd_f32x64_insert_x2(X,I,Y) _simd_f32x64_insert_x2_safe(X,I,Y)
#define _simd_f32x64__insert_x2_enable() true
#endif _simd_f32x64_insert_x2_

#define _simd_f32x64_extract_x4_safe(X,I) (reinterpret_cast<const _simd_f32x64*>(&X)[I])
#ifdef _simd_f32x64_extract_x4_
#define _simd_f32x64_extract_x4(X,I) _simd_f32x64_extract_x4_(X,I)
#define _simd_f32x64__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_extract_x4_instruction_set>()
#else
#define _simd_f32x64_extract_x4(X,I) _simd_f32x64_extract_x4_safe(X,I)
#define _simd_f32x64__extract_x4_enable() true
#endif _simd_f32x64_extract_x4_

#define _simd_f32x64_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_f32x64*>(&X)[I] = Y)
#ifdef _simd_f32x64_insert_x4_
#define _simd_f32x64_insert_x4(X,I,Y) _simd_f32x64_insert_x4_(X,I,Y)
#define _simd_f32x64__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_insert_x4_instruction_set>()
#else
#define _simd_f32x64_insert_x4(X,I,Y) _simd_f32x64_insert_x4_safe(X,I,Y)
#define _simd_f32x64__insert_x4_enable() true
#endif _simd_f32x64_insert_x4_

#define _simd_f32x64_extract_x8_safe(X,I) (reinterpret_cast<const _simd_f32x64*>(&X)[I])
#ifdef _simd_f32x64_extract_x8_
#define _simd_f32x64_extract_x8(X,I) _simd_f32x64_extract_x8_(X,I)
#define _simd_f32x64__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_extract_x8_instruction_set>()
#else
#define _simd_f32x64_extract_x8(X,I) _simd_f32x64_extract_x8_safe(X,I)
#define _simd_f32x64__extract_x8_enable() true
#endif _simd_f32x64_extract_x8_

#define _simd_f32x64_insert_x8_safe(X,I,Y) (reinterpret_cast<_simd_f32x64*>(&X)[I] = Y)
#ifdef _simd_f32x64_insert_x8_
#define _simd_f32x64_insert_x8(X,I,Y) _simd_f32x64_insert_x8_(X,I,Y)
#define _simd_f32x64__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_insert_x8_instruction_set>()
#else
#define _simd_f32x64_insert_x8(X,I,Y) _simd_f32x64_insert_x8_safe(X,I,Y)
#define _simd_f32x64__insert_x8_enable() true
#endif _simd_f32x64_insert_x8_

#define _simd_f32x64_extract_x16_safe(X,I) (reinterpret_cast<const _simd_f32x64*>(&X)[I])
#ifdef _simd_f32x64_extract_x16_
#define _simd_f32x64_extract_x16(X,I) _simd_f32x64_extract_x16_(X,I)
#define _simd_f32x64__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_extract_x16_instruction_set>()
#else
#define _simd_f32x64_extract_x16(X,I) _simd_f32x64_extract_x16_safe(X,I)
#define _simd_f32x64__extract_x16_enable() true
#endif _simd_f32x64_extract_x16_

#define _simd_f32x64_insert_x16_safe(X,I,Y) (reinterpret_cast<_simd_f32x64*>(&X)[I] = Y)
#ifdef _simd_f32x64_insert_x16_
#define _simd_f32x64_insert_x16(X,I,Y) _simd_f32x64_insert_x16_(X,I,Y)
#define _simd_f32x64__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_insert_x16_instruction_set>()
#else
#define _simd_f32x64_insert_x16(X,I,Y) _simd_f32x64_insert_x16_safe(X,I,Y)
#define _simd_f32x64__insert_x16_enable() true
#endif _simd_f32x64_insert_x16_

#define _simd_f32x64_extract_x32_safe(X,I) (reinterpret_cast<const _simd_f32x64*>(&X)[I])
#ifdef _simd_f32x64_extract_x32_
#define _simd_f32x64_extract_x32(X,I) _simd_f32x64_extract_x32_(X,I)
#define _simd_f32x64__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_extract_x32_instruction_set>()
#else
#define _simd_f32x64_extract_x32(X,I) _simd_f32x64_extract_x32_safe(X,I)
#define _simd_f32x64__extract_x32_enable() true
#endif _simd_f32x64_extract_x32_

#define _simd_f32x64_insert_x32_safe(X,I,Y) (reinterpret_cast<_simd_f32x64*>(&X)[I] = Y)
#ifdef _simd_f32x64_insert_x32_
#define _simd_f32x64_insert_x32(X,I,Y) _simd_f32x64_insert_x32_(X,I,Y)
#define _simd_f32x64__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_insert_x32_instruction_set>()
#else
#define _simd_f32x64_insert_x32(X,I,Y) _simd_f32x64_insert_x32_safe(X,I,Y)
#define _simd_f32x64__insert_x32_enable() true
#endif _simd_f32x64_insert_x32_

#define _simd_f32x64_extract_safe(X,I) _simd_f32x64_extract_x1_safe(X,I)
#define _simd_f32x64_extract(X,I) _simd_f32x64_extract_x1(X,I)
#define _simd_f32x64_extract_enable() _simd_f32x64_extract_x1_enable()

#define _simd_f32x64_insert_safe(X,I,Y) _simd_f32x64_insert_x1_safe(X,I,Y)
#define _simd_f32x64_insert(X,I,Y) _simd_f32x64_insert_x1(X,I,Y)
#define _simd_f32x64_insert_enable() _simd_f32x64_insert_x1_enable()

//#ifndef _simd_f32x64_splitlo
//	#define _simd_f32x64_splitlo(X) _simd_f32x32_extract_x32(X,0)
//	#define _simd_f32x64_splitlo_enable() _simd_f32x32_extract_x32_enable()
//#endif

//#ifndef _simd_f32x64_splithi
//	#define _simd_f32x64_splithi(X) _simd_f32x32_extract_x32(X,1)
//	#define _simd_f32x64_splithi_enable() _simd_f32x32_extract_x32_enable()
//#endif

//#ifndef _simd_f32x64_combine
//	#define _simd_f32x64_combine(X,Y) _simd_f32x64_insert_x32(_simd_f32x64_insert_x32(_simd_f32x64_fill_undefined(), 0, X), 1, Y)
//	#define _simd_f32x64_combine_enable() (_simd_f32x64_insert_x32_enable() && _simd_f32x64_fill_undefined_enable())
//#endif

// -- s64 --

#define _simd_s64x2_extract_x1_safe(X,I) (reinterpret_cast<const _simd_s64x2*>(&X)[I])
#ifdef _simd_s64x2_extract_x1_
#define _simd_s64x2_extract_x1(X,I) _simd_s64x2_extract_x1_(X,I)
#define _simd_s64x2__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_extract_x1_instruction_set>()
#else
#define _simd_s64x2_extract_x1(X,I) _simd_s64x2_extract_x1_safe(X,I)
#define _simd_s64x2__extract_x1_enable() true
#endif _simd_s64x2_extract_x1_

#define _simd_s64x2_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_s64x2*>(&X)[I] = Y)
#ifdef _simd_s64x2_insert_x1_
#define _simd_s64x2_insert_x1(X,I,Y) _simd_s64x2_insert_x1_(X,I,Y)
#define _simd_s64x2__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_insert_x1_instruction_set>()
#else
#define _simd_s64x2_insert_x1(X,I,Y) _simd_s64x2_insert_x1_safe(X,I,Y)
#define _simd_s64x2__insert_x1_enable() true
#endif _simd_s64x2_insert_x1_

#define _simd_s64x2_extract_x4_safe(X,I) _simd_s64x2_insert_x2_safe(_simd_s64x2_fill_undefined_safe(),0,X)
#ifdef _simd_s64x2_extract_x4_
#define _simd_s64x2_extract_x4(X,I) _simd_s64x2_extract_x4_(X,I)
#define _simd_s64x2__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_extract_x4_instruction_set>()
#else
#define _simd_s64x2_extract_x4(X,I) _simd_s64x2_extract_x4_safe(X,I)
#define _simd_s64x2__extract_x4_enable() true
#endif _simd_s64x2_extract_x4_

#define _simd_s64x2_insert_x4_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s64x1) * 4)
#ifdef _simd_s64x2_insert_x4_
#define _simd_s64x2_insert_x4(X,I,Y) _simd_s64x2_insert_x4_(X,I,Y)
#define _simd_s64x2__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_insert_x4_instruction_set>()
#else
#define _simd_s64x2_insert_x4(X,I,Y) _simd_s64x2_insert_x4_safe(X,I,Y)
#define _simd_s64x2__insert_x4_enable() true
#endif _simd_s64x2_insert_x4_

#define _simd_s64x2_extract_x8_safe(X,I) _simd_s64x2_insert_x2_safe(_simd_s64x2_fill_undefined_safe(),0,X)
#ifdef _simd_s64x2_extract_x8_
#define _simd_s64x2_extract_x8(X,I) _simd_s64x2_extract_x8_(X,I)
#define _simd_s64x2__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_extract_x8_instruction_set>()
#else
#define _simd_s64x2_extract_x8(X,I) _simd_s64x2_extract_x8_safe(X,I)
#define _simd_s64x2__extract_x8_enable() true
#endif _simd_s64x2_extract_x8_

#define _simd_s64x2_insert_x8_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s64x1) * 8)
#ifdef _simd_s64x2_insert_x8_
#define _simd_s64x2_insert_x8(X,I,Y) _simd_s64x2_insert_x8_(X,I,Y)
#define _simd_s64x2__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_insert_x8_instruction_set>()
#else
#define _simd_s64x2_insert_x8(X,I,Y) _simd_s64x2_insert_x8_safe(X,I,Y)
#define _simd_s64x2__insert_x8_enable() true
#endif _simd_s64x2_insert_x8_

#define _simd_s64x2_extract_x16_safe(X,I) _simd_s64x2_insert_x2_safe(_simd_s64x2_fill_undefined_safe(),0,X)
#ifdef _simd_s64x2_extract_x16_
#define _simd_s64x2_extract_x16(X,I) _simd_s64x2_extract_x16_(X,I)
#define _simd_s64x2__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_extract_x16_instruction_set>()
#else
#define _simd_s64x2_extract_x16(X,I) _simd_s64x2_extract_x16_safe(X,I)
#define _simd_s64x2__extract_x16_enable() true
#endif _simd_s64x2_extract_x16_

#define _simd_s64x2_insert_x16_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s64x1) * 16)
#ifdef _simd_s64x2_insert_x16_
#define _simd_s64x2_insert_x16(X,I,Y) _simd_s64x2_insert_x16_(X,I,Y)
#define _simd_s64x2__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_insert_x16_instruction_set>()
#else
#define _simd_s64x2_insert_x16(X,I,Y) _simd_s64x2_insert_x16_safe(X,I,Y)
#define _simd_s64x2__insert_x16_enable() true
#endif _simd_s64x2_insert_x16_

#define _simd_s64x2_extract_x32_safe(X,I) _simd_s64x2_insert_x2_safe(_simd_s64x2_fill_undefined_safe(),0,X)
#ifdef _simd_s64x2_extract_x32_
#define _simd_s64x2_extract_x32(X,I) _simd_s64x2_extract_x32_(X,I)
#define _simd_s64x2__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_extract_x32_instruction_set>()
#else
#define _simd_s64x2_extract_x32(X,I) _simd_s64x2_extract_x32_safe(X,I)
#define _simd_s64x2__extract_x32_enable() true
#endif _simd_s64x2_extract_x32_

#define _simd_s64x2_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s64x1) * 32)
#ifdef _simd_s64x2_insert_x32_
#define _simd_s64x2_insert_x32(X,I,Y) _simd_s64x2_insert_x32_(X,I,Y)
#define _simd_s64x2__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_insert_x32_instruction_set>()
#else
#define _simd_s64x2_insert_x32(X,I,Y) _simd_s64x2_insert_x32_safe(X,I,Y)
#define _simd_s64x2__insert_x32_enable() true
#endif _simd_s64x2_insert_x32_

#define _simd_s64x2_extract_x64_safe(X,I) _simd_s64x2_insert_x2_safe(_simd_s64x2_fill_undefined_safe(),0,X)
#ifdef _simd_s64x2_extract_x64_
#define _simd_s64x2_extract_x64(X,I) _simd_s64x2_extract_x64_(X,I)
#define _simd_s64x2__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_extract_x64_instruction_set>()
#else
#define _simd_s64x2_extract_x64(X,I) _simd_s64x2_extract_x64_safe(X,I)
#define _simd_s64x2__extract_x64_enable() true
#endif _simd_s64x2_extract_x64_

#define _simd_s64x2_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s64x1) * 64)
#ifdef _simd_s64x2_insert_x64_
#define _simd_s64x2_insert_x64(X,I,Y) _simd_s64x2_insert_x64_(X,I,Y)
#define _simd_s64x2__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_insert_x64_instruction_set>()
#else
#define _simd_s64x2_insert_x64(X,I,Y) _simd_s64x2_insert_x64_safe(X,I,Y)
#define _simd_s64x2__insert_x64_enable() true
#endif _simd_s64x2_insert_x64_

#define _simd_s64x2_extract_safe(X,I) _simd_s64x2_extract_x1_safe(X,I)
#define _simd_s64x2_extract(X,I) _simd_s64x2_extract_x1(X,I)
#define _simd_s64x2_extract_enable() _simd_s64x2_extract_x1_enable()

#define _simd_s64x2_insert_safe(X,I,Y) _simd_s64x2_insert_x1_safe(X,I,Y)
#define _simd_s64x2_insert(X,I,Y) _simd_s64x2_insert_x1(X,I,Y)
#define _simd_s64x2_insert_enable() _simd_s64x2_insert_x1_enable()

//#ifndef _simd_s64x2_splitlo
//	#define _simd_s64x2_splitlo(X) _simd_s64x1_extract_x1(X,0)
//	#define _simd_s64x2_splitlo_enable() _simd_s64x1_extract_x1_enable()
//#endif

//#ifndef _simd_s64x2_splithi
//	#define _simd_s64x2_splithi(X) _simd_s64x1_extract_x1(X,1)
//	#define _simd_s64x2_splithi_enable() _simd_s64x1_extract_x1_enable()
//#endif

//#ifndef _simd_s64x2_combine
//	#define _simd_s64x2_combine(X,Y) _simd_s64x2_insert_x1(_simd_s64x2_insert_x1(_simd_s64x2_fill_undefined(), 0, X), 1, Y)
//	#define _simd_s64x2_combine_enable() (_simd_s64x2_insert_x1_enable() && _simd_s64x2_fill_undefined_enable())
//#endif

#define _simd_s64x4_extract_x1_safe(X,I) (reinterpret_cast<const _simd_s64x4*>(&X)[I])
#ifdef _simd_s64x4_extract_x1_
#define _simd_s64x4_extract_x1(X,I) _simd_s64x4_extract_x1_(X,I)
#define _simd_s64x4__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_extract_x1_instruction_set>()
#else
#define _simd_s64x4_extract_x1(X,I) _simd_s64x4_extract_x1_safe(X,I)
#define _simd_s64x4__extract_x1_enable() true
#endif _simd_s64x4_extract_x1_

#define _simd_s64x4_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_s64x4*>(&X)[I] = Y)
#ifdef _simd_s64x4_insert_x1_
#define _simd_s64x4_insert_x1(X,I,Y) _simd_s64x4_insert_x1_(X,I,Y)
#define _simd_s64x4__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_insert_x1_instruction_set>()
#else
#define _simd_s64x4_insert_x1(X,I,Y) _simd_s64x4_insert_x1_safe(X,I,Y)
#define _simd_s64x4__insert_x1_enable() true
#endif _simd_s64x4_insert_x1_

#define _simd_s64x4_extract_x2_safe(X,I) (reinterpret_cast<const _simd_s64x4*>(&X)[I])
#ifdef _simd_s64x4_extract_x2_
#define _simd_s64x4_extract_x2(X,I) _simd_s64x4_extract_x2_(X,I)
#define _simd_s64x4__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_extract_x2_instruction_set>()
#else
#define _simd_s64x4_extract_x2(X,I) _simd_s64x4_extract_x2_safe(X,I)
#define _simd_s64x4__extract_x2_enable() true
#endif _simd_s64x4_extract_x2_

#define _simd_s64x4_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_s64x4*>(&X)[I] = Y)
#ifdef _simd_s64x4_insert_x2_
#define _simd_s64x4_insert_x2(X,I,Y) _simd_s64x4_insert_x2_(X,I,Y)
#define _simd_s64x4__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_insert_x2_instruction_set>()
#else
#define _simd_s64x4_insert_x2(X,I,Y) _simd_s64x4_insert_x2_safe(X,I,Y)
#define _simd_s64x4__insert_x2_enable() true
#endif _simd_s64x4_insert_x2_

#define _simd_s64x4_extract_x8_safe(X,I) _simd_s64x4_insert_x4_safe(_simd_s64x4_fill_undefined_safe(),0,X)
#ifdef _simd_s64x4_extract_x8_
#define _simd_s64x4_extract_x8(X,I) _simd_s64x4_extract_x8_(X,I)
#define _simd_s64x4__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_extract_x8_instruction_set>()
#else
#define _simd_s64x4_extract_x8(X,I) _simd_s64x4_extract_x8_safe(X,I)
#define _simd_s64x4__extract_x8_enable() true
#endif _simd_s64x4_extract_x8_

#define _simd_s64x4_insert_x8_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s64x1) * 8)
#ifdef _simd_s64x4_insert_x8_
#define _simd_s64x4_insert_x8(X,I,Y) _simd_s64x4_insert_x8_(X,I,Y)
#define _simd_s64x4__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_insert_x8_instruction_set>()
#else
#define _simd_s64x4_insert_x8(X,I,Y) _simd_s64x4_insert_x8_safe(X,I,Y)
#define _simd_s64x4__insert_x8_enable() true
#endif _simd_s64x4_insert_x8_

#define _simd_s64x4_extract_x16_safe(X,I) _simd_s64x4_insert_x4_safe(_simd_s64x4_fill_undefined_safe(),0,X)
#ifdef _simd_s64x4_extract_x16_
#define _simd_s64x4_extract_x16(X,I) _simd_s64x4_extract_x16_(X,I)
#define _simd_s64x4__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_extract_x16_instruction_set>()
#else
#define _simd_s64x4_extract_x16(X,I) _simd_s64x4_extract_x16_safe(X,I)
#define _simd_s64x4__extract_x16_enable() true
#endif _simd_s64x4_extract_x16_

#define _simd_s64x4_insert_x16_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s64x1) * 16)
#ifdef _simd_s64x4_insert_x16_
#define _simd_s64x4_insert_x16(X,I,Y) _simd_s64x4_insert_x16_(X,I,Y)
#define _simd_s64x4__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_insert_x16_instruction_set>()
#else
#define _simd_s64x4_insert_x16(X,I,Y) _simd_s64x4_insert_x16_safe(X,I,Y)
#define _simd_s64x4__insert_x16_enable() true
#endif _simd_s64x4_insert_x16_

#define _simd_s64x4_extract_x32_safe(X,I) _simd_s64x4_insert_x4_safe(_simd_s64x4_fill_undefined_safe(),0,X)
#ifdef _simd_s64x4_extract_x32_
#define _simd_s64x4_extract_x32(X,I) _simd_s64x4_extract_x32_(X,I)
#define _simd_s64x4__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_extract_x32_instruction_set>()
#else
#define _simd_s64x4_extract_x32(X,I) _simd_s64x4_extract_x32_safe(X,I)
#define _simd_s64x4__extract_x32_enable() true
#endif _simd_s64x4_extract_x32_

#define _simd_s64x4_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s64x1) * 32)
#ifdef _simd_s64x4_insert_x32_
#define _simd_s64x4_insert_x32(X,I,Y) _simd_s64x4_insert_x32_(X,I,Y)
#define _simd_s64x4__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_insert_x32_instruction_set>()
#else
#define _simd_s64x4_insert_x32(X,I,Y) _simd_s64x4_insert_x32_safe(X,I,Y)
#define _simd_s64x4__insert_x32_enable() true
#endif _simd_s64x4_insert_x32_

#define _simd_s64x4_extract_x64_safe(X,I) _simd_s64x4_insert_x4_safe(_simd_s64x4_fill_undefined_safe(),0,X)
#ifdef _simd_s64x4_extract_x64_
#define _simd_s64x4_extract_x64(X,I) _simd_s64x4_extract_x64_(X,I)
#define _simd_s64x4__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_extract_x64_instruction_set>()
#else
#define _simd_s64x4_extract_x64(X,I) _simd_s64x4_extract_x64_safe(X,I)
#define _simd_s64x4__extract_x64_enable() true
#endif _simd_s64x4_extract_x64_

#define _simd_s64x4_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s64x1) * 64)
#ifdef _simd_s64x4_insert_x64_
#define _simd_s64x4_insert_x64(X,I,Y) _simd_s64x4_insert_x64_(X,I,Y)
#define _simd_s64x4__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_insert_x64_instruction_set>()
#else
#define _simd_s64x4_insert_x64(X,I,Y) _simd_s64x4_insert_x64_safe(X,I,Y)
#define _simd_s64x4__insert_x64_enable() true
#endif _simd_s64x4_insert_x64_

#define _simd_s64x4_extract_safe(X,I) _simd_s64x4_extract_x1_safe(X,I)
#define _simd_s64x4_extract(X,I) _simd_s64x4_extract_x1(X,I)
#define _simd_s64x4_extract_enable() _simd_s64x4_extract_x1_enable()

#define _simd_s64x4_insert_safe(X,I,Y) _simd_s64x4_insert_x1_safe(X,I,Y)
#define _simd_s64x4_insert(X,I,Y) _simd_s64x4_insert_x1(X,I,Y)
#define _simd_s64x4_insert_enable() _simd_s64x4_insert_x1_enable()

//#ifndef _simd_s64x4_splitlo
//	#define _simd_s64x4_splitlo(X) _simd_s64x2_extract_x2(X,0)
//	#define _simd_s64x4_splitlo_enable() _simd_s64x2_extract_x2_enable()
//#endif

//#ifndef _simd_s64x4_splithi
//	#define _simd_s64x4_splithi(X) _simd_s64x2_extract_x2(X,1)
//	#define _simd_s64x4_splithi_enable() _simd_s64x2_extract_x2_enable()
//#endif

//#ifndef _simd_s64x4_combine
//	#define _simd_s64x4_combine(X,Y) _simd_s64x4_insert_x2(_simd_s64x4_insert_x2(_simd_s64x4_fill_undefined(), 0, X), 1, Y)
//	#define _simd_s64x4_combine_enable() (_simd_s64x4_insert_x2_enable() && _simd_s64x4_fill_undefined_enable())
//#endif

#define _simd_s64x8_extract_x1_safe(X,I) (reinterpret_cast<const _simd_s64x8*>(&X)[I])
#ifdef _simd_s64x8_extract_x1_
#define _simd_s64x8_extract_x1(X,I) _simd_s64x8_extract_x1_(X,I)
#define _simd_s64x8__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_extract_x1_instruction_set>()
#else
#define _simd_s64x8_extract_x1(X,I) _simd_s64x8_extract_x1_safe(X,I)
#define _simd_s64x8__extract_x1_enable() true
#endif _simd_s64x8_extract_x1_

#define _simd_s64x8_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_s64x8*>(&X)[I] = Y)
#ifdef _simd_s64x8_insert_x1_
#define _simd_s64x8_insert_x1(X,I,Y) _simd_s64x8_insert_x1_(X,I,Y)
#define _simd_s64x8__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_insert_x1_instruction_set>()
#else
#define _simd_s64x8_insert_x1(X,I,Y) _simd_s64x8_insert_x1_safe(X,I,Y)
#define _simd_s64x8__insert_x1_enable() true
#endif _simd_s64x8_insert_x1_

#define _simd_s64x8_extract_x2_safe(X,I) (reinterpret_cast<const _simd_s64x8*>(&X)[I])
#ifdef _simd_s64x8_extract_x2_
#define _simd_s64x8_extract_x2(X,I) _simd_s64x8_extract_x2_(X,I)
#define _simd_s64x8__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_extract_x2_instruction_set>()
#else
#define _simd_s64x8_extract_x2(X,I) _simd_s64x8_extract_x2_safe(X,I)
#define _simd_s64x8__extract_x2_enable() true
#endif _simd_s64x8_extract_x2_

#define _simd_s64x8_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_s64x8*>(&X)[I] = Y)
#ifdef _simd_s64x8_insert_x2_
#define _simd_s64x8_insert_x2(X,I,Y) _simd_s64x8_insert_x2_(X,I,Y)
#define _simd_s64x8__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_insert_x2_instruction_set>()
#else
#define _simd_s64x8_insert_x2(X,I,Y) _simd_s64x8_insert_x2_safe(X,I,Y)
#define _simd_s64x8__insert_x2_enable() true
#endif _simd_s64x8_insert_x2_

#define _simd_s64x8_extract_x4_safe(X,I) (reinterpret_cast<const _simd_s64x8*>(&X)[I])
#ifdef _simd_s64x8_extract_x4_
#define _simd_s64x8_extract_x4(X,I) _simd_s64x8_extract_x4_(X,I)
#define _simd_s64x8__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_extract_x4_instruction_set>()
#else
#define _simd_s64x8_extract_x4(X,I) _simd_s64x8_extract_x4_safe(X,I)
#define _simd_s64x8__extract_x4_enable() true
#endif _simd_s64x8_extract_x4_

#define _simd_s64x8_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_s64x8*>(&X)[I] = Y)
#ifdef _simd_s64x8_insert_x4_
#define _simd_s64x8_insert_x4(X,I,Y) _simd_s64x8_insert_x4_(X,I,Y)
#define _simd_s64x8__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_insert_x4_instruction_set>()
#else
#define _simd_s64x8_insert_x4(X,I,Y) _simd_s64x8_insert_x4_safe(X,I,Y)
#define _simd_s64x8__insert_x4_enable() true
#endif _simd_s64x8_insert_x4_

#define _simd_s64x8_extract_x16_safe(X,I) _simd_s64x8_insert_x8_safe(_simd_s64x8_fill_undefined_safe(),0,X)
#ifdef _simd_s64x8_extract_x16_
#define _simd_s64x8_extract_x16(X,I) _simd_s64x8_extract_x16_(X,I)
#define _simd_s64x8__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_extract_x16_instruction_set>()
#else
#define _simd_s64x8_extract_x16(X,I) _simd_s64x8_extract_x16_safe(X,I)
#define _simd_s64x8__extract_x16_enable() true
#endif _simd_s64x8_extract_x16_

#define _simd_s64x8_insert_x16_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s64x1) * 16)
#ifdef _simd_s64x8_insert_x16_
#define _simd_s64x8_insert_x16(X,I,Y) _simd_s64x8_insert_x16_(X,I,Y)
#define _simd_s64x8__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_insert_x16_instruction_set>()
#else
#define _simd_s64x8_insert_x16(X,I,Y) _simd_s64x8_insert_x16_safe(X,I,Y)
#define _simd_s64x8__insert_x16_enable() true
#endif _simd_s64x8_insert_x16_

#define _simd_s64x8_extract_x32_safe(X,I) _simd_s64x8_insert_x8_safe(_simd_s64x8_fill_undefined_safe(),0,X)
#ifdef _simd_s64x8_extract_x32_
#define _simd_s64x8_extract_x32(X,I) _simd_s64x8_extract_x32_(X,I)
#define _simd_s64x8__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_extract_x32_instruction_set>()
#else
#define _simd_s64x8_extract_x32(X,I) _simd_s64x8_extract_x32_safe(X,I)
#define _simd_s64x8__extract_x32_enable() true
#endif _simd_s64x8_extract_x32_

#define _simd_s64x8_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s64x1) * 32)
#ifdef _simd_s64x8_insert_x32_
#define _simd_s64x8_insert_x32(X,I,Y) _simd_s64x8_insert_x32_(X,I,Y)
#define _simd_s64x8__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_insert_x32_instruction_set>()
#else
#define _simd_s64x8_insert_x32(X,I,Y) _simd_s64x8_insert_x32_safe(X,I,Y)
#define _simd_s64x8__insert_x32_enable() true
#endif _simd_s64x8_insert_x32_

#define _simd_s64x8_extract_x64_safe(X,I) _simd_s64x8_insert_x8_safe(_simd_s64x8_fill_undefined_safe(),0,X)
#ifdef _simd_s64x8_extract_x64_
#define _simd_s64x8_extract_x64(X,I) _simd_s64x8_extract_x64_(X,I)
#define _simd_s64x8__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_extract_x64_instruction_set>()
#else
#define _simd_s64x8_extract_x64(X,I) _simd_s64x8_extract_x64_safe(X,I)
#define _simd_s64x8__extract_x64_enable() true
#endif _simd_s64x8_extract_x64_

#define _simd_s64x8_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s64x1) * 64)
#ifdef _simd_s64x8_insert_x64_
#define _simd_s64x8_insert_x64(X,I,Y) _simd_s64x8_insert_x64_(X,I,Y)
#define _simd_s64x8__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_insert_x64_instruction_set>()
#else
#define _simd_s64x8_insert_x64(X,I,Y) _simd_s64x8_insert_x64_safe(X,I,Y)
#define _simd_s64x8__insert_x64_enable() true
#endif _simd_s64x8_insert_x64_

#define _simd_s64x8_extract_safe(X,I) _simd_s64x8_extract_x1_safe(X,I)
#define _simd_s64x8_extract(X,I) _simd_s64x8_extract_x1(X,I)
#define _simd_s64x8_extract_enable() _simd_s64x8_extract_x1_enable()

#define _simd_s64x8_insert_safe(X,I,Y) _simd_s64x8_insert_x1_safe(X,I,Y)
#define _simd_s64x8_insert(X,I,Y) _simd_s64x8_insert_x1(X,I,Y)
#define _simd_s64x8_insert_enable() _simd_s64x8_insert_x1_enable()

//#ifndef _simd_s64x8_splitlo
//	#define _simd_s64x8_splitlo(X) _simd_s64x4_extract_x4(X,0)
//	#define _simd_s64x8_splitlo_enable() _simd_s64x4_extract_x4_enable()
//#endif

//#ifndef _simd_s64x8_splithi
//	#define _simd_s64x8_splithi(X) _simd_s64x4_extract_x4(X,1)
//	#define _simd_s64x8_splithi_enable() _simd_s64x4_extract_x4_enable()
//#endif

//#ifndef _simd_s64x8_combine
//	#define _simd_s64x8_combine(X,Y) _simd_s64x8_insert_x4(_simd_s64x8_insert_x4(_simd_s64x8_fill_undefined(), 0, X), 1, Y)
//	#define _simd_s64x8_combine_enable() (_simd_s64x8_insert_x4_enable() && _simd_s64x8_fill_undefined_enable())
//#endif

#define _simd_s64x16_extract_x1_safe(X,I) (reinterpret_cast<const _simd_s64x16*>(&X)[I])
#ifdef _simd_s64x16_extract_x1_
#define _simd_s64x16_extract_x1(X,I) _simd_s64x16_extract_x1_(X,I)
#define _simd_s64x16__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_extract_x1_instruction_set>()
#else
#define _simd_s64x16_extract_x1(X,I) _simd_s64x16_extract_x1_safe(X,I)
#define _simd_s64x16__extract_x1_enable() true
#endif _simd_s64x16_extract_x1_

#define _simd_s64x16_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_s64x16*>(&X)[I] = Y)
#ifdef _simd_s64x16_insert_x1_
#define _simd_s64x16_insert_x1(X,I,Y) _simd_s64x16_insert_x1_(X,I,Y)
#define _simd_s64x16__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_insert_x1_instruction_set>()
#else
#define _simd_s64x16_insert_x1(X,I,Y) _simd_s64x16_insert_x1_safe(X,I,Y)
#define _simd_s64x16__insert_x1_enable() true
#endif _simd_s64x16_insert_x1_

#define _simd_s64x16_extract_x2_safe(X,I) (reinterpret_cast<const _simd_s64x16*>(&X)[I])
#ifdef _simd_s64x16_extract_x2_
#define _simd_s64x16_extract_x2(X,I) _simd_s64x16_extract_x2_(X,I)
#define _simd_s64x16__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_extract_x2_instruction_set>()
#else
#define _simd_s64x16_extract_x2(X,I) _simd_s64x16_extract_x2_safe(X,I)
#define _simd_s64x16__extract_x2_enable() true
#endif _simd_s64x16_extract_x2_

#define _simd_s64x16_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_s64x16*>(&X)[I] = Y)
#ifdef _simd_s64x16_insert_x2_
#define _simd_s64x16_insert_x2(X,I,Y) _simd_s64x16_insert_x2_(X,I,Y)
#define _simd_s64x16__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_insert_x2_instruction_set>()
#else
#define _simd_s64x16_insert_x2(X,I,Y) _simd_s64x16_insert_x2_safe(X,I,Y)
#define _simd_s64x16__insert_x2_enable() true
#endif _simd_s64x16_insert_x2_

#define _simd_s64x16_extract_x4_safe(X,I) (reinterpret_cast<const _simd_s64x16*>(&X)[I])
#ifdef _simd_s64x16_extract_x4_
#define _simd_s64x16_extract_x4(X,I) _simd_s64x16_extract_x4_(X,I)
#define _simd_s64x16__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_extract_x4_instruction_set>()
#else
#define _simd_s64x16_extract_x4(X,I) _simd_s64x16_extract_x4_safe(X,I)
#define _simd_s64x16__extract_x4_enable() true
#endif _simd_s64x16_extract_x4_

#define _simd_s64x16_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_s64x16*>(&X)[I] = Y)
#ifdef _simd_s64x16_insert_x4_
#define _simd_s64x16_insert_x4(X,I,Y) _simd_s64x16_insert_x4_(X,I,Y)
#define _simd_s64x16__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_insert_x4_instruction_set>()
#else
#define _simd_s64x16_insert_x4(X,I,Y) _simd_s64x16_insert_x4_safe(X,I,Y)
#define _simd_s64x16__insert_x4_enable() true
#endif _simd_s64x16_insert_x4_

#define _simd_s64x16_extract_x8_safe(X,I) (reinterpret_cast<const _simd_s64x16*>(&X)[I])
#ifdef _simd_s64x16_extract_x8_
#define _simd_s64x16_extract_x8(X,I) _simd_s64x16_extract_x8_(X,I)
#define _simd_s64x16__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_extract_x8_instruction_set>()
#else
#define _simd_s64x16_extract_x8(X,I) _simd_s64x16_extract_x8_safe(X,I)
#define _simd_s64x16__extract_x8_enable() true
#endif _simd_s64x16_extract_x8_

#define _simd_s64x16_insert_x8_safe(X,I,Y) (reinterpret_cast<_simd_s64x16*>(&X)[I] = Y)
#ifdef _simd_s64x16_insert_x8_
#define _simd_s64x16_insert_x8(X,I,Y) _simd_s64x16_insert_x8_(X,I,Y)
#define _simd_s64x16__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_insert_x8_instruction_set>()
#else
#define _simd_s64x16_insert_x8(X,I,Y) _simd_s64x16_insert_x8_safe(X,I,Y)
#define _simd_s64x16__insert_x8_enable() true
#endif _simd_s64x16_insert_x8_

#define _simd_s64x16_extract_x32_safe(X,I) _simd_s64x16_insert_x16_safe(_simd_s64x16_fill_undefined_safe(),0,X)
#ifdef _simd_s64x16_extract_x32_
#define _simd_s64x16_extract_x32(X,I) _simd_s64x16_extract_x32_(X,I)
#define _simd_s64x16__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_extract_x32_instruction_set>()
#else
#define _simd_s64x16_extract_x32(X,I) _simd_s64x16_extract_x32_safe(X,I)
#define _simd_s64x16__extract_x32_enable() true
#endif _simd_s64x16_extract_x32_

#define _simd_s64x16_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s64x1) * 32)
#ifdef _simd_s64x16_insert_x32_
#define _simd_s64x16_insert_x32(X,I,Y) _simd_s64x16_insert_x32_(X,I,Y)
#define _simd_s64x16__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_insert_x32_instruction_set>()
#else
#define _simd_s64x16_insert_x32(X,I,Y) _simd_s64x16_insert_x32_safe(X,I,Y)
#define _simd_s64x16__insert_x32_enable() true
#endif _simd_s64x16_insert_x32_

#define _simd_s64x16_extract_x64_safe(X,I) _simd_s64x16_insert_x16_safe(_simd_s64x16_fill_undefined_safe(),0,X)
#ifdef _simd_s64x16_extract_x64_
#define _simd_s64x16_extract_x64(X,I) _simd_s64x16_extract_x64_(X,I)
#define _simd_s64x16__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_extract_x64_instruction_set>()
#else
#define _simd_s64x16_extract_x64(X,I) _simd_s64x16_extract_x64_safe(X,I)
#define _simd_s64x16__extract_x64_enable() true
#endif _simd_s64x16_extract_x64_

#define _simd_s64x16_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s64x1) * 64)
#ifdef _simd_s64x16_insert_x64_
#define _simd_s64x16_insert_x64(X,I,Y) _simd_s64x16_insert_x64_(X,I,Y)
#define _simd_s64x16__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_insert_x64_instruction_set>()
#else
#define _simd_s64x16_insert_x64(X,I,Y) _simd_s64x16_insert_x64_safe(X,I,Y)
#define _simd_s64x16__insert_x64_enable() true
#endif _simd_s64x16_insert_x64_

#define _simd_s64x16_extract_safe(X,I) _simd_s64x16_extract_x1_safe(X,I)
#define _simd_s64x16_extract(X,I) _simd_s64x16_extract_x1(X,I)
#define _simd_s64x16_extract_enable() _simd_s64x16_extract_x1_enable()

#define _simd_s64x16_insert_safe(X,I,Y) _simd_s64x16_insert_x1_safe(X,I,Y)
#define _simd_s64x16_insert(X,I,Y) _simd_s64x16_insert_x1(X,I,Y)
#define _simd_s64x16_insert_enable() _simd_s64x16_insert_x1_enable()

//#ifndef _simd_s64x16_splitlo
//	#define _simd_s64x16_splitlo(X) _simd_s64x8_extract_x8(X,0)
//	#define _simd_s64x16_splitlo_enable() _simd_s64x8_extract_x8_enable()
//#endif

//#ifndef _simd_s64x16_splithi
//	#define _simd_s64x16_splithi(X) _simd_s64x8_extract_x8(X,1)
//	#define _simd_s64x16_splithi_enable() _simd_s64x8_extract_x8_enable()
//#endif

//#ifndef _simd_s64x16_combine
//	#define _simd_s64x16_combine(X,Y) _simd_s64x16_insert_x8(_simd_s64x16_insert_x8(_simd_s64x16_fill_undefined(), 0, X), 1, Y)
//	#define _simd_s64x16_combine_enable() (_simd_s64x16_insert_x8_enable() && _simd_s64x16_fill_undefined_enable())
//#endif

#define _simd_s64x32_extract_x1_safe(X,I) (reinterpret_cast<const _simd_s64x32*>(&X)[I])
#ifdef _simd_s64x32_extract_x1_
#define _simd_s64x32_extract_x1(X,I) _simd_s64x32_extract_x1_(X,I)
#define _simd_s64x32__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_extract_x1_instruction_set>()
#else
#define _simd_s64x32_extract_x1(X,I) _simd_s64x32_extract_x1_safe(X,I)
#define _simd_s64x32__extract_x1_enable() true
#endif _simd_s64x32_extract_x1_

#define _simd_s64x32_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_s64x32*>(&X)[I] = Y)
#ifdef _simd_s64x32_insert_x1_
#define _simd_s64x32_insert_x1(X,I,Y) _simd_s64x32_insert_x1_(X,I,Y)
#define _simd_s64x32__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_insert_x1_instruction_set>()
#else
#define _simd_s64x32_insert_x1(X,I,Y) _simd_s64x32_insert_x1_safe(X,I,Y)
#define _simd_s64x32__insert_x1_enable() true
#endif _simd_s64x32_insert_x1_

#define _simd_s64x32_extract_x2_safe(X,I) (reinterpret_cast<const _simd_s64x32*>(&X)[I])
#ifdef _simd_s64x32_extract_x2_
#define _simd_s64x32_extract_x2(X,I) _simd_s64x32_extract_x2_(X,I)
#define _simd_s64x32__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_extract_x2_instruction_set>()
#else
#define _simd_s64x32_extract_x2(X,I) _simd_s64x32_extract_x2_safe(X,I)
#define _simd_s64x32__extract_x2_enable() true
#endif _simd_s64x32_extract_x2_

#define _simd_s64x32_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_s64x32*>(&X)[I] = Y)
#ifdef _simd_s64x32_insert_x2_
#define _simd_s64x32_insert_x2(X,I,Y) _simd_s64x32_insert_x2_(X,I,Y)
#define _simd_s64x32__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_insert_x2_instruction_set>()
#else
#define _simd_s64x32_insert_x2(X,I,Y) _simd_s64x32_insert_x2_safe(X,I,Y)
#define _simd_s64x32__insert_x2_enable() true
#endif _simd_s64x32_insert_x2_

#define _simd_s64x32_extract_x4_safe(X,I) (reinterpret_cast<const _simd_s64x32*>(&X)[I])
#ifdef _simd_s64x32_extract_x4_
#define _simd_s64x32_extract_x4(X,I) _simd_s64x32_extract_x4_(X,I)
#define _simd_s64x32__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_extract_x4_instruction_set>()
#else
#define _simd_s64x32_extract_x4(X,I) _simd_s64x32_extract_x4_safe(X,I)
#define _simd_s64x32__extract_x4_enable() true
#endif _simd_s64x32_extract_x4_

#define _simd_s64x32_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_s64x32*>(&X)[I] = Y)
#ifdef _simd_s64x32_insert_x4_
#define _simd_s64x32_insert_x4(X,I,Y) _simd_s64x32_insert_x4_(X,I,Y)
#define _simd_s64x32__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_insert_x4_instruction_set>()
#else
#define _simd_s64x32_insert_x4(X,I,Y) _simd_s64x32_insert_x4_safe(X,I,Y)
#define _simd_s64x32__insert_x4_enable() true
#endif _simd_s64x32_insert_x4_

#define _simd_s64x32_extract_x8_safe(X,I) (reinterpret_cast<const _simd_s64x32*>(&X)[I])
#ifdef _simd_s64x32_extract_x8_
#define _simd_s64x32_extract_x8(X,I) _simd_s64x32_extract_x8_(X,I)
#define _simd_s64x32__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_extract_x8_instruction_set>()
#else
#define _simd_s64x32_extract_x8(X,I) _simd_s64x32_extract_x8_safe(X,I)
#define _simd_s64x32__extract_x8_enable() true
#endif _simd_s64x32_extract_x8_

#define _simd_s64x32_insert_x8_safe(X,I,Y) (reinterpret_cast<_simd_s64x32*>(&X)[I] = Y)
#ifdef _simd_s64x32_insert_x8_
#define _simd_s64x32_insert_x8(X,I,Y) _simd_s64x32_insert_x8_(X,I,Y)
#define _simd_s64x32__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_insert_x8_instruction_set>()
#else
#define _simd_s64x32_insert_x8(X,I,Y) _simd_s64x32_insert_x8_safe(X,I,Y)
#define _simd_s64x32__insert_x8_enable() true
#endif _simd_s64x32_insert_x8_

#define _simd_s64x32_extract_x16_safe(X,I) (reinterpret_cast<const _simd_s64x32*>(&X)[I])
#ifdef _simd_s64x32_extract_x16_
#define _simd_s64x32_extract_x16(X,I) _simd_s64x32_extract_x16_(X,I)
#define _simd_s64x32__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_extract_x16_instruction_set>()
#else
#define _simd_s64x32_extract_x16(X,I) _simd_s64x32_extract_x16_safe(X,I)
#define _simd_s64x32__extract_x16_enable() true
#endif _simd_s64x32_extract_x16_

#define _simd_s64x32_insert_x16_safe(X,I,Y) (reinterpret_cast<_simd_s64x32*>(&X)[I] = Y)
#ifdef _simd_s64x32_insert_x16_
#define _simd_s64x32_insert_x16(X,I,Y) _simd_s64x32_insert_x16_(X,I,Y)
#define _simd_s64x32__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_insert_x16_instruction_set>()
#else
#define _simd_s64x32_insert_x16(X,I,Y) _simd_s64x32_insert_x16_safe(X,I,Y)
#define _simd_s64x32__insert_x16_enable() true
#endif _simd_s64x32_insert_x16_

#define _simd_s64x32_extract_x64_safe(X,I) _simd_s64x32_insert_x32_safe(_simd_s64x32_fill_undefined_safe(),0,X)
#ifdef _simd_s64x32_extract_x64_
#define _simd_s64x32_extract_x64(X,I) _simd_s64x32_extract_x64_(X,I)
#define _simd_s64x32__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_extract_x64_instruction_set>()
#else
#define _simd_s64x32_extract_x64(X,I) _simd_s64x32_extract_x64_safe(X,I)
#define _simd_s64x32__extract_x64_enable() true
#endif _simd_s64x32_extract_x64_

#define _simd_s64x32_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s64x1) * 64)
#ifdef _simd_s64x32_insert_x64_
#define _simd_s64x32_insert_x64(X,I,Y) _simd_s64x32_insert_x64_(X,I,Y)
#define _simd_s64x32__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_insert_x64_instruction_set>()
#else
#define _simd_s64x32_insert_x64(X,I,Y) _simd_s64x32_insert_x64_safe(X,I,Y)
#define _simd_s64x32__insert_x64_enable() true
#endif _simd_s64x32_insert_x64_

#define _simd_s64x32_extract_safe(X,I) _simd_s64x32_extract_x1_safe(X,I)
#define _simd_s64x32_extract(X,I) _simd_s64x32_extract_x1(X,I)
#define _simd_s64x32_extract_enable() _simd_s64x32_extract_x1_enable()

#define _simd_s64x32_insert_safe(X,I,Y) _simd_s64x32_insert_x1_safe(X,I,Y)
#define _simd_s64x32_insert(X,I,Y) _simd_s64x32_insert_x1(X,I,Y)
#define _simd_s64x32_insert_enable() _simd_s64x32_insert_x1_enable()

//#ifndef _simd_s64x32_splitlo
//	#define _simd_s64x32_splitlo(X) _simd_s64x16_extract_x16(X,0)
//	#define _simd_s64x32_splitlo_enable() _simd_s64x16_extract_x16_enable()
//#endif

//#ifndef _simd_s64x32_splithi
//	#define _simd_s64x32_splithi(X) _simd_s64x16_extract_x16(X,1)
//	#define _simd_s64x32_splithi_enable() _simd_s64x16_extract_x16_enable()
//#endif

//#ifndef _simd_s64x32_combine
//	#define _simd_s64x32_combine(X,Y) _simd_s64x32_insert_x16(_simd_s64x32_insert_x16(_simd_s64x32_fill_undefined(), 0, X), 1, Y)
//	#define _simd_s64x32_combine_enable() (_simd_s64x32_insert_x16_enable() && _simd_s64x32_fill_undefined_enable())
//#endif

#define _simd_s64x64_extract_x1_safe(X,I) (reinterpret_cast<const _simd_s64x64*>(&X)[I])
#ifdef _simd_s64x64_extract_x1_
#define _simd_s64x64_extract_x1(X,I) _simd_s64x64_extract_x1_(X,I)
#define _simd_s64x64__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_extract_x1_instruction_set>()
#else
#define _simd_s64x64_extract_x1(X,I) _simd_s64x64_extract_x1_safe(X,I)
#define _simd_s64x64__extract_x1_enable() true
#endif _simd_s64x64_extract_x1_

#define _simd_s64x64_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_s64x64*>(&X)[I] = Y)
#ifdef _simd_s64x64_insert_x1_
#define _simd_s64x64_insert_x1(X,I,Y) _simd_s64x64_insert_x1_(X,I,Y)
#define _simd_s64x64__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_insert_x1_instruction_set>()
#else
#define _simd_s64x64_insert_x1(X,I,Y) _simd_s64x64_insert_x1_safe(X,I,Y)
#define _simd_s64x64__insert_x1_enable() true
#endif _simd_s64x64_insert_x1_

#define _simd_s64x64_extract_x2_safe(X,I) (reinterpret_cast<const _simd_s64x64*>(&X)[I])
#ifdef _simd_s64x64_extract_x2_
#define _simd_s64x64_extract_x2(X,I) _simd_s64x64_extract_x2_(X,I)
#define _simd_s64x64__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_extract_x2_instruction_set>()
#else
#define _simd_s64x64_extract_x2(X,I) _simd_s64x64_extract_x2_safe(X,I)
#define _simd_s64x64__extract_x2_enable() true
#endif _simd_s64x64_extract_x2_

#define _simd_s64x64_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_s64x64*>(&X)[I] = Y)
#ifdef _simd_s64x64_insert_x2_
#define _simd_s64x64_insert_x2(X,I,Y) _simd_s64x64_insert_x2_(X,I,Y)
#define _simd_s64x64__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_insert_x2_instruction_set>()
#else
#define _simd_s64x64_insert_x2(X,I,Y) _simd_s64x64_insert_x2_safe(X,I,Y)
#define _simd_s64x64__insert_x2_enable() true
#endif _simd_s64x64_insert_x2_

#define _simd_s64x64_extract_x4_safe(X,I) (reinterpret_cast<const _simd_s64x64*>(&X)[I])
#ifdef _simd_s64x64_extract_x4_
#define _simd_s64x64_extract_x4(X,I) _simd_s64x64_extract_x4_(X,I)
#define _simd_s64x64__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_extract_x4_instruction_set>()
#else
#define _simd_s64x64_extract_x4(X,I) _simd_s64x64_extract_x4_safe(X,I)
#define _simd_s64x64__extract_x4_enable() true
#endif _simd_s64x64_extract_x4_

#define _simd_s64x64_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_s64x64*>(&X)[I] = Y)
#ifdef _simd_s64x64_insert_x4_
#define _simd_s64x64_insert_x4(X,I,Y) _simd_s64x64_insert_x4_(X,I,Y)
#define _simd_s64x64__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_insert_x4_instruction_set>()
#else
#define _simd_s64x64_insert_x4(X,I,Y) _simd_s64x64_insert_x4_safe(X,I,Y)
#define _simd_s64x64__insert_x4_enable() true
#endif _simd_s64x64_insert_x4_

#define _simd_s64x64_extract_x8_safe(X,I) (reinterpret_cast<const _simd_s64x64*>(&X)[I])
#ifdef _simd_s64x64_extract_x8_
#define _simd_s64x64_extract_x8(X,I) _simd_s64x64_extract_x8_(X,I)
#define _simd_s64x64__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_extract_x8_instruction_set>()
#else
#define _simd_s64x64_extract_x8(X,I) _simd_s64x64_extract_x8_safe(X,I)
#define _simd_s64x64__extract_x8_enable() true
#endif _simd_s64x64_extract_x8_

#define _simd_s64x64_insert_x8_safe(X,I,Y) (reinterpret_cast<_simd_s64x64*>(&X)[I] = Y)
#ifdef _simd_s64x64_insert_x8_
#define _simd_s64x64_insert_x8(X,I,Y) _simd_s64x64_insert_x8_(X,I,Y)
#define _simd_s64x64__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_insert_x8_instruction_set>()
#else
#define _simd_s64x64_insert_x8(X,I,Y) _simd_s64x64_insert_x8_safe(X,I,Y)
#define _simd_s64x64__insert_x8_enable() true
#endif _simd_s64x64_insert_x8_

#define _simd_s64x64_extract_x16_safe(X,I) (reinterpret_cast<const _simd_s64x64*>(&X)[I])
#ifdef _simd_s64x64_extract_x16_
#define _simd_s64x64_extract_x16(X,I) _simd_s64x64_extract_x16_(X,I)
#define _simd_s64x64__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_extract_x16_instruction_set>()
#else
#define _simd_s64x64_extract_x16(X,I) _simd_s64x64_extract_x16_safe(X,I)
#define _simd_s64x64__extract_x16_enable() true
#endif _simd_s64x64_extract_x16_

#define _simd_s64x64_insert_x16_safe(X,I,Y) (reinterpret_cast<_simd_s64x64*>(&X)[I] = Y)
#ifdef _simd_s64x64_insert_x16_
#define _simd_s64x64_insert_x16(X,I,Y) _simd_s64x64_insert_x16_(X,I,Y)
#define _simd_s64x64__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_insert_x16_instruction_set>()
#else
#define _simd_s64x64_insert_x16(X,I,Y) _simd_s64x64_insert_x16_safe(X,I,Y)
#define _simd_s64x64__insert_x16_enable() true
#endif _simd_s64x64_insert_x16_

#define _simd_s64x64_extract_x32_safe(X,I) (reinterpret_cast<const _simd_s64x64*>(&X)[I])
#ifdef _simd_s64x64_extract_x32_
#define _simd_s64x64_extract_x32(X,I) _simd_s64x64_extract_x32_(X,I)
#define _simd_s64x64__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_extract_x32_instruction_set>()
#else
#define _simd_s64x64_extract_x32(X,I) _simd_s64x64_extract_x32_safe(X,I)
#define _simd_s64x64__extract_x32_enable() true
#endif _simd_s64x64_extract_x32_

#define _simd_s64x64_insert_x32_safe(X,I,Y) (reinterpret_cast<_simd_s64x64*>(&X)[I] = Y)
#ifdef _simd_s64x64_insert_x32_
#define _simd_s64x64_insert_x32(X,I,Y) _simd_s64x64_insert_x32_(X,I,Y)
#define _simd_s64x64__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_insert_x32_instruction_set>()
#else
#define _simd_s64x64_insert_x32(X,I,Y) _simd_s64x64_insert_x32_safe(X,I,Y)
#define _simd_s64x64__insert_x32_enable() true
#endif _simd_s64x64_insert_x32_

#define _simd_s64x64_extract_safe(X,I) _simd_s64x64_extract_x1_safe(X,I)
#define _simd_s64x64_extract(X,I) _simd_s64x64_extract_x1(X,I)
#define _simd_s64x64_extract_enable() _simd_s64x64_extract_x1_enable()

#define _simd_s64x64_insert_safe(X,I,Y) _simd_s64x64_insert_x1_safe(X,I,Y)
#define _simd_s64x64_insert(X,I,Y) _simd_s64x64_insert_x1(X,I,Y)
#define _simd_s64x64_insert_enable() _simd_s64x64_insert_x1_enable()

//#ifndef _simd_s64x64_splitlo
//	#define _simd_s64x64_splitlo(X) _simd_s64x32_extract_x32(X,0)
//	#define _simd_s64x64_splitlo_enable() _simd_s64x32_extract_x32_enable()
//#endif

//#ifndef _simd_s64x64_splithi
//	#define _simd_s64x64_splithi(X) _simd_s64x32_extract_x32(X,1)
//	#define _simd_s64x64_splithi_enable() _simd_s64x32_extract_x32_enable()
//#endif

//#ifndef _simd_s64x64_combine
//	#define _simd_s64x64_combine(X,Y) _simd_s64x64_insert_x32(_simd_s64x64_insert_x32(_simd_s64x64_fill_undefined(), 0, X), 1, Y)
//	#define _simd_s64x64_combine_enable() (_simd_s64x64_insert_x32_enable() && _simd_s64x64_fill_undefined_enable())
//#endif

// -- u64 --

#define _simd_u64x2_extract_x1_safe(X,I) (reinterpret_cast<const _simd_u64x2*>(&X)[I])
#ifdef _simd_u64x2_extract_x1_
#define _simd_u64x2_extract_x1(X,I) _simd_u64x2_extract_x1_(X,I)
#define _simd_u64x2__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_extract_x1_instruction_set>()
#else
#define _simd_u64x2_extract_x1(X,I) _simd_u64x2_extract_x1_safe(X,I)
#define _simd_u64x2__extract_x1_enable() true
#endif _simd_u64x2_extract_x1_

#define _simd_u64x2_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_u64x2*>(&X)[I] = Y)
#ifdef _simd_u64x2_insert_x1_
#define _simd_u64x2_insert_x1(X,I,Y) _simd_u64x2_insert_x1_(X,I,Y)
#define _simd_u64x2__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_insert_x1_instruction_set>()
#else
#define _simd_u64x2_insert_x1(X,I,Y) _simd_u64x2_insert_x1_safe(X,I,Y)
#define _simd_u64x2__insert_x1_enable() true
#endif _simd_u64x2_insert_x1_

#define _simd_u64x2_extract_x4_safe(X,I) _simd_u64x2_insert_x2_safe(_simd_u64x2_fill_undefined_safe(),0,X)
#ifdef _simd_u64x2_extract_x4_
#define _simd_u64x2_extract_x4(X,I) _simd_u64x2_extract_x4_(X,I)
#define _simd_u64x2__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_extract_x4_instruction_set>()
#else
#define _simd_u64x2_extract_x4(X,I) _simd_u64x2_extract_x4_safe(X,I)
#define _simd_u64x2__extract_x4_enable() true
#endif _simd_u64x2_extract_x4_

#define _simd_u64x2_insert_x4_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u64x1) * 4)
#ifdef _simd_u64x2_insert_x4_
#define _simd_u64x2_insert_x4(X,I,Y) _simd_u64x2_insert_x4_(X,I,Y)
#define _simd_u64x2__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_insert_x4_instruction_set>()
#else
#define _simd_u64x2_insert_x4(X,I,Y) _simd_u64x2_insert_x4_safe(X,I,Y)
#define _simd_u64x2__insert_x4_enable() true
#endif _simd_u64x2_insert_x4_

#define _simd_u64x2_extract_x8_safe(X,I) _simd_u64x2_insert_x2_safe(_simd_u64x2_fill_undefined_safe(),0,X)
#ifdef _simd_u64x2_extract_x8_
#define _simd_u64x2_extract_x8(X,I) _simd_u64x2_extract_x8_(X,I)
#define _simd_u64x2__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_extract_x8_instruction_set>()
#else
#define _simd_u64x2_extract_x8(X,I) _simd_u64x2_extract_x8_safe(X,I)
#define _simd_u64x2__extract_x8_enable() true
#endif _simd_u64x2_extract_x8_

#define _simd_u64x2_insert_x8_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u64x1) * 8)
#ifdef _simd_u64x2_insert_x8_
#define _simd_u64x2_insert_x8(X,I,Y) _simd_u64x2_insert_x8_(X,I,Y)
#define _simd_u64x2__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_insert_x8_instruction_set>()
#else
#define _simd_u64x2_insert_x8(X,I,Y) _simd_u64x2_insert_x8_safe(X,I,Y)
#define _simd_u64x2__insert_x8_enable() true
#endif _simd_u64x2_insert_x8_

#define _simd_u64x2_extract_x16_safe(X,I) _simd_u64x2_insert_x2_safe(_simd_u64x2_fill_undefined_safe(),0,X)
#ifdef _simd_u64x2_extract_x16_
#define _simd_u64x2_extract_x16(X,I) _simd_u64x2_extract_x16_(X,I)
#define _simd_u64x2__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_extract_x16_instruction_set>()
#else
#define _simd_u64x2_extract_x16(X,I) _simd_u64x2_extract_x16_safe(X,I)
#define _simd_u64x2__extract_x16_enable() true
#endif _simd_u64x2_extract_x16_

#define _simd_u64x2_insert_x16_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u64x1) * 16)
#ifdef _simd_u64x2_insert_x16_
#define _simd_u64x2_insert_x16(X,I,Y) _simd_u64x2_insert_x16_(X,I,Y)
#define _simd_u64x2__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_insert_x16_instruction_set>()
#else
#define _simd_u64x2_insert_x16(X,I,Y) _simd_u64x2_insert_x16_safe(X,I,Y)
#define _simd_u64x2__insert_x16_enable() true
#endif _simd_u64x2_insert_x16_

#define _simd_u64x2_extract_x32_safe(X,I) _simd_u64x2_insert_x2_safe(_simd_u64x2_fill_undefined_safe(),0,X)
#ifdef _simd_u64x2_extract_x32_
#define _simd_u64x2_extract_x32(X,I) _simd_u64x2_extract_x32_(X,I)
#define _simd_u64x2__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_extract_x32_instruction_set>()
#else
#define _simd_u64x2_extract_x32(X,I) _simd_u64x2_extract_x32_safe(X,I)
#define _simd_u64x2__extract_x32_enable() true
#endif _simd_u64x2_extract_x32_

#define _simd_u64x2_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u64x1) * 32)
#ifdef _simd_u64x2_insert_x32_
#define _simd_u64x2_insert_x32(X,I,Y) _simd_u64x2_insert_x32_(X,I,Y)
#define _simd_u64x2__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_insert_x32_instruction_set>()
#else
#define _simd_u64x2_insert_x32(X,I,Y) _simd_u64x2_insert_x32_safe(X,I,Y)
#define _simd_u64x2__insert_x32_enable() true
#endif _simd_u64x2_insert_x32_

#define _simd_u64x2_extract_x64_safe(X,I) _simd_u64x2_insert_x2_safe(_simd_u64x2_fill_undefined_safe(),0,X)
#ifdef _simd_u64x2_extract_x64_
#define _simd_u64x2_extract_x64(X,I) _simd_u64x2_extract_x64_(X,I)
#define _simd_u64x2__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_extract_x64_instruction_set>()
#else
#define _simd_u64x2_extract_x64(X,I) _simd_u64x2_extract_x64_safe(X,I)
#define _simd_u64x2__extract_x64_enable() true
#endif _simd_u64x2_extract_x64_

#define _simd_u64x2_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u64x1) * 64)
#ifdef _simd_u64x2_insert_x64_
#define _simd_u64x2_insert_x64(X,I,Y) _simd_u64x2_insert_x64_(X,I,Y)
#define _simd_u64x2__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_insert_x64_instruction_set>()
#else
#define _simd_u64x2_insert_x64(X,I,Y) _simd_u64x2_insert_x64_safe(X,I,Y)
#define _simd_u64x2__insert_x64_enable() true
#endif _simd_u64x2_insert_x64_

#define _simd_u64x2_extract_safe(X,I) _simd_u64x2_extract_x1_safe(X,I)
#define _simd_u64x2_extract(X,I) _simd_u64x2_extract_x1(X,I)
#define _simd_u64x2_extract_enable() _simd_u64x2_extract_x1_enable()

#define _simd_u64x2_insert_safe(X,I,Y) _simd_u64x2_insert_x1_safe(X,I,Y)
#define _simd_u64x2_insert(X,I,Y) _simd_u64x2_insert_x1(X,I,Y)
#define _simd_u64x2_insert_enable() _simd_u64x2_insert_x1_enable()

//#ifndef _simd_u64x2_splitlo
//	#define _simd_u64x2_splitlo(X) _simd_u64x1_extract_x1(X,0)
//	#define _simd_u64x2_splitlo_enable() _simd_u64x1_extract_x1_enable()
//#endif

//#ifndef _simd_u64x2_splithi
//	#define _simd_u64x2_splithi(X) _simd_u64x1_extract_x1(X,1)
//	#define _simd_u64x2_splithi_enable() _simd_u64x1_extract_x1_enable()
//#endif

//#ifndef _simd_u64x2_combine
//	#define _simd_u64x2_combine(X,Y) _simd_u64x2_insert_x1(_simd_u64x2_insert_x1(_simd_u64x2_fill_undefined(), 0, X), 1, Y)
//	#define _simd_u64x2_combine_enable() (_simd_u64x2_insert_x1_enable() && _simd_u64x2_fill_undefined_enable())
//#endif

#define _simd_u64x4_extract_x1_safe(X,I) (reinterpret_cast<const _simd_u64x4*>(&X)[I])
#ifdef _simd_u64x4_extract_x1_
#define _simd_u64x4_extract_x1(X,I) _simd_u64x4_extract_x1_(X,I)
#define _simd_u64x4__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_extract_x1_instruction_set>()
#else
#define _simd_u64x4_extract_x1(X,I) _simd_u64x4_extract_x1_safe(X,I)
#define _simd_u64x4__extract_x1_enable() true
#endif _simd_u64x4_extract_x1_

#define _simd_u64x4_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_u64x4*>(&X)[I] = Y)
#ifdef _simd_u64x4_insert_x1_
#define _simd_u64x4_insert_x1(X,I,Y) _simd_u64x4_insert_x1_(X,I,Y)
#define _simd_u64x4__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_insert_x1_instruction_set>()
#else
#define _simd_u64x4_insert_x1(X,I,Y) _simd_u64x4_insert_x1_safe(X,I,Y)
#define _simd_u64x4__insert_x1_enable() true
#endif _simd_u64x4_insert_x1_

#define _simd_u64x4_extract_x2_safe(X,I) (reinterpret_cast<const _simd_u64x4*>(&X)[I])
#ifdef _simd_u64x4_extract_x2_
#define _simd_u64x4_extract_x2(X,I) _simd_u64x4_extract_x2_(X,I)
#define _simd_u64x4__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_extract_x2_instruction_set>()
#else
#define _simd_u64x4_extract_x2(X,I) _simd_u64x4_extract_x2_safe(X,I)
#define _simd_u64x4__extract_x2_enable() true
#endif _simd_u64x4_extract_x2_

#define _simd_u64x4_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_u64x4*>(&X)[I] = Y)
#ifdef _simd_u64x4_insert_x2_
#define _simd_u64x4_insert_x2(X,I,Y) _simd_u64x4_insert_x2_(X,I,Y)
#define _simd_u64x4__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_insert_x2_instruction_set>()
#else
#define _simd_u64x4_insert_x2(X,I,Y) _simd_u64x4_insert_x2_safe(X,I,Y)
#define _simd_u64x4__insert_x2_enable() true
#endif _simd_u64x4_insert_x2_

#define _simd_u64x4_extract_x8_safe(X,I) _simd_u64x4_insert_x4_safe(_simd_u64x4_fill_undefined_safe(),0,X)
#ifdef _simd_u64x4_extract_x8_
#define _simd_u64x4_extract_x8(X,I) _simd_u64x4_extract_x8_(X,I)
#define _simd_u64x4__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_extract_x8_instruction_set>()
#else
#define _simd_u64x4_extract_x8(X,I) _simd_u64x4_extract_x8_safe(X,I)
#define _simd_u64x4__extract_x8_enable() true
#endif _simd_u64x4_extract_x8_

#define _simd_u64x4_insert_x8_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u64x1) * 8)
#ifdef _simd_u64x4_insert_x8_
#define _simd_u64x4_insert_x8(X,I,Y) _simd_u64x4_insert_x8_(X,I,Y)
#define _simd_u64x4__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_insert_x8_instruction_set>()
#else
#define _simd_u64x4_insert_x8(X,I,Y) _simd_u64x4_insert_x8_safe(X,I,Y)
#define _simd_u64x4__insert_x8_enable() true
#endif _simd_u64x4_insert_x8_

#define _simd_u64x4_extract_x16_safe(X,I) _simd_u64x4_insert_x4_safe(_simd_u64x4_fill_undefined_safe(),0,X)
#ifdef _simd_u64x4_extract_x16_
#define _simd_u64x4_extract_x16(X,I) _simd_u64x4_extract_x16_(X,I)
#define _simd_u64x4__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_extract_x16_instruction_set>()
#else
#define _simd_u64x4_extract_x16(X,I) _simd_u64x4_extract_x16_safe(X,I)
#define _simd_u64x4__extract_x16_enable() true
#endif _simd_u64x4_extract_x16_

#define _simd_u64x4_insert_x16_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u64x1) * 16)
#ifdef _simd_u64x4_insert_x16_
#define _simd_u64x4_insert_x16(X,I,Y) _simd_u64x4_insert_x16_(X,I,Y)
#define _simd_u64x4__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_insert_x16_instruction_set>()
#else
#define _simd_u64x4_insert_x16(X,I,Y) _simd_u64x4_insert_x16_safe(X,I,Y)
#define _simd_u64x4__insert_x16_enable() true
#endif _simd_u64x4_insert_x16_

#define _simd_u64x4_extract_x32_safe(X,I) _simd_u64x4_insert_x4_safe(_simd_u64x4_fill_undefined_safe(),0,X)
#ifdef _simd_u64x4_extract_x32_
#define _simd_u64x4_extract_x32(X,I) _simd_u64x4_extract_x32_(X,I)
#define _simd_u64x4__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_extract_x32_instruction_set>()
#else
#define _simd_u64x4_extract_x32(X,I) _simd_u64x4_extract_x32_safe(X,I)
#define _simd_u64x4__extract_x32_enable() true
#endif _simd_u64x4_extract_x32_

#define _simd_u64x4_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u64x1) * 32)
#ifdef _simd_u64x4_insert_x32_
#define _simd_u64x4_insert_x32(X,I,Y) _simd_u64x4_insert_x32_(X,I,Y)
#define _simd_u64x4__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_insert_x32_instruction_set>()
#else
#define _simd_u64x4_insert_x32(X,I,Y) _simd_u64x4_insert_x32_safe(X,I,Y)
#define _simd_u64x4__insert_x32_enable() true
#endif _simd_u64x4_insert_x32_

#define _simd_u64x4_extract_x64_safe(X,I) _simd_u64x4_insert_x4_safe(_simd_u64x4_fill_undefined_safe(),0,X)
#ifdef _simd_u64x4_extract_x64_
#define _simd_u64x4_extract_x64(X,I) _simd_u64x4_extract_x64_(X,I)
#define _simd_u64x4__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_extract_x64_instruction_set>()
#else
#define _simd_u64x4_extract_x64(X,I) _simd_u64x4_extract_x64_safe(X,I)
#define _simd_u64x4__extract_x64_enable() true
#endif _simd_u64x4_extract_x64_

#define _simd_u64x4_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u64x1) * 64)
#ifdef _simd_u64x4_insert_x64_
#define _simd_u64x4_insert_x64(X,I,Y) _simd_u64x4_insert_x64_(X,I,Y)
#define _simd_u64x4__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_insert_x64_instruction_set>()
#else
#define _simd_u64x4_insert_x64(X,I,Y) _simd_u64x4_insert_x64_safe(X,I,Y)
#define _simd_u64x4__insert_x64_enable() true
#endif _simd_u64x4_insert_x64_

#define _simd_u64x4_extract_safe(X,I) _simd_u64x4_extract_x1_safe(X,I)
#define _simd_u64x4_extract(X,I) _simd_u64x4_extract_x1(X,I)
#define _simd_u64x4_extract_enable() _simd_u64x4_extract_x1_enable()

#define _simd_u64x4_insert_safe(X,I,Y) _simd_u64x4_insert_x1_safe(X,I,Y)
#define _simd_u64x4_insert(X,I,Y) _simd_u64x4_insert_x1(X,I,Y)
#define _simd_u64x4_insert_enable() _simd_u64x4_insert_x1_enable()

//#ifndef _simd_u64x4_splitlo
//	#define _simd_u64x4_splitlo(X) _simd_u64x2_extract_x2(X,0)
//	#define _simd_u64x4_splitlo_enable() _simd_u64x2_extract_x2_enable()
//#endif

//#ifndef _simd_u64x4_splithi
//	#define _simd_u64x4_splithi(X) _simd_u64x2_extract_x2(X,1)
//	#define _simd_u64x4_splithi_enable() _simd_u64x2_extract_x2_enable()
//#endif

//#ifndef _simd_u64x4_combine
//	#define _simd_u64x4_combine(X,Y) _simd_u64x4_insert_x2(_simd_u64x4_insert_x2(_simd_u64x4_fill_undefined(), 0, X), 1, Y)
//	#define _simd_u64x4_combine_enable() (_simd_u64x4_insert_x2_enable() && _simd_u64x4_fill_undefined_enable())
//#endif

#define _simd_u64x8_extract_x1_safe(X,I) (reinterpret_cast<const _simd_u64x8*>(&X)[I])
#ifdef _simd_u64x8_extract_x1_
#define _simd_u64x8_extract_x1(X,I) _simd_u64x8_extract_x1_(X,I)
#define _simd_u64x8__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_extract_x1_instruction_set>()
#else
#define _simd_u64x8_extract_x1(X,I) _simd_u64x8_extract_x1_safe(X,I)
#define _simd_u64x8__extract_x1_enable() true
#endif _simd_u64x8_extract_x1_

#define _simd_u64x8_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_u64x8*>(&X)[I] = Y)
#ifdef _simd_u64x8_insert_x1_
#define _simd_u64x8_insert_x1(X,I,Y) _simd_u64x8_insert_x1_(X,I,Y)
#define _simd_u64x8__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_insert_x1_instruction_set>()
#else
#define _simd_u64x8_insert_x1(X,I,Y) _simd_u64x8_insert_x1_safe(X,I,Y)
#define _simd_u64x8__insert_x1_enable() true
#endif _simd_u64x8_insert_x1_

#define _simd_u64x8_extract_x2_safe(X,I) (reinterpret_cast<const _simd_u64x8*>(&X)[I])
#ifdef _simd_u64x8_extract_x2_
#define _simd_u64x8_extract_x2(X,I) _simd_u64x8_extract_x2_(X,I)
#define _simd_u64x8__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_extract_x2_instruction_set>()
#else
#define _simd_u64x8_extract_x2(X,I) _simd_u64x8_extract_x2_safe(X,I)
#define _simd_u64x8__extract_x2_enable() true
#endif _simd_u64x8_extract_x2_

#define _simd_u64x8_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_u64x8*>(&X)[I] = Y)
#ifdef _simd_u64x8_insert_x2_
#define _simd_u64x8_insert_x2(X,I,Y) _simd_u64x8_insert_x2_(X,I,Y)
#define _simd_u64x8__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_insert_x2_instruction_set>()
#else
#define _simd_u64x8_insert_x2(X,I,Y) _simd_u64x8_insert_x2_safe(X,I,Y)
#define _simd_u64x8__insert_x2_enable() true
#endif _simd_u64x8_insert_x2_

#define _simd_u64x8_extract_x4_safe(X,I) (reinterpret_cast<const _simd_u64x8*>(&X)[I])
#ifdef _simd_u64x8_extract_x4_
#define _simd_u64x8_extract_x4(X,I) _simd_u64x8_extract_x4_(X,I)
#define _simd_u64x8__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_extract_x4_instruction_set>()
#else
#define _simd_u64x8_extract_x4(X,I) _simd_u64x8_extract_x4_safe(X,I)
#define _simd_u64x8__extract_x4_enable() true
#endif _simd_u64x8_extract_x4_

#define _simd_u64x8_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_u64x8*>(&X)[I] = Y)
#ifdef _simd_u64x8_insert_x4_
#define _simd_u64x8_insert_x4(X,I,Y) _simd_u64x8_insert_x4_(X,I,Y)
#define _simd_u64x8__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_insert_x4_instruction_set>()
#else
#define _simd_u64x8_insert_x4(X,I,Y) _simd_u64x8_insert_x4_safe(X,I,Y)
#define _simd_u64x8__insert_x4_enable() true
#endif _simd_u64x8_insert_x4_

#define _simd_u64x8_extract_x16_safe(X,I) _simd_u64x8_insert_x8_safe(_simd_u64x8_fill_undefined_safe(),0,X)
#ifdef _simd_u64x8_extract_x16_
#define _simd_u64x8_extract_x16(X,I) _simd_u64x8_extract_x16_(X,I)
#define _simd_u64x8__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_extract_x16_instruction_set>()
#else
#define _simd_u64x8_extract_x16(X,I) _simd_u64x8_extract_x16_safe(X,I)
#define _simd_u64x8__extract_x16_enable() true
#endif _simd_u64x8_extract_x16_

#define _simd_u64x8_insert_x16_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u64x1) * 16)
#ifdef _simd_u64x8_insert_x16_
#define _simd_u64x8_insert_x16(X,I,Y) _simd_u64x8_insert_x16_(X,I,Y)
#define _simd_u64x8__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_insert_x16_instruction_set>()
#else
#define _simd_u64x8_insert_x16(X,I,Y) _simd_u64x8_insert_x16_safe(X,I,Y)
#define _simd_u64x8__insert_x16_enable() true
#endif _simd_u64x8_insert_x16_

#define _simd_u64x8_extract_x32_safe(X,I) _simd_u64x8_insert_x8_safe(_simd_u64x8_fill_undefined_safe(),0,X)
#ifdef _simd_u64x8_extract_x32_
#define _simd_u64x8_extract_x32(X,I) _simd_u64x8_extract_x32_(X,I)
#define _simd_u64x8__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_extract_x32_instruction_set>()
#else
#define _simd_u64x8_extract_x32(X,I) _simd_u64x8_extract_x32_safe(X,I)
#define _simd_u64x8__extract_x32_enable() true
#endif _simd_u64x8_extract_x32_

#define _simd_u64x8_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u64x1) * 32)
#ifdef _simd_u64x8_insert_x32_
#define _simd_u64x8_insert_x32(X,I,Y) _simd_u64x8_insert_x32_(X,I,Y)
#define _simd_u64x8__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_insert_x32_instruction_set>()
#else
#define _simd_u64x8_insert_x32(X,I,Y) _simd_u64x8_insert_x32_safe(X,I,Y)
#define _simd_u64x8__insert_x32_enable() true
#endif _simd_u64x8_insert_x32_

#define _simd_u64x8_extract_x64_safe(X,I) _simd_u64x8_insert_x8_safe(_simd_u64x8_fill_undefined_safe(),0,X)
#ifdef _simd_u64x8_extract_x64_
#define _simd_u64x8_extract_x64(X,I) _simd_u64x8_extract_x64_(X,I)
#define _simd_u64x8__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_extract_x64_instruction_set>()
#else
#define _simd_u64x8_extract_x64(X,I) _simd_u64x8_extract_x64_safe(X,I)
#define _simd_u64x8__extract_x64_enable() true
#endif _simd_u64x8_extract_x64_

#define _simd_u64x8_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u64x1) * 64)
#ifdef _simd_u64x8_insert_x64_
#define _simd_u64x8_insert_x64(X,I,Y) _simd_u64x8_insert_x64_(X,I,Y)
#define _simd_u64x8__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_insert_x64_instruction_set>()
#else
#define _simd_u64x8_insert_x64(X,I,Y) _simd_u64x8_insert_x64_safe(X,I,Y)
#define _simd_u64x8__insert_x64_enable() true
#endif _simd_u64x8_insert_x64_

#define _simd_u64x8_extract_safe(X,I) _simd_u64x8_extract_x1_safe(X,I)
#define _simd_u64x8_extract(X,I) _simd_u64x8_extract_x1(X,I)
#define _simd_u64x8_extract_enable() _simd_u64x8_extract_x1_enable()

#define _simd_u64x8_insert_safe(X,I,Y) _simd_u64x8_insert_x1_safe(X,I,Y)
#define _simd_u64x8_insert(X,I,Y) _simd_u64x8_insert_x1(X,I,Y)
#define _simd_u64x8_insert_enable() _simd_u64x8_insert_x1_enable()

//#ifndef _simd_u64x8_splitlo
//	#define _simd_u64x8_splitlo(X) _simd_u64x4_extract_x4(X,0)
//	#define _simd_u64x8_splitlo_enable() _simd_u64x4_extract_x4_enable()
//#endif

//#ifndef _simd_u64x8_splithi
//	#define _simd_u64x8_splithi(X) _simd_u64x4_extract_x4(X,1)
//	#define _simd_u64x8_splithi_enable() _simd_u64x4_extract_x4_enable()
//#endif

//#ifndef _simd_u64x8_combine
//	#define _simd_u64x8_combine(X,Y) _simd_u64x8_insert_x4(_simd_u64x8_insert_x4(_simd_u64x8_fill_undefined(), 0, X), 1, Y)
//	#define _simd_u64x8_combine_enable() (_simd_u64x8_insert_x4_enable() && _simd_u64x8_fill_undefined_enable())
//#endif

#define _simd_u64x16_extract_x1_safe(X,I) (reinterpret_cast<const _simd_u64x16*>(&X)[I])
#ifdef _simd_u64x16_extract_x1_
#define _simd_u64x16_extract_x1(X,I) _simd_u64x16_extract_x1_(X,I)
#define _simd_u64x16__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_extract_x1_instruction_set>()
#else
#define _simd_u64x16_extract_x1(X,I) _simd_u64x16_extract_x1_safe(X,I)
#define _simd_u64x16__extract_x1_enable() true
#endif _simd_u64x16_extract_x1_

#define _simd_u64x16_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_u64x16*>(&X)[I] = Y)
#ifdef _simd_u64x16_insert_x1_
#define _simd_u64x16_insert_x1(X,I,Y) _simd_u64x16_insert_x1_(X,I,Y)
#define _simd_u64x16__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_insert_x1_instruction_set>()
#else
#define _simd_u64x16_insert_x1(X,I,Y) _simd_u64x16_insert_x1_safe(X,I,Y)
#define _simd_u64x16__insert_x1_enable() true
#endif _simd_u64x16_insert_x1_

#define _simd_u64x16_extract_x2_safe(X,I) (reinterpret_cast<const _simd_u64x16*>(&X)[I])
#ifdef _simd_u64x16_extract_x2_
#define _simd_u64x16_extract_x2(X,I) _simd_u64x16_extract_x2_(X,I)
#define _simd_u64x16__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_extract_x2_instruction_set>()
#else
#define _simd_u64x16_extract_x2(X,I) _simd_u64x16_extract_x2_safe(X,I)
#define _simd_u64x16__extract_x2_enable() true
#endif _simd_u64x16_extract_x2_

#define _simd_u64x16_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_u64x16*>(&X)[I] = Y)
#ifdef _simd_u64x16_insert_x2_
#define _simd_u64x16_insert_x2(X,I,Y) _simd_u64x16_insert_x2_(X,I,Y)
#define _simd_u64x16__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_insert_x2_instruction_set>()
#else
#define _simd_u64x16_insert_x2(X,I,Y) _simd_u64x16_insert_x2_safe(X,I,Y)
#define _simd_u64x16__insert_x2_enable() true
#endif _simd_u64x16_insert_x2_

#define _simd_u64x16_extract_x4_safe(X,I) (reinterpret_cast<const _simd_u64x16*>(&X)[I])
#ifdef _simd_u64x16_extract_x4_
#define _simd_u64x16_extract_x4(X,I) _simd_u64x16_extract_x4_(X,I)
#define _simd_u64x16__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_extract_x4_instruction_set>()
#else
#define _simd_u64x16_extract_x4(X,I) _simd_u64x16_extract_x4_safe(X,I)
#define _simd_u64x16__extract_x4_enable() true
#endif _simd_u64x16_extract_x4_

#define _simd_u64x16_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_u64x16*>(&X)[I] = Y)
#ifdef _simd_u64x16_insert_x4_
#define _simd_u64x16_insert_x4(X,I,Y) _simd_u64x16_insert_x4_(X,I,Y)
#define _simd_u64x16__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_insert_x4_instruction_set>()
#else
#define _simd_u64x16_insert_x4(X,I,Y) _simd_u64x16_insert_x4_safe(X,I,Y)
#define _simd_u64x16__insert_x4_enable() true
#endif _simd_u64x16_insert_x4_

#define _simd_u64x16_extract_x8_safe(X,I) (reinterpret_cast<const _simd_u64x16*>(&X)[I])
#ifdef _simd_u64x16_extract_x8_
#define _simd_u64x16_extract_x8(X,I) _simd_u64x16_extract_x8_(X,I)
#define _simd_u64x16__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_extract_x8_instruction_set>()
#else
#define _simd_u64x16_extract_x8(X,I) _simd_u64x16_extract_x8_safe(X,I)
#define _simd_u64x16__extract_x8_enable() true
#endif _simd_u64x16_extract_x8_

#define _simd_u64x16_insert_x8_safe(X,I,Y) (reinterpret_cast<_simd_u64x16*>(&X)[I] = Y)
#ifdef _simd_u64x16_insert_x8_
#define _simd_u64x16_insert_x8(X,I,Y) _simd_u64x16_insert_x8_(X,I,Y)
#define _simd_u64x16__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_insert_x8_instruction_set>()
#else
#define _simd_u64x16_insert_x8(X,I,Y) _simd_u64x16_insert_x8_safe(X,I,Y)
#define _simd_u64x16__insert_x8_enable() true
#endif _simd_u64x16_insert_x8_

#define _simd_u64x16_extract_x32_safe(X,I) _simd_u64x16_insert_x16_safe(_simd_u64x16_fill_undefined_safe(),0,X)
#ifdef _simd_u64x16_extract_x32_
#define _simd_u64x16_extract_x32(X,I) _simd_u64x16_extract_x32_(X,I)
#define _simd_u64x16__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_extract_x32_instruction_set>()
#else
#define _simd_u64x16_extract_x32(X,I) _simd_u64x16_extract_x32_safe(X,I)
#define _simd_u64x16__extract_x32_enable() true
#endif _simd_u64x16_extract_x32_

#define _simd_u64x16_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u64x1) * 32)
#ifdef _simd_u64x16_insert_x32_
#define _simd_u64x16_insert_x32(X,I,Y) _simd_u64x16_insert_x32_(X,I,Y)
#define _simd_u64x16__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_insert_x32_instruction_set>()
#else
#define _simd_u64x16_insert_x32(X,I,Y) _simd_u64x16_insert_x32_safe(X,I,Y)
#define _simd_u64x16__insert_x32_enable() true
#endif _simd_u64x16_insert_x32_

#define _simd_u64x16_extract_x64_safe(X,I) _simd_u64x16_insert_x16_safe(_simd_u64x16_fill_undefined_safe(),0,X)
#ifdef _simd_u64x16_extract_x64_
#define _simd_u64x16_extract_x64(X,I) _simd_u64x16_extract_x64_(X,I)
#define _simd_u64x16__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_extract_x64_instruction_set>()
#else
#define _simd_u64x16_extract_x64(X,I) _simd_u64x16_extract_x64_safe(X,I)
#define _simd_u64x16__extract_x64_enable() true
#endif _simd_u64x16_extract_x64_

#define _simd_u64x16_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u64x1) * 64)
#ifdef _simd_u64x16_insert_x64_
#define _simd_u64x16_insert_x64(X,I,Y) _simd_u64x16_insert_x64_(X,I,Y)
#define _simd_u64x16__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_insert_x64_instruction_set>()
#else
#define _simd_u64x16_insert_x64(X,I,Y) _simd_u64x16_insert_x64_safe(X,I,Y)
#define _simd_u64x16__insert_x64_enable() true
#endif _simd_u64x16_insert_x64_

#define _simd_u64x16_extract_safe(X,I) _simd_u64x16_extract_x1_safe(X,I)
#define _simd_u64x16_extract(X,I) _simd_u64x16_extract_x1(X,I)
#define _simd_u64x16_extract_enable() _simd_u64x16_extract_x1_enable()

#define _simd_u64x16_insert_safe(X,I,Y) _simd_u64x16_insert_x1_safe(X,I,Y)
#define _simd_u64x16_insert(X,I,Y) _simd_u64x16_insert_x1(X,I,Y)
#define _simd_u64x16_insert_enable() _simd_u64x16_insert_x1_enable()

//#ifndef _simd_u64x16_splitlo
//	#define _simd_u64x16_splitlo(X) _simd_u64x8_extract_x8(X,0)
//	#define _simd_u64x16_splitlo_enable() _simd_u64x8_extract_x8_enable()
//#endif

//#ifndef _simd_u64x16_splithi
//	#define _simd_u64x16_splithi(X) _simd_u64x8_extract_x8(X,1)
//	#define _simd_u64x16_splithi_enable() _simd_u64x8_extract_x8_enable()
//#endif

//#ifndef _simd_u64x16_combine
//	#define _simd_u64x16_combine(X,Y) _simd_u64x16_insert_x8(_simd_u64x16_insert_x8(_simd_u64x16_fill_undefined(), 0, X), 1, Y)
//	#define _simd_u64x16_combine_enable() (_simd_u64x16_insert_x8_enable() && _simd_u64x16_fill_undefined_enable())
//#endif

#define _simd_u64x32_extract_x1_safe(X,I) (reinterpret_cast<const _simd_u64x32*>(&X)[I])
#ifdef _simd_u64x32_extract_x1_
#define _simd_u64x32_extract_x1(X,I) _simd_u64x32_extract_x1_(X,I)
#define _simd_u64x32__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_extract_x1_instruction_set>()
#else
#define _simd_u64x32_extract_x1(X,I) _simd_u64x32_extract_x1_safe(X,I)
#define _simd_u64x32__extract_x1_enable() true
#endif _simd_u64x32_extract_x1_

#define _simd_u64x32_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_u64x32*>(&X)[I] = Y)
#ifdef _simd_u64x32_insert_x1_
#define _simd_u64x32_insert_x1(X,I,Y) _simd_u64x32_insert_x1_(X,I,Y)
#define _simd_u64x32__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_insert_x1_instruction_set>()
#else
#define _simd_u64x32_insert_x1(X,I,Y) _simd_u64x32_insert_x1_safe(X,I,Y)
#define _simd_u64x32__insert_x1_enable() true
#endif _simd_u64x32_insert_x1_

#define _simd_u64x32_extract_x2_safe(X,I) (reinterpret_cast<const _simd_u64x32*>(&X)[I])
#ifdef _simd_u64x32_extract_x2_
#define _simd_u64x32_extract_x2(X,I) _simd_u64x32_extract_x2_(X,I)
#define _simd_u64x32__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_extract_x2_instruction_set>()
#else
#define _simd_u64x32_extract_x2(X,I) _simd_u64x32_extract_x2_safe(X,I)
#define _simd_u64x32__extract_x2_enable() true
#endif _simd_u64x32_extract_x2_

#define _simd_u64x32_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_u64x32*>(&X)[I] = Y)
#ifdef _simd_u64x32_insert_x2_
#define _simd_u64x32_insert_x2(X,I,Y) _simd_u64x32_insert_x2_(X,I,Y)
#define _simd_u64x32__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_insert_x2_instruction_set>()
#else
#define _simd_u64x32_insert_x2(X,I,Y) _simd_u64x32_insert_x2_safe(X,I,Y)
#define _simd_u64x32__insert_x2_enable() true
#endif _simd_u64x32_insert_x2_

#define _simd_u64x32_extract_x4_safe(X,I) (reinterpret_cast<const _simd_u64x32*>(&X)[I])
#ifdef _simd_u64x32_extract_x4_
#define _simd_u64x32_extract_x4(X,I) _simd_u64x32_extract_x4_(X,I)
#define _simd_u64x32__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_extract_x4_instruction_set>()
#else
#define _simd_u64x32_extract_x4(X,I) _simd_u64x32_extract_x4_safe(X,I)
#define _simd_u64x32__extract_x4_enable() true
#endif _simd_u64x32_extract_x4_

#define _simd_u64x32_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_u64x32*>(&X)[I] = Y)
#ifdef _simd_u64x32_insert_x4_
#define _simd_u64x32_insert_x4(X,I,Y) _simd_u64x32_insert_x4_(X,I,Y)
#define _simd_u64x32__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_insert_x4_instruction_set>()
#else
#define _simd_u64x32_insert_x4(X,I,Y) _simd_u64x32_insert_x4_safe(X,I,Y)
#define _simd_u64x32__insert_x4_enable() true
#endif _simd_u64x32_insert_x4_

#define _simd_u64x32_extract_x8_safe(X,I) (reinterpret_cast<const _simd_u64x32*>(&X)[I])
#ifdef _simd_u64x32_extract_x8_
#define _simd_u64x32_extract_x8(X,I) _simd_u64x32_extract_x8_(X,I)
#define _simd_u64x32__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_extract_x8_instruction_set>()
#else
#define _simd_u64x32_extract_x8(X,I) _simd_u64x32_extract_x8_safe(X,I)
#define _simd_u64x32__extract_x8_enable() true
#endif _simd_u64x32_extract_x8_

#define _simd_u64x32_insert_x8_safe(X,I,Y) (reinterpret_cast<_simd_u64x32*>(&X)[I] = Y)
#ifdef _simd_u64x32_insert_x8_
#define _simd_u64x32_insert_x8(X,I,Y) _simd_u64x32_insert_x8_(X,I,Y)
#define _simd_u64x32__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_insert_x8_instruction_set>()
#else
#define _simd_u64x32_insert_x8(X,I,Y) _simd_u64x32_insert_x8_safe(X,I,Y)
#define _simd_u64x32__insert_x8_enable() true
#endif _simd_u64x32_insert_x8_

#define _simd_u64x32_extract_x16_safe(X,I) (reinterpret_cast<const _simd_u64x32*>(&X)[I])
#ifdef _simd_u64x32_extract_x16_
#define _simd_u64x32_extract_x16(X,I) _simd_u64x32_extract_x16_(X,I)
#define _simd_u64x32__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_extract_x16_instruction_set>()
#else
#define _simd_u64x32_extract_x16(X,I) _simd_u64x32_extract_x16_safe(X,I)
#define _simd_u64x32__extract_x16_enable() true
#endif _simd_u64x32_extract_x16_

#define _simd_u64x32_insert_x16_safe(X,I,Y) (reinterpret_cast<_simd_u64x32*>(&X)[I] = Y)
#ifdef _simd_u64x32_insert_x16_
#define _simd_u64x32_insert_x16(X,I,Y) _simd_u64x32_insert_x16_(X,I,Y)
#define _simd_u64x32__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_insert_x16_instruction_set>()
#else
#define _simd_u64x32_insert_x16(X,I,Y) _simd_u64x32_insert_x16_safe(X,I,Y)
#define _simd_u64x32__insert_x16_enable() true
#endif _simd_u64x32_insert_x16_

#define _simd_u64x32_extract_x64_safe(X,I) _simd_u64x32_insert_x32_safe(_simd_u64x32_fill_undefined_safe(),0,X)
#ifdef _simd_u64x32_extract_x64_
#define _simd_u64x32_extract_x64(X,I) _simd_u64x32_extract_x64_(X,I)
#define _simd_u64x32__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_extract_x64_instruction_set>()
#else
#define _simd_u64x32_extract_x64(X,I) _simd_u64x32_extract_x64_safe(X,I)
#define _simd_u64x32__extract_x64_enable() true
#endif _simd_u64x32_extract_x64_

#define _simd_u64x32_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u64x1) * 64)
#ifdef _simd_u64x32_insert_x64_
#define _simd_u64x32_insert_x64(X,I,Y) _simd_u64x32_insert_x64_(X,I,Y)
#define _simd_u64x32__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_insert_x64_instruction_set>()
#else
#define _simd_u64x32_insert_x64(X,I,Y) _simd_u64x32_insert_x64_safe(X,I,Y)
#define _simd_u64x32__insert_x64_enable() true
#endif _simd_u64x32_insert_x64_

#define _simd_u64x32_extract_safe(X,I) _simd_u64x32_extract_x1_safe(X,I)
#define _simd_u64x32_extract(X,I) _simd_u64x32_extract_x1(X,I)
#define _simd_u64x32_extract_enable() _simd_u64x32_extract_x1_enable()

#define _simd_u64x32_insert_safe(X,I,Y) _simd_u64x32_insert_x1_safe(X,I,Y)
#define _simd_u64x32_insert(X,I,Y) _simd_u64x32_insert_x1(X,I,Y)
#define _simd_u64x32_insert_enable() _simd_u64x32_insert_x1_enable()

//#ifndef _simd_u64x32_splitlo
//	#define _simd_u64x32_splitlo(X) _simd_u64x16_extract_x16(X,0)
//	#define _simd_u64x32_splitlo_enable() _simd_u64x16_extract_x16_enable()
//#endif

//#ifndef _simd_u64x32_splithi
//	#define _simd_u64x32_splithi(X) _simd_u64x16_extract_x16(X,1)
//	#define _simd_u64x32_splithi_enable() _simd_u64x16_extract_x16_enable()
//#endif

//#ifndef _simd_u64x32_combine
//	#define _simd_u64x32_combine(X,Y) _simd_u64x32_insert_x16(_simd_u64x32_insert_x16(_simd_u64x32_fill_undefined(), 0, X), 1, Y)
//	#define _simd_u64x32_combine_enable() (_simd_u64x32_insert_x16_enable() && _simd_u64x32_fill_undefined_enable())
//#endif

#define _simd_u64x64_extract_x1_safe(X,I) (reinterpret_cast<const _simd_u64x64*>(&X)[I])
#ifdef _simd_u64x64_extract_x1_
#define _simd_u64x64_extract_x1(X,I) _simd_u64x64_extract_x1_(X,I)
#define _simd_u64x64__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_extract_x1_instruction_set>()
#else
#define _simd_u64x64_extract_x1(X,I) _simd_u64x64_extract_x1_safe(X,I)
#define _simd_u64x64__extract_x1_enable() true
#endif _simd_u64x64_extract_x1_

#define _simd_u64x64_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_u64x64*>(&X)[I] = Y)
#ifdef _simd_u64x64_insert_x1_
#define _simd_u64x64_insert_x1(X,I,Y) _simd_u64x64_insert_x1_(X,I,Y)
#define _simd_u64x64__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_insert_x1_instruction_set>()
#else
#define _simd_u64x64_insert_x1(X,I,Y) _simd_u64x64_insert_x1_safe(X,I,Y)
#define _simd_u64x64__insert_x1_enable() true
#endif _simd_u64x64_insert_x1_

#define _simd_u64x64_extract_x2_safe(X,I) (reinterpret_cast<const _simd_u64x64*>(&X)[I])
#ifdef _simd_u64x64_extract_x2_
#define _simd_u64x64_extract_x2(X,I) _simd_u64x64_extract_x2_(X,I)
#define _simd_u64x64__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_extract_x2_instruction_set>()
#else
#define _simd_u64x64_extract_x2(X,I) _simd_u64x64_extract_x2_safe(X,I)
#define _simd_u64x64__extract_x2_enable() true
#endif _simd_u64x64_extract_x2_

#define _simd_u64x64_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_u64x64*>(&X)[I] = Y)
#ifdef _simd_u64x64_insert_x2_
#define _simd_u64x64_insert_x2(X,I,Y) _simd_u64x64_insert_x2_(X,I,Y)
#define _simd_u64x64__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_insert_x2_instruction_set>()
#else
#define _simd_u64x64_insert_x2(X,I,Y) _simd_u64x64_insert_x2_safe(X,I,Y)
#define _simd_u64x64__insert_x2_enable() true
#endif _simd_u64x64_insert_x2_

#define _simd_u64x64_extract_x4_safe(X,I) (reinterpret_cast<const _simd_u64x64*>(&X)[I])
#ifdef _simd_u64x64_extract_x4_
#define _simd_u64x64_extract_x4(X,I) _simd_u64x64_extract_x4_(X,I)
#define _simd_u64x64__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_extract_x4_instruction_set>()
#else
#define _simd_u64x64_extract_x4(X,I) _simd_u64x64_extract_x4_safe(X,I)
#define _simd_u64x64__extract_x4_enable() true
#endif _simd_u64x64_extract_x4_

#define _simd_u64x64_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_u64x64*>(&X)[I] = Y)
#ifdef _simd_u64x64_insert_x4_
#define _simd_u64x64_insert_x4(X,I,Y) _simd_u64x64_insert_x4_(X,I,Y)
#define _simd_u64x64__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_insert_x4_instruction_set>()
#else
#define _simd_u64x64_insert_x4(X,I,Y) _simd_u64x64_insert_x4_safe(X,I,Y)
#define _simd_u64x64__insert_x4_enable() true
#endif _simd_u64x64_insert_x4_

#define _simd_u64x64_extract_x8_safe(X,I) (reinterpret_cast<const _simd_u64x64*>(&X)[I])
#ifdef _simd_u64x64_extract_x8_
#define _simd_u64x64_extract_x8(X,I) _simd_u64x64_extract_x8_(X,I)
#define _simd_u64x64__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_extract_x8_instruction_set>()
#else
#define _simd_u64x64_extract_x8(X,I) _simd_u64x64_extract_x8_safe(X,I)
#define _simd_u64x64__extract_x8_enable() true
#endif _simd_u64x64_extract_x8_

#define _simd_u64x64_insert_x8_safe(X,I,Y) (reinterpret_cast<_simd_u64x64*>(&X)[I] = Y)
#ifdef _simd_u64x64_insert_x8_
#define _simd_u64x64_insert_x8(X,I,Y) _simd_u64x64_insert_x8_(X,I,Y)
#define _simd_u64x64__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_insert_x8_instruction_set>()
#else
#define _simd_u64x64_insert_x8(X,I,Y) _simd_u64x64_insert_x8_safe(X,I,Y)
#define _simd_u64x64__insert_x8_enable() true
#endif _simd_u64x64_insert_x8_

#define _simd_u64x64_extract_x16_safe(X,I) (reinterpret_cast<const _simd_u64x64*>(&X)[I])
#ifdef _simd_u64x64_extract_x16_
#define _simd_u64x64_extract_x16(X,I) _simd_u64x64_extract_x16_(X,I)
#define _simd_u64x64__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_extract_x16_instruction_set>()
#else
#define _simd_u64x64_extract_x16(X,I) _simd_u64x64_extract_x16_safe(X,I)
#define _simd_u64x64__extract_x16_enable() true
#endif _simd_u64x64_extract_x16_

#define _simd_u64x64_insert_x16_safe(X,I,Y) (reinterpret_cast<_simd_u64x64*>(&X)[I] = Y)
#ifdef _simd_u64x64_insert_x16_
#define _simd_u64x64_insert_x16(X,I,Y) _simd_u64x64_insert_x16_(X,I,Y)
#define _simd_u64x64__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_insert_x16_instruction_set>()
#else
#define _simd_u64x64_insert_x16(X,I,Y) _simd_u64x64_insert_x16_safe(X,I,Y)
#define _simd_u64x64__insert_x16_enable() true
#endif _simd_u64x64_insert_x16_

#define _simd_u64x64_extract_x32_safe(X,I) (reinterpret_cast<const _simd_u64x64*>(&X)[I])
#ifdef _simd_u64x64_extract_x32_
#define _simd_u64x64_extract_x32(X,I) _simd_u64x64_extract_x32_(X,I)
#define _simd_u64x64__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_extract_x32_instruction_set>()
#else
#define _simd_u64x64_extract_x32(X,I) _simd_u64x64_extract_x32_safe(X,I)
#define _simd_u64x64__extract_x32_enable() true
#endif _simd_u64x64_extract_x32_

#define _simd_u64x64_insert_x32_safe(X,I,Y) (reinterpret_cast<_simd_u64x64*>(&X)[I] = Y)
#ifdef _simd_u64x64_insert_x32_
#define _simd_u64x64_insert_x32(X,I,Y) _simd_u64x64_insert_x32_(X,I,Y)
#define _simd_u64x64__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_insert_x32_instruction_set>()
#else
#define _simd_u64x64_insert_x32(X,I,Y) _simd_u64x64_insert_x32_safe(X,I,Y)
#define _simd_u64x64__insert_x32_enable() true
#endif _simd_u64x64_insert_x32_

#define _simd_u64x64_extract_safe(X,I) _simd_u64x64_extract_x1_safe(X,I)
#define _simd_u64x64_extract(X,I) _simd_u64x64_extract_x1(X,I)
#define _simd_u64x64_extract_enable() _simd_u64x64_extract_x1_enable()

#define _simd_u64x64_insert_safe(X,I,Y) _simd_u64x64_insert_x1_safe(X,I,Y)
#define _simd_u64x64_insert(X,I,Y) _simd_u64x64_insert_x1(X,I,Y)
#define _simd_u64x64_insert_enable() _simd_u64x64_insert_x1_enable()

//#ifndef _simd_u64x64_splitlo
//	#define _simd_u64x64_splitlo(X) _simd_u64x32_extract_x32(X,0)
//	#define _simd_u64x64_splitlo_enable() _simd_u64x32_extract_x32_enable()
//#endif

//#ifndef _simd_u64x64_splithi
//	#define _simd_u64x64_splithi(X) _simd_u64x32_extract_x32(X,1)
//	#define _simd_u64x64_splithi_enable() _simd_u64x32_extract_x32_enable()
//#endif

//#ifndef _simd_u64x64_combine
//	#define _simd_u64x64_combine(X,Y) _simd_u64x64_insert_x32(_simd_u64x64_insert_x32(_simd_u64x64_fill_undefined(), 0, X), 1, Y)
//	#define _simd_u64x64_combine_enable() (_simd_u64x64_insert_x32_enable() && _simd_u64x64_fill_undefined_enable())
//#endif

// -- s32 --

#define _simd_s32x2_extract_x1_safe(X,I) (reinterpret_cast<const _simd_s32x2*>(&X)[I])
#ifdef _simd_s32x2_extract_x1_
#define _simd_s32x2_extract_x1(X,I) _simd_s32x2_extract_x1_(X,I)
#define _simd_s32x2__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_extract_x1_instruction_set>()
#else
#define _simd_s32x2_extract_x1(X,I) _simd_s32x2_extract_x1_safe(X,I)
#define _simd_s32x2__extract_x1_enable() true
#endif _simd_s32x2_extract_x1_

#define _simd_s32x2_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_s32x2*>(&X)[I] = Y)
#ifdef _simd_s32x2_insert_x1_
#define _simd_s32x2_insert_x1(X,I,Y) _simd_s32x2_insert_x1_(X,I,Y)
#define _simd_s32x2__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_insert_x1_instruction_set>()
#else
#define _simd_s32x2_insert_x1(X,I,Y) _simd_s32x2_insert_x1_safe(X,I,Y)
#define _simd_s32x2__insert_x1_enable() true
#endif _simd_s32x2_insert_x1_

#define _simd_s32x2_extract_x4_safe(X,I) _simd_s32x2_insert_x2_safe(_simd_s32x2_fill_undefined_safe(),0,X)
#ifdef _simd_s32x2_extract_x4_
#define _simd_s32x2_extract_x4(X,I) _simd_s32x2_extract_x4_(X,I)
#define _simd_s32x2__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_extract_x4_instruction_set>()
#else
#define _simd_s32x2_extract_x4(X,I) _simd_s32x2_extract_x4_safe(X,I)
#define _simd_s32x2__extract_x4_enable() true
#endif _simd_s32x2_extract_x4_

#define _simd_s32x2_insert_x4_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s32x1) * 4)
#ifdef _simd_s32x2_insert_x4_
#define _simd_s32x2_insert_x4(X,I,Y) _simd_s32x2_insert_x4_(X,I,Y)
#define _simd_s32x2__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_insert_x4_instruction_set>()
#else
#define _simd_s32x2_insert_x4(X,I,Y) _simd_s32x2_insert_x4_safe(X,I,Y)
#define _simd_s32x2__insert_x4_enable() true
#endif _simd_s32x2_insert_x4_

#define _simd_s32x2_extract_x8_safe(X,I) _simd_s32x2_insert_x2_safe(_simd_s32x2_fill_undefined_safe(),0,X)
#ifdef _simd_s32x2_extract_x8_
#define _simd_s32x2_extract_x8(X,I) _simd_s32x2_extract_x8_(X,I)
#define _simd_s32x2__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_extract_x8_instruction_set>()
#else
#define _simd_s32x2_extract_x8(X,I) _simd_s32x2_extract_x8_safe(X,I)
#define _simd_s32x2__extract_x8_enable() true
#endif _simd_s32x2_extract_x8_

#define _simd_s32x2_insert_x8_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s32x1) * 8)
#ifdef _simd_s32x2_insert_x8_
#define _simd_s32x2_insert_x8(X,I,Y) _simd_s32x2_insert_x8_(X,I,Y)
#define _simd_s32x2__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_insert_x8_instruction_set>()
#else
#define _simd_s32x2_insert_x8(X,I,Y) _simd_s32x2_insert_x8_safe(X,I,Y)
#define _simd_s32x2__insert_x8_enable() true
#endif _simd_s32x2_insert_x8_

#define _simd_s32x2_extract_x16_safe(X,I) _simd_s32x2_insert_x2_safe(_simd_s32x2_fill_undefined_safe(),0,X)
#ifdef _simd_s32x2_extract_x16_
#define _simd_s32x2_extract_x16(X,I) _simd_s32x2_extract_x16_(X,I)
#define _simd_s32x2__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_extract_x16_instruction_set>()
#else
#define _simd_s32x2_extract_x16(X,I) _simd_s32x2_extract_x16_safe(X,I)
#define _simd_s32x2__extract_x16_enable() true
#endif _simd_s32x2_extract_x16_

#define _simd_s32x2_insert_x16_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s32x1) * 16)
#ifdef _simd_s32x2_insert_x16_
#define _simd_s32x2_insert_x16(X,I,Y) _simd_s32x2_insert_x16_(X,I,Y)
#define _simd_s32x2__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_insert_x16_instruction_set>()
#else
#define _simd_s32x2_insert_x16(X,I,Y) _simd_s32x2_insert_x16_safe(X,I,Y)
#define _simd_s32x2__insert_x16_enable() true
#endif _simd_s32x2_insert_x16_

#define _simd_s32x2_extract_x32_safe(X,I) _simd_s32x2_insert_x2_safe(_simd_s32x2_fill_undefined_safe(),0,X)
#ifdef _simd_s32x2_extract_x32_
#define _simd_s32x2_extract_x32(X,I) _simd_s32x2_extract_x32_(X,I)
#define _simd_s32x2__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_extract_x32_instruction_set>()
#else
#define _simd_s32x2_extract_x32(X,I) _simd_s32x2_extract_x32_safe(X,I)
#define _simd_s32x2__extract_x32_enable() true
#endif _simd_s32x2_extract_x32_

#define _simd_s32x2_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s32x1) * 32)
#ifdef _simd_s32x2_insert_x32_
#define _simd_s32x2_insert_x32(X,I,Y) _simd_s32x2_insert_x32_(X,I,Y)
#define _simd_s32x2__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_insert_x32_instruction_set>()
#else
#define _simd_s32x2_insert_x32(X,I,Y) _simd_s32x2_insert_x32_safe(X,I,Y)
#define _simd_s32x2__insert_x32_enable() true
#endif _simd_s32x2_insert_x32_

#define _simd_s32x2_extract_x64_safe(X,I) _simd_s32x2_insert_x2_safe(_simd_s32x2_fill_undefined_safe(),0,X)
#ifdef _simd_s32x2_extract_x64_
#define _simd_s32x2_extract_x64(X,I) _simd_s32x2_extract_x64_(X,I)
#define _simd_s32x2__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_extract_x64_instruction_set>()
#else
#define _simd_s32x2_extract_x64(X,I) _simd_s32x2_extract_x64_safe(X,I)
#define _simd_s32x2__extract_x64_enable() true
#endif _simd_s32x2_extract_x64_

#define _simd_s32x2_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s32x1) * 64)
#ifdef _simd_s32x2_insert_x64_
#define _simd_s32x2_insert_x64(X,I,Y) _simd_s32x2_insert_x64_(X,I,Y)
#define _simd_s32x2__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_insert_x64_instruction_set>()
#else
#define _simd_s32x2_insert_x64(X,I,Y) _simd_s32x2_insert_x64_safe(X,I,Y)
#define _simd_s32x2__insert_x64_enable() true
#endif _simd_s32x2_insert_x64_

#define _simd_s32x2_extract_safe(X,I) _simd_s32x2_extract_x1_safe(X,I)
#define _simd_s32x2_extract(X,I) _simd_s32x2_extract_x1(X,I)
#define _simd_s32x2_extract_enable() _simd_s32x2_extract_x1_enable()

#define _simd_s32x2_insert_safe(X,I,Y) _simd_s32x2_insert_x1_safe(X,I,Y)
#define _simd_s32x2_insert(X,I,Y) _simd_s32x2_insert_x1(X,I,Y)
#define _simd_s32x2_insert_enable() _simd_s32x2_insert_x1_enable()

//#ifndef _simd_s32x2_splitlo
//	#define _simd_s32x2_splitlo(X) _simd_s32x1_extract_x1(X,0)
//	#define _simd_s32x2_splitlo_enable() _simd_s32x1_extract_x1_enable()
//#endif

//#ifndef _simd_s32x2_splithi
//	#define _simd_s32x2_splithi(X) _simd_s32x1_extract_x1(X,1)
//	#define _simd_s32x2_splithi_enable() _simd_s32x1_extract_x1_enable()
//#endif

//#ifndef _simd_s32x2_combine
//	#define _simd_s32x2_combine(X,Y) _simd_s32x2_insert_x1(_simd_s32x2_insert_x1(_simd_s32x2_fill_undefined(), 0, X), 1, Y)
//	#define _simd_s32x2_combine_enable() (_simd_s32x2_insert_x1_enable() && _simd_s32x2_fill_undefined_enable())
//#endif

#define _simd_s32x4_extract_x1_safe(X,I) (reinterpret_cast<const _simd_s32x4*>(&X)[I])
#ifdef _simd_s32x4_extract_x1_
#define _simd_s32x4_extract_x1(X,I) _simd_s32x4_extract_x1_(X,I)
#define _simd_s32x4__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_extract_x1_instruction_set>()
#else
#define _simd_s32x4_extract_x1(X,I) _simd_s32x4_extract_x1_safe(X,I)
#define _simd_s32x4__extract_x1_enable() true
#endif _simd_s32x4_extract_x1_

#define _simd_s32x4_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_s32x4*>(&X)[I] = Y)
#ifdef _simd_s32x4_insert_x1_
#define _simd_s32x4_insert_x1(X,I,Y) _simd_s32x4_insert_x1_(X,I,Y)
#define _simd_s32x4__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_insert_x1_instruction_set>()
#else
#define _simd_s32x4_insert_x1(X,I,Y) _simd_s32x4_insert_x1_safe(X,I,Y)
#define _simd_s32x4__insert_x1_enable() true
#endif _simd_s32x4_insert_x1_

#define _simd_s32x4_extract_x2_safe(X,I) (reinterpret_cast<const _simd_s32x4*>(&X)[I])
#ifdef _simd_s32x4_extract_x2_
#define _simd_s32x4_extract_x2(X,I) _simd_s32x4_extract_x2_(X,I)
#define _simd_s32x4__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_extract_x2_instruction_set>()
#else
#define _simd_s32x4_extract_x2(X,I) _simd_s32x4_extract_x2_safe(X,I)
#define _simd_s32x4__extract_x2_enable() true
#endif _simd_s32x4_extract_x2_

#define _simd_s32x4_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_s32x4*>(&X)[I] = Y)
#ifdef _simd_s32x4_insert_x2_
#define _simd_s32x4_insert_x2(X,I,Y) _simd_s32x4_insert_x2_(X,I,Y)
#define _simd_s32x4__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_insert_x2_instruction_set>()
#else
#define _simd_s32x4_insert_x2(X,I,Y) _simd_s32x4_insert_x2_safe(X,I,Y)
#define _simd_s32x4__insert_x2_enable() true
#endif _simd_s32x4_insert_x2_

#define _simd_s32x4_extract_x8_safe(X,I) _simd_s32x4_insert_x4_safe(_simd_s32x4_fill_undefined_safe(),0,X)
#ifdef _simd_s32x4_extract_x8_
#define _simd_s32x4_extract_x8(X,I) _simd_s32x4_extract_x8_(X,I)
#define _simd_s32x4__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_extract_x8_instruction_set>()
#else
#define _simd_s32x4_extract_x8(X,I) _simd_s32x4_extract_x8_safe(X,I)
#define _simd_s32x4__extract_x8_enable() true
#endif _simd_s32x4_extract_x8_

#define _simd_s32x4_insert_x8_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s32x1) * 8)
#ifdef _simd_s32x4_insert_x8_
#define _simd_s32x4_insert_x8(X,I,Y) _simd_s32x4_insert_x8_(X,I,Y)
#define _simd_s32x4__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_insert_x8_instruction_set>()
#else
#define _simd_s32x4_insert_x8(X,I,Y) _simd_s32x4_insert_x8_safe(X,I,Y)
#define _simd_s32x4__insert_x8_enable() true
#endif _simd_s32x4_insert_x8_

#define _simd_s32x4_extract_x16_safe(X,I) _simd_s32x4_insert_x4_safe(_simd_s32x4_fill_undefined_safe(),0,X)
#ifdef _simd_s32x4_extract_x16_
#define _simd_s32x4_extract_x16(X,I) _simd_s32x4_extract_x16_(X,I)
#define _simd_s32x4__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_extract_x16_instruction_set>()
#else
#define _simd_s32x4_extract_x16(X,I) _simd_s32x4_extract_x16_safe(X,I)
#define _simd_s32x4__extract_x16_enable() true
#endif _simd_s32x4_extract_x16_

#define _simd_s32x4_insert_x16_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s32x1) * 16)
#ifdef _simd_s32x4_insert_x16_
#define _simd_s32x4_insert_x16(X,I,Y) _simd_s32x4_insert_x16_(X,I,Y)
#define _simd_s32x4__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_insert_x16_instruction_set>()
#else
#define _simd_s32x4_insert_x16(X,I,Y) _simd_s32x4_insert_x16_safe(X,I,Y)
#define _simd_s32x4__insert_x16_enable() true
#endif _simd_s32x4_insert_x16_

#define _simd_s32x4_extract_x32_safe(X,I) _simd_s32x4_insert_x4_safe(_simd_s32x4_fill_undefined_safe(),0,X)
#ifdef _simd_s32x4_extract_x32_
#define _simd_s32x4_extract_x32(X,I) _simd_s32x4_extract_x32_(X,I)
#define _simd_s32x4__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_extract_x32_instruction_set>()
#else
#define _simd_s32x4_extract_x32(X,I) _simd_s32x4_extract_x32_safe(X,I)
#define _simd_s32x4__extract_x32_enable() true
#endif _simd_s32x4_extract_x32_

#define _simd_s32x4_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s32x1) * 32)
#ifdef _simd_s32x4_insert_x32_
#define _simd_s32x4_insert_x32(X,I,Y) _simd_s32x4_insert_x32_(X,I,Y)
#define _simd_s32x4__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_insert_x32_instruction_set>()
#else
#define _simd_s32x4_insert_x32(X,I,Y) _simd_s32x4_insert_x32_safe(X,I,Y)
#define _simd_s32x4__insert_x32_enable() true
#endif _simd_s32x4_insert_x32_

#define _simd_s32x4_extract_x64_safe(X,I) _simd_s32x4_insert_x4_safe(_simd_s32x4_fill_undefined_safe(),0,X)
#ifdef _simd_s32x4_extract_x64_
#define _simd_s32x4_extract_x64(X,I) _simd_s32x4_extract_x64_(X,I)
#define _simd_s32x4__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_extract_x64_instruction_set>()
#else
#define _simd_s32x4_extract_x64(X,I) _simd_s32x4_extract_x64_safe(X,I)
#define _simd_s32x4__extract_x64_enable() true
#endif _simd_s32x4_extract_x64_

#define _simd_s32x4_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s32x1) * 64)
#ifdef _simd_s32x4_insert_x64_
#define _simd_s32x4_insert_x64(X,I,Y) _simd_s32x4_insert_x64_(X,I,Y)
#define _simd_s32x4__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_insert_x64_instruction_set>()
#else
#define _simd_s32x4_insert_x64(X,I,Y) _simd_s32x4_insert_x64_safe(X,I,Y)
#define _simd_s32x4__insert_x64_enable() true
#endif _simd_s32x4_insert_x64_

#define _simd_s32x4_extract_safe(X,I) _simd_s32x4_extract_x1_safe(X,I)
#define _simd_s32x4_extract(X,I) _simd_s32x4_extract_x1(X,I)
#define _simd_s32x4_extract_enable() _simd_s32x4_extract_x1_enable()

#define _simd_s32x4_insert_safe(X,I,Y) _simd_s32x4_insert_x1_safe(X,I,Y)
#define _simd_s32x4_insert(X,I,Y) _simd_s32x4_insert_x1(X,I,Y)
#define _simd_s32x4_insert_enable() _simd_s32x4_insert_x1_enable()

//#ifndef _simd_s32x4_splitlo
//	#define _simd_s32x4_splitlo(X) _simd_s32x2_extract_x2(X,0)
//	#define _simd_s32x4_splitlo_enable() _simd_s32x2_extract_x2_enable()
//#endif

//#ifndef _simd_s32x4_splithi
//	#define _simd_s32x4_splithi(X) _simd_s32x2_extract_x2(X,1)
//	#define _simd_s32x4_splithi_enable() _simd_s32x2_extract_x2_enable()
//#endif

//#ifndef _simd_s32x4_combine
//	#define _simd_s32x4_combine(X,Y) _simd_s32x4_insert_x2(_simd_s32x4_insert_x2(_simd_s32x4_fill_undefined(), 0, X), 1, Y)
//	#define _simd_s32x4_combine_enable() (_simd_s32x4_insert_x2_enable() && _simd_s32x4_fill_undefined_enable())
//#endif

#define _simd_s32x8_extract_x1_safe(X,I) (reinterpret_cast<const _simd_s32x8*>(&X)[I])
#ifdef _simd_s32x8_extract_x1_
#define _simd_s32x8_extract_x1(X,I) _simd_s32x8_extract_x1_(X,I)
#define _simd_s32x8__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_extract_x1_instruction_set>()
#else
#define _simd_s32x8_extract_x1(X,I) _simd_s32x8_extract_x1_safe(X,I)
#define _simd_s32x8__extract_x1_enable() true
#endif _simd_s32x8_extract_x1_

#define _simd_s32x8_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_s32x8*>(&X)[I] = Y)
#ifdef _simd_s32x8_insert_x1_
#define _simd_s32x8_insert_x1(X,I,Y) _simd_s32x8_insert_x1_(X,I,Y)
#define _simd_s32x8__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_insert_x1_instruction_set>()
#else
#define _simd_s32x8_insert_x1(X,I,Y) _simd_s32x8_insert_x1_safe(X,I,Y)
#define _simd_s32x8__insert_x1_enable() true
#endif _simd_s32x8_insert_x1_

#define _simd_s32x8_extract_x2_safe(X,I) (reinterpret_cast<const _simd_s32x8*>(&X)[I])
#ifdef _simd_s32x8_extract_x2_
#define _simd_s32x8_extract_x2(X,I) _simd_s32x8_extract_x2_(X,I)
#define _simd_s32x8__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_extract_x2_instruction_set>()
#else
#define _simd_s32x8_extract_x2(X,I) _simd_s32x8_extract_x2_safe(X,I)
#define _simd_s32x8__extract_x2_enable() true
#endif _simd_s32x8_extract_x2_

#define _simd_s32x8_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_s32x8*>(&X)[I] = Y)
#ifdef _simd_s32x8_insert_x2_
#define _simd_s32x8_insert_x2(X,I,Y) _simd_s32x8_insert_x2_(X,I,Y)
#define _simd_s32x8__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_insert_x2_instruction_set>()
#else
#define _simd_s32x8_insert_x2(X,I,Y) _simd_s32x8_insert_x2_safe(X,I,Y)
#define _simd_s32x8__insert_x2_enable() true
#endif _simd_s32x8_insert_x2_

#define _simd_s32x8_extract_x4_safe(X,I) (reinterpret_cast<const _simd_s32x8*>(&X)[I])
#ifdef _simd_s32x8_extract_x4_
#define _simd_s32x8_extract_x4(X,I) _simd_s32x8_extract_x4_(X,I)
#define _simd_s32x8__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_extract_x4_instruction_set>()
#else
#define _simd_s32x8_extract_x4(X,I) _simd_s32x8_extract_x4_safe(X,I)
#define _simd_s32x8__extract_x4_enable() true
#endif _simd_s32x8_extract_x4_

#define _simd_s32x8_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_s32x8*>(&X)[I] = Y)
#ifdef _simd_s32x8_insert_x4_
#define _simd_s32x8_insert_x4(X,I,Y) _simd_s32x8_insert_x4_(X,I,Y)
#define _simd_s32x8__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_insert_x4_instruction_set>()
#else
#define _simd_s32x8_insert_x4(X,I,Y) _simd_s32x8_insert_x4_safe(X,I,Y)
#define _simd_s32x8__insert_x4_enable() true
#endif _simd_s32x8_insert_x4_

#define _simd_s32x8_extract_x16_safe(X,I) _simd_s32x8_insert_x8_safe(_simd_s32x8_fill_undefined_safe(),0,X)
#ifdef _simd_s32x8_extract_x16_
#define _simd_s32x8_extract_x16(X,I) _simd_s32x8_extract_x16_(X,I)
#define _simd_s32x8__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_extract_x16_instruction_set>()
#else
#define _simd_s32x8_extract_x16(X,I) _simd_s32x8_extract_x16_safe(X,I)
#define _simd_s32x8__extract_x16_enable() true
#endif _simd_s32x8_extract_x16_

#define _simd_s32x8_insert_x16_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s32x1) * 16)
#ifdef _simd_s32x8_insert_x16_
#define _simd_s32x8_insert_x16(X,I,Y) _simd_s32x8_insert_x16_(X,I,Y)
#define _simd_s32x8__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_insert_x16_instruction_set>()
#else
#define _simd_s32x8_insert_x16(X,I,Y) _simd_s32x8_insert_x16_safe(X,I,Y)
#define _simd_s32x8__insert_x16_enable() true
#endif _simd_s32x8_insert_x16_

#define _simd_s32x8_extract_x32_safe(X,I) _simd_s32x8_insert_x8_safe(_simd_s32x8_fill_undefined_safe(),0,X)
#ifdef _simd_s32x8_extract_x32_
#define _simd_s32x8_extract_x32(X,I) _simd_s32x8_extract_x32_(X,I)
#define _simd_s32x8__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_extract_x32_instruction_set>()
#else
#define _simd_s32x8_extract_x32(X,I) _simd_s32x8_extract_x32_safe(X,I)
#define _simd_s32x8__extract_x32_enable() true
#endif _simd_s32x8_extract_x32_

#define _simd_s32x8_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s32x1) * 32)
#ifdef _simd_s32x8_insert_x32_
#define _simd_s32x8_insert_x32(X,I,Y) _simd_s32x8_insert_x32_(X,I,Y)
#define _simd_s32x8__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_insert_x32_instruction_set>()
#else
#define _simd_s32x8_insert_x32(X,I,Y) _simd_s32x8_insert_x32_safe(X,I,Y)
#define _simd_s32x8__insert_x32_enable() true
#endif _simd_s32x8_insert_x32_

#define _simd_s32x8_extract_x64_safe(X,I) _simd_s32x8_insert_x8_safe(_simd_s32x8_fill_undefined_safe(),0,X)
#ifdef _simd_s32x8_extract_x64_
#define _simd_s32x8_extract_x64(X,I) _simd_s32x8_extract_x64_(X,I)
#define _simd_s32x8__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_extract_x64_instruction_set>()
#else
#define _simd_s32x8_extract_x64(X,I) _simd_s32x8_extract_x64_safe(X,I)
#define _simd_s32x8__extract_x64_enable() true
#endif _simd_s32x8_extract_x64_

#define _simd_s32x8_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s32x1) * 64)
#ifdef _simd_s32x8_insert_x64_
#define _simd_s32x8_insert_x64(X,I,Y) _simd_s32x8_insert_x64_(X,I,Y)
#define _simd_s32x8__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_insert_x64_instruction_set>()
#else
#define _simd_s32x8_insert_x64(X,I,Y) _simd_s32x8_insert_x64_safe(X,I,Y)
#define _simd_s32x8__insert_x64_enable() true
#endif _simd_s32x8_insert_x64_

#define _simd_s32x8_extract_safe(X,I) _simd_s32x8_extract_x1_safe(X,I)
#define _simd_s32x8_extract(X,I) _simd_s32x8_extract_x1(X,I)
#define _simd_s32x8_extract_enable() _simd_s32x8_extract_x1_enable()

#define _simd_s32x8_insert_safe(X,I,Y) _simd_s32x8_insert_x1_safe(X,I,Y)
#define _simd_s32x8_insert(X,I,Y) _simd_s32x8_insert_x1(X,I,Y)
#define _simd_s32x8_insert_enable() _simd_s32x8_insert_x1_enable()

//#ifndef _simd_s32x8_splitlo
//	#define _simd_s32x8_splitlo(X) _simd_s32x4_extract_x4(X,0)
//	#define _simd_s32x8_splitlo_enable() _simd_s32x4_extract_x4_enable()
//#endif

//#ifndef _simd_s32x8_splithi
//	#define _simd_s32x8_splithi(X) _simd_s32x4_extract_x4(X,1)
//	#define _simd_s32x8_splithi_enable() _simd_s32x4_extract_x4_enable()
//#endif

//#ifndef _simd_s32x8_combine
//	#define _simd_s32x8_combine(X,Y) _simd_s32x8_insert_x4(_simd_s32x8_insert_x4(_simd_s32x8_fill_undefined(), 0, X), 1, Y)
//	#define _simd_s32x8_combine_enable() (_simd_s32x8_insert_x4_enable() && _simd_s32x8_fill_undefined_enable())
//#endif

#define _simd_s32x16_extract_x1_safe(X,I) (reinterpret_cast<const _simd_s32x16*>(&X)[I])
#ifdef _simd_s32x16_extract_x1_
#define _simd_s32x16_extract_x1(X,I) _simd_s32x16_extract_x1_(X,I)
#define _simd_s32x16__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_extract_x1_instruction_set>()
#else
#define _simd_s32x16_extract_x1(X,I) _simd_s32x16_extract_x1_safe(X,I)
#define _simd_s32x16__extract_x1_enable() true
#endif _simd_s32x16_extract_x1_

#define _simd_s32x16_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_s32x16*>(&X)[I] = Y)
#ifdef _simd_s32x16_insert_x1_
#define _simd_s32x16_insert_x1(X,I,Y) _simd_s32x16_insert_x1_(X,I,Y)
#define _simd_s32x16__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_insert_x1_instruction_set>()
#else
#define _simd_s32x16_insert_x1(X,I,Y) _simd_s32x16_insert_x1_safe(X,I,Y)
#define _simd_s32x16__insert_x1_enable() true
#endif _simd_s32x16_insert_x1_

#define _simd_s32x16_extract_x2_safe(X,I) (reinterpret_cast<const _simd_s32x16*>(&X)[I])
#ifdef _simd_s32x16_extract_x2_
#define _simd_s32x16_extract_x2(X,I) _simd_s32x16_extract_x2_(X,I)
#define _simd_s32x16__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_extract_x2_instruction_set>()
#else
#define _simd_s32x16_extract_x2(X,I) _simd_s32x16_extract_x2_safe(X,I)
#define _simd_s32x16__extract_x2_enable() true
#endif _simd_s32x16_extract_x2_

#define _simd_s32x16_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_s32x16*>(&X)[I] = Y)
#ifdef _simd_s32x16_insert_x2_
#define _simd_s32x16_insert_x2(X,I,Y) _simd_s32x16_insert_x2_(X,I,Y)
#define _simd_s32x16__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_insert_x2_instruction_set>()
#else
#define _simd_s32x16_insert_x2(X,I,Y) _simd_s32x16_insert_x2_safe(X,I,Y)
#define _simd_s32x16__insert_x2_enable() true
#endif _simd_s32x16_insert_x2_

#define _simd_s32x16_extract_x4_safe(X,I) (reinterpret_cast<const _simd_s32x16*>(&X)[I])
#ifdef _simd_s32x16_extract_x4_
#define _simd_s32x16_extract_x4(X,I) _simd_s32x16_extract_x4_(X,I)
#define _simd_s32x16__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_extract_x4_instruction_set>()
#else
#define _simd_s32x16_extract_x4(X,I) _simd_s32x16_extract_x4_safe(X,I)
#define _simd_s32x16__extract_x4_enable() true
#endif _simd_s32x16_extract_x4_

#define _simd_s32x16_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_s32x16*>(&X)[I] = Y)
#ifdef _simd_s32x16_insert_x4_
#define _simd_s32x16_insert_x4(X,I,Y) _simd_s32x16_insert_x4_(X,I,Y)
#define _simd_s32x16__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_insert_x4_instruction_set>()
#else
#define _simd_s32x16_insert_x4(X,I,Y) _simd_s32x16_insert_x4_safe(X,I,Y)
#define _simd_s32x16__insert_x4_enable() true
#endif _simd_s32x16_insert_x4_

#define _simd_s32x16_extract_x8_safe(X,I) (reinterpret_cast<const _simd_s32x16*>(&X)[I])
#ifdef _simd_s32x16_extract_x8_
#define _simd_s32x16_extract_x8(X,I) _simd_s32x16_extract_x8_(X,I)
#define _simd_s32x16__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_extract_x8_instruction_set>()
#else
#define _simd_s32x16_extract_x8(X,I) _simd_s32x16_extract_x8_safe(X,I)
#define _simd_s32x16__extract_x8_enable() true
#endif _simd_s32x16_extract_x8_

#define _simd_s32x16_insert_x8_safe(X,I,Y) (reinterpret_cast<_simd_s32x16*>(&X)[I] = Y)
#ifdef _simd_s32x16_insert_x8_
#define _simd_s32x16_insert_x8(X,I,Y) _simd_s32x16_insert_x8_(X,I,Y)
#define _simd_s32x16__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_insert_x8_instruction_set>()
#else
#define _simd_s32x16_insert_x8(X,I,Y) _simd_s32x16_insert_x8_safe(X,I,Y)
#define _simd_s32x16__insert_x8_enable() true
#endif _simd_s32x16_insert_x8_

#define _simd_s32x16_extract_x32_safe(X,I) _simd_s32x16_insert_x16_safe(_simd_s32x16_fill_undefined_safe(),0,X)
#ifdef _simd_s32x16_extract_x32_
#define _simd_s32x16_extract_x32(X,I) _simd_s32x16_extract_x32_(X,I)
#define _simd_s32x16__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_extract_x32_instruction_set>()
#else
#define _simd_s32x16_extract_x32(X,I) _simd_s32x16_extract_x32_safe(X,I)
#define _simd_s32x16__extract_x32_enable() true
#endif _simd_s32x16_extract_x32_

#define _simd_s32x16_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s32x1) * 32)
#ifdef _simd_s32x16_insert_x32_
#define _simd_s32x16_insert_x32(X,I,Y) _simd_s32x16_insert_x32_(X,I,Y)
#define _simd_s32x16__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_insert_x32_instruction_set>()
#else
#define _simd_s32x16_insert_x32(X,I,Y) _simd_s32x16_insert_x32_safe(X,I,Y)
#define _simd_s32x16__insert_x32_enable() true
#endif _simd_s32x16_insert_x32_

#define _simd_s32x16_extract_x64_safe(X,I) _simd_s32x16_insert_x16_safe(_simd_s32x16_fill_undefined_safe(),0,X)
#ifdef _simd_s32x16_extract_x64_
#define _simd_s32x16_extract_x64(X,I) _simd_s32x16_extract_x64_(X,I)
#define _simd_s32x16__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_extract_x64_instruction_set>()
#else
#define _simd_s32x16_extract_x64(X,I) _simd_s32x16_extract_x64_safe(X,I)
#define _simd_s32x16__extract_x64_enable() true
#endif _simd_s32x16_extract_x64_

#define _simd_s32x16_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s32x1) * 64)
#ifdef _simd_s32x16_insert_x64_
#define _simd_s32x16_insert_x64(X,I,Y) _simd_s32x16_insert_x64_(X,I,Y)
#define _simd_s32x16__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_insert_x64_instruction_set>()
#else
#define _simd_s32x16_insert_x64(X,I,Y) _simd_s32x16_insert_x64_safe(X,I,Y)
#define _simd_s32x16__insert_x64_enable() true
#endif _simd_s32x16_insert_x64_

#define _simd_s32x16_extract_safe(X,I) _simd_s32x16_extract_x1_safe(X,I)
#define _simd_s32x16_extract(X,I) _simd_s32x16_extract_x1(X,I)
#define _simd_s32x16_extract_enable() _simd_s32x16_extract_x1_enable()

#define _simd_s32x16_insert_safe(X,I,Y) _simd_s32x16_insert_x1_safe(X,I,Y)
#define _simd_s32x16_insert(X,I,Y) _simd_s32x16_insert_x1(X,I,Y)
#define _simd_s32x16_insert_enable() _simd_s32x16_insert_x1_enable()

//#ifndef _simd_s32x16_splitlo
//	#define _simd_s32x16_splitlo(X) _simd_s32x8_extract_x8(X,0)
//	#define _simd_s32x16_splitlo_enable() _simd_s32x8_extract_x8_enable()
//#endif

//#ifndef _simd_s32x16_splithi
//	#define _simd_s32x16_splithi(X) _simd_s32x8_extract_x8(X,1)
//	#define _simd_s32x16_splithi_enable() _simd_s32x8_extract_x8_enable()
//#endif

//#ifndef _simd_s32x16_combine
//	#define _simd_s32x16_combine(X,Y) _simd_s32x16_insert_x8(_simd_s32x16_insert_x8(_simd_s32x16_fill_undefined(), 0, X), 1, Y)
//	#define _simd_s32x16_combine_enable() (_simd_s32x16_insert_x8_enable() && _simd_s32x16_fill_undefined_enable())
//#endif

#define _simd_s32x32_extract_x1_safe(X,I) (reinterpret_cast<const _simd_s32x32*>(&X)[I])
#ifdef _simd_s32x32_extract_x1_
#define _simd_s32x32_extract_x1(X,I) _simd_s32x32_extract_x1_(X,I)
#define _simd_s32x32__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_extract_x1_instruction_set>()
#else
#define _simd_s32x32_extract_x1(X,I) _simd_s32x32_extract_x1_safe(X,I)
#define _simd_s32x32__extract_x1_enable() true
#endif _simd_s32x32_extract_x1_

#define _simd_s32x32_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_s32x32*>(&X)[I] = Y)
#ifdef _simd_s32x32_insert_x1_
#define _simd_s32x32_insert_x1(X,I,Y) _simd_s32x32_insert_x1_(X,I,Y)
#define _simd_s32x32__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_insert_x1_instruction_set>()
#else
#define _simd_s32x32_insert_x1(X,I,Y) _simd_s32x32_insert_x1_safe(X,I,Y)
#define _simd_s32x32__insert_x1_enable() true
#endif _simd_s32x32_insert_x1_

#define _simd_s32x32_extract_x2_safe(X,I) (reinterpret_cast<const _simd_s32x32*>(&X)[I])
#ifdef _simd_s32x32_extract_x2_
#define _simd_s32x32_extract_x2(X,I) _simd_s32x32_extract_x2_(X,I)
#define _simd_s32x32__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_extract_x2_instruction_set>()
#else
#define _simd_s32x32_extract_x2(X,I) _simd_s32x32_extract_x2_safe(X,I)
#define _simd_s32x32__extract_x2_enable() true
#endif _simd_s32x32_extract_x2_

#define _simd_s32x32_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_s32x32*>(&X)[I] = Y)
#ifdef _simd_s32x32_insert_x2_
#define _simd_s32x32_insert_x2(X,I,Y) _simd_s32x32_insert_x2_(X,I,Y)
#define _simd_s32x32__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_insert_x2_instruction_set>()
#else
#define _simd_s32x32_insert_x2(X,I,Y) _simd_s32x32_insert_x2_safe(X,I,Y)
#define _simd_s32x32__insert_x2_enable() true
#endif _simd_s32x32_insert_x2_

#define _simd_s32x32_extract_x4_safe(X,I) (reinterpret_cast<const _simd_s32x32*>(&X)[I])
#ifdef _simd_s32x32_extract_x4_
#define _simd_s32x32_extract_x4(X,I) _simd_s32x32_extract_x4_(X,I)
#define _simd_s32x32__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_extract_x4_instruction_set>()
#else
#define _simd_s32x32_extract_x4(X,I) _simd_s32x32_extract_x4_safe(X,I)
#define _simd_s32x32__extract_x4_enable() true
#endif _simd_s32x32_extract_x4_

#define _simd_s32x32_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_s32x32*>(&X)[I] = Y)
#ifdef _simd_s32x32_insert_x4_
#define _simd_s32x32_insert_x4(X,I,Y) _simd_s32x32_insert_x4_(X,I,Y)
#define _simd_s32x32__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_insert_x4_instruction_set>()
#else
#define _simd_s32x32_insert_x4(X,I,Y) _simd_s32x32_insert_x4_safe(X,I,Y)
#define _simd_s32x32__insert_x4_enable() true
#endif _simd_s32x32_insert_x4_

#define _simd_s32x32_extract_x8_safe(X,I) (reinterpret_cast<const _simd_s32x32*>(&X)[I])
#ifdef _simd_s32x32_extract_x8_
#define _simd_s32x32_extract_x8(X,I) _simd_s32x32_extract_x8_(X,I)
#define _simd_s32x32__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_extract_x8_instruction_set>()
#else
#define _simd_s32x32_extract_x8(X,I) _simd_s32x32_extract_x8_safe(X,I)
#define _simd_s32x32__extract_x8_enable() true
#endif _simd_s32x32_extract_x8_

#define _simd_s32x32_insert_x8_safe(X,I,Y) (reinterpret_cast<_simd_s32x32*>(&X)[I] = Y)
#ifdef _simd_s32x32_insert_x8_
#define _simd_s32x32_insert_x8(X,I,Y) _simd_s32x32_insert_x8_(X,I,Y)
#define _simd_s32x32__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_insert_x8_instruction_set>()
#else
#define _simd_s32x32_insert_x8(X,I,Y) _simd_s32x32_insert_x8_safe(X,I,Y)
#define _simd_s32x32__insert_x8_enable() true
#endif _simd_s32x32_insert_x8_

#define _simd_s32x32_extract_x16_safe(X,I) (reinterpret_cast<const _simd_s32x32*>(&X)[I])
#ifdef _simd_s32x32_extract_x16_
#define _simd_s32x32_extract_x16(X,I) _simd_s32x32_extract_x16_(X,I)
#define _simd_s32x32__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_extract_x16_instruction_set>()
#else
#define _simd_s32x32_extract_x16(X,I) _simd_s32x32_extract_x16_safe(X,I)
#define _simd_s32x32__extract_x16_enable() true
#endif _simd_s32x32_extract_x16_

#define _simd_s32x32_insert_x16_safe(X,I,Y) (reinterpret_cast<_simd_s32x32*>(&X)[I] = Y)
#ifdef _simd_s32x32_insert_x16_
#define _simd_s32x32_insert_x16(X,I,Y) _simd_s32x32_insert_x16_(X,I,Y)
#define _simd_s32x32__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_insert_x16_instruction_set>()
#else
#define _simd_s32x32_insert_x16(X,I,Y) _simd_s32x32_insert_x16_safe(X,I,Y)
#define _simd_s32x32__insert_x16_enable() true
#endif _simd_s32x32_insert_x16_

#define _simd_s32x32_extract_x64_safe(X,I) _simd_s32x32_insert_x32_safe(_simd_s32x32_fill_undefined_safe(),0,X)
#ifdef _simd_s32x32_extract_x64_
#define _simd_s32x32_extract_x64(X,I) _simd_s32x32_extract_x64_(X,I)
#define _simd_s32x32__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_extract_x64_instruction_set>()
#else
#define _simd_s32x32_extract_x64(X,I) _simd_s32x32_extract_x64_safe(X,I)
#define _simd_s32x32__extract_x64_enable() true
#endif _simd_s32x32_extract_x64_

#define _simd_s32x32_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s32x1) * 64)
#ifdef _simd_s32x32_insert_x64_
#define _simd_s32x32_insert_x64(X,I,Y) _simd_s32x32_insert_x64_(X,I,Y)
#define _simd_s32x32__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_insert_x64_instruction_set>()
#else
#define _simd_s32x32_insert_x64(X,I,Y) _simd_s32x32_insert_x64_safe(X,I,Y)
#define _simd_s32x32__insert_x64_enable() true
#endif _simd_s32x32_insert_x64_

#define _simd_s32x32_extract_safe(X,I) _simd_s32x32_extract_x1_safe(X,I)
#define _simd_s32x32_extract(X,I) _simd_s32x32_extract_x1(X,I)
#define _simd_s32x32_extract_enable() _simd_s32x32_extract_x1_enable()

#define _simd_s32x32_insert_safe(X,I,Y) _simd_s32x32_insert_x1_safe(X,I,Y)
#define _simd_s32x32_insert(X,I,Y) _simd_s32x32_insert_x1(X,I,Y)
#define _simd_s32x32_insert_enable() _simd_s32x32_insert_x1_enable()

//#ifndef _simd_s32x32_splitlo
//	#define _simd_s32x32_splitlo(X) _simd_s32x16_extract_x16(X,0)
//	#define _simd_s32x32_splitlo_enable() _simd_s32x16_extract_x16_enable()
//#endif

//#ifndef _simd_s32x32_splithi
//	#define _simd_s32x32_splithi(X) _simd_s32x16_extract_x16(X,1)
//	#define _simd_s32x32_splithi_enable() _simd_s32x16_extract_x16_enable()
//#endif

//#ifndef _simd_s32x32_combine
//	#define _simd_s32x32_combine(X,Y) _simd_s32x32_insert_x16(_simd_s32x32_insert_x16(_simd_s32x32_fill_undefined(), 0, X), 1, Y)
//	#define _simd_s32x32_combine_enable() (_simd_s32x32_insert_x16_enable() && _simd_s32x32_fill_undefined_enable())
//#endif

#define _simd_s32x64_extract_x1_safe(X,I) (reinterpret_cast<const _simd_s32x64*>(&X)[I])
#ifdef _simd_s32x64_extract_x1_
#define _simd_s32x64_extract_x1(X,I) _simd_s32x64_extract_x1_(X,I)
#define _simd_s32x64__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_extract_x1_instruction_set>()
#else
#define _simd_s32x64_extract_x1(X,I) _simd_s32x64_extract_x1_safe(X,I)
#define _simd_s32x64__extract_x1_enable() true
#endif _simd_s32x64_extract_x1_

#define _simd_s32x64_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_s32x64*>(&X)[I] = Y)
#ifdef _simd_s32x64_insert_x1_
#define _simd_s32x64_insert_x1(X,I,Y) _simd_s32x64_insert_x1_(X,I,Y)
#define _simd_s32x64__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_insert_x1_instruction_set>()
#else
#define _simd_s32x64_insert_x1(X,I,Y) _simd_s32x64_insert_x1_safe(X,I,Y)
#define _simd_s32x64__insert_x1_enable() true
#endif _simd_s32x64_insert_x1_

#define _simd_s32x64_extract_x2_safe(X,I) (reinterpret_cast<const _simd_s32x64*>(&X)[I])
#ifdef _simd_s32x64_extract_x2_
#define _simd_s32x64_extract_x2(X,I) _simd_s32x64_extract_x2_(X,I)
#define _simd_s32x64__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_extract_x2_instruction_set>()
#else
#define _simd_s32x64_extract_x2(X,I) _simd_s32x64_extract_x2_safe(X,I)
#define _simd_s32x64__extract_x2_enable() true
#endif _simd_s32x64_extract_x2_

#define _simd_s32x64_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_s32x64*>(&X)[I] = Y)
#ifdef _simd_s32x64_insert_x2_
#define _simd_s32x64_insert_x2(X,I,Y) _simd_s32x64_insert_x2_(X,I,Y)
#define _simd_s32x64__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_insert_x2_instruction_set>()
#else
#define _simd_s32x64_insert_x2(X,I,Y) _simd_s32x64_insert_x2_safe(X,I,Y)
#define _simd_s32x64__insert_x2_enable() true
#endif _simd_s32x64_insert_x2_

#define _simd_s32x64_extract_x4_safe(X,I) (reinterpret_cast<const _simd_s32x64*>(&X)[I])
#ifdef _simd_s32x64_extract_x4_
#define _simd_s32x64_extract_x4(X,I) _simd_s32x64_extract_x4_(X,I)
#define _simd_s32x64__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_extract_x4_instruction_set>()
#else
#define _simd_s32x64_extract_x4(X,I) _simd_s32x64_extract_x4_safe(X,I)
#define _simd_s32x64__extract_x4_enable() true
#endif _simd_s32x64_extract_x4_

#define _simd_s32x64_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_s32x64*>(&X)[I] = Y)
#ifdef _simd_s32x64_insert_x4_
#define _simd_s32x64_insert_x4(X,I,Y) _simd_s32x64_insert_x4_(X,I,Y)
#define _simd_s32x64__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_insert_x4_instruction_set>()
#else
#define _simd_s32x64_insert_x4(X,I,Y) _simd_s32x64_insert_x4_safe(X,I,Y)
#define _simd_s32x64__insert_x4_enable() true
#endif _simd_s32x64_insert_x4_

#define _simd_s32x64_extract_x8_safe(X,I) (reinterpret_cast<const _simd_s32x64*>(&X)[I])
#ifdef _simd_s32x64_extract_x8_
#define _simd_s32x64_extract_x8(X,I) _simd_s32x64_extract_x8_(X,I)
#define _simd_s32x64__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_extract_x8_instruction_set>()
#else
#define _simd_s32x64_extract_x8(X,I) _simd_s32x64_extract_x8_safe(X,I)
#define _simd_s32x64__extract_x8_enable() true
#endif _simd_s32x64_extract_x8_

#define _simd_s32x64_insert_x8_safe(X,I,Y) (reinterpret_cast<_simd_s32x64*>(&X)[I] = Y)
#ifdef _simd_s32x64_insert_x8_
#define _simd_s32x64_insert_x8(X,I,Y) _simd_s32x64_insert_x8_(X,I,Y)
#define _simd_s32x64__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_insert_x8_instruction_set>()
#else
#define _simd_s32x64_insert_x8(X,I,Y) _simd_s32x64_insert_x8_safe(X,I,Y)
#define _simd_s32x64__insert_x8_enable() true
#endif _simd_s32x64_insert_x8_

#define _simd_s32x64_extract_x16_safe(X,I) (reinterpret_cast<const _simd_s32x64*>(&X)[I])
#ifdef _simd_s32x64_extract_x16_
#define _simd_s32x64_extract_x16(X,I) _simd_s32x64_extract_x16_(X,I)
#define _simd_s32x64__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_extract_x16_instruction_set>()
#else
#define _simd_s32x64_extract_x16(X,I) _simd_s32x64_extract_x16_safe(X,I)
#define _simd_s32x64__extract_x16_enable() true
#endif _simd_s32x64_extract_x16_

#define _simd_s32x64_insert_x16_safe(X,I,Y) (reinterpret_cast<_simd_s32x64*>(&X)[I] = Y)
#ifdef _simd_s32x64_insert_x16_
#define _simd_s32x64_insert_x16(X,I,Y) _simd_s32x64_insert_x16_(X,I,Y)
#define _simd_s32x64__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_insert_x16_instruction_set>()
#else
#define _simd_s32x64_insert_x16(X,I,Y) _simd_s32x64_insert_x16_safe(X,I,Y)
#define _simd_s32x64__insert_x16_enable() true
#endif _simd_s32x64_insert_x16_

#define _simd_s32x64_extract_x32_safe(X,I) (reinterpret_cast<const _simd_s32x64*>(&X)[I])
#ifdef _simd_s32x64_extract_x32_
#define _simd_s32x64_extract_x32(X,I) _simd_s32x64_extract_x32_(X,I)
#define _simd_s32x64__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_extract_x32_instruction_set>()
#else
#define _simd_s32x64_extract_x32(X,I) _simd_s32x64_extract_x32_safe(X,I)
#define _simd_s32x64__extract_x32_enable() true
#endif _simd_s32x64_extract_x32_

#define _simd_s32x64_insert_x32_safe(X,I,Y) (reinterpret_cast<_simd_s32x64*>(&X)[I] = Y)
#ifdef _simd_s32x64_insert_x32_
#define _simd_s32x64_insert_x32(X,I,Y) _simd_s32x64_insert_x32_(X,I,Y)
#define _simd_s32x64__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_insert_x32_instruction_set>()
#else
#define _simd_s32x64_insert_x32(X,I,Y) _simd_s32x64_insert_x32_safe(X,I,Y)
#define _simd_s32x64__insert_x32_enable() true
#endif _simd_s32x64_insert_x32_

#define _simd_s32x64_extract_safe(X,I) _simd_s32x64_extract_x1_safe(X,I)
#define _simd_s32x64_extract(X,I) _simd_s32x64_extract_x1(X,I)
#define _simd_s32x64_extract_enable() _simd_s32x64_extract_x1_enable()

#define _simd_s32x64_insert_safe(X,I,Y) _simd_s32x64_insert_x1_safe(X,I,Y)
#define _simd_s32x64_insert(X,I,Y) _simd_s32x64_insert_x1(X,I,Y)
#define _simd_s32x64_insert_enable() _simd_s32x64_insert_x1_enable()

//#ifndef _simd_s32x64_splitlo
//	#define _simd_s32x64_splitlo(X) _simd_s32x32_extract_x32(X,0)
//	#define _simd_s32x64_splitlo_enable() _simd_s32x32_extract_x32_enable()
//#endif

//#ifndef _simd_s32x64_splithi
//	#define _simd_s32x64_splithi(X) _simd_s32x32_extract_x32(X,1)
//	#define _simd_s32x64_splithi_enable() _simd_s32x32_extract_x32_enable()
//#endif

//#ifndef _simd_s32x64_combine
//	#define _simd_s32x64_combine(X,Y) _simd_s32x64_insert_x32(_simd_s32x64_insert_x32(_simd_s32x64_fill_undefined(), 0, X), 1, Y)
//	#define _simd_s32x64_combine_enable() (_simd_s32x64_insert_x32_enable() && _simd_s32x64_fill_undefined_enable())
//#endif

// -- u32 --

#define _simd_u32x2_extract_x1_safe(X,I) (reinterpret_cast<const _simd_u32x2*>(&X)[I])
#ifdef _simd_u32x2_extract_x1_
#define _simd_u32x2_extract_x1(X,I) _simd_u32x2_extract_x1_(X,I)
#define _simd_u32x2__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_extract_x1_instruction_set>()
#else
#define _simd_u32x2_extract_x1(X,I) _simd_u32x2_extract_x1_safe(X,I)
#define _simd_u32x2__extract_x1_enable() true
#endif _simd_u32x2_extract_x1_

#define _simd_u32x2_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_u32x2*>(&X)[I] = Y)
#ifdef _simd_u32x2_insert_x1_
#define _simd_u32x2_insert_x1(X,I,Y) _simd_u32x2_insert_x1_(X,I,Y)
#define _simd_u32x2__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_insert_x1_instruction_set>()
#else
#define _simd_u32x2_insert_x1(X,I,Y) _simd_u32x2_insert_x1_safe(X,I,Y)
#define _simd_u32x2__insert_x1_enable() true
#endif _simd_u32x2_insert_x1_

#define _simd_u32x2_extract_x4_safe(X,I) _simd_u32x2_insert_x2_safe(_simd_u32x2_fill_undefined_safe(),0,X)
#ifdef _simd_u32x2_extract_x4_
#define _simd_u32x2_extract_x4(X,I) _simd_u32x2_extract_x4_(X,I)
#define _simd_u32x2__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_extract_x4_instruction_set>()
#else
#define _simd_u32x2_extract_x4(X,I) _simd_u32x2_extract_x4_safe(X,I)
#define _simd_u32x2__extract_x4_enable() true
#endif _simd_u32x2_extract_x4_

#define _simd_u32x2_insert_x4_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u32x1) * 4)
#ifdef _simd_u32x2_insert_x4_
#define _simd_u32x2_insert_x4(X,I,Y) _simd_u32x2_insert_x4_(X,I,Y)
#define _simd_u32x2__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_insert_x4_instruction_set>()
#else
#define _simd_u32x2_insert_x4(X,I,Y) _simd_u32x2_insert_x4_safe(X,I,Y)
#define _simd_u32x2__insert_x4_enable() true
#endif _simd_u32x2_insert_x4_

#define _simd_u32x2_extract_x8_safe(X,I) _simd_u32x2_insert_x2_safe(_simd_u32x2_fill_undefined_safe(),0,X)
#ifdef _simd_u32x2_extract_x8_
#define _simd_u32x2_extract_x8(X,I) _simd_u32x2_extract_x8_(X,I)
#define _simd_u32x2__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_extract_x8_instruction_set>()
#else
#define _simd_u32x2_extract_x8(X,I) _simd_u32x2_extract_x8_safe(X,I)
#define _simd_u32x2__extract_x8_enable() true
#endif _simd_u32x2_extract_x8_

#define _simd_u32x2_insert_x8_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u32x1) * 8)
#ifdef _simd_u32x2_insert_x8_
#define _simd_u32x2_insert_x8(X,I,Y) _simd_u32x2_insert_x8_(X,I,Y)
#define _simd_u32x2__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_insert_x8_instruction_set>()
#else
#define _simd_u32x2_insert_x8(X,I,Y) _simd_u32x2_insert_x8_safe(X,I,Y)
#define _simd_u32x2__insert_x8_enable() true
#endif _simd_u32x2_insert_x8_

#define _simd_u32x2_extract_x16_safe(X,I) _simd_u32x2_insert_x2_safe(_simd_u32x2_fill_undefined_safe(),0,X)
#ifdef _simd_u32x2_extract_x16_
#define _simd_u32x2_extract_x16(X,I) _simd_u32x2_extract_x16_(X,I)
#define _simd_u32x2__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_extract_x16_instruction_set>()
#else
#define _simd_u32x2_extract_x16(X,I) _simd_u32x2_extract_x16_safe(X,I)
#define _simd_u32x2__extract_x16_enable() true
#endif _simd_u32x2_extract_x16_

#define _simd_u32x2_insert_x16_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u32x1) * 16)
#ifdef _simd_u32x2_insert_x16_
#define _simd_u32x2_insert_x16(X,I,Y) _simd_u32x2_insert_x16_(X,I,Y)
#define _simd_u32x2__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_insert_x16_instruction_set>()
#else
#define _simd_u32x2_insert_x16(X,I,Y) _simd_u32x2_insert_x16_safe(X,I,Y)
#define _simd_u32x2__insert_x16_enable() true
#endif _simd_u32x2_insert_x16_

#define _simd_u32x2_extract_x32_safe(X,I) _simd_u32x2_insert_x2_safe(_simd_u32x2_fill_undefined_safe(),0,X)
#ifdef _simd_u32x2_extract_x32_
#define _simd_u32x2_extract_x32(X,I) _simd_u32x2_extract_x32_(X,I)
#define _simd_u32x2__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_extract_x32_instruction_set>()
#else
#define _simd_u32x2_extract_x32(X,I) _simd_u32x2_extract_x32_safe(X,I)
#define _simd_u32x2__extract_x32_enable() true
#endif _simd_u32x2_extract_x32_

#define _simd_u32x2_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u32x1) * 32)
#ifdef _simd_u32x2_insert_x32_
#define _simd_u32x2_insert_x32(X,I,Y) _simd_u32x2_insert_x32_(X,I,Y)
#define _simd_u32x2__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_insert_x32_instruction_set>()
#else
#define _simd_u32x2_insert_x32(X,I,Y) _simd_u32x2_insert_x32_safe(X,I,Y)
#define _simd_u32x2__insert_x32_enable() true
#endif _simd_u32x2_insert_x32_

#define _simd_u32x2_extract_x64_safe(X,I) _simd_u32x2_insert_x2_safe(_simd_u32x2_fill_undefined_safe(),0,X)
#ifdef _simd_u32x2_extract_x64_
#define _simd_u32x2_extract_x64(X,I) _simd_u32x2_extract_x64_(X,I)
#define _simd_u32x2__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_extract_x64_instruction_set>()
#else
#define _simd_u32x2_extract_x64(X,I) _simd_u32x2_extract_x64_safe(X,I)
#define _simd_u32x2__extract_x64_enable() true
#endif _simd_u32x2_extract_x64_

#define _simd_u32x2_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u32x1) * 64)
#ifdef _simd_u32x2_insert_x64_
#define _simd_u32x2_insert_x64(X,I,Y) _simd_u32x2_insert_x64_(X,I,Y)
#define _simd_u32x2__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_insert_x64_instruction_set>()
#else
#define _simd_u32x2_insert_x64(X,I,Y) _simd_u32x2_insert_x64_safe(X,I,Y)
#define _simd_u32x2__insert_x64_enable() true
#endif _simd_u32x2_insert_x64_

#define _simd_u32x2_extract_safe(X,I) _simd_u32x2_extract_x1_safe(X,I)
#define _simd_u32x2_extract(X,I) _simd_u32x2_extract_x1(X,I)
#define _simd_u32x2_extract_enable() _simd_u32x2_extract_x1_enable()

#define _simd_u32x2_insert_safe(X,I,Y) _simd_u32x2_insert_x1_safe(X,I,Y)
#define _simd_u32x2_insert(X,I,Y) _simd_u32x2_insert_x1(X,I,Y)
#define _simd_u32x2_insert_enable() _simd_u32x2_insert_x1_enable()

//#ifndef _simd_u32x2_splitlo
//	#define _simd_u32x2_splitlo(X) _simd_u32x1_extract_x1(X,0)
//	#define _simd_u32x2_splitlo_enable() _simd_u32x1_extract_x1_enable()
//#endif

//#ifndef _simd_u32x2_splithi
//	#define _simd_u32x2_splithi(X) _simd_u32x1_extract_x1(X,1)
//	#define _simd_u32x2_splithi_enable() _simd_u32x1_extract_x1_enable()
//#endif

//#ifndef _simd_u32x2_combine
//	#define _simd_u32x2_combine(X,Y) _simd_u32x2_insert_x1(_simd_u32x2_insert_x1(_simd_u32x2_fill_undefined(), 0, X), 1, Y)
//	#define _simd_u32x2_combine_enable() (_simd_u32x2_insert_x1_enable() && _simd_u32x2_fill_undefined_enable())
//#endif

#define _simd_u32x4_extract_x1_safe(X,I) (reinterpret_cast<const _simd_u32x4*>(&X)[I])
#ifdef _simd_u32x4_extract_x1_
#define _simd_u32x4_extract_x1(X,I) _simd_u32x4_extract_x1_(X,I)
#define _simd_u32x4__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_extract_x1_instruction_set>()
#else
#define _simd_u32x4_extract_x1(X,I) _simd_u32x4_extract_x1_safe(X,I)
#define _simd_u32x4__extract_x1_enable() true
#endif _simd_u32x4_extract_x1_

#define _simd_u32x4_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_u32x4*>(&X)[I] = Y)
#ifdef _simd_u32x4_insert_x1_
#define _simd_u32x4_insert_x1(X,I,Y) _simd_u32x4_insert_x1_(X,I,Y)
#define _simd_u32x4__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_insert_x1_instruction_set>()
#else
#define _simd_u32x4_insert_x1(X,I,Y) _simd_u32x4_insert_x1_safe(X,I,Y)
#define _simd_u32x4__insert_x1_enable() true
#endif _simd_u32x4_insert_x1_

#define _simd_u32x4_extract_x2_safe(X,I) (reinterpret_cast<const _simd_u32x4*>(&X)[I])
#ifdef _simd_u32x4_extract_x2_
#define _simd_u32x4_extract_x2(X,I) _simd_u32x4_extract_x2_(X,I)
#define _simd_u32x4__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_extract_x2_instruction_set>()
#else
#define _simd_u32x4_extract_x2(X,I) _simd_u32x4_extract_x2_safe(X,I)
#define _simd_u32x4__extract_x2_enable() true
#endif _simd_u32x4_extract_x2_

#define _simd_u32x4_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_u32x4*>(&X)[I] = Y)
#ifdef _simd_u32x4_insert_x2_
#define _simd_u32x4_insert_x2(X,I,Y) _simd_u32x4_insert_x2_(X,I,Y)
#define _simd_u32x4__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_insert_x2_instruction_set>()
#else
#define _simd_u32x4_insert_x2(X,I,Y) _simd_u32x4_insert_x2_safe(X,I,Y)
#define _simd_u32x4__insert_x2_enable() true
#endif _simd_u32x4_insert_x2_

#define _simd_u32x4_extract_x8_safe(X,I) _simd_u32x4_insert_x4_safe(_simd_u32x4_fill_undefined_safe(),0,X)
#ifdef _simd_u32x4_extract_x8_
#define _simd_u32x4_extract_x8(X,I) _simd_u32x4_extract_x8_(X,I)
#define _simd_u32x4__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_extract_x8_instruction_set>()
#else
#define _simd_u32x4_extract_x8(X,I) _simd_u32x4_extract_x8_safe(X,I)
#define _simd_u32x4__extract_x8_enable() true
#endif _simd_u32x4_extract_x8_

#define _simd_u32x4_insert_x8_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u32x1) * 8)
#ifdef _simd_u32x4_insert_x8_
#define _simd_u32x4_insert_x8(X,I,Y) _simd_u32x4_insert_x8_(X,I,Y)
#define _simd_u32x4__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_insert_x8_instruction_set>()
#else
#define _simd_u32x4_insert_x8(X,I,Y) _simd_u32x4_insert_x8_safe(X,I,Y)
#define _simd_u32x4__insert_x8_enable() true
#endif _simd_u32x4_insert_x8_

#define _simd_u32x4_extract_x16_safe(X,I) _simd_u32x4_insert_x4_safe(_simd_u32x4_fill_undefined_safe(),0,X)
#ifdef _simd_u32x4_extract_x16_
#define _simd_u32x4_extract_x16(X,I) _simd_u32x4_extract_x16_(X,I)
#define _simd_u32x4__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_extract_x16_instruction_set>()
#else
#define _simd_u32x4_extract_x16(X,I) _simd_u32x4_extract_x16_safe(X,I)
#define _simd_u32x4__extract_x16_enable() true
#endif _simd_u32x4_extract_x16_

#define _simd_u32x4_insert_x16_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u32x1) * 16)
#ifdef _simd_u32x4_insert_x16_
#define _simd_u32x4_insert_x16(X,I,Y) _simd_u32x4_insert_x16_(X,I,Y)
#define _simd_u32x4__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_insert_x16_instruction_set>()
#else
#define _simd_u32x4_insert_x16(X,I,Y) _simd_u32x4_insert_x16_safe(X,I,Y)
#define _simd_u32x4__insert_x16_enable() true
#endif _simd_u32x4_insert_x16_

#define _simd_u32x4_extract_x32_safe(X,I) _simd_u32x4_insert_x4_safe(_simd_u32x4_fill_undefined_safe(),0,X)
#ifdef _simd_u32x4_extract_x32_
#define _simd_u32x4_extract_x32(X,I) _simd_u32x4_extract_x32_(X,I)
#define _simd_u32x4__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_extract_x32_instruction_set>()
#else
#define _simd_u32x4_extract_x32(X,I) _simd_u32x4_extract_x32_safe(X,I)
#define _simd_u32x4__extract_x32_enable() true
#endif _simd_u32x4_extract_x32_

#define _simd_u32x4_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u32x1) * 32)
#ifdef _simd_u32x4_insert_x32_
#define _simd_u32x4_insert_x32(X,I,Y) _simd_u32x4_insert_x32_(X,I,Y)
#define _simd_u32x4__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_insert_x32_instruction_set>()
#else
#define _simd_u32x4_insert_x32(X,I,Y) _simd_u32x4_insert_x32_safe(X,I,Y)
#define _simd_u32x4__insert_x32_enable() true
#endif _simd_u32x4_insert_x32_

#define _simd_u32x4_extract_x64_safe(X,I) _simd_u32x4_insert_x4_safe(_simd_u32x4_fill_undefined_safe(),0,X)
#ifdef _simd_u32x4_extract_x64_
#define _simd_u32x4_extract_x64(X,I) _simd_u32x4_extract_x64_(X,I)
#define _simd_u32x4__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_extract_x64_instruction_set>()
#else
#define _simd_u32x4_extract_x64(X,I) _simd_u32x4_extract_x64_safe(X,I)
#define _simd_u32x4__extract_x64_enable() true
#endif _simd_u32x4_extract_x64_

#define _simd_u32x4_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u32x1) * 64)
#ifdef _simd_u32x4_insert_x64_
#define _simd_u32x4_insert_x64(X,I,Y) _simd_u32x4_insert_x64_(X,I,Y)
#define _simd_u32x4__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_insert_x64_instruction_set>()
#else
#define _simd_u32x4_insert_x64(X,I,Y) _simd_u32x4_insert_x64_safe(X,I,Y)
#define _simd_u32x4__insert_x64_enable() true
#endif _simd_u32x4_insert_x64_

#define _simd_u32x4_extract_safe(X,I) _simd_u32x4_extract_x1_safe(X,I)
#define _simd_u32x4_extract(X,I) _simd_u32x4_extract_x1(X,I)
#define _simd_u32x4_extract_enable() _simd_u32x4_extract_x1_enable()

#define _simd_u32x4_insert_safe(X,I,Y) _simd_u32x4_insert_x1_safe(X,I,Y)
#define _simd_u32x4_insert(X,I,Y) _simd_u32x4_insert_x1(X,I,Y)
#define _simd_u32x4_insert_enable() _simd_u32x4_insert_x1_enable()

//#ifndef _simd_u32x4_splitlo
//	#define _simd_u32x4_splitlo(X) _simd_u32x2_extract_x2(X,0)
//	#define _simd_u32x4_splitlo_enable() _simd_u32x2_extract_x2_enable()
//#endif

//#ifndef _simd_u32x4_splithi
//	#define _simd_u32x4_splithi(X) _simd_u32x2_extract_x2(X,1)
//	#define _simd_u32x4_splithi_enable() _simd_u32x2_extract_x2_enable()
//#endif

//#ifndef _simd_u32x4_combine
//	#define _simd_u32x4_combine(X,Y) _simd_u32x4_insert_x2(_simd_u32x4_insert_x2(_simd_u32x4_fill_undefined(), 0, X), 1, Y)
//	#define _simd_u32x4_combine_enable() (_simd_u32x4_insert_x2_enable() && _simd_u32x4_fill_undefined_enable())
//#endif

#define _simd_u32x8_extract_x1_safe(X,I) (reinterpret_cast<const _simd_u32x8*>(&X)[I])
#ifdef _simd_u32x8_extract_x1_
#define _simd_u32x8_extract_x1(X,I) _simd_u32x8_extract_x1_(X,I)
#define _simd_u32x8__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_extract_x1_instruction_set>()
#else
#define _simd_u32x8_extract_x1(X,I) _simd_u32x8_extract_x1_safe(X,I)
#define _simd_u32x8__extract_x1_enable() true
#endif _simd_u32x8_extract_x1_

#define _simd_u32x8_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_u32x8*>(&X)[I] = Y)
#ifdef _simd_u32x8_insert_x1_
#define _simd_u32x8_insert_x1(X,I,Y) _simd_u32x8_insert_x1_(X,I,Y)
#define _simd_u32x8__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_insert_x1_instruction_set>()
#else
#define _simd_u32x8_insert_x1(X,I,Y) _simd_u32x8_insert_x1_safe(X,I,Y)
#define _simd_u32x8__insert_x1_enable() true
#endif _simd_u32x8_insert_x1_

#define _simd_u32x8_extract_x2_safe(X,I) (reinterpret_cast<const _simd_u32x8*>(&X)[I])
#ifdef _simd_u32x8_extract_x2_
#define _simd_u32x8_extract_x2(X,I) _simd_u32x8_extract_x2_(X,I)
#define _simd_u32x8__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_extract_x2_instruction_set>()
#else
#define _simd_u32x8_extract_x2(X,I) _simd_u32x8_extract_x2_safe(X,I)
#define _simd_u32x8__extract_x2_enable() true
#endif _simd_u32x8_extract_x2_

#define _simd_u32x8_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_u32x8*>(&X)[I] = Y)
#ifdef _simd_u32x8_insert_x2_
#define _simd_u32x8_insert_x2(X,I,Y) _simd_u32x8_insert_x2_(X,I,Y)
#define _simd_u32x8__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_insert_x2_instruction_set>()
#else
#define _simd_u32x8_insert_x2(X,I,Y) _simd_u32x8_insert_x2_safe(X,I,Y)
#define _simd_u32x8__insert_x2_enable() true
#endif _simd_u32x8_insert_x2_

#define _simd_u32x8_extract_x4_safe(X,I) (reinterpret_cast<const _simd_u32x8*>(&X)[I])
#ifdef _simd_u32x8_extract_x4_
#define _simd_u32x8_extract_x4(X,I) _simd_u32x8_extract_x4_(X,I)
#define _simd_u32x8__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_extract_x4_instruction_set>()
#else
#define _simd_u32x8_extract_x4(X,I) _simd_u32x8_extract_x4_safe(X,I)
#define _simd_u32x8__extract_x4_enable() true
#endif _simd_u32x8_extract_x4_

#define _simd_u32x8_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_u32x8*>(&X)[I] = Y)
#ifdef _simd_u32x8_insert_x4_
#define _simd_u32x8_insert_x4(X,I,Y) _simd_u32x8_insert_x4_(X,I,Y)
#define _simd_u32x8__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_insert_x4_instruction_set>()
#else
#define _simd_u32x8_insert_x4(X,I,Y) _simd_u32x8_insert_x4_safe(X,I,Y)
#define _simd_u32x8__insert_x4_enable() true
#endif _simd_u32x8_insert_x4_

#define _simd_u32x8_extract_x16_safe(X,I) _simd_u32x8_insert_x8_safe(_simd_u32x8_fill_undefined_safe(),0,X)
#ifdef _simd_u32x8_extract_x16_
#define _simd_u32x8_extract_x16(X,I) _simd_u32x8_extract_x16_(X,I)
#define _simd_u32x8__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_extract_x16_instruction_set>()
#else
#define _simd_u32x8_extract_x16(X,I) _simd_u32x8_extract_x16_safe(X,I)
#define _simd_u32x8__extract_x16_enable() true
#endif _simd_u32x8_extract_x16_

#define _simd_u32x8_insert_x16_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u32x1) * 16)
#ifdef _simd_u32x8_insert_x16_
#define _simd_u32x8_insert_x16(X,I,Y) _simd_u32x8_insert_x16_(X,I,Y)
#define _simd_u32x8__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_insert_x16_instruction_set>()
#else
#define _simd_u32x8_insert_x16(X,I,Y) _simd_u32x8_insert_x16_safe(X,I,Y)
#define _simd_u32x8__insert_x16_enable() true
#endif _simd_u32x8_insert_x16_

#define _simd_u32x8_extract_x32_safe(X,I) _simd_u32x8_insert_x8_safe(_simd_u32x8_fill_undefined_safe(),0,X)
#ifdef _simd_u32x8_extract_x32_
#define _simd_u32x8_extract_x32(X,I) _simd_u32x8_extract_x32_(X,I)
#define _simd_u32x8__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_extract_x32_instruction_set>()
#else
#define _simd_u32x8_extract_x32(X,I) _simd_u32x8_extract_x32_safe(X,I)
#define _simd_u32x8__extract_x32_enable() true
#endif _simd_u32x8_extract_x32_

#define _simd_u32x8_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u32x1) * 32)
#ifdef _simd_u32x8_insert_x32_
#define _simd_u32x8_insert_x32(X,I,Y) _simd_u32x8_insert_x32_(X,I,Y)
#define _simd_u32x8__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_insert_x32_instruction_set>()
#else
#define _simd_u32x8_insert_x32(X,I,Y) _simd_u32x8_insert_x32_safe(X,I,Y)
#define _simd_u32x8__insert_x32_enable() true
#endif _simd_u32x8_insert_x32_

#define _simd_u32x8_extract_x64_safe(X,I) _simd_u32x8_insert_x8_safe(_simd_u32x8_fill_undefined_safe(),0,X)
#ifdef _simd_u32x8_extract_x64_
#define _simd_u32x8_extract_x64(X,I) _simd_u32x8_extract_x64_(X,I)
#define _simd_u32x8__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_extract_x64_instruction_set>()
#else
#define _simd_u32x8_extract_x64(X,I) _simd_u32x8_extract_x64_safe(X,I)
#define _simd_u32x8__extract_x64_enable() true
#endif _simd_u32x8_extract_x64_

#define _simd_u32x8_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u32x1) * 64)
#ifdef _simd_u32x8_insert_x64_
#define _simd_u32x8_insert_x64(X,I,Y) _simd_u32x8_insert_x64_(X,I,Y)
#define _simd_u32x8__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_insert_x64_instruction_set>()
#else
#define _simd_u32x8_insert_x64(X,I,Y) _simd_u32x8_insert_x64_safe(X,I,Y)
#define _simd_u32x8__insert_x64_enable() true
#endif _simd_u32x8_insert_x64_

#define _simd_u32x8_extract_safe(X,I) _simd_u32x8_extract_x1_safe(X,I)
#define _simd_u32x8_extract(X,I) _simd_u32x8_extract_x1(X,I)
#define _simd_u32x8_extract_enable() _simd_u32x8_extract_x1_enable()

#define _simd_u32x8_insert_safe(X,I,Y) _simd_u32x8_insert_x1_safe(X,I,Y)
#define _simd_u32x8_insert(X,I,Y) _simd_u32x8_insert_x1(X,I,Y)
#define _simd_u32x8_insert_enable() _simd_u32x8_insert_x1_enable()

//#ifndef _simd_u32x8_splitlo
//	#define _simd_u32x8_splitlo(X) _simd_u32x4_extract_x4(X,0)
//	#define _simd_u32x8_splitlo_enable() _simd_u32x4_extract_x4_enable()
//#endif

//#ifndef _simd_u32x8_splithi
//	#define _simd_u32x8_splithi(X) _simd_u32x4_extract_x4(X,1)
//	#define _simd_u32x8_splithi_enable() _simd_u32x4_extract_x4_enable()
//#endif

//#ifndef _simd_u32x8_combine
//	#define _simd_u32x8_combine(X,Y) _simd_u32x8_insert_x4(_simd_u32x8_insert_x4(_simd_u32x8_fill_undefined(), 0, X), 1, Y)
//	#define _simd_u32x8_combine_enable() (_simd_u32x8_insert_x4_enable() && _simd_u32x8_fill_undefined_enable())
//#endif

#define _simd_u32x16_extract_x1_safe(X,I) (reinterpret_cast<const _simd_u32x16*>(&X)[I])
#ifdef _simd_u32x16_extract_x1_
#define _simd_u32x16_extract_x1(X,I) _simd_u32x16_extract_x1_(X,I)
#define _simd_u32x16__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_extract_x1_instruction_set>()
#else
#define _simd_u32x16_extract_x1(X,I) _simd_u32x16_extract_x1_safe(X,I)
#define _simd_u32x16__extract_x1_enable() true
#endif _simd_u32x16_extract_x1_

#define _simd_u32x16_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_u32x16*>(&X)[I] = Y)
#ifdef _simd_u32x16_insert_x1_
#define _simd_u32x16_insert_x1(X,I,Y) _simd_u32x16_insert_x1_(X,I,Y)
#define _simd_u32x16__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_insert_x1_instruction_set>()
#else
#define _simd_u32x16_insert_x1(X,I,Y) _simd_u32x16_insert_x1_safe(X,I,Y)
#define _simd_u32x16__insert_x1_enable() true
#endif _simd_u32x16_insert_x1_

#define _simd_u32x16_extract_x2_safe(X,I) (reinterpret_cast<const _simd_u32x16*>(&X)[I])
#ifdef _simd_u32x16_extract_x2_
#define _simd_u32x16_extract_x2(X,I) _simd_u32x16_extract_x2_(X,I)
#define _simd_u32x16__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_extract_x2_instruction_set>()
#else
#define _simd_u32x16_extract_x2(X,I) _simd_u32x16_extract_x2_safe(X,I)
#define _simd_u32x16__extract_x2_enable() true
#endif _simd_u32x16_extract_x2_

#define _simd_u32x16_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_u32x16*>(&X)[I] = Y)
#ifdef _simd_u32x16_insert_x2_
#define _simd_u32x16_insert_x2(X,I,Y) _simd_u32x16_insert_x2_(X,I,Y)
#define _simd_u32x16__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_insert_x2_instruction_set>()
#else
#define _simd_u32x16_insert_x2(X,I,Y) _simd_u32x16_insert_x2_safe(X,I,Y)
#define _simd_u32x16__insert_x2_enable() true
#endif _simd_u32x16_insert_x2_

#define _simd_u32x16_extract_x4_safe(X,I) (reinterpret_cast<const _simd_u32x16*>(&X)[I])
#ifdef _simd_u32x16_extract_x4_
#define _simd_u32x16_extract_x4(X,I) _simd_u32x16_extract_x4_(X,I)
#define _simd_u32x16__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_extract_x4_instruction_set>()
#else
#define _simd_u32x16_extract_x4(X,I) _simd_u32x16_extract_x4_safe(X,I)
#define _simd_u32x16__extract_x4_enable() true
#endif _simd_u32x16_extract_x4_

#define _simd_u32x16_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_u32x16*>(&X)[I] = Y)
#ifdef _simd_u32x16_insert_x4_
#define _simd_u32x16_insert_x4(X,I,Y) _simd_u32x16_insert_x4_(X,I,Y)
#define _simd_u32x16__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_insert_x4_instruction_set>()
#else
#define _simd_u32x16_insert_x4(X,I,Y) _simd_u32x16_insert_x4_safe(X,I,Y)
#define _simd_u32x16__insert_x4_enable() true
#endif _simd_u32x16_insert_x4_

#define _simd_u32x16_extract_x8_safe(X,I) (reinterpret_cast<const _simd_u32x16*>(&X)[I])
#ifdef _simd_u32x16_extract_x8_
#define _simd_u32x16_extract_x8(X,I) _simd_u32x16_extract_x8_(X,I)
#define _simd_u32x16__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_extract_x8_instruction_set>()
#else
#define _simd_u32x16_extract_x8(X,I) _simd_u32x16_extract_x8_safe(X,I)
#define _simd_u32x16__extract_x8_enable() true
#endif _simd_u32x16_extract_x8_

#define _simd_u32x16_insert_x8_safe(X,I,Y) (reinterpret_cast<_simd_u32x16*>(&X)[I] = Y)
#ifdef _simd_u32x16_insert_x8_
#define _simd_u32x16_insert_x8(X,I,Y) _simd_u32x16_insert_x8_(X,I,Y)
#define _simd_u32x16__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_insert_x8_instruction_set>()
#else
#define _simd_u32x16_insert_x8(X,I,Y) _simd_u32x16_insert_x8_safe(X,I,Y)
#define _simd_u32x16__insert_x8_enable() true
#endif _simd_u32x16_insert_x8_

#define _simd_u32x16_extract_x32_safe(X,I) _simd_u32x16_insert_x16_safe(_simd_u32x16_fill_undefined_safe(),0,X)
#ifdef _simd_u32x16_extract_x32_
#define _simd_u32x16_extract_x32(X,I) _simd_u32x16_extract_x32_(X,I)
#define _simd_u32x16__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_extract_x32_instruction_set>()
#else
#define _simd_u32x16_extract_x32(X,I) _simd_u32x16_extract_x32_safe(X,I)
#define _simd_u32x16__extract_x32_enable() true
#endif _simd_u32x16_extract_x32_

#define _simd_u32x16_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u32x1) * 32)
#ifdef _simd_u32x16_insert_x32_
#define _simd_u32x16_insert_x32(X,I,Y) _simd_u32x16_insert_x32_(X,I,Y)
#define _simd_u32x16__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_insert_x32_instruction_set>()
#else
#define _simd_u32x16_insert_x32(X,I,Y) _simd_u32x16_insert_x32_safe(X,I,Y)
#define _simd_u32x16__insert_x32_enable() true
#endif _simd_u32x16_insert_x32_

#define _simd_u32x16_extract_x64_safe(X,I) _simd_u32x16_insert_x16_safe(_simd_u32x16_fill_undefined_safe(),0,X)
#ifdef _simd_u32x16_extract_x64_
#define _simd_u32x16_extract_x64(X,I) _simd_u32x16_extract_x64_(X,I)
#define _simd_u32x16__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_extract_x64_instruction_set>()
#else
#define _simd_u32x16_extract_x64(X,I) _simd_u32x16_extract_x64_safe(X,I)
#define _simd_u32x16__extract_x64_enable() true
#endif _simd_u32x16_extract_x64_

#define _simd_u32x16_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u32x1) * 64)
#ifdef _simd_u32x16_insert_x64_
#define _simd_u32x16_insert_x64(X,I,Y) _simd_u32x16_insert_x64_(X,I,Y)
#define _simd_u32x16__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_insert_x64_instruction_set>()
#else
#define _simd_u32x16_insert_x64(X,I,Y) _simd_u32x16_insert_x64_safe(X,I,Y)
#define _simd_u32x16__insert_x64_enable() true
#endif _simd_u32x16_insert_x64_

#define _simd_u32x16_extract_safe(X,I) _simd_u32x16_extract_x1_safe(X,I)
#define _simd_u32x16_extract(X,I) _simd_u32x16_extract_x1(X,I)
#define _simd_u32x16_extract_enable() _simd_u32x16_extract_x1_enable()

#define _simd_u32x16_insert_safe(X,I,Y) _simd_u32x16_insert_x1_safe(X,I,Y)
#define _simd_u32x16_insert(X,I,Y) _simd_u32x16_insert_x1(X,I,Y)
#define _simd_u32x16_insert_enable() _simd_u32x16_insert_x1_enable()

//#ifndef _simd_u32x16_splitlo
//	#define _simd_u32x16_splitlo(X) _simd_u32x8_extract_x8(X,0)
//	#define _simd_u32x16_splitlo_enable() _simd_u32x8_extract_x8_enable()
//#endif

//#ifndef _simd_u32x16_splithi
//	#define _simd_u32x16_splithi(X) _simd_u32x8_extract_x8(X,1)
//	#define _simd_u32x16_splithi_enable() _simd_u32x8_extract_x8_enable()
//#endif

//#ifndef _simd_u32x16_combine
//	#define _simd_u32x16_combine(X,Y) _simd_u32x16_insert_x8(_simd_u32x16_insert_x8(_simd_u32x16_fill_undefined(), 0, X), 1, Y)
//	#define _simd_u32x16_combine_enable() (_simd_u32x16_insert_x8_enable() && _simd_u32x16_fill_undefined_enable())
//#endif

#define _simd_u32x32_extract_x1_safe(X,I) (reinterpret_cast<const _simd_u32x32*>(&X)[I])
#ifdef _simd_u32x32_extract_x1_
#define _simd_u32x32_extract_x1(X,I) _simd_u32x32_extract_x1_(X,I)
#define _simd_u32x32__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_extract_x1_instruction_set>()
#else
#define _simd_u32x32_extract_x1(X,I) _simd_u32x32_extract_x1_safe(X,I)
#define _simd_u32x32__extract_x1_enable() true
#endif _simd_u32x32_extract_x1_

#define _simd_u32x32_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_u32x32*>(&X)[I] = Y)
#ifdef _simd_u32x32_insert_x1_
#define _simd_u32x32_insert_x1(X,I,Y) _simd_u32x32_insert_x1_(X,I,Y)
#define _simd_u32x32__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_insert_x1_instruction_set>()
#else
#define _simd_u32x32_insert_x1(X,I,Y) _simd_u32x32_insert_x1_safe(X,I,Y)
#define _simd_u32x32__insert_x1_enable() true
#endif _simd_u32x32_insert_x1_

#define _simd_u32x32_extract_x2_safe(X,I) (reinterpret_cast<const _simd_u32x32*>(&X)[I])
#ifdef _simd_u32x32_extract_x2_
#define _simd_u32x32_extract_x2(X,I) _simd_u32x32_extract_x2_(X,I)
#define _simd_u32x32__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_extract_x2_instruction_set>()
#else
#define _simd_u32x32_extract_x2(X,I) _simd_u32x32_extract_x2_safe(X,I)
#define _simd_u32x32__extract_x2_enable() true
#endif _simd_u32x32_extract_x2_

#define _simd_u32x32_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_u32x32*>(&X)[I] = Y)
#ifdef _simd_u32x32_insert_x2_
#define _simd_u32x32_insert_x2(X,I,Y) _simd_u32x32_insert_x2_(X,I,Y)
#define _simd_u32x32__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_insert_x2_instruction_set>()
#else
#define _simd_u32x32_insert_x2(X,I,Y) _simd_u32x32_insert_x2_safe(X,I,Y)
#define _simd_u32x32__insert_x2_enable() true
#endif _simd_u32x32_insert_x2_

#define _simd_u32x32_extract_x4_safe(X,I) (reinterpret_cast<const _simd_u32x32*>(&X)[I])
#ifdef _simd_u32x32_extract_x4_
#define _simd_u32x32_extract_x4(X,I) _simd_u32x32_extract_x4_(X,I)
#define _simd_u32x32__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_extract_x4_instruction_set>()
#else
#define _simd_u32x32_extract_x4(X,I) _simd_u32x32_extract_x4_safe(X,I)
#define _simd_u32x32__extract_x4_enable() true
#endif _simd_u32x32_extract_x4_

#define _simd_u32x32_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_u32x32*>(&X)[I] = Y)
#ifdef _simd_u32x32_insert_x4_
#define _simd_u32x32_insert_x4(X,I,Y) _simd_u32x32_insert_x4_(X,I,Y)
#define _simd_u32x32__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_insert_x4_instruction_set>()
#else
#define _simd_u32x32_insert_x4(X,I,Y) _simd_u32x32_insert_x4_safe(X,I,Y)
#define _simd_u32x32__insert_x4_enable() true
#endif _simd_u32x32_insert_x4_

#define _simd_u32x32_extract_x8_safe(X,I) (reinterpret_cast<const _simd_u32x32*>(&X)[I])
#ifdef _simd_u32x32_extract_x8_
#define _simd_u32x32_extract_x8(X,I) _simd_u32x32_extract_x8_(X,I)
#define _simd_u32x32__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_extract_x8_instruction_set>()
#else
#define _simd_u32x32_extract_x8(X,I) _simd_u32x32_extract_x8_safe(X,I)
#define _simd_u32x32__extract_x8_enable() true
#endif _simd_u32x32_extract_x8_

#define _simd_u32x32_insert_x8_safe(X,I,Y) (reinterpret_cast<_simd_u32x32*>(&X)[I] = Y)
#ifdef _simd_u32x32_insert_x8_
#define _simd_u32x32_insert_x8(X,I,Y) _simd_u32x32_insert_x8_(X,I,Y)
#define _simd_u32x32__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_insert_x8_instruction_set>()
#else
#define _simd_u32x32_insert_x8(X,I,Y) _simd_u32x32_insert_x8_safe(X,I,Y)
#define _simd_u32x32__insert_x8_enable() true
#endif _simd_u32x32_insert_x8_

#define _simd_u32x32_extract_x16_safe(X,I) (reinterpret_cast<const _simd_u32x32*>(&X)[I])
#ifdef _simd_u32x32_extract_x16_
#define _simd_u32x32_extract_x16(X,I) _simd_u32x32_extract_x16_(X,I)
#define _simd_u32x32__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_extract_x16_instruction_set>()
#else
#define _simd_u32x32_extract_x16(X,I) _simd_u32x32_extract_x16_safe(X,I)
#define _simd_u32x32__extract_x16_enable() true
#endif _simd_u32x32_extract_x16_

#define _simd_u32x32_insert_x16_safe(X,I,Y) (reinterpret_cast<_simd_u32x32*>(&X)[I] = Y)
#ifdef _simd_u32x32_insert_x16_
#define _simd_u32x32_insert_x16(X,I,Y) _simd_u32x32_insert_x16_(X,I,Y)
#define _simd_u32x32__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_insert_x16_instruction_set>()
#else
#define _simd_u32x32_insert_x16(X,I,Y) _simd_u32x32_insert_x16_safe(X,I,Y)
#define _simd_u32x32__insert_x16_enable() true
#endif _simd_u32x32_insert_x16_

#define _simd_u32x32_extract_x64_safe(X,I) _simd_u32x32_insert_x32_safe(_simd_u32x32_fill_undefined_safe(),0,X)
#ifdef _simd_u32x32_extract_x64_
#define _simd_u32x32_extract_x64(X,I) _simd_u32x32_extract_x64_(X,I)
#define _simd_u32x32__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_extract_x64_instruction_set>()
#else
#define _simd_u32x32_extract_x64(X,I) _simd_u32x32_extract_x64_safe(X,I)
#define _simd_u32x32__extract_x64_enable() true
#endif _simd_u32x32_extract_x64_

#define _simd_u32x32_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u32x1) * 64)
#ifdef _simd_u32x32_insert_x64_
#define _simd_u32x32_insert_x64(X,I,Y) _simd_u32x32_insert_x64_(X,I,Y)
#define _simd_u32x32__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_insert_x64_instruction_set>()
#else
#define _simd_u32x32_insert_x64(X,I,Y) _simd_u32x32_insert_x64_safe(X,I,Y)
#define _simd_u32x32__insert_x64_enable() true
#endif _simd_u32x32_insert_x64_

#define _simd_u32x32_extract_safe(X,I) _simd_u32x32_extract_x1_safe(X,I)
#define _simd_u32x32_extract(X,I) _simd_u32x32_extract_x1(X,I)
#define _simd_u32x32_extract_enable() _simd_u32x32_extract_x1_enable()

#define _simd_u32x32_insert_safe(X,I,Y) _simd_u32x32_insert_x1_safe(X,I,Y)
#define _simd_u32x32_insert(X,I,Y) _simd_u32x32_insert_x1(X,I,Y)
#define _simd_u32x32_insert_enable() _simd_u32x32_insert_x1_enable()

//#ifndef _simd_u32x32_splitlo
//	#define _simd_u32x32_splitlo(X) _simd_u32x16_extract_x16(X,0)
//	#define _simd_u32x32_splitlo_enable() _simd_u32x16_extract_x16_enable()
//#endif

//#ifndef _simd_u32x32_splithi
//	#define _simd_u32x32_splithi(X) _simd_u32x16_extract_x16(X,1)
//	#define _simd_u32x32_splithi_enable() _simd_u32x16_extract_x16_enable()
//#endif

//#ifndef _simd_u32x32_combine
//	#define _simd_u32x32_combine(X,Y) _simd_u32x32_insert_x16(_simd_u32x32_insert_x16(_simd_u32x32_fill_undefined(), 0, X), 1, Y)
//	#define _simd_u32x32_combine_enable() (_simd_u32x32_insert_x16_enable() && _simd_u32x32_fill_undefined_enable())
//#endif

#define _simd_u32x64_extract_x1_safe(X,I) (reinterpret_cast<const _simd_u32x64*>(&X)[I])
#ifdef _simd_u32x64_extract_x1_
#define _simd_u32x64_extract_x1(X,I) _simd_u32x64_extract_x1_(X,I)
#define _simd_u32x64__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_extract_x1_instruction_set>()
#else
#define _simd_u32x64_extract_x1(X,I) _simd_u32x64_extract_x1_safe(X,I)
#define _simd_u32x64__extract_x1_enable() true
#endif _simd_u32x64_extract_x1_

#define _simd_u32x64_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_u32x64*>(&X)[I] = Y)
#ifdef _simd_u32x64_insert_x1_
#define _simd_u32x64_insert_x1(X,I,Y) _simd_u32x64_insert_x1_(X,I,Y)
#define _simd_u32x64__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_insert_x1_instruction_set>()
#else
#define _simd_u32x64_insert_x1(X,I,Y) _simd_u32x64_insert_x1_safe(X,I,Y)
#define _simd_u32x64__insert_x1_enable() true
#endif _simd_u32x64_insert_x1_

#define _simd_u32x64_extract_x2_safe(X,I) (reinterpret_cast<const _simd_u32x64*>(&X)[I])
#ifdef _simd_u32x64_extract_x2_
#define _simd_u32x64_extract_x2(X,I) _simd_u32x64_extract_x2_(X,I)
#define _simd_u32x64__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_extract_x2_instruction_set>()
#else
#define _simd_u32x64_extract_x2(X,I) _simd_u32x64_extract_x2_safe(X,I)
#define _simd_u32x64__extract_x2_enable() true
#endif _simd_u32x64_extract_x2_

#define _simd_u32x64_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_u32x64*>(&X)[I] = Y)
#ifdef _simd_u32x64_insert_x2_
#define _simd_u32x64_insert_x2(X,I,Y) _simd_u32x64_insert_x2_(X,I,Y)
#define _simd_u32x64__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_insert_x2_instruction_set>()
#else
#define _simd_u32x64_insert_x2(X,I,Y) _simd_u32x64_insert_x2_safe(X,I,Y)
#define _simd_u32x64__insert_x2_enable() true
#endif _simd_u32x64_insert_x2_

#define _simd_u32x64_extract_x4_safe(X,I) (reinterpret_cast<const _simd_u32x64*>(&X)[I])
#ifdef _simd_u32x64_extract_x4_
#define _simd_u32x64_extract_x4(X,I) _simd_u32x64_extract_x4_(X,I)
#define _simd_u32x64__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_extract_x4_instruction_set>()
#else
#define _simd_u32x64_extract_x4(X,I) _simd_u32x64_extract_x4_safe(X,I)
#define _simd_u32x64__extract_x4_enable() true
#endif _simd_u32x64_extract_x4_

#define _simd_u32x64_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_u32x64*>(&X)[I] = Y)
#ifdef _simd_u32x64_insert_x4_
#define _simd_u32x64_insert_x4(X,I,Y) _simd_u32x64_insert_x4_(X,I,Y)
#define _simd_u32x64__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_insert_x4_instruction_set>()
#else
#define _simd_u32x64_insert_x4(X,I,Y) _simd_u32x64_insert_x4_safe(X,I,Y)
#define _simd_u32x64__insert_x4_enable() true
#endif _simd_u32x64_insert_x4_

#define _simd_u32x64_extract_x8_safe(X,I) (reinterpret_cast<const _simd_u32x64*>(&X)[I])
#ifdef _simd_u32x64_extract_x8_
#define _simd_u32x64_extract_x8(X,I) _simd_u32x64_extract_x8_(X,I)
#define _simd_u32x64__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_extract_x8_instruction_set>()
#else
#define _simd_u32x64_extract_x8(X,I) _simd_u32x64_extract_x8_safe(X,I)
#define _simd_u32x64__extract_x8_enable() true
#endif _simd_u32x64_extract_x8_

#define _simd_u32x64_insert_x8_safe(X,I,Y) (reinterpret_cast<_simd_u32x64*>(&X)[I] = Y)
#ifdef _simd_u32x64_insert_x8_
#define _simd_u32x64_insert_x8(X,I,Y) _simd_u32x64_insert_x8_(X,I,Y)
#define _simd_u32x64__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_insert_x8_instruction_set>()
#else
#define _simd_u32x64_insert_x8(X,I,Y) _simd_u32x64_insert_x8_safe(X,I,Y)
#define _simd_u32x64__insert_x8_enable() true
#endif _simd_u32x64_insert_x8_

#define _simd_u32x64_extract_x16_safe(X,I) (reinterpret_cast<const _simd_u32x64*>(&X)[I])
#ifdef _simd_u32x64_extract_x16_
#define _simd_u32x64_extract_x16(X,I) _simd_u32x64_extract_x16_(X,I)
#define _simd_u32x64__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_extract_x16_instruction_set>()
#else
#define _simd_u32x64_extract_x16(X,I) _simd_u32x64_extract_x16_safe(X,I)
#define _simd_u32x64__extract_x16_enable() true
#endif _simd_u32x64_extract_x16_

#define _simd_u32x64_insert_x16_safe(X,I,Y) (reinterpret_cast<_simd_u32x64*>(&X)[I] = Y)
#ifdef _simd_u32x64_insert_x16_
#define _simd_u32x64_insert_x16(X,I,Y) _simd_u32x64_insert_x16_(X,I,Y)
#define _simd_u32x64__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_insert_x16_instruction_set>()
#else
#define _simd_u32x64_insert_x16(X,I,Y) _simd_u32x64_insert_x16_safe(X,I,Y)
#define _simd_u32x64__insert_x16_enable() true
#endif _simd_u32x64_insert_x16_

#define _simd_u32x64_extract_x32_safe(X,I) (reinterpret_cast<const _simd_u32x64*>(&X)[I])
#ifdef _simd_u32x64_extract_x32_
#define _simd_u32x64_extract_x32(X,I) _simd_u32x64_extract_x32_(X,I)
#define _simd_u32x64__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_extract_x32_instruction_set>()
#else
#define _simd_u32x64_extract_x32(X,I) _simd_u32x64_extract_x32_safe(X,I)
#define _simd_u32x64__extract_x32_enable() true
#endif _simd_u32x64_extract_x32_

#define _simd_u32x64_insert_x32_safe(X,I,Y) (reinterpret_cast<_simd_u32x64*>(&X)[I] = Y)
#ifdef _simd_u32x64_insert_x32_
#define _simd_u32x64_insert_x32(X,I,Y) _simd_u32x64_insert_x32_(X,I,Y)
#define _simd_u32x64__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_insert_x32_instruction_set>()
#else
#define _simd_u32x64_insert_x32(X,I,Y) _simd_u32x64_insert_x32_safe(X,I,Y)
#define _simd_u32x64__insert_x32_enable() true
#endif _simd_u32x64_insert_x32_

#define _simd_u32x64_extract_safe(X,I) _simd_u32x64_extract_x1_safe(X,I)
#define _simd_u32x64_extract(X,I) _simd_u32x64_extract_x1(X,I)
#define _simd_u32x64_extract_enable() _simd_u32x64_extract_x1_enable()

#define _simd_u32x64_insert_safe(X,I,Y) _simd_u32x64_insert_x1_safe(X,I,Y)
#define _simd_u32x64_insert(X,I,Y) _simd_u32x64_insert_x1(X,I,Y)
#define _simd_u32x64_insert_enable() _simd_u32x64_insert_x1_enable()

//#ifndef _simd_u32x64_splitlo
//	#define _simd_u32x64_splitlo(X) _simd_u32x32_extract_x32(X,0)
//	#define _simd_u32x64_splitlo_enable() _simd_u32x32_extract_x32_enable()
//#endif

//#ifndef _simd_u32x64_splithi
//	#define _simd_u32x64_splithi(X) _simd_u32x32_extract_x32(X,1)
//	#define _simd_u32x64_splithi_enable() _simd_u32x32_extract_x32_enable()
//#endif

//#ifndef _simd_u32x64_combine
//	#define _simd_u32x64_combine(X,Y) _simd_u32x64_insert_x32(_simd_u32x64_insert_x32(_simd_u32x64_fill_undefined(), 0, X), 1, Y)
//	#define _simd_u32x64_combine_enable() (_simd_u32x64_insert_x32_enable() && _simd_u32x64_fill_undefined_enable())
//#endif

// -- s16 --

#define _simd_s16x2_extract_x1_safe(X,I) (reinterpret_cast<const _simd_s16x2*>(&X)[I])
#ifdef _simd_s16x2_extract_x1_
#define _simd_s16x2_extract_x1(X,I) _simd_s16x2_extract_x1_(X,I)
#define _simd_s16x2__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_extract_x1_instruction_set>()
#else
#define _simd_s16x2_extract_x1(X,I) _simd_s16x2_extract_x1_safe(X,I)
#define _simd_s16x2__extract_x1_enable() true
#endif _simd_s16x2_extract_x1_

#define _simd_s16x2_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_s16x2*>(&X)[I] = Y)
#ifdef _simd_s16x2_insert_x1_
#define _simd_s16x2_insert_x1(X,I,Y) _simd_s16x2_insert_x1_(X,I,Y)
#define _simd_s16x2__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_insert_x1_instruction_set>()
#else
#define _simd_s16x2_insert_x1(X,I,Y) _simd_s16x2_insert_x1_safe(X,I,Y)
#define _simd_s16x2__insert_x1_enable() true
#endif _simd_s16x2_insert_x1_

#define _simd_s16x2_extract_x4_safe(X,I) _simd_s16x2_insert_x2_safe(_simd_s16x2_fill_undefined_safe(),0,X)
#ifdef _simd_s16x2_extract_x4_
#define _simd_s16x2_extract_x4(X,I) _simd_s16x2_extract_x4_(X,I)
#define _simd_s16x2__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_extract_x4_instruction_set>()
#else
#define _simd_s16x2_extract_x4(X,I) _simd_s16x2_extract_x4_safe(X,I)
#define _simd_s16x2__extract_x4_enable() true
#endif _simd_s16x2_extract_x4_

#define _simd_s16x2_insert_x4_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s16x1) * 4)
#ifdef _simd_s16x2_insert_x4_
#define _simd_s16x2_insert_x4(X,I,Y) _simd_s16x2_insert_x4_(X,I,Y)
#define _simd_s16x2__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_insert_x4_instruction_set>()
#else
#define _simd_s16x2_insert_x4(X,I,Y) _simd_s16x2_insert_x4_safe(X,I,Y)
#define _simd_s16x2__insert_x4_enable() true
#endif _simd_s16x2_insert_x4_

#define _simd_s16x2_extract_x8_safe(X,I) _simd_s16x2_insert_x2_safe(_simd_s16x2_fill_undefined_safe(),0,X)
#ifdef _simd_s16x2_extract_x8_
#define _simd_s16x2_extract_x8(X,I) _simd_s16x2_extract_x8_(X,I)
#define _simd_s16x2__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_extract_x8_instruction_set>()
#else
#define _simd_s16x2_extract_x8(X,I) _simd_s16x2_extract_x8_safe(X,I)
#define _simd_s16x2__extract_x8_enable() true
#endif _simd_s16x2_extract_x8_

#define _simd_s16x2_insert_x8_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s16x1) * 8)
#ifdef _simd_s16x2_insert_x8_
#define _simd_s16x2_insert_x8(X,I,Y) _simd_s16x2_insert_x8_(X,I,Y)
#define _simd_s16x2__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_insert_x8_instruction_set>()
#else
#define _simd_s16x2_insert_x8(X,I,Y) _simd_s16x2_insert_x8_safe(X,I,Y)
#define _simd_s16x2__insert_x8_enable() true
#endif _simd_s16x2_insert_x8_

#define _simd_s16x2_extract_x16_safe(X,I) _simd_s16x2_insert_x2_safe(_simd_s16x2_fill_undefined_safe(),0,X)
#ifdef _simd_s16x2_extract_x16_
#define _simd_s16x2_extract_x16(X,I) _simd_s16x2_extract_x16_(X,I)
#define _simd_s16x2__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_extract_x16_instruction_set>()
#else
#define _simd_s16x2_extract_x16(X,I) _simd_s16x2_extract_x16_safe(X,I)
#define _simd_s16x2__extract_x16_enable() true
#endif _simd_s16x2_extract_x16_

#define _simd_s16x2_insert_x16_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s16x1) * 16)
#ifdef _simd_s16x2_insert_x16_
#define _simd_s16x2_insert_x16(X,I,Y) _simd_s16x2_insert_x16_(X,I,Y)
#define _simd_s16x2__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_insert_x16_instruction_set>()
#else
#define _simd_s16x2_insert_x16(X,I,Y) _simd_s16x2_insert_x16_safe(X,I,Y)
#define _simd_s16x2__insert_x16_enable() true
#endif _simd_s16x2_insert_x16_

#define _simd_s16x2_extract_x32_safe(X,I) _simd_s16x2_insert_x2_safe(_simd_s16x2_fill_undefined_safe(),0,X)
#ifdef _simd_s16x2_extract_x32_
#define _simd_s16x2_extract_x32(X,I) _simd_s16x2_extract_x32_(X,I)
#define _simd_s16x2__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_extract_x32_instruction_set>()
#else
#define _simd_s16x2_extract_x32(X,I) _simd_s16x2_extract_x32_safe(X,I)
#define _simd_s16x2__extract_x32_enable() true
#endif _simd_s16x2_extract_x32_

#define _simd_s16x2_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s16x1) * 32)
#ifdef _simd_s16x2_insert_x32_
#define _simd_s16x2_insert_x32(X,I,Y) _simd_s16x2_insert_x32_(X,I,Y)
#define _simd_s16x2__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_insert_x32_instruction_set>()
#else
#define _simd_s16x2_insert_x32(X,I,Y) _simd_s16x2_insert_x32_safe(X,I,Y)
#define _simd_s16x2__insert_x32_enable() true
#endif _simd_s16x2_insert_x32_

#define _simd_s16x2_extract_x64_safe(X,I) _simd_s16x2_insert_x2_safe(_simd_s16x2_fill_undefined_safe(),0,X)
#ifdef _simd_s16x2_extract_x64_
#define _simd_s16x2_extract_x64(X,I) _simd_s16x2_extract_x64_(X,I)
#define _simd_s16x2__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_extract_x64_instruction_set>()
#else
#define _simd_s16x2_extract_x64(X,I) _simd_s16x2_extract_x64_safe(X,I)
#define _simd_s16x2__extract_x64_enable() true
#endif _simd_s16x2_extract_x64_

#define _simd_s16x2_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s16x1) * 64)
#ifdef _simd_s16x2_insert_x64_
#define _simd_s16x2_insert_x64(X,I,Y) _simd_s16x2_insert_x64_(X,I,Y)
#define _simd_s16x2__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_insert_x64_instruction_set>()
#else
#define _simd_s16x2_insert_x64(X,I,Y) _simd_s16x2_insert_x64_safe(X,I,Y)
#define _simd_s16x2__insert_x64_enable() true
#endif _simd_s16x2_insert_x64_

#define _simd_s16x2_extract_safe(X,I) _simd_s16x2_extract_x1_safe(X,I)
#define _simd_s16x2_extract(X,I) _simd_s16x2_extract_x1(X,I)
#define _simd_s16x2_extract_enable() _simd_s16x2_extract_x1_enable()

#define _simd_s16x2_insert_safe(X,I,Y) _simd_s16x2_insert_x1_safe(X,I,Y)
#define _simd_s16x2_insert(X,I,Y) _simd_s16x2_insert_x1(X,I,Y)
#define _simd_s16x2_insert_enable() _simd_s16x2_insert_x1_enable()

//#ifndef _simd_s16x2_splitlo
//	#define _simd_s16x2_splitlo(X) _simd_s16x1_extract_x1(X,0)
//	#define _simd_s16x2_splitlo_enable() _simd_s16x1_extract_x1_enable()
//#endif

//#ifndef _simd_s16x2_splithi
//	#define _simd_s16x2_splithi(X) _simd_s16x1_extract_x1(X,1)
//	#define _simd_s16x2_splithi_enable() _simd_s16x1_extract_x1_enable()
//#endif

//#ifndef _simd_s16x2_combine
//	#define _simd_s16x2_combine(X,Y) _simd_s16x2_insert_x1(_simd_s16x2_insert_x1(_simd_s16x2_fill_undefined(), 0, X), 1, Y)
//	#define _simd_s16x2_combine_enable() (_simd_s16x2_insert_x1_enable() && _simd_s16x2_fill_undefined_enable())
//#endif

#define _simd_s16x4_extract_x1_safe(X,I) (reinterpret_cast<const _simd_s16x4*>(&X)[I])
#ifdef _simd_s16x4_extract_x1_
#define _simd_s16x4_extract_x1(X,I) _simd_s16x4_extract_x1_(X,I)
#define _simd_s16x4__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_extract_x1_instruction_set>()
#else
#define _simd_s16x4_extract_x1(X,I) _simd_s16x4_extract_x1_safe(X,I)
#define _simd_s16x4__extract_x1_enable() true
#endif _simd_s16x4_extract_x1_

#define _simd_s16x4_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_s16x4*>(&X)[I] = Y)
#ifdef _simd_s16x4_insert_x1_
#define _simd_s16x4_insert_x1(X,I,Y) _simd_s16x4_insert_x1_(X,I,Y)
#define _simd_s16x4__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_insert_x1_instruction_set>()
#else
#define _simd_s16x4_insert_x1(X,I,Y) _simd_s16x4_insert_x1_safe(X,I,Y)
#define _simd_s16x4__insert_x1_enable() true
#endif _simd_s16x4_insert_x1_

#define _simd_s16x4_extract_x2_safe(X,I) (reinterpret_cast<const _simd_s16x4*>(&X)[I])
#ifdef _simd_s16x4_extract_x2_
#define _simd_s16x4_extract_x2(X,I) _simd_s16x4_extract_x2_(X,I)
#define _simd_s16x4__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_extract_x2_instruction_set>()
#else
#define _simd_s16x4_extract_x2(X,I) _simd_s16x4_extract_x2_safe(X,I)
#define _simd_s16x4__extract_x2_enable() true
#endif _simd_s16x4_extract_x2_

#define _simd_s16x4_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_s16x4*>(&X)[I] = Y)
#ifdef _simd_s16x4_insert_x2_
#define _simd_s16x4_insert_x2(X,I,Y) _simd_s16x4_insert_x2_(X,I,Y)
#define _simd_s16x4__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_insert_x2_instruction_set>()
#else
#define _simd_s16x4_insert_x2(X,I,Y) _simd_s16x4_insert_x2_safe(X,I,Y)
#define _simd_s16x4__insert_x2_enable() true
#endif _simd_s16x4_insert_x2_

#define _simd_s16x4_extract_x8_safe(X,I) _simd_s16x4_insert_x4_safe(_simd_s16x4_fill_undefined_safe(),0,X)
#ifdef _simd_s16x4_extract_x8_
#define _simd_s16x4_extract_x8(X,I) _simd_s16x4_extract_x8_(X,I)
#define _simd_s16x4__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_extract_x8_instruction_set>()
#else
#define _simd_s16x4_extract_x8(X,I) _simd_s16x4_extract_x8_safe(X,I)
#define _simd_s16x4__extract_x8_enable() true
#endif _simd_s16x4_extract_x8_

#define _simd_s16x4_insert_x8_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s16x1) * 8)
#ifdef _simd_s16x4_insert_x8_
#define _simd_s16x4_insert_x8(X,I,Y) _simd_s16x4_insert_x8_(X,I,Y)
#define _simd_s16x4__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_insert_x8_instruction_set>()
#else
#define _simd_s16x4_insert_x8(X,I,Y) _simd_s16x4_insert_x8_safe(X,I,Y)
#define _simd_s16x4__insert_x8_enable() true
#endif _simd_s16x4_insert_x8_

#define _simd_s16x4_extract_x16_safe(X,I) _simd_s16x4_insert_x4_safe(_simd_s16x4_fill_undefined_safe(),0,X)
#ifdef _simd_s16x4_extract_x16_
#define _simd_s16x4_extract_x16(X,I) _simd_s16x4_extract_x16_(X,I)
#define _simd_s16x4__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_extract_x16_instruction_set>()
#else
#define _simd_s16x4_extract_x16(X,I) _simd_s16x4_extract_x16_safe(X,I)
#define _simd_s16x4__extract_x16_enable() true
#endif _simd_s16x4_extract_x16_

#define _simd_s16x4_insert_x16_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s16x1) * 16)
#ifdef _simd_s16x4_insert_x16_
#define _simd_s16x4_insert_x16(X,I,Y) _simd_s16x4_insert_x16_(X,I,Y)
#define _simd_s16x4__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_insert_x16_instruction_set>()
#else
#define _simd_s16x4_insert_x16(X,I,Y) _simd_s16x4_insert_x16_safe(X,I,Y)
#define _simd_s16x4__insert_x16_enable() true
#endif _simd_s16x4_insert_x16_

#define _simd_s16x4_extract_x32_safe(X,I) _simd_s16x4_insert_x4_safe(_simd_s16x4_fill_undefined_safe(),0,X)
#ifdef _simd_s16x4_extract_x32_
#define _simd_s16x4_extract_x32(X,I) _simd_s16x4_extract_x32_(X,I)
#define _simd_s16x4__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_extract_x32_instruction_set>()
#else
#define _simd_s16x4_extract_x32(X,I) _simd_s16x4_extract_x32_safe(X,I)
#define _simd_s16x4__extract_x32_enable() true
#endif _simd_s16x4_extract_x32_

#define _simd_s16x4_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s16x1) * 32)
#ifdef _simd_s16x4_insert_x32_
#define _simd_s16x4_insert_x32(X,I,Y) _simd_s16x4_insert_x32_(X,I,Y)
#define _simd_s16x4__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_insert_x32_instruction_set>()
#else
#define _simd_s16x4_insert_x32(X,I,Y) _simd_s16x4_insert_x32_safe(X,I,Y)
#define _simd_s16x4__insert_x32_enable() true
#endif _simd_s16x4_insert_x32_

#define _simd_s16x4_extract_x64_safe(X,I) _simd_s16x4_insert_x4_safe(_simd_s16x4_fill_undefined_safe(),0,X)
#ifdef _simd_s16x4_extract_x64_
#define _simd_s16x4_extract_x64(X,I) _simd_s16x4_extract_x64_(X,I)
#define _simd_s16x4__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_extract_x64_instruction_set>()
#else
#define _simd_s16x4_extract_x64(X,I) _simd_s16x4_extract_x64_safe(X,I)
#define _simd_s16x4__extract_x64_enable() true
#endif _simd_s16x4_extract_x64_

#define _simd_s16x4_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s16x1) * 64)
#ifdef _simd_s16x4_insert_x64_
#define _simd_s16x4_insert_x64(X,I,Y) _simd_s16x4_insert_x64_(X,I,Y)
#define _simd_s16x4__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_insert_x64_instruction_set>()
#else
#define _simd_s16x4_insert_x64(X,I,Y) _simd_s16x4_insert_x64_safe(X,I,Y)
#define _simd_s16x4__insert_x64_enable() true
#endif _simd_s16x4_insert_x64_

#define _simd_s16x4_extract_safe(X,I) _simd_s16x4_extract_x1_safe(X,I)
#define _simd_s16x4_extract(X,I) _simd_s16x4_extract_x1(X,I)
#define _simd_s16x4_extract_enable() _simd_s16x4_extract_x1_enable()

#define _simd_s16x4_insert_safe(X,I,Y) _simd_s16x4_insert_x1_safe(X,I,Y)
#define _simd_s16x4_insert(X,I,Y) _simd_s16x4_insert_x1(X,I,Y)
#define _simd_s16x4_insert_enable() _simd_s16x4_insert_x1_enable()

//#ifndef _simd_s16x4_splitlo
//	#define _simd_s16x4_splitlo(X) _simd_s16x2_extract_x2(X,0)
//	#define _simd_s16x4_splitlo_enable() _simd_s16x2_extract_x2_enable()
//#endif

//#ifndef _simd_s16x4_splithi
//	#define _simd_s16x4_splithi(X) _simd_s16x2_extract_x2(X,1)
//	#define _simd_s16x4_splithi_enable() _simd_s16x2_extract_x2_enable()
//#endif

//#ifndef _simd_s16x4_combine
//	#define _simd_s16x4_combine(X,Y) _simd_s16x4_insert_x2(_simd_s16x4_insert_x2(_simd_s16x4_fill_undefined(), 0, X), 1, Y)
//	#define _simd_s16x4_combine_enable() (_simd_s16x4_insert_x2_enable() && _simd_s16x4_fill_undefined_enable())
//#endif

#define _simd_s16x8_extract_x1_safe(X,I) (reinterpret_cast<const _simd_s16x8*>(&X)[I])
#ifdef _simd_s16x8_extract_x1_
#define _simd_s16x8_extract_x1(X,I) _simd_s16x8_extract_x1_(X,I)
#define _simd_s16x8__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_extract_x1_instruction_set>()
#else
#define _simd_s16x8_extract_x1(X,I) _simd_s16x8_extract_x1_safe(X,I)
#define _simd_s16x8__extract_x1_enable() true
#endif _simd_s16x8_extract_x1_

#define _simd_s16x8_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_s16x8*>(&X)[I] = Y)
#ifdef _simd_s16x8_insert_x1_
#define _simd_s16x8_insert_x1(X,I,Y) _simd_s16x8_insert_x1_(X,I,Y)
#define _simd_s16x8__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_insert_x1_instruction_set>()
#else
#define _simd_s16x8_insert_x1(X,I,Y) _simd_s16x8_insert_x1_safe(X,I,Y)
#define _simd_s16x8__insert_x1_enable() true
#endif _simd_s16x8_insert_x1_

#define _simd_s16x8_extract_x2_safe(X,I) (reinterpret_cast<const _simd_s16x8*>(&X)[I])
#ifdef _simd_s16x8_extract_x2_
#define _simd_s16x8_extract_x2(X,I) _simd_s16x8_extract_x2_(X,I)
#define _simd_s16x8__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_extract_x2_instruction_set>()
#else
#define _simd_s16x8_extract_x2(X,I) _simd_s16x8_extract_x2_safe(X,I)
#define _simd_s16x8__extract_x2_enable() true
#endif _simd_s16x8_extract_x2_

#define _simd_s16x8_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_s16x8*>(&X)[I] = Y)
#ifdef _simd_s16x8_insert_x2_
#define _simd_s16x8_insert_x2(X,I,Y) _simd_s16x8_insert_x2_(X,I,Y)
#define _simd_s16x8__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_insert_x2_instruction_set>()
#else
#define _simd_s16x8_insert_x2(X,I,Y) _simd_s16x8_insert_x2_safe(X,I,Y)
#define _simd_s16x8__insert_x2_enable() true
#endif _simd_s16x8_insert_x2_

#define _simd_s16x8_extract_x4_safe(X,I) (reinterpret_cast<const _simd_s16x8*>(&X)[I])
#ifdef _simd_s16x8_extract_x4_
#define _simd_s16x8_extract_x4(X,I) _simd_s16x8_extract_x4_(X,I)
#define _simd_s16x8__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_extract_x4_instruction_set>()
#else
#define _simd_s16x8_extract_x4(X,I) _simd_s16x8_extract_x4_safe(X,I)
#define _simd_s16x8__extract_x4_enable() true
#endif _simd_s16x8_extract_x4_

#define _simd_s16x8_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_s16x8*>(&X)[I] = Y)
#ifdef _simd_s16x8_insert_x4_
#define _simd_s16x8_insert_x4(X,I,Y) _simd_s16x8_insert_x4_(X,I,Y)
#define _simd_s16x8__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_insert_x4_instruction_set>()
#else
#define _simd_s16x8_insert_x4(X,I,Y) _simd_s16x8_insert_x4_safe(X,I,Y)
#define _simd_s16x8__insert_x4_enable() true
#endif _simd_s16x8_insert_x4_

#define _simd_s16x8_extract_x16_safe(X,I) _simd_s16x8_insert_x8_safe(_simd_s16x8_fill_undefined_safe(),0,X)
#ifdef _simd_s16x8_extract_x16_
#define _simd_s16x8_extract_x16(X,I) _simd_s16x8_extract_x16_(X,I)
#define _simd_s16x8__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_extract_x16_instruction_set>()
#else
#define _simd_s16x8_extract_x16(X,I) _simd_s16x8_extract_x16_safe(X,I)
#define _simd_s16x8__extract_x16_enable() true
#endif _simd_s16x8_extract_x16_

#define _simd_s16x8_insert_x16_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s16x1) * 16)
#ifdef _simd_s16x8_insert_x16_
#define _simd_s16x8_insert_x16(X,I,Y) _simd_s16x8_insert_x16_(X,I,Y)
#define _simd_s16x8__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_insert_x16_instruction_set>()
#else
#define _simd_s16x8_insert_x16(X,I,Y) _simd_s16x8_insert_x16_safe(X,I,Y)
#define _simd_s16x8__insert_x16_enable() true
#endif _simd_s16x8_insert_x16_

#define _simd_s16x8_extract_x32_safe(X,I) _simd_s16x8_insert_x8_safe(_simd_s16x8_fill_undefined_safe(),0,X)
#ifdef _simd_s16x8_extract_x32_
#define _simd_s16x8_extract_x32(X,I) _simd_s16x8_extract_x32_(X,I)
#define _simd_s16x8__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_extract_x32_instruction_set>()
#else
#define _simd_s16x8_extract_x32(X,I) _simd_s16x8_extract_x32_safe(X,I)
#define _simd_s16x8__extract_x32_enable() true
#endif _simd_s16x8_extract_x32_

#define _simd_s16x8_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s16x1) * 32)
#ifdef _simd_s16x8_insert_x32_
#define _simd_s16x8_insert_x32(X,I,Y) _simd_s16x8_insert_x32_(X,I,Y)
#define _simd_s16x8__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_insert_x32_instruction_set>()
#else
#define _simd_s16x8_insert_x32(X,I,Y) _simd_s16x8_insert_x32_safe(X,I,Y)
#define _simd_s16x8__insert_x32_enable() true
#endif _simd_s16x8_insert_x32_

#define _simd_s16x8_extract_x64_safe(X,I) _simd_s16x8_insert_x8_safe(_simd_s16x8_fill_undefined_safe(),0,X)
#ifdef _simd_s16x8_extract_x64_
#define _simd_s16x8_extract_x64(X,I) _simd_s16x8_extract_x64_(X,I)
#define _simd_s16x8__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_extract_x64_instruction_set>()
#else
#define _simd_s16x8_extract_x64(X,I) _simd_s16x8_extract_x64_safe(X,I)
#define _simd_s16x8__extract_x64_enable() true
#endif _simd_s16x8_extract_x64_

#define _simd_s16x8_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s16x1) * 64)
#ifdef _simd_s16x8_insert_x64_
#define _simd_s16x8_insert_x64(X,I,Y) _simd_s16x8_insert_x64_(X,I,Y)
#define _simd_s16x8__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_insert_x64_instruction_set>()
#else
#define _simd_s16x8_insert_x64(X,I,Y) _simd_s16x8_insert_x64_safe(X,I,Y)
#define _simd_s16x8__insert_x64_enable() true
#endif _simd_s16x8_insert_x64_

#define _simd_s16x8_extract_safe(X,I) _simd_s16x8_extract_x1_safe(X,I)
#define _simd_s16x8_extract(X,I) _simd_s16x8_extract_x1(X,I)
#define _simd_s16x8_extract_enable() _simd_s16x8_extract_x1_enable()

#define _simd_s16x8_insert_safe(X,I,Y) _simd_s16x8_insert_x1_safe(X,I,Y)
#define _simd_s16x8_insert(X,I,Y) _simd_s16x8_insert_x1(X,I,Y)
#define _simd_s16x8_insert_enable() _simd_s16x8_insert_x1_enable()

//#ifndef _simd_s16x8_splitlo
//	#define _simd_s16x8_splitlo(X) _simd_s16x4_extract_x4(X,0)
//	#define _simd_s16x8_splitlo_enable() _simd_s16x4_extract_x4_enable()
//#endif

//#ifndef _simd_s16x8_splithi
//	#define _simd_s16x8_splithi(X) _simd_s16x4_extract_x4(X,1)
//	#define _simd_s16x8_splithi_enable() _simd_s16x4_extract_x4_enable()
//#endif

//#ifndef _simd_s16x8_combine
//	#define _simd_s16x8_combine(X,Y) _simd_s16x8_insert_x4(_simd_s16x8_insert_x4(_simd_s16x8_fill_undefined(), 0, X), 1, Y)
//	#define _simd_s16x8_combine_enable() (_simd_s16x8_insert_x4_enable() && _simd_s16x8_fill_undefined_enable())
//#endif

#define _simd_s16x16_extract_x1_safe(X,I) (reinterpret_cast<const _simd_s16x16*>(&X)[I])
#ifdef _simd_s16x16_extract_x1_
#define _simd_s16x16_extract_x1(X,I) _simd_s16x16_extract_x1_(X,I)
#define _simd_s16x16__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_extract_x1_instruction_set>()
#else
#define _simd_s16x16_extract_x1(X,I) _simd_s16x16_extract_x1_safe(X,I)
#define _simd_s16x16__extract_x1_enable() true
#endif _simd_s16x16_extract_x1_

#define _simd_s16x16_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_s16x16*>(&X)[I] = Y)
#ifdef _simd_s16x16_insert_x1_
#define _simd_s16x16_insert_x1(X,I,Y) _simd_s16x16_insert_x1_(X,I,Y)
#define _simd_s16x16__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_insert_x1_instruction_set>()
#else
#define _simd_s16x16_insert_x1(X,I,Y) _simd_s16x16_insert_x1_safe(X,I,Y)
#define _simd_s16x16__insert_x1_enable() true
#endif _simd_s16x16_insert_x1_

#define _simd_s16x16_extract_x2_safe(X,I) (reinterpret_cast<const _simd_s16x16*>(&X)[I])
#ifdef _simd_s16x16_extract_x2_
#define _simd_s16x16_extract_x2(X,I) _simd_s16x16_extract_x2_(X,I)
#define _simd_s16x16__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_extract_x2_instruction_set>()
#else
#define _simd_s16x16_extract_x2(X,I) _simd_s16x16_extract_x2_safe(X,I)
#define _simd_s16x16__extract_x2_enable() true
#endif _simd_s16x16_extract_x2_

#define _simd_s16x16_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_s16x16*>(&X)[I] = Y)
#ifdef _simd_s16x16_insert_x2_
#define _simd_s16x16_insert_x2(X,I,Y) _simd_s16x16_insert_x2_(X,I,Y)
#define _simd_s16x16__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_insert_x2_instruction_set>()
#else
#define _simd_s16x16_insert_x2(X,I,Y) _simd_s16x16_insert_x2_safe(X,I,Y)
#define _simd_s16x16__insert_x2_enable() true
#endif _simd_s16x16_insert_x2_

#define _simd_s16x16_extract_x4_safe(X,I) (reinterpret_cast<const _simd_s16x16*>(&X)[I])
#ifdef _simd_s16x16_extract_x4_
#define _simd_s16x16_extract_x4(X,I) _simd_s16x16_extract_x4_(X,I)
#define _simd_s16x16__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_extract_x4_instruction_set>()
#else
#define _simd_s16x16_extract_x4(X,I) _simd_s16x16_extract_x4_safe(X,I)
#define _simd_s16x16__extract_x4_enable() true
#endif _simd_s16x16_extract_x4_

#define _simd_s16x16_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_s16x16*>(&X)[I] = Y)
#ifdef _simd_s16x16_insert_x4_
#define _simd_s16x16_insert_x4(X,I,Y) _simd_s16x16_insert_x4_(X,I,Y)
#define _simd_s16x16__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_insert_x4_instruction_set>()
#else
#define _simd_s16x16_insert_x4(X,I,Y) _simd_s16x16_insert_x4_safe(X,I,Y)
#define _simd_s16x16__insert_x4_enable() true
#endif _simd_s16x16_insert_x4_

#define _simd_s16x16_extract_x8_safe(X,I) (reinterpret_cast<const _simd_s16x16*>(&X)[I])
#ifdef _simd_s16x16_extract_x8_
#define _simd_s16x16_extract_x8(X,I) _simd_s16x16_extract_x8_(X,I)
#define _simd_s16x16__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_extract_x8_instruction_set>()
#else
#define _simd_s16x16_extract_x8(X,I) _simd_s16x16_extract_x8_safe(X,I)
#define _simd_s16x16__extract_x8_enable() true
#endif _simd_s16x16_extract_x8_

#define _simd_s16x16_insert_x8_safe(X,I,Y) (reinterpret_cast<_simd_s16x16*>(&X)[I] = Y)
#ifdef _simd_s16x16_insert_x8_
#define _simd_s16x16_insert_x8(X,I,Y) _simd_s16x16_insert_x8_(X,I,Y)
#define _simd_s16x16__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_insert_x8_instruction_set>()
#else
#define _simd_s16x16_insert_x8(X,I,Y) _simd_s16x16_insert_x8_safe(X,I,Y)
#define _simd_s16x16__insert_x8_enable() true
#endif _simd_s16x16_insert_x8_

#define _simd_s16x16_extract_x32_safe(X,I) _simd_s16x16_insert_x16_safe(_simd_s16x16_fill_undefined_safe(),0,X)
#ifdef _simd_s16x16_extract_x32_
#define _simd_s16x16_extract_x32(X,I) _simd_s16x16_extract_x32_(X,I)
#define _simd_s16x16__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_extract_x32_instruction_set>()
#else
#define _simd_s16x16_extract_x32(X,I) _simd_s16x16_extract_x32_safe(X,I)
#define _simd_s16x16__extract_x32_enable() true
#endif _simd_s16x16_extract_x32_

#define _simd_s16x16_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s16x1) * 32)
#ifdef _simd_s16x16_insert_x32_
#define _simd_s16x16_insert_x32(X,I,Y) _simd_s16x16_insert_x32_(X,I,Y)
#define _simd_s16x16__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_insert_x32_instruction_set>()
#else
#define _simd_s16x16_insert_x32(X,I,Y) _simd_s16x16_insert_x32_safe(X,I,Y)
#define _simd_s16x16__insert_x32_enable() true
#endif _simd_s16x16_insert_x32_

#define _simd_s16x16_extract_x64_safe(X,I) _simd_s16x16_insert_x16_safe(_simd_s16x16_fill_undefined_safe(),0,X)
#ifdef _simd_s16x16_extract_x64_
#define _simd_s16x16_extract_x64(X,I) _simd_s16x16_extract_x64_(X,I)
#define _simd_s16x16__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_extract_x64_instruction_set>()
#else
#define _simd_s16x16_extract_x64(X,I) _simd_s16x16_extract_x64_safe(X,I)
#define _simd_s16x16__extract_x64_enable() true
#endif _simd_s16x16_extract_x64_

#define _simd_s16x16_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s16x1) * 64)
#ifdef _simd_s16x16_insert_x64_
#define _simd_s16x16_insert_x64(X,I,Y) _simd_s16x16_insert_x64_(X,I,Y)
#define _simd_s16x16__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_insert_x64_instruction_set>()
#else
#define _simd_s16x16_insert_x64(X,I,Y) _simd_s16x16_insert_x64_safe(X,I,Y)
#define _simd_s16x16__insert_x64_enable() true
#endif _simd_s16x16_insert_x64_

#define _simd_s16x16_extract_safe(X,I) _simd_s16x16_extract_x1_safe(X,I)
#define _simd_s16x16_extract(X,I) _simd_s16x16_extract_x1(X,I)
#define _simd_s16x16_extract_enable() _simd_s16x16_extract_x1_enable()

#define _simd_s16x16_insert_safe(X,I,Y) _simd_s16x16_insert_x1_safe(X,I,Y)
#define _simd_s16x16_insert(X,I,Y) _simd_s16x16_insert_x1(X,I,Y)
#define _simd_s16x16_insert_enable() _simd_s16x16_insert_x1_enable()

//#ifndef _simd_s16x16_splitlo
//	#define _simd_s16x16_splitlo(X) _simd_s16x8_extract_x8(X,0)
//	#define _simd_s16x16_splitlo_enable() _simd_s16x8_extract_x8_enable()
//#endif

//#ifndef _simd_s16x16_splithi
//	#define _simd_s16x16_splithi(X) _simd_s16x8_extract_x8(X,1)
//	#define _simd_s16x16_splithi_enable() _simd_s16x8_extract_x8_enable()
//#endif

//#ifndef _simd_s16x16_combine
//	#define _simd_s16x16_combine(X,Y) _simd_s16x16_insert_x8(_simd_s16x16_insert_x8(_simd_s16x16_fill_undefined(), 0, X), 1, Y)
//	#define _simd_s16x16_combine_enable() (_simd_s16x16_insert_x8_enable() && _simd_s16x16_fill_undefined_enable())
//#endif

#define _simd_s16x32_extract_x1_safe(X,I) (reinterpret_cast<const _simd_s16x32*>(&X)[I])
#ifdef _simd_s16x32_extract_x1_
#define _simd_s16x32_extract_x1(X,I) _simd_s16x32_extract_x1_(X,I)
#define _simd_s16x32__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_extract_x1_instruction_set>()
#else
#define _simd_s16x32_extract_x1(X,I) _simd_s16x32_extract_x1_safe(X,I)
#define _simd_s16x32__extract_x1_enable() true
#endif _simd_s16x32_extract_x1_

#define _simd_s16x32_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_s16x32*>(&X)[I] = Y)
#ifdef _simd_s16x32_insert_x1_
#define _simd_s16x32_insert_x1(X,I,Y) _simd_s16x32_insert_x1_(X,I,Y)
#define _simd_s16x32__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_insert_x1_instruction_set>()
#else
#define _simd_s16x32_insert_x1(X,I,Y) _simd_s16x32_insert_x1_safe(X,I,Y)
#define _simd_s16x32__insert_x1_enable() true
#endif _simd_s16x32_insert_x1_

#define _simd_s16x32_extract_x2_safe(X,I) (reinterpret_cast<const _simd_s16x32*>(&X)[I])
#ifdef _simd_s16x32_extract_x2_
#define _simd_s16x32_extract_x2(X,I) _simd_s16x32_extract_x2_(X,I)
#define _simd_s16x32__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_extract_x2_instruction_set>()
#else
#define _simd_s16x32_extract_x2(X,I) _simd_s16x32_extract_x2_safe(X,I)
#define _simd_s16x32__extract_x2_enable() true
#endif _simd_s16x32_extract_x2_

#define _simd_s16x32_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_s16x32*>(&X)[I] = Y)
#ifdef _simd_s16x32_insert_x2_
#define _simd_s16x32_insert_x2(X,I,Y) _simd_s16x32_insert_x2_(X,I,Y)
#define _simd_s16x32__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_insert_x2_instruction_set>()
#else
#define _simd_s16x32_insert_x2(X,I,Y) _simd_s16x32_insert_x2_safe(X,I,Y)
#define _simd_s16x32__insert_x2_enable() true
#endif _simd_s16x32_insert_x2_

#define _simd_s16x32_extract_x4_safe(X,I) (reinterpret_cast<const _simd_s16x32*>(&X)[I])
#ifdef _simd_s16x32_extract_x4_
#define _simd_s16x32_extract_x4(X,I) _simd_s16x32_extract_x4_(X,I)
#define _simd_s16x32__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_extract_x4_instruction_set>()
#else
#define _simd_s16x32_extract_x4(X,I) _simd_s16x32_extract_x4_safe(X,I)
#define _simd_s16x32__extract_x4_enable() true
#endif _simd_s16x32_extract_x4_

#define _simd_s16x32_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_s16x32*>(&X)[I] = Y)
#ifdef _simd_s16x32_insert_x4_
#define _simd_s16x32_insert_x4(X,I,Y) _simd_s16x32_insert_x4_(X,I,Y)
#define _simd_s16x32__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_insert_x4_instruction_set>()
#else
#define _simd_s16x32_insert_x4(X,I,Y) _simd_s16x32_insert_x4_safe(X,I,Y)
#define _simd_s16x32__insert_x4_enable() true
#endif _simd_s16x32_insert_x4_

#define _simd_s16x32_extract_x8_safe(X,I) (reinterpret_cast<const _simd_s16x32*>(&X)[I])
#ifdef _simd_s16x32_extract_x8_
#define _simd_s16x32_extract_x8(X,I) _simd_s16x32_extract_x8_(X,I)
#define _simd_s16x32__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_extract_x8_instruction_set>()
#else
#define _simd_s16x32_extract_x8(X,I) _simd_s16x32_extract_x8_safe(X,I)
#define _simd_s16x32__extract_x8_enable() true
#endif _simd_s16x32_extract_x8_

#define _simd_s16x32_insert_x8_safe(X,I,Y) (reinterpret_cast<_simd_s16x32*>(&X)[I] = Y)
#ifdef _simd_s16x32_insert_x8_
#define _simd_s16x32_insert_x8(X,I,Y) _simd_s16x32_insert_x8_(X,I,Y)
#define _simd_s16x32__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_insert_x8_instruction_set>()
#else
#define _simd_s16x32_insert_x8(X,I,Y) _simd_s16x32_insert_x8_safe(X,I,Y)
#define _simd_s16x32__insert_x8_enable() true
#endif _simd_s16x32_insert_x8_

#define _simd_s16x32_extract_x16_safe(X,I) (reinterpret_cast<const _simd_s16x32*>(&X)[I])
#ifdef _simd_s16x32_extract_x16_
#define _simd_s16x32_extract_x16(X,I) _simd_s16x32_extract_x16_(X,I)
#define _simd_s16x32__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_extract_x16_instruction_set>()
#else
#define _simd_s16x32_extract_x16(X,I) _simd_s16x32_extract_x16_safe(X,I)
#define _simd_s16x32__extract_x16_enable() true
#endif _simd_s16x32_extract_x16_

#define _simd_s16x32_insert_x16_safe(X,I,Y) (reinterpret_cast<_simd_s16x32*>(&X)[I] = Y)
#ifdef _simd_s16x32_insert_x16_
#define _simd_s16x32_insert_x16(X,I,Y) _simd_s16x32_insert_x16_(X,I,Y)
#define _simd_s16x32__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_insert_x16_instruction_set>()
#else
#define _simd_s16x32_insert_x16(X,I,Y) _simd_s16x32_insert_x16_safe(X,I,Y)
#define _simd_s16x32__insert_x16_enable() true
#endif _simd_s16x32_insert_x16_

#define _simd_s16x32_extract_x64_safe(X,I) _simd_s16x32_insert_x32_safe(_simd_s16x32_fill_undefined_safe(),0,X)
#ifdef _simd_s16x32_extract_x64_
#define _simd_s16x32_extract_x64(X,I) _simd_s16x32_extract_x64_(X,I)
#define _simd_s16x32__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_extract_x64_instruction_set>()
#else
#define _simd_s16x32_extract_x64(X,I) _simd_s16x32_extract_x64_safe(X,I)
#define _simd_s16x32__extract_x64_enable() true
#endif _simd_s16x32_extract_x64_

#define _simd_s16x32_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s16x1) * 64)
#ifdef _simd_s16x32_insert_x64_
#define _simd_s16x32_insert_x64(X,I,Y) _simd_s16x32_insert_x64_(X,I,Y)
#define _simd_s16x32__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_insert_x64_instruction_set>()
#else
#define _simd_s16x32_insert_x64(X,I,Y) _simd_s16x32_insert_x64_safe(X,I,Y)
#define _simd_s16x32__insert_x64_enable() true
#endif _simd_s16x32_insert_x64_

#define _simd_s16x32_extract_safe(X,I) _simd_s16x32_extract_x1_safe(X,I)
#define _simd_s16x32_extract(X,I) _simd_s16x32_extract_x1(X,I)
#define _simd_s16x32_extract_enable() _simd_s16x32_extract_x1_enable()

#define _simd_s16x32_insert_safe(X,I,Y) _simd_s16x32_insert_x1_safe(X,I,Y)
#define _simd_s16x32_insert(X,I,Y) _simd_s16x32_insert_x1(X,I,Y)
#define _simd_s16x32_insert_enable() _simd_s16x32_insert_x1_enable()

//#ifndef _simd_s16x32_splitlo
//	#define _simd_s16x32_splitlo(X) _simd_s16x16_extract_x16(X,0)
//	#define _simd_s16x32_splitlo_enable() _simd_s16x16_extract_x16_enable()
//#endif

//#ifndef _simd_s16x32_splithi
//	#define _simd_s16x32_splithi(X) _simd_s16x16_extract_x16(X,1)
//	#define _simd_s16x32_splithi_enable() _simd_s16x16_extract_x16_enable()
//#endif

//#ifndef _simd_s16x32_combine
//	#define _simd_s16x32_combine(X,Y) _simd_s16x32_insert_x16(_simd_s16x32_insert_x16(_simd_s16x32_fill_undefined(), 0, X), 1, Y)
//	#define _simd_s16x32_combine_enable() (_simd_s16x32_insert_x16_enable() && _simd_s16x32_fill_undefined_enable())
//#endif

#define _simd_s16x64_extract_x1_safe(X,I) (reinterpret_cast<const _simd_s16x64*>(&X)[I])
#ifdef _simd_s16x64_extract_x1_
#define _simd_s16x64_extract_x1(X,I) _simd_s16x64_extract_x1_(X,I)
#define _simd_s16x64__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_extract_x1_instruction_set>()
#else
#define _simd_s16x64_extract_x1(X,I) _simd_s16x64_extract_x1_safe(X,I)
#define _simd_s16x64__extract_x1_enable() true
#endif _simd_s16x64_extract_x1_

#define _simd_s16x64_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_s16x64*>(&X)[I] = Y)
#ifdef _simd_s16x64_insert_x1_
#define _simd_s16x64_insert_x1(X,I,Y) _simd_s16x64_insert_x1_(X,I,Y)
#define _simd_s16x64__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_insert_x1_instruction_set>()
#else
#define _simd_s16x64_insert_x1(X,I,Y) _simd_s16x64_insert_x1_safe(X,I,Y)
#define _simd_s16x64__insert_x1_enable() true
#endif _simd_s16x64_insert_x1_

#define _simd_s16x64_extract_x2_safe(X,I) (reinterpret_cast<const _simd_s16x64*>(&X)[I])
#ifdef _simd_s16x64_extract_x2_
#define _simd_s16x64_extract_x2(X,I) _simd_s16x64_extract_x2_(X,I)
#define _simd_s16x64__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_extract_x2_instruction_set>()
#else
#define _simd_s16x64_extract_x2(X,I) _simd_s16x64_extract_x2_safe(X,I)
#define _simd_s16x64__extract_x2_enable() true
#endif _simd_s16x64_extract_x2_

#define _simd_s16x64_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_s16x64*>(&X)[I] = Y)
#ifdef _simd_s16x64_insert_x2_
#define _simd_s16x64_insert_x2(X,I,Y) _simd_s16x64_insert_x2_(X,I,Y)
#define _simd_s16x64__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_insert_x2_instruction_set>()
#else
#define _simd_s16x64_insert_x2(X,I,Y) _simd_s16x64_insert_x2_safe(X,I,Y)
#define _simd_s16x64__insert_x2_enable() true
#endif _simd_s16x64_insert_x2_

#define _simd_s16x64_extract_x4_safe(X,I) (reinterpret_cast<const _simd_s16x64*>(&X)[I])
#ifdef _simd_s16x64_extract_x4_
#define _simd_s16x64_extract_x4(X,I) _simd_s16x64_extract_x4_(X,I)
#define _simd_s16x64__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_extract_x4_instruction_set>()
#else
#define _simd_s16x64_extract_x4(X,I) _simd_s16x64_extract_x4_safe(X,I)
#define _simd_s16x64__extract_x4_enable() true
#endif _simd_s16x64_extract_x4_

#define _simd_s16x64_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_s16x64*>(&X)[I] = Y)
#ifdef _simd_s16x64_insert_x4_
#define _simd_s16x64_insert_x4(X,I,Y) _simd_s16x64_insert_x4_(X,I,Y)
#define _simd_s16x64__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_insert_x4_instruction_set>()
#else
#define _simd_s16x64_insert_x4(X,I,Y) _simd_s16x64_insert_x4_safe(X,I,Y)
#define _simd_s16x64__insert_x4_enable() true
#endif _simd_s16x64_insert_x4_

#define _simd_s16x64_extract_x8_safe(X,I) (reinterpret_cast<const _simd_s16x64*>(&X)[I])
#ifdef _simd_s16x64_extract_x8_
#define _simd_s16x64_extract_x8(X,I) _simd_s16x64_extract_x8_(X,I)
#define _simd_s16x64__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_extract_x8_instruction_set>()
#else
#define _simd_s16x64_extract_x8(X,I) _simd_s16x64_extract_x8_safe(X,I)
#define _simd_s16x64__extract_x8_enable() true
#endif _simd_s16x64_extract_x8_

#define _simd_s16x64_insert_x8_safe(X,I,Y) (reinterpret_cast<_simd_s16x64*>(&X)[I] = Y)
#ifdef _simd_s16x64_insert_x8_
#define _simd_s16x64_insert_x8(X,I,Y) _simd_s16x64_insert_x8_(X,I,Y)
#define _simd_s16x64__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_insert_x8_instruction_set>()
#else
#define _simd_s16x64_insert_x8(X,I,Y) _simd_s16x64_insert_x8_safe(X,I,Y)
#define _simd_s16x64__insert_x8_enable() true
#endif _simd_s16x64_insert_x8_

#define _simd_s16x64_extract_x16_safe(X,I) (reinterpret_cast<const _simd_s16x64*>(&X)[I])
#ifdef _simd_s16x64_extract_x16_
#define _simd_s16x64_extract_x16(X,I) _simd_s16x64_extract_x16_(X,I)
#define _simd_s16x64__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_extract_x16_instruction_set>()
#else
#define _simd_s16x64_extract_x16(X,I) _simd_s16x64_extract_x16_safe(X,I)
#define _simd_s16x64__extract_x16_enable() true
#endif _simd_s16x64_extract_x16_

#define _simd_s16x64_insert_x16_safe(X,I,Y) (reinterpret_cast<_simd_s16x64*>(&X)[I] = Y)
#ifdef _simd_s16x64_insert_x16_
#define _simd_s16x64_insert_x16(X,I,Y) _simd_s16x64_insert_x16_(X,I,Y)
#define _simd_s16x64__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_insert_x16_instruction_set>()
#else
#define _simd_s16x64_insert_x16(X,I,Y) _simd_s16x64_insert_x16_safe(X,I,Y)
#define _simd_s16x64__insert_x16_enable() true
#endif _simd_s16x64_insert_x16_

#define _simd_s16x64_extract_x32_safe(X,I) (reinterpret_cast<const _simd_s16x64*>(&X)[I])
#ifdef _simd_s16x64_extract_x32_
#define _simd_s16x64_extract_x32(X,I) _simd_s16x64_extract_x32_(X,I)
#define _simd_s16x64__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_extract_x32_instruction_set>()
#else
#define _simd_s16x64_extract_x32(X,I) _simd_s16x64_extract_x32_safe(X,I)
#define _simd_s16x64__extract_x32_enable() true
#endif _simd_s16x64_extract_x32_

#define _simd_s16x64_insert_x32_safe(X,I,Y) (reinterpret_cast<_simd_s16x64*>(&X)[I] = Y)
#ifdef _simd_s16x64_insert_x32_
#define _simd_s16x64_insert_x32(X,I,Y) _simd_s16x64_insert_x32_(X,I,Y)
#define _simd_s16x64__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_insert_x32_instruction_set>()
#else
#define _simd_s16x64_insert_x32(X,I,Y) _simd_s16x64_insert_x32_safe(X,I,Y)
#define _simd_s16x64__insert_x32_enable() true
#endif _simd_s16x64_insert_x32_

#define _simd_s16x64_extract_safe(X,I) _simd_s16x64_extract_x1_safe(X,I)
#define _simd_s16x64_extract(X,I) _simd_s16x64_extract_x1(X,I)
#define _simd_s16x64_extract_enable() _simd_s16x64_extract_x1_enable()

#define _simd_s16x64_insert_safe(X,I,Y) _simd_s16x64_insert_x1_safe(X,I,Y)
#define _simd_s16x64_insert(X,I,Y) _simd_s16x64_insert_x1(X,I,Y)
#define _simd_s16x64_insert_enable() _simd_s16x64_insert_x1_enable()

//#ifndef _simd_s16x64_splitlo
//	#define _simd_s16x64_splitlo(X) _simd_s16x32_extract_x32(X,0)
//	#define _simd_s16x64_splitlo_enable() _simd_s16x32_extract_x32_enable()
//#endif

//#ifndef _simd_s16x64_splithi
//	#define _simd_s16x64_splithi(X) _simd_s16x32_extract_x32(X,1)
//	#define _simd_s16x64_splithi_enable() _simd_s16x32_extract_x32_enable()
//#endif

//#ifndef _simd_s16x64_combine
//	#define _simd_s16x64_combine(X,Y) _simd_s16x64_insert_x32(_simd_s16x64_insert_x32(_simd_s16x64_fill_undefined(), 0, X), 1, Y)
//	#define _simd_s16x64_combine_enable() (_simd_s16x64_insert_x32_enable() && _simd_s16x64_fill_undefined_enable())
//#endif

// -- u16 --

#define _simd_u16x2_extract_x1_safe(X,I) (reinterpret_cast<const _simd_u16x2*>(&X)[I])
#ifdef _simd_u16x2_extract_x1_
#define _simd_u16x2_extract_x1(X,I) _simd_u16x2_extract_x1_(X,I)
#define _simd_u16x2__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_extract_x1_instruction_set>()
#else
#define _simd_u16x2_extract_x1(X,I) _simd_u16x2_extract_x1_safe(X,I)
#define _simd_u16x2__extract_x1_enable() true
#endif _simd_u16x2_extract_x1_

#define _simd_u16x2_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_u16x2*>(&X)[I] = Y)
#ifdef _simd_u16x2_insert_x1_
#define _simd_u16x2_insert_x1(X,I,Y) _simd_u16x2_insert_x1_(X,I,Y)
#define _simd_u16x2__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_insert_x1_instruction_set>()
#else
#define _simd_u16x2_insert_x1(X,I,Y) _simd_u16x2_insert_x1_safe(X,I,Y)
#define _simd_u16x2__insert_x1_enable() true
#endif _simd_u16x2_insert_x1_

#define _simd_u16x2_extract_x4_safe(X,I) _simd_u16x2_insert_x2_safe(_simd_u16x2_fill_undefined_safe(),0,X)
#ifdef _simd_u16x2_extract_x4_
#define _simd_u16x2_extract_x4(X,I) _simd_u16x2_extract_x4_(X,I)
#define _simd_u16x2__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_extract_x4_instruction_set>()
#else
#define _simd_u16x2_extract_x4(X,I) _simd_u16x2_extract_x4_safe(X,I)
#define _simd_u16x2__extract_x4_enable() true
#endif _simd_u16x2_extract_x4_

#define _simd_u16x2_insert_x4_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u16x1) * 4)
#ifdef _simd_u16x2_insert_x4_
#define _simd_u16x2_insert_x4(X,I,Y) _simd_u16x2_insert_x4_(X,I,Y)
#define _simd_u16x2__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_insert_x4_instruction_set>()
#else
#define _simd_u16x2_insert_x4(X,I,Y) _simd_u16x2_insert_x4_safe(X,I,Y)
#define _simd_u16x2__insert_x4_enable() true
#endif _simd_u16x2_insert_x4_

#define _simd_u16x2_extract_x8_safe(X,I) _simd_u16x2_insert_x2_safe(_simd_u16x2_fill_undefined_safe(),0,X)
#ifdef _simd_u16x2_extract_x8_
#define _simd_u16x2_extract_x8(X,I) _simd_u16x2_extract_x8_(X,I)
#define _simd_u16x2__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_extract_x8_instruction_set>()
#else
#define _simd_u16x2_extract_x8(X,I) _simd_u16x2_extract_x8_safe(X,I)
#define _simd_u16x2__extract_x8_enable() true
#endif _simd_u16x2_extract_x8_

#define _simd_u16x2_insert_x8_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u16x1) * 8)
#ifdef _simd_u16x2_insert_x8_
#define _simd_u16x2_insert_x8(X,I,Y) _simd_u16x2_insert_x8_(X,I,Y)
#define _simd_u16x2__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_insert_x8_instruction_set>()
#else
#define _simd_u16x2_insert_x8(X,I,Y) _simd_u16x2_insert_x8_safe(X,I,Y)
#define _simd_u16x2__insert_x8_enable() true
#endif _simd_u16x2_insert_x8_

#define _simd_u16x2_extract_x16_safe(X,I) _simd_u16x2_insert_x2_safe(_simd_u16x2_fill_undefined_safe(),0,X)
#ifdef _simd_u16x2_extract_x16_
#define _simd_u16x2_extract_x16(X,I) _simd_u16x2_extract_x16_(X,I)
#define _simd_u16x2__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_extract_x16_instruction_set>()
#else
#define _simd_u16x2_extract_x16(X,I) _simd_u16x2_extract_x16_safe(X,I)
#define _simd_u16x2__extract_x16_enable() true
#endif _simd_u16x2_extract_x16_

#define _simd_u16x2_insert_x16_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u16x1) * 16)
#ifdef _simd_u16x2_insert_x16_
#define _simd_u16x2_insert_x16(X,I,Y) _simd_u16x2_insert_x16_(X,I,Y)
#define _simd_u16x2__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_insert_x16_instruction_set>()
#else
#define _simd_u16x2_insert_x16(X,I,Y) _simd_u16x2_insert_x16_safe(X,I,Y)
#define _simd_u16x2__insert_x16_enable() true
#endif _simd_u16x2_insert_x16_

#define _simd_u16x2_extract_x32_safe(X,I) _simd_u16x2_insert_x2_safe(_simd_u16x2_fill_undefined_safe(),0,X)
#ifdef _simd_u16x2_extract_x32_
#define _simd_u16x2_extract_x32(X,I) _simd_u16x2_extract_x32_(X,I)
#define _simd_u16x2__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_extract_x32_instruction_set>()
#else
#define _simd_u16x2_extract_x32(X,I) _simd_u16x2_extract_x32_safe(X,I)
#define _simd_u16x2__extract_x32_enable() true
#endif _simd_u16x2_extract_x32_

#define _simd_u16x2_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u16x1) * 32)
#ifdef _simd_u16x2_insert_x32_
#define _simd_u16x2_insert_x32(X,I,Y) _simd_u16x2_insert_x32_(X,I,Y)
#define _simd_u16x2__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_insert_x32_instruction_set>()
#else
#define _simd_u16x2_insert_x32(X,I,Y) _simd_u16x2_insert_x32_safe(X,I,Y)
#define _simd_u16x2__insert_x32_enable() true
#endif _simd_u16x2_insert_x32_

#define _simd_u16x2_extract_x64_safe(X,I) _simd_u16x2_insert_x2_safe(_simd_u16x2_fill_undefined_safe(),0,X)
#ifdef _simd_u16x2_extract_x64_
#define _simd_u16x2_extract_x64(X,I) _simd_u16x2_extract_x64_(X,I)
#define _simd_u16x2__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_extract_x64_instruction_set>()
#else
#define _simd_u16x2_extract_x64(X,I) _simd_u16x2_extract_x64_safe(X,I)
#define _simd_u16x2__extract_x64_enable() true
#endif _simd_u16x2_extract_x64_

#define _simd_u16x2_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u16x1) * 64)
#ifdef _simd_u16x2_insert_x64_
#define _simd_u16x2_insert_x64(X,I,Y) _simd_u16x2_insert_x64_(X,I,Y)
#define _simd_u16x2__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_insert_x64_instruction_set>()
#else
#define _simd_u16x2_insert_x64(X,I,Y) _simd_u16x2_insert_x64_safe(X,I,Y)
#define _simd_u16x2__insert_x64_enable() true
#endif _simd_u16x2_insert_x64_

#define _simd_u16x2_extract_safe(X,I) _simd_u16x2_extract_x1_safe(X,I)
#define _simd_u16x2_extract(X,I) _simd_u16x2_extract_x1(X,I)
#define _simd_u16x2_extract_enable() _simd_u16x2_extract_x1_enable()

#define _simd_u16x2_insert_safe(X,I,Y) _simd_u16x2_insert_x1_safe(X,I,Y)
#define _simd_u16x2_insert(X,I,Y) _simd_u16x2_insert_x1(X,I,Y)
#define _simd_u16x2_insert_enable() _simd_u16x2_insert_x1_enable()

//#ifndef _simd_u16x2_splitlo
//	#define _simd_u16x2_splitlo(X) _simd_u16x1_extract_x1(X,0)
//	#define _simd_u16x2_splitlo_enable() _simd_u16x1_extract_x1_enable()
//#endif

//#ifndef _simd_u16x2_splithi
//	#define _simd_u16x2_splithi(X) _simd_u16x1_extract_x1(X,1)
//	#define _simd_u16x2_splithi_enable() _simd_u16x1_extract_x1_enable()
//#endif

//#ifndef _simd_u16x2_combine
//	#define _simd_u16x2_combine(X,Y) _simd_u16x2_insert_x1(_simd_u16x2_insert_x1(_simd_u16x2_fill_undefined(), 0, X), 1, Y)
//	#define _simd_u16x2_combine_enable() (_simd_u16x2_insert_x1_enable() && _simd_u16x2_fill_undefined_enable())
//#endif

#define _simd_u16x4_extract_x1_safe(X,I) (reinterpret_cast<const _simd_u16x4*>(&X)[I])
#ifdef _simd_u16x4_extract_x1_
#define _simd_u16x4_extract_x1(X,I) _simd_u16x4_extract_x1_(X,I)
#define _simd_u16x4__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_extract_x1_instruction_set>()
#else
#define _simd_u16x4_extract_x1(X,I) _simd_u16x4_extract_x1_safe(X,I)
#define _simd_u16x4__extract_x1_enable() true
#endif _simd_u16x4_extract_x1_

#define _simd_u16x4_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_u16x4*>(&X)[I] = Y)
#ifdef _simd_u16x4_insert_x1_
#define _simd_u16x4_insert_x1(X,I,Y) _simd_u16x4_insert_x1_(X,I,Y)
#define _simd_u16x4__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_insert_x1_instruction_set>()
#else
#define _simd_u16x4_insert_x1(X,I,Y) _simd_u16x4_insert_x1_safe(X,I,Y)
#define _simd_u16x4__insert_x1_enable() true
#endif _simd_u16x4_insert_x1_

#define _simd_u16x4_extract_x2_safe(X,I) (reinterpret_cast<const _simd_u16x4*>(&X)[I])
#ifdef _simd_u16x4_extract_x2_
#define _simd_u16x4_extract_x2(X,I) _simd_u16x4_extract_x2_(X,I)
#define _simd_u16x4__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_extract_x2_instruction_set>()
#else
#define _simd_u16x4_extract_x2(X,I) _simd_u16x4_extract_x2_safe(X,I)
#define _simd_u16x4__extract_x2_enable() true
#endif _simd_u16x4_extract_x2_

#define _simd_u16x4_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_u16x4*>(&X)[I] = Y)
#ifdef _simd_u16x4_insert_x2_
#define _simd_u16x4_insert_x2(X,I,Y) _simd_u16x4_insert_x2_(X,I,Y)
#define _simd_u16x4__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_insert_x2_instruction_set>()
#else
#define _simd_u16x4_insert_x2(X,I,Y) _simd_u16x4_insert_x2_safe(X,I,Y)
#define _simd_u16x4__insert_x2_enable() true
#endif _simd_u16x4_insert_x2_

#define _simd_u16x4_extract_x8_safe(X,I) _simd_u16x4_insert_x4_safe(_simd_u16x4_fill_undefined_safe(),0,X)
#ifdef _simd_u16x4_extract_x8_
#define _simd_u16x4_extract_x8(X,I) _simd_u16x4_extract_x8_(X,I)
#define _simd_u16x4__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_extract_x8_instruction_set>()
#else
#define _simd_u16x4_extract_x8(X,I) _simd_u16x4_extract_x8_safe(X,I)
#define _simd_u16x4__extract_x8_enable() true
#endif _simd_u16x4_extract_x8_

#define _simd_u16x4_insert_x8_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u16x1) * 8)
#ifdef _simd_u16x4_insert_x8_
#define _simd_u16x4_insert_x8(X,I,Y) _simd_u16x4_insert_x8_(X,I,Y)
#define _simd_u16x4__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_insert_x8_instruction_set>()
#else
#define _simd_u16x4_insert_x8(X,I,Y) _simd_u16x4_insert_x8_safe(X,I,Y)
#define _simd_u16x4__insert_x8_enable() true
#endif _simd_u16x4_insert_x8_

#define _simd_u16x4_extract_x16_safe(X,I) _simd_u16x4_insert_x4_safe(_simd_u16x4_fill_undefined_safe(),0,X)
#ifdef _simd_u16x4_extract_x16_
#define _simd_u16x4_extract_x16(X,I) _simd_u16x4_extract_x16_(X,I)
#define _simd_u16x4__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_extract_x16_instruction_set>()
#else
#define _simd_u16x4_extract_x16(X,I) _simd_u16x4_extract_x16_safe(X,I)
#define _simd_u16x4__extract_x16_enable() true
#endif _simd_u16x4_extract_x16_

#define _simd_u16x4_insert_x16_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u16x1) * 16)
#ifdef _simd_u16x4_insert_x16_
#define _simd_u16x4_insert_x16(X,I,Y) _simd_u16x4_insert_x16_(X,I,Y)
#define _simd_u16x4__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_insert_x16_instruction_set>()
#else
#define _simd_u16x4_insert_x16(X,I,Y) _simd_u16x4_insert_x16_safe(X,I,Y)
#define _simd_u16x4__insert_x16_enable() true
#endif _simd_u16x4_insert_x16_

#define _simd_u16x4_extract_x32_safe(X,I) _simd_u16x4_insert_x4_safe(_simd_u16x4_fill_undefined_safe(),0,X)
#ifdef _simd_u16x4_extract_x32_
#define _simd_u16x4_extract_x32(X,I) _simd_u16x4_extract_x32_(X,I)
#define _simd_u16x4__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_extract_x32_instruction_set>()
#else
#define _simd_u16x4_extract_x32(X,I) _simd_u16x4_extract_x32_safe(X,I)
#define _simd_u16x4__extract_x32_enable() true
#endif _simd_u16x4_extract_x32_

#define _simd_u16x4_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u16x1) * 32)
#ifdef _simd_u16x4_insert_x32_
#define _simd_u16x4_insert_x32(X,I,Y) _simd_u16x4_insert_x32_(X,I,Y)
#define _simd_u16x4__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_insert_x32_instruction_set>()
#else
#define _simd_u16x4_insert_x32(X,I,Y) _simd_u16x4_insert_x32_safe(X,I,Y)
#define _simd_u16x4__insert_x32_enable() true
#endif _simd_u16x4_insert_x32_

#define _simd_u16x4_extract_x64_safe(X,I) _simd_u16x4_insert_x4_safe(_simd_u16x4_fill_undefined_safe(),0,X)
#ifdef _simd_u16x4_extract_x64_
#define _simd_u16x4_extract_x64(X,I) _simd_u16x4_extract_x64_(X,I)
#define _simd_u16x4__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_extract_x64_instruction_set>()
#else
#define _simd_u16x4_extract_x64(X,I) _simd_u16x4_extract_x64_safe(X,I)
#define _simd_u16x4__extract_x64_enable() true
#endif _simd_u16x4_extract_x64_

#define _simd_u16x4_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u16x1) * 64)
#ifdef _simd_u16x4_insert_x64_
#define _simd_u16x4_insert_x64(X,I,Y) _simd_u16x4_insert_x64_(X,I,Y)
#define _simd_u16x4__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_insert_x64_instruction_set>()
#else
#define _simd_u16x4_insert_x64(X,I,Y) _simd_u16x4_insert_x64_safe(X,I,Y)
#define _simd_u16x4__insert_x64_enable() true
#endif _simd_u16x4_insert_x64_

#define _simd_u16x4_extract_safe(X,I) _simd_u16x4_extract_x1_safe(X,I)
#define _simd_u16x4_extract(X,I) _simd_u16x4_extract_x1(X,I)
#define _simd_u16x4_extract_enable() _simd_u16x4_extract_x1_enable()

#define _simd_u16x4_insert_safe(X,I,Y) _simd_u16x4_insert_x1_safe(X,I,Y)
#define _simd_u16x4_insert(X,I,Y) _simd_u16x4_insert_x1(X,I,Y)
#define _simd_u16x4_insert_enable() _simd_u16x4_insert_x1_enable()

//#ifndef _simd_u16x4_splitlo
//	#define _simd_u16x4_splitlo(X) _simd_u16x2_extract_x2(X,0)
//	#define _simd_u16x4_splitlo_enable() _simd_u16x2_extract_x2_enable()
//#endif

//#ifndef _simd_u16x4_splithi
//	#define _simd_u16x4_splithi(X) _simd_u16x2_extract_x2(X,1)
//	#define _simd_u16x4_splithi_enable() _simd_u16x2_extract_x2_enable()
//#endif

//#ifndef _simd_u16x4_combine
//	#define _simd_u16x4_combine(X,Y) _simd_u16x4_insert_x2(_simd_u16x4_insert_x2(_simd_u16x4_fill_undefined(), 0, X), 1, Y)
//	#define _simd_u16x4_combine_enable() (_simd_u16x4_insert_x2_enable() && _simd_u16x4_fill_undefined_enable())
//#endif

#define _simd_u16x8_extract_x1_safe(X,I) (reinterpret_cast<const _simd_u16x8*>(&X)[I])
#ifdef _simd_u16x8_extract_x1_
#define _simd_u16x8_extract_x1(X,I) _simd_u16x8_extract_x1_(X,I)
#define _simd_u16x8__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_extract_x1_instruction_set>()
#else
#define _simd_u16x8_extract_x1(X,I) _simd_u16x8_extract_x1_safe(X,I)
#define _simd_u16x8__extract_x1_enable() true
#endif _simd_u16x8_extract_x1_

#define _simd_u16x8_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_u16x8*>(&X)[I] = Y)
#ifdef _simd_u16x8_insert_x1_
#define _simd_u16x8_insert_x1(X,I,Y) _simd_u16x8_insert_x1_(X,I,Y)
#define _simd_u16x8__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_insert_x1_instruction_set>()
#else
#define _simd_u16x8_insert_x1(X,I,Y) _simd_u16x8_insert_x1_safe(X,I,Y)
#define _simd_u16x8__insert_x1_enable() true
#endif _simd_u16x8_insert_x1_

#define _simd_u16x8_extract_x2_safe(X,I) (reinterpret_cast<const _simd_u16x8*>(&X)[I])
#ifdef _simd_u16x8_extract_x2_
#define _simd_u16x8_extract_x2(X,I) _simd_u16x8_extract_x2_(X,I)
#define _simd_u16x8__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_extract_x2_instruction_set>()
#else
#define _simd_u16x8_extract_x2(X,I) _simd_u16x8_extract_x2_safe(X,I)
#define _simd_u16x8__extract_x2_enable() true
#endif _simd_u16x8_extract_x2_

#define _simd_u16x8_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_u16x8*>(&X)[I] = Y)
#ifdef _simd_u16x8_insert_x2_
#define _simd_u16x8_insert_x2(X,I,Y) _simd_u16x8_insert_x2_(X,I,Y)
#define _simd_u16x8__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_insert_x2_instruction_set>()
#else
#define _simd_u16x8_insert_x2(X,I,Y) _simd_u16x8_insert_x2_safe(X,I,Y)
#define _simd_u16x8__insert_x2_enable() true
#endif _simd_u16x8_insert_x2_

#define _simd_u16x8_extract_x4_safe(X,I) (reinterpret_cast<const _simd_u16x8*>(&X)[I])
#ifdef _simd_u16x8_extract_x4_
#define _simd_u16x8_extract_x4(X,I) _simd_u16x8_extract_x4_(X,I)
#define _simd_u16x8__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_extract_x4_instruction_set>()
#else
#define _simd_u16x8_extract_x4(X,I) _simd_u16x8_extract_x4_safe(X,I)
#define _simd_u16x8__extract_x4_enable() true
#endif _simd_u16x8_extract_x4_

#define _simd_u16x8_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_u16x8*>(&X)[I] = Y)
#ifdef _simd_u16x8_insert_x4_
#define _simd_u16x8_insert_x4(X,I,Y) _simd_u16x8_insert_x4_(X,I,Y)
#define _simd_u16x8__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_insert_x4_instruction_set>()
#else
#define _simd_u16x8_insert_x4(X,I,Y) _simd_u16x8_insert_x4_safe(X,I,Y)
#define _simd_u16x8__insert_x4_enable() true
#endif _simd_u16x8_insert_x4_

#define _simd_u16x8_extract_x16_safe(X,I) _simd_u16x8_insert_x8_safe(_simd_u16x8_fill_undefined_safe(),0,X)
#ifdef _simd_u16x8_extract_x16_
#define _simd_u16x8_extract_x16(X,I) _simd_u16x8_extract_x16_(X,I)
#define _simd_u16x8__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_extract_x16_instruction_set>()
#else
#define _simd_u16x8_extract_x16(X,I) _simd_u16x8_extract_x16_safe(X,I)
#define _simd_u16x8__extract_x16_enable() true
#endif _simd_u16x8_extract_x16_

#define _simd_u16x8_insert_x16_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u16x1) * 16)
#ifdef _simd_u16x8_insert_x16_
#define _simd_u16x8_insert_x16(X,I,Y) _simd_u16x8_insert_x16_(X,I,Y)
#define _simd_u16x8__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_insert_x16_instruction_set>()
#else
#define _simd_u16x8_insert_x16(X,I,Y) _simd_u16x8_insert_x16_safe(X,I,Y)
#define _simd_u16x8__insert_x16_enable() true
#endif _simd_u16x8_insert_x16_

#define _simd_u16x8_extract_x32_safe(X,I) _simd_u16x8_insert_x8_safe(_simd_u16x8_fill_undefined_safe(),0,X)
#ifdef _simd_u16x8_extract_x32_
#define _simd_u16x8_extract_x32(X,I) _simd_u16x8_extract_x32_(X,I)
#define _simd_u16x8__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_extract_x32_instruction_set>()
#else
#define _simd_u16x8_extract_x32(X,I) _simd_u16x8_extract_x32_safe(X,I)
#define _simd_u16x8__extract_x32_enable() true
#endif _simd_u16x8_extract_x32_

#define _simd_u16x8_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u16x1) * 32)
#ifdef _simd_u16x8_insert_x32_
#define _simd_u16x8_insert_x32(X,I,Y) _simd_u16x8_insert_x32_(X,I,Y)
#define _simd_u16x8__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_insert_x32_instruction_set>()
#else
#define _simd_u16x8_insert_x32(X,I,Y) _simd_u16x8_insert_x32_safe(X,I,Y)
#define _simd_u16x8__insert_x32_enable() true
#endif _simd_u16x8_insert_x32_

#define _simd_u16x8_extract_x64_safe(X,I) _simd_u16x8_insert_x8_safe(_simd_u16x8_fill_undefined_safe(),0,X)
#ifdef _simd_u16x8_extract_x64_
#define _simd_u16x8_extract_x64(X,I) _simd_u16x8_extract_x64_(X,I)
#define _simd_u16x8__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_extract_x64_instruction_set>()
#else
#define _simd_u16x8_extract_x64(X,I) _simd_u16x8_extract_x64_safe(X,I)
#define _simd_u16x8__extract_x64_enable() true
#endif _simd_u16x8_extract_x64_

#define _simd_u16x8_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u16x1) * 64)
#ifdef _simd_u16x8_insert_x64_
#define _simd_u16x8_insert_x64(X,I,Y) _simd_u16x8_insert_x64_(X,I,Y)
#define _simd_u16x8__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_insert_x64_instruction_set>()
#else
#define _simd_u16x8_insert_x64(X,I,Y) _simd_u16x8_insert_x64_safe(X,I,Y)
#define _simd_u16x8__insert_x64_enable() true
#endif _simd_u16x8_insert_x64_

#define _simd_u16x8_extract_safe(X,I) _simd_u16x8_extract_x1_safe(X,I)
#define _simd_u16x8_extract(X,I) _simd_u16x8_extract_x1(X,I)
#define _simd_u16x8_extract_enable() _simd_u16x8_extract_x1_enable()

#define _simd_u16x8_insert_safe(X,I,Y) _simd_u16x8_insert_x1_safe(X,I,Y)
#define _simd_u16x8_insert(X,I,Y) _simd_u16x8_insert_x1(X,I,Y)
#define _simd_u16x8_insert_enable() _simd_u16x8_insert_x1_enable()

//#ifndef _simd_u16x8_splitlo
//	#define _simd_u16x8_splitlo(X) _simd_u16x4_extract_x4(X,0)
//	#define _simd_u16x8_splitlo_enable() _simd_u16x4_extract_x4_enable()
//#endif

//#ifndef _simd_u16x8_splithi
//	#define _simd_u16x8_splithi(X) _simd_u16x4_extract_x4(X,1)
//	#define _simd_u16x8_splithi_enable() _simd_u16x4_extract_x4_enable()
//#endif

//#ifndef _simd_u16x8_combine
//	#define _simd_u16x8_combine(X,Y) _simd_u16x8_insert_x4(_simd_u16x8_insert_x4(_simd_u16x8_fill_undefined(), 0, X), 1, Y)
//	#define _simd_u16x8_combine_enable() (_simd_u16x8_insert_x4_enable() && _simd_u16x8_fill_undefined_enable())
//#endif

#define _simd_u16x16_extract_x1_safe(X,I) (reinterpret_cast<const _simd_u16x16*>(&X)[I])
#ifdef _simd_u16x16_extract_x1_
#define _simd_u16x16_extract_x1(X,I) _simd_u16x16_extract_x1_(X,I)
#define _simd_u16x16__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_extract_x1_instruction_set>()
#else
#define _simd_u16x16_extract_x1(X,I) _simd_u16x16_extract_x1_safe(X,I)
#define _simd_u16x16__extract_x1_enable() true
#endif _simd_u16x16_extract_x1_

#define _simd_u16x16_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_u16x16*>(&X)[I] = Y)
#ifdef _simd_u16x16_insert_x1_
#define _simd_u16x16_insert_x1(X,I,Y) _simd_u16x16_insert_x1_(X,I,Y)
#define _simd_u16x16__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_insert_x1_instruction_set>()
#else
#define _simd_u16x16_insert_x1(X,I,Y) _simd_u16x16_insert_x1_safe(X,I,Y)
#define _simd_u16x16__insert_x1_enable() true
#endif _simd_u16x16_insert_x1_

#define _simd_u16x16_extract_x2_safe(X,I) (reinterpret_cast<const _simd_u16x16*>(&X)[I])
#ifdef _simd_u16x16_extract_x2_
#define _simd_u16x16_extract_x2(X,I) _simd_u16x16_extract_x2_(X,I)
#define _simd_u16x16__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_extract_x2_instruction_set>()
#else
#define _simd_u16x16_extract_x2(X,I) _simd_u16x16_extract_x2_safe(X,I)
#define _simd_u16x16__extract_x2_enable() true
#endif _simd_u16x16_extract_x2_

#define _simd_u16x16_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_u16x16*>(&X)[I] = Y)
#ifdef _simd_u16x16_insert_x2_
#define _simd_u16x16_insert_x2(X,I,Y) _simd_u16x16_insert_x2_(X,I,Y)
#define _simd_u16x16__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_insert_x2_instruction_set>()
#else
#define _simd_u16x16_insert_x2(X,I,Y) _simd_u16x16_insert_x2_safe(X,I,Y)
#define _simd_u16x16__insert_x2_enable() true
#endif _simd_u16x16_insert_x2_

#define _simd_u16x16_extract_x4_safe(X,I) (reinterpret_cast<const _simd_u16x16*>(&X)[I])
#ifdef _simd_u16x16_extract_x4_
#define _simd_u16x16_extract_x4(X,I) _simd_u16x16_extract_x4_(X,I)
#define _simd_u16x16__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_extract_x4_instruction_set>()
#else
#define _simd_u16x16_extract_x4(X,I) _simd_u16x16_extract_x4_safe(X,I)
#define _simd_u16x16__extract_x4_enable() true
#endif _simd_u16x16_extract_x4_

#define _simd_u16x16_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_u16x16*>(&X)[I] = Y)
#ifdef _simd_u16x16_insert_x4_
#define _simd_u16x16_insert_x4(X,I,Y) _simd_u16x16_insert_x4_(X,I,Y)
#define _simd_u16x16__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_insert_x4_instruction_set>()
#else
#define _simd_u16x16_insert_x4(X,I,Y) _simd_u16x16_insert_x4_safe(X,I,Y)
#define _simd_u16x16__insert_x4_enable() true
#endif _simd_u16x16_insert_x4_

#define _simd_u16x16_extract_x8_safe(X,I) (reinterpret_cast<const _simd_u16x16*>(&X)[I])
#ifdef _simd_u16x16_extract_x8_
#define _simd_u16x16_extract_x8(X,I) _simd_u16x16_extract_x8_(X,I)
#define _simd_u16x16__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_extract_x8_instruction_set>()
#else
#define _simd_u16x16_extract_x8(X,I) _simd_u16x16_extract_x8_safe(X,I)
#define _simd_u16x16__extract_x8_enable() true
#endif _simd_u16x16_extract_x8_

#define _simd_u16x16_insert_x8_safe(X,I,Y) (reinterpret_cast<_simd_u16x16*>(&X)[I] = Y)
#ifdef _simd_u16x16_insert_x8_
#define _simd_u16x16_insert_x8(X,I,Y) _simd_u16x16_insert_x8_(X,I,Y)
#define _simd_u16x16__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_insert_x8_instruction_set>()
#else
#define _simd_u16x16_insert_x8(X,I,Y) _simd_u16x16_insert_x8_safe(X,I,Y)
#define _simd_u16x16__insert_x8_enable() true
#endif _simd_u16x16_insert_x8_

#define _simd_u16x16_extract_x32_safe(X,I) _simd_u16x16_insert_x16_safe(_simd_u16x16_fill_undefined_safe(),0,X)
#ifdef _simd_u16x16_extract_x32_
#define _simd_u16x16_extract_x32(X,I) _simd_u16x16_extract_x32_(X,I)
#define _simd_u16x16__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_extract_x32_instruction_set>()
#else
#define _simd_u16x16_extract_x32(X,I) _simd_u16x16_extract_x32_safe(X,I)
#define _simd_u16x16__extract_x32_enable() true
#endif _simd_u16x16_extract_x32_

#define _simd_u16x16_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u16x1) * 32)
#ifdef _simd_u16x16_insert_x32_
#define _simd_u16x16_insert_x32(X,I,Y) _simd_u16x16_insert_x32_(X,I,Y)
#define _simd_u16x16__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_insert_x32_instruction_set>()
#else
#define _simd_u16x16_insert_x32(X,I,Y) _simd_u16x16_insert_x32_safe(X,I,Y)
#define _simd_u16x16__insert_x32_enable() true
#endif _simd_u16x16_insert_x32_

#define _simd_u16x16_extract_x64_safe(X,I) _simd_u16x16_insert_x16_safe(_simd_u16x16_fill_undefined_safe(),0,X)
#ifdef _simd_u16x16_extract_x64_
#define _simd_u16x16_extract_x64(X,I) _simd_u16x16_extract_x64_(X,I)
#define _simd_u16x16__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_extract_x64_instruction_set>()
#else
#define _simd_u16x16_extract_x64(X,I) _simd_u16x16_extract_x64_safe(X,I)
#define _simd_u16x16__extract_x64_enable() true
#endif _simd_u16x16_extract_x64_

#define _simd_u16x16_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u16x1) * 64)
#ifdef _simd_u16x16_insert_x64_
#define _simd_u16x16_insert_x64(X,I,Y) _simd_u16x16_insert_x64_(X,I,Y)
#define _simd_u16x16__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_insert_x64_instruction_set>()
#else
#define _simd_u16x16_insert_x64(X,I,Y) _simd_u16x16_insert_x64_safe(X,I,Y)
#define _simd_u16x16__insert_x64_enable() true
#endif _simd_u16x16_insert_x64_

#define _simd_u16x16_extract_safe(X,I) _simd_u16x16_extract_x1_safe(X,I)
#define _simd_u16x16_extract(X,I) _simd_u16x16_extract_x1(X,I)
#define _simd_u16x16_extract_enable() _simd_u16x16_extract_x1_enable()

#define _simd_u16x16_insert_safe(X,I,Y) _simd_u16x16_insert_x1_safe(X,I,Y)
#define _simd_u16x16_insert(X,I,Y) _simd_u16x16_insert_x1(X,I,Y)
#define _simd_u16x16_insert_enable() _simd_u16x16_insert_x1_enable()

//#ifndef _simd_u16x16_splitlo
//	#define _simd_u16x16_splitlo(X) _simd_u16x8_extract_x8(X,0)
//	#define _simd_u16x16_splitlo_enable() _simd_u16x8_extract_x8_enable()
//#endif

//#ifndef _simd_u16x16_splithi
//	#define _simd_u16x16_splithi(X) _simd_u16x8_extract_x8(X,1)
//	#define _simd_u16x16_splithi_enable() _simd_u16x8_extract_x8_enable()
//#endif

//#ifndef _simd_u16x16_combine
//	#define _simd_u16x16_combine(X,Y) _simd_u16x16_insert_x8(_simd_u16x16_insert_x8(_simd_u16x16_fill_undefined(), 0, X), 1, Y)
//	#define _simd_u16x16_combine_enable() (_simd_u16x16_insert_x8_enable() && _simd_u16x16_fill_undefined_enable())
//#endif

#define _simd_u16x32_extract_x1_safe(X,I) (reinterpret_cast<const _simd_u16x32*>(&X)[I])
#ifdef _simd_u16x32_extract_x1_
#define _simd_u16x32_extract_x1(X,I) _simd_u16x32_extract_x1_(X,I)
#define _simd_u16x32__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_extract_x1_instruction_set>()
#else
#define _simd_u16x32_extract_x1(X,I) _simd_u16x32_extract_x1_safe(X,I)
#define _simd_u16x32__extract_x1_enable() true
#endif _simd_u16x32_extract_x1_

#define _simd_u16x32_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_u16x32*>(&X)[I] = Y)
#ifdef _simd_u16x32_insert_x1_
#define _simd_u16x32_insert_x1(X,I,Y) _simd_u16x32_insert_x1_(X,I,Y)
#define _simd_u16x32__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_insert_x1_instruction_set>()
#else
#define _simd_u16x32_insert_x1(X,I,Y) _simd_u16x32_insert_x1_safe(X,I,Y)
#define _simd_u16x32__insert_x1_enable() true
#endif _simd_u16x32_insert_x1_

#define _simd_u16x32_extract_x2_safe(X,I) (reinterpret_cast<const _simd_u16x32*>(&X)[I])
#ifdef _simd_u16x32_extract_x2_
#define _simd_u16x32_extract_x2(X,I) _simd_u16x32_extract_x2_(X,I)
#define _simd_u16x32__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_extract_x2_instruction_set>()
#else
#define _simd_u16x32_extract_x2(X,I) _simd_u16x32_extract_x2_safe(X,I)
#define _simd_u16x32__extract_x2_enable() true
#endif _simd_u16x32_extract_x2_

#define _simd_u16x32_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_u16x32*>(&X)[I] = Y)
#ifdef _simd_u16x32_insert_x2_
#define _simd_u16x32_insert_x2(X,I,Y) _simd_u16x32_insert_x2_(X,I,Y)
#define _simd_u16x32__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_insert_x2_instruction_set>()
#else
#define _simd_u16x32_insert_x2(X,I,Y) _simd_u16x32_insert_x2_safe(X,I,Y)
#define _simd_u16x32__insert_x2_enable() true
#endif _simd_u16x32_insert_x2_

#define _simd_u16x32_extract_x4_safe(X,I) (reinterpret_cast<const _simd_u16x32*>(&X)[I])
#ifdef _simd_u16x32_extract_x4_
#define _simd_u16x32_extract_x4(X,I) _simd_u16x32_extract_x4_(X,I)
#define _simd_u16x32__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_extract_x4_instruction_set>()
#else
#define _simd_u16x32_extract_x4(X,I) _simd_u16x32_extract_x4_safe(X,I)
#define _simd_u16x32__extract_x4_enable() true
#endif _simd_u16x32_extract_x4_

#define _simd_u16x32_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_u16x32*>(&X)[I] = Y)
#ifdef _simd_u16x32_insert_x4_
#define _simd_u16x32_insert_x4(X,I,Y) _simd_u16x32_insert_x4_(X,I,Y)
#define _simd_u16x32__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_insert_x4_instruction_set>()
#else
#define _simd_u16x32_insert_x4(X,I,Y) _simd_u16x32_insert_x4_safe(X,I,Y)
#define _simd_u16x32__insert_x4_enable() true
#endif _simd_u16x32_insert_x4_

#define _simd_u16x32_extract_x8_safe(X,I) (reinterpret_cast<const _simd_u16x32*>(&X)[I])
#ifdef _simd_u16x32_extract_x8_
#define _simd_u16x32_extract_x8(X,I) _simd_u16x32_extract_x8_(X,I)
#define _simd_u16x32__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_extract_x8_instruction_set>()
#else
#define _simd_u16x32_extract_x8(X,I) _simd_u16x32_extract_x8_safe(X,I)
#define _simd_u16x32__extract_x8_enable() true
#endif _simd_u16x32_extract_x8_

#define _simd_u16x32_insert_x8_safe(X,I,Y) (reinterpret_cast<_simd_u16x32*>(&X)[I] = Y)
#ifdef _simd_u16x32_insert_x8_
#define _simd_u16x32_insert_x8(X,I,Y) _simd_u16x32_insert_x8_(X,I,Y)
#define _simd_u16x32__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_insert_x8_instruction_set>()
#else
#define _simd_u16x32_insert_x8(X,I,Y) _simd_u16x32_insert_x8_safe(X,I,Y)
#define _simd_u16x32__insert_x8_enable() true
#endif _simd_u16x32_insert_x8_

#define _simd_u16x32_extract_x16_safe(X,I) (reinterpret_cast<const _simd_u16x32*>(&X)[I])
#ifdef _simd_u16x32_extract_x16_
#define _simd_u16x32_extract_x16(X,I) _simd_u16x32_extract_x16_(X,I)
#define _simd_u16x32__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_extract_x16_instruction_set>()
#else
#define _simd_u16x32_extract_x16(X,I) _simd_u16x32_extract_x16_safe(X,I)
#define _simd_u16x32__extract_x16_enable() true
#endif _simd_u16x32_extract_x16_

#define _simd_u16x32_insert_x16_safe(X,I,Y) (reinterpret_cast<_simd_u16x32*>(&X)[I] = Y)
#ifdef _simd_u16x32_insert_x16_
#define _simd_u16x32_insert_x16(X,I,Y) _simd_u16x32_insert_x16_(X,I,Y)
#define _simd_u16x32__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_insert_x16_instruction_set>()
#else
#define _simd_u16x32_insert_x16(X,I,Y) _simd_u16x32_insert_x16_safe(X,I,Y)
#define _simd_u16x32__insert_x16_enable() true
#endif _simd_u16x32_insert_x16_

#define _simd_u16x32_extract_x64_safe(X,I) _simd_u16x32_insert_x32_safe(_simd_u16x32_fill_undefined_safe(),0,X)
#ifdef _simd_u16x32_extract_x64_
#define _simd_u16x32_extract_x64(X,I) _simd_u16x32_extract_x64_(X,I)
#define _simd_u16x32__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_extract_x64_instruction_set>()
#else
#define _simd_u16x32_extract_x64(X,I) _simd_u16x32_extract_x64_safe(X,I)
#define _simd_u16x32__extract_x64_enable() true
#endif _simd_u16x32_extract_x64_

#define _simd_u16x32_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u16x1) * 64)
#ifdef _simd_u16x32_insert_x64_
#define _simd_u16x32_insert_x64(X,I,Y) _simd_u16x32_insert_x64_(X,I,Y)
#define _simd_u16x32__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_insert_x64_instruction_set>()
#else
#define _simd_u16x32_insert_x64(X,I,Y) _simd_u16x32_insert_x64_safe(X,I,Y)
#define _simd_u16x32__insert_x64_enable() true
#endif _simd_u16x32_insert_x64_

#define _simd_u16x32_extract_safe(X,I) _simd_u16x32_extract_x1_safe(X,I)
#define _simd_u16x32_extract(X,I) _simd_u16x32_extract_x1(X,I)
#define _simd_u16x32_extract_enable() _simd_u16x32_extract_x1_enable()

#define _simd_u16x32_insert_safe(X,I,Y) _simd_u16x32_insert_x1_safe(X,I,Y)
#define _simd_u16x32_insert(X,I,Y) _simd_u16x32_insert_x1(X,I,Y)
#define _simd_u16x32_insert_enable() _simd_u16x32_insert_x1_enable()

//#ifndef _simd_u16x32_splitlo
//	#define _simd_u16x32_splitlo(X) _simd_u16x16_extract_x16(X,0)
//	#define _simd_u16x32_splitlo_enable() _simd_u16x16_extract_x16_enable()
//#endif

//#ifndef _simd_u16x32_splithi
//	#define _simd_u16x32_splithi(X) _simd_u16x16_extract_x16(X,1)
//	#define _simd_u16x32_splithi_enable() _simd_u16x16_extract_x16_enable()
//#endif

//#ifndef _simd_u16x32_combine
//	#define _simd_u16x32_combine(X,Y) _simd_u16x32_insert_x16(_simd_u16x32_insert_x16(_simd_u16x32_fill_undefined(), 0, X), 1, Y)
//	#define _simd_u16x32_combine_enable() (_simd_u16x32_insert_x16_enable() && _simd_u16x32_fill_undefined_enable())
//#endif

#define _simd_u16x64_extract_x1_safe(X,I) (reinterpret_cast<const _simd_u16x64*>(&X)[I])
#ifdef _simd_u16x64_extract_x1_
#define _simd_u16x64_extract_x1(X,I) _simd_u16x64_extract_x1_(X,I)
#define _simd_u16x64__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_extract_x1_instruction_set>()
#else
#define _simd_u16x64_extract_x1(X,I) _simd_u16x64_extract_x1_safe(X,I)
#define _simd_u16x64__extract_x1_enable() true
#endif _simd_u16x64_extract_x1_

#define _simd_u16x64_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_u16x64*>(&X)[I] = Y)
#ifdef _simd_u16x64_insert_x1_
#define _simd_u16x64_insert_x1(X,I,Y) _simd_u16x64_insert_x1_(X,I,Y)
#define _simd_u16x64__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_insert_x1_instruction_set>()
#else
#define _simd_u16x64_insert_x1(X,I,Y) _simd_u16x64_insert_x1_safe(X,I,Y)
#define _simd_u16x64__insert_x1_enable() true
#endif _simd_u16x64_insert_x1_

#define _simd_u16x64_extract_x2_safe(X,I) (reinterpret_cast<const _simd_u16x64*>(&X)[I])
#ifdef _simd_u16x64_extract_x2_
#define _simd_u16x64_extract_x2(X,I) _simd_u16x64_extract_x2_(X,I)
#define _simd_u16x64__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_extract_x2_instruction_set>()
#else
#define _simd_u16x64_extract_x2(X,I) _simd_u16x64_extract_x2_safe(X,I)
#define _simd_u16x64__extract_x2_enable() true
#endif _simd_u16x64_extract_x2_

#define _simd_u16x64_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_u16x64*>(&X)[I] = Y)
#ifdef _simd_u16x64_insert_x2_
#define _simd_u16x64_insert_x2(X,I,Y) _simd_u16x64_insert_x2_(X,I,Y)
#define _simd_u16x64__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_insert_x2_instruction_set>()
#else
#define _simd_u16x64_insert_x2(X,I,Y) _simd_u16x64_insert_x2_safe(X,I,Y)
#define _simd_u16x64__insert_x2_enable() true
#endif _simd_u16x64_insert_x2_

#define _simd_u16x64_extract_x4_safe(X,I) (reinterpret_cast<const _simd_u16x64*>(&X)[I])
#ifdef _simd_u16x64_extract_x4_
#define _simd_u16x64_extract_x4(X,I) _simd_u16x64_extract_x4_(X,I)
#define _simd_u16x64__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_extract_x4_instruction_set>()
#else
#define _simd_u16x64_extract_x4(X,I) _simd_u16x64_extract_x4_safe(X,I)
#define _simd_u16x64__extract_x4_enable() true
#endif _simd_u16x64_extract_x4_

#define _simd_u16x64_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_u16x64*>(&X)[I] = Y)
#ifdef _simd_u16x64_insert_x4_
#define _simd_u16x64_insert_x4(X,I,Y) _simd_u16x64_insert_x4_(X,I,Y)
#define _simd_u16x64__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_insert_x4_instruction_set>()
#else
#define _simd_u16x64_insert_x4(X,I,Y) _simd_u16x64_insert_x4_safe(X,I,Y)
#define _simd_u16x64__insert_x4_enable() true
#endif _simd_u16x64_insert_x4_

#define _simd_u16x64_extract_x8_safe(X,I) (reinterpret_cast<const _simd_u16x64*>(&X)[I])
#ifdef _simd_u16x64_extract_x8_
#define _simd_u16x64_extract_x8(X,I) _simd_u16x64_extract_x8_(X,I)
#define _simd_u16x64__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_extract_x8_instruction_set>()
#else
#define _simd_u16x64_extract_x8(X,I) _simd_u16x64_extract_x8_safe(X,I)
#define _simd_u16x64__extract_x8_enable() true
#endif _simd_u16x64_extract_x8_

#define _simd_u16x64_insert_x8_safe(X,I,Y) (reinterpret_cast<_simd_u16x64*>(&X)[I] = Y)
#ifdef _simd_u16x64_insert_x8_
#define _simd_u16x64_insert_x8(X,I,Y) _simd_u16x64_insert_x8_(X,I,Y)
#define _simd_u16x64__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_insert_x8_instruction_set>()
#else
#define _simd_u16x64_insert_x8(X,I,Y) _simd_u16x64_insert_x8_safe(X,I,Y)
#define _simd_u16x64__insert_x8_enable() true
#endif _simd_u16x64_insert_x8_

#define _simd_u16x64_extract_x16_safe(X,I) (reinterpret_cast<const _simd_u16x64*>(&X)[I])
#ifdef _simd_u16x64_extract_x16_
#define _simd_u16x64_extract_x16(X,I) _simd_u16x64_extract_x16_(X,I)
#define _simd_u16x64__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_extract_x16_instruction_set>()
#else
#define _simd_u16x64_extract_x16(X,I) _simd_u16x64_extract_x16_safe(X,I)
#define _simd_u16x64__extract_x16_enable() true
#endif _simd_u16x64_extract_x16_

#define _simd_u16x64_insert_x16_safe(X,I,Y) (reinterpret_cast<_simd_u16x64*>(&X)[I] = Y)
#ifdef _simd_u16x64_insert_x16_
#define _simd_u16x64_insert_x16(X,I,Y) _simd_u16x64_insert_x16_(X,I,Y)
#define _simd_u16x64__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_insert_x16_instruction_set>()
#else
#define _simd_u16x64_insert_x16(X,I,Y) _simd_u16x64_insert_x16_safe(X,I,Y)
#define _simd_u16x64__insert_x16_enable() true
#endif _simd_u16x64_insert_x16_

#define _simd_u16x64_extract_x32_safe(X,I) (reinterpret_cast<const _simd_u16x64*>(&X)[I])
#ifdef _simd_u16x64_extract_x32_
#define _simd_u16x64_extract_x32(X,I) _simd_u16x64_extract_x32_(X,I)
#define _simd_u16x64__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_extract_x32_instruction_set>()
#else
#define _simd_u16x64_extract_x32(X,I) _simd_u16x64_extract_x32_safe(X,I)
#define _simd_u16x64__extract_x32_enable() true
#endif _simd_u16x64_extract_x32_

#define _simd_u16x64_insert_x32_safe(X,I,Y) (reinterpret_cast<_simd_u16x64*>(&X)[I] = Y)
#ifdef _simd_u16x64_insert_x32_
#define _simd_u16x64_insert_x32(X,I,Y) _simd_u16x64_insert_x32_(X,I,Y)
#define _simd_u16x64__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_insert_x32_instruction_set>()
#else
#define _simd_u16x64_insert_x32(X,I,Y) _simd_u16x64_insert_x32_safe(X,I,Y)
#define _simd_u16x64__insert_x32_enable() true
#endif _simd_u16x64_insert_x32_

#define _simd_u16x64_extract_safe(X,I) _simd_u16x64_extract_x1_safe(X,I)
#define _simd_u16x64_extract(X,I) _simd_u16x64_extract_x1(X,I)
#define _simd_u16x64_extract_enable() _simd_u16x64_extract_x1_enable()

#define _simd_u16x64_insert_safe(X,I,Y) _simd_u16x64_insert_x1_safe(X,I,Y)
#define _simd_u16x64_insert(X,I,Y) _simd_u16x64_insert_x1(X,I,Y)
#define _simd_u16x64_insert_enable() _simd_u16x64_insert_x1_enable()

//#ifndef _simd_u16x64_splitlo
//	#define _simd_u16x64_splitlo(X) _simd_u16x32_extract_x32(X,0)
//	#define _simd_u16x64_splitlo_enable() _simd_u16x32_extract_x32_enable()
//#endif

//#ifndef _simd_u16x64_splithi
//	#define _simd_u16x64_splithi(X) _simd_u16x32_extract_x32(X,1)
//	#define _simd_u16x64_splithi_enable() _simd_u16x32_extract_x32_enable()
//#endif

//#ifndef _simd_u16x64_combine
//	#define _simd_u16x64_combine(X,Y) _simd_u16x64_insert_x32(_simd_u16x64_insert_x32(_simd_u16x64_fill_undefined(), 0, X), 1, Y)
//	#define _simd_u16x64_combine_enable() (_simd_u16x64_insert_x32_enable() && _simd_u16x64_fill_undefined_enable())
//#endif

// -- s8 --

#define _simd_s8x2_extract_x1_safe(X,I) (reinterpret_cast<const _simd_s8x2*>(&X)[I])
#ifdef _simd_s8x2_extract_x1_
#define _simd_s8x2_extract_x1(X,I) _simd_s8x2_extract_x1_(X,I)
#define _simd_s8x2__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_extract_x1_instruction_set>()
#else
#define _simd_s8x2_extract_x1(X,I) _simd_s8x2_extract_x1_safe(X,I)
#define _simd_s8x2__extract_x1_enable() true
#endif _simd_s8x2_extract_x1_

#define _simd_s8x2_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_s8x2*>(&X)[I] = Y)
#ifdef _simd_s8x2_insert_x1_
#define _simd_s8x2_insert_x1(X,I,Y) _simd_s8x2_insert_x1_(X,I,Y)
#define _simd_s8x2__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_insert_x1_instruction_set>()
#else
#define _simd_s8x2_insert_x1(X,I,Y) _simd_s8x2_insert_x1_safe(X,I,Y)
#define _simd_s8x2__insert_x1_enable() true
#endif _simd_s8x2_insert_x1_

#define _simd_s8x2_extract_x4_safe(X,I) _simd_s8x2_insert_x2_safe(_simd_s8x2_fill_undefined_safe(),0,X)
#ifdef _simd_s8x2_extract_x4_
#define _simd_s8x2_extract_x4(X,I) _simd_s8x2_extract_x4_(X,I)
#define _simd_s8x2__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_extract_x4_instruction_set>()
#else
#define _simd_s8x2_extract_x4(X,I) _simd_s8x2_extract_x4_safe(X,I)
#define _simd_s8x2__extract_x4_enable() true
#endif _simd_s8x2_extract_x4_

#define _simd_s8x2_insert_x4_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s8x1) * 4)
#ifdef _simd_s8x2_insert_x4_
#define _simd_s8x2_insert_x4(X,I,Y) _simd_s8x2_insert_x4_(X,I,Y)
#define _simd_s8x2__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_insert_x4_instruction_set>()
#else
#define _simd_s8x2_insert_x4(X,I,Y) _simd_s8x2_insert_x4_safe(X,I,Y)
#define _simd_s8x2__insert_x4_enable() true
#endif _simd_s8x2_insert_x4_

#define _simd_s8x2_extract_x8_safe(X,I) _simd_s8x2_insert_x2_safe(_simd_s8x2_fill_undefined_safe(),0,X)
#ifdef _simd_s8x2_extract_x8_
#define _simd_s8x2_extract_x8(X,I) _simd_s8x2_extract_x8_(X,I)
#define _simd_s8x2__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_extract_x8_instruction_set>()
#else
#define _simd_s8x2_extract_x8(X,I) _simd_s8x2_extract_x8_safe(X,I)
#define _simd_s8x2__extract_x8_enable() true
#endif _simd_s8x2_extract_x8_

#define _simd_s8x2_insert_x8_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s8x1) * 8)
#ifdef _simd_s8x2_insert_x8_
#define _simd_s8x2_insert_x8(X,I,Y) _simd_s8x2_insert_x8_(X,I,Y)
#define _simd_s8x2__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_insert_x8_instruction_set>()
#else
#define _simd_s8x2_insert_x8(X,I,Y) _simd_s8x2_insert_x8_safe(X,I,Y)
#define _simd_s8x2__insert_x8_enable() true
#endif _simd_s8x2_insert_x8_

#define _simd_s8x2_extract_x16_safe(X,I) _simd_s8x2_insert_x2_safe(_simd_s8x2_fill_undefined_safe(),0,X)
#ifdef _simd_s8x2_extract_x16_
#define _simd_s8x2_extract_x16(X,I) _simd_s8x2_extract_x16_(X,I)
#define _simd_s8x2__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_extract_x16_instruction_set>()
#else
#define _simd_s8x2_extract_x16(X,I) _simd_s8x2_extract_x16_safe(X,I)
#define _simd_s8x2__extract_x16_enable() true
#endif _simd_s8x2_extract_x16_

#define _simd_s8x2_insert_x16_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s8x1) * 16)
#ifdef _simd_s8x2_insert_x16_
#define _simd_s8x2_insert_x16(X,I,Y) _simd_s8x2_insert_x16_(X,I,Y)
#define _simd_s8x2__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_insert_x16_instruction_set>()
#else
#define _simd_s8x2_insert_x16(X,I,Y) _simd_s8x2_insert_x16_safe(X,I,Y)
#define _simd_s8x2__insert_x16_enable() true
#endif _simd_s8x2_insert_x16_

#define _simd_s8x2_extract_x32_safe(X,I) _simd_s8x2_insert_x2_safe(_simd_s8x2_fill_undefined_safe(),0,X)
#ifdef _simd_s8x2_extract_x32_
#define _simd_s8x2_extract_x32(X,I) _simd_s8x2_extract_x32_(X,I)
#define _simd_s8x2__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_extract_x32_instruction_set>()
#else
#define _simd_s8x2_extract_x32(X,I) _simd_s8x2_extract_x32_safe(X,I)
#define _simd_s8x2__extract_x32_enable() true
#endif _simd_s8x2_extract_x32_

#define _simd_s8x2_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s8x1) * 32)
#ifdef _simd_s8x2_insert_x32_
#define _simd_s8x2_insert_x32(X,I,Y) _simd_s8x2_insert_x32_(X,I,Y)
#define _simd_s8x2__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_insert_x32_instruction_set>()
#else
#define _simd_s8x2_insert_x32(X,I,Y) _simd_s8x2_insert_x32_safe(X,I,Y)
#define _simd_s8x2__insert_x32_enable() true
#endif _simd_s8x2_insert_x32_

#define _simd_s8x2_extract_x64_safe(X,I) _simd_s8x2_insert_x2_safe(_simd_s8x2_fill_undefined_safe(),0,X)
#ifdef _simd_s8x2_extract_x64_
#define _simd_s8x2_extract_x64(X,I) _simd_s8x2_extract_x64_(X,I)
#define _simd_s8x2__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_extract_x64_instruction_set>()
#else
#define _simd_s8x2_extract_x64(X,I) _simd_s8x2_extract_x64_safe(X,I)
#define _simd_s8x2__extract_x64_enable() true
#endif _simd_s8x2_extract_x64_

#define _simd_s8x2_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s8x1) * 64)
#ifdef _simd_s8x2_insert_x64_
#define _simd_s8x2_insert_x64(X,I,Y) _simd_s8x2_insert_x64_(X,I,Y)
#define _simd_s8x2__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_insert_x64_instruction_set>()
#else
#define _simd_s8x2_insert_x64(X,I,Y) _simd_s8x2_insert_x64_safe(X,I,Y)
#define _simd_s8x2__insert_x64_enable() true
#endif _simd_s8x2_insert_x64_

#define _simd_s8x2_extract_safe(X,I) _simd_s8x2_extract_x1_safe(X,I)
#define _simd_s8x2_extract(X,I) _simd_s8x2_extract_x1(X,I)
#define _simd_s8x2_extract_enable() _simd_s8x2_extract_x1_enable()

#define _simd_s8x2_insert_safe(X,I,Y) _simd_s8x2_insert_x1_safe(X,I,Y)
#define _simd_s8x2_insert(X,I,Y) _simd_s8x2_insert_x1(X,I,Y)
#define _simd_s8x2_insert_enable() _simd_s8x2_insert_x1_enable()

//#ifndef _simd_s8x2_splitlo
//	#define _simd_s8x2_splitlo(X) _simd_s8x1_extract_x1(X,0)
//	#define _simd_s8x2_splitlo_enable() _simd_s8x1_extract_x1_enable()
//#endif

//#ifndef _simd_s8x2_splithi
//	#define _simd_s8x2_splithi(X) _simd_s8x1_extract_x1(X,1)
//	#define _simd_s8x2_splithi_enable() _simd_s8x1_extract_x1_enable()
//#endif

//#ifndef _simd_s8x2_combine
//	#define _simd_s8x2_combine(X,Y) _simd_s8x2_insert_x1(_simd_s8x2_insert_x1(_simd_s8x2_fill_undefined(), 0, X), 1, Y)
//	#define _simd_s8x2_combine_enable() (_simd_s8x2_insert_x1_enable() && _simd_s8x2_fill_undefined_enable())
//#endif

#define _simd_s8x4_extract_x1_safe(X,I) (reinterpret_cast<const _simd_s8x4*>(&X)[I])
#ifdef _simd_s8x4_extract_x1_
#define _simd_s8x4_extract_x1(X,I) _simd_s8x4_extract_x1_(X,I)
#define _simd_s8x4__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_extract_x1_instruction_set>()
#else
#define _simd_s8x4_extract_x1(X,I) _simd_s8x4_extract_x1_safe(X,I)
#define _simd_s8x4__extract_x1_enable() true
#endif _simd_s8x4_extract_x1_

#define _simd_s8x4_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_s8x4*>(&X)[I] = Y)
#ifdef _simd_s8x4_insert_x1_
#define _simd_s8x4_insert_x1(X,I,Y) _simd_s8x4_insert_x1_(X,I,Y)
#define _simd_s8x4__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_insert_x1_instruction_set>()
#else
#define _simd_s8x4_insert_x1(X,I,Y) _simd_s8x4_insert_x1_safe(X,I,Y)
#define _simd_s8x4__insert_x1_enable() true
#endif _simd_s8x4_insert_x1_

#define _simd_s8x4_extract_x2_safe(X,I) (reinterpret_cast<const _simd_s8x4*>(&X)[I])
#ifdef _simd_s8x4_extract_x2_
#define _simd_s8x4_extract_x2(X,I) _simd_s8x4_extract_x2_(X,I)
#define _simd_s8x4__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_extract_x2_instruction_set>()
#else
#define _simd_s8x4_extract_x2(X,I) _simd_s8x4_extract_x2_safe(X,I)
#define _simd_s8x4__extract_x2_enable() true
#endif _simd_s8x4_extract_x2_

#define _simd_s8x4_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_s8x4*>(&X)[I] = Y)
#ifdef _simd_s8x4_insert_x2_
#define _simd_s8x4_insert_x2(X,I,Y) _simd_s8x4_insert_x2_(X,I,Y)
#define _simd_s8x4__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_insert_x2_instruction_set>()
#else
#define _simd_s8x4_insert_x2(X,I,Y) _simd_s8x4_insert_x2_safe(X,I,Y)
#define _simd_s8x4__insert_x2_enable() true
#endif _simd_s8x4_insert_x2_

#define _simd_s8x4_extract_x8_safe(X,I) _simd_s8x4_insert_x4_safe(_simd_s8x4_fill_undefined_safe(),0,X)
#ifdef _simd_s8x4_extract_x8_
#define _simd_s8x4_extract_x8(X,I) _simd_s8x4_extract_x8_(X,I)
#define _simd_s8x4__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_extract_x8_instruction_set>()
#else
#define _simd_s8x4_extract_x8(X,I) _simd_s8x4_extract_x8_safe(X,I)
#define _simd_s8x4__extract_x8_enable() true
#endif _simd_s8x4_extract_x8_

#define _simd_s8x4_insert_x8_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s8x1) * 8)
#ifdef _simd_s8x4_insert_x8_
#define _simd_s8x4_insert_x8(X,I,Y) _simd_s8x4_insert_x8_(X,I,Y)
#define _simd_s8x4__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_insert_x8_instruction_set>()
#else
#define _simd_s8x4_insert_x8(X,I,Y) _simd_s8x4_insert_x8_safe(X,I,Y)
#define _simd_s8x4__insert_x8_enable() true
#endif _simd_s8x4_insert_x8_

#define _simd_s8x4_extract_x16_safe(X,I) _simd_s8x4_insert_x4_safe(_simd_s8x4_fill_undefined_safe(),0,X)
#ifdef _simd_s8x4_extract_x16_
#define _simd_s8x4_extract_x16(X,I) _simd_s8x4_extract_x16_(X,I)
#define _simd_s8x4__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_extract_x16_instruction_set>()
#else
#define _simd_s8x4_extract_x16(X,I) _simd_s8x4_extract_x16_safe(X,I)
#define _simd_s8x4__extract_x16_enable() true
#endif _simd_s8x4_extract_x16_

#define _simd_s8x4_insert_x16_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s8x1) * 16)
#ifdef _simd_s8x4_insert_x16_
#define _simd_s8x4_insert_x16(X,I,Y) _simd_s8x4_insert_x16_(X,I,Y)
#define _simd_s8x4__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_insert_x16_instruction_set>()
#else
#define _simd_s8x4_insert_x16(X,I,Y) _simd_s8x4_insert_x16_safe(X,I,Y)
#define _simd_s8x4__insert_x16_enable() true
#endif _simd_s8x4_insert_x16_

#define _simd_s8x4_extract_x32_safe(X,I) _simd_s8x4_insert_x4_safe(_simd_s8x4_fill_undefined_safe(),0,X)
#ifdef _simd_s8x4_extract_x32_
#define _simd_s8x4_extract_x32(X,I) _simd_s8x4_extract_x32_(X,I)
#define _simd_s8x4__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_extract_x32_instruction_set>()
#else
#define _simd_s8x4_extract_x32(X,I) _simd_s8x4_extract_x32_safe(X,I)
#define _simd_s8x4__extract_x32_enable() true
#endif _simd_s8x4_extract_x32_

#define _simd_s8x4_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s8x1) * 32)
#ifdef _simd_s8x4_insert_x32_
#define _simd_s8x4_insert_x32(X,I,Y) _simd_s8x4_insert_x32_(X,I,Y)
#define _simd_s8x4__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_insert_x32_instruction_set>()
#else
#define _simd_s8x4_insert_x32(X,I,Y) _simd_s8x4_insert_x32_safe(X,I,Y)
#define _simd_s8x4__insert_x32_enable() true
#endif _simd_s8x4_insert_x32_

#define _simd_s8x4_extract_x64_safe(X,I) _simd_s8x4_insert_x4_safe(_simd_s8x4_fill_undefined_safe(),0,X)
#ifdef _simd_s8x4_extract_x64_
#define _simd_s8x4_extract_x64(X,I) _simd_s8x4_extract_x64_(X,I)
#define _simd_s8x4__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_extract_x64_instruction_set>()
#else
#define _simd_s8x4_extract_x64(X,I) _simd_s8x4_extract_x64_safe(X,I)
#define _simd_s8x4__extract_x64_enable() true
#endif _simd_s8x4_extract_x64_

#define _simd_s8x4_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s8x1) * 64)
#ifdef _simd_s8x4_insert_x64_
#define _simd_s8x4_insert_x64(X,I,Y) _simd_s8x4_insert_x64_(X,I,Y)
#define _simd_s8x4__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_insert_x64_instruction_set>()
#else
#define _simd_s8x4_insert_x64(X,I,Y) _simd_s8x4_insert_x64_safe(X,I,Y)
#define _simd_s8x4__insert_x64_enable() true
#endif _simd_s8x4_insert_x64_

#define _simd_s8x4_extract_safe(X,I) _simd_s8x4_extract_x1_safe(X,I)
#define _simd_s8x4_extract(X,I) _simd_s8x4_extract_x1(X,I)
#define _simd_s8x4_extract_enable() _simd_s8x4_extract_x1_enable()

#define _simd_s8x4_insert_safe(X,I,Y) _simd_s8x4_insert_x1_safe(X,I,Y)
#define _simd_s8x4_insert(X,I,Y) _simd_s8x4_insert_x1(X,I,Y)
#define _simd_s8x4_insert_enable() _simd_s8x4_insert_x1_enable()

//#ifndef _simd_s8x4_splitlo
//	#define _simd_s8x4_splitlo(X) _simd_s8x2_extract_x2(X,0)
//	#define _simd_s8x4_splitlo_enable() _simd_s8x2_extract_x2_enable()
//#endif

//#ifndef _simd_s8x4_splithi
//	#define _simd_s8x4_splithi(X) _simd_s8x2_extract_x2(X,1)
//	#define _simd_s8x4_splithi_enable() _simd_s8x2_extract_x2_enable()
//#endif

//#ifndef _simd_s8x4_combine
//	#define _simd_s8x4_combine(X,Y) _simd_s8x4_insert_x2(_simd_s8x4_insert_x2(_simd_s8x4_fill_undefined(), 0, X), 1, Y)
//	#define _simd_s8x4_combine_enable() (_simd_s8x4_insert_x2_enable() && _simd_s8x4_fill_undefined_enable())
//#endif

#define _simd_s8x8_extract_x1_safe(X,I) (reinterpret_cast<const _simd_s8x8*>(&X)[I])
#ifdef _simd_s8x8_extract_x1_
#define _simd_s8x8_extract_x1(X,I) _simd_s8x8_extract_x1_(X,I)
#define _simd_s8x8__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_extract_x1_instruction_set>()
#else
#define _simd_s8x8_extract_x1(X,I) _simd_s8x8_extract_x1_safe(X,I)
#define _simd_s8x8__extract_x1_enable() true
#endif _simd_s8x8_extract_x1_

#define _simd_s8x8_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_s8x8*>(&X)[I] = Y)
#ifdef _simd_s8x8_insert_x1_
#define _simd_s8x8_insert_x1(X,I,Y) _simd_s8x8_insert_x1_(X,I,Y)
#define _simd_s8x8__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_insert_x1_instruction_set>()
#else
#define _simd_s8x8_insert_x1(X,I,Y) _simd_s8x8_insert_x1_safe(X,I,Y)
#define _simd_s8x8__insert_x1_enable() true
#endif _simd_s8x8_insert_x1_

#define _simd_s8x8_extract_x2_safe(X,I) (reinterpret_cast<const _simd_s8x8*>(&X)[I])
#ifdef _simd_s8x8_extract_x2_
#define _simd_s8x8_extract_x2(X,I) _simd_s8x8_extract_x2_(X,I)
#define _simd_s8x8__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_extract_x2_instruction_set>()
#else
#define _simd_s8x8_extract_x2(X,I) _simd_s8x8_extract_x2_safe(X,I)
#define _simd_s8x8__extract_x2_enable() true
#endif _simd_s8x8_extract_x2_

#define _simd_s8x8_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_s8x8*>(&X)[I] = Y)
#ifdef _simd_s8x8_insert_x2_
#define _simd_s8x8_insert_x2(X,I,Y) _simd_s8x8_insert_x2_(X,I,Y)
#define _simd_s8x8__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_insert_x2_instruction_set>()
#else
#define _simd_s8x8_insert_x2(X,I,Y) _simd_s8x8_insert_x2_safe(X,I,Y)
#define _simd_s8x8__insert_x2_enable() true
#endif _simd_s8x8_insert_x2_

#define _simd_s8x8_extract_x4_safe(X,I) (reinterpret_cast<const _simd_s8x8*>(&X)[I])
#ifdef _simd_s8x8_extract_x4_
#define _simd_s8x8_extract_x4(X,I) _simd_s8x8_extract_x4_(X,I)
#define _simd_s8x8__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_extract_x4_instruction_set>()
#else
#define _simd_s8x8_extract_x4(X,I) _simd_s8x8_extract_x4_safe(X,I)
#define _simd_s8x8__extract_x4_enable() true
#endif _simd_s8x8_extract_x4_

#define _simd_s8x8_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_s8x8*>(&X)[I] = Y)
#ifdef _simd_s8x8_insert_x4_
#define _simd_s8x8_insert_x4(X,I,Y) _simd_s8x8_insert_x4_(X,I,Y)
#define _simd_s8x8__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_insert_x4_instruction_set>()
#else
#define _simd_s8x8_insert_x4(X,I,Y) _simd_s8x8_insert_x4_safe(X,I,Y)
#define _simd_s8x8__insert_x4_enable() true
#endif _simd_s8x8_insert_x4_

#define _simd_s8x8_extract_x16_safe(X,I) _simd_s8x8_insert_x8_safe(_simd_s8x8_fill_undefined_safe(),0,X)
#ifdef _simd_s8x8_extract_x16_
#define _simd_s8x8_extract_x16(X,I) _simd_s8x8_extract_x16_(X,I)
#define _simd_s8x8__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_extract_x16_instruction_set>()
#else
#define _simd_s8x8_extract_x16(X,I) _simd_s8x8_extract_x16_safe(X,I)
#define _simd_s8x8__extract_x16_enable() true
#endif _simd_s8x8_extract_x16_

#define _simd_s8x8_insert_x16_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s8x1) * 16)
#ifdef _simd_s8x8_insert_x16_
#define _simd_s8x8_insert_x16(X,I,Y) _simd_s8x8_insert_x16_(X,I,Y)
#define _simd_s8x8__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_insert_x16_instruction_set>()
#else
#define _simd_s8x8_insert_x16(X,I,Y) _simd_s8x8_insert_x16_safe(X,I,Y)
#define _simd_s8x8__insert_x16_enable() true
#endif _simd_s8x8_insert_x16_

#define _simd_s8x8_extract_x32_safe(X,I) _simd_s8x8_insert_x8_safe(_simd_s8x8_fill_undefined_safe(),0,X)
#ifdef _simd_s8x8_extract_x32_
#define _simd_s8x8_extract_x32(X,I) _simd_s8x8_extract_x32_(X,I)
#define _simd_s8x8__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_extract_x32_instruction_set>()
#else
#define _simd_s8x8_extract_x32(X,I) _simd_s8x8_extract_x32_safe(X,I)
#define _simd_s8x8__extract_x32_enable() true
#endif _simd_s8x8_extract_x32_

#define _simd_s8x8_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s8x1) * 32)
#ifdef _simd_s8x8_insert_x32_
#define _simd_s8x8_insert_x32(X,I,Y) _simd_s8x8_insert_x32_(X,I,Y)
#define _simd_s8x8__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_insert_x32_instruction_set>()
#else
#define _simd_s8x8_insert_x32(X,I,Y) _simd_s8x8_insert_x32_safe(X,I,Y)
#define _simd_s8x8__insert_x32_enable() true
#endif _simd_s8x8_insert_x32_

#define _simd_s8x8_extract_x64_safe(X,I) _simd_s8x8_insert_x8_safe(_simd_s8x8_fill_undefined_safe(),0,X)
#ifdef _simd_s8x8_extract_x64_
#define _simd_s8x8_extract_x64(X,I) _simd_s8x8_extract_x64_(X,I)
#define _simd_s8x8__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_extract_x64_instruction_set>()
#else
#define _simd_s8x8_extract_x64(X,I) _simd_s8x8_extract_x64_safe(X,I)
#define _simd_s8x8__extract_x64_enable() true
#endif _simd_s8x8_extract_x64_

#define _simd_s8x8_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s8x1) * 64)
#ifdef _simd_s8x8_insert_x64_
#define _simd_s8x8_insert_x64(X,I,Y) _simd_s8x8_insert_x64_(X,I,Y)
#define _simd_s8x8__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_insert_x64_instruction_set>()
#else
#define _simd_s8x8_insert_x64(X,I,Y) _simd_s8x8_insert_x64_safe(X,I,Y)
#define _simd_s8x8__insert_x64_enable() true
#endif _simd_s8x8_insert_x64_

#define _simd_s8x8_extract_safe(X,I) _simd_s8x8_extract_x1_safe(X,I)
#define _simd_s8x8_extract(X,I) _simd_s8x8_extract_x1(X,I)
#define _simd_s8x8_extract_enable() _simd_s8x8_extract_x1_enable()

#define _simd_s8x8_insert_safe(X,I,Y) _simd_s8x8_insert_x1_safe(X,I,Y)
#define _simd_s8x8_insert(X,I,Y) _simd_s8x8_insert_x1(X,I,Y)
#define _simd_s8x8_insert_enable() _simd_s8x8_insert_x1_enable()

//#ifndef _simd_s8x8_splitlo
//	#define _simd_s8x8_splitlo(X) _simd_s8x4_extract_x4(X,0)
//	#define _simd_s8x8_splitlo_enable() _simd_s8x4_extract_x4_enable()
//#endif

//#ifndef _simd_s8x8_splithi
//	#define _simd_s8x8_splithi(X) _simd_s8x4_extract_x4(X,1)
//	#define _simd_s8x8_splithi_enable() _simd_s8x4_extract_x4_enable()
//#endif

//#ifndef _simd_s8x8_combine
//	#define _simd_s8x8_combine(X,Y) _simd_s8x8_insert_x4(_simd_s8x8_insert_x4(_simd_s8x8_fill_undefined(), 0, X), 1, Y)
//	#define _simd_s8x8_combine_enable() (_simd_s8x8_insert_x4_enable() && _simd_s8x8_fill_undefined_enable())
//#endif

#define _simd_s8x16_extract_x1_safe(X,I) (reinterpret_cast<const _simd_s8x16*>(&X)[I])
#ifdef _simd_s8x16_extract_x1_
#define _simd_s8x16_extract_x1(X,I) _simd_s8x16_extract_x1_(X,I)
#define _simd_s8x16__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_extract_x1_instruction_set>()
#else
#define _simd_s8x16_extract_x1(X,I) _simd_s8x16_extract_x1_safe(X,I)
#define _simd_s8x16__extract_x1_enable() true
#endif _simd_s8x16_extract_x1_

#define _simd_s8x16_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_s8x16*>(&X)[I] = Y)
#ifdef _simd_s8x16_insert_x1_
#define _simd_s8x16_insert_x1(X,I,Y) _simd_s8x16_insert_x1_(X,I,Y)
#define _simd_s8x16__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_insert_x1_instruction_set>()
#else
#define _simd_s8x16_insert_x1(X,I,Y) _simd_s8x16_insert_x1_safe(X,I,Y)
#define _simd_s8x16__insert_x1_enable() true
#endif _simd_s8x16_insert_x1_

#define _simd_s8x16_extract_x2_safe(X,I) (reinterpret_cast<const _simd_s8x16*>(&X)[I])
#ifdef _simd_s8x16_extract_x2_
#define _simd_s8x16_extract_x2(X,I) _simd_s8x16_extract_x2_(X,I)
#define _simd_s8x16__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_extract_x2_instruction_set>()
#else
#define _simd_s8x16_extract_x2(X,I) _simd_s8x16_extract_x2_safe(X,I)
#define _simd_s8x16__extract_x2_enable() true
#endif _simd_s8x16_extract_x2_

#define _simd_s8x16_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_s8x16*>(&X)[I] = Y)
#ifdef _simd_s8x16_insert_x2_
#define _simd_s8x16_insert_x2(X,I,Y) _simd_s8x16_insert_x2_(X,I,Y)
#define _simd_s8x16__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_insert_x2_instruction_set>()
#else
#define _simd_s8x16_insert_x2(X,I,Y) _simd_s8x16_insert_x2_safe(X,I,Y)
#define _simd_s8x16__insert_x2_enable() true
#endif _simd_s8x16_insert_x2_

#define _simd_s8x16_extract_x4_safe(X,I) (reinterpret_cast<const _simd_s8x16*>(&X)[I])
#ifdef _simd_s8x16_extract_x4_
#define _simd_s8x16_extract_x4(X,I) _simd_s8x16_extract_x4_(X,I)
#define _simd_s8x16__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_extract_x4_instruction_set>()
#else
#define _simd_s8x16_extract_x4(X,I) _simd_s8x16_extract_x4_safe(X,I)
#define _simd_s8x16__extract_x4_enable() true
#endif _simd_s8x16_extract_x4_

#define _simd_s8x16_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_s8x16*>(&X)[I] = Y)
#ifdef _simd_s8x16_insert_x4_
#define _simd_s8x16_insert_x4(X,I,Y) _simd_s8x16_insert_x4_(X,I,Y)
#define _simd_s8x16__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_insert_x4_instruction_set>()
#else
#define _simd_s8x16_insert_x4(X,I,Y) _simd_s8x16_insert_x4_safe(X,I,Y)
#define _simd_s8x16__insert_x4_enable() true
#endif _simd_s8x16_insert_x4_

#define _simd_s8x16_extract_x8_safe(X,I) (reinterpret_cast<const _simd_s8x16*>(&X)[I])
#ifdef _simd_s8x16_extract_x8_
#define _simd_s8x16_extract_x8(X,I) _simd_s8x16_extract_x8_(X,I)
#define _simd_s8x16__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_extract_x8_instruction_set>()
#else
#define _simd_s8x16_extract_x8(X,I) _simd_s8x16_extract_x8_safe(X,I)
#define _simd_s8x16__extract_x8_enable() true
#endif _simd_s8x16_extract_x8_

#define _simd_s8x16_insert_x8_safe(X,I,Y) (reinterpret_cast<_simd_s8x16*>(&X)[I] = Y)
#ifdef _simd_s8x16_insert_x8_
#define _simd_s8x16_insert_x8(X,I,Y) _simd_s8x16_insert_x8_(X,I,Y)
#define _simd_s8x16__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_insert_x8_instruction_set>()
#else
#define _simd_s8x16_insert_x8(X,I,Y) _simd_s8x16_insert_x8_safe(X,I,Y)
#define _simd_s8x16__insert_x8_enable() true
#endif _simd_s8x16_insert_x8_

#define _simd_s8x16_extract_x32_safe(X,I) _simd_s8x16_insert_x16_safe(_simd_s8x16_fill_undefined_safe(),0,X)
#ifdef _simd_s8x16_extract_x32_
#define _simd_s8x16_extract_x32(X,I) _simd_s8x16_extract_x32_(X,I)
#define _simd_s8x16__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_extract_x32_instruction_set>()
#else
#define _simd_s8x16_extract_x32(X,I) _simd_s8x16_extract_x32_safe(X,I)
#define _simd_s8x16__extract_x32_enable() true
#endif _simd_s8x16_extract_x32_

#define _simd_s8x16_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s8x1) * 32)
#ifdef _simd_s8x16_insert_x32_
#define _simd_s8x16_insert_x32(X,I,Y) _simd_s8x16_insert_x32_(X,I,Y)
#define _simd_s8x16__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_insert_x32_instruction_set>()
#else
#define _simd_s8x16_insert_x32(X,I,Y) _simd_s8x16_insert_x32_safe(X,I,Y)
#define _simd_s8x16__insert_x32_enable() true
#endif _simd_s8x16_insert_x32_

#define _simd_s8x16_extract_x64_safe(X,I) _simd_s8x16_insert_x16_safe(_simd_s8x16_fill_undefined_safe(),0,X)
#ifdef _simd_s8x16_extract_x64_
#define _simd_s8x16_extract_x64(X,I) _simd_s8x16_extract_x64_(X,I)
#define _simd_s8x16__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_extract_x64_instruction_set>()
#else
#define _simd_s8x16_extract_x64(X,I) _simd_s8x16_extract_x64_safe(X,I)
#define _simd_s8x16__extract_x64_enable() true
#endif _simd_s8x16_extract_x64_

#define _simd_s8x16_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s8x1) * 64)
#ifdef _simd_s8x16_insert_x64_
#define _simd_s8x16_insert_x64(X,I,Y) _simd_s8x16_insert_x64_(X,I,Y)
#define _simd_s8x16__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_insert_x64_instruction_set>()
#else
#define _simd_s8x16_insert_x64(X,I,Y) _simd_s8x16_insert_x64_safe(X,I,Y)
#define _simd_s8x16__insert_x64_enable() true
#endif _simd_s8x16_insert_x64_

#define _simd_s8x16_extract_safe(X,I) _simd_s8x16_extract_x1_safe(X,I)
#define _simd_s8x16_extract(X,I) _simd_s8x16_extract_x1(X,I)
#define _simd_s8x16_extract_enable() _simd_s8x16_extract_x1_enable()

#define _simd_s8x16_insert_safe(X,I,Y) _simd_s8x16_insert_x1_safe(X,I,Y)
#define _simd_s8x16_insert(X,I,Y) _simd_s8x16_insert_x1(X,I,Y)
#define _simd_s8x16_insert_enable() _simd_s8x16_insert_x1_enable()

//#ifndef _simd_s8x16_splitlo
//	#define _simd_s8x16_splitlo(X) _simd_s8x8_extract_x8(X,0)
//	#define _simd_s8x16_splitlo_enable() _simd_s8x8_extract_x8_enable()
//#endif

//#ifndef _simd_s8x16_splithi
//	#define _simd_s8x16_splithi(X) _simd_s8x8_extract_x8(X,1)
//	#define _simd_s8x16_splithi_enable() _simd_s8x8_extract_x8_enable()
//#endif

//#ifndef _simd_s8x16_combine
//	#define _simd_s8x16_combine(X,Y) _simd_s8x16_insert_x8(_simd_s8x16_insert_x8(_simd_s8x16_fill_undefined(), 0, X), 1, Y)
//	#define _simd_s8x16_combine_enable() (_simd_s8x16_insert_x8_enable() && _simd_s8x16_fill_undefined_enable())
//#endif

#define _simd_s8x32_extract_x1_safe(X,I) (reinterpret_cast<const _simd_s8x32*>(&X)[I])
#ifdef _simd_s8x32_extract_x1_
#define _simd_s8x32_extract_x1(X,I) _simd_s8x32_extract_x1_(X,I)
#define _simd_s8x32__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_extract_x1_instruction_set>()
#else
#define _simd_s8x32_extract_x1(X,I) _simd_s8x32_extract_x1_safe(X,I)
#define _simd_s8x32__extract_x1_enable() true
#endif _simd_s8x32_extract_x1_

#define _simd_s8x32_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_s8x32*>(&X)[I] = Y)
#ifdef _simd_s8x32_insert_x1_
#define _simd_s8x32_insert_x1(X,I,Y) _simd_s8x32_insert_x1_(X,I,Y)
#define _simd_s8x32__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_insert_x1_instruction_set>()
#else
#define _simd_s8x32_insert_x1(X,I,Y) _simd_s8x32_insert_x1_safe(X,I,Y)
#define _simd_s8x32__insert_x1_enable() true
#endif _simd_s8x32_insert_x1_

#define _simd_s8x32_extract_x2_safe(X,I) (reinterpret_cast<const _simd_s8x32*>(&X)[I])
#ifdef _simd_s8x32_extract_x2_
#define _simd_s8x32_extract_x2(X,I) _simd_s8x32_extract_x2_(X,I)
#define _simd_s8x32__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_extract_x2_instruction_set>()
#else
#define _simd_s8x32_extract_x2(X,I) _simd_s8x32_extract_x2_safe(X,I)
#define _simd_s8x32__extract_x2_enable() true
#endif _simd_s8x32_extract_x2_

#define _simd_s8x32_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_s8x32*>(&X)[I] = Y)
#ifdef _simd_s8x32_insert_x2_
#define _simd_s8x32_insert_x2(X,I,Y) _simd_s8x32_insert_x2_(X,I,Y)
#define _simd_s8x32__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_insert_x2_instruction_set>()
#else
#define _simd_s8x32_insert_x2(X,I,Y) _simd_s8x32_insert_x2_safe(X,I,Y)
#define _simd_s8x32__insert_x2_enable() true
#endif _simd_s8x32_insert_x2_

#define _simd_s8x32_extract_x4_safe(X,I) (reinterpret_cast<const _simd_s8x32*>(&X)[I])
#ifdef _simd_s8x32_extract_x4_
#define _simd_s8x32_extract_x4(X,I) _simd_s8x32_extract_x4_(X,I)
#define _simd_s8x32__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_extract_x4_instruction_set>()
#else
#define _simd_s8x32_extract_x4(X,I) _simd_s8x32_extract_x4_safe(X,I)
#define _simd_s8x32__extract_x4_enable() true
#endif _simd_s8x32_extract_x4_

#define _simd_s8x32_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_s8x32*>(&X)[I] = Y)
#ifdef _simd_s8x32_insert_x4_
#define _simd_s8x32_insert_x4(X,I,Y) _simd_s8x32_insert_x4_(X,I,Y)
#define _simd_s8x32__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_insert_x4_instruction_set>()
#else
#define _simd_s8x32_insert_x4(X,I,Y) _simd_s8x32_insert_x4_safe(X,I,Y)
#define _simd_s8x32__insert_x4_enable() true
#endif _simd_s8x32_insert_x4_

#define _simd_s8x32_extract_x8_safe(X,I) (reinterpret_cast<const _simd_s8x32*>(&X)[I])
#ifdef _simd_s8x32_extract_x8_
#define _simd_s8x32_extract_x8(X,I) _simd_s8x32_extract_x8_(X,I)
#define _simd_s8x32__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_extract_x8_instruction_set>()
#else
#define _simd_s8x32_extract_x8(X,I) _simd_s8x32_extract_x8_safe(X,I)
#define _simd_s8x32__extract_x8_enable() true
#endif _simd_s8x32_extract_x8_

#define _simd_s8x32_insert_x8_safe(X,I,Y) (reinterpret_cast<_simd_s8x32*>(&X)[I] = Y)
#ifdef _simd_s8x32_insert_x8_
#define _simd_s8x32_insert_x8(X,I,Y) _simd_s8x32_insert_x8_(X,I,Y)
#define _simd_s8x32__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_insert_x8_instruction_set>()
#else
#define _simd_s8x32_insert_x8(X,I,Y) _simd_s8x32_insert_x8_safe(X,I,Y)
#define _simd_s8x32__insert_x8_enable() true
#endif _simd_s8x32_insert_x8_

#define _simd_s8x32_extract_x16_safe(X,I) (reinterpret_cast<const _simd_s8x32*>(&X)[I])
#ifdef _simd_s8x32_extract_x16_
#define _simd_s8x32_extract_x16(X,I) _simd_s8x32_extract_x16_(X,I)
#define _simd_s8x32__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_extract_x16_instruction_set>()
#else
#define _simd_s8x32_extract_x16(X,I) _simd_s8x32_extract_x16_safe(X,I)
#define _simd_s8x32__extract_x16_enable() true
#endif _simd_s8x32_extract_x16_

#define _simd_s8x32_insert_x16_safe(X,I,Y) (reinterpret_cast<_simd_s8x32*>(&X)[I] = Y)
#ifdef _simd_s8x32_insert_x16_
#define _simd_s8x32_insert_x16(X,I,Y) _simd_s8x32_insert_x16_(X,I,Y)
#define _simd_s8x32__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_insert_x16_instruction_set>()
#else
#define _simd_s8x32_insert_x16(X,I,Y) _simd_s8x32_insert_x16_safe(X,I,Y)
#define _simd_s8x32__insert_x16_enable() true
#endif _simd_s8x32_insert_x16_

#define _simd_s8x32_extract_x64_safe(X,I) _simd_s8x32_insert_x32_safe(_simd_s8x32_fill_undefined_safe(),0,X)
#ifdef _simd_s8x32_extract_x64_
#define _simd_s8x32_extract_x64(X,I) _simd_s8x32_extract_x64_(X,I)
#define _simd_s8x32__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_extract_x64_instruction_set>()
#else
#define _simd_s8x32_extract_x64(X,I) _simd_s8x32_extract_x64_safe(X,I)
#define _simd_s8x32__extract_x64_enable() true
#endif _simd_s8x32_extract_x64_

#define _simd_s8x32_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_s8x1) * 64)
#ifdef _simd_s8x32_insert_x64_
#define _simd_s8x32_insert_x64(X,I,Y) _simd_s8x32_insert_x64_(X,I,Y)
#define _simd_s8x32__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_insert_x64_instruction_set>()
#else
#define _simd_s8x32_insert_x64(X,I,Y) _simd_s8x32_insert_x64_safe(X,I,Y)
#define _simd_s8x32__insert_x64_enable() true
#endif _simd_s8x32_insert_x64_

#define _simd_s8x32_extract_safe(X,I) _simd_s8x32_extract_x1_safe(X,I)
#define _simd_s8x32_extract(X,I) _simd_s8x32_extract_x1(X,I)
#define _simd_s8x32_extract_enable() _simd_s8x32_extract_x1_enable()

#define _simd_s8x32_insert_safe(X,I,Y) _simd_s8x32_insert_x1_safe(X,I,Y)
#define _simd_s8x32_insert(X,I,Y) _simd_s8x32_insert_x1(X,I,Y)
#define _simd_s8x32_insert_enable() _simd_s8x32_insert_x1_enable()

//#ifndef _simd_s8x32_splitlo
//	#define _simd_s8x32_splitlo(X) _simd_s8x16_extract_x16(X,0)
//	#define _simd_s8x32_splitlo_enable() _simd_s8x16_extract_x16_enable()
//#endif

//#ifndef _simd_s8x32_splithi
//	#define _simd_s8x32_splithi(X) _simd_s8x16_extract_x16(X,1)
//	#define _simd_s8x32_splithi_enable() _simd_s8x16_extract_x16_enable()
//#endif

//#ifndef _simd_s8x32_combine
//	#define _simd_s8x32_combine(X,Y) _simd_s8x32_insert_x16(_simd_s8x32_insert_x16(_simd_s8x32_fill_undefined(), 0, X), 1, Y)
//	#define _simd_s8x32_combine_enable() (_simd_s8x32_insert_x16_enable() && _simd_s8x32_fill_undefined_enable())
//#endif

#define _simd_s8x64_extract_x1_safe(X,I) (reinterpret_cast<const _simd_s8x64*>(&X)[I])
#ifdef _simd_s8x64_extract_x1_
#define _simd_s8x64_extract_x1(X,I) _simd_s8x64_extract_x1_(X,I)
#define _simd_s8x64__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_extract_x1_instruction_set>()
#else
#define _simd_s8x64_extract_x1(X,I) _simd_s8x64_extract_x1_safe(X,I)
#define _simd_s8x64__extract_x1_enable() true
#endif _simd_s8x64_extract_x1_

#define _simd_s8x64_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_s8x64*>(&X)[I] = Y)
#ifdef _simd_s8x64_insert_x1_
#define _simd_s8x64_insert_x1(X,I,Y) _simd_s8x64_insert_x1_(X,I,Y)
#define _simd_s8x64__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_insert_x1_instruction_set>()
#else
#define _simd_s8x64_insert_x1(X,I,Y) _simd_s8x64_insert_x1_safe(X,I,Y)
#define _simd_s8x64__insert_x1_enable() true
#endif _simd_s8x64_insert_x1_

#define _simd_s8x64_extract_x2_safe(X,I) (reinterpret_cast<const _simd_s8x64*>(&X)[I])
#ifdef _simd_s8x64_extract_x2_
#define _simd_s8x64_extract_x2(X,I) _simd_s8x64_extract_x2_(X,I)
#define _simd_s8x64__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_extract_x2_instruction_set>()
#else
#define _simd_s8x64_extract_x2(X,I) _simd_s8x64_extract_x2_safe(X,I)
#define _simd_s8x64__extract_x2_enable() true
#endif _simd_s8x64_extract_x2_

#define _simd_s8x64_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_s8x64*>(&X)[I] = Y)
#ifdef _simd_s8x64_insert_x2_
#define _simd_s8x64_insert_x2(X,I,Y) _simd_s8x64_insert_x2_(X,I,Y)
#define _simd_s8x64__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_insert_x2_instruction_set>()
#else
#define _simd_s8x64_insert_x2(X,I,Y) _simd_s8x64_insert_x2_safe(X,I,Y)
#define _simd_s8x64__insert_x2_enable() true
#endif _simd_s8x64_insert_x2_

#define _simd_s8x64_extract_x4_safe(X,I) (reinterpret_cast<const _simd_s8x64*>(&X)[I])
#ifdef _simd_s8x64_extract_x4_
#define _simd_s8x64_extract_x4(X,I) _simd_s8x64_extract_x4_(X,I)
#define _simd_s8x64__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_extract_x4_instruction_set>()
#else
#define _simd_s8x64_extract_x4(X,I) _simd_s8x64_extract_x4_safe(X,I)
#define _simd_s8x64__extract_x4_enable() true
#endif _simd_s8x64_extract_x4_

#define _simd_s8x64_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_s8x64*>(&X)[I] = Y)
#ifdef _simd_s8x64_insert_x4_
#define _simd_s8x64_insert_x4(X,I,Y) _simd_s8x64_insert_x4_(X,I,Y)
#define _simd_s8x64__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_insert_x4_instruction_set>()
#else
#define _simd_s8x64_insert_x4(X,I,Y) _simd_s8x64_insert_x4_safe(X,I,Y)
#define _simd_s8x64__insert_x4_enable() true
#endif _simd_s8x64_insert_x4_

#define _simd_s8x64_extract_x8_safe(X,I) (reinterpret_cast<const _simd_s8x64*>(&X)[I])
#ifdef _simd_s8x64_extract_x8_
#define _simd_s8x64_extract_x8(X,I) _simd_s8x64_extract_x8_(X,I)
#define _simd_s8x64__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_extract_x8_instruction_set>()
#else
#define _simd_s8x64_extract_x8(X,I) _simd_s8x64_extract_x8_safe(X,I)
#define _simd_s8x64__extract_x8_enable() true
#endif _simd_s8x64_extract_x8_

#define _simd_s8x64_insert_x8_safe(X,I,Y) (reinterpret_cast<_simd_s8x64*>(&X)[I] = Y)
#ifdef _simd_s8x64_insert_x8_
#define _simd_s8x64_insert_x8(X,I,Y) _simd_s8x64_insert_x8_(X,I,Y)
#define _simd_s8x64__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_insert_x8_instruction_set>()
#else
#define _simd_s8x64_insert_x8(X,I,Y) _simd_s8x64_insert_x8_safe(X,I,Y)
#define _simd_s8x64__insert_x8_enable() true
#endif _simd_s8x64_insert_x8_

#define _simd_s8x64_extract_x16_safe(X,I) (reinterpret_cast<const _simd_s8x64*>(&X)[I])
#ifdef _simd_s8x64_extract_x16_
#define _simd_s8x64_extract_x16(X,I) _simd_s8x64_extract_x16_(X,I)
#define _simd_s8x64__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_extract_x16_instruction_set>()
#else
#define _simd_s8x64_extract_x16(X,I) _simd_s8x64_extract_x16_safe(X,I)
#define _simd_s8x64__extract_x16_enable() true
#endif _simd_s8x64_extract_x16_

#define _simd_s8x64_insert_x16_safe(X,I,Y) (reinterpret_cast<_simd_s8x64*>(&X)[I] = Y)
#ifdef _simd_s8x64_insert_x16_
#define _simd_s8x64_insert_x16(X,I,Y) _simd_s8x64_insert_x16_(X,I,Y)
#define _simd_s8x64__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_insert_x16_instruction_set>()
#else
#define _simd_s8x64_insert_x16(X,I,Y) _simd_s8x64_insert_x16_safe(X,I,Y)
#define _simd_s8x64__insert_x16_enable() true
#endif _simd_s8x64_insert_x16_

#define _simd_s8x64_extract_x32_safe(X,I) (reinterpret_cast<const _simd_s8x64*>(&X)[I])
#ifdef _simd_s8x64_extract_x32_
#define _simd_s8x64_extract_x32(X,I) _simd_s8x64_extract_x32_(X,I)
#define _simd_s8x64__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_extract_x32_instruction_set>()
#else
#define _simd_s8x64_extract_x32(X,I) _simd_s8x64_extract_x32_safe(X,I)
#define _simd_s8x64__extract_x32_enable() true
#endif _simd_s8x64_extract_x32_

#define _simd_s8x64_insert_x32_safe(X,I,Y) (reinterpret_cast<_simd_s8x64*>(&X)[I] = Y)
#ifdef _simd_s8x64_insert_x32_
#define _simd_s8x64_insert_x32(X,I,Y) _simd_s8x64_insert_x32_(X,I,Y)
#define _simd_s8x64__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_insert_x32_instruction_set>()
#else
#define _simd_s8x64_insert_x32(X,I,Y) _simd_s8x64_insert_x32_safe(X,I,Y)
#define _simd_s8x64__insert_x32_enable() true
#endif _simd_s8x64_insert_x32_

#define _simd_s8x64_extract_safe(X,I) _simd_s8x64_extract_x1_safe(X,I)
#define _simd_s8x64_extract(X,I) _simd_s8x64_extract_x1(X,I)
#define _simd_s8x64_extract_enable() _simd_s8x64_extract_x1_enable()

#define _simd_s8x64_insert_safe(X,I,Y) _simd_s8x64_insert_x1_safe(X,I,Y)
#define _simd_s8x64_insert(X,I,Y) _simd_s8x64_insert_x1(X,I,Y)
#define _simd_s8x64_insert_enable() _simd_s8x64_insert_x1_enable()

//#ifndef _simd_s8x64_splitlo
//	#define _simd_s8x64_splitlo(X) _simd_s8x32_extract_x32(X,0)
//	#define _simd_s8x64_splitlo_enable() _simd_s8x32_extract_x32_enable()
//#endif

//#ifndef _simd_s8x64_splithi
//	#define _simd_s8x64_splithi(X) _simd_s8x32_extract_x32(X,1)
//	#define _simd_s8x64_splithi_enable() _simd_s8x32_extract_x32_enable()
//#endif

//#ifndef _simd_s8x64_combine
//	#define _simd_s8x64_combine(X,Y) _simd_s8x64_insert_x32(_simd_s8x64_insert_x32(_simd_s8x64_fill_undefined(), 0, X), 1, Y)
//	#define _simd_s8x64_combine_enable() (_simd_s8x64_insert_x32_enable() && _simd_s8x64_fill_undefined_enable())
//#endif

// -- u8 --

#define _simd_u8x2_extract_x1_safe(X,I) (reinterpret_cast<const _simd_u8x2*>(&X)[I])
#ifdef _simd_u8x2_extract_x1_
#define _simd_u8x2_extract_x1(X,I) _simd_u8x2_extract_x1_(X,I)
#define _simd_u8x2__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_extract_x1_instruction_set>()
#else
#define _simd_u8x2_extract_x1(X,I) _simd_u8x2_extract_x1_safe(X,I)
#define _simd_u8x2__extract_x1_enable() true
#endif _simd_u8x2_extract_x1_

#define _simd_u8x2_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_u8x2*>(&X)[I] = Y)
#ifdef _simd_u8x2_insert_x1_
#define _simd_u8x2_insert_x1(X,I,Y) _simd_u8x2_insert_x1_(X,I,Y)
#define _simd_u8x2__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_insert_x1_instruction_set>()
#else
#define _simd_u8x2_insert_x1(X,I,Y) _simd_u8x2_insert_x1_safe(X,I,Y)
#define _simd_u8x2__insert_x1_enable() true
#endif _simd_u8x2_insert_x1_

#define _simd_u8x2_extract_x4_safe(X,I) _simd_u8x2_insert_x2_safe(_simd_u8x2_fill_undefined_safe(),0,X)
#ifdef _simd_u8x2_extract_x4_
#define _simd_u8x2_extract_x4(X,I) _simd_u8x2_extract_x4_(X,I)
#define _simd_u8x2__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_extract_x4_instruction_set>()
#else
#define _simd_u8x2_extract_x4(X,I) _simd_u8x2_extract_x4_safe(X,I)
#define _simd_u8x2__extract_x4_enable() true
#endif _simd_u8x2_extract_x4_

#define _simd_u8x2_insert_x4_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u8x1) * 4)
#ifdef _simd_u8x2_insert_x4_
#define _simd_u8x2_insert_x4(X,I,Y) _simd_u8x2_insert_x4_(X,I,Y)
#define _simd_u8x2__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_insert_x4_instruction_set>()
#else
#define _simd_u8x2_insert_x4(X,I,Y) _simd_u8x2_insert_x4_safe(X,I,Y)
#define _simd_u8x2__insert_x4_enable() true
#endif _simd_u8x2_insert_x4_

#define _simd_u8x2_extract_x8_safe(X,I) _simd_u8x2_insert_x2_safe(_simd_u8x2_fill_undefined_safe(),0,X)
#ifdef _simd_u8x2_extract_x8_
#define _simd_u8x2_extract_x8(X,I) _simd_u8x2_extract_x8_(X,I)
#define _simd_u8x2__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_extract_x8_instruction_set>()
#else
#define _simd_u8x2_extract_x8(X,I) _simd_u8x2_extract_x8_safe(X,I)
#define _simd_u8x2__extract_x8_enable() true
#endif _simd_u8x2_extract_x8_

#define _simd_u8x2_insert_x8_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u8x1) * 8)
#ifdef _simd_u8x2_insert_x8_
#define _simd_u8x2_insert_x8(X,I,Y) _simd_u8x2_insert_x8_(X,I,Y)
#define _simd_u8x2__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_insert_x8_instruction_set>()
#else
#define _simd_u8x2_insert_x8(X,I,Y) _simd_u8x2_insert_x8_safe(X,I,Y)
#define _simd_u8x2__insert_x8_enable() true
#endif _simd_u8x2_insert_x8_

#define _simd_u8x2_extract_x16_safe(X,I) _simd_u8x2_insert_x2_safe(_simd_u8x2_fill_undefined_safe(),0,X)
#ifdef _simd_u8x2_extract_x16_
#define _simd_u8x2_extract_x16(X,I) _simd_u8x2_extract_x16_(X,I)
#define _simd_u8x2__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_extract_x16_instruction_set>()
#else
#define _simd_u8x2_extract_x16(X,I) _simd_u8x2_extract_x16_safe(X,I)
#define _simd_u8x2__extract_x16_enable() true
#endif _simd_u8x2_extract_x16_

#define _simd_u8x2_insert_x16_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u8x1) * 16)
#ifdef _simd_u8x2_insert_x16_
#define _simd_u8x2_insert_x16(X,I,Y) _simd_u8x2_insert_x16_(X,I,Y)
#define _simd_u8x2__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_insert_x16_instruction_set>()
#else
#define _simd_u8x2_insert_x16(X,I,Y) _simd_u8x2_insert_x16_safe(X,I,Y)
#define _simd_u8x2__insert_x16_enable() true
#endif _simd_u8x2_insert_x16_

#define _simd_u8x2_extract_x32_safe(X,I) _simd_u8x2_insert_x2_safe(_simd_u8x2_fill_undefined_safe(),0,X)
#ifdef _simd_u8x2_extract_x32_
#define _simd_u8x2_extract_x32(X,I) _simd_u8x2_extract_x32_(X,I)
#define _simd_u8x2__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_extract_x32_instruction_set>()
#else
#define _simd_u8x2_extract_x32(X,I) _simd_u8x2_extract_x32_safe(X,I)
#define _simd_u8x2__extract_x32_enable() true
#endif _simd_u8x2_extract_x32_

#define _simd_u8x2_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u8x1) * 32)
#ifdef _simd_u8x2_insert_x32_
#define _simd_u8x2_insert_x32(X,I,Y) _simd_u8x2_insert_x32_(X,I,Y)
#define _simd_u8x2__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_insert_x32_instruction_set>()
#else
#define _simd_u8x2_insert_x32(X,I,Y) _simd_u8x2_insert_x32_safe(X,I,Y)
#define _simd_u8x2__insert_x32_enable() true
#endif _simd_u8x2_insert_x32_

#define _simd_u8x2_extract_x64_safe(X,I) _simd_u8x2_insert_x2_safe(_simd_u8x2_fill_undefined_safe(),0,X)
#ifdef _simd_u8x2_extract_x64_
#define _simd_u8x2_extract_x64(X,I) _simd_u8x2_extract_x64_(X,I)
#define _simd_u8x2__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_extract_x64_instruction_set>()
#else
#define _simd_u8x2_extract_x64(X,I) _simd_u8x2_extract_x64_safe(X,I)
#define _simd_u8x2__extract_x64_enable() true
#endif _simd_u8x2_extract_x64_

#define _simd_u8x2_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u8x1) * 64)
#ifdef _simd_u8x2_insert_x64_
#define _simd_u8x2_insert_x64(X,I,Y) _simd_u8x2_insert_x64_(X,I,Y)
#define _simd_u8x2__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_insert_x64_instruction_set>()
#else
#define _simd_u8x2_insert_x64(X,I,Y) _simd_u8x2_insert_x64_safe(X,I,Y)
#define _simd_u8x2__insert_x64_enable() true
#endif _simd_u8x2_insert_x64_

#define _simd_u8x2_extract_safe(X,I) _simd_u8x2_extract_x1_safe(X,I)
#define _simd_u8x2_extract(X,I) _simd_u8x2_extract_x1(X,I)
#define _simd_u8x2_extract_enable() _simd_u8x2_extract_x1_enable()

#define _simd_u8x2_insert_safe(X,I,Y) _simd_u8x2_insert_x1_safe(X,I,Y)
#define _simd_u8x2_insert(X,I,Y) _simd_u8x2_insert_x1(X,I,Y)
#define _simd_u8x2_insert_enable() _simd_u8x2_insert_x1_enable()

//#ifndef _simd_u8x2_splitlo
//	#define _simd_u8x2_splitlo(X) _simd_u8x1_extract_x1(X,0)
//	#define _simd_u8x2_splitlo_enable() _simd_u8x1_extract_x1_enable()
//#endif

//#ifndef _simd_u8x2_splithi
//	#define _simd_u8x2_splithi(X) _simd_u8x1_extract_x1(X,1)
//	#define _simd_u8x2_splithi_enable() _simd_u8x1_extract_x1_enable()
//#endif

//#ifndef _simd_u8x2_combine
//	#define _simd_u8x2_combine(X,Y) _simd_u8x2_insert_x1(_simd_u8x2_insert_x1(_simd_u8x2_fill_undefined(), 0, X), 1, Y)
//	#define _simd_u8x2_combine_enable() (_simd_u8x2_insert_x1_enable() && _simd_u8x2_fill_undefined_enable())
//#endif

#define _simd_u8x4_extract_x1_safe(X,I) (reinterpret_cast<const _simd_u8x4*>(&X)[I])
#ifdef _simd_u8x4_extract_x1_
#define _simd_u8x4_extract_x1(X,I) _simd_u8x4_extract_x1_(X,I)
#define _simd_u8x4__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_extract_x1_instruction_set>()
#else
#define _simd_u8x4_extract_x1(X,I) _simd_u8x4_extract_x1_safe(X,I)
#define _simd_u8x4__extract_x1_enable() true
#endif _simd_u8x4_extract_x1_

#define _simd_u8x4_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_u8x4*>(&X)[I] = Y)
#ifdef _simd_u8x4_insert_x1_
#define _simd_u8x4_insert_x1(X,I,Y) _simd_u8x4_insert_x1_(X,I,Y)
#define _simd_u8x4__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_insert_x1_instruction_set>()
#else
#define _simd_u8x4_insert_x1(X,I,Y) _simd_u8x4_insert_x1_safe(X,I,Y)
#define _simd_u8x4__insert_x1_enable() true
#endif _simd_u8x4_insert_x1_

#define _simd_u8x4_extract_x2_safe(X,I) (reinterpret_cast<const _simd_u8x4*>(&X)[I])
#ifdef _simd_u8x4_extract_x2_
#define _simd_u8x4_extract_x2(X,I) _simd_u8x4_extract_x2_(X,I)
#define _simd_u8x4__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_extract_x2_instruction_set>()
#else
#define _simd_u8x4_extract_x2(X,I) _simd_u8x4_extract_x2_safe(X,I)
#define _simd_u8x4__extract_x2_enable() true
#endif _simd_u8x4_extract_x2_

#define _simd_u8x4_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_u8x4*>(&X)[I] = Y)
#ifdef _simd_u8x4_insert_x2_
#define _simd_u8x4_insert_x2(X,I,Y) _simd_u8x4_insert_x2_(X,I,Y)
#define _simd_u8x4__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_insert_x2_instruction_set>()
#else
#define _simd_u8x4_insert_x2(X,I,Y) _simd_u8x4_insert_x2_safe(X,I,Y)
#define _simd_u8x4__insert_x2_enable() true
#endif _simd_u8x4_insert_x2_

#define _simd_u8x4_extract_x8_safe(X,I) _simd_u8x4_insert_x4_safe(_simd_u8x4_fill_undefined_safe(),0,X)
#ifdef _simd_u8x4_extract_x8_
#define _simd_u8x4_extract_x8(X,I) _simd_u8x4_extract_x8_(X,I)
#define _simd_u8x4__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_extract_x8_instruction_set>()
#else
#define _simd_u8x4_extract_x8(X,I) _simd_u8x4_extract_x8_safe(X,I)
#define _simd_u8x4__extract_x8_enable() true
#endif _simd_u8x4_extract_x8_

#define _simd_u8x4_insert_x8_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u8x1) * 8)
#ifdef _simd_u8x4_insert_x8_
#define _simd_u8x4_insert_x8(X,I,Y) _simd_u8x4_insert_x8_(X,I,Y)
#define _simd_u8x4__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_insert_x8_instruction_set>()
#else
#define _simd_u8x4_insert_x8(X,I,Y) _simd_u8x4_insert_x8_safe(X,I,Y)
#define _simd_u8x4__insert_x8_enable() true
#endif _simd_u8x4_insert_x8_

#define _simd_u8x4_extract_x16_safe(X,I) _simd_u8x4_insert_x4_safe(_simd_u8x4_fill_undefined_safe(),0,X)
#ifdef _simd_u8x4_extract_x16_
#define _simd_u8x4_extract_x16(X,I) _simd_u8x4_extract_x16_(X,I)
#define _simd_u8x4__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_extract_x16_instruction_set>()
#else
#define _simd_u8x4_extract_x16(X,I) _simd_u8x4_extract_x16_safe(X,I)
#define _simd_u8x4__extract_x16_enable() true
#endif _simd_u8x4_extract_x16_

#define _simd_u8x4_insert_x16_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u8x1) * 16)
#ifdef _simd_u8x4_insert_x16_
#define _simd_u8x4_insert_x16(X,I,Y) _simd_u8x4_insert_x16_(X,I,Y)
#define _simd_u8x4__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_insert_x16_instruction_set>()
#else
#define _simd_u8x4_insert_x16(X,I,Y) _simd_u8x4_insert_x16_safe(X,I,Y)
#define _simd_u8x4__insert_x16_enable() true
#endif _simd_u8x4_insert_x16_

#define _simd_u8x4_extract_x32_safe(X,I) _simd_u8x4_insert_x4_safe(_simd_u8x4_fill_undefined_safe(),0,X)
#ifdef _simd_u8x4_extract_x32_
#define _simd_u8x4_extract_x32(X,I) _simd_u8x4_extract_x32_(X,I)
#define _simd_u8x4__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_extract_x32_instruction_set>()
#else
#define _simd_u8x4_extract_x32(X,I) _simd_u8x4_extract_x32_safe(X,I)
#define _simd_u8x4__extract_x32_enable() true
#endif _simd_u8x4_extract_x32_

#define _simd_u8x4_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u8x1) * 32)
#ifdef _simd_u8x4_insert_x32_
#define _simd_u8x4_insert_x32(X,I,Y) _simd_u8x4_insert_x32_(X,I,Y)
#define _simd_u8x4__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_insert_x32_instruction_set>()
#else
#define _simd_u8x4_insert_x32(X,I,Y) _simd_u8x4_insert_x32_safe(X,I,Y)
#define _simd_u8x4__insert_x32_enable() true
#endif _simd_u8x4_insert_x32_

#define _simd_u8x4_extract_x64_safe(X,I) _simd_u8x4_insert_x4_safe(_simd_u8x4_fill_undefined_safe(),0,X)
#ifdef _simd_u8x4_extract_x64_
#define _simd_u8x4_extract_x64(X,I) _simd_u8x4_extract_x64_(X,I)
#define _simd_u8x4__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_extract_x64_instruction_set>()
#else
#define _simd_u8x4_extract_x64(X,I) _simd_u8x4_extract_x64_safe(X,I)
#define _simd_u8x4__extract_x64_enable() true
#endif _simd_u8x4_extract_x64_

#define _simd_u8x4_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u8x1) * 64)
#ifdef _simd_u8x4_insert_x64_
#define _simd_u8x4_insert_x64(X,I,Y) _simd_u8x4_insert_x64_(X,I,Y)
#define _simd_u8x4__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_insert_x64_instruction_set>()
#else
#define _simd_u8x4_insert_x64(X,I,Y) _simd_u8x4_insert_x64_safe(X,I,Y)
#define _simd_u8x4__insert_x64_enable() true
#endif _simd_u8x4_insert_x64_

#define _simd_u8x4_extract_safe(X,I) _simd_u8x4_extract_x1_safe(X,I)
#define _simd_u8x4_extract(X,I) _simd_u8x4_extract_x1(X,I)
#define _simd_u8x4_extract_enable() _simd_u8x4_extract_x1_enable()

#define _simd_u8x4_insert_safe(X,I,Y) _simd_u8x4_insert_x1_safe(X,I,Y)
#define _simd_u8x4_insert(X,I,Y) _simd_u8x4_insert_x1(X,I,Y)
#define _simd_u8x4_insert_enable() _simd_u8x4_insert_x1_enable()

//#ifndef _simd_u8x4_splitlo
//	#define _simd_u8x4_splitlo(X) _simd_u8x2_extract_x2(X,0)
//	#define _simd_u8x4_splitlo_enable() _simd_u8x2_extract_x2_enable()
//#endif

//#ifndef _simd_u8x4_splithi
//	#define _simd_u8x4_splithi(X) _simd_u8x2_extract_x2(X,1)
//	#define _simd_u8x4_splithi_enable() _simd_u8x2_extract_x2_enable()
//#endif

//#ifndef _simd_u8x4_combine
//	#define _simd_u8x4_combine(X,Y) _simd_u8x4_insert_x2(_simd_u8x4_insert_x2(_simd_u8x4_fill_undefined(), 0, X), 1, Y)
//	#define _simd_u8x4_combine_enable() (_simd_u8x4_insert_x2_enable() && _simd_u8x4_fill_undefined_enable())
//#endif

#define _simd_u8x8_extract_x1_safe(X,I) (reinterpret_cast<const _simd_u8x8*>(&X)[I])
#ifdef _simd_u8x8_extract_x1_
#define _simd_u8x8_extract_x1(X,I) _simd_u8x8_extract_x1_(X,I)
#define _simd_u8x8__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_extract_x1_instruction_set>()
#else
#define _simd_u8x8_extract_x1(X,I) _simd_u8x8_extract_x1_safe(X,I)
#define _simd_u8x8__extract_x1_enable() true
#endif _simd_u8x8_extract_x1_

#define _simd_u8x8_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_u8x8*>(&X)[I] = Y)
#ifdef _simd_u8x8_insert_x1_
#define _simd_u8x8_insert_x1(X,I,Y) _simd_u8x8_insert_x1_(X,I,Y)
#define _simd_u8x8__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_insert_x1_instruction_set>()
#else
#define _simd_u8x8_insert_x1(X,I,Y) _simd_u8x8_insert_x1_safe(X,I,Y)
#define _simd_u8x8__insert_x1_enable() true
#endif _simd_u8x8_insert_x1_

#define _simd_u8x8_extract_x2_safe(X,I) (reinterpret_cast<const _simd_u8x8*>(&X)[I])
#ifdef _simd_u8x8_extract_x2_
#define _simd_u8x8_extract_x2(X,I) _simd_u8x8_extract_x2_(X,I)
#define _simd_u8x8__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_extract_x2_instruction_set>()
#else
#define _simd_u8x8_extract_x2(X,I) _simd_u8x8_extract_x2_safe(X,I)
#define _simd_u8x8__extract_x2_enable() true
#endif _simd_u8x8_extract_x2_

#define _simd_u8x8_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_u8x8*>(&X)[I] = Y)
#ifdef _simd_u8x8_insert_x2_
#define _simd_u8x8_insert_x2(X,I,Y) _simd_u8x8_insert_x2_(X,I,Y)
#define _simd_u8x8__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_insert_x2_instruction_set>()
#else
#define _simd_u8x8_insert_x2(X,I,Y) _simd_u8x8_insert_x2_safe(X,I,Y)
#define _simd_u8x8__insert_x2_enable() true
#endif _simd_u8x8_insert_x2_

#define _simd_u8x8_extract_x4_safe(X,I) (reinterpret_cast<const _simd_u8x8*>(&X)[I])
#ifdef _simd_u8x8_extract_x4_
#define _simd_u8x8_extract_x4(X,I) _simd_u8x8_extract_x4_(X,I)
#define _simd_u8x8__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_extract_x4_instruction_set>()
#else
#define _simd_u8x8_extract_x4(X,I) _simd_u8x8_extract_x4_safe(X,I)
#define _simd_u8x8__extract_x4_enable() true
#endif _simd_u8x8_extract_x4_

#define _simd_u8x8_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_u8x8*>(&X)[I] = Y)
#ifdef _simd_u8x8_insert_x4_
#define _simd_u8x8_insert_x4(X,I,Y) _simd_u8x8_insert_x4_(X,I,Y)
#define _simd_u8x8__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_insert_x4_instruction_set>()
#else
#define _simd_u8x8_insert_x4(X,I,Y) _simd_u8x8_insert_x4_safe(X,I,Y)
#define _simd_u8x8__insert_x4_enable() true
#endif _simd_u8x8_insert_x4_

#define _simd_u8x8_extract_x16_safe(X,I) _simd_u8x8_insert_x8_safe(_simd_u8x8_fill_undefined_safe(),0,X)
#ifdef _simd_u8x8_extract_x16_
#define _simd_u8x8_extract_x16(X,I) _simd_u8x8_extract_x16_(X,I)
#define _simd_u8x8__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_extract_x16_instruction_set>()
#else
#define _simd_u8x8_extract_x16(X,I) _simd_u8x8_extract_x16_safe(X,I)
#define _simd_u8x8__extract_x16_enable() true
#endif _simd_u8x8_extract_x16_

#define _simd_u8x8_insert_x16_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u8x1) * 16)
#ifdef _simd_u8x8_insert_x16_
#define _simd_u8x8_insert_x16(X,I,Y) _simd_u8x8_insert_x16_(X,I,Y)
#define _simd_u8x8__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_insert_x16_instruction_set>()
#else
#define _simd_u8x8_insert_x16(X,I,Y) _simd_u8x8_insert_x16_safe(X,I,Y)
#define _simd_u8x8__insert_x16_enable() true
#endif _simd_u8x8_insert_x16_

#define _simd_u8x8_extract_x32_safe(X,I) _simd_u8x8_insert_x8_safe(_simd_u8x8_fill_undefined_safe(),0,X)
#ifdef _simd_u8x8_extract_x32_
#define _simd_u8x8_extract_x32(X,I) _simd_u8x8_extract_x32_(X,I)
#define _simd_u8x8__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_extract_x32_instruction_set>()
#else
#define _simd_u8x8_extract_x32(X,I) _simd_u8x8_extract_x32_safe(X,I)
#define _simd_u8x8__extract_x32_enable() true
#endif _simd_u8x8_extract_x32_

#define _simd_u8x8_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u8x1) * 32)
#ifdef _simd_u8x8_insert_x32_
#define _simd_u8x8_insert_x32(X,I,Y) _simd_u8x8_insert_x32_(X,I,Y)
#define _simd_u8x8__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_insert_x32_instruction_set>()
#else
#define _simd_u8x8_insert_x32(X,I,Y) _simd_u8x8_insert_x32_safe(X,I,Y)
#define _simd_u8x8__insert_x32_enable() true
#endif _simd_u8x8_insert_x32_

#define _simd_u8x8_extract_x64_safe(X,I) _simd_u8x8_insert_x8_safe(_simd_u8x8_fill_undefined_safe(),0,X)
#ifdef _simd_u8x8_extract_x64_
#define _simd_u8x8_extract_x64(X,I) _simd_u8x8_extract_x64_(X,I)
#define _simd_u8x8__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_extract_x64_instruction_set>()
#else
#define _simd_u8x8_extract_x64(X,I) _simd_u8x8_extract_x64_safe(X,I)
#define _simd_u8x8__extract_x64_enable() true
#endif _simd_u8x8_extract_x64_

#define _simd_u8x8_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u8x1) * 64)
#ifdef _simd_u8x8_insert_x64_
#define _simd_u8x8_insert_x64(X,I,Y) _simd_u8x8_insert_x64_(X,I,Y)
#define _simd_u8x8__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_insert_x64_instruction_set>()
#else
#define _simd_u8x8_insert_x64(X,I,Y) _simd_u8x8_insert_x64_safe(X,I,Y)
#define _simd_u8x8__insert_x64_enable() true
#endif _simd_u8x8_insert_x64_

#define _simd_u8x8_extract_safe(X,I) _simd_u8x8_extract_x1_safe(X,I)
#define _simd_u8x8_extract(X,I) _simd_u8x8_extract_x1(X,I)
#define _simd_u8x8_extract_enable() _simd_u8x8_extract_x1_enable()

#define _simd_u8x8_insert_safe(X,I,Y) _simd_u8x8_insert_x1_safe(X,I,Y)
#define _simd_u8x8_insert(X,I,Y) _simd_u8x8_insert_x1(X,I,Y)
#define _simd_u8x8_insert_enable() _simd_u8x8_insert_x1_enable()

//#ifndef _simd_u8x8_splitlo
//	#define _simd_u8x8_splitlo(X) _simd_u8x4_extract_x4(X,0)
//	#define _simd_u8x8_splitlo_enable() _simd_u8x4_extract_x4_enable()
//#endif

//#ifndef _simd_u8x8_splithi
//	#define _simd_u8x8_splithi(X) _simd_u8x4_extract_x4(X,1)
//	#define _simd_u8x8_splithi_enable() _simd_u8x4_extract_x4_enable()
//#endif

//#ifndef _simd_u8x8_combine
//	#define _simd_u8x8_combine(X,Y) _simd_u8x8_insert_x4(_simd_u8x8_insert_x4(_simd_u8x8_fill_undefined(), 0, X), 1, Y)
//	#define _simd_u8x8_combine_enable() (_simd_u8x8_insert_x4_enable() && _simd_u8x8_fill_undefined_enable())
//#endif

#define _simd_u8x16_extract_x1_safe(X,I) (reinterpret_cast<const _simd_u8x16*>(&X)[I])
#ifdef _simd_u8x16_extract_x1_
#define _simd_u8x16_extract_x1(X,I) _simd_u8x16_extract_x1_(X,I)
#define _simd_u8x16__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_extract_x1_instruction_set>()
#else
#define _simd_u8x16_extract_x1(X,I) _simd_u8x16_extract_x1_safe(X,I)
#define _simd_u8x16__extract_x1_enable() true
#endif _simd_u8x16_extract_x1_

#define _simd_u8x16_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_u8x16*>(&X)[I] = Y)
#ifdef _simd_u8x16_insert_x1_
#define _simd_u8x16_insert_x1(X,I,Y) _simd_u8x16_insert_x1_(X,I,Y)
#define _simd_u8x16__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_insert_x1_instruction_set>()
#else
#define _simd_u8x16_insert_x1(X,I,Y) _simd_u8x16_insert_x1_safe(X,I,Y)
#define _simd_u8x16__insert_x1_enable() true
#endif _simd_u8x16_insert_x1_

#define _simd_u8x16_extract_x2_safe(X,I) (reinterpret_cast<const _simd_u8x16*>(&X)[I])
#ifdef _simd_u8x16_extract_x2_
#define _simd_u8x16_extract_x2(X,I) _simd_u8x16_extract_x2_(X,I)
#define _simd_u8x16__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_extract_x2_instruction_set>()
#else
#define _simd_u8x16_extract_x2(X,I) _simd_u8x16_extract_x2_safe(X,I)
#define _simd_u8x16__extract_x2_enable() true
#endif _simd_u8x16_extract_x2_

#define _simd_u8x16_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_u8x16*>(&X)[I] = Y)
#ifdef _simd_u8x16_insert_x2_
#define _simd_u8x16_insert_x2(X,I,Y) _simd_u8x16_insert_x2_(X,I,Y)
#define _simd_u8x16__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_insert_x2_instruction_set>()
#else
#define _simd_u8x16_insert_x2(X,I,Y) _simd_u8x16_insert_x2_safe(X,I,Y)
#define _simd_u8x16__insert_x2_enable() true
#endif _simd_u8x16_insert_x2_

#define _simd_u8x16_extract_x4_safe(X,I) (reinterpret_cast<const _simd_u8x16*>(&X)[I])
#ifdef _simd_u8x16_extract_x4_
#define _simd_u8x16_extract_x4(X,I) _simd_u8x16_extract_x4_(X,I)
#define _simd_u8x16__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_extract_x4_instruction_set>()
#else
#define _simd_u8x16_extract_x4(X,I) _simd_u8x16_extract_x4_safe(X,I)
#define _simd_u8x16__extract_x4_enable() true
#endif _simd_u8x16_extract_x4_

#define _simd_u8x16_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_u8x16*>(&X)[I] = Y)
#ifdef _simd_u8x16_insert_x4_
#define _simd_u8x16_insert_x4(X,I,Y) _simd_u8x16_insert_x4_(X,I,Y)
#define _simd_u8x16__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_insert_x4_instruction_set>()
#else
#define _simd_u8x16_insert_x4(X,I,Y) _simd_u8x16_insert_x4_safe(X,I,Y)
#define _simd_u8x16__insert_x4_enable() true
#endif _simd_u8x16_insert_x4_

#define _simd_u8x16_extract_x8_safe(X,I) (reinterpret_cast<const _simd_u8x16*>(&X)[I])
#ifdef _simd_u8x16_extract_x8_
#define _simd_u8x16_extract_x8(X,I) _simd_u8x16_extract_x8_(X,I)
#define _simd_u8x16__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_extract_x8_instruction_set>()
#else
#define _simd_u8x16_extract_x8(X,I) _simd_u8x16_extract_x8_safe(X,I)
#define _simd_u8x16__extract_x8_enable() true
#endif _simd_u8x16_extract_x8_

#define _simd_u8x16_insert_x8_safe(X,I,Y) (reinterpret_cast<_simd_u8x16*>(&X)[I] = Y)
#ifdef _simd_u8x16_insert_x8_
#define _simd_u8x16_insert_x8(X,I,Y) _simd_u8x16_insert_x8_(X,I,Y)
#define _simd_u8x16__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_insert_x8_instruction_set>()
#else
#define _simd_u8x16_insert_x8(X,I,Y) _simd_u8x16_insert_x8_safe(X,I,Y)
#define _simd_u8x16__insert_x8_enable() true
#endif _simd_u8x16_insert_x8_

#define _simd_u8x16_extract_x32_safe(X,I) _simd_u8x16_insert_x16_safe(_simd_u8x16_fill_undefined_safe(),0,X)
#ifdef _simd_u8x16_extract_x32_
#define _simd_u8x16_extract_x32(X,I) _simd_u8x16_extract_x32_(X,I)
#define _simd_u8x16__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_extract_x32_instruction_set>()
#else
#define _simd_u8x16_extract_x32(X,I) _simd_u8x16_extract_x32_safe(X,I)
#define _simd_u8x16__extract_x32_enable() true
#endif _simd_u8x16_extract_x32_

#define _simd_u8x16_insert_x32_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u8x1) * 32)
#ifdef _simd_u8x16_insert_x32_
#define _simd_u8x16_insert_x32(X,I,Y) _simd_u8x16_insert_x32_(X,I,Y)
#define _simd_u8x16__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_insert_x32_instruction_set>()
#else
#define _simd_u8x16_insert_x32(X,I,Y) _simd_u8x16_insert_x32_safe(X,I,Y)
#define _simd_u8x16__insert_x32_enable() true
#endif _simd_u8x16_insert_x32_

#define _simd_u8x16_extract_x64_safe(X,I) _simd_u8x16_insert_x16_safe(_simd_u8x16_fill_undefined_safe(),0,X)
#ifdef _simd_u8x16_extract_x64_
#define _simd_u8x16_extract_x64(X,I) _simd_u8x16_extract_x64_(X,I)
#define _simd_u8x16__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_extract_x64_instruction_set>()
#else
#define _simd_u8x16_extract_x64(X,I) _simd_u8x16_extract_x64_safe(X,I)
#define _simd_u8x16__extract_x64_enable() true
#endif _simd_u8x16_extract_x64_

#define _simd_u8x16_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u8x1) * 64)
#ifdef _simd_u8x16_insert_x64_
#define _simd_u8x16_insert_x64(X,I,Y) _simd_u8x16_insert_x64_(X,I,Y)
#define _simd_u8x16__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_insert_x64_instruction_set>()
#else
#define _simd_u8x16_insert_x64(X,I,Y) _simd_u8x16_insert_x64_safe(X,I,Y)
#define _simd_u8x16__insert_x64_enable() true
#endif _simd_u8x16_insert_x64_

#define _simd_u8x16_extract_safe(X,I) _simd_u8x16_extract_x1_safe(X,I)
#define _simd_u8x16_extract(X,I) _simd_u8x16_extract_x1(X,I)
#define _simd_u8x16_extract_enable() _simd_u8x16_extract_x1_enable()

#define _simd_u8x16_insert_safe(X,I,Y) _simd_u8x16_insert_x1_safe(X,I,Y)
#define _simd_u8x16_insert(X,I,Y) _simd_u8x16_insert_x1(X,I,Y)
#define _simd_u8x16_insert_enable() _simd_u8x16_insert_x1_enable()

//#ifndef _simd_u8x16_splitlo
//	#define _simd_u8x16_splitlo(X) _simd_u8x8_extract_x8(X,0)
//	#define _simd_u8x16_splitlo_enable() _simd_u8x8_extract_x8_enable()
//#endif

//#ifndef _simd_u8x16_splithi
//	#define _simd_u8x16_splithi(X) _simd_u8x8_extract_x8(X,1)
//	#define _simd_u8x16_splithi_enable() _simd_u8x8_extract_x8_enable()
//#endif

//#ifndef _simd_u8x16_combine
//	#define _simd_u8x16_combine(X,Y) _simd_u8x16_insert_x8(_simd_u8x16_insert_x8(_simd_u8x16_fill_undefined(), 0, X), 1, Y)
//	#define _simd_u8x16_combine_enable() (_simd_u8x16_insert_x8_enable() && _simd_u8x16_fill_undefined_enable())
//#endif

#define _simd_u8x32_extract_x1_safe(X,I) (reinterpret_cast<const _simd_u8x32*>(&X)[I])
#ifdef _simd_u8x32_extract_x1_
#define _simd_u8x32_extract_x1(X,I) _simd_u8x32_extract_x1_(X,I)
#define _simd_u8x32__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_extract_x1_instruction_set>()
#else
#define _simd_u8x32_extract_x1(X,I) _simd_u8x32_extract_x1_safe(X,I)
#define _simd_u8x32__extract_x1_enable() true
#endif _simd_u8x32_extract_x1_

#define _simd_u8x32_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_u8x32*>(&X)[I] = Y)
#ifdef _simd_u8x32_insert_x1_
#define _simd_u8x32_insert_x1(X,I,Y) _simd_u8x32_insert_x1_(X,I,Y)
#define _simd_u8x32__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_insert_x1_instruction_set>()
#else
#define _simd_u8x32_insert_x1(X,I,Y) _simd_u8x32_insert_x1_safe(X,I,Y)
#define _simd_u8x32__insert_x1_enable() true
#endif _simd_u8x32_insert_x1_

#define _simd_u8x32_extract_x2_safe(X,I) (reinterpret_cast<const _simd_u8x32*>(&X)[I])
#ifdef _simd_u8x32_extract_x2_
#define _simd_u8x32_extract_x2(X,I) _simd_u8x32_extract_x2_(X,I)
#define _simd_u8x32__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_extract_x2_instruction_set>()
#else
#define _simd_u8x32_extract_x2(X,I) _simd_u8x32_extract_x2_safe(X,I)
#define _simd_u8x32__extract_x2_enable() true
#endif _simd_u8x32_extract_x2_

#define _simd_u8x32_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_u8x32*>(&X)[I] = Y)
#ifdef _simd_u8x32_insert_x2_
#define _simd_u8x32_insert_x2(X,I,Y) _simd_u8x32_insert_x2_(X,I,Y)
#define _simd_u8x32__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_insert_x2_instruction_set>()
#else
#define _simd_u8x32_insert_x2(X,I,Y) _simd_u8x32_insert_x2_safe(X,I,Y)
#define _simd_u8x32__insert_x2_enable() true
#endif _simd_u8x32_insert_x2_

#define _simd_u8x32_extract_x4_safe(X,I) (reinterpret_cast<const _simd_u8x32*>(&X)[I])
#ifdef _simd_u8x32_extract_x4_
#define _simd_u8x32_extract_x4(X,I) _simd_u8x32_extract_x4_(X,I)
#define _simd_u8x32__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_extract_x4_instruction_set>()
#else
#define _simd_u8x32_extract_x4(X,I) _simd_u8x32_extract_x4_safe(X,I)
#define _simd_u8x32__extract_x4_enable() true
#endif _simd_u8x32_extract_x4_

#define _simd_u8x32_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_u8x32*>(&X)[I] = Y)
#ifdef _simd_u8x32_insert_x4_
#define _simd_u8x32_insert_x4(X,I,Y) _simd_u8x32_insert_x4_(X,I,Y)
#define _simd_u8x32__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_insert_x4_instruction_set>()
#else
#define _simd_u8x32_insert_x4(X,I,Y) _simd_u8x32_insert_x4_safe(X,I,Y)
#define _simd_u8x32__insert_x4_enable() true
#endif _simd_u8x32_insert_x4_

#define _simd_u8x32_extract_x8_safe(X,I) (reinterpret_cast<const _simd_u8x32*>(&X)[I])
#ifdef _simd_u8x32_extract_x8_
#define _simd_u8x32_extract_x8(X,I) _simd_u8x32_extract_x8_(X,I)
#define _simd_u8x32__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_extract_x8_instruction_set>()
#else
#define _simd_u8x32_extract_x8(X,I) _simd_u8x32_extract_x8_safe(X,I)
#define _simd_u8x32__extract_x8_enable() true
#endif _simd_u8x32_extract_x8_

#define _simd_u8x32_insert_x8_safe(X,I,Y) (reinterpret_cast<_simd_u8x32*>(&X)[I] = Y)
#ifdef _simd_u8x32_insert_x8_
#define _simd_u8x32_insert_x8(X,I,Y) _simd_u8x32_insert_x8_(X,I,Y)
#define _simd_u8x32__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_insert_x8_instruction_set>()
#else
#define _simd_u8x32_insert_x8(X,I,Y) _simd_u8x32_insert_x8_safe(X,I,Y)
#define _simd_u8x32__insert_x8_enable() true
#endif _simd_u8x32_insert_x8_

#define _simd_u8x32_extract_x16_safe(X,I) (reinterpret_cast<const _simd_u8x32*>(&X)[I])
#ifdef _simd_u8x32_extract_x16_
#define _simd_u8x32_extract_x16(X,I) _simd_u8x32_extract_x16_(X,I)
#define _simd_u8x32__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_extract_x16_instruction_set>()
#else
#define _simd_u8x32_extract_x16(X,I) _simd_u8x32_extract_x16_safe(X,I)
#define _simd_u8x32__extract_x16_enable() true
#endif _simd_u8x32_extract_x16_

#define _simd_u8x32_insert_x16_safe(X,I,Y) (reinterpret_cast<_simd_u8x32*>(&X)[I] = Y)
#ifdef _simd_u8x32_insert_x16_
#define _simd_u8x32_insert_x16(X,I,Y) _simd_u8x32_insert_x16_(X,I,Y)
#define _simd_u8x32__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_insert_x16_instruction_set>()
#else
#define _simd_u8x32_insert_x16(X,I,Y) _simd_u8x32_insert_x16_safe(X,I,Y)
#define _simd_u8x32__insert_x16_enable() true
#endif _simd_u8x32_insert_x16_

#define _simd_u8x32_extract_x64_safe(X,I) _simd_u8x32_insert_x32_safe(_simd_u8x32_fill_undefined_safe(),0,X)
#ifdef _simd_u8x32_extract_x64_
#define _simd_u8x32_extract_x64(X,I) _simd_u8x32_extract_x64_(X,I)
#define _simd_u8x32__extract_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_extract_x64_instruction_set>()
#else
#define _simd_u8x32_extract_x64(X,I) _simd_u8x32_extract_x64_safe(X,I)
#define _simd_u8x32__extract_x64_enable() true
#endif _simd_u8x32_extract_x64_

#define _simd_u8x32_insert_x64_safe(X,I,Y) memcpy(&X, &Y, sizeof(_simd_u8x1) * 64)
#ifdef _simd_u8x32_insert_x64_
#define _simd_u8x32_insert_x64(X,I,Y) _simd_u8x32_insert_x64_(X,I,Y)
#define _simd_u8x32__insert_x64_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_insert_x64_instruction_set>()
#else
#define _simd_u8x32_insert_x64(X,I,Y) _simd_u8x32_insert_x64_safe(X,I,Y)
#define _simd_u8x32__insert_x64_enable() true
#endif _simd_u8x32_insert_x64_

#define _simd_u8x32_extract_safe(X,I) _simd_u8x32_extract_x1_safe(X,I)
#define _simd_u8x32_extract(X,I) _simd_u8x32_extract_x1(X,I)
#define _simd_u8x32_extract_enable() _simd_u8x32_extract_x1_enable()

#define _simd_u8x32_insert_safe(X,I,Y) _simd_u8x32_insert_x1_safe(X,I,Y)
#define _simd_u8x32_insert(X,I,Y) _simd_u8x32_insert_x1(X,I,Y)
#define _simd_u8x32_insert_enable() _simd_u8x32_insert_x1_enable()

//#ifndef _simd_u8x32_splitlo
//	#define _simd_u8x32_splitlo(X) _simd_u8x16_extract_x16(X,0)
//	#define _simd_u8x32_splitlo_enable() _simd_u8x16_extract_x16_enable()
//#endif

//#ifndef _simd_u8x32_splithi
//	#define _simd_u8x32_splithi(X) _simd_u8x16_extract_x16(X,1)
//	#define _simd_u8x32_splithi_enable() _simd_u8x16_extract_x16_enable()
//#endif

//#ifndef _simd_u8x32_combine
//	#define _simd_u8x32_combine(X,Y) _simd_u8x32_insert_x16(_simd_u8x32_insert_x16(_simd_u8x32_fill_undefined(), 0, X), 1, Y)
//	#define _simd_u8x32_combine_enable() (_simd_u8x32_insert_x16_enable() && _simd_u8x32_fill_undefined_enable())
//#endif

#define _simd_u8x64_extract_x1_safe(X,I) (reinterpret_cast<const _simd_u8x64*>(&X)[I])
#ifdef _simd_u8x64_extract_x1_
#define _simd_u8x64_extract_x1(X,I) _simd_u8x64_extract_x1_(X,I)
#define _simd_u8x64__extract_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_extract_x1_instruction_set>()
#else
#define _simd_u8x64_extract_x1(X,I) _simd_u8x64_extract_x1_safe(X,I)
#define _simd_u8x64__extract_x1_enable() true
#endif _simd_u8x64_extract_x1_

#define _simd_u8x64_insert_x1_safe(X,I,Y) (reinterpret_cast<_simd_u8x64*>(&X)[I] = Y)
#ifdef _simd_u8x64_insert_x1_
#define _simd_u8x64_insert_x1(X,I,Y) _simd_u8x64_insert_x1_(X,I,Y)
#define _simd_u8x64__insert_x1_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_insert_x1_instruction_set>()
#else
#define _simd_u8x64_insert_x1(X,I,Y) _simd_u8x64_insert_x1_safe(X,I,Y)
#define _simd_u8x64__insert_x1_enable() true
#endif _simd_u8x64_insert_x1_

#define _simd_u8x64_extract_x2_safe(X,I) (reinterpret_cast<const _simd_u8x64*>(&X)[I])
#ifdef _simd_u8x64_extract_x2_
#define _simd_u8x64_extract_x2(X,I) _simd_u8x64_extract_x2_(X,I)
#define _simd_u8x64__extract_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_extract_x2_instruction_set>()
#else
#define _simd_u8x64_extract_x2(X,I) _simd_u8x64_extract_x2_safe(X,I)
#define _simd_u8x64__extract_x2_enable() true
#endif _simd_u8x64_extract_x2_

#define _simd_u8x64_insert_x2_safe(X,I,Y) (reinterpret_cast<_simd_u8x64*>(&X)[I] = Y)
#ifdef _simd_u8x64_insert_x2_
#define _simd_u8x64_insert_x2(X,I,Y) _simd_u8x64_insert_x2_(X,I,Y)
#define _simd_u8x64__insert_x2_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_insert_x2_instruction_set>()
#else
#define _simd_u8x64_insert_x2(X,I,Y) _simd_u8x64_insert_x2_safe(X,I,Y)
#define _simd_u8x64__insert_x2_enable() true
#endif _simd_u8x64_insert_x2_

#define _simd_u8x64_extract_x4_safe(X,I) (reinterpret_cast<const _simd_u8x64*>(&X)[I])
#ifdef _simd_u8x64_extract_x4_
#define _simd_u8x64_extract_x4(X,I) _simd_u8x64_extract_x4_(X,I)
#define _simd_u8x64__extract_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_extract_x4_instruction_set>()
#else
#define _simd_u8x64_extract_x4(X,I) _simd_u8x64_extract_x4_safe(X,I)
#define _simd_u8x64__extract_x4_enable() true
#endif _simd_u8x64_extract_x4_

#define _simd_u8x64_insert_x4_safe(X,I,Y) (reinterpret_cast<_simd_u8x64*>(&X)[I] = Y)
#ifdef _simd_u8x64_insert_x4_
#define _simd_u8x64_insert_x4(X,I,Y) _simd_u8x64_insert_x4_(X,I,Y)
#define _simd_u8x64__insert_x4_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_insert_x4_instruction_set>()
#else
#define _simd_u8x64_insert_x4(X,I,Y) _simd_u8x64_insert_x4_safe(X,I,Y)
#define _simd_u8x64__insert_x4_enable() true
#endif _simd_u8x64_insert_x4_

#define _simd_u8x64_extract_x8_safe(X,I) (reinterpret_cast<const _simd_u8x64*>(&X)[I])
#ifdef _simd_u8x64_extract_x8_
#define _simd_u8x64_extract_x8(X,I) _simd_u8x64_extract_x8_(X,I)
#define _simd_u8x64__extract_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_extract_x8_instruction_set>()
#else
#define _simd_u8x64_extract_x8(X,I) _simd_u8x64_extract_x8_safe(X,I)
#define _simd_u8x64__extract_x8_enable() true
#endif _simd_u8x64_extract_x8_

#define _simd_u8x64_insert_x8_safe(X,I,Y) (reinterpret_cast<_simd_u8x64*>(&X)[I] = Y)
#ifdef _simd_u8x64_insert_x8_
#define _simd_u8x64_insert_x8(X,I,Y) _simd_u8x64_insert_x8_(X,I,Y)
#define _simd_u8x64__insert_x8_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_insert_x8_instruction_set>()
#else
#define _simd_u8x64_insert_x8(X,I,Y) _simd_u8x64_insert_x8_safe(X,I,Y)
#define _simd_u8x64__insert_x8_enable() true
#endif _simd_u8x64_insert_x8_

#define _simd_u8x64_extract_x16_safe(X,I) (reinterpret_cast<const _simd_u8x64*>(&X)[I])
#ifdef _simd_u8x64_extract_x16_
#define _simd_u8x64_extract_x16(X,I) _simd_u8x64_extract_x16_(X,I)
#define _simd_u8x64__extract_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_extract_x16_instruction_set>()
#else
#define _simd_u8x64_extract_x16(X,I) _simd_u8x64_extract_x16_safe(X,I)
#define _simd_u8x64__extract_x16_enable() true
#endif _simd_u8x64_extract_x16_

#define _simd_u8x64_insert_x16_safe(X,I,Y) (reinterpret_cast<_simd_u8x64*>(&X)[I] = Y)
#ifdef _simd_u8x64_insert_x16_
#define _simd_u8x64_insert_x16(X,I,Y) _simd_u8x64_insert_x16_(X,I,Y)
#define _simd_u8x64__insert_x16_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_insert_x16_instruction_set>()
#else
#define _simd_u8x64_insert_x16(X,I,Y) _simd_u8x64_insert_x16_safe(X,I,Y)
#define _simd_u8x64__insert_x16_enable() true
#endif _simd_u8x64_insert_x16_

#define _simd_u8x64_extract_x32_safe(X,I) (reinterpret_cast<const _simd_u8x64*>(&X)[I])
#ifdef _simd_u8x64_extract_x32_
#define _simd_u8x64_extract_x32(X,I) _simd_u8x64_extract_x32_(X,I)
#define _simd_u8x64__extract_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_extract_x32_instruction_set>()
#else
#define _simd_u8x64_extract_x32(X,I) _simd_u8x64_extract_x32_safe(X,I)
#define _simd_u8x64__extract_x32_enable() true
#endif _simd_u8x64_extract_x32_

#define _simd_u8x64_insert_x32_safe(X,I,Y) (reinterpret_cast<_simd_u8x64*>(&X)[I] = Y)
#ifdef _simd_u8x64_insert_x32_
#define _simd_u8x64_insert_x32(X,I,Y) _simd_u8x64_insert_x32_(X,I,Y)
#define _simd_u8x64__insert_x32_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_insert_x32_instruction_set>()
#else
#define _simd_u8x64_insert_x32(X,I,Y) _simd_u8x64_insert_x32_safe(X,I,Y)
#define _simd_u8x64__insert_x32_enable() true
#endif _simd_u8x64_insert_x32_

#define _simd_u8x64_extract_safe(X,I) _simd_u8x64_extract_x1_safe(X,I)
#define _simd_u8x64_extract(X,I) _simd_u8x64_extract_x1(X,I)
#define _simd_u8x64_extract_enable() _simd_u8x64_extract_x1_enable()

#define _simd_u8x64_insert_safe(X,I,Y) _simd_u8x64_insert_x1_safe(X,I,Y)
#define _simd_u8x64_insert(X,I,Y) _simd_u8x64_insert_x1(X,I,Y)
#define _simd_u8x64_insert_enable() _simd_u8x64_insert_x1_enable()

//#ifndef _simd_u8x64_splitlo
//	#define _simd_u8x64_splitlo(X) _simd_u8x32_extract_x32(X,0)
//	#define _simd_u8x64_splitlo_enable() _simd_u8x32_extract_x32_enable()
//#endif

//#ifndef _simd_u8x64_splithi
//	#define _simd_u8x64_splithi(X) _simd_u8x32_extract_x32(X,1)
//	#define _simd_u8x64_splithi_enable() _simd_u8x32_extract_x32_enable()
//#endif

//#ifndef _simd_u8x64_combine
//	#define _simd_u8x64_combine(X,Y) _simd_u8x64_insert_x32(_simd_u8x64_insert_x32(_simd_u8x64_fill_undefined(), 0, X), 1, Y)
//	#define _simd_u8x64_combine_enable() (_simd_u8x64_insert_x32_enable() && _simd_u8x64_fill_undefined_enable())
//#endif

