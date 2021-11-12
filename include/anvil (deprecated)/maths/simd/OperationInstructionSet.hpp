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

#ifdef _simd_f64x2_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_fma_instruction_set };
	};
#endif
#ifdef _simd_f64x2_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_fms_instruction_set };
	};
#endif
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
#ifdef _simd_f64x2_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_lshift_instruction_set };
	};
#endif
#ifdef _simd_f64x2_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_rshift_instruction_set };
	};
#endif
#ifdef _simd_f64x2_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_atan2_instruction_set };
	};
#endif
#ifdef _simd_f64x2_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_reflect_instruction_set };
	};
#endif
#ifdef _simd_f64x2_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_not_instruction_set };
	};
#endif
#ifdef _simd_f64x2_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_abs_instruction_set };
	};
#endif
#ifdef _simd_f64x2_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_exp_instruction_set };
	};
#endif
#ifdef _simd_f64x2_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_log_instruction_set };
	};
#endif
#ifdef _simd_f64x2_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_log2_instruction_set };
	};
#endif
#ifdef _simd_f64x2_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_log10_instruction_set };
	};
#endif
#ifdef _simd_f64x2_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_ceil_instruction_set };
	};
#endif
#ifdef _simd_f64x2_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_floor_instruction_set };
	};
#endif
#ifdef _simd_f64x2_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_round_instruction_set };
	};
#endif
#ifdef _simd_f64x2_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_sin_instruction_set };
	};
#endif
#ifdef _simd_f64x2_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_cos_instruction_set };
	};
#endif
#ifdef _simd_f64x2_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_tan_instruction_set };
	};
#endif
#ifdef _simd_f64x2_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_asin_instruction_set };
	};
#endif
#ifdef _simd_f64x2_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_acos_instruction_set };
	};
#endif
#ifdef _simd_f64x2_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_atan_instruction_set };
	};
#endif
#ifdef _simd_f64x2_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_sinh_instruction_set };
	};
#endif
#ifdef _simd_f64x2_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_cosh_instruction_set };
	};
#endif
#ifdef _simd_f64x2_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_tanh_instruction_set };
	};
#endif
#ifdef _simd_f64x2_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_sqrt_instruction_set };
	};
#endif
#ifdef _simd_f64x2_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_cbrt_instruction_set };
	};
#endif
#ifdef _simd_f64x2_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_avg_instruction_set };
	};
#endif
#ifdef _simd_f64x2_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_sum_instruction_set };
	};
#endif
#ifdef _simd_f64x2_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_f64x1, 2> {
		enum : int64_t { value = _simd_f64x2_popcount_instruction_set };
	};
#endif
#ifdef _simd_f64x4_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_fma_instruction_set };
	};
#endif
#ifdef _simd_f64x4_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_fms_instruction_set };
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
#ifdef _simd_f64x4_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_lshift_instruction_set };
	};
#endif
#ifdef _simd_f64x4_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_rshift_instruction_set };
	};
#endif
#ifdef _simd_f64x4_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_atan2_instruction_set };
	};
#endif
#ifdef _simd_f64x4_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_reflect_instruction_set };
	};
#endif
#ifdef _simd_f64x4_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_not_instruction_set };
	};
#endif
#ifdef _simd_f64x4_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_abs_instruction_set };
	};
#endif
#ifdef _simd_f64x4_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_exp_instruction_set };
	};
#endif
#ifdef _simd_f64x4_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_log_instruction_set };
	};
#endif
#ifdef _simd_f64x4_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_log2_instruction_set };
	};
#endif
#ifdef _simd_f64x4_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_log10_instruction_set };
	};
#endif
#ifdef _simd_f64x4_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_ceil_instruction_set };
	};
#endif
#ifdef _simd_f64x4_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_floor_instruction_set };
	};
#endif
#ifdef _simd_f64x4_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_round_instruction_set };
	};
#endif
#ifdef _simd_f64x4_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_sin_instruction_set };
	};
#endif
#ifdef _simd_f64x4_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_cos_instruction_set };
	};
#endif
#ifdef _simd_f64x4_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_tan_instruction_set };
	};
#endif
#ifdef _simd_f64x4_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_asin_instruction_set };
	};
#endif
#ifdef _simd_f64x4_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_acos_instruction_set };
	};
#endif
#ifdef _simd_f64x4_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_atan_instruction_set };
	};
#endif
#ifdef _simd_f64x4_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_sinh_instruction_set };
	};
#endif
#ifdef _simd_f64x4_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_cosh_instruction_set };
	};
#endif
#ifdef _simd_f64x4_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_tanh_instruction_set };
	};
#endif
#ifdef _simd_f64x4_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_sqrt_instruction_set };
	};
#endif
#ifdef _simd_f64x4_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_cbrt_instruction_set };
	};
#endif
#ifdef _simd_f64x4_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_avg_instruction_set };
	};
#endif
#ifdef _simd_f64x4_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_sum_instruction_set };
	};
#endif
#ifdef _simd_f64x4_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_f64x1, 4> {
		enum : int64_t { value = _simd_f64x4_popcount_instruction_set };
	};
#endif
#ifdef _simd_f64x8_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_fma_instruction_set };
	};
#endif
#ifdef _simd_f64x8_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_fms_instruction_set };
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
#ifdef _simd_f64x8_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_lshift_instruction_set };
	};
#endif
#ifdef _simd_f64x8_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_rshift_instruction_set };
	};
#endif
#ifdef _simd_f64x8_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_atan2_instruction_set };
	};
#endif
#ifdef _simd_f64x8_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_reflect_instruction_set };
	};
#endif
#ifdef _simd_f64x8_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_not_instruction_set };
	};
#endif
#ifdef _simd_f64x8_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_abs_instruction_set };
	};
#endif
#ifdef _simd_f64x8_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_exp_instruction_set };
	};
#endif
#ifdef _simd_f64x8_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_log_instruction_set };
	};
#endif
#ifdef _simd_f64x8_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_log2_instruction_set };
	};
#endif
#ifdef _simd_f64x8_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_log10_instruction_set };
	};
#endif
#ifdef _simd_f64x8_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_ceil_instruction_set };
	};
#endif
#ifdef _simd_f64x8_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_floor_instruction_set };
	};
#endif
#ifdef _simd_f64x8_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_round_instruction_set };
	};
#endif
#ifdef _simd_f64x8_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_sin_instruction_set };
	};
#endif
#ifdef _simd_f64x8_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_cos_instruction_set };
	};
#endif
#ifdef _simd_f64x8_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_tan_instruction_set };
	};
#endif
#ifdef _simd_f64x8_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_asin_instruction_set };
	};
#endif
#ifdef _simd_f64x8_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_acos_instruction_set };
	};
#endif
#ifdef _simd_f64x8_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_atan_instruction_set };
	};
#endif
#ifdef _simd_f64x8_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_sinh_instruction_set };
	};
#endif
#ifdef _simd_f64x8_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_cosh_instruction_set };
	};
#endif
#ifdef _simd_f64x8_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_tanh_instruction_set };
	};
#endif
#ifdef _simd_f64x8_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_sqrt_instruction_set };
	};
#endif
#ifdef _simd_f64x8_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_cbrt_instruction_set };
	};
#endif
#ifdef _simd_f64x8_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_avg_instruction_set };
	};
#endif
#ifdef _simd_f64x8_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_sum_instruction_set };
	};
#endif
#ifdef _simd_f64x8_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_f64x1, 8> {
		enum : int64_t { value = _simd_f64x8_popcount_instruction_set };
	};
#endif
#ifdef _simd_f64x16_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_fma_instruction_set };
	};
#endif
#ifdef _simd_f64x16_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_fms_instruction_set };
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
#ifdef _simd_f64x16_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_lshift_instruction_set };
	};
#endif
#ifdef _simd_f64x16_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_rshift_instruction_set };
	};
#endif
#ifdef _simd_f64x16_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_atan2_instruction_set };
	};
#endif
#ifdef _simd_f64x16_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_reflect_instruction_set };
	};
#endif
#ifdef _simd_f64x16_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_not_instruction_set };
	};
#endif
#ifdef _simd_f64x16_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_abs_instruction_set };
	};
#endif
#ifdef _simd_f64x16_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_exp_instruction_set };
	};
#endif
#ifdef _simd_f64x16_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_log_instruction_set };
	};
#endif
#ifdef _simd_f64x16_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_log2_instruction_set };
	};
#endif
#ifdef _simd_f64x16_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_log10_instruction_set };
	};
#endif
#ifdef _simd_f64x16_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_ceil_instruction_set };
	};
#endif
#ifdef _simd_f64x16_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_floor_instruction_set };
	};
#endif
#ifdef _simd_f64x16_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_round_instruction_set };
	};
#endif
#ifdef _simd_f64x16_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_sin_instruction_set };
	};
#endif
#ifdef _simd_f64x16_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_cos_instruction_set };
	};
#endif
#ifdef _simd_f64x16_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_tan_instruction_set };
	};
#endif
#ifdef _simd_f64x16_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_asin_instruction_set };
	};
#endif
#ifdef _simd_f64x16_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_acos_instruction_set };
	};
#endif
#ifdef _simd_f64x16_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_atan_instruction_set };
	};
#endif
#ifdef _simd_f64x16_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_sinh_instruction_set };
	};
#endif
#ifdef _simd_f64x16_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_cosh_instruction_set };
	};
#endif
#ifdef _simd_f64x16_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_tanh_instruction_set };
	};
#endif
#ifdef _simd_f64x16_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_sqrt_instruction_set };
	};
#endif
#ifdef _simd_f64x16_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_cbrt_instruction_set };
	};
#endif
#ifdef _simd_f64x16_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_avg_instruction_set };
	};
#endif
#ifdef _simd_f64x16_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_sum_instruction_set };
	};
#endif
#ifdef _simd_f64x16_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_f64x1, 16> {
		enum : int64_t { value = _simd_f64x16_popcount_instruction_set };
	};
#endif
#ifdef _simd_f64x32_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_fma_instruction_set };
	};
#endif
#ifdef _simd_f64x32_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_fms_instruction_set };
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
#ifdef _simd_f64x32_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_lshift_instruction_set };
	};
#endif
#ifdef _simd_f64x32_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_rshift_instruction_set };
	};
#endif
#ifdef _simd_f64x32_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_atan2_instruction_set };
	};
#endif
#ifdef _simd_f64x32_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_reflect_instruction_set };
	};
#endif
#ifdef _simd_f64x32_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_not_instruction_set };
	};
#endif
#ifdef _simd_f64x32_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_abs_instruction_set };
	};
#endif
#ifdef _simd_f64x32_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_exp_instruction_set };
	};
#endif
#ifdef _simd_f64x32_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_log_instruction_set };
	};
#endif
#ifdef _simd_f64x32_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_log2_instruction_set };
	};
#endif
#ifdef _simd_f64x32_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_log10_instruction_set };
	};
#endif
#ifdef _simd_f64x32_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_ceil_instruction_set };
	};
#endif
#ifdef _simd_f64x32_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_floor_instruction_set };
	};
#endif
#ifdef _simd_f64x32_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_round_instruction_set };
	};
#endif
#ifdef _simd_f64x32_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_sin_instruction_set };
	};
#endif
#ifdef _simd_f64x32_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_cos_instruction_set };
	};
#endif
#ifdef _simd_f64x32_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_tan_instruction_set };
	};
#endif
#ifdef _simd_f64x32_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_asin_instruction_set };
	};
#endif
#ifdef _simd_f64x32_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_acos_instruction_set };
	};
#endif
#ifdef _simd_f64x32_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_atan_instruction_set };
	};
#endif
#ifdef _simd_f64x32_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_sinh_instruction_set };
	};
#endif
#ifdef _simd_f64x32_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_cosh_instruction_set };
	};
#endif
#ifdef _simd_f64x32_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_tanh_instruction_set };
	};
#endif
#ifdef _simd_f64x32_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_sqrt_instruction_set };
	};
#endif
#ifdef _simd_f64x32_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_cbrt_instruction_set };
	};
#endif
#ifdef _simd_f64x32_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_avg_instruction_set };
	};
#endif
#ifdef _simd_f64x32_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_sum_instruction_set };
	};
#endif
#ifdef _simd_f64x32_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_f64x1, 32> {
		enum : int64_t { value = _simd_f64x32_popcount_instruction_set };
	};
#endif
#ifdef _simd_f64x64_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_fma_instruction_set };
	};
#endif
#ifdef _simd_f64x64_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_fms_instruction_set };
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
#ifdef _simd_f64x64_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_lshift_instruction_set };
	};
#endif
#ifdef _simd_f64x64_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_rshift_instruction_set };
	};
#endif
#ifdef _simd_f64x64_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_atan2_instruction_set };
	};
#endif
#ifdef _simd_f64x64_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_reflect_instruction_set };
	};
#endif
#ifdef _simd_f64x64_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_not_instruction_set };
	};
#endif
#ifdef _simd_f64x64_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_abs_instruction_set };
	};
#endif
#ifdef _simd_f64x64_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_exp_instruction_set };
	};
#endif
#ifdef _simd_f64x64_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_log_instruction_set };
	};
#endif
#ifdef _simd_f64x64_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_log2_instruction_set };
	};
#endif
#ifdef _simd_f64x64_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_log10_instruction_set };
	};
#endif
#ifdef _simd_f64x64_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_ceil_instruction_set };
	};
#endif
#ifdef _simd_f64x64_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_floor_instruction_set };
	};
#endif
#ifdef _simd_f64x64_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_round_instruction_set };
	};
#endif
#ifdef _simd_f64x64_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_sin_instruction_set };
	};
#endif
#ifdef _simd_f64x64_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_cos_instruction_set };
	};
#endif
#ifdef _simd_f64x64_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_tan_instruction_set };
	};
#endif
#ifdef _simd_f64x64_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_asin_instruction_set };
	};
#endif
#ifdef _simd_f64x64_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_acos_instruction_set };
	};
#endif
#ifdef _simd_f64x64_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_atan_instruction_set };
	};
#endif
#ifdef _simd_f64x64_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_sinh_instruction_set };
	};
#endif
#ifdef _simd_f64x64_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_cosh_instruction_set };
	};
#endif
#ifdef _simd_f64x64_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_tanh_instruction_set };
	};
#endif
#ifdef _simd_f64x64_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_sqrt_instruction_set };
	};
#endif
#ifdef _simd_f64x64_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_cbrt_instruction_set };
	};
#endif
#ifdef _simd_f64x64_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_avg_instruction_set };
	};
#endif
#ifdef _simd_f64x64_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_sum_instruction_set };
	};
#endif
#ifdef _simd_f64x64_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_f64x1, 64> {
		enum : int64_t { value = _simd_f64x64_popcount_instruction_set };
	};
#endif
#ifdef _simd_f32x2_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_fma_instruction_set };
	};
#endif
#ifdef _simd_f32x2_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_fms_instruction_set };
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
#ifdef _simd_f32x2_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_lshift_instruction_set };
	};
#endif
#ifdef _simd_f32x2_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_rshift_instruction_set };
	};
#endif
#ifdef _simd_f32x2_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_atan2_instruction_set };
	};
#endif
#ifdef _simd_f32x2_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_reflect_instruction_set };
	};
#endif
#ifdef _simd_f32x2_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_not_instruction_set };
	};
#endif
#ifdef _simd_f32x2_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_abs_instruction_set };
	};
#endif
#ifdef _simd_f32x2_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_exp_instruction_set };
	};
#endif
#ifdef _simd_f32x2_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_log_instruction_set };
	};
#endif
#ifdef _simd_f32x2_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_log2_instruction_set };
	};
#endif
#ifdef _simd_f32x2_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_log10_instruction_set };
	};
#endif
#ifdef _simd_f32x2_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_ceil_instruction_set };
	};
#endif
#ifdef _simd_f32x2_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_floor_instruction_set };
	};
#endif
#ifdef _simd_f32x2_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_round_instruction_set };
	};
#endif
#ifdef _simd_f32x2_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_sin_instruction_set };
	};
#endif
#ifdef _simd_f32x2_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_cos_instruction_set };
	};
#endif
#ifdef _simd_f32x2_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_tan_instruction_set };
	};
#endif
#ifdef _simd_f32x2_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_asin_instruction_set };
	};
#endif
#ifdef _simd_f32x2_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_acos_instruction_set };
	};
#endif
#ifdef _simd_f32x2_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_atan_instruction_set };
	};
#endif
#ifdef _simd_f32x2_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_sinh_instruction_set };
	};
#endif
#ifdef _simd_f32x2_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_cosh_instruction_set };
	};
#endif
#ifdef _simd_f32x2_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_tanh_instruction_set };
	};
#endif
#ifdef _simd_f32x2_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_sqrt_instruction_set };
	};
#endif
#ifdef _simd_f32x2_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_cbrt_instruction_set };
	};
#endif
#ifdef _simd_f32x2_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_avg_instruction_set };
	};
#endif
#ifdef _simd_f32x2_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_sum_instruction_set };
	};
#endif
#ifdef _simd_f32x2_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_f32x1, 2> {
		enum : int64_t { value = _simd_f32x2_popcount_instruction_set };
	};
#endif
#ifdef _simd_f32x4_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_fma_instruction_set };
	};
#endif
#ifdef _simd_f32x4_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_fms_instruction_set };
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
#ifdef _simd_f32x4_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_lshift_instruction_set };
	};
#endif
#ifdef _simd_f32x4_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_rshift_instruction_set };
	};
#endif
#ifdef _simd_f32x4_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_atan2_instruction_set };
	};
#endif
#ifdef _simd_f32x4_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_reflect_instruction_set };
	};
#endif
#ifdef _simd_f32x4_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_not_instruction_set };
	};
#endif
#ifdef _simd_f32x4_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_abs_instruction_set };
	};
#endif
#ifdef _simd_f32x4_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_exp_instruction_set };
	};
#endif
#ifdef _simd_f32x4_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_log_instruction_set };
	};
#endif
#ifdef _simd_f32x4_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_log2_instruction_set };
	};
#endif
#ifdef _simd_f32x4_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_log10_instruction_set };
	};
#endif
#ifdef _simd_f32x4_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_ceil_instruction_set };
	};
#endif
#ifdef _simd_f32x4_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_floor_instruction_set };
	};
#endif
#ifdef _simd_f32x4_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_round_instruction_set };
	};
#endif
#ifdef _simd_f32x4_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_sin_instruction_set };
	};
#endif
#ifdef _simd_f32x4_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_cos_instruction_set };
	};
#endif
#ifdef _simd_f32x4_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_tan_instruction_set };
	};
#endif
#ifdef _simd_f32x4_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_asin_instruction_set };
	};
#endif
#ifdef _simd_f32x4_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_acos_instruction_set };
	};
#endif
#ifdef _simd_f32x4_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_atan_instruction_set };
	};
#endif
#ifdef _simd_f32x4_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_sinh_instruction_set };
	};
#endif
#ifdef _simd_f32x4_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_cosh_instruction_set };
	};
#endif
#ifdef _simd_f32x4_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_tanh_instruction_set };
	};
#endif
#ifdef _simd_f32x4_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_sqrt_instruction_set };
	};
#endif
#ifdef _simd_f32x4_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_cbrt_instruction_set };
	};
#endif
#ifdef _simd_f32x4_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_avg_instruction_set };
	};
#endif
#ifdef _simd_f32x4_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_sum_instruction_set };
	};
#endif
#ifdef _simd_f32x4_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_f32x1, 4> {
		enum : int64_t { value = _simd_f32x4_popcount_instruction_set };
	};
#endif
#ifdef _simd_f32x8_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_fma_instruction_set };
	};
#endif
#ifdef _simd_f32x8_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_fms_instruction_set };
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
#ifdef _simd_f32x8_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_lshift_instruction_set };
	};
#endif
#ifdef _simd_f32x8_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_rshift_instruction_set };
	};
#endif
#ifdef _simd_f32x8_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_atan2_instruction_set };
	};
#endif
#ifdef _simd_f32x8_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_reflect_instruction_set };
	};
#endif
#ifdef _simd_f32x8_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_not_instruction_set };
	};
#endif
#ifdef _simd_f32x8_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_abs_instruction_set };
	};
#endif
#ifdef _simd_f32x8_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_exp_instruction_set };
	};
#endif
#ifdef _simd_f32x8_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_log_instruction_set };
	};
#endif
#ifdef _simd_f32x8_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_log2_instruction_set };
	};
#endif
#ifdef _simd_f32x8_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_log10_instruction_set };
	};
#endif
#ifdef _simd_f32x8_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_ceil_instruction_set };
	};
#endif
#ifdef _simd_f32x8_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_floor_instruction_set };
	};
#endif
#ifdef _simd_f32x8_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_round_instruction_set };
	};
#endif
#ifdef _simd_f32x8_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_sin_instruction_set };
	};
#endif
#ifdef _simd_f32x8_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_cos_instruction_set };
	};
#endif
#ifdef _simd_f32x8_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_tan_instruction_set };
	};
#endif
#ifdef _simd_f32x8_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_asin_instruction_set };
	};
#endif
#ifdef _simd_f32x8_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_acos_instruction_set };
	};
#endif
#ifdef _simd_f32x8_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_atan_instruction_set };
	};
#endif
#ifdef _simd_f32x8_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_sinh_instruction_set };
	};
#endif
#ifdef _simd_f32x8_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_cosh_instruction_set };
	};
#endif
#ifdef _simd_f32x8_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_tanh_instruction_set };
	};
#endif
#ifdef _simd_f32x8_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_sqrt_instruction_set };
	};
#endif
#ifdef _simd_f32x8_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_cbrt_instruction_set };
	};
#endif
#ifdef _simd_f32x8_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_avg_instruction_set };
	};
#endif
#ifdef _simd_f32x8_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_sum_instruction_set };
	};
#endif
#ifdef _simd_f32x8_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_f32x1, 8> {
		enum : int64_t { value = _simd_f32x8_popcount_instruction_set };
	};
#endif
#ifdef _simd_f32x16_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_fma_instruction_set };
	};
#endif
#ifdef _simd_f32x16_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_fms_instruction_set };
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
#ifdef _simd_f32x16_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_lshift_instruction_set };
	};
#endif
#ifdef _simd_f32x16_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_rshift_instruction_set };
	};
#endif
#ifdef _simd_f32x16_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_atan2_instruction_set };
	};
#endif
#ifdef _simd_f32x16_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_reflect_instruction_set };
	};
#endif
#ifdef _simd_f32x16_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_not_instruction_set };
	};
#endif
#ifdef _simd_f32x16_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_abs_instruction_set };
	};
#endif
#ifdef _simd_f32x16_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_exp_instruction_set };
	};
#endif
#ifdef _simd_f32x16_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_log_instruction_set };
	};
#endif
#ifdef _simd_f32x16_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_log2_instruction_set };
	};
#endif
#ifdef _simd_f32x16_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_log10_instruction_set };
	};
#endif
#ifdef _simd_f32x16_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_ceil_instruction_set };
	};
#endif
#ifdef _simd_f32x16_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_floor_instruction_set };
	};
#endif
#ifdef _simd_f32x16_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_round_instruction_set };
	};
#endif
#ifdef _simd_f32x16_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_sin_instruction_set };
	};
#endif
#ifdef _simd_f32x16_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_cos_instruction_set };
	};
#endif
#ifdef _simd_f32x16_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_tan_instruction_set };
	};
#endif
#ifdef _simd_f32x16_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_asin_instruction_set };
	};
#endif
#ifdef _simd_f32x16_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_acos_instruction_set };
	};
#endif
#ifdef _simd_f32x16_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_atan_instruction_set };
	};
#endif
#ifdef _simd_f32x16_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_sinh_instruction_set };
	};
#endif
#ifdef _simd_f32x16_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_cosh_instruction_set };
	};
#endif
#ifdef _simd_f32x16_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_tanh_instruction_set };
	};
#endif
#ifdef _simd_f32x16_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_sqrt_instruction_set };
	};
#endif
#ifdef _simd_f32x16_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_cbrt_instruction_set };
	};
#endif
#ifdef _simd_f32x16_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_avg_instruction_set };
	};
#endif
#ifdef _simd_f32x16_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_sum_instruction_set };
	};
#endif
#ifdef _simd_f32x16_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_f32x1, 16> {
		enum : int64_t { value = _simd_f32x16_popcount_instruction_set };
	};
#endif
#ifdef _simd_f32x32_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_fma_instruction_set };
	};
#endif
#ifdef _simd_f32x32_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_fms_instruction_set };
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
#ifdef _simd_f32x32_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_lshift_instruction_set };
	};
#endif
#ifdef _simd_f32x32_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_rshift_instruction_set };
	};
#endif
#ifdef _simd_f32x32_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_atan2_instruction_set };
	};
#endif
#ifdef _simd_f32x32_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_reflect_instruction_set };
	};
#endif
#ifdef _simd_f32x32_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_not_instruction_set };
	};
#endif
#ifdef _simd_f32x32_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_abs_instruction_set };
	};
#endif
#ifdef _simd_f32x32_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_exp_instruction_set };
	};
#endif
#ifdef _simd_f32x32_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_log_instruction_set };
	};
#endif
#ifdef _simd_f32x32_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_log2_instruction_set };
	};
#endif
#ifdef _simd_f32x32_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_log10_instruction_set };
	};
#endif
#ifdef _simd_f32x32_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_ceil_instruction_set };
	};
#endif
#ifdef _simd_f32x32_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_floor_instruction_set };
	};
#endif
#ifdef _simd_f32x32_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_round_instruction_set };
	};
#endif
#ifdef _simd_f32x32_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_sin_instruction_set };
	};
#endif
#ifdef _simd_f32x32_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_cos_instruction_set };
	};
#endif
#ifdef _simd_f32x32_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_tan_instruction_set };
	};
#endif
#ifdef _simd_f32x32_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_asin_instruction_set };
	};
#endif
#ifdef _simd_f32x32_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_acos_instruction_set };
	};
#endif
#ifdef _simd_f32x32_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_atan_instruction_set };
	};
#endif
#ifdef _simd_f32x32_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_sinh_instruction_set };
	};
#endif
#ifdef _simd_f32x32_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_cosh_instruction_set };
	};
#endif
#ifdef _simd_f32x32_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_tanh_instruction_set };
	};
#endif
#ifdef _simd_f32x32_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_sqrt_instruction_set };
	};
#endif
#ifdef _simd_f32x32_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_cbrt_instruction_set };
	};
#endif
#ifdef _simd_f32x32_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_avg_instruction_set };
	};
#endif
#ifdef _simd_f32x32_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_sum_instruction_set };
	};
#endif
#ifdef _simd_f32x32_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_f32x1, 32> {
		enum : int64_t { value = _simd_f32x32_popcount_instruction_set };
	};
#endif
#ifdef _simd_f32x64_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_fma_instruction_set };
	};
#endif
#ifdef _simd_f32x64_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_fms_instruction_set };
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
#ifdef _simd_f32x64_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_lshift_instruction_set };
	};
#endif
#ifdef _simd_f32x64_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_rshift_instruction_set };
	};
#endif
#ifdef _simd_f32x64_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_atan2_instruction_set };
	};
#endif
#ifdef _simd_f32x64_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_reflect_instruction_set };
	};
#endif
#ifdef _simd_f32x64_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_not_instruction_set };
	};
#endif
#ifdef _simd_f32x64_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_abs_instruction_set };
	};
#endif
#ifdef _simd_f32x64_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_exp_instruction_set };
	};
#endif
#ifdef _simd_f32x64_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_log_instruction_set };
	};
#endif
#ifdef _simd_f32x64_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_log2_instruction_set };
	};
#endif
#ifdef _simd_f32x64_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_log10_instruction_set };
	};
#endif
#ifdef _simd_f32x64_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_ceil_instruction_set };
	};
#endif
#ifdef _simd_f32x64_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_floor_instruction_set };
	};
#endif
#ifdef _simd_f32x64_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_round_instruction_set };
	};
#endif
#ifdef _simd_f32x64_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_sin_instruction_set };
	};
#endif
#ifdef _simd_f32x64_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_cos_instruction_set };
	};
#endif
#ifdef _simd_f32x64_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_tan_instruction_set };
	};
#endif
#ifdef _simd_f32x64_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_asin_instruction_set };
	};
#endif
#ifdef _simd_f32x64_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_acos_instruction_set };
	};
#endif
#ifdef _simd_f32x64_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_atan_instruction_set };
	};
#endif
#ifdef _simd_f32x64_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_sinh_instruction_set };
	};
#endif
#ifdef _simd_f32x64_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_cosh_instruction_set };
	};
#endif
#ifdef _simd_f32x64_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_tanh_instruction_set };
	};
#endif
#ifdef _simd_f32x64_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_sqrt_instruction_set };
	};
#endif
#ifdef _simd_f32x64_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_cbrt_instruction_set };
	};
#endif
#ifdef _simd_f32x64_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_avg_instruction_set };
	};
#endif
#ifdef _simd_f32x64_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_sum_instruction_set };
	};
#endif
#ifdef _simd_f32x64_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_f32x1, 64> {
		enum : int64_t { value = _simd_f32x64_popcount_instruction_set };
	};
#endif
#ifdef _simd_s64x2_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_fma_instruction_set };
	};
#endif
#ifdef _simd_s64x2_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_fms_instruction_set };
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
#ifdef _simd_s64x2_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_lshift_instruction_set };
	};
#endif
#ifdef _simd_s64x2_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_rshift_instruction_set };
	};
#endif
#ifdef _simd_s64x2_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_atan2_instruction_set };
	};
#endif
#ifdef _simd_s64x2_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_reflect_instruction_set };
	};
#endif
#ifdef _simd_s64x2_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_not_instruction_set };
	};
#endif
#ifdef _simd_s64x2_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_abs_instruction_set };
	};
#endif
#ifdef _simd_s64x2_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_exp_instruction_set };
	};
#endif
#ifdef _simd_s64x2_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_log_instruction_set };
	};
#endif
#ifdef _simd_s64x2_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_log2_instruction_set };
	};
#endif
#ifdef _simd_s64x2_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_log10_instruction_set };
	};
#endif
#ifdef _simd_s64x2_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_ceil_instruction_set };
	};
#endif
#ifdef _simd_s64x2_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_floor_instruction_set };
	};
#endif
#ifdef _simd_s64x2_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_round_instruction_set };
	};
#endif
#ifdef _simd_s64x2_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_sin_instruction_set };
	};
#endif
#ifdef _simd_s64x2_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_cos_instruction_set };
	};
#endif
#ifdef _simd_s64x2_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_tan_instruction_set };
	};
#endif
#ifdef _simd_s64x2_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_asin_instruction_set };
	};
#endif
#ifdef _simd_s64x2_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_acos_instruction_set };
	};
#endif
#ifdef _simd_s64x2_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_atan_instruction_set };
	};
#endif
#ifdef _simd_s64x2_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_sinh_instruction_set };
	};
#endif
#ifdef _simd_s64x2_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_cosh_instruction_set };
	};
#endif
#ifdef _simd_s64x2_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_tanh_instruction_set };
	};
#endif
#ifdef _simd_s64x2_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_sqrt_instruction_set };
	};
#endif
#ifdef _simd_s64x2_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_cbrt_instruction_set };
	};
#endif
#ifdef _simd_s64x2_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_avg_instruction_set };
	};
#endif
#ifdef _simd_s64x2_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_sum_instruction_set };
	};
#endif
#ifdef _simd_s64x2_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_s64x1, 2> {
		enum : int64_t { value = _simd_s64x2_popcount_instruction_set };
	};
#endif
#ifdef _simd_s64x4_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_fma_instruction_set };
	};
#endif
#ifdef _simd_s64x4_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_fms_instruction_set };
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
#ifdef _simd_s64x4_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_lshift_instruction_set };
	};
#endif
#ifdef _simd_s64x4_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_rshift_instruction_set };
	};
#endif
#ifdef _simd_s64x4_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_atan2_instruction_set };
	};
#endif
#ifdef _simd_s64x4_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_reflect_instruction_set };
	};
#endif
#ifdef _simd_s64x4_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_not_instruction_set };
	};
#endif
#ifdef _simd_s64x4_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_abs_instruction_set };
	};
#endif
#ifdef _simd_s64x4_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_exp_instruction_set };
	};
#endif
#ifdef _simd_s64x4_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_log_instruction_set };
	};
#endif
#ifdef _simd_s64x4_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_log2_instruction_set };
	};
#endif
#ifdef _simd_s64x4_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_log10_instruction_set };
	};
#endif
#ifdef _simd_s64x4_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_ceil_instruction_set };
	};
#endif
#ifdef _simd_s64x4_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_floor_instruction_set };
	};
#endif
#ifdef _simd_s64x4_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_round_instruction_set };
	};
#endif
#ifdef _simd_s64x4_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_sin_instruction_set };
	};
#endif
#ifdef _simd_s64x4_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_cos_instruction_set };
	};
#endif
#ifdef _simd_s64x4_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_tan_instruction_set };
	};
#endif
#ifdef _simd_s64x4_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_asin_instruction_set };
	};
#endif
#ifdef _simd_s64x4_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_acos_instruction_set };
	};
#endif
#ifdef _simd_s64x4_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_atan_instruction_set };
	};
#endif
#ifdef _simd_s64x4_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_sinh_instruction_set };
	};
#endif
#ifdef _simd_s64x4_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_cosh_instruction_set };
	};
#endif
#ifdef _simd_s64x4_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_tanh_instruction_set };
	};
#endif
#ifdef _simd_s64x4_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_sqrt_instruction_set };
	};
#endif
#ifdef _simd_s64x4_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_cbrt_instruction_set };
	};
#endif
#ifdef _simd_s64x4_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_avg_instruction_set };
	};
#endif
#ifdef _simd_s64x4_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_sum_instruction_set };
	};
#endif
#ifdef _simd_s64x4_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_s64x1, 4> {
		enum : int64_t { value = _simd_s64x4_popcount_instruction_set };
	};
#endif
#ifdef _simd_s64x8_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_fma_instruction_set };
	};
#endif
#ifdef _simd_s64x8_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_fms_instruction_set };
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
#ifdef _simd_s64x8_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_lshift_instruction_set };
	};
#endif
#ifdef _simd_s64x8_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_rshift_instruction_set };
	};
#endif
#ifdef _simd_s64x8_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_atan2_instruction_set };
	};
#endif
#ifdef _simd_s64x8_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_reflect_instruction_set };
	};
#endif
#ifdef _simd_s64x8_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_not_instruction_set };
	};
#endif
#ifdef _simd_s64x8_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_abs_instruction_set };
	};
#endif
#ifdef _simd_s64x8_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_exp_instruction_set };
	};
#endif
#ifdef _simd_s64x8_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_log_instruction_set };
	};
#endif
#ifdef _simd_s64x8_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_log2_instruction_set };
	};
#endif
#ifdef _simd_s64x8_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_log10_instruction_set };
	};
#endif
#ifdef _simd_s64x8_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_ceil_instruction_set };
	};
#endif
#ifdef _simd_s64x8_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_floor_instruction_set };
	};
#endif
#ifdef _simd_s64x8_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_round_instruction_set };
	};
#endif
#ifdef _simd_s64x8_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_sin_instruction_set };
	};
#endif
#ifdef _simd_s64x8_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_cos_instruction_set };
	};
#endif
#ifdef _simd_s64x8_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_tan_instruction_set };
	};
#endif
#ifdef _simd_s64x8_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_asin_instruction_set };
	};
#endif
#ifdef _simd_s64x8_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_acos_instruction_set };
	};
#endif
#ifdef _simd_s64x8_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_atan_instruction_set };
	};
#endif
#ifdef _simd_s64x8_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_sinh_instruction_set };
	};
#endif
#ifdef _simd_s64x8_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_cosh_instruction_set };
	};
#endif
#ifdef _simd_s64x8_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_tanh_instruction_set };
	};
#endif
#ifdef _simd_s64x8_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_sqrt_instruction_set };
	};
#endif
#ifdef _simd_s64x8_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_cbrt_instruction_set };
	};
#endif
#ifdef _simd_s64x8_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_avg_instruction_set };
	};
#endif
#ifdef _simd_s64x8_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_sum_instruction_set };
	};
#endif
#ifdef _simd_s64x8_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_s64x1, 8> {
		enum : int64_t { value = _simd_s64x8_popcount_instruction_set };
	};
#endif
#ifdef _simd_s64x16_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_fma_instruction_set };
	};
#endif
#ifdef _simd_s64x16_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_fms_instruction_set };
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
#ifdef _simd_s64x16_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_lshift_instruction_set };
	};
#endif
#ifdef _simd_s64x16_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_rshift_instruction_set };
	};
#endif
#ifdef _simd_s64x16_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_atan2_instruction_set };
	};
#endif
#ifdef _simd_s64x16_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_reflect_instruction_set };
	};
#endif
#ifdef _simd_s64x16_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_not_instruction_set };
	};
#endif
#ifdef _simd_s64x16_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_abs_instruction_set };
	};
#endif
#ifdef _simd_s64x16_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_exp_instruction_set };
	};
#endif
#ifdef _simd_s64x16_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_log_instruction_set };
	};
#endif
#ifdef _simd_s64x16_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_log2_instruction_set };
	};
#endif
#ifdef _simd_s64x16_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_log10_instruction_set };
	};
#endif
#ifdef _simd_s64x16_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_ceil_instruction_set };
	};
#endif
#ifdef _simd_s64x16_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_floor_instruction_set };
	};
#endif
#ifdef _simd_s64x16_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_round_instruction_set };
	};
#endif
#ifdef _simd_s64x16_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_sin_instruction_set };
	};
#endif
#ifdef _simd_s64x16_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_cos_instruction_set };
	};
#endif
#ifdef _simd_s64x16_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_tan_instruction_set };
	};
#endif
#ifdef _simd_s64x16_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_asin_instruction_set };
	};
#endif
#ifdef _simd_s64x16_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_acos_instruction_set };
	};
#endif
#ifdef _simd_s64x16_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_atan_instruction_set };
	};
#endif
#ifdef _simd_s64x16_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_sinh_instruction_set };
	};
#endif
#ifdef _simd_s64x16_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_cosh_instruction_set };
	};
#endif
#ifdef _simd_s64x16_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_tanh_instruction_set };
	};
#endif
#ifdef _simd_s64x16_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_sqrt_instruction_set };
	};
#endif
#ifdef _simd_s64x16_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_cbrt_instruction_set };
	};
#endif
#ifdef _simd_s64x16_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_avg_instruction_set };
	};
#endif
#ifdef _simd_s64x16_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_sum_instruction_set };
	};
#endif
#ifdef _simd_s64x16_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_s64x1, 16> {
		enum : int64_t { value = _simd_s64x16_popcount_instruction_set };
	};
#endif
#ifdef _simd_s64x32_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_fma_instruction_set };
	};
#endif
#ifdef _simd_s64x32_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_fms_instruction_set };
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
#ifdef _simd_s64x32_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_lshift_instruction_set };
	};
#endif
#ifdef _simd_s64x32_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_rshift_instruction_set };
	};
#endif
#ifdef _simd_s64x32_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_atan2_instruction_set };
	};
#endif
#ifdef _simd_s64x32_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_reflect_instruction_set };
	};
#endif
#ifdef _simd_s64x32_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_not_instruction_set };
	};
#endif
#ifdef _simd_s64x32_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_abs_instruction_set };
	};
#endif
#ifdef _simd_s64x32_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_exp_instruction_set };
	};
#endif
#ifdef _simd_s64x32_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_log_instruction_set };
	};
#endif
#ifdef _simd_s64x32_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_log2_instruction_set };
	};
#endif
#ifdef _simd_s64x32_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_log10_instruction_set };
	};
#endif
#ifdef _simd_s64x32_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_ceil_instruction_set };
	};
#endif
#ifdef _simd_s64x32_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_floor_instruction_set };
	};
#endif
#ifdef _simd_s64x32_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_round_instruction_set };
	};
#endif
#ifdef _simd_s64x32_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_sin_instruction_set };
	};
#endif
#ifdef _simd_s64x32_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_cos_instruction_set };
	};
#endif
#ifdef _simd_s64x32_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_tan_instruction_set };
	};
#endif
#ifdef _simd_s64x32_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_asin_instruction_set };
	};
#endif
#ifdef _simd_s64x32_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_acos_instruction_set };
	};
#endif
#ifdef _simd_s64x32_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_atan_instruction_set };
	};
#endif
#ifdef _simd_s64x32_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_sinh_instruction_set };
	};
#endif
#ifdef _simd_s64x32_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_cosh_instruction_set };
	};
#endif
#ifdef _simd_s64x32_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_tanh_instruction_set };
	};
#endif
#ifdef _simd_s64x32_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_sqrt_instruction_set };
	};
#endif
#ifdef _simd_s64x32_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_cbrt_instruction_set };
	};
#endif
#ifdef _simd_s64x32_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_avg_instruction_set };
	};
#endif
#ifdef _simd_s64x32_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_sum_instruction_set };
	};
#endif
#ifdef _simd_s64x32_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_s64x1, 32> {
		enum : int64_t { value = _simd_s64x32_popcount_instruction_set };
	};
#endif
#ifdef _simd_s64x64_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_fma_instruction_set };
	};
#endif
#ifdef _simd_s64x64_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_fms_instruction_set };
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
#ifdef _simd_s64x64_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_lshift_instruction_set };
	};
#endif
#ifdef _simd_s64x64_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_rshift_instruction_set };
	};
#endif
#ifdef _simd_s64x64_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_atan2_instruction_set };
	};
#endif
#ifdef _simd_s64x64_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_reflect_instruction_set };
	};
#endif
#ifdef _simd_s64x64_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_not_instruction_set };
	};
#endif
#ifdef _simd_s64x64_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_abs_instruction_set };
	};
#endif
#ifdef _simd_s64x64_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_exp_instruction_set };
	};
#endif
#ifdef _simd_s64x64_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_log_instruction_set };
	};
#endif
#ifdef _simd_s64x64_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_log2_instruction_set };
	};
#endif
#ifdef _simd_s64x64_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_log10_instruction_set };
	};
#endif
#ifdef _simd_s64x64_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_ceil_instruction_set };
	};
#endif
#ifdef _simd_s64x64_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_floor_instruction_set };
	};
#endif
#ifdef _simd_s64x64_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_round_instruction_set };
	};
#endif
#ifdef _simd_s64x64_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_sin_instruction_set };
	};
#endif
#ifdef _simd_s64x64_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_cos_instruction_set };
	};
#endif
#ifdef _simd_s64x64_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_tan_instruction_set };
	};
#endif
#ifdef _simd_s64x64_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_asin_instruction_set };
	};
#endif
#ifdef _simd_s64x64_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_acos_instruction_set };
	};
#endif
#ifdef _simd_s64x64_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_atan_instruction_set };
	};
#endif
#ifdef _simd_s64x64_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_sinh_instruction_set };
	};
#endif
#ifdef _simd_s64x64_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_cosh_instruction_set };
	};
#endif
#ifdef _simd_s64x64_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_tanh_instruction_set };
	};
#endif
#ifdef _simd_s64x64_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_sqrt_instruction_set };
	};
#endif
#ifdef _simd_s64x64_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_cbrt_instruction_set };
	};
#endif
#ifdef _simd_s64x64_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_avg_instruction_set };
	};
#endif
#ifdef _simd_s64x64_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_sum_instruction_set };
	};
#endif
#ifdef _simd_s64x64_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_s64x1, 64> {
		enum : int64_t { value = _simd_s64x64_popcount_instruction_set };
	};
#endif
#ifdef _simd_u64x2_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_fma_instruction_set };
	};
#endif
#ifdef _simd_u64x2_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_fms_instruction_set };
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
#ifdef _simd_u64x2_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_lshift_instruction_set };
	};
#endif
#ifdef _simd_u64x2_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_rshift_instruction_set };
	};
#endif
#ifdef _simd_u64x2_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_atan2_instruction_set };
	};
#endif
#ifdef _simd_u64x2_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_reflect_instruction_set };
	};
#endif
#ifdef _simd_u64x2_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_not_instruction_set };
	};
#endif
#ifdef _simd_u64x2_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_abs_instruction_set };
	};
#endif
#ifdef _simd_u64x2_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_exp_instruction_set };
	};
#endif
#ifdef _simd_u64x2_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_log_instruction_set };
	};
#endif
#ifdef _simd_u64x2_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_log2_instruction_set };
	};
#endif
#ifdef _simd_u64x2_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_log10_instruction_set };
	};
#endif
#ifdef _simd_u64x2_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_ceil_instruction_set };
	};
#endif
#ifdef _simd_u64x2_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_floor_instruction_set };
	};
#endif
#ifdef _simd_u64x2_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_round_instruction_set };
	};
#endif
#ifdef _simd_u64x2_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_sin_instruction_set };
	};
#endif
#ifdef _simd_u64x2_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_cos_instruction_set };
	};
#endif
#ifdef _simd_u64x2_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_tan_instruction_set };
	};
#endif
#ifdef _simd_u64x2_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_asin_instruction_set };
	};
#endif
#ifdef _simd_u64x2_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_acos_instruction_set };
	};
#endif
#ifdef _simd_u64x2_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_atan_instruction_set };
	};
#endif
#ifdef _simd_u64x2_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_sinh_instruction_set };
	};
#endif
#ifdef _simd_u64x2_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_cosh_instruction_set };
	};
#endif
#ifdef _simd_u64x2_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_tanh_instruction_set };
	};
#endif
#ifdef _simd_u64x2_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_sqrt_instruction_set };
	};
#endif
#ifdef _simd_u64x2_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_cbrt_instruction_set };
	};
#endif
#ifdef _simd_u64x2_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_avg_instruction_set };
	};
#endif
#ifdef _simd_u64x2_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_sum_instruction_set };
	};
#endif
#ifdef _simd_u64x2_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_u64x1, 2> {
		enum : int64_t { value = _simd_u64x2_popcount_instruction_set };
	};
#endif
#ifdef _simd_u64x4_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_fma_instruction_set };
	};
#endif
#ifdef _simd_u64x4_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_fms_instruction_set };
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
#ifdef _simd_u64x4_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_lshift_instruction_set };
	};
#endif
#ifdef _simd_u64x4_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_rshift_instruction_set };
	};
#endif
#ifdef _simd_u64x4_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_atan2_instruction_set };
	};
#endif
#ifdef _simd_u64x4_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_reflect_instruction_set };
	};
#endif
#ifdef _simd_u64x4_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_not_instruction_set };
	};
#endif
#ifdef _simd_u64x4_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_abs_instruction_set };
	};
#endif
#ifdef _simd_u64x4_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_exp_instruction_set };
	};
#endif
#ifdef _simd_u64x4_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_log_instruction_set };
	};
#endif
#ifdef _simd_u64x4_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_log2_instruction_set };
	};
#endif
#ifdef _simd_u64x4_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_log10_instruction_set };
	};
#endif
#ifdef _simd_u64x4_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_ceil_instruction_set };
	};
#endif
#ifdef _simd_u64x4_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_floor_instruction_set };
	};
#endif
#ifdef _simd_u64x4_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_round_instruction_set };
	};
#endif
#ifdef _simd_u64x4_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_sin_instruction_set };
	};
#endif
#ifdef _simd_u64x4_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_cos_instruction_set };
	};
#endif
#ifdef _simd_u64x4_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_tan_instruction_set };
	};
#endif
#ifdef _simd_u64x4_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_asin_instruction_set };
	};
#endif
#ifdef _simd_u64x4_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_acos_instruction_set };
	};
#endif
#ifdef _simd_u64x4_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_atan_instruction_set };
	};
#endif
#ifdef _simd_u64x4_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_sinh_instruction_set };
	};
#endif
#ifdef _simd_u64x4_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_cosh_instruction_set };
	};
#endif
#ifdef _simd_u64x4_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_tanh_instruction_set };
	};
#endif
#ifdef _simd_u64x4_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_sqrt_instruction_set };
	};
#endif
#ifdef _simd_u64x4_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_cbrt_instruction_set };
	};
#endif
#ifdef _simd_u64x4_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_avg_instruction_set };
	};
#endif
#ifdef _simd_u64x4_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_sum_instruction_set };
	};
#endif
#ifdef _simd_u64x4_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_u64x1, 4> {
		enum : int64_t { value = _simd_u64x4_popcount_instruction_set };
	};
#endif
#ifdef _simd_u64x8_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_fma_instruction_set };
	};
#endif
#ifdef _simd_u64x8_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_fms_instruction_set };
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
#ifdef _simd_u64x8_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_lshift_instruction_set };
	};
#endif
#ifdef _simd_u64x8_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_rshift_instruction_set };
	};
#endif
#ifdef _simd_u64x8_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_atan2_instruction_set };
	};
#endif
#ifdef _simd_u64x8_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_reflect_instruction_set };
	};
#endif
#ifdef _simd_u64x8_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_not_instruction_set };
	};
#endif
#ifdef _simd_u64x8_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_abs_instruction_set };
	};
#endif
#ifdef _simd_u64x8_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_exp_instruction_set };
	};
#endif
#ifdef _simd_u64x8_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_log_instruction_set };
	};
#endif
#ifdef _simd_u64x8_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_log2_instruction_set };
	};
#endif
#ifdef _simd_u64x8_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_log10_instruction_set };
	};
#endif
#ifdef _simd_u64x8_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_ceil_instruction_set };
	};
#endif
#ifdef _simd_u64x8_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_floor_instruction_set };
	};
#endif
#ifdef _simd_u64x8_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_round_instruction_set };
	};
#endif
#ifdef _simd_u64x8_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_sin_instruction_set };
	};
#endif
#ifdef _simd_u64x8_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_cos_instruction_set };
	};
#endif
#ifdef _simd_u64x8_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_tan_instruction_set };
	};
#endif
#ifdef _simd_u64x8_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_asin_instruction_set };
	};
#endif
#ifdef _simd_u64x8_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_acos_instruction_set };
	};
#endif
#ifdef _simd_u64x8_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_atan_instruction_set };
	};
#endif
#ifdef _simd_u64x8_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_sinh_instruction_set };
	};
#endif
#ifdef _simd_u64x8_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_cosh_instruction_set };
	};
#endif
#ifdef _simd_u64x8_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_tanh_instruction_set };
	};
#endif
#ifdef _simd_u64x8_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_sqrt_instruction_set };
	};
#endif
#ifdef _simd_u64x8_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_cbrt_instruction_set };
	};
#endif
#ifdef _simd_u64x8_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_avg_instruction_set };
	};
#endif
#ifdef _simd_u64x8_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_sum_instruction_set };
	};
#endif
#ifdef _simd_u64x8_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_u64x1, 8> {
		enum : int64_t { value = _simd_u64x8_popcount_instruction_set };
	};
#endif
#ifdef _simd_u64x16_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_fma_instruction_set };
	};
#endif
#ifdef _simd_u64x16_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_fms_instruction_set };
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
#ifdef _simd_u64x16_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_lshift_instruction_set };
	};
#endif
#ifdef _simd_u64x16_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_rshift_instruction_set };
	};
#endif
#ifdef _simd_u64x16_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_atan2_instruction_set };
	};
#endif
#ifdef _simd_u64x16_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_reflect_instruction_set };
	};
#endif
#ifdef _simd_u64x16_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_not_instruction_set };
	};
#endif
#ifdef _simd_u64x16_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_abs_instruction_set };
	};
#endif
#ifdef _simd_u64x16_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_exp_instruction_set };
	};
#endif
#ifdef _simd_u64x16_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_log_instruction_set };
	};
#endif
#ifdef _simd_u64x16_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_log2_instruction_set };
	};
#endif
#ifdef _simd_u64x16_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_log10_instruction_set };
	};
#endif
#ifdef _simd_u64x16_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_ceil_instruction_set };
	};
#endif
#ifdef _simd_u64x16_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_floor_instruction_set };
	};
#endif
#ifdef _simd_u64x16_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_round_instruction_set };
	};
#endif
#ifdef _simd_u64x16_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_sin_instruction_set };
	};
#endif
#ifdef _simd_u64x16_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_cos_instruction_set };
	};
#endif
#ifdef _simd_u64x16_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_tan_instruction_set };
	};
#endif
#ifdef _simd_u64x16_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_asin_instruction_set };
	};
#endif
#ifdef _simd_u64x16_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_acos_instruction_set };
	};
#endif
#ifdef _simd_u64x16_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_atan_instruction_set };
	};
#endif
#ifdef _simd_u64x16_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_sinh_instruction_set };
	};
#endif
#ifdef _simd_u64x16_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_cosh_instruction_set };
	};
#endif
#ifdef _simd_u64x16_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_tanh_instruction_set };
	};
#endif
#ifdef _simd_u64x16_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_sqrt_instruction_set };
	};
#endif
#ifdef _simd_u64x16_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_cbrt_instruction_set };
	};
#endif
#ifdef _simd_u64x16_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_avg_instruction_set };
	};
#endif
#ifdef _simd_u64x16_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_sum_instruction_set };
	};
#endif
#ifdef _simd_u64x16_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_u64x1, 16> {
		enum : int64_t { value = _simd_u64x16_popcount_instruction_set };
	};
#endif
#ifdef _simd_u64x32_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_fma_instruction_set };
	};
#endif
#ifdef _simd_u64x32_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_fms_instruction_set };
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
#ifdef _simd_u64x32_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_lshift_instruction_set };
	};
#endif
#ifdef _simd_u64x32_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_rshift_instruction_set };
	};
#endif
#ifdef _simd_u64x32_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_atan2_instruction_set };
	};
#endif
#ifdef _simd_u64x32_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_reflect_instruction_set };
	};
#endif
#ifdef _simd_u64x32_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_not_instruction_set };
	};
#endif
#ifdef _simd_u64x32_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_abs_instruction_set };
	};
#endif
#ifdef _simd_u64x32_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_exp_instruction_set };
	};
#endif
#ifdef _simd_u64x32_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_log_instruction_set };
	};
#endif
#ifdef _simd_u64x32_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_log2_instruction_set };
	};
#endif
#ifdef _simd_u64x32_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_log10_instruction_set };
	};
#endif
#ifdef _simd_u64x32_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_ceil_instruction_set };
	};
#endif
#ifdef _simd_u64x32_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_floor_instruction_set };
	};
#endif
#ifdef _simd_u64x32_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_round_instruction_set };
	};
#endif
#ifdef _simd_u64x32_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_sin_instruction_set };
	};
#endif
#ifdef _simd_u64x32_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_cos_instruction_set };
	};
#endif
#ifdef _simd_u64x32_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_tan_instruction_set };
	};
#endif
#ifdef _simd_u64x32_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_asin_instruction_set };
	};
#endif
#ifdef _simd_u64x32_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_acos_instruction_set };
	};
#endif
#ifdef _simd_u64x32_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_atan_instruction_set };
	};
#endif
#ifdef _simd_u64x32_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_sinh_instruction_set };
	};
#endif
#ifdef _simd_u64x32_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_cosh_instruction_set };
	};
#endif
#ifdef _simd_u64x32_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_tanh_instruction_set };
	};
#endif
#ifdef _simd_u64x32_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_sqrt_instruction_set };
	};
#endif
#ifdef _simd_u64x32_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_cbrt_instruction_set };
	};
#endif
#ifdef _simd_u64x32_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_avg_instruction_set };
	};
#endif
#ifdef _simd_u64x32_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_sum_instruction_set };
	};
#endif
#ifdef _simd_u64x32_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_u64x1, 32> {
		enum : int64_t { value = _simd_u64x32_popcount_instruction_set };
	};
#endif
#ifdef _simd_u64x64_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_fma_instruction_set };
	};
#endif
#ifdef _simd_u64x64_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_fms_instruction_set };
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
#ifdef _simd_u64x64_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_lshift_instruction_set };
	};
#endif
#ifdef _simd_u64x64_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_rshift_instruction_set };
	};
#endif
#ifdef _simd_u64x64_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_atan2_instruction_set };
	};
#endif
#ifdef _simd_u64x64_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_reflect_instruction_set };
	};
#endif
#ifdef _simd_u64x64_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_not_instruction_set };
	};
#endif
#ifdef _simd_u64x64_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_abs_instruction_set };
	};
#endif
#ifdef _simd_u64x64_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_exp_instruction_set };
	};
#endif
#ifdef _simd_u64x64_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_log_instruction_set };
	};
#endif
#ifdef _simd_u64x64_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_log2_instruction_set };
	};
#endif
#ifdef _simd_u64x64_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_log10_instruction_set };
	};
#endif
#ifdef _simd_u64x64_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_ceil_instruction_set };
	};
#endif
#ifdef _simd_u64x64_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_floor_instruction_set };
	};
#endif
#ifdef _simd_u64x64_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_round_instruction_set };
	};
#endif
#ifdef _simd_u64x64_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_sin_instruction_set };
	};
#endif
#ifdef _simd_u64x64_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_cos_instruction_set };
	};
#endif
#ifdef _simd_u64x64_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_tan_instruction_set };
	};
#endif
#ifdef _simd_u64x64_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_asin_instruction_set };
	};
#endif
#ifdef _simd_u64x64_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_acos_instruction_set };
	};
#endif
#ifdef _simd_u64x64_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_atan_instruction_set };
	};
#endif
#ifdef _simd_u64x64_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_sinh_instruction_set };
	};
#endif
#ifdef _simd_u64x64_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_cosh_instruction_set };
	};
#endif
#ifdef _simd_u64x64_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_tanh_instruction_set };
	};
#endif
#ifdef _simd_u64x64_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_sqrt_instruction_set };
	};
#endif
#ifdef _simd_u64x64_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_cbrt_instruction_set };
	};
#endif
#ifdef _simd_u64x64_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_avg_instruction_set };
	};
#endif
#ifdef _simd_u64x64_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_sum_instruction_set };
	};
#endif
#ifdef _simd_u64x64_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_u64x1, 64> {
		enum : int64_t { value = _simd_u64x64_popcount_instruction_set };
	};
#endif
#ifdef _simd_s32x2_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_fma_instruction_set };
	};
#endif
#ifdef _simd_s32x2_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_fms_instruction_set };
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
#ifdef _simd_s32x2_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_lshift_instruction_set };
	};
#endif
#ifdef _simd_s32x2_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_rshift_instruction_set };
	};
#endif
#ifdef _simd_s32x2_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_atan2_instruction_set };
	};
#endif
#ifdef _simd_s32x2_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_reflect_instruction_set };
	};
#endif
#ifdef _simd_s32x2_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_not_instruction_set };
	};
#endif
#ifdef _simd_s32x2_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_abs_instruction_set };
	};
#endif
#ifdef _simd_s32x2_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_exp_instruction_set };
	};
#endif
#ifdef _simd_s32x2_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_log_instruction_set };
	};
#endif
#ifdef _simd_s32x2_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_log2_instruction_set };
	};
#endif
#ifdef _simd_s32x2_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_log10_instruction_set };
	};
#endif
#ifdef _simd_s32x2_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_ceil_instruction_set };
	};
#endif
#ifdef _simd_s32x2_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_floor_instruction_set };
	};
#endif
#ifdef _simd_s32x2_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_round_instruction_set };
	};
#endif
#ifdef _simd_s32x2_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_sin_instruction_set };
	};
#endif
#ifdef _simd_s32x2_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_cos_instruction_set };
	};
#endif
#ifdef _simd_s32x2_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_tan_instruction_set };
	};
#endif
#ifdef _simd_s32x2_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_asin_instruction_set };
	};
#endif
#ifdef _simd_s32x2_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_acos_instruction_set };
	};
#endif
#ifdef _simd_s32x2_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_atan_instruction_set };
	};
#endif
#ifdef _simd_s32x2_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_sinh_instruction_set };
	};
#endif
#ifdef _simd_s32x2_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_cosh_instruction_set };
	};
#endif
#ifdef _simd_s32x2_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_tanh_instruction_set };
	};
#endif
#ifdef _simd_s32x2_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_sqrt_instruction_set };
	};
#endif
#ifdef _simd_s32x2_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_cbrt_instruction_set };
	};
#endif
#ifdef _simd_s32x2_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_avg_instruction_set };
	};
#endif
#ifdef _simd_s32x2_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_sum_instruction_set };
	};
#endif
#ifdef _simd_s32x2_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_s32x1, 2> {
		enum : int64_t { value = _simd_s32x2_popcount_instruction_set };
	};
#endif
#ifdef _simd_s32x4_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_fma_instruction_set };
	};
#endif
#ifdef _simd_s32x4_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_fms_instruction_set };
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
#ifdef _simd_s32x4_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_lshift_instruction_set };
	};
#endif
#ifdef _simd_s32x4_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_rshift_instruction_set };
	};
#endif
#ifdef _simd_s32x4_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_atan2_instruction_set };
	};
#endif
#ifdef _simd_s32x4_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_reflect_instruction_set };
	};
#endif
#ifdef _simd_s32x4_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_not_instruction_set };
	};
#endif
#ifdef _simd_s32x4_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_abs_instruction_set };
	};
#endif
#ifdef _simd_s32x4_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_exp_instruction_set };
	};
#endif
#ifdef _simd_s32x4_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_log_instruction_set };
	};
#endif
#ifdef _simd_s32x4_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_log2_instruction_set };
	};
#endif
#ifdef _simd_s32x4_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_log10_instruction_set };
	};
#endif
#ifdef _simd_s32x4_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_ceil_instruction_set };
	};
#endif
#ifdef _simd_s32x4_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_floor_instruction_set };
	};
#endif
#ifdef _simd_s32x4_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_round_instruction_set };
	};
#endif
#ifdef _simd_s32x4_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_sin_instruction_set };
	};
#endif
#ifdef _simd_s32x4_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_cos_instruction_set };
	};
#endif
#ifdef _simd_s32x4_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_tan_instruction_set };
	};
#endif
#ifdef _simd_s32x4_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_asin_instruction_set };
	};
#endif
#ifdef _simd_s32x4_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_acos_instruction_set };
	};
#endif
#ifdef _simd_s32x4_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_atan_instruction_set };
	};
#endif
#ifdef _simd_s32x4_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_sinh_instruction_set };
	};
#endif
#ifdef _simd_s32x4_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_cosh_instruction_set };
	};
#endif
#ifdef _simd_s32x4_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_tanh_instruction_set };
	};
#endif
#ifdef _simd_s32x4_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_sqrt_instruction_set };
	};
#endif
#ifdef _simd_s32x4_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_cbrt_instruction_set };
	};
#endif
#ifdef _simd_s32x4_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_avg_instruction_set };
	};
#endif
#ifdef _simd_s32x4_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_sum_instruction_set };
	};
#endif
#ifdef _simd_s32x4_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_s32x1, 4> {
		enum : int64_t { value = _simd_s32x4_popcount_instruction_set };
	};
#endif
#ifdef _simd_s32x8_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_fma_instruction_set };
	};
#endif
#ifdef _simd_s32x8_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_fms_instruction_set };
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
#ifdef _simd_s32x8_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_lshift_instruction_set };
	};
#endif
#ifdef _simd_s32x8_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_rshift_instruction_set };
	};
#endif
#ifdef _simd_s32x8_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_atan2_instruction_set };
	};
#endif
#ifdef _simd_s32x8_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_reflect_instruction_set };
	};
#endif
#ifdef _simd_s32x8_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_not_instruction_set };
	};
#endif
#ifdef _simd_s32x8_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_abs_instruction_set };
	};
#endif
#ifdef _simd_s32x8_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_exp_instruction_set };
	};
#endif
#ifdef _simd_s32x8_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_log_instruction_set };
	};
#endif
#ifdef _simd_s32x8_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_log2_instruction_set };
	};
#endif
#ifdef _simd_s32x8_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_log10_instruction_set };
	};
#endif
#ifdef _simd_s32x8_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_ceil_instruction_set };
	};
#endif
#ifdef _simd_s32x8_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_floor_instruction_set };
	};
#endif
#ifdef _simd_s32x8_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_round_instruction_set };
	};
#endif
#ifdef _simd_s32x8_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_sin_instruction_set };
	};
#endif
#ifdef _simd_s32x8_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_cos_instruction_set };
	};
#endif
#ifdef _simd_s32x8_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_tan_instruction_set };
	};
#endif
#ifdef _simd_s32x8_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_asin_instruction_set };
	};
#endif
#ifdef _simd_s32x8_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_acos_instruction_set };
	};
#endif
#ifdef _simd_s32x8_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_atan_instruction_set };
	};
#endif
#ifdef _simd_s32x8_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_sinh_instruction_set };
	};
#endif
#ifdef _simd_s32x8_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_cosh_instruction_set };
	};
#endif
#ifdef _simd_s32x8_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_tanh_instruction_set };
	};
#endif
#ifdef _simd_s32x8_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_sqrt_instruction_set };
	};
#endif
#ifdef _simd_s32x8_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_cbrt_instruction_set };
	};
#endif
#ifdef _simd_s32x8_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_avg_instruction_set };
	};
#endif
#ifdef _simd_s32x8_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_sum_instruction_set };
	};
#endif
#ifdef _simd_s32x8_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_s32x1, 8> {
		enum : int64_t { value = _simd_s32x8_popcount_instruction_set };
	};
#endif
#ifdef _simd_s32x16_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_fma_instruction_set };
	};
#endif
#ifdef _simd_s32x16_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_fms_instruction_set };
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
#ifdef _simd_s32x16_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_lshift_instruction_set };
	};
#endif
#ifdef _simd_s32x16_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_rshift_instruction_set };
	};
#endif
#ifdef _simd_s32x16_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_atan2_instruction_set };
	};
#endif
#ifdef _simd_s32x16_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_reflect_instruction_set };
	};
#endif
#ifdef _simd_s32x16_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_not_instruction_set };
	};
#endif
#ifdef _simd_s32x16_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_abs_instruction_set };
	};
#endif
#ifdef _simd_s32x16_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_exp_instruction_set };
	};
#endif
#ifdef _simd_s32x16_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_log_instruction_set };
	};
#endif
#ifdef _simd_s32x16_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_log2_instruction_set };
	};
#endif
#ifdef _simd_s32x16_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_log10_instruction_set };
	};
#endif
#ifdef _simd_s32x16_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_ceil_instruction_set };
	};
#endif
#ifdef _simd_s32x16_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_floor_instruction_set };
	};
#endif
#ifdef _simd_s32x16_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_round_instruction_set };
	};
#endif
#ifdef _simd_s32x16_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_sin_instruction_set };
	};
#endif
#ifdef _simd_s32x16_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_cos_instruction_set };
	};
#endif
#ifdef _simd_s32x16_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_tan_instruction_set };
	};
#endif
#ifdef _simd_s32x16_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_asin_instruction_set };
	};
#endif
#ifdef _simd_s32x16_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_acos_instruction_set };
	};
#endif
#ifdef _simd_s32x16_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_atan_instruction_set };
	};
#endif
#ifdef _simd_s32x16_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_sinh_instruction_set };
	};
#endif
#ifdef _simd_s32x16_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_cosh_instruction_set };
	};
#endif
#ifdef _simd_s32x16_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_tanh_instruction_set };
	};
#endif
#ifdef _simd_s32x16_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_sqrt_instruction_set };
	};
#endif
#ifdef _simd_s32x16_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_cbrt_instruction_set };
	};
#endif
#ifdef _simd_s32x16_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_avg_instruction_set };
	};
#endif
#ifdef _simd_s32x16_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_sum_instruction_set };
	};
#endif
#ifdef _simd_s32x16_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_s32x1, 16> {
		enum : int64_t { value = _simd_s32x16_popcount_instruction_set };
	};
#endif
#ifdef _simd_s32x32_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_fma_instruction_set };
	};
#endif
#ifdef _simd_s32x32_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_fms_instruction_set };
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
#ifdef _simd_s32x32_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_lshift_instruction_set };
	};
#endif
#ifdef _simd_s32x32_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_rshift_instruction_set };
	};
#endif
#ifdef _simd_s32x32_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_atan2_instruction_set };
	};
#endif
#ifdef _simd_s32x32_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_reflect_instruction_set };
	};
#endif
#ifdef _simd_s32x32_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_not_instruction_set };
	};
#endif
#ifdef _simd_s32x32_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_abs_instruction_set };
	};
#endif
#ifdef _simd_s32x32_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_exp_instruction_set };
	};
#endif
#ifdef _simd_s32x32_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_log_instruction_set };
	};
#endif
#ifdef _simd_s32x32_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_log2_instruction_set };
	};
#endif
#ifdef _simd_s32x32_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_log10_instruction_set };
	};
#endif
#ifdef _simd_s32x32_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_ceil_instruction_set };
	};
#endif
#ifdef _simd_s32x32_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_floor_instruction_set };
	};
#endif
#ifdef _simd_s32x32_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_round_instruction_set };
	};
#endif
#ifdef _simd_s32x32_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_sin_instruction_set };
	};
#endif
#ifdef _simd_s32x32_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_cos_instruction_set };
	};
#endif
#ifdef _simd_s32x32_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_tan_instruction_set };
	};
#endif
#ifdef _simd_s32x32_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_asin_instruction_set };
	};
#endif
#ifdef _simd_s32x32_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_acos_instruction_set };
	};
#endif
#ifdef _simd_s32x32_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_atan_instruction_set };
	};
#endif
#ifdef _simd_s32x32_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_sinh_instruction_set };
	};
#endif
#ifdef _simd_s32x32_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_cosh_instruction_set };
	};
#endif
#ifdef _simd_s32x32_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_tanh_instruction_set };
	};
#endif
#ifdef _simd_s32x32_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_sqrt_instruction_set };
	};
#endif
#ifdef _simd_s32x32_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_cbrt_instruction_set };
	};
#endif
#ifdef _simd_s32x32_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_avg_instruction_set };
	};
#endif
#ifdef _simd_s32x32_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_sum_instruction_set };
	};
#endif
#ifdef _simd_s32x32_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_s32x1, 32> {
		enum : int64_t { value = _simd_s32x32_popcount_instruction_set };
	};
#endif
#ifdef _simd_s32x64_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_fma_instruction_set };
	};
#endif
#ifdef _simd_s32x64_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_fms_instruction_set };
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
#ifdef _simd_s32x64_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_lshift_instruction_set };
	};
#endif
#ifdef _simd_s32x64_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_rshift_instruction_set };
	};
#endif
#ifdef _simd_s32x64_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_atan2_instruction_set };
	};
#endif
#ifdef _simd_s32x64_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_reflect_instruction_set };
	};
#endif
#ifdef _simd_s32x64_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_not_instruction_set };
	};
#endif
#ifdef _simd_s32x64_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_abs_instruction_set };
	};
#endif
#ifdef _simd_s32x64_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_exp_instruction_set };
	};
#endif
#ifdef _simd_s32x64_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_log_instruction_set };
	};
#endif
#ifdef _simd_s32x64_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_log2_instruction_set };
	};
#endif
#ifdef _simd_s32x64_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_log10_instruction_set };
	};
#endif
#ifdef _simd_s32x64_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_ceil_instruction_set };
	};
#endif
#ifdef _simd_s32x64_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_floor_instruction_set };
	};
#endif
#ifdef _simd_s32x64_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_round_instruction_set };
	};
#endif
#ifdef _simd_s32x64_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_sin_instruction_set };
	};
#endif
#ifdef _simd_s32x64_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_cos_instruction_set };
	};
#endif
#ifdef _simd_s32x64_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_tan_instruction_set };
	};
#endif
#ifdef _simd_s32x64_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_asin_instruction_set };
	};
#endif
#ifdef _simd_s32x64_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_acos_instruction_set };
	};
#endif
#ifdef _simd_s32x64_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_atan_instruction_set };
	};
#endif
#ifdef _simd_s32x64_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_sinh_instruction_set };
	};
#endif
#ifdef _simd_s32x64_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_cosh_instruction_set };
	};
#endif
#ifdef _simd_s32x64_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_tanh_instruction_set };
	};
#endif
#ifdef _simd_s32x64_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_sqrt_instruction_set };
	};
#endif
#ifdef _simd_s32x64_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_cbrt_instruction_set };
	};
#endif
#ifdef _simd_s32x64_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_avg_instruction_set };
	};
#endif
#ifdef _simd_s32x64_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_sum_instruction_set };
	};
#endif
#ifdef _simd_s32x64_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_s32x1, 64> {
		enum : int64_t { value = _simd_s32x64_popcount_instruction_set };
	};
#endif
#ifdef _simd_u32x2_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_fma_instruction_set };
	};
#endif
#ifdef _simd_u32x2_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_fms_instruction_set };
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
#ifdef _simd_u32x2_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_lshift_instruction_set };
	};
#endif
#ifdef _simd_u32x2_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_rshift_instruction_set };
	};
#endif
#ifdef _simd_u32x2_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_atan2_instruction_set };
	};
#endif
#ifdef _simd_u32x2_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_reflect_instruction_set };
	};
#endif
#ifdef _simd_u32x2_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_not_instruction_set };
	};
#endif
#ifdef _simd_u32x2_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_abs_instruction_set };
	};
#endif
#ifdef _simd_u32x2_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_exp_instruction_set };
	};
#endif
#ifdef _simd_u32x2_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_log_instruction_set };
	};
#endif
#ifdef _simd_u32x2_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_log2_instruction_set };
	};
#endif
#ifdef _simd_u32x2_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_log10_instruction_set };
	};
#endif
#ifdef _simd_u32x2_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_ceil_instruction_set };
	};
#endif
#ifdef _simd_u32x2_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_floor_instruction_set };
	};
#endif
#ifdef _simd_u32x2_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_round_instruction_set };
	};
#endif
#ifdef _simd_u32x2_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_sin_instruction_set };
	};
#endif
#ifdef _simd_u32x2_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_cos_instruction_set };
	};
#endif
#ifdef _simd_u32x2_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_tan_instruction_set };
	};
#endif
#ifdef _simd_u32x2_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_asin_instruction_set };
	};
#endif
#ifdef _simd_u32x2_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_acos_instruction_set };
	};
#endif
#ifdef _simd_u32x2_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_atan_instruction_set };
	};
#endif
#ifdef _simd_u32x2_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_sinh_instruction_set };
	};
#endif
#ifdef _simd_u32x2_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_cosh_instruction_set };
	};
#endif
#ifdef _simd_u32x2_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_tanh_instruction_set };
	};
#endif
#ifdef _simd_u32x2_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_sqrt_instruction_set };
	};
#endif
#ifdef _simd_u32x2_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_cbrt_instruction_set };
	};
#endif
#ifdef _simd_u32x2_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_avg_instruction_set };
	};
#endif
#ifdef _simd_u32x2_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_sum_instruction_set };
	};
#endif
#ifdef _simd_u32x2_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_u32x1, 2> {
		enum : int64_t { value = _simd_u32x2_popcount_instruction_set };
	};
#endif
#ifdef _simd_u32x4_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_fma_instruction_set };
	};
#endif
#ifdef _simd_u32x4_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_fms_instruction_set };
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
#ifdef _simd_u32x4_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_lshift_instruction_set };
	};
#endif
#ifdef _simd_u32x4_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_rshift_instruction_set };
	};
#endif
#ifdef _simd_u32x4_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_atan2_instruction_set };
	};
#endif
#ifdef _simd_u32x4_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_reflect_instruction_set };
	};
#endif
#ifdef _simd_u32x4_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_not_instruction_set };
	};
#endif
#ifdef _simd_u32x4_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_abs_instruction_set };
	};
#endif
#ifdef _simd_u32x4_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_exp_instruction_set };
	};
#endif
#ifdef _simd_u32x4_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_log_instruction_set };
	};
#endif
#ifdef _simd_u32x4_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_log2_instruction_set };
	};
#endif
#ifdef _simd_u32x4_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_log10_instruction_set };
	};
#endif
#ifdef _simd_u32x4_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_ceil_instruction_set };
	};
#endif
#ifdef _simd_u32x4_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_floor_instruction_set };
	};
#endif
#ifdef _simd_u32x4_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_round_instruction_set };
	};
#endif
#ifdef _simd_u32x4_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_sin_instruction_set };
	};
#endif
#ifdef _simd_u32x4_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_cos_instruction_set };
	};
#endif
#ifdef _simd_u32x4_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_tan_instruction_set };
	};
#endif
#ifdef _simd_u32x4_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_asin_instruction_set };
	};
#endif
#ifdef _simd_u32x4_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_acos_instruction_set };
	};
#endif
#ifdef _simd_u32x4_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_atan_instruction_set };
	};
#endif
#ifdef _simd_u32x4_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_sinh_instruction_set };
	};
#endif
#ifdef _simd_u32x4_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_cosh_instruction_set };
	};
#endif
#ifdef _simd_u32x4_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_tanh_instruction_set };
	};
#endif
#ifdef _simd_u32x4_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_sqrt_instruction_set };
	};
#endif
#ifdef _simd_u32x4_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_cbrt_instruction_set };
	};
#endif
#ifdef _simd_u32x4_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_avg_instruction_set };
	};
#endif
#ifdef _simd_u32x4_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_sum_instruction_set };
	};
#endif
#ifdef _simd_u32x4_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_u32x1, 4> {
		enum : int64_t { value = _simd_u32x4_popcount_instruction_set };
	};
#endif
#ifdef _simd_u32x8_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_fma_instruction_set };
	};
#endif
#ifdef _simd_u32x8_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_fms_instruction_set };
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
#ifdef _simd_u32x8_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_lshift_instruction_set };
	};
#endif
#ifdef _simd_u32x8_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_rshift_instruction_set };
	};
#endif
#ifdef _simd_u32x8_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_atan2_instruction_set };
	};
#endif
#ifdef _simd_u32x8_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_reflect_instruction_set };
	};
#endif
#ifdef _simd_u32x8_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_not_instruction_set };
	};
#endif
#ifdef _simd_u32x8_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_abs_instruction_set };
	};
#endif
#ifdef _simd_u32x8_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_exp_instruction_set };
	};
#endif
#ifdef _simd_u32x8_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_log_instruction_set };
	};
#endif
#ifdef _simd_u32x8_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_log2_instruction_set };
	};
#endif
#ifdef _simd_u32x8_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_log10_instruction_set };
	};
#endif
#ifdef _simd_u32x8_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_ceil_instruction_set };
	};
#endif
#ifdef _simd_u32x8_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_floor_instruction_set };
	};
#endif
#ifdef _simd_u32x8_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_round_instruction_set };
	};
#endif
#ifdef _simd_u32x8_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_sin_instruction_set };
	};
#endif
#ifdef _simd_u32x8_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_cos_instruction_set };
	};
#endif
#ifdef _simd_u32x8_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_tan_instruction_set };
	};
#endif
#ifdef _simd_u32x8_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_asin_instruction_set };
	};
#endif
#ifdef _simd_u32x8_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_acos_instruction_set };
	};
#endif
#ifdef _simd_u32x8_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_atan_instruction_set };
	};
#endif
#ifdef _simd_u32x8_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_sinh_instruction_set };
	};
#endif
#ifdef _simd_u32x8_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_cosh_instruction_set };
	};
#endif
#ifdef _simd_u32x8_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_tanh_instruction_set };
	};
#endif
#ifdef _simd_u32x8_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_sqrt_instruction_set };
	};
#endif
#ifdef _simd_u32x8_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_cbrt_instruction_set };
	};
#endif
#ifdef _simd_u32x8_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_avg_instruction_set };
	};
#endif
#ifdef _simd_u32x8_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_sum_instruction_set };
	};
#endif
#ifdef _simd_u32x8_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_u32x1, 8> {
		enum : int64_t { value = _simd_u32x8_popcount_instruction_set };
	};
#endif
#ifdef _simd_u32x16_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_fma_instruction_set };
	};
#endif
#ifdef _simd_u32x16_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_fms_instruction_set };
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
#ifdef _simd_u32x16_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_lshift_instruction_set };
	};
#endif
#ifdef _simd_u32x16_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_rshift_instruction_set };
	};
#endif
#ifdef _simd_u32x16_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_atan2_instruction_set };
	};
#endif
#ifdef _simd_u32x16_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_reflect_instruction_set };
	};
#endif
#ifdef _simd_u32x16_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_not_instruction_set };
	};
#endif
#ifdef _simd_u32x16_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_abs_instruction_set };
	};
#endif
#ifdef _simd_u32x16_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_exp_instruction_set };
	};
#endif
#ifdef _simd_u32x16_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_log_instruction_set };
	};
#endif
#ifdef _simd_u32x16_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_log2_instruction_set };
	};
#endif
#ifdef _simd_u32x16_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_log10_instruction_set };
	};
#endif
#ifdef _simd_u32x16_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_ceil_instruction_set };
	};
#endif
#ifdef _simd_u32x16_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_floor_instruction_set };
	};
#endif
#ifdef _simd_u32x16_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_round_instruction_set };
	};
#endif
#ifdef _simd_u32x16_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_sin_instruction_set };
	};
#endif
#ifdef _simd_u32x16_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_cos_instruction_set };
	};
#endif
#ifdef _simd_u32x16_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_tan_instruction_set };
	};
#endif
#ifdef _simd_u32x16_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_asin_instruction_set };
	};
#endif
#ifdef _simd_u32x16_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_acos_instruction_set };
	};
#endif
#ifdef _simd_u32x16_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_atan_instruction_set };
	};
#endif
#ifdef _simd_u32x16_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_sinh_instruction_set };
	};
#endif
#ifdef _simd_u32x16_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_cosh_instruction_set };
	};
#endif
#ifdef _simd_u32x16_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_tanh_instruction_set };
	};
#endif
#ifdef _simd_u32x16_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_sqrt_instruction_set };
	};
#endif
#ifdef _simd_u32x16_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_cbrt_instruction_set };
	};
#endif
#ifdef _simd_u32x16_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_avg_instruction_set };
	};
#endif
#ifdef _simd_u32x16_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_sum_instruction_set };
	};
#endif
#ifdef _simd_u32x16_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_u32x1, 16> {
		enum : int64_t { value = _simd_u32x16_popcount_instruction_set };
	};
#endif
#ifdef _simd_u32x32_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_fma_instruction_set };
	};
#endif
#ifdef _simd_u32x32_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_fms_instruction_set };
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
#ifdef _simd_u32x32_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_lshift_instruction_set };
	};
#endif
#ifdef _simd_u32x32_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_rshift_instruction_set };
	};
#endif
#ifdef _simd_u32x32_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_atan2_instruction_set };
	};
#endif
#ifdef _simd_u32x32_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_reflect_instruction_set };
	};
#endif
#ifdef _simd_u32x32_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_not_instruction_set };
	};
#endif
#ifdef _simd_u32x32_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_abs_instruction_set };
	};
#endif
#ifdef _simd_u32x32_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_exp_instruction_set };
	};
#endif
#ifdef _simd_u32x32_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_log_instruction_set };
	};
#endif
#ifdef _simd_u32x32_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_log2_instruction_set };
	};
#endif
#ifdef _simd_u32x32_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_log10_instruction_set };
	};
#endif
#ifdef _simd_u32x32_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_ceil_instruction_set };
	};
#endif
#ifdef _simd_u32x32_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_floor_instruction_set };
	};
#endif
#ifdef _simd_u32x32_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_round_instruction_set };
	};
#endif
#ifdef _simd_u32x32_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_sin_instruction_set };
	};
#endif
#ifdef _simd_u32x32_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_cos_instruction_set };
	};
#endif
#ifdef _simd_u32x32_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_tan_instruction_set };
	};
#endif
#ifdef _simd_u32x32_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_asin_instruction_set };
	};
#endif
#ifdef _simd_u32x32_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_acos_instruction_set };
	};
#endif
#ifdef _simd_u32x32_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_atan_instruction_set };
	};
#endif
#ifdef _simd_u32x32_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_sinh_instruction_set };
	};
#endif
#ifdef _simd_u32x32_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_cosh_instruction_set };
	};
#endif
#ifdef _simd_u32x32_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_tanh_instruction_set };
	};
#endif
#ifdef _simd_u32x32_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_sqrt_instruction_set };
	};
#endif
#ifdef _simd_u32x32_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_cbrt_instruction_set };
	};
#endif
#ifdef _simd_u32x32_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_avg_instruction_set };
	};
#endif
#ifdef _simd_u32x32_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_sum_instruction_set };
	};
#endif
#ifdef _simd_u32x32_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_u32x1, 32> {
		enum : int64_t { value = _simd_u32x32_popcount_instruction_set };
	};
#endif
#ifdef _simd_u32x64_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_fma_instruction_set };
	};
#endif
#ifdef _simd_u32x64_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_fms_instruction_set };
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
#ifdef _simd_u32x64_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_lshift_instruction_set };
	};
#endif
#ifdef _simd_u32x64_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_rshift_instruction_set };
	};
#endif
#ifdef _simd_u32x64_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_atan2_instruction_set };
	};
#endif
#ifdef _simd_u32x64_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_reflect_instruction_set };
	};
#endif
#ifdef _simd_u32x64_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_not_instruction_set };
	};
#endif
#ifdef _simd_u32x64_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_abs_instruction_set };
	};
#endif
#ifdef _simd_u32x64_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_exp_instruction_set };
	};
#endif
#ifdef _simd_u32x64_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_log_instruction_set };
	};
#endif
#ifdef _simd_u32x64_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_log2_instruction_set };
	};
#endif
#ifdef _simd_u32x64_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_log10_instruction_set };
	};
#endif
#ifdef _simd_u32x64_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_ceil_instruction_set };
	};
#endif
#ifdef _simd_u32x64_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_floor_instruction_set };
	};
#endif
#ifdef _simd_u32x64_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_round_instruction_set };
	};
#endif
#ifdef _simd_u32x64_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_sin_instruction_set };
	};
#endif
#ifdef _simd_u32x64_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_cos_instruction_set };
	};
#endif
#ifdef _simd_u32x64_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_tan_instruction_set };
	};
#endif
#ifdef _simd_u32x64_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_asin_instruction_set };
	};
#endif
#ifdef _simd_u32x64_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_acos_instruction_set };
	};
#endif
#ifdef _simd_u32x64_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_atan_instruction_set };
	};
#endif
#ifdef _simd_u32x64_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_sinh_instruction_set };
	};
#endif
#ifdef _simd_u32x64_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_cosh_instruction_set };
	};
#endif
#ifdef _simd_u32x64_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_tanh_instruction_set };
	};
#endif
#ifdef _simd_u32x64_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_sqrt_instruction_set };
	};
#endif
#ifdef _simd_u32x64_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_cbrt_instruction_set };
	};
#endif
#ifdef _simd_u32x64_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_avg_instruction_set };
	};
#endif
#ifdef _simd_u32x64_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_sum_instruction_set };
	};
#endif
#ifdef _simd_u32x64_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_u32x1, 64> {
		enum : int64_t { value = _simd_u32x64_popcount_instruction_set };
	};
#endif
#ifdef _simd_s16x2_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_fma_instruction_set };
	};
#endif
#ifdef _simd_s16x2_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_fms_instruction_set };
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
#ifdef _simd_s16x2_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_lshift_instruction_set };
	};
#endif
#ifdef _simd_s16x2_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_rshift_instruction_set };
	};
#endif
#ifdef _simd_s16x2_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_atan2_instruction_set };
	};
#endif
#ifdef _simd_s16x2_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_reflect_instruction_set };
	};
#endif
#ifdef _simd_s16x2_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_not_instruction_set };
	};
#endif
#ifdef _simd_s16x2_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_abs_instruction_set };
	};
#endif
#ifdef _simd_s16x2_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_exp_instruction_set };
	};
#endif
#ifdef _simd_s16x2_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_log_instruction_set };
	};
#endif
#ifdef _simd_s16x2_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_log2_instruction_set };
	};
#endif
#ifdef _simd_s16x2_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_log10_instruction_set };
	};
#endif
#ifdef _simd_s16x2_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_ceil_instruction_set };
	};
#endif
#ifdef _simd_s16x2_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_floor_instruction_set };
	};
#endif
#ifdef _simd_s16x2_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_round_instruction_set };
	};
#endif
#ifdef _simd_s16x2_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_sin_instruction_set };
	};
#endif
#ifdef _simd_s16x2_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_cos_instruction_set };
	};
#endif
#ifdef _simd_s16x2_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_tan_instruction_set };
	};
#endif
#ifdef _simd_s16x2_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_asin_instruction_set };
	};
#endif
#ifdef _simd_s16x2_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_acos_instruction_set };
	};
#endif
#ifdef _simd_s16x2_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_atan_instruction_set };
	};
#endif
#ifdef _simd_s16x2_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_sinh_instruction_set };
	};
#endif
#ifdef _simd_s16x2_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_cosh_instruction_set };
	};
#endif
#ifdef _simd_s16x2_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_tanh_instruction_set };
	};
#endif
#ifdef _simd_s16x2_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_sqrt_instruction_set };
	};
#endif
#ifdef _simd_s16x2_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_cbrt_instruction_set };
	};
#endif
#ifdef _simd_s16x2_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_avg_instruction_set };
	};
#endif
#ifdef _simd_s16x2_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_sum_instruction_set };
	};
#endif
#ifdef _simd_s16x2_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_s16x1, 2> {
		enum : int64_t { value = _simd_s16x2_popcount_instruction_set };
	};
#endif
#ifdef _simd_s16x4_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_fma_instruction_set };
	};
#endif
#ifdef _simd_s16x4_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_fms_instruction_set };
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
#ifdef _simd_s16x4_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_lshift_instruction_set };
	};
#endif
#ifdef _simd_s16x4_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_rshift_instruction_set };
	};
#endif
#ifdef _simd_s16x4_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_atan2_instruction_set };
	};
#endif
#ifdef _simd_s16x4_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_reflect_instruction_set };
	};
#endif
#ifdef _simd_s16x4_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_not_instruction_set };
	};
#endif
#ifdef _simd_s16x4_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_abs_instruction_set };
	};
#endif
#ifdef _simd_s16x4_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_exp_instruction_set };
	};
#endif
#ifdef _simd_s16x4_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_log_instruction_set };
	};
#endif
#ifdef _simd_s16x4_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_log2_instruction_set };
	};
#endif
#ifdef _simd_s16x4_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_log10_instruction_set };
	};
#endif
#ifdef _simd_s16x4_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_ceil_instruction_set };
	};
#endif
#ifdef _simd_s16x4_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_floor_instruction_set };
	};
#endif
#ifdef _simd_s16x4_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_round_instruction_set };
	};
#endif
#ifdef _simd_s16x4_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_sin_instruction_set };
	};
#endif
#ifdef _simd_s16x4_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_cos_instruction_set };
	};
#endif
#ifdef _simd_s16x4_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_tan_instruction_set };
	};
#endif
#ifdef _simd_s16x4_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_asin_instruction_set };
	};
#endif
#ifdef _simd_s16x4_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_acos_instruction_set };
	};
#endif
#ifdef _simd_s16x4_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_atan_instruction_set };
	};
#endif
#ifdef _simd_s16x4_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_sinh_instruction_set };
	};
#endif
#ifdef _simd_s16x4_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_cosh_instruction_set };
	};
#endif
#ifdef _simd_s16x4_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_tanh_instruction_set };
	};
#endif
#ifdef _simd_s16x4_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_sqrt_instruction_set };
	};
#endif
#ifdef _simd_s16x4_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_cbrt_instruction_set };
	};
#endif
#ifdef _simd_s16x4_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_avg_instruction_set };
	};
#endif
#ifdef _simd_s16x4_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_sum_instruction_set };
	};
#endif
#ifdef _simd_s16x4_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_s16x1, 4> {
		enum : int64_t { value = _simd_s16x4_popcount_instruction_set };
	};
#endif
#ifdef _simd_s16x8_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_fma_instruction_set };
	};
#endif
#ifdef _simd_s16x8_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_fms_instruction_set };
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
#ifdef _simd_s16x8_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_lshift_instruction_set };
	};
#endif
#ifdef _simd_s16x8_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_rshift_instruction_set };
	};
#endif
#ifdef _simd_s16x8_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_atan2_instruction_set };
	};
#endif
#ifdef _simd_s16x8_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_reflect_instruction_set };
	};
#endif
#ifdef _simd_s16x8_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_not_instruction_set };
	};
#endif
#ifdef _simd_s16x8_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_abs_instruction_set };
	};
#endif
#ifdef _simd_s16x8_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_exp_instruction_set };
	};
#endif
#ifdef _simd_s16x8_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_log_instruction_set };
	};
#endif
#ifdef _simd_s16x8_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_log2_instruction_set };
	};
#endif
#ifdef _simd_s16x8_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_log10_instruction_set };
	};
#endif
#ifdef _simd_s16x8_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_ceil_instruction_set };
	};
#endif
#ifdef _simd_s16x8_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_floor_instruction_set };
	};
#endif
#ifdef _simd_s16x8_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_round_instruction_set };
	};
#endif
#ifdef _simd_s16x8_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_sin_instruction_set };
	};
#endif
#ifdef _simd_s16x8_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_cos_instruction_set };
	};
#endif
#ifdef _simd_s16x8_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_tan_instruction_set };
	};
#endif
#ifdef _simd_s16x8_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_asin_instruction_set };
	};
#endif
#ifdef _simd_s16x8_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_acos_instruction_set };
	};
#endif
#ifdef _simd_s16x8_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_atan_instruction_set };
	};
#endif
#ifdef _simd_s16x8_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_sinh_instruction_set };
	};
#endif
#ifdef _simd_s16x8_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_cosh_instruction_set };
	};
#endif
#ifdef _simd_s16x8_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_tanh_instruction_set };
	};
#endif
#ifdef _simd_s16x8_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_sqrt_instruction_set };
	};
#endif
#ifdef _simd_s16x8_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_cbrt_instruction_set };
	};
#endif
#ifdef _simd_s16x8_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_avg_instruction_set };
	};
#endif
#ifdef _simd_s16x8_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_sum_instruction_set };
	};
#endif
#ifdef _simd_s16x8_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_s16x1, 8> {
		enum : int64_t { value = _simd_s16x8_popcount_instruction_set };
	};
#endif
#ifdef _simd_s16x16_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_fma_instruction_set };
	};
#endif
#ifdef _simd_s16x16_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_fms_instruction_set };
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
#ifdef _simd_s16x16_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_lshift_instruction_set };
	};
#endif
#ifdef _simd_s16x16_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_rshift_instruction_set };
	};
#endif
#ifdef _simd_s16x16_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_atan2_instruction_set };
	};
#endif
#ifdef _simd_s16x16_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_reflect_instruction_set };
	};
#endif
#ifdef _simd_s16x16_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_not_instruction_set };
	};
#endif
#ifdef _simd_s16x16_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_abs_instruction_set };
	};
#endif
#ifdef _simd_s16x16_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_exp_instruction_set };
	};
#endif
#ifdef _simd_s16x16_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_log_instruction_set };
	};
#endif
#ifdef _simd_s16x16_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_log2_instruction_set };
	};
#endif
#ifdef _simd_s16x16_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_log10_instruction_set };
	};
#endif
#ifdef _simd_s16x16_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_ceil_instruction_set };
	};
#endif
#ifdef _simd_s16x16_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_floor_instruction_set };
	};
#endif
#ifdef _simd_s16x16_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_round_instruction_set };
	};
#endif
#ifdef _simd_s16x16_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_sin_instruction_set };
	};
#endif
#ifdef _simd_s16x16_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_cos_instruction_set };
	};
#endif
#ifdef _simd_s16x16_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_tan_instruction_set };
	};
#endif
#ifdef _simd_s16x16_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_asin_instruction_set };
	};
#endif
#ifdef _simd_s16x16_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_acos_instruction_set };
	};
#endif
#ifdef _simd_s16x16_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_atan_instruction_set };
	};
#endif
#ifdef _simd_s16x16_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_sinh_instruction_set };
	};
#endif
#ifdef _simd_s16x16_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_cosh_instruction_set };
	};
#endif
#ifdef _simd_s16x16_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_tanh_instruction_set };
	};
#endif
#ifdef _simd_s16x16_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_sqrt_instruction_set };
	};
#endif
#ifdef _simd_s16x16_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_cbrt_instruction_set };
	};
#endif
#ifdef _simd_s16x16_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_avg_instruction_set };
	};
#endif
#ifdef _simd_s16x16_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_sum_instruction_set };
	};
#endif
#ifdef _simd_s16x16_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_s16x1, 16> {
		enum : int64_t { value = _simd_s16x16_popcount_instruction_set };
	};
#endif
#ifdef _simd_s16x32_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_fma_instruction_set };
	};
#endif
#ifdef _simd_s16x32_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_fms_instruction_set };
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
#ifdef _simd_s16x32_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_lshift_instruction_set };
	};
#endif
#ifdef _simd_s16x32_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_rshift_instruction_set };
	};
#endif
#ifdef _simd_s16x32_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_atan2_instruction_set };
	};
#endif
#ifdef _simd_s16x32_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_reflect_instruction_set };
	};
#endif
#ifdef _simd_s16x32_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_not_instruction_set };
	};
#endif
#ifdef _simd_s16x32_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_abs_instruction_set };
	};
#endif
#ifdef _simd_s16x32_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_exp_instruction_set };
	};
#endif
#ifdef _simd_s16x32_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_log_instruction_set };
	};
#endif
#ifdef _simd_s16x32_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_log2_instruction_set };
	};
#endif
#ifdef _simd_s16x32_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_log10_instruction_set };
	};
#endif
#ifdef _simd_s16x32_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_ceil_instruction_set };
	};
#endif
#ifdef _simd_s16x32_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_floor_instruction_set };
	};
#endif
#ifdef _simd_s16x32_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_round_instruction_set };
	};
#endif
#ifdef _simd_s16x32_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_sin_instruction_set };
	};
#endif
#ifdef _simd_s16x32_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_cos_instruction_set };
	};
#endif
#ifdef _simd_s16x32_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_tan_instruction_set };
	};
#endif
#ifdef _simd_s16x32_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_asin_instruction_set };
	};
#endif
#ifdef _simd_s16x32_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_acos_instruction_set };
	};
#endif
#ifdef _simd_s16x32_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_atan_instruction_set };
	};
#endif
#ifdef _simd_s16x32_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_sinh_instruction_set };
	};
#endif
#ifdef _simd_s16x32_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_cosh_instruction_set };
	};
#endif
#ifdef _simd_s16x32_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_tanh_instruction_set };
	};
#endif
#ifdef _simd_s16x32_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_sqrt_instruction_set };
	};
#endif
#ifdef _simd_s16x32_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_cbrt_instruction_set };
	};
#endif
#ifdef _simd_s16x32_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_avg_instruction_set };
	};
#endif
#ifdef _simd_s16x32_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_sum_instruction_set };
	};
#endif
#ifdef _simd_s16x32_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_s16x1, 32> {
		enum : int64_t { value = _simd_s16x32_popcount_instruction_set };
	};
#endif
#ifdef _simd_s16x64_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_fma_instruction_set };
	};
#endif
#ifdef _simd_s16x64_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_fms_instruction_set };
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
#ifdef _simd_s16x64_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_lshift_instruction_set };
	};
#endif
#ifdef _simd_s16x64_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_rshift_instruction_set };
	};
#endif
#ifdef _simd_s16x64_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_atan2_instruction_set };
	};
#endif
#ifdef _simd_s16x64_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_reflect_instruction_set };
	};
#endif
#ifdef _simd_s16x64_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_not_instruction_set };
	};
#endif
#ifdef _simd_s16x64_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_abs_instruction_set };
	};
#endif
#ifdef _simd_s16x64_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_exp_instruction_set };
	};
#endif
#ifdef _simd_s16x64_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_log_instruction_set };
	};
#endif
#ifdef _simd_s16x64_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_log2_instruction_set };
	};
#endif
#ifdef _simd_s16x64_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_log10_instruction_set };
	};
#endif
#ifdef _simd_s16x64_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_ceil_instruction_set };
	};
#endif
#ifdef _simd_s16x64_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_floor_instruction_set };
	};
#endif
#ifdef _simd_s16x64_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_round_instruction_set };
	};
#endif
#ifdef _simd_s16x64_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_sin_instruction_set };
	};
#endif
#ifdef _simd_s16x64_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_cos_instruction_set };
	};
#endif
#ifdef _simd_s16x64_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_tan_instruction_set };
	};
#endif
#ifdef _simd_s16x64_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_asin_instruction_set };
	};
#endif
#ifdef _simd_s16x64_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_acos_instruction_set };
	};
#endif
#ifdef _simd_s16x64_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_atan_instruction_set };
	};
#endif
#ifdef _simd_s16x64_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_sinh_instruction_set };
	};
#endif
#ifdef _simd_s16x64_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_cosh_instruction_set };
	};
#endif
#ifdef _simd_s16x64_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_tanh_instruction_set };
	};
#endif
#ifdef _simd_s16x64_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_sqrt_instruction_set };
	};
#endif
#ifdef _simd_s16x64_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_cbrt_instruction_set };
	};
#endif
#ifdef _simd_s16x64_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_avg_instruction_set };
	};
#endif
#ifdef _simd_s16x64_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_sum_instruction_set };
	};
#endif
#ifdef _simd_s16x64_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_s16x1, 64> {
		enum : int64_t { value = _simd_s16x64_popcount_instruction_set };
	};
#endif
#ifdef _simd_u16x2_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_fma_instruction_set };
	};
#endif
#ifdef _simd_u16x2_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_fms_instruction_set };
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
#ifdef _simd_u16x2_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_lshift_instruction_set };
	};
#endif
#ifdef _simd_u16x2_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_rshift_instruction_set };
	};
#endif
#ifdef _simd_u16x2_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_atan2_instruction_set };
	};
#endif
#ifdef _simd_u16x2_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_reflect_instruction_set };
	};
#endif
#ifdef _simd_u16x2_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_not_instruction_set };
	};
#endif
#ifdef _simd_u16x2_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_abs_instruction_set };
	};
#endif
#ifdef _simd_u16x2_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_exp_instruction_set };
	};
#endif
#ifdef _simd_u16x2_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_log_instruction_set };
	};
#endif
#ifdef _simd_u16x2_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_log2_instruction_set };
	};
#endif
#ifdef _simd_u16x2_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_log10_instruction_set };
	};
#endif
#ifdef _simd_u16x2_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_ceil_instruction_set };
	};
#endif
#ifdef _simd_u16x2_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_floor_instruction_set };
	};
#endif
#ifdef _simd_u16x2_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_round_instruction_set };
	};
#endif
#ifdef _simd_u16x2_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_sin_instruction_set };
	};
#endif
#ifdef _simd_u16x2_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_cos_instruction_set };
	};
#endif
#ifdef _simd_u16x2_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_tan_instruction_set };
	};
#endif
#ifdef _simd_u16x2_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_asin_instruction_set };
	};
#endif
#ifdef _simd_u16x2_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_acos_instruction_set };
	};
#endif
#ifdef _simd_u16x2_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_atan_instruction_set };
	};
#endif
#ifdef _simd_u16x2_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_sinh_instruction_set };
	};
#endif
#ifdef _simd_u16x2_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_cosh_instruction_set };
	};
#endif
#ifdef _simd_u16x2_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_tanh_instruction_set };
	};
#endif
#ifdef _simd_u16x2_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_sqrt_instruction_set };
	};
#endif
#ifdef _simd_u16x2_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_cbrt_instruction_set };
	};
#endif
#ifdef _simd_u16x2_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_avg_instruction_set };
	};
#endif
#ifdef _simd_u16x2_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_sum_instruction_set };
	};
#endif
#ifdef _simd_u16x2_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_u16x1, 2> {
		enum : int64_t { value = _simd_u16x2_popcount_instruction_set };
	};
#endif
#ifdef _simd_u16x4_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_fma_instruction_set };
	};
#endif
#ifdef _simd_u16x4_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_fms_instruction_set };
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
#ifdef _simd_u16x4_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_lshift_instruction_set };
	};
#endif
#ifdef _simd_u16x4_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_rshift_instruction_set };
	};
#endif
#ifdef _simd_u16x4_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_atan2_instruction_set };
	};
#endif
#ifdef _simd_u16x4_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_reflect_instruction_set };
	};
#endif
#ifdef _simd_u16x4_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_not_instruction_set };
	};
#endif
#ifdef _simd_u16x4_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_abs_instruction_set };
	};
#endif
#ifdef _simd_u16x4_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_exp_instruction_set };
	};
#endif
#ifdef _simd_u16x4_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_log_instruction_set };
	};
#endif
#ifdef _simd_u16x4_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_log2_instruction_set };
	};
#endif
#ifdef _simd_u16x4_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_log10_instruction_set };
	};
#endif
#ifdef _simd_u16x4_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_ceil_instruction_set };
	};
#endif
#ifdef _simd_u16x4_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_floor_instruction_set };
	};
#endif
#ifdef _simd_u16x4_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_round_instruction_set };
	};
#endif
#ifdef _simd_u16x4_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_sin_instruction_set };
	};
#endif
#ifdef _simd_u16x4_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_cos_instruction_set };
	};
#endif
#ifdef _simd_u16x4_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_tan_instruction_set };
	};
#endif
#ifdef _simd_u16x4_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_asin_instruction_set };
	};
#endif
#ifdef _simd_u16x4_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_acos_instruction_set };
	};
#endif
#ifdef _simd_u16x4_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_atan_instruction_set };
	};
#endif
#ifdef _simd_u16x4_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_sinh_instruction_set };
	};
#endif
#ifdef _simd_u16x4_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_cosh_instruction_set };
	};
#endif
#ifdef _simd_u16x4_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_tanh_instruction_set };
	};
#endif
#ifdef _simd_u16x4_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_sqrt_instruction_set };
	};
#endif
#ifdef _simd_u16x4_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_cbrt_instruction_set };
	};
#endif
#ifdef _simd_u16x4_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_avg_instruction_set };
	};
#endif
#ifdef _simd_u16x4_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_sum_instruction_set };
	};
#endif
#ifdef _simd_u16x4_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_u16x1, 4> {
		enum : int64_t { value = _simd_u16x4_popcount_instruction_set };
	};
#endif
#ifdef _simd_u16x8_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_fma_instruction_set };
	};
#endif
#ifdef _simd_u16x8_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_fms_instruction_set };
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
#ifdef _simd_u16x8_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_lshift_instruction_set };
	};
#endif
#ifdef _simd_u16x8_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_rshift_instruction_set };
	};
#endif
#ifdef _simd_u16x8_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_atan2_instruction_set };
	};
#endif
#ifdef _simd_u16x8_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_reflect_instruction_set };
	};
#endif
#ifdef _simd_u16x8_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_not_instruction_set };
	};
#endif
#ifdef _simd_u16x8_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_abs_instruction_set };
	};
#endif
#ifdef _simd_u16x8_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_exp_instruction_set };
	};
#endif
#ifdef _simd_u16x8_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_log_instruction_set };
	};
#endif
#ifdef _simd_u16x8_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_log2_instruction_set };
	};
#endif
#ifdef _simd_u16x8_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_log10_instruction_set };
	};
#endif
#ifdef _simd_u16x8_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_ceil_instruction_set };
	};
#endif
#ifdef _simd_u16x8_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_floor_instruction_set };
	};
#endif
#ifdef _simd_u16x8_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_round_instruction_set };
	};
#endif
#ifdef _simd_u16x8_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_sin_instruction_set };
	};
#endif
#ifdef _simd_u16x8_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_cos_instruction_set };
	};
#endif
#ifdef _simd_u16x8_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_tan_instruction_set };
	};
#endif
#ifdef _simd_u16x8_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_asin_instruction_set };
	};
#endif
#ifdef _simd_u16x8_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_acos_instruction_set };
	};
#endif
#ifdef _simd_u16x8_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_atan_instruction_set };
	};
#endif
#ifdef _simd_u16x8_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_sinh_instruction_set };
	};
#endif
#ifdef _simd_u16x8_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_cosh_instruction_set };
	};
#endif
#ifdef _simd_u16x8_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_tanh_instruction_set };
	};
#endif
#ifdef _simd_u16x8_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_sqrt_instruction_set };
	};
#endif
#ifdef _simd_u16x8_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_cbrt_instruction_set };
	};
#endif
#ifdef _simd_u16x8_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_avg_instruction_set };
	};
#endif
#ifdef _simd_u16x8_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_sum_instruction_set };
	};
#endif
#ifdef _simd_u16x8_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_u16x1, 8> {
		enum : int64_t { value = _simd_u16x8_popcount_instruction_set };
	};
#endif
#ifdef _simd_u16x16_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_fma_instruction_set };
	};
#endif
#ifdef _simd_u16x16_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_fms_instruction_set };
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
#ifdef _simd_u16x16_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_lshift_instruction_set };
	};
#endif
#ifdef _simd_u16x16_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_rshift_instruction_set };
	};
#endif
#ifdef _simd_u16x16_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_atan2_instruction_set };
	};
#endif
#ifdef _simd_u16x16_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_reflect_instruction_set };
	};
#endif
#ifdef _simd_u16x16_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_not_instruction_set };
	};
#endif
#ifdef _simd_u16x16_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_abs_instruction_set };
	};
#endif
#ifdef _simd_u16x16_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_exp_instruction_set };
	};
#endif
#ifdef _simd_u16x16_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_log_instruction_set };
	};
#endif
#ifdef _simd_u16x16_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_log2_instruction_set };
	};
#endif
#ifdef _simd_u16x16_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_log10_instruction_set };
	};
#endif
#ifdef _simd_u16x16_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_ceil_instruction_set };
	};
#endif
#ifdef _simd_u16x16_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_floor_instruction_set };
	};
#endif
#ifdef _simd_u16x16_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_round_instruction_set };
	};
#endif
#ifdef _simd_u16x16_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_sin_instruction_set };
	};
#endif
#ifdef _simd_u16x16_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_cos_instruction_set };
	};
#endif
#ifdef _simd_u16x16_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_tan_instruction_set };
	};
#endif
#ifdef _simd_u16x16_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_asin_instruction_set };
	};
#endif
#ifdef _simd_u16x16_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_acos_instruction_set };
	};
#endif
#ifdef _simd_u16x16_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_atan_instruction_set };
	};
#endif
#ifdef _simd_u16x16_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_sinh_instruction_set };
	};
#endif
#ifdef _simd_u16x16_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_cosh_instruction_set };
	};
#endif
#ifdef _simd_u16x16_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_tanh_instruction_set };
	};
#endif
#ifdef _simd_u16x16_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_sqrt_instruction_set };
	};
#endif
#ifdef _simd_u16x16_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_cbrt_instruction_set };
	};
#endif
#ifdef _simd_u16x16_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_avg_instruction_set };
	};
#endif
#ifdef _simd_u16x16_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_sum_instruction_set };
	};
#endif
#ifdef _simd_u16x16_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_u16x1, 16> {
		enum : int64_t { value = _simd_u16x16_popcount_instruction_set };
	};
#endif
#ifdef _simd_u16x32_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_fma_instruction_set };
	};
#endif
#ifdef _simd_u16x32_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_fms_instruction_set };
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
#ifdef _simd_u16x32_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_lshift_instruction_set };
	};
#endif
#ifdef _simd_u16x32_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_rshift_instruction_set };
	};
#endif
#ifdef _simd_u16x32_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_atan2_instruction_set };
	};
#endif
#ifdef _simd_u16x32_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_reflect_instruction_set };
	};
#endif
#ifdef _simd_u16x32_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_not_instruction_set };
	};
#endif
#ifdef _simd_u16x32_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_abs_instruction_set };
	};
#endif
#ifdef _simd_u16x32_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_exp_instruction_set };
	};
#endif
#ifdef _simd_u16x32_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_log_instruction_set };
	};
#endif
#ifdef _simd_u16x32_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_log2_instruction_set };
	};
#endif
#ifdef _simd_u16x32_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_log10_instruction_set };
	};
#endif
#ifdef _simd_u16x32_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_ceil_instruction_set };
	};
#endif
#ifdef _simd_u16x32_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_floor_instruction_set };
	};
#endif
#ifdef _simd_u16x32_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_round_instruction_set };
	};
#endif
#ifdef _simd_u16x32_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_sin_instruction_set };
	};
#endif
#ifdef _simd_u16x32_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_cos_instruction_set };
	};
#endif
#ifdef _simd_u16x32_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_tan_instruction_set };
	};
#endif
#ifdef _simd_u16x32_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_asin_instruction_set };
	};
#endif
#ifdef _simd_u16x32_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_acos_instruction_set };
	};
#endif
#ifdef _simd_u16x32_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_atan_instruction_set };
	};
#endif
#ifdef _simd_u16x32_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_sinh_instruction_set };
	};
#endif
#ifdef _simd_u16x32_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_cosh_instruction_set };
	};
#endif
#ifdef _simd_u16x32_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_tanh_instruction_set };
	};
#endif
#ifdef _simd_u16x32_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_sqrt_instruction_set };
	};
#endif
#ifdef _simd_u16x32_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_cbrt_instruction_set };
	};
#endif
#ifdef _simd_u16x32_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_avg_instruction_set };
	};
#endif
#ifdef _simd_u16x32_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_sum_instruction_set };
	};
#endif
#ifdef _simd_u16x32_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_u16x1, 32> {
		enum : int64_t { value = _simd_u16x32_popcount_instruction_set };
	};
#endif
#ifdef _simd_u16x64_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_fma_instruction_set };
	};
#endif
#ifdef _simd_u16x64_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_fms_instruction_set };
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
#ifdef _simd_u16x64_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_lshift_instruction_set };
	};
#endif
#ifdef _simd_u16x64_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_rshift_instruction_set };
	};
#endif
#ifdef _simd_u16x64_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_atan2_instruction_set };
	};
#endif
#ifdef _simd_u16x64_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_reflect_instruction_set };
	};
#endif
#ifdef _simd_u16x64_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_not_instruction_set };
	};
#endif
#ifdef _simd_u16x64_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_abs_instruction_set };
	};
#endif
#ifdef _simd_u16x64_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_exp_instruction_set };
	};
#endif
#ifdef _simd_u16x64_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_log_instruction_set };
	};
#endif
#ifdef _simd_u16x64_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_log2_instruction_set };
	};
#endif
#ifdef _simd_u16x64_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_log10_instruction_set };
	};
#endif
#ifdef _simd_u16x64_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_ceil_instruction_set };
	};
#endif
#ifdef _simd_u16x64_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_floor_instruction_set };
	};
#endif
#ifdef _simd_u16x64_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_round_instruction_set };
	};
#endif
#ifdef _simd_u16x64_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_sin_instruction_set };
	};
#endif
#ifdef _simd_u16x64_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_cos_instruction_set };
	};
#endif
#ifdef _simd_u16x64_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_tan_instruction_set };
	};
#endif
#ifdef _simd_u16x64_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_asin_instruction_set };
	};
#endif
#ifdef _simd_u16x64_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_acos_instruction_set };
	};
#endif
#ifdef _simd_u16x64_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_atan_instruction_set };
	};
#endif
#ifdef _simd_u16x64_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_sinh_instruction_set };
	};
#endif
#ifdef _simd_u16x64_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_cosh_instruction_set };
	};
#endif
#ifdef _simd_u16x64_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_tanh_instruction_set };
	};
#endif
#ifdef _simd_u16x64_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_sqrt_instruction_set };
	};
#endif
#ifdef _simd_u16x64_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_cbrt_instruction_set };
	};
#endif
#ifdef _simd_u16x64_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_avg_instruction_set };
	};
#endif
#ifdef _simd_u16x64_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_sum_instruction_set };
	};
#endif
#ifdef _simd_u16x64_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_u16x1, 64> {
		enum : int64_t { value = _simd_u16x64_popcount_instruction_set };
	};
#endif
#ifdef _simd_s8x2_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_fma_instruction_set };
	};
#endif
#ifdef _simd_s8x2_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_fms_instruction_set };
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
#ifdef _simd_s8x2_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_lshift_instruction_set };
	};
#endif
#ifdef _simd_s8x2_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_rshift_instruction_set };
	};
#endif
#ifdef _simd_s8x2_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_atan2_instruction_set };
	};
#endif
#ifdef _simd_s8x2_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_reflect_instruction_set };
	};
#endif
#ifdef _simd_s8x2_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_not_instruction_set };
	};
#endif
#ifdef _simd_s8x2_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_abs_instruction_set };
	};
#endif
#ifdef _simd_s8x2_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_exp_instruction_set };
	};
#endif
#ifdef _simd_s8x2_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_log_instruction_set };
	};
#endif
#ifdef _simd_s8x2_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_log2_instruction_set };
	};
#endif
#ifdef _simd_s8x2_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_log10_instruction_set };
	};
#endif
#ifdef _simd_s8x2_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_ceil_instruction_set };
	};
#endif
#ifdef _simd_s8x2_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_floor_instruction_set };
	};
#endif
#ifdef _simd_s8x2_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_round_instruction_set };
	};
#endif
#ifdef _simd_s8x2_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_sin_instruction_set };
	};
#endif
#ifdef _simd_s8x2_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_cos_instruction_set };
	};
#endif
#ifdef _simd_s8x2_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_tan_instruction_set };
	};
#endif
#ifdef _simd_s8x2_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_asin_instruction_set };
	};
#endif
#ifdef _simd_s8x2_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_acos_instruction_set };
	};
#endif
#ifdef _simd_s8x2_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_atan_instruction_set };
	};
#endif
#ifdef _simd_s8x2_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_sinh_instruction_set };
	};
#endif
#ifdef _simd_s8x2_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_cosh_instruction_set };
	};
#endif
#ifdef _simd_s8x2_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_tanh_instruction_set };
	};
#endif
#ifdef _simd_s8x2_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_sqrt_instruction_set };
	};
#endif
#ifdef _simd_s8x2_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_cbrt_instruction_set };
	};
#endif
#ifdef _simd_s8x2_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_avg_instruction_set };
	};
#endif
#ifdef _simd_s8x2_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_sum_instruction_set };
	};
#endif
#ifdef _simd_s8x2_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_s8x1, 2> {
		enum : int64_t { value = _simd_s8x2_popcount_instruction_set };
	};
#endif
#ifdef _simd_s8x4_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_fma_instruction_set };
	};
#endif
#ifdef _simd_s8x4_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_fms_instruction_set };
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
#ifdef _simd_s8x4_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_lshift_instruction_set };
	};
#endif
#ifdef _simd_s8x4_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_rshift_instruction_set };
	};
#endif
#ifdef _simd_s8x4_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_atan2_instruction_set };
	};
#endif
#ifdef _simd_s8x4_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_reflect_instruction_set };
	};
#endif
#ifdef _simd_s8x4_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_not_instruction_set };
	};
#endif
#ifdef _simd_s8x4_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_abs_instruction_set };
	};
#endif
#ifdef _simd_s8x4_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_exp_instruction_set };
	};
#endif
#ifdef _simd_s8x4_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_log_instruction_set };
	};
#endif
#ifdef _simd_s8x4_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_log2_instruction_set };
	};
#endif
#ifdef _simd_s8x4_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_log10_instruction_set };
	};
#endif
#ifdef _simd_s8x4_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_ceil_instruction_set };
	};
#endif
#ifdef _simd_s8x4_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_floor_instruction_set };
	};
#endif
#ifdef _simd_s8x4_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_round_instruction_set };
	};
#endif
#ifdef _simd_s8x4_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_sin_instruction_set };
	};
#endif
#ifdef _simd_s8x4_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_cos_instruction_set };
	};
#endif
#ifdef _simd_s8x4_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_tan_instruction_set };
	};
#endif
#ifdef _simd_s8x4_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_asin_instruction_set };
	};
#endif
#ifdef _simd_s8x4_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_acos_instruction_set };
	};
#endif
#ifdef _simd_s8x4_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_atan_instruction_set };
	};
#endif
#ifdef _simd_s8x4_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_sinh_instruction_set };
	};
#endif
#ifdef _simd_s8x4_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_cosh_instruction_set };
	};
#endif
#ifdef _simd_s8x4_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_tanh_instruction_set };
	};
#endif
#ifdef _simd_s8x4_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_sqrt_instruction_set };
	};
#endif
#ifdef _simd_s8x4_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_cbrt_instruction_set };
	};
#endif
#ifdef _simd_s8x4_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_avg_instruction_set };
	};
#endif
#ifdef _simd_s8x4_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_sum_instruction_set };
	};
#endif
#ifdef _simd_s8x4_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_s8x1, 4> {
		enum : int64_t { value = _simd_s8x4_popcount_instruction_set };
	};
#endif
#ifdef _simd_s8x8_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_fma_instruction_set };
	};
#endif
#ifdef _simd_s8x8_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_fms_instruction_set };
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
#ifdef _simd_s8x8_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_lshift_instruction_set };
	};
#endif
#ifdef _simd_s8x8_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_rshift_instruction_set };
	};
#endif
#ifdef _simd_s8x8_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_atan2_instruction_set };
	};
#endif
#ifdef _simd_s8x8_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_reflect_instruction_set };
	};
#endif
#ifdef _simd_s8x8_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_not_instruction_set };
	};
#endif
#ifdef _simd_s8x8_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_abs_instruction_set };
	};
#endif
#ifdef _simd_s8x8_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_exp_instruction_set };
	};
#endif
#ifdef _simd_s8x8_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_log_instruction_set };
	};
#endif
#ifdef _simd_s8x8_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_log2_instruction_set };
	};
#endif
#ifdef _simd_s8x8_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_log10_instruction_set };
	};
#endif
#ifdef _simd_s8x8_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_ceil_instruction_set };
	};
#endif
#ifdef _simd_s8x8_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_floor_instruction_set };
	};
#endif
#ifdef _simd_s8x8_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_round_instruction_set };
	};
#endif
#ifdef _simd_s8x8_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_sin_instruction_set };
	};
#endif
#ifdef _simd_s8x8_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_cos_instruction_set };
	};
#endif
#ifdef _simd_s8x8_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_tan_instruction_set };
	};
#endif
#ifdef _simd_s8x8_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_asin_instruction_set };
	};
#endif
#ifdef _simd_s8x8_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_acos_instruction_set };
	};
#endif
#ifdef _simd_s8x8_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_atan_instruction_set };
	};
#endif
#ifdef _simd_s8x8_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_sinh_instruction_set };
	};
#endif
#ifdef _simd_s8x8_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_cosh_instruction_set };
	};
#endif
#ifdef _simd_s8x8_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_tanh_instruction_set };
	};
#endif
#ifdef _simd_s8x8_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_sqrt_instruction_set };
	};
#endif
#ifdef _simd_s8x8_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_cbrt_instruction_set };
	};
#endif
#ifdef _simd_s8x8_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_avg_instruction_set };
	};
#endif
#ifdef _simd_s8x8_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_sum_instruction_set };
	};
#endif
#ifdef _simd_s8x8_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_s8x1, 8> {
		enum : int64_t { value = _simd_s8x8_popcount_instruction_set };
	};
#endif
#ifdef _simd_s8x16_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_fma_instruction_set };
	};
#endif
#ifdef _simd_s8x16_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_fms_instruction_set };
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
#ifdef _simd_s8x16_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_lshift_instruction_set };
	};
#endif
#ifdef _simd_s8x16_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_rshift_instruction_set };
	};
#endif
#ifdef _simd_s8x16_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_atan2_instruction_set };
	};
#endif
#ifdef _simd_s8x16_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_reflect_instruction_set };
	};
#endif
#ifdef _simd_s8x16_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_not_instruction_set };
	};
#endif
#ifdef _simd_s8x16_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_abs_instruction_set };
	};
#endif
#ifdef _simd_s8x16_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_exp_instruction_set };
	};
#endif
#ifdef _simd_s8x16_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_log_instruction_set };
	};
#endif
#ifdef _simd_s8x16_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_log2_instruction_set };
	};
#endif
#ifdef _simd_s8x16_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_log10_instruction_set };
	};
#endif
#ifdef _simd_s8x16_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_ceil_instruction_set };
	};
#endif
#ifdef _simd_s8x16_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_floor_instruction_set };
	};
#endif
#ifdef _simd_s8x16_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_round_instruction_set };
	};
#endif
#ifdef _simd_s8x16_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_sin_instruction_set };
	};
#endif
#ifdef _simd_s8x16_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_cos_instruction_set };
	};
#endif
#ifdef _simd_s8x16_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_tan_instruction_set };
	};
#endif
#ifdef _simd_s8x16_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_asin_instruction_set };
	};
#endif
#ifdef _simd_s8x16_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_acos_instruction_set };
	};
#endif
#ifdef _simd_s8x16_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_atan_instruction_set };
	};
#endif
#ifdef _simd_s8x16_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_sinh_instruction_set };
	};
#endif
#ifdef _simd_s8x16_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_cosh_instruction_set };
	};
#endif
#ifdef _simd_s8x16_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_tanh_instruction_set };
	};
#endif
#ifdef _simd_s8x16_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_sqrt_instruction_set };
	};
#endif
#ifdef _simd_s8x16_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_cbrt_instruction_set };
	};
#endif
#ifdef _simd_s8x16_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_avg_instruction_set };
	};
#endif
#ifdef _simd_s8x16_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_sum_instruction_set };
	};
#endif
#ifdef _simd_s8x16_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_s8x1, 16> {
		enum : int64_t { value = _simd_s8x16_popcount_instruction_set };
	};
#endif
#ifdef _simd_s8x32_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_fma_instruction_set };
	};
#endif
#ifdef _simd_s8x32_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_fms_instruction_set };
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
#ifdef _simd_s8x32_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_lshift_instruction_set };
	};
#endif
#ifdef _simd_s8x32_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_rshift_instruction_set };
	};
#endif
#ifdef _simd_s8x32_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_atan2_instruction_set };
	};
#endif
#ifdef _simd_s8x32_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_reflect_instruction_set };
	};
#endif
#ifdef _simd_s8x32_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_not_instruction_set };
	};
#endif
#ifdef _simd_s8x32_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_abs_instruction_set };
	};
#endif
#ifdef _simd_s8x32_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_exp_instruction_set };
	};
#endif
#ifdef _simd_s8x32_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_log_instruction_set };
	};
#endif
#ifdef _simd_s8x32_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_log2_instruction_set };
	};
#endif
#ifdef _simd_s8x32_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_log10_instruction_set };
	};
#endif
#ifdef _simd_s8x32_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_ceil_instruction_set };
	};
#endif
#ifdef _simd_s8x32_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_floor_instruction_set };
	};
#endif
#ifdef _simd_s8x32_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_round_instruction_set };
	};
#endif
#ifdef _simd_s8x32_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_sin_instruction_set };
	};
#endif
#ifdef _simd_s8x32_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_cos_instruction_set };
	};
#endif
#ifdef _simd_s8x32_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_tan_instruction_set };
	};
#endif
#ifdef _simd_s8x32_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_asin_instruction_set };
	};
#endif
#ifdef _simd_s8x32_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_acos_instruction_set };
	};
#endif
#ifdef _simd_s8x32_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_atan_instruction_set };
	};
#endif
#ifdef _simd_s8x32_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_sinh_instruction_set };
	};
#endif
#ifdef _simd_s8x32_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_cosh_instruction_set };
	};
#endif
#ifdef _simd_s8x32_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_tanh_instruction_set };
	};
#endif
#ifdef _simd_s8x32_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_sqrt_instruction_set };
	};
#endif
#ifdef _simd_s8x32_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_cbrt_instruction_set };
	};
#endif
#ifdef _simd_s8x32_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_avg_instruction_set };
	};
#endif
#ifdef _simd_s8x32_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_sum_instruction_set };
	};
#endif
#ifdef _simd_s8x32_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_s8x1, 32> {
		enum : int64_t { value = _simd_s8x32_popcount_instruction_set };
	};
#endif
#ifdef _simd_s8x64_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_fma_instruction_set };
	};
#endif
#ifdef _simd_s8x64_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_fms_instruction_set };
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
#ifdef _simd_s8x64_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_lshift_instruction_set };
	};
#endif
#ifdef _simd_s8x64_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_rshift_instruction_set };
	};
#endif
#ifdef _simd_s8x64_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_atan2_instruction_set };
	};
#endif
#ifdef _simd_s8x64_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_reflect_instruction_set };
	};
#endif
#ifdef _simd_s8x64_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_not_instruction_set };
	};
#endif
#ifdef _simd_s8x64_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_abs_instruction_set };
	};
#endif
#ifdef _simd_s8x64_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_exp_instruction_set };
	};
#endif
#ifdef _simd_s8x64_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_log_instruction_set };
	};
#endif
#ifdef _simd_s8x64_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_log2_instruction_set };
	};
#endif
#ifdef _simd_s8x64_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_log10_instruction_set };
	};
#endif
#ifdef _simd_s8x64_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_ceil_instruction_set };
	};
#endif
#ifdef _simd_s8x64_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_floor_instruction_set };
	};
#endif
#ifdef _simd_s8x64_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_round_instruction_set };
	};
#endif
#ifdef _simd_s8x64_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_sin_instruction_set };
	};
#endif
#ifdef _simd_s8x64_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_cos_instruction_set };
	};
#endif
#ifdef _simd_s8x64_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_tan_instruction_set };
	};
#endif
#ifdef _simd_s8x64_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_asin_instruction_set };
	};
#endif
#ifdef _simd_s8x64_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_acos_instruction_set };
	};
#endif
#ifdef _simd_s8x64_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_atan_instruction_set };
	};
#endif
#ifdef _simd_s8x64_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_sinh_instruction_set };
	};
#endif
#ifdef _simd_s8x64_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_cosh_instruction_set };
	};
#endif
#ifdef _simd_s8x64_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_tanh_instruction_set };
	};
#endif
#ifdef _simd_s8x64_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_sqrt_instruction_set };
	};
#endif
#ifdef _simd_s8x64_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_cbrt_instruction_set };
	};
#endif
#ifdef _simd_s8x64_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_avg_instruction_set };
	};
#endif
#ifdef _simd_s8x64_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_sum_instruction_set };
	};
#endif
#ifdef _simd_s8x64_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_s8x1, 64> {
		enum : int64_t { value = _simd_s8x64_popcount_instruction_set };
	};
#endif
#ifdef _simd_u8x2_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_fma_instruction_set };
	};
#endif
#ifdef _simd_u8x2_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_fms_instruction_set };
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
#ifdef _simd_u8x2_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_lshift_instruction_set };
	};
#endif
#ifdef _simd_u8x2_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_rshift_instruction_set };
	};
#endif
#ifdef _simd_u8x2_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_atan2_instruction_set };
	};
#endif
#ifdef _simd_u8x2_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_reflect_instruction_set };
	};
#endif
#ifdef _simd_u8x2_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_not_instruction_set };
	};
#endif
#ifdef _simd_u8x2_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_abs_instruction_set };
	};
#endif
#ifdef _simd_u8x2_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_exp_instruction_set };
	};
#endif
#ifdef _simd_u8x2_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_log_instruction_set };
	};
#endif
#ifdef _simd_u8x2_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_log2_instruction_set };
	};
#endif
#ifdef _simd_u8x2_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_log10_instruction_set };
	};
#endif
#ifdef _simd_u8x2_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_ceil_instruction_set };
	};
#endif
#ifdef _simd_u8x2_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_floor_instruction_set };
	};
#endif
#ifdef _simd_u8x2_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_round_instruction_set };
	};
#endif
#ifdef _simd_u8x2_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_sin_instruction_set };
	};
#endif
#ifdef _simd_u8x2_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_cos_instruction_set };
	};
#endif
#ifdef _simd_u8x2_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_tan_instruction_set };
	};
#endif
#ifdef _simd_u8x2_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_asin_instruction_set };
	};
#endif
#ifdef _simd_u8x2_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_acos_instruction_set };
	};
#endif
#ifdef _simd_u8x2_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_atan_instruction_set };
	};
#endif
#ifdef _simd_u8x2_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_sinh_instruction_set };
	};
#endif
#ifdef _simd_u8x2_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_cosh_instruction_set };
	};
#endif
#ifdef _simd_u8x2_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_tanh_instruction_set };
	};
#endif
#ifdef _simd_u8x2_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_sqrt_instruction_set };
	};
#endif
#ifdef _simd_u8x2_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_cbrt_instruction_set };
	};
#endif
#ifdef _simd_u8x2_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_avg_instruction_set };
	};
#endif
#ifdef _simd_u8x2_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_sum_instruction_set };
	};
#endif
#ifdef _simd_u8x2_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_u8x1, 2> {
		enum : int64_t { value = _simd_u8x2_popcount_instruction_set };
	};
#endif
#ifdef _simd_u8x4_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_fma_instruction_set };
	};
#endif
#ifdef _simd_u8x4_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_fms_instruction_set };
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
#ifdef _simd_u8x4_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_lshift_instruction_set };
	};
#endif
#ifdef _simd_u8x4_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_rshift_instruction_set };
	};
#endif
#ifdef _simd_u8x4_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_atan2_instruction_set };
	};
#endif
#ifdef _simd_u8x4_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_reflect_instruction_set };
	};
#endif
#ifdef _simd_u8x4_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_not_instruction_set };
	};
#endif
#ifdef _simd_u8x4_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_abs_instruction_set };
	};
#endif
#ifdef _simd_u8x4_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_exp_instruction_set };
	};
#endif
#ifdef _simd_u8x4_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_log_instruction_set };
	};
#endif
#ifdef _simd_u8x4_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_log2_instruction_set };
	};
#endif
#ifdef _simd_u8x4_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_log10_instruction_set };
	};
#endif
#ifdef _simd_u8x4_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_ceil_instruction_set };
	};
#endif
#ifdef _simd_u8x4_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_floor_instruction_set };
	};
#endif
#ifdef _simd_u8x4_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_round_instruction_set };
	};
#endif
#ifdef _simd_u8x4_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_sin_instruction_set };
	};
#endif
#ifdef _simd_u8x4_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_cos_instruction_set };
	};
#endif
#ifdef _simd_u8x4_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_tan_instruction_set };
	};
#endif
#ifdef _simd_u8x4_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_asin_instruction_set };
	};
#endif
#ifdef _simd_u8x4_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_acos_instruction_set };
	};
#endif
#ifdef _simd_u8x4_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_atan_instruction_set };
	};
#endif
#ifdef _simd_u8x4_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_sinh_instruction_set };
	};
#endif
#ifdef _simd_u8x4_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_cosh_instruction_set };
	};
#endif
#ifdef _simd_u8x4_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_tanh_instruction_set };
	};
#endif
#ifdef _simd_u8x4_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_sqrt_instruction_set };
	};
#endif
#ifdef _simd_u8x4_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_cbrt_instruction_set };
	};
#endif
#ifdef _simd_u8x4_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_avg_instruction_set };
	};
#endif
#ifdef _simd_u8x4_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_sum_instruction_set };
	};
#endif
#ifdef _simd_u8x4_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_u8x1, 4> {
		enum : int64_t { value = _simd_u8x4_popcount_instruction_set };
	};
#endif
#ifdef _simd_u8x8_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_fma_instruction_set };
	};
#endif
#ifdef _simd_u8x8_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_fms_instruction_set };
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
#ifdef _simd_u8x8_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_lshift_instruction_set };
	};
#endif
#ifdef _simd_u8x8_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_rshift_instruction_set };
	};
#endif
#ifdef _simd_u8x8_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_atan2_instruction_set };
	};
#endif
#ifdef _simd_u8x8_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_reflect_instruction_set };
	};
#endif
#ifdef _simd_u8x8_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_not_instruction_set };
	};
#endif
#ifdef _simd_u8x8_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_abs_instruction_set };
	};
#endif
#ifdef _simd_u8x8_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_exp_instruction_set };
	};
#endif
#ifdef _simd_u8x8_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_log_instruction_set };
	};
#endif
#ifdef _simd_u8x8_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_log2_instruction_set };
	};
#endif
#ifdef _simd_u8x8_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_log10_instruction_set };
	};
#endif
#ifdef _simd_u8x8_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_ceil_instruction_set };
	};
#endif
#ifdef _simd_u8x8_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_floor_instruction_set };
	};
#endif
#ifdef _simd_u8x8_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_round_instruction_set };
	};
#endif
#ifdef _simd_u8x8_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_sin_instruction_set };
	};
#endif
#ifdef _simd_u8x8_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_cos_instruction_set };
	};
#endif
#ifdef _simd_u8x8_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_tan_instruction_set };
	};
#endif
#ifdef _simd_u8x8_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_asin_instruction_set };
	};
#endif
#ifdef _simd_u8x8_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_acos_instruction_set };
	};
#endif
#ifdef _simd_u8x8_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_atan_instruction_set };
	};
#endif
#ifdef _simd_u8x8_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_sinh_instruction_set };
	};
#endif
#ifdef _simd_u8x8_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_cosh_instruction_set };
	};
#endif
#ifdef _simd_u8x8_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_tanh_instruction_set };
	};
#endif
#ifdef _simd_u8x8_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_sqrt_instruction_set };
	};
#endif
#ifdef _simd_u8x8_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_cbrt_instruction_set };
	};
#endif
#ifdef _simd_u8x8_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_avg_instruction_set };
	};
#endif
#ifdef _simd_u8x8_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_sum_instruction_set };
	};
#endif
#ifdef _simd_u8x8_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_u8x1, 8> {
		enum : int64_t { value = _simd_u8x8_popcount_instruction_set };
	};
#endif
#ifdef _simd_u8x16_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_fma_instruction_set };
	};
#endif
#ifdef _simd_u8x16_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_fms_instruction_set };
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
#ifdef _simd_u8x16_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_lshift_instruction_set };
	};
#endif
#ifdef _simd_u8x16_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_rshift_instruction_set };
	};
#endif
#ifdef _simd_u8x16_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_atan2_instruction_set };
	};
#endif
#ifdef _simd_u8x16_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_reflect_instruction_set };
	};
#endif
#ifdef _simd_u8x16_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_not_instruction_set };
	};
#endif
#ifdef _simd_u8x16_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_abs_instruction_set };
	};
#endif
#ifdef _simd_u8x16_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_exp_instruction_set };
	};
#endif
#ifdef _simd_u8x16_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_log_instruction_set };
	};
#endif
#ifdef _simd_u8x16_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_log2_instruction_set };
	};
#endif
#ifdef _simd_u8x16_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_log10_instruction_set };
	};
#endif
#ifdef _simd_u8x16_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_ceil_instruction_set };
	};
#endif
#ifdef _simd_u8x16_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_floor_instruction_set };
	};
#endif
#ifdef _simd_u8x16_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_round_instruction_set };
	};
#endif
#ifdef _simd_u8x16_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_sin_instruction_set };
	};
#endif
#ifdef _simd_u8x16_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_cos_instruction_set };
	};
#endif
#ifdef _simd_u8x16_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_tan_instruction_set };
	};
#endif
#ifdef _simd_u8x16_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_asin_instruction_set };
	};
#endif
#ifdef _simd_u8x16_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_acos_instruction_set };
	};
#endif
#ifdef _simd_u8x16_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_atan_instruction_set };
	};
#endif
#ifdef _simd_u8x16_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_sinh_instruction_set };
	};
#endif
#ifdef _simd_u8x16_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_cosh_instruction_set };
	};
#endif
#ifdef _simd_u8x16_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_tanh_instruction_set };
	};
#endif
#ifdef _simd_u8x16_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_sqrt_instruction_set };
	};
#endif
#ifdef _simd_u8x16_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_cbrt_instruction_set };
	};
#endif
#ifdef _simd_u8x16_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_avg_instruction_set };
	};
#endif
#ifdef _simd_u8x16_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_sum_instruction_set };
	};
#endif
#ifdef _simd_u8x16_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_u8x1, 16> {
		enum : int64_t { value = _simd_u8x16_popcount_instruction_set };
	};
#endif
#ifdef _simd_u8x32_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_fma_instruction_set };
	};
#endif
#ifdef _simd_u8x32_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_fms_instruction_set };
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
#ifdef _simd_u8x32_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_lshift_instruction_set };
	};
#endif
#ifdef _simd_u8x32_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_rshift_instruction_set };
	};
#endif
#ifdef _simd_u8x32_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_atan2_instruction_set };
	};
#endif
#ifdef _simd_u8x32_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_reflect_instruction_set };
	};
#endif
#ifdef _simd_u8x32_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_not_instruction_set };
	};
#endif
#ifdef _simd_u8x32_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_abs_instruction_set };
	};
#endif
#ifdef _simd_u8x32_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_exp_instruction_set };
	};
#endif
#ifdef _simd_u8x32_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_log_instruction_set };
	};
#endif
#ifdef _simd_u8x32_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_log2_instruction_set };
	};
#endif
#ifdef _simd_u8x32_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_log10_instruction_set };
	};
#endif
#ifdef _simd_u8x32_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_ceil_instruction_set };
	};
#endif
#ifdef _simd_u8x32_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_floor_instruction_set };
	};
#endif
#ifdef _simd_u8x32_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_round_instruction_set };
	};
#endif
#ifdef _simd_u8x32_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_sin_instruction_set };
	};
#endif
#ifdef _simd_u8x32_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_cos_instruction_set };
	};
#endif
#ifdef _simd_u8x32_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_tan_instruction_set };
	};
#endif
#ifdef _simd_u8x32_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_asin_instruction_set };
	};
#endif
#ifdef _simd_u8x32_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_acos_instruction_set };
	};
#endif
#ifdef _simd_u8x32_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_atan_instruction_set };
	};
#endif
#ifdef _simd_u8x32_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_sinh_instruction_set };
	};
#endif
#ifdef _simd_u8x32_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_cosh_instruction_set };
	};
#endif
#ifdef _simd_u8x32_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_tanh_instruction_set };
	};
#endif
#ifdef _simd_u8x32_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_sqrt_instruction_set };
	};
#endif
#ifdef _simd_u8x32_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_cbrt_instruction_set };
	};
#endif
#ifdef _simd_u8x32_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_avg_instruction_set };
	};
#endif
#ifdef _simd_u8x32_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_sum_instruction_set };
	};
#endif
#ifdef _simd_u8x32_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_u8x1, 32> {
		enum : int64_t { value = _simd_u8x32_popcount_instruction_set };
	};
#endif
#ifdef _simd_u8x64_fma_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMA, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_fma_instruction_set };
	};
#endif
#ifdef _simd_u8x64_fms_instruction_set
	template<>
	struct OperationInstructionSet<OP_FMS, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_fms_instruction_set };
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
#ifdef _simd_u8x64_lshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_LSHIFT, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_lshift_instruction_set };
	};
#endif
#ifdef _simd_u8x64_rshift_instruction_set
	template<>
	struct OperationInstructionSet<OP_RSHIFT, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_rshift_instruction_set };
	};
#endif
#ifdef _simd_u8x64_atan2_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN2, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_atan2_instruction_set };
	};
#endif
#ifdef _simd_u8x64_reflect_instruction_set
	template<>
	struct OperationInstructionSet<OP_REFLECT, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_reflect_instruction_set };
	};
#endif
#ifdef _simd_u8x64_not_instruction_set
	template<>
	struct OperationInstructionSet<OP_NOT, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_not_instruction_set };
	};
#endif
#ifdef _simd_u8x64_abs_instruction_set
	template<>
	struct OperationInstructionSet<OP_ABS, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_abs_instruction_set };
	};
#endif
#ifdef _simd_u8x64_exp_instruction_set
	template<>
	struct OperationInstructionSet<OP_EXP, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_exp_instruction_set };
	};
#endif
#ifdef _simd_u8x64_log_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_log_instruction_set };
	};
#endif
#ifdef _simd_u8x64_log2_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG2, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_log2_instruction_set };
	};
#endif
#ifdef _simd_u8x64_log10_instruction_set
	template<>
	struct OperationInstructionSet<OP_LOG10, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_log10_instruction_set };
	};
#endif
#ifdef _simd_u8x64_ceil_instruction_set
	template<>
	struct OperationInstructionSet<OP_CEIL, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_ceil_instruction_set };
	};
#endif
#ifdef _simd_u8x64_floor_instruction_set
	template<>
	struct OperationInstructionSet<OP_FLOOR, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_floor_instruction_set };
	};
#endif
#ifdef _simd_u8x64_round_instruction_set
	template<>
	struct OperationInstructionSet<OP_ROUND, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_round_instruction_set };
	};
#endif
#ifdef _simd_u8x64_sin_instruction_set
	template<>
	struct OperationInstructionSet<OP_SIN, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_sin_instruction_set };
	};
#endif
#ifdef _simd_u8x64_cos_instruction_set
	template<>
	struct OperationInstructionSet<OP_COS, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_cos_instruction_set };
	};
#endif
#ifdef _simd_u8x64_tan_instruction_set
	template<>
	struct OperationInstructionSet<OP_TAN, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_tan_instruction_set };
	};
#endif
#ifdef _simd_u8x64_asin_instruction_set
	template<>
	struct OperationInstructionSet<OP_ASIN, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_asin_instruction_set };
	};
#endif
#ifdef _simd_u8x64_acos_instruction_set
	template<>
	struct OperationInstructionSet<OP_ACOS, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_acos_instruction_set };
	};
#endif
#ifdef _simd_u8x64_atan_instruction_set
	template<>
	struct OperationInstructionSet<OP_ATAN, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_atan_instruction_set };
	};
#endif
#ifdef _simd_u8x64_sinh_instruction_set
	template<>
	struct OperationInstructionSet<OP_SINH, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_sinh_instruction_set };
	};
#endif
#ifdef _simd_u8x64_cosh_instruction_set
	template<>
	struct OperationInstructionSet<OP_COSH, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_cosh_instruction_set };
	};
#endif
#ifdef _simd_u8x64_tanh_instruction_set
	template<>
	struct OperationInstructionSet<OP_TANH, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_tanh_instruction_set };
	};
#endif
#ifdef _simd_u8x64_sqrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_SQRT, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_sqrt_instruction_set };
	};
#endif
#ifdef _simd_u8x64_cbrt_instruction_set
	template<>
	struct OperationInstructionSet<OP_CBRT, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_cbrt_instruction_set };
	};
#endif
#ifdef _simd_u8x64_avg_instruction_set
	template<>
	struct OperationInstructionSet<OP_AVG, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_avg_instruction_set };
	};
#endif
#ifdef _simd_u8x64_sum_instruction_set
	template<>
	struct OperationInstructionSet<OP_SUM, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_sum_instruction_set };
	};
#endif
#ifdef _simd_u8x64_popcount_instruction_set
	template<>
	struct OperationInstructionSet<OP_POPCN, _simd_u8x1, 64> {
		enum : int64_t { value = _simd_u8x64_popcount_instruction_set };
	};
#endif
