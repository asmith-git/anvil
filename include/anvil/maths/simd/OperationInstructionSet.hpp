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

#ifdef _simd_f64x2_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_add_instruction_set };
	};
#endif
#ifdef _simd_f64x2_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_sub_instruction_set };
	};
#endif
#ifdef _simd_f64x2_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_mul_instruction_set };
	};
#endif
#ifdef _simd_f64x2_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_div_instruction_set };
	};
#endif
#ifdef _simd_f64x2_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_min_instruction_set };
	};
#endif
#ifdef _simd_f64x2_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_max_instruction_set };
	};
#endif
#ifdef _simd_f64x2_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_f64x2_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_cmpne_instruction_set };
	};
#endif
#ifdef _simd_f64x2_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_cmplt_instruction_set };
	};
#endif
#ifdef _simd_f64x2_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_f64x2_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_cmple_instruction_set };
	};
#endif
#ifdef _simd_f64x2_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_cmpge_instruction_set };
	};
#endif
#ifdef _simd_f64x2_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_and_instruction_set };
	};
#endif
#ifdef _simd_f64x2_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_or_instruction_set };
	};
#endif
#ifdef _simd_f64x2_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_xor_instruction_set };
	};
#endif
#ifdef _simd_f64x4_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_add_instruction_set };
	};
#endif
#ifdef _simd_f64x4_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_sub_instruction_set };
	};
#endif
#ifdef _simd_f64x4_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_mul_instruction_set };
	};
#endif
#ifdef _simd_f64x4_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_div_instruction_set };
	};
#endif
#ifdef _simd_f64x4_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_min_instruction_set };
	};
#endif
#ifdef _simd_f64x4_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_max_instruction_set };
	};
#endif
#ifdef _simd_f64x4_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_f64x4_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_cmpne_instruction_set };
	};
#endif
#ifdef _simd_f64x4_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_cmplt_instruction_set };
	};
#endif
#ifdef _simd_f64x4_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_f64x4_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_cmple_instruction_set };
	};
#endif
#ifdef _simd_f64x4_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_cmpge_instruction_set };
	};
#endif
#ifdef _simd_f64x4_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_and_instruction_set };
	};
#endif
#ifdef _simd_f64x4_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_or_instruction_set };
	};
#endif
#ifdef _simd_f64x4_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_xor_instruction_set };
	};
#endif
#ifdef _simd_f64x8_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_add_instruction_set };
	};
#endif
#ifdef _simd_f64x8_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_sub_instruction_set };
	};
#endif
#ifdef _simd_f64x8_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_mul_instruction_set };
	};
#endif
#ifdef _simd_f64x8_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_div_instruction_set };
	};
#endif
#ifdef _simd_f64x8_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_min_instruction_set };
	};
#endif
#ifdef _simd_f64x8_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_max_instruction_set };
	};
#endif
#ifdef _simd_f64x8_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_f64x8_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_cmpne_instruction_set };
	};
#endif
#ifdef _simd_f64x8_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_cmplt_instruction_set };
	};
#endif
#ifdef _simd_f64x8_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_f64x8_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_cmple_instruction_set };
	};
#endif
#ifdef _simd_f64x8_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_cmpge_instruction_set };
	};
#endif
#ifdef _simd_f64x8_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_and_instruction_set };
	};
#endif
#ifdef _simd_f64x8_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_or_instruction_set };
	};
#endif
#ifdef _simd_f64x8_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_xor_instruction_set };
	};
#endif
#ifdef _simd_f64x16_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_add_instruction_set };
	};
#endif
#ifdef _simd_f64x16_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_sub_instruction_set };
	};
#endif
#ifdef _simd_f64x16_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_mul_instruction_set };
	};
#endif
#ifdef _simd_f64x16_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_div_instruction_set };
	};
#endif
#ifdef _simd_f64x16_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_min_instruction_set };
	};
#endif
#ifdef _simd_f64x16_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_max_instruction_set };
	};
#endif
#ifdef _simd_f64x16_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_f64x16_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_cmpne_instruction_set };
	};
#endif
#ifdef _simd_f64x16_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_cmplt_instruction_set };
	};
#endif
#ifdef _simd_f64x16_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_f64x16_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_cmple_instruction_set };
	};
#endif
#ifdef _simd_f64x16_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_cmpge_instruction_set };
	};
#endif
#ifdef _simd_f64x16_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_and_instruction_set };
	};
#endif
#ifdef _simd_f64x16_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_or_instruction_set };
	};
#endif
#ifdef _simd_f64x16_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_xor_instruction_set };
	};
#endif
#ifdef _simd_f64x32_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_add_instruction_set };
	};
#endif
#ifdef _simd_f64x32_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_sub_instruction_set };
	};
#endif
#ifdef _simd_f64x32_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_mul_instruction_set };
	};
#endif
#ifdef _simd_f64x32_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_div_instruction_set };
	};
#endif
#ifdef _simd_f64x32_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_min_instruction_set };
	};
#endif
#ifdef _simd_f64x32_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_max_instruction_set };
	};
#endif
#ifdef _simd_f64x32_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_f64x32_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_cmpne_instruction_set };
	};
#endif
#ifdef _simd_f64x32_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_cmplt_instruction_set };
	};
#endif
#ifdef _simd_f64x32_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_f64x32_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_cmple_instruction_set };
	};
#endif
#ifdef _simd_f64x32_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_cmpge_instruction_set };
	};
#endif
#ifdef _simd_f64x32_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_and_instruction_set };
	};
#endif
#ifdef _simd_f64x32_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_or_instruction_set };
	};
#endif
#ifdef _simd_f64x32_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_xor_instruction_set };
	};
#endif
#ifdef _simd_f64x64_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_add_instruction_set };
	};
#endif
#ifdef _simd_f64x64_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_sub_instruction_set };
	};
#endif
#ifdef _simd_f64x64_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_mul_instruction_set };
	};
#endif
#ifdef _simd_f64x64_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_div_instruction_set };
	};
#endif
#ifdef _simd_f64x64_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_min_instruction_set };
	};
#endif
#ifdef _simd_f64x64_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_max_instruction_set };
	};
#endif
#ifdef _simd_f64x64_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_f64x64_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_cmpne_instruction_set };
	};
#endif
#ifdef _simd_f64x64_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_cmplt_instruction_set };
	};
#endif
#ifdef _simd_f64x64_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_f64x64_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_cmple_instruction_set };
	};
#endif
#ifdef _simd_f64x64_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_cmpge_instruction_set };
	};
#endif
#ifdef _simd_f64x64_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_and_instruction_set };
	};
#endif
#ifdef _simd_f64x64_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_or_instruction_set };
	};
#endif
#ifdef _simd_f64x64_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_xor_instruction_set };
	};
#endif
#ifdef _simd_f32x2_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_add_instruction_set };
	};
#endif
#ifdef _simd_f32x2_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_sub_instruction_set };
	};
#endif
#ifdef _simd_f32x2_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_mul_instruction_set };
	};
#endif
#ifdef _simd_f32x2_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_div_instruction_set };
	};
#endif
#ifdef _simd_f32x2_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_min_instruction_set };
	};
#endif
#ifdef _simd_f32x2_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_max_instruction_set };
	};
#endif
#ifdef _simd_f32x2_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_f32x2_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_cmpne_instruction_set };
	};
#endif
#ifdef _simd_f32x2_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_cmplt_instruction_set };
	};
#endif
#ifdef _simd_f32x2_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_f32x2_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_cmple_instruction_set };
	};
#endif
#ifdef _simd_f32x2_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_cmpge_instruction_set };
	};
#endif
#ifdef _simd_f32x2_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_and_instruction_set };
	};
#endif
#ifdef _simd_f32x2_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_or_instruction_set };
	};
#endif
#ifdef _simd_f32x2_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_xor_instruction_set };
	};
#endif
#ifdef _simd_f32x4_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_add_instruction_set };
	};
#endif
#ifdef _simd_f32x4_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_sub_instruction_set };
	};
#endif
#ifdef _simd_f32x4_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_mul_instruction_set };
	};
#endif
#ifdef _simd_f32x4_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_div_instruction_set };
	};
#endif
#ifdef _simd_f32x4_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_min_instruction_set };
	};
#endif
#ifdef _simd_f32x4_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_max_instruction_set };
	};
#endif
#ifdef _simd_f32x4_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_f32x4_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_cmpne_instruction_set };
	};
#endif
#ifdef _simd_f32x4_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_cmplt_instruction_set };
	};
#endif
#ifdef _simd_f32x4_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_f32x4_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_cmple_instruction_set };
	};
#endif
#ifdef _simd_f32x4_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_cmpge_instruction_set };
	};
#endif
#ifdef _simd_f32x4_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_and_instruction_set };
	};
#endif
#ifdef _simd_f32x4_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_or_instruction_set };
	};
#endif
#ifdef _simd_f32x4_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_xor_instruction_set };
	};
#endif
#ifdef _simd_f32x8_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_add_instruction_set };
	};
#endif
#ifdef _simd_f32x8_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_sub_instruction_set };
	};
#endif
#ifdef _simd_f32x8_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_mul_instruction_set };
	};
#endif
#ifdef _simd_f32x8_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_div_instruction_set };
	};
#endif
#ifdef _simd_f32x8_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_min_instruction_set };
	};
#endif
#ifdef _simd_f32x8_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_max_instruction_set };
	};
#endif
#ifdef _simd_f32x8_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_f32x8_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_cmpne_instruction_set };
	};
#endif
#ifdef _simd_f32x8_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_cmplt_instruction_set };
	};
#endif
#ifdef _simd_f32x8_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_f32x8_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_cmple_instruction_set };
	};
#endif
#ifdef _simd_f32x8_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_cmpge_instruction_set };
	};
#endif
#ifdef _simd_f32x8_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_and_instruction_set };
	};
#endif
#ifdef _simd_f32x8_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_or_instruction_set };
	};
#endif
#ifdef _simd_f32x8_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_xor_instruction_set };
	};
#endif
#ifdef _simd_f32x16_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_add_instruction_set };
	};
#endif
#ifdef _simd_f32x16_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_sub_instruction_set };
	};
#endif
#ifdef _simd_f32x16_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_mul_instruction_set };
	};
#endif
#ifdef _simd_f32x16_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_div_instruction_set };
	};
#endif
#ifdef _simd_f32x16_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_min_instruction_set };
	};
#endif
#ifdef _simd_f32x16_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_max_instruction_set };
	};
#endif
#ifdef _simd_f32x16_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_f32x16_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_cmpne_instruction_set };
	};
#endif
#ifdef _simd_f32x16_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_cmplt_instruction_set };
	};
#endif
#ifdef _simd_f32x16_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_f32x16_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_cmple_instruction_set };
	};
#endif
#ifdef _simd_f32x16_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_cmpge_instruction_set };
	};
#endif
#ifdef _simd_f32x16_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_and_instruction_set };
	};
#endif
#ifdef _simd_f32x16_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_or_instruction_set };
	};
#endif
#ifdef _simd_f32x16_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_xor_instruction_set };
	};
#endif
#ifdef _simd_f32x32_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_add_instruction_set };
	};
#endif
#ifdef _simd_f32x32_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_sub_instruction_set };
	};
#endif
#ifdef _simd_f32x32_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_mul_instruction_set };
	};
#endif
#ifdef _simd_f32x32_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_div_instruction_set };
	};
#endif
#ifdef _simd_f32x32_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_min_instruction_set };
	};
#endif
#ifdef _simd_f32x32_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_max_instruction_set };
	};
#endif
#ifdef _simd_f32x32_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_f32x32_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_cmpne_instruction_set };
	};
#endif
#ifdef _simd_f32x32_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_cmplt_instruction_set };
	};
#endif
#ifdef _simd_f32x32_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_f32x32_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_cmple_instruction_set };
	};
#endif
#ifdef _simd_f32x32_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_cmpge_instruction_set };
	};
#endif
#ifdef _simd_f32x32_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_and_instruction_set };
	};
#endif
#ifdef _simd_f32x32_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_or_instruction_set };
	};
#endif
#ifdef _simd_f32x32_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_xor_instruction_set };
	};
#endif
#ifdef _simd_f32x64_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_add_instruction_set };
	};
#endif
#ifdef _simd_f32x64_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_sub_instruction_set };
	};
#endif
#ifdef _simd_f32x64_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_mul_instruction_set };
	};
#endif
#ifdef _simd_f32x64_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_div_instruction_set };
	};
#endif
#ifdef _simd_f32x64_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_min_instruction_set };
	};
#endif
#ifdef _simd_f32x64_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_max_instruction_set };
	};
#endif
#ifdef _simd_f32x64_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_f32x64_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_cmpne_instruction_set };
	};
#endif
#ifdef _simd_f32x64_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_cmplt_instruction_set };
	};
#endif
#ifdef _simd_f32x64_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_f32x64_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_cmple_instruction_set };
	};
#endif
#ifdef _simd_f32x64_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_cmpge_instruction_set };
	};
#endif
#ifdef _simd_f32x64_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_and_instruction_set };
	};
#endif
#ifdef _simd_f32x64_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_or_instruction_set };
	};
#endif
#ifdef _simd_f32x64_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_xor_instruction_set };
	};
#endif
#ifdef _simd_s64x2_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_add_instruction_set };
	};
#endif
#ifdef _simd_s64x2_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_sub_instruction_set };
	};
#endif
#ifdef _simd_s64x2_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_mul_instruction_set };
	};
#endif
#ifdef _simd_s64x2_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_div_instruction_set };
	};
#endif
#ifdef _simd_s64x2_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_min_instruction_set };
	};
#endif
#ifdef _simd_s64x2_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_max_instruction_set };
	};
#endif
#ifdef _simd_s64x2_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_s64x2_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_cmpne_instruction_set };
	};
#endif
#ifdef _simd_s64x2_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_cmplt_instruction_set };
	};
#endif
#ifdef _simd_s64x2_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_s64x2_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_cmple_instruction_set };
	};
#endif
#ifdef _simd_s64x2_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_cmpge_instruction_set };
	};
#endif
#ifdef _simd_s64x2_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_and_instruction_set };
	};
#endif
#ifdef _simd_s64x2_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_or_instruction_set };
	};
#endif
#ifdef _simd_s64x2_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_xor_instruction_set };
	};
#endif
#ifdef _simd_s64x4_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_add_instruction_set };
	};
#endif
#ifdef _simd_s64x4_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_sub_instruction_set };
	};
#endif
#ifdef _simd_s64x4_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_mul_instruction_set };
	};
#endif
#ifdef _simd_s64x4_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_div_instruction_set };
	};
#endif
#ifdef _simd_s64x4_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_min_instruction_set };
	};
#endif
#ifdef _simd_s64x4_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_max_instruction_set };
	};
#endif
#ifdef _simd_s64x4_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_s64x4_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_cmpne_instruction_set };
	};
#endif
#ifdef _simd_s64x4_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_cmplt_instruction_set };
	};
#endif
#ifdef _simd_s64x4_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_s64x4_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_cmple_instruction_set };
	};
#endif
#ifdef _simd_s64x4_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_cmpge_instruction_set };
	};
#endif
#ifdef _simd_s64x4_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_and_instruction_set };
	};
#endif
#ifdef _simd_s64x4_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_or_instruction_set };
	};
#endif
#ifdef _simd_s64x4_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_xor_instruction_set };
	};
#endif
#ifdef _simd_s64x8_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_add_instruction_set };
	};
#endif
#ifdef _simd_s64x8_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_sub_instruction_set };
	};
#endif
#ifdef _simd_s64x8_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_mul_instruction_set };
	};
#endif
#ifdef _simd_s64x8_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_div_instruction_set };
	};
#endif
#ifdef _simd_s64x8_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_min_instruction_set };
	};
#endif
#ifdef _simd_s64x8_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_max_instruction_set };
	};
#endif
#ifdef _simd_s64x8_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_s64x8_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_cmpne_instruction_set };
	};
#endif
#ifdef _simd_s64x8_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_cmplt_instruction_set };
	};
#endif
#ifdef _simd_s64x8_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_s64x8_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_cmple_instruction_set };
	};
#endif
#ifdef _simd_s64x8_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_cmpge_instruction_set };
	};
#endif
#ifdef _simd_s64x8_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_and_instruction_set };
	};
#endif
#ifdef _simd_s64x8_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_or_instruction_set };
	};
#endif
#ifdef _simd_s64x8_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_xor_instruction_set };
	};
#endif
#ifdef _simd_s64x16_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_add_instruction_set };
	};
#endif
#ifdef _simd_s64x16_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_sub_instruction_set };
	};
#endif
#ifdef _simd_s64x16_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_mul_instruction_set };
	};
#endif
#ifdef _simd_s64x16_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_div_instruction_set };
	};
#endif
#ifdef _simd_s64x16_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_min_instruction_set };
	};
#endif
#ifdef _simd_s64x16_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_max_instruction_set };
	};
#endif
#ifdef _simd_s64x16_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_s64x16_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_cmpne_instruction_set };
	};
#endif
#ifdef _simd_s64x16_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_cmplt_instruction_set };
	};
#endif
#ifdef _simd_s64x16_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_s64x16_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_cmple_instruction_set };
	};
#endif
#ifdef _simd_s64x16_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_cmpge_instruction_set };
	};
#endif
#ifdef _simd_s64x16_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_and_instruction_set };
	};
#endif
#ifdef _simd_s64x16_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_or_instruction_set };
	};
#endif
#ifdef _simd_s64x16_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_xor_instruction_set };
	};
#endif
#ifdef _simd_s64x32_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_add_instruction_set };
	};
#endif
#ifdef _simd_s64x32_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_sub_instruction_set };
	};
#endif
#ifdef _simd_s64x32_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_mul_instruction_set };
	};
#endif
#ifdef _simd_s64x32_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_div_instruction_set };
	};
#endif
#ifdef _simd_s64x32_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_min_instruction_set };
	};
#endif
#ifdef _simd_s64x32_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_max_instruction_set };
	};
#endif
#ifdef _simd_s64x32_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_s64x32_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_cmpne_instruction_set };
	};
#endif
#ifdef _simd_s64x32_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_cmplt_instruction_set };
	};
#endif
#ifdef _simd_s64x32_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_s64x32_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_cmple_instruction_set };
	};
#endif
#ifdef _simd_s64x32_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_cmpge_instruction_set };
	};
#endif
#ifdef _simd_s64x32_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_and_instruction_set };
	};
#endif
#ifdef _simd_s64x32_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_or_instruction_set };
	};
#endif
#ifdef _simd_s64x32_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_xor_instruction_set };
	};
#endif
#ifdef _simd_s64x64_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_add_instruction_set };
	};
#endif
#ifdef _simd_s64x64_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_sub_instruction_set };
	};
#endif
#ifdef _simd_s64x64_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_mul_instruction_set };
	};
#endif
#ifdef _simd_s64x64_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_div_instruction_set };
	};
#endif
#ifdef _simd_s64x64_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_min_instruction_set };
	};
#endif
#ifdef _simd_s64x64_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_max_instruction_set };
	};
#endif
#ifdef _simd_s64x64_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_s64x64_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_cmpne_instruction_set };
	};
#endif
#ifdef _simd_s64x64_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_cmplt_instruction_set };
	};
#endif
#ifdef _simd_s64x64_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_s64x64_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_cmple_instruction_set };
	};
#endif
#ifdef _simd_s64x64_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_cmpge_instruction_set };
	};
#endif
#ifdef _simd_s64x64_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_and_instruction_set };
	};
#endif
#ifdef _simd_s64x64_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_or_instruction_set };
	};
#endif
#ifdef _simd_s64x64_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_xor_instruction_set };
	};
#endif
#ifdef _simd_u64x2_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_add_instruction_set };
	};
#endif
#ifdef _simd_u64x2_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_sub_instruction_set };
	};
#endif
#ifdef _simd_u64x2_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_mul_instruction_set };
	};
#endif
#ifdef _simd_u64x2_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_div_instruction_set };
	};
#endif
#ifdef _simd_u64x2_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_min_instruction_set };
	};
#endif
#ifdef _simd_u64x2_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_max_instruction_set };
	};
#endif
#ifdef _simd_u64x2_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_u64x2_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_cmpne_instruction_set };
	};
#endif
#ifdef _simd_u64x2_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_cmplt_instruction_set };
	};
#endif
#ifdef _simd_u64x2_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_u64x2_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_cmple_instruction_set };
	};
#endif
#ifdef _simd_u64x2_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_cmpge_instruction_set };
	};
#endif
#ifdef _simd_u64x2_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_and_instruction_set };
	};
#endif
#ifdef _simd_u64x2_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_or_instruction_set };
	};
#endif
#ifdef _simd_u64x2_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_xor_instruction_set };
	};
#endif
#ifdef _simd_u64x4_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_add_instruction_set };
	};
#endif
#ifdef _simd_u64x4_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_sub_instruction_set };
	};
#endif
#ifdef _simd_u64x4_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_mul_instruction_set };
	};
#endif
#ifdef _simd_u64x4_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_div_instruction_set };
	};
#endif
#ifdef _simd_u64x4_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_min_instruction_set };
	};
#endif
#ifdef _simd_u64x4_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_max_instruction_set };
	};
#endif
#ifdef _simd_u64x4_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_u64x4_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_cmpne_instruction_set };
	};
#endif
#ifdef _simd_u64x4_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_cmplt_instruction_set };
	};
#endif
#ifdef _simd_u64x4_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_u64x4_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_cmple_instruction_set };
	};
#endif
#ifdef _simd_u64x4_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_cmpge_instruction_set };
	};
#endif
#ifdef _simd_u64x4_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_and_instruction_set };
	};
#endif
#ifdef _simd_u64x4_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_or_instruction_set };
	};
#endif
#ifdef _simd_u64x4_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_xor_instruction_set };
	};
#endif
#ifdef _simd_u64x8_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_add_instruction_set };
	};
#endif
#ifdef _simd_u64x8_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_sub_instruction_set };
	};
#endif
#ifdef _simd_u64x8_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_mul_instruction_set };
	};
#endif
#ifdef _simd_u64x8_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_div_instruction_set };
	};
#endif
#ifdef _simd_u64x8_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_min_instruction_set };
	};
#endif
#ifdef _simd_u64x8_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_max_instruction_set };
	};
#endif
#ifdef _simd_u64x8_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_u64x8_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_cmpne_instruction_set };
	};
#endif
#ifdef _simd_u64x8_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_cmplt_instruction_set };
	};
#endif
#ifdef _simd_u64x8_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_u64x8_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_cmple_instruction_set };
	};
#endif
#ifdef _simd_u64x8_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_cmpge_instruction_set };
	};
#endif
#ifdef _simd_u64x8_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_and_instruction_set };
	};
#endif
#ifdef _simd_u64x8_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_or_instruction_set };
	};
#endif
#ifdef _simd_u64x8_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_xor_instruction_set };
	};
#endif
#ifdef _simd_u64x16_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_add_instruction_set };
	};
#endif
#ifdef _simd_u64x16_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_sub_instruction_set };
	};
#endif
#ifdef _simd_u64x16_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_mul_instruction_set };
	};
#endif
#ifdef _simd_u64x16_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_div_instruction_set };
	};
#endif
#ifdef _simd_u64x16_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_min_instruction_set };
	};
#endif
#ifdef _simd_u64x16_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_max_instruction_set };
	};
#endif
#ifdef _simd_u64x16_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_u64x16_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_cmpne_instruction_set };
	};
#endif
#ifdef _simd_u64x16_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_cmplt_instruction_set };
	};
#endif
#ifdef _simd_u64x16_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_u64x16_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_cmple_instruction_set };
	};
#endif
#ifdef _simd_u64x16_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_cmpge_instruction_set };
	};
#endif
#ifdef _simd_u64x16_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_and_instruction_set };
	};
#endif
#ifdef _simd_u64x16_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_or_instruction_set };
	};
#endif
#ifdef _simd_u64x16_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_xor_instruction_set };
	};
#endif
#ifdef _simd_u64x32_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_add_instruction_set };
	};
#endif
#ifdef _simd_u64x32_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_sub_instruction_set };
	};
#endif
#ifdef _simd_u64x32_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_mul_instruction_set };
	};
#endif
#ifdef _simd_u64x32_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_div_instruction_set };
	};
#endif
#ifdef _simd_u64x32_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_min_instruction_set };
	};
#endif
#ifdef _simd_u64x32_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_max_instruction_set };
	};
#endif
#ifdef _simd_u64x32_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_u64x32_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_cmpne_instruction_set };
	};
#endif
#ifdef _simd_u64x32_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_cmplt_instruction_set };
	};
#endif
#ifdef _simd_u64x32_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_u64x32_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_cmple_instruction_set };
	};
#endif
#ifdef _simd_u64x32_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_cmpge_instruction_set };
	};
#endif
#ifdef _simd_u64x32_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_and_instruction_set };
	};
#endif
#ifdef _simd_u64x32_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_or_instruction_set };
	};
#endif
#ifdef _simd_u64x32_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_xor_instruction_set };
	};
#endif
#ifdef _simd_u64x64_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_add_instruction_set };
	};
#endif
#ifdef _simd_u64x64_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_sub_instruction_set };
	};
#endif
#ifdef _simd_u64x64_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_mul_instruction_set };
	};
#endif
#ifdef _simd_u64x64_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_div_instruction_set };
	};
#endif
#ifdef _simd_u64x64_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_min_instruction_set };
	};
#endif
#ifdef _simd_u64x64_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_max_instruction_set };
	};
#endif
#ifdef _simd_u64x64_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_u64x64_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_cmpne_instruction_set };
	};
#endif
#ifdef _simd_u64x64_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_cmplt_instruction_set };
	};
#endif
#ifdef _simd_u64x64_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_u64x64_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_cmple_instruction_set };
	};
#endif
#ifdef _simd_u64x64_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_cmpge_instruction_set };
	};
#endif
#ifdef _simd_u64x64_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_and_instruction_set };
	};
#endif
#ifdef _simd_u64x64_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_or_instruction_set };
	};
#endif
#ifdef _simd_u64x64_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_xor_instruction_set };
	};
#endif
#ifdef _simd_s32x2_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_add_instruction_set };
	};
#endif
#ifdef _simd_s32x2_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_sub_instruction_set };
	};
#endif
#ifdef _simd_s32x2_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_mul_instruction_set };
	};
#endif
#ifdef _simd_s32x2_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_div_instruction_set };
	};
#endif
#ifdef _simd_s32x2_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_min_instruction_set };
	};
#endif
#ifdef _simd_s32x2_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_max_instruction_set };
	};
#endif
#ifdef _simd_s32x2_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_s32x2_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_cmpne_instruction_set };
	};
#endif
#ifdef _simd_s32x2_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_cmplt_instruction_set };
	};
#endif
#ifdef _simd_s32x2_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_s32x2_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_cmple_instruction_set };
	};
#endif
#ifdef _simd_s32x2_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_cmpge_instruction_set };
	};
#endif
#ifdef _simd_s32x2_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_and_instruction_set };
	};
#endif
#ifdef _simd_s32x2_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_or_instruction_set };
	};
#endif
#ifdef _simd_s32x2_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_xor_instruction_set };
	};
#endif
#ifdef _simd_s32x4_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_add_instruction_set };
	};
#endif
#ifdef _simd_s32x4_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_sub_instruction_set };
	};
#endif
#ifdef _simd_s32x4_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_mul_instruction_set };
	};
#endif
#ifdef _simd_s32x4_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_div_instruction_set };
	};
#endif
#ifdef _simd_s32x4_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_min_instruction_set };
	};
#endif
#ifdef _simd_s32x4_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_max_instruction_set };
	};
#endif
#ifdef _simd_s32x4_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_s32x4_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_cmpne_instruction_set };
	};
#endif
#ifdef _simd_s32x4_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_cmplt_instruction_set };
	};
#endif
#ifdef _simd_s32x4_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_s32x4_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_cmple_instruction_set };
	};
#endif
#ifdef _simd_s32x4_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_cmpge_instruction_set };
	};
#endif
#ifdef _simd_s32x4_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_and_instruction_set };
	};
#endif
#ifdef _simd_s32x4_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_or_instruction_set };
	};
#endif
#ifdef _simd_s32x4_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_xor_instruction_set };
	};
#endif
#ifdef _simd_s32x8_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_add_instruction_set };
	};
#endif
#ifdef _simd_s32x8_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_sub_instruction_set };
	};
#endif
#ifdef _simd_s32x8_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_mul_instruction_set };
	};
#endif
#ifdef _simd_s32x8_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_div_instruction_set };
	};
#endif
#ifdef _simd_s32x8_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_min_instruction_set };
	};
#endif
#ifdef _simd_s32x8_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_max_instruction_set };
	};
#endif
#ifdef _simd_s32x8_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_s32x8_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_cmpne_instruction_set };
	};
#endif
#ifdef _simd_s32x8_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_cmplt_instruction_set };
	};
#endif
#ifdef _simd_s32x8_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_s32x8_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_cmple_instruction_set };
	};
#endif
#ifdef _simd_s32x8_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_cmpge_instruction_set };
	};
#endif
#ifdef _simd_s32x8_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_and_instruction_set };
	};
#endif
#ifdef _simd_s32x8_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_or_instruction_set };
	};
#endif
#ifdef _simd_s32x8_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_xor_instruction_set };
	};
#endif
#ifdef _simd_s32x16_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_add_instruction_set };
	};
#endif
#ifdef _simd_s32x16_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_sub_instruction_set };
	};
#endif
#ifdef _simd_s32x16_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_mul_instruction_set };
	};
#endif
#ifdef _simd_s32x16_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_div_instruction_set };
	};
#endif
#ifdef _simd_s32x16_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_min_instruction_set };
	};
#endif
#ifdef _simd_s32x16_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_max_instruction_set };
	};
#endif
#ifdef _simd_s32x16_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_s32x16_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_cmpne_instruction_set };
	};
#endif
#ifdef _simd_s32x16_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_cmplt_instruction_set };
	};
#endif
#ifdef _simd_s32x16_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_s32x16_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_cmple_instruction_set };
	};
#endif
#ifdef _simd_s32x16_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_cmpge_instruction_set };
	};
#endif
#ifdef _simd_s32x16_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_and_instruction_set };
	};
#endif
#ifdef _simd_s32x16_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_or_instruction_set };
	};
#endif
#ifdef _simd_s32x16_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_xor_instruction_set };
	};
#endif
#ifdef _simd_s32x32_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_add_instruction_set };
	};
#endif
#ifdef _simd_s32x32_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_sub_instruction_set };
	};
#endif
#ifdef _simd_s32x32_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_mul_instruction_set };
	};
#endif
#ifdef _simd_s32x32_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_div_instruction_set };
	};
#endif
#ifdef _simd_s32x32_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_min_instruction_set };
	};
#endif
#ifdef _simd_s32x32_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_max_instruction_set };
	};
#endif
#ifdef _simd_s32x32_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_s32x32_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_cmpne_instruction_set };
	};
#endif
#ifdef _simd_s32x32_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_cmplt_instruction_set };
	};
#endif
#ifdef _simd_s32x32_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_s32x32_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_cmple_instruction_set };
	};
#endif
#ifdef _simd_s32x32_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_cmpge_instruction_set };
	};
#endif
#ifdef _simd_s32x32_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_and_instruction_set };
	};
#endif
#ifdef _simd_s32x32_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_or_instruction_set };
	};
#endif
#ifdef _simd_s32x32_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_xor_instruction_set };
	};
#endif
#ifdef _simd_s32x64_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_add_instruction_set };
	};
#endif
#ifdef _simd_s32x64_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_sub_instruction_set };
	};
#endif
#ifdef _simd_s32x64_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_mul_instruction_set };
	};
#endif
#ifdef _simd_s32x64_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_div_instruction_set };
	};
#endif
#ifdef _simd_s32x64_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_min_instruction_set };
	};
#endif
#ifdef _simd_s32x64_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_max_instruction_set };
	};
#endif
#ifdef _simd_s32x64_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_s32x64_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_cmpne_instruction_set };
	};
#endif
#ifdef _simd_s32x64_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_cmplt_instruction_set };
	};
#endif
#ifdef _simd_s32x64_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_s32x64_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_cmple_instruction_set };
	};
#endif
#ifdef _simd_s32x64_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_cmpge_instruction_set };
	};
#endif
#ifdef _simd_s32x64_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_and_instruction_set };
	};
#endif
#ifdef _simd_s32x64_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_or_instruction_set };
	};
#endif
#ifdef _simd_s32x64_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_xor_instruction_set };
	};
#endif
#ifdef _simd_u32x2_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_add_instruction_set };
	};
#endif
#ifdef _simd_u32x2_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_sub_instruction_set };
	};
#endif
#ifdef _simd_u32x2_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_mul_instruction_set };
	};
#endif
#ifdef _simd_u32x2_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_div_instruction_set };
	};
#endif
#ifdef _simd_u32x2_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_min_instruction_set };
	};
#endif
#ifdef _simd_u32x2_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_max_instruction_set };
	};
#endif
#ifdef _simd_u32x2_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_u32x2_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_cmpne_instruction_set };
	};
#endif
#ifdef _simd_u32x2_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_cmplt_instruction_set };
	};
#endif
#ifdef _simd_u32x2_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_u32x2_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_cmple_instruction_set };
	};
#endif
#ifdef _simd_u32x2_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_cmpge_instruction_set };
	};
#endif
#ifdef _simd_u32x2_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_and_instruction_set };
	};
#endif
#ifdef _simd_u32x2_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_or_instruction_set };
	};
#endif
#ifdef _simd_u32x2_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_xor_instruction_set };
	};
#endif
#ifdef _simd_u32x4_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_add_instruction_set };
	};
#endif
#ifdef _simd_u32x4_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_sub_instruction_set };
	};
#endif
#ifdef _simd_u32x4_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_mul_instruction_set };
	};
#endif
#ifdef _simd_u32x4_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_div_instruction_set };
	};
#endif
#ifdef _simd_u32x4_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_min_instruction_set };
	};
#endif
#ifdef _simd_u32x4_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_max_instruction_set };
	};
#endif
#ifdef _simd_u32x4_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_u32x4_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_cmpne_instruction_set };
	};
#endif
#ifdef _simd_u32x4_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_cmplt_instruction_set };
	};
#endif
#ifdef _simd_u32x4_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_u32x4_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_cmple_instruction_set };
	};
#endif
#ifdef _simd_u32x4_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_cmpge_instruction_set };
	};
#endif
#ifdef _simd_u32x4_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_and_instruction_set };
	};
#endif
#ifdef _simd_u32x4_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_or_instruction_set };
	};
#endif
#ifdef _simd_u32x4_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_xor_instruction_set };
	};
#endif
#ifdef _simd_u32x8_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_add_instruction_set };
	};
#endif
#ifdef _simd_u32x8_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_sub_instruction_set };
	};
#endif
#ifdef _simd_u32x8_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_mul_instruction_set };
	};
#endif
#ifdef _simd_u32x8_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_div_instruction_set };
	};
#endif
#ifdef _simd_u32x8_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_min_instruction_set };
	};
#endif
#ifdef _simd_u32x8_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_max_instruction_set };
	};
#endif
#ifdef _simd_u32x8_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_u32x8_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_cmpne_instruction_set };
	};
#endif
#ifdef _simd_u32x8_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_cmplt_instruction_set };
	};
#endif
#ifdef _simd_u32x8_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_u32x8_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_cmple_instruction_set };
	};
#endif
#ifdef _simd_u32x8_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_cmpge_instruction_set };
	};
#endif
#ifdef _simd_u32x8_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_and_instruction_set };
	};
#endif
#ifdef _simd_u32x8_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_or_instruction_set };
	};
#endif
#ifdef _simd_u32x8_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_xor_instruction_set };
	};
#endif
#ifdef _simd_u32x16_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_add_instruction_set };
	};
#endif
#ifdef _simd_u32x16_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_sub_instruction_set };
	};
#endif
#ifdef _simd_u32x16_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_mul_instruction_set };
	};
#endif
#ifdef _simd_u32x16_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_div_instruction_set };
	};
#endif
#ifdef _simd_u32x16_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_min_instruction_set };
	};
#endif
#ifdef _simd_u32x16_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_max_instruction_set };
	};
#endif
#ifdef _simd_u32x16_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_u32x16_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_cmpne_instruction_set };
	};
#endif
#ifdef _simd_u32x16_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_cmplt_instruction_set };
	};
#endif
#ifdef _simd_u32x16_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_u32x16_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_cmple_instruction_set };
	};
#endif
#ifdef _simd_u32x16_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_cmpge_instruction_set };
	};
#endif
#ifdef _simd_u32x16_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_and_instruction_set };
	};
#endif
#ifdef _simd_u32x16_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_or_instruction_set };
	};
#endif
#ifdef _simd_u32x16_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_xor_instruction_set };
	};
#endif
#ifdef _simd_u32x32_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_add_instruction_set };
	};
#endif
#ifdef _simd_u32x32_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_sub_instruction_set };
	};
#endif
#ifdef _simd_u32x32_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_mul_instruction_set };
	};
#endif
#ifdef _simd_u32x32_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_div_instruction_set };
	};
#endif
#ifdef _simd_u32x32_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_min_instruction_set };
	};
#endif
#ifdef _simd_u32x32_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_max_instruction_set };
	};
#endif
#ifdef _simd_u32x32_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_u32x32_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_cmpne_instruction_set };
	};
#endif
#ifdef _simd_u32x32_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_cmplt_instruction_set };
	};
#endif
#ifdef _simd_u32x32_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_u32x32_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_cmple_instruction_set };
	};
#endif
#ifdef _simd_u32x32_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_cmpge_instruction_set };
	};
#endif
#ifdef _simd_u32x32_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_and_instruction_set };
	};
#endif
#ifdef _simd_u32x32_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_or_instruction_set };
	};
#endif
#ifdef _simd_u32x32_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_xor_instruction_set };
	};
#endif
#ifdef _simd_u32x64_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_add_instruction_set };
	};
#endif
#ifdef _simd_u32x64_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_sub_instruction_set };
	};
#endif
#ifdef _simd_u32x64_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_mul_instruction_set };
	};
#endif
#ifdef _simd_u32x64_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_div_instruction_set };
	};
#endif
#ifdef _simd_u32x64_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_min_instruction_set };
	};
#endif
#ifdef _simd_u32x64_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_max_instruction_set };
	};
#endif
#ifdef _simd_u32x64_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_u32x64_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_cmpne_instruction_set };
	};
#endif
#ifdef _simd_u32x64_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_cmplt_instruction_set };
	};
#endif
#ifdef _simd_u32x64_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_u32x64_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_cmple_instruction_set };
	};
#endif
#ifdef _simd_u32x64_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_cmpge_instruction_set };
	};
#endif
#ifdef _simd_u32x64_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_and_instruction_set };
	};
#endif
#ifdef _simd_u32x64_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_or_instruction_set };
	};
#endif
#ifdef _simd_u32x64_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_xor_instruction_set };
	};
#endif
#ifdef _simd_s16x2_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_add_instruction_set };
	};
#endif
#ifdef _simd_s16x2_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_sub_instruction_set };
	};
#endif
#ifdef _simd_s16x2_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_mul_instruction_set };
	};
#endif
#ifdef _simd_s16x2_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_div_instruction_set };
	};
#endif
#ifdef _simd_s16x2_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_min_instruction_set };
	};
#endif
#ifdef _simd_s16x2_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_max_instruction_set };
	};
#endif
#ifdef _simd_s16x2_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_s16x2_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_cmpne_instruction_set };
	};
#endif
#ifdef _simd_s16x2_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_cmplt_instruction_set };
	};
#endif
#ifdef _simd_s16x2_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_s16x2_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_cmple_instruction_set };
	};
#endif
#ifdef _simd_s16x2_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_cmpge_instruction_set };
	};
#endif
#ifdef _simd_s16x2_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_and_instruction_set };
	};
#endif
#ifdef _simd_s16x2_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_or_instruction_set };
	};
#endif
#ifdef _simd_s16x2_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_xor_instruction_set };
	};
#endif
#ifdef _simd_s16x4_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_add_instruction_set };
	};
#endif
#ifdef _simd_s16x4_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_sub_instruction_set };
	};
#endif
#ifdef _simd_s16x4_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_mul_instruction_set };
	};
#endif
#ifdef _simd_s16x4_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_div_instruction_set };
	};
#endif
#ifdef _simd_s16x4_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_min_instruction_set };
	};
#endif
#ifdef _simd_s16x4_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_max_instruction_set };
	};
#endif
#ifdef _simd_s16x4_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_s16x4_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_cmpne_instruction_set };
	};
#endif
#ifdef _simd_s16x4_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_cmplt_instruction_set };
	};
#endif
#ifdef _simd_s16x4_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_s16x4_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_cmple_instruction_set };
	};
#endif
#ifdef _simd_s16x4_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_cmpge_instruction_set };
	};
#endif
#ifdef _simd_s16x4_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_and_instruction_set };
	};
#endif
#ifdef _simd_s16x4_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_or_instruction_set };
	};
#endif
#ifdef _simd_s16x4_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_xor_instruction_set };
	};
#endif
#ifdef _simd_s16x8_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_add_instruction_set };
	};
#endif
#ifdef _simd_s16x8_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_sub_instruction_set };
	};
#endif
#ifdef _simd_s16x8_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_mul_instruction_set };
	};
#endif
#ifdef _simd_s16x8_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_div_instruction_set };
	};
#endif
#ifdef _simd_s16x8_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_min_instruction_set };
	};
#endif
#ifdef _simd_s16x8_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_max_instruction_set };
	};
#endif
#ifdef _simd_s16x8_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_s16x8_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_cmpne_instruction_set };
	};
#endif
#ifdef _simd_s16x8_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_cmplt_instruction_set };
	};
#endif
#ifdef _simd_s16x8_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_s16x8_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_cmple_instruction_set };
	};
#endif
#ifdef _simd_s16x8_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_cmpge_instruction_set };
	};
#endif
#ifdef _simd_s16x8_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_and_instruction_set };
	};
#endif
#ifdef _simd_s16x8_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_or_instruction_set };
	};
#endif
#ifdef _simd_s16x8_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_xor_instruction_set };
	};
#endif
#ifdef _simd_s16x16_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_add_instruction_set };
	};
#endif
#ifdef _simd_s16x16_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_sub_instruction_set };
	};
#endif
#ifdef _simd_s16x16_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_mul_instruction_set };
	};
#endif
#ifdef _simd_s16x16_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_div_instruction_set };
	};
#endif
#ifdef _simd_s16x16_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_min_instruction_set };
	};
#endif
#ifdef _simd_s16x16_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_max_instruction_set };
	};
#endif
#ifdef _simd_s16x16_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_s16x16_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_cmpne_instruction_set };
	};
#endif
#ifdef _simd_s16x16_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_cmplt_instruction_set };
	};
#endif
#ifdef _simd_s16x16_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_s16x16_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_cmple_instruction_set };
	};
#endif
#ifdef _simd_s16x16_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_cmpge_instruction_set };
	};
#endif
#ifdef _simd_s16x16_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_and_instruction_set };
	};
#endif
#ifdef _simd_s16x16_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_or_instruction_set };
	};
#endif
#ifdef _simd_s16x16_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_xor_instruction_set };
	};
#endif
#ifdef _simd_s16x32_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_add_instruction_set };
	};
#endif
#ifdef _simd_s16x32_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_sub_instruction_set };
	};
#endif
#ifdef _simd_s16x32_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_mul_instruction_set };
	};
#endif
#ifdef _simd_s16x32_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_div_instruction_set };
	};
#endif
#ifdef _simd_s16x32_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_min_instruction_set };
	};
#endif
#ifdef _simd_s16x32_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_max_instruction_set };
	};
#endif
#ifdef _simd_s16x32_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_s16x32_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_cmpne_instruction_set };
	};
#endif
#ifdef _simd_s16x32_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_cmplt_instruction_set };
	};
#endif
#ifdef _simd_s16x32_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_s16x32_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_cmple_instruction_set };
	};
#endif
#ifdef _simd_s16x32_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_cmpge_instruction_set };
	};
#endif
#ifdef _simd_s16x32_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_and_instruction_set };
	};
#endif
#ifdef _simd_s16x32_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_or_instruction_set };
	};
#endif
#ifdef _simd_s16x32_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_xor_instruction_set };
	};
#endif
#ifdef _simd_s16x64_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_add_instruction_set };
	};
#endif
#ifdef _simd_s16x64_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_sub_instruction_set };
	};
#endif
#ifdef _simd_s16x64_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_mul_instruction_set };
	};
#endif
#ifdef _simd_s16x64_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_div_instruction_set };
	};
#endif
#ifdef _simd_s16x64_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_min_instruction_set };
	};
#endif
#ifdef _simd_s16x64_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_max_instruction_set };
	};
#endif
#ifdef _simd_s16x64_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_s16x64_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_cmpne_instruction_set };
	};
#endif
#ifdef _simd_s16x64_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_cmplt_instruction_set };
	};
#endif
#ifdef _simd_s16x64_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_s16x64_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_cmple_instruction_set };
	};
#endif
#ifdef _simd_s16x64_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_cmpge_instruction_set };
	};
#endif
#ifdef _simd_s16x64_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_and_instruction_set };
	};
#endif
#ifdef _simd_s16x64_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_or_instruction_set };
	};
#endif
#ifdef _simd_s16x64_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_xor_instruction_set };
	};
#endif
#ifdef _simd_u16x2_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_add_instruction_set };
	};
#endif
#ifdef _simd_u16x2_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_sub_instruction_set };
	};
#endif
#ifdef _simd_u16x2_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_mul_instruction_set };
	};
#endif
#ifdef _simd_u16x2_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_div_instruction_set };
	};
#endif
#ifdef _simd_u16x2_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_min_instruction_set };
	};
#endif
#ifdef _simd_u16x2_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_max_instruction_set };
	};
#endif
#ifdef _simd_u16x2_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_u16x2_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_cmpne_instruction_set };
	};
#endif
#ifdef _simd_u16x2_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_cmplt_instruction_set };
	};
#endif
#ifdef _simd_u16x2_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_u16x2_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_cmple_instruction_set };
	};
#endif
#ifdef _simd_u16x2_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_cmpge_instruction_set };
	};
#endif
#ifdef _simd_u16x2_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_and_instruction_set };
	};
#endif
#ifdef _simd_u16x2_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_or_instruction_set };
	};
#endif
#ifdef _simd_u16x2_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_xor_instruction_set };
	};
#endif
#ifdef _simd_u16x4_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_add_instruction_set };
	};
#endif
#ifdef _simd_u16x4_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_sub_instruction_set };
	};
#endif
#ifdef _simd_u16x4_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_mul_instruction_set };
	};
#endif
#ifdef _simd_u16x4_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_div_instruction_set };
	};
#endif
#ifdef _simd_u16x4_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_min_instruction_set };
	};
#endif
#ifdef _simd_u16x4_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_max_instruction_set };
	};
#endif
#ifdef _simd_u16x4_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_u16x4_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_cmpne_instruction_set };
	};
#endif
#ifdef _simd_u16x4_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_cmplt_instruction_set };
	};
#endif
#ifdef _simd_u16x4_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_u16x4_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_cmple_instruction_set };
	};
#endif
#ifdef _simd_u16x4_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_cmpge_instruction_set };
	};
#endif
#ifdef _simd_u16x4_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_and_instruction_set };
	};
#endif
#ifdef _simd_u16x4_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_or_instruction_set };
	};
#endif
#ifdef _simd_u16x4_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_xor_instruction_set };
	};
#endif
#ifdef _simd_u16x8_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_add_instruction_set };
	};
#endif
#ifdef _simd_u16x8_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_sub_instruction_set };
	};
#endif
#ifdef _simd_u16x8_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_mul_instruction_set };
	};
#endif
#ifdef _simd_u16x8_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_div_instruction_set };
	};
#endif
#ifdef _simd_u16x8_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_min_instruction_set };
	};
#endif
#ifdef _simd_u16x8_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_max_instruction_set };
	};
#endif
#ifdef _simd_u16x8_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_u16x8_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_cmpne_instruction_set };
	};
#endif
#ifdef _simd_u16x8_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_cmplt_instruction_set };
	};
#endif
#ifdef _simd_u16x8_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_u16x8_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_cmple_instruction_set };
	};
#endif
#ifdef _simd_u16x8_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_cmpge_instruction_set };
	};
#endif
#ifdef _simd_u16x8_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_and_instruction_set };
	};
#endif
#ifdef _simd_u16x8_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_or_instruction_set };
	};
#endif
#ifdef _simd_u16x8_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_xor_instruction_set };
	};
#endif
#ifdef _simd_u16x16_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_add_instruction_set };
	};
#endif
#ifdef _simd_u16x16_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_sub_instruction_set };
	};
#endif
#ifdef _simd_u16x16_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_mul_instruction_set };
	};
#endif
#ifdef _simd_u16x16_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_div_instruction_set };
	};
#endif
#ifdef _simd_u16x16_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_min_instruction_set };
	};
#endif
#ifdef _simd_u16x16_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_max_instruction_set };
	};
#endif
#ifdef _simd_u16x16_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_u16x16_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_cmpne_instruction_set };
	};
#endif
#ifdef _simd_u16x16_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_cmplt_instruction_set };
	};
#endif
#ifdef _simd_u16x16_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_u16x16_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_cmple_instruction_set };
	};
#endif
#ifdef _simd_u16x16_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_cmpge_instruction_set };
	};
#endif
#ifdef _simd_u16x16_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_and_instruction_set };
	};
#endif
#ifdef _simd_u16x16_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_or_instruction_set };
	};
#endif
#ifdef _simd_u16x16_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_xor_instruction_set };
	};
#endif
#ifdef _simd_u16x32_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_add_instruction_set };
	};
#endif
#ifdef _simd_u16x32_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_sub_instruction_set };
	};
#endif
#ifdef _simd_u16x32_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_mul_instruction_set };
	};
#endif
#ifdef _simd_u16x32_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_div_instruction_set };
	};
#endif
#ifdef _simd_u16x32_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_min_instruction_set };
	};
#endif
#ifdef _simd_u16x32_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_max_instruction_set };
	};
#endif
#ifdef _simd_u16x32_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_u16x32_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_cmpne_instruction_set };
	};
#endif
#ifdef _simd_u16x32_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_cmplt_instruction_set };
	};
#endif
#ifdef _simd_u16x32_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_u16x32_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_cmple_instruction_set };
	};
#endif
#ifdef _simd_u16x32_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_cmpge_instruction_set };
	};
#endif
#ifdef _simd_u16x32_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_and_instruction_set };
	};
#endif
#ifdef _simd_u16x32_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_or_instruction_set };
	};
#endif
#ifdef _simd_u16x32_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_xor_instruction_set };
	};
#endif
#ifdef _simd_u16x64_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_add_instruction_set };
	};
#endif
#ifdef _simd_u16x64_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_sub_instruction_set };
	};
#endif
#ifdef _simd_u16x64_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_mul_instruction_set };
	};
#endif
#ifdef _simd_u16x64_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_div_instruction_set };
	};
#endif
#ifdef _simd_u16x64_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_min_instruction_set };
	};
#endif
#ifdef _simd_u16x64_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_max_instruction_set };
	};
#endif
#ifdef _simd_u16x64_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_u16x64_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_cmpne_instruction_set };
	};
#endif
#ifdef _simd_u16x64_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_cmplt_instruction_set };
	};
#endif
#ifdef _simd_u16x64_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_u16x64_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_cmple_instruction_set };
	};
#endif
#ifdef _simd_u16x64_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_cmpge_instruction_set };
	};
#endif
#ifdef _simd_u16x64_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_and_instruction_set };
	};
#endif
#ifdef _simd_u16x64_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_or_instruction_set };
	};
#endif
#ifdef _simd_u16x64_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_xor_instruction_set };
	};
#endif
#ifdef _simd_s8x2_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_add_instruction_set };
	};
#endif
#ifdef _simd_s8x2_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_sub_instruction_set };
	};
#endif
#ifdef _simd_s8x2_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_mul_instruction_set };
	};
#endif
#ifdef _simd_s8x2_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_div_instruction_set };
	};
#endif
#ifdef _simd_s8x2_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_min_instruction_set };
	};
#endif
#ifdef _simd_s8x2_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_max_instruction_set };
	};
#endif
#ifdef _simd_s8x2_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_s8x2_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_cmpne_instruction_set };
	};
#endif
#ifdef _simd_s8x2_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_cmplt_instruction_set };
	};
#endif
#ifdef _simd_s8x2_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_s8x2_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_cmple_instruction_set };
	};
#endif
#ifdef _simd_s8x2_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_cmpge_instruction_set };
	};
#endif
#ifdef _simd_s8x2_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_and_instruction_set };
	};
#endif
#ifdef _simd_s8x2_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_or_instruction_set };
	};
#endif
#ifdef _simd_s8x2_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_xor_instruction_set };
	};
#endif
#ifdef _simd_s8x4_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_add_instruction_set };
	};
#endif
#ifdef _simd_s8x4_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_sub_instruction_set };
	};
#endif
#ifdef _simd_s8x4_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_mul_instruction_set };
	};
#endif
#ifdef _simd_s8x4_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_div_instruction_set };
	};
#endif
#ifdef _simd_s8x4_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_min_instruction_set };
	};
#endif
#ifdef _simd_s8x4_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_max_instruction_set };
	};
#endif
#ifdef _simd_s8x4_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_s8x4_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_cmpne_instruction_set };
	};
#endif
#ifdef _simd_s8x4_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_cmplt_instruction_set };
	};
#endif
#ifdef _simd_s8x4_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_s8x4_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_cmple_instruction_set };
	};
#endif
#ifdef _simd_s8x4_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_cmpge_instruction_set };
	};
#endif
#ifdef _simd_s8x4_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_and_instruction_set };
	};
#endif
#ifdef _simd_s8x4_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_or_instruction_set };
	};
#endif
#ifdef _simd_s8x4_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_xor_instruction_set };
	};
#endif
#ifdef _simd_s8x8_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_add_instruction_set };
	};
#endif
#ifdef _simd_s8x8_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_sub_instruction_set };
	};
#endif
#ifdef _simd_s8x8_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_mul_instruction_set };
	};
#endif
#ifdef _simd_s8x8_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_div_instruction_set };
	};
#endif
#ifdef _simd_s8x8_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_min_instruction_set };
	};
#endif
#ifdef _simd_s8x8_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_max_instruction_set };
	};
#endif
#ifdef _simd_s8x8_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_s8x8_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_cmpne_instruction_set };
	};
#endif
#ifdef _simd_s8x8_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_cmplt_instruction_set };
	};
#endif
#ifdef _simd_s8x8_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_s8x8_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_cmple_instruction_set };
	};
#endif
#ifdef _simd_s8x8_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_cmpge_instruction_set };
	};
#endif
#ifdef _simd_s8x8_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_and_instruction_set };
	};
#endif
#ifdef _simd_s8x8_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_or_instruction_set };
	};
#endif
#ifdef _simd_s8x8_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_xor_instruction_set };
	};
#endif
#ifdef _simd_s8x16_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_add_instruction_set };
	};
#endif
#ifdef _simd_s8x16_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_sub_instruction_set };
	};
#endif
#ifdef _simd_s8x16_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_mul_instruction_set };
	};
#endif
#ifdef _simd_s8x16_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_div_instruction_set };
	};
#endif
#ifdef _simd_s8x16_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_min_instruction_set };
	};
#endif
#ifdef _simd_s8x16_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_max_instruction_set };
	};
#endif
#ifdef _simd_s8x16_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_s8x16_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_cmpne_instruction_set };
	};
#endif
#ifdef _simd_s8x16_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_cmplt_instruction_set };
	};
#endif
#ifdef _simd_s8x16_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_s8x16_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_cmple_instruction_set };
	};
#endif
#ifdef _simd_s8x16_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_cmpge_instruction_set };
	};
#endif
#ifdef _simd_s8x16_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_and_instruction_set };
	};
#endif
#ifdef _simd_s8x16_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_or_instruction_set };
	};
#endif
#ifdef _simd_s8x16_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_xor_instruction_set };
	};
#endif
#ifdef _simd_s8x32_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_add_instruction_set };
	};
#endif
#ifdef _simd_s8x32_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_sub_instruction_set };
	};
#endif
#ifdef _simd_s8x32_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_mul_instruction_set };
	};
#endif
#ifdef _simd_s8x32_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_div_instruction_set };
	};
#endif
#ifdef _simd_s8x32_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_min_instruction_set };
	};
#endif
#ifdef _simd_s8x32_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_max_instruction_set };
	};
#endif
#ifdef _simd_s8x32_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_s8x32_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_cmpne_instruction_set };
	};
#endif
#ifdef _simd_s8x32_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_cmplt_instruction_set };
	};
#endif
#ifdef _simd_s8x32_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_s8x32_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_cmple_instruction_set };
	};
#endif
#ifdef _simd_s8x32_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_cmpge_instruction_set };
	};
#endif
#ifdef _simd_s8x32_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_and_instruction_set };
	};
#endif
#ifdef _simd_s8x32_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_or_instruction_set };
	};
#endif
#ifdef _simd_s8x32_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_xor_instruction_set };
	};
#endif
#ifdef _simd_s8x64_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_add_instruction_set };
	};
#endif
#ifdef _simd_s8x64_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_sub_instruction_set };
	};
#endif
#ifdef _simd_s8x64_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_mul_instruction_set };
	};
#endif
#ifdef _simd_s8x64_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_div_instruction_set };
	};
#endif
#ifdef _simd_s8x64_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_min_instruction_set };
	};
#endif
#ifdef _simd_s8x64_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_max_instruction_set };
	};
#endif
#ifdef _simd_s8x64_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_s8x64_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_cmpne_instruction_set };
	};
#endif
#ifdef _simd_s8x64_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_cmplt_instruction_set };
	};
#endif
#ifdef _simd_s8x64_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_s8x64_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_cmple_instruction_set };
	};
#endif
#ifdef _simd_s8x64_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_cmpge_instruction_set };
	};
#endif
#ifdef _simd_s8x64_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_and_instruction_set };
	};
#endif
#ifdef _simd_s8x64_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_or_instruction_set };
	};
#endif
#ifdef _simd_s8x64_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_xor_instruction_set };
	};
#endif
#ifdef _simd_u8x2_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_add_instruction_set };
	};
#endif
#ifdef _simd_u8x2_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_sub_instruction_set };
	};
#endif
#ifdef _simd_u8x2_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_mul_instruction_set };
	};
#endif
#ifdef _simd_u8x2_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_div_instruction_set };
	};
#endif
#ifdef _simd_u8x2_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_min_instruction_set };
	};
#endif
#ifdef _simd_u8x2_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_max_instruction_set };
	};
#endif
#ifdef _simd_u8x2_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_u8x2_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_cmpne_instruction_set };
	};
#endif
#ifdef _simd_u8x2_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_cmplt_instruction_set };
	};
#endif
#ifdef _simd_u8x2_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_u8x2_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_cmple_instruction_set };
	};
#endif
#ifdef _simd_u8x2_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_cmpge_instruction_set };
	};
#endif
#ifdef _simd_u8x2_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_and_instruction_set };
	};
#endif
#ifdef _simd_u8x2_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_or_instruction_set };
	};
#endif
#ifdef _simd_u8x2_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_xor_instruction_set };
	};
#endif
#ifdef _simd_u8x4_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_add_instruction_set };
	};
#endif
#ifdef _simd_u8x4_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_sub_instruction_set };
	};
#endif
#ifdef _simd_u8x4_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_mul_instruction_set };
	};
#endif
#ifdef _simd_u8x4_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_div_instruction_set };
	};
#endif
#ifdef _simd_u8x4_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_min_instruction_set };
	};
#endif
#ifdef _simd_u8x4_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_max_instruction_set };
	};
#endif
#ifdef _simd_u8x4_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_u8x4_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_cmpne_instruction_set };
	};
#endif
#ifdef _simd_u8x4_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_cmplt_instruction_set };
	};
#endif
#ifdef _simd_u8x4_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_u8x4_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_cmple_instruction_set };
	};
#endif
#ifdef _simd_u8x4_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_cmpge_instruction_set };
	};
#endif
#ifdef _simd_u8x4_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_and_instruction_set };
	};
#endif
#ifdef _simd_u8x4_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_or_instruction_set };
	};
#endif
#ifdef _simd_u8x4_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_xor_instruction_set };
	};
#endif
#ifdef _simd_u8x8_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_add_instruction_set };
	};
#endif
#ifdef _simd_u8x8_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_sub_instruction_set };
	};
#endif
#ifdef _simd_u8x8_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_mul_instruction_set };
	};
#endif
#ifdef _simd_u8x8_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_div_instruction_set };
	};
#endif
#ifdef _simd_u8x8_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_min_instruction_set };
	};
#endif
#ifdef _simd_u8x8_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_max_instruction_set };
	};
#endif
#ifdef _simd_u8x8_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_u8x8_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_cmpne_instruction_set };
	};
#endif
#ifdef _simd_u8x8_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_cmplt_instruction_set };
	};
#endif
#ifdef _simd_u8x8_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_u8x8_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_cmple_instruction_set };
	};
#endif
#ifdef _simd_u8x8_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_cmpge_instruction_set };
	};
#endif
#ifdef _simd_u8x8_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_and_instruction_set };
	};
#endif
#ifdef _simd_u8x8_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_or_instruction_set };
	};
#endif
#ifdef _simd_u8x8_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_xor_instruction_set };
	};
#endif
#ifdef _simd_u8x16_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_add_instruction_set };
	};
#endif
#ifdef _simd_u8x16_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_sub_instruction_set };
	};
#endif
#ifdef _simd_u8x16_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_mul_instruction_set };
	};
#endif
#ifdef _simd_u8x16_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_div_instruction_set };
	};
#endif
#ifdef _simd_u8x16_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_min_instruction_set };
	};
#endif
#ifdef _simd_u8x16_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_max_instruction_set };
	};
#endif
#ifdef _simd_u8x16_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_u8x16_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_cmpne_instruction_set };
	};
#endif
#ifdef _simd_u8x16_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_cmplt_instruction_set };
	};
#endif
#ifdef _simd_u8x16_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_u8x16_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_cmple_instruction_set };
	};
#endif
#ifdef _simd_u8x16_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_cmpge_instruction_set };
	};
#endif
#ifdef _simd_u8x16_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_and_instruction_set };
	};
#endif
#ifdef _simd_u8x16_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_or_instruction_set };
	};
#endif
#ifdef _simd_u8x16_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_xor_instruction_set };
	};
#endif
#ifdef _simd_u8x32_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_add_instruction_set };
	};
#endif
#ifdef _simd_u8x32_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_sub_instruction_set };
	};
#endif
#ifdef _simd_u8x32_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_mul_instruction_set };
	};
#endif
#ifdef _simd_u8x32_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_div_instruction_set };
	};
#endif
#ifdef _simd_u8x32_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_min_instruction_set };
	};
#endif
#ifdef _simd_u8x32_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_max_instruction_set };
	};
#endif
#ifdef _simd_u8x32_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_u8x32_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_cmpne_instruction_set };
	};
#endif
#ifdef _simd_u8x32_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_cmplt_instruction_set };
	};
#endif
#ifdef _simd_u8x32_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_u8x32_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_cmple_instruction_set };
	};
#endif
#ifdef _simd_u8x32_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_cmpge_instruction_set };
	};
#endif
#ifdef _simd_u8x32_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_and_instruction_set };
	};
#endif
#ifdef _simd_u8x32_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_or_instruction_set };
	};
#endif
#ifdef _simd_u8x32_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_xor_instruction_set };
	};
#endif
#ifdef _simd_u8x64_add_instruction_set
	template<>
	struct OperationInstructionSet<OP_ADD, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_add_instruction_set };
	};
#endif
#ifdef _simd_u8x64_sub_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUB, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_sub_instruction_set };
	};
#endif
#ifdef _simd_u8x64_mul_instruction_set
	template<>
	struct OperationInstructionSet<OP_MUL, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_mul_instruction_set };
	};
#endif
#ifdef _simd_u8x64_div_instruction_set
	template<>
	struct OperationInstructionSet<OP_DIV, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_div_instruction_set };
	};
#endif
#ifdef _simd_u8x64_min_instruction_set
	template<>
	struct OperationInstructionSet<OP_MIN, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_min_instruction_set };
	};
#endif
#ifdef _simd_u8x64_max_instruction_set
	template<>
	struct OperationInstructionSet<OP_MAX, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_max_instruction_set };
	};
#endif
#ifdef _simd_u8x64_cmpeq_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPEQ, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_cmpeq_instruction_set };
	};
#endif
#ifdef _simd_u8x64_cmpne_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPNE, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_cmpne_instruction_set };
	};
#endif
#ifdef _simd_u8x64_cmplt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLT, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_cmplt_instruction_set };
	};
#endif
#ifdef _simd_u8x64_cmpgt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGT, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_cmpgt_instruction_set };
	};
#endif
#ifdef _simd_u8x64_cmple_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPLE, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_cmple_instruction_set };
	};
#endif
#ifdef _simd_u8x64_cmpge_instruction_set
	template<>
	struct OperationInstructionSet<OP_CMPGE, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_cmpge_instruction_set };
	};
#endif
#ifdef _simd_u8x64_and_instruction_set
	template<>
	struct OperationInstructionSet<OP_AND, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_and_instruction_set };
	};
#endif
#ifdef _simd_u8x64_or_instruction_set
	template<>
	struct OperationInstructionSet<OP_OR, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_or_instruction_set };
	};
#endif
#ifdef _simd_u8x64_xor_instruction_set
	template<>
	struct OperationInstructionSet<OP_XOR, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_xor_instruction_set };
	};
#endif
