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

typedef float32x4_t __m128;

// Non-SSE Helpers

#define _mm_not_ps(X) vreinterpretq_f32_s32(vmvnq_s32(vreinterpretq_s32_f32(X)))

namespace anvil { namespace detail {
	static ANVIL_CONSTEXPR_FN float f32_all_ones(const uint32_t aValue) { return *reinterpret_cast<const float*>(&aValue); }
}}

static ANVIL_CONSTEXPR_VAR const float ANVIL_ALL_ONE_F32 = anvil::detail::f32_all_ones(UINT32_MAX);

// SSE Intrinsics

#define _mm_add_ps(X,Y) vaddq_f32(X,Y)
#define _mm_add_ss(X,Y) vsetq_lane_f32(vget_lane_f32(vadd_f32(vget_low_f32(X), vget_low_f32(Y)),0), Y, 0)
#define _mm_and_ps(X,Y) vreinterpretq_f32_s32(vandq_s32(vreinterpretq_s32_f32(X),vreinterpretq_s32_f32(Y)))
#define _mm_andnot_ps(X,Y) _mm_and_ps(_mm_not_ps(X),Y)
#define _mm_cmpeq_ps(X,Y) vreinterpretq_f32_s32(vceqq_f32(vreinterpretq_s32_f32(X),vreinterpretq_s32_f32(Y)))
#define _mm_cmpeq_ss(X,Y) vsetq_lane_f32(vgetq_lane_f32(X,0) == vgetq_lane_f32(Y,0) ? ANVIL_ALL_ONE_F32 : 0.f, Y, 0)
static ANVIL_STRONG_INLINE __m128 ANVIL_SIMD_CALL _mm_cmpge_ps(const __m128 a, const __m128 b) throw() {
	float bufA[4];
	float bufB[4];
	vst1q_f32(bufA, a);
	vst1q_f32(bufB, b);
	for (int i = 0; i < 4; ++i) bufA[i] bufA[i] >= bufB[i] ? ANVIL_ALL_ONE_F32 : 0.f;
	return vld1q_f32(reinterpret_cast<float*>(bufA));
}
#define _mm_cmpeq_ss(X,Y) vsetq_lane_f32(vgetq_lane_f32(X,0) >= vgetq_lane_f32(Y,0) ? ANVIL_ALL_ONE_F32 : 0.f, Y, 0)
static ANVIL_STRONG_INLINE __m128 ANVIL_SIMD_CALL _mm_cmpgt_ps(const __m128 a, const __m128 b) throw() {
	float bufA[4];
	float bufB[4];
	vst1q_f32(bufA, a);
	vst1q_f32(bufB, b);
	for (int i = 0; i < 4; ++i) bufA[i] bufA[i] > bufB[i] ? ANVIL_ALL_ONE_F32 : 0.f;
	return vld1q_f32(reinterpret_cast<float*>(bufA));
}
#define _mm_cmpeq_ss(X,Y) vsetq_lane_f32(vgetq_lane_f32(X,0) > vgetq_lane_f32(Y,0) ? ANVIL_ALL_ONE_F32 : 0.f, Y, 0)
static ANVIL_STRONG_INLINE __m128 ANVIL_SIMD_CALL _mm_cmple_ps(const __m128 a, const __m128 b) throw() {
	float bufA[4];
	float bufB[4];
	vst1q_f32(bufA, a);
	vst1q_f32(bufB, b);
	for (int i = 0; i < 4; ++i) bufA[i] bufA[i] <= bufB[i] ? ANVIL_ALL_ONE_F32 : 0.f;
	return vld1q_f32(reinterpret_cast<float*>(bufA));
}
#define _mm_cmpeq_ss(X,Y) vsetq_lane_f32(vgetq_lane_f32(X,0) <= vgetq_lane_f32(Y,0) ? ANVIL_ALL_ONE_F32 : 0.f, Y, 0)
static ANVIL_STRONG_INLINE __m128 ANVIL_SIMD_CALL _mm_cmplt_ps(const __m128 a, const __m128 b) throw() {
	float bufA[4];
	float bufB[4];
	vst1q_f32(bufA, a);
	vst1q_f32(bufB, b);
	for (int i = 0; i < 4; ++i) bufA[i] bufA[i] < bufB[i] ? ANVIL_ALL_ONE_F32 : 0.f;
	return vld1q_f32(reinterpret_cast<float*>(bufA));
}
#define _mm_cmpeq_ss(X,Y) vsetq_lane_f32(vgetq_lane_f32(X,0) < vgetq_lane_f32(Y,0) ? ANVIL_ALL_ONE_F32 : 0.f, Y, 0)
#define _mm_cmpneq_ps(X,Y) vreinterpretq_f32_s32(vmvnq_s32(vceqq_f32(vreinterpretq_s32_f32(X),vreinterpretq_s32_f32(Y))))
#define _mm_cmpeq_ss(X,Y) vsetq_lane_f32(vgetq_lane_f32(X,0) != vgetq_lane_f32(Y,0) ? ANVIL_ALL_ONE_F32 : 0.f, Y, 0)
#define _mm_cmpnge_ps(X,Y) vreinterpretq_f32_s32(vmvnq_s32(vreinterpretq_s32_f32(_mm_cmpge_ps(X,Y)))))
#define _mm_cmpnge_ss(X,Y) _mm_cmplt_ss(X,Y)
#define _mm_cmpngt_ps(X,Y) vreinterpretq_f32_s32(vmvnq_s32(vreinterpretq_s32_f32(_mm_cmpgt_ps(X,Y))))
#define _mm_cmpnge_ss(X,Y) _mm_cmple_ss(X,Y)
#define _mm_cmpnle_ps(X,Y) vreinterpretq_f32_s32(vmvnq_s32(vreinterpretq_s32_f32(_mm_cmple_ps(X,Y))))
#define _mm_cmpnle_ss(X,Y) _mm_cmpgt_ss(X,Y)
#define _mm_cmpnlt_ps(X,Y) vreinterpretq_f32_s32(vmvnq_s32(vreinterpretq_s32_f32(_mm_cmplt_ps(X,Y))))
#define _mm_cmpnlt_ss(X,Y) _mm_cmpge_ss(X,Y)
//! \todo __m128 _mm_cmpord_ps (__m128 a, __m128 b)
//! \todo __m128 _mm_cmpord_ss (__m128 a, __m128 b)
//! \todo __m128 _mm_cmpunord_ps (__m128 a, __m128 b)
//! \todo __m128 _mm_cmpunord_ss (__m128 a, __m128 b)
//! \todo int _mm_comieq_ss (__m128 a, __m128 b)
//! \todo int _mm_comige_ss (__m128 a, __m128 b)
//! \todo int _mm_comigt_ss (__m128 a, __m128 b)
//! \todo int _mm_comile_ss (__m128 a, __m128 b)
//! \todo int _mm_comilt_ss (__m128 a, __m128 b)
//! \todo int _mm_comineq_ss (__m128 a, __m128 b)
//! \todo __m128 _mm_cvt_si2ss (__m128 a, int b)
//! \todo int _mm_cvt_ss2si (__m128 a)
//! \todo __m128 _mm_cvtsi32_ss (__m128 a, int b)
//! \todo float _mm_cvtss_f32 (__m128 a)
//! \todo int _mm_cvtss_si32 (__m128 a)
//! \todo __int64 _mm_cvtss_si64 (__m128 a)
//! \todo int _mm_cvtt_ss2si (__m128 a)
//! \todo int _mm_cvttss_si32 (__m128 a)
//! \todo __int64 _mm_cvttss_si64 (__m128 a)
static ANVIL_STRONG_INLINE __m128 ANVIL_SIMD_CALL _mm_div_ps(const __m128 a, const __m128 b) throw() {
	float bufA[4];
	float bufB[4];
	vst1q_f32(bufA, a);
	vst1q_f32(bufB, b);
	for (int i = 0; i < 4; ++i) bufA[i] /= bufB[i];
	return vld1q_f32(bufA);
}

#define _mm_div_ss(X,Y) vsetq_lane_f32(vgetq_lane_f32(X,0) / vgetq_lane_f32(Y,0), Y, 0)
//! \todo unsigned int _MM_GET_EXCEPTION_MASK ()
//! \todo unsigned int _MM_GET_EXCEPTION_STATE ()
//! \todo unsigned int _MM_GET_FLUSH_ZERO_MODE ()
//! \todo unsigned int _MM_GET_ROUNDING_MODE ()
//! \todo unsigned int _mm_getcsr (void)
#define _mm_load_ps(X) _mm_loadu_ps(X)
#define _mm_load_ps1(X) _mm_load1_ps(X)
#define _mm_load_ss(X) _mm_set_ss(*X)
#define _mm_load1_ps(X) _mm_set1_ps(*X)
#define _mm_loadr_ps(X) _mm_set_ps(X[3],X[2],X[1],X[0])
#define _mm_loadu_ps(X) vld1q_f32(X)
#define _mm_max_ps(X,Y) vmaxq_f32(X,Y)
#define _mm_max_ss(X,Y) vsetq_lane_f32(vget_lane_f32(vmax_f32(vget_low_f32(X),vget_low_f32(Y)),0), Y, 0)
#define _mm_min_ps(X,Y) vminq_f32(X,Y)
#define _mm_min_ss(X,Y) vsetq_lane_f32(vget_lane_f32(vmin_f32(vget_low_f32(X),vget_low_f32(Y)),0), Y, 0)
//! \todo __m128 _mm_move_ss (__m128 a, __m128 b)
//! \todo __m128 _mm_movehl_ps (__m128 a, __m128 b)
//! \todo __m128 _mm_movelh_ps (__m128 a, __m128 b)
//! \todo int _mm_movemask_ps (__m128 a)
#define _mm_mul_ps(X,Y) vmulq_f32(X,Y)
#define _mm_mul_ss(X,Y) vsetq_lane_f32(vget_lane_f32(vmul_f32(vget_low_f32(X), vget_low_f32(Y)),0), Y, 0)
#define _mm_or_ps(X,Y) vreinterpretq_f32_s32(vorrq_s32(vreinterpretq_s32_f32(X),vreinterpretq_s32_f32(Y)))
//! \todo void _mm_prefetch (char const* p, int i)
//! \todo __m128 _mm_rcp_ps (__m128 a)
//! \todo __m128 _mm_rcp_ss (__m128 a)
//! \todo __m128 _mm_rsqrt_ps (__m128 a)
//! \todo __m128 _mm_rsqrt_ss (__m128 a)
//! \todo void _MM_SET_EXCEPTION_MASK (unsigned int a)
//! \todo void _MM_SET_EXCEPTION_STATE (unsigned int a)
//! \todo void _MM_SET_FLUSH_ZERO_MODE (unsigned int a)
static ANVIL_STRONG_INLINE __m128 ANVIL_SIMD_CALL _mm_set_ps(const float a, const float b, const float c, const float d) throw() {
	const float buf[4] = { a, b, c, d };
	return vld1q_f32(buf);
}
#define _mm_set_ps1(X) _mm_set1_ps(X)
//! \todo void _MM_SET_ROUNDING_MODE (unsigned int a)
#define _mm_set_ss(X) vsetq_lane_f32(X,_mm_set1_ps(),0)
#define _mm_set1_ps(X) vdupq_n_f32(X)
//! \todo void _mm_setcsr (unsigned int a)
//! \todo __m128 _mm_setr_ps (float e3, float e2, float e1, float e0)
#define _mm_setzero_ps() _mm_set1_ps(0.f)
//! \todo void _mm_sfence (void)
//! \todo __m128 _mm_shuffle_ps (__m128 a, __m128 b, unsigned int imm8)
//! \todo __m128 _mm_sqrt_ps (__m128 a)
//! \todo __m128 _mm_sqrt_ss (__m128 a)
#define _mm_store_ps(X,Y) _mm_storeu_ps(X,Y)
#define _mm_store_ps1(X,Y) _mm_store1_ps(X,Y)
#define _mm_store_ss(X,Y) _mm_store1_ps(X,Y)
static ANVIL_STRONG_INLINE void ANVIL_SIMD_CALL _mm_store1_ps(float* ptr, __m128 a) throw() {
	float tmp;
	vst1q_lane_f32(&tmp, a, 0);
	for (int i = 0; i < 4; ++i) ptr[i] = tmp;
}
static ANVIL_STRONG_INLINE void ANVIL_SIMD_CALL _mm_storer_ps(float* ptr, __m128 a) throw() {
	float buf[4];
	_mm_store_ps(buf, a);
	ptr[0] = buf[3];
	ptr[1] = buf[2];
	ptr[2] = buf[1];
	ptr[3] = buf[0];
}
#define _mm_storeu_ps(X,Y) vst1q_f32(X,Y)
#define _mm_stream_ps(X,Y) _mm_storeu_ps(X,Y)
#define _mm_sub_ps(X,Y) vsubq_f32(X,Y)
#define _mm_sub_ss(X,Y) vsetq_lane_f32(vget_lane_f32(vsub_f32(vget_low_f32(X), vget_low_f32(Y)),0), Y, 0)
//! \todo _MM_TRANSPOSE4_PS (__m128 row0, __m128 row1, __m128 row2, __m128 row3)
#define _mm_ucomieq_ss(X,Y) (vgetq_lane_f32(X,0) == vgetq_lane_f32(Y,0))
#define _mm_ucomige_ss(X,Y) (vgetq_lane_f32(X,0) >= vgetq_lane_f32(Y,0))
#define _mm_ucomigt_ss(X,Y) (vgetq_lane_f32(X,0) > vgetq_lane_f32(Y,0))
#define _mm_ucomile_ss(X,Y) (vgetq_lane_f32(X,0) <= vgetq_lane_f32(Y,0))
#define _mm_ucomilt_ss(X,Y) (vgetq_lane_f32(X,0) < vgetq_lane_f32(Y,0))
#define _mm_ucomineq_ss(X,Y) (vgetq_lane_f32(X,0) != vgetq_lane_f32(Y,0))
#define _mm_undefined_ps() __m128()
#define _mm_unpackhi_ps(X,Y) vcombine_f32(vget_high_f32(X),vget_high_f32(Y))
#define _mm_unpacklo_ps(X,Y) vcombine_f32(vget_low_f32(X),vget_low_f32(Y))
#define _mm_xor_ps(X,Y) vreinterpretq_f32_s32(veorq_s32(vreinterpretq_s32_f32(X),vreinterpretq_s32_f32(Y)))