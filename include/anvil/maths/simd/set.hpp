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

static ANVIL_STRONG_INLINE _simd_f64x2 ANVIL_SIMD_CALL _simd_f64x2_set_safe(_simd_f64x1 a0, _simd_f64x1 b0) {
	_simd_f64x2 tmp;
	reinterpret_cast<_simd_f64x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[1] = b0;
	return tmp;
}
#ifdef _simd_f64x2_set_
	#define _simd_f64x2_set(a0, b0) _simd_f64x2_set_(a0, b0)
	#define _simd_f64x2_set_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x2_set_instruction_set>()
#elif defined(_simd_f64x1_set_)
	#define _simd_f64x2_set_(a0, b0) _simd_f64x2_combine(\
		_simd_f64x1_set_(a0),\
		_simd_f64x1_set_(b0));
	#define _simd_f64x2_set(a0, b0) _simd_f64x2_set_(a0, b0)
	#define _simd_f64x2_set_enable() (_simd_f64x1_set_enable() && _simd_f64x2_combine_enable())
#else
	#define _simd_f64x2_set(a0, b0) _simd_f64x2_set_safe(a0, b0)
	#define _simd_f64x2_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_f64x4 ANVIL_SIMD_CALL _simd_f64x4_set_safe(_simd_f64x1 a0, _simd_f64x1 b0, _simd_f64x1 c0, _simd_f64x1 d0) {
	_simd_f64x4 tmp;
	reinterpret_cast<_simd_f64x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[3] = d0;
	return tmp;
}
#ifdef _simd_f64x4_set_
	#define _simd_f64x4_set(a0, b0, c0, d0) _simd_f64x4_set_(a0, b0, c0, d0)
	#define _simd_f64x4_set_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x4_set_instruction_set>()
#elif defined(_simd_f64x2_set_)
	#define _simd_f64x4_set_(a0, b0, c0, d0) _simd_f64x4_combine(\
		_simd_f64x2_set_(a0, b0),\
		_simd_f64x2_set_(c0, d0));
	#define _simd_f64x4_set(a0, b0, c0, d0) _simd_f64x4_set_(a0, b0, c0, d0)
	#define _simd_f64x4_set_enable() (_simd_f64x2_set_enable() && _simd_f64x4_combine_enable())
#else
	#define _simd_f64x4_set(a0, b0, c0, d0) _simd_f64x4_set_safe(a0, b0, c0, d0)
	#define _simd_f64x4_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_f64x8 ANVIL_SIMD_CALL _simd_f64x8_set_safe(_simd_f64x1 a0, _simd_f64x1 b0, _simd_f64x1 c0, _simd_f64x1 d0, _simd_f64x1 e0, _simd_f64x1 f0, _simd_f64x1 g0, _simd_f64x1 h0) {
	_simd_f64x8 tmp;
	reinterpret_cast<_simd_f64x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[7] = h0;
	return tmp;
}
#ifdef _simd_f64x8_set_
	#define _simd_f64x8_set(a0, b0, c0, d0, e0, f0, g0, h0) _simd_f64x8_set_(a0, b0, c0, d0, e0, f0, g0, h0)
	#define _simd_f64x8_set_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x8_set_instruction_set>()
#elif defined(_simd_f64x4_set_)
	#define _simd_f64x8_set_(a0, b0, c0, d0, e0, f0, g0, h0) _simd_f64x8_combine(\
		_simd_f64x4_set_(a0, b0, c0, d0),\
		_simd_f64x4_set_(e0, f0, g0, h0));
	#define _simd_f64x8_set(a0, b0, c0, d0, e0, f0, g0, h0) _simd_f64x8_set_(a0, b0, c0, d0, e0, f0, g0, h0)
	#define _simd_f64x8_set_enable() (_simd_f64x4_set_enable() && _simd_f64x8_combine_enable())
#else
	#define _simd_f64x8_set(a0, b0, c0, d0, e0, f0, g0, h0) _simd_f64x8_set_safe(a0, b0, c0, d0, e0, f0, g0, h0)
	#define _simd_f64x8_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_f64x16 ANVIL_SIMD_CALL _simd_f64x16_set_safe(_simd_f64x1 a0, _simd_f64x1 b0, _simd_f64x1 c0, _simd_f64x1 d0, _simd_f64x1 e0, _simd_f64x1 f0, _simd_f64x1 g0, _simd_f64x1 h0, _simd_f64x1 i0, _simd_f64x1 j0, _simd_f64x1 k0, _simd_f64x1 l0, _simd_f64x1 m0, _simd_f64x1 n0, _simd_f64x1 o0, _simd_f64x1 p0) {
	_simd_f64x16 tmp;
	reinterpret_cast<_simd_f64x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[7] = h0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[8] = i0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[9] = j0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[10] = k0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[11] = l0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[12] = m0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[13] = n0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[14] = o0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[15] = p0;
	return tmp;
}
#ifdef _simd_f64x16_set_
	#define _simd_f64x16_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_f64x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0)
	#define _simd_f64x16_set_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x16_set_instruction_set>()
#elif defined(_simd_f64x8_set_)
	#define _simd_f64x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_f64x16_combine(\
		_simd_f64x8_set_(a0, b0, c0, d0, e0, f0, g0, h0),\
		_simd_f64x8_set_(i0, j0, k0, l0, m0, n0, o0, p0));
	#define _simd_f64x16_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_f64x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0)
	#define _simd_f64x16_set_enable() (_simd_f64x8_set_enable() && _simd_f64x16_combine_enable())
#else
	#define _simd_f64x16_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_f64x16_set_safe(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0)
	#define _simd_f64x16_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_f64x32 ANVIL_SIMD_CALL _simd_f64x32_set_safe(_simd_f64x1 a0, _simd_f64x1 b0, _simd_f64x1 c0, _simd_f64x1 d0, _simd_f64x1 e0, _simd_f64x1 f0, _simd_f64x1 g0, _simd_f64x1 h0, _simd_f64x1 i0, _simd_f64x1 j0, _simd_f64x1 k0, _simd_f64x1 l0, _simd_f64x1 m0, _simd_f64x1 n0, _simd_f64x1 o0, _simd_f64x1 p0, _simd_f64x1 q0, _simd_f64x1 r0, _simd_f64x1 s0, _simd_f64x1 t0, _simd_f64x1 u0, _simd_f64x1 v0, _simd_f64x1 w0, _simd_f64x1 x0, _simd_f64x1 y0, _simd_f64x1 z0, _simd_f64x1 a1, _simd_f64x1 b1, _simd_f64x1 c1, _simd_f64x1 d1, _simd_f64x1 e1, _simd_f64x1 f1) {
	_simd_f64x32 tmp;
	reinterpret_cast<_simd_f64x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[7] = h0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[8] = i0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[9] = j0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[10] = k0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[11] = l0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[12] = m0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[13] = n0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[14] = o0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[15] = p0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[16] = q0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[17] = r0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[18] = s0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[19] = t0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[20] = u0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[21] = v0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[22] = w0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[23] = x0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[24] = y0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[25] = z0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[26] = a1;
	reinterpret_cast<_simd_f64x1*>(&tmp)[27] = b1;
	reinterpret_cast<_simd_f64x1*>(&tmp)[28] = c1;
	reinterpret_cast<_simd_f64x1*>(&tmp)[29] = d1;
	reinterpret_cast<_simd_f64x1*>(&tmp)[30] = e1;
	reinterpret_cast<_simd_f64x1*>(&tmp)[31] = f1;
	return tmp;
}
#ifdef _simd_f64x32_set_
	#define _simd_f64x32_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_f64x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1)
	#define _simd_f64x32_set_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x32_set_instruction_set>()
#elif defined(_simd_f64x16_set_)
	#define _simd_f64x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_f64x32_combine(\
		_simd_f64x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0),\
		_simd_f64x16_set_(q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1));
	#define _simd_f64x32_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_f64x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1)
	#define _simd_f64x32_set_enable() (_simd_f64x16_set_enable() && _simd_f64x32_combine_enable())
#else
	#define _simd_f64x32_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_f64x32_set_safe(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1)
	#define _simd_f64x32_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_f64x64 ANVIL_SIMD_CALL _simd_f64x64_set_safe(_simd_f64x1 a0, _simd_f64x1 b0, _simd_f64x1 c0, _simd_f64x1 d0, _simd_f64x1 e0, _simd_f64x1 f0, _simd_f64x1 g0, _simd_f64x1 h0, _simd_f64x1 i0, _simd_f64x1 j0, _simd_f64x1 k0, _simd_f64x1 l0, _simd_f64x1 m0, _simd_f64x1 n0, _simd_f64x1 o0, _simd_f64x1 p0, _simd_f64x1 q0, _simd_f64x1 r0, _simd_f64x1 s0, _simd_f64x1 t0, _simd_f64x1 u0, _simd_f64x1 v0, _simd_f64x1 w0, _simd_f64x1 x0, _simd_f64x1 y0, _simd_f64x1 z0, _simd_f64x1 a1, _simd_f64x1 b1, _simd_f64x1 c1, _simd_f64x1 d1, _simd_f64x1 e1, _simd_f64x1 f1, _simd_f64x1 g1, _simd_f64x1 h1, _simd_f64x1 i1, _simd_f64x1 j1, _simd_f64x1 k1, _simd_f64x1 l1, _simd_f64x1 m1, _simd_f64x1 n1, _simd_f64x1 o1, _simd_f64x1 p1, _simd_f64x1 q1, _simd_f64x1 r1, _simd_f64x1 s1, _simd_f64x1 t1, _simd_f64x1 u1, _simd_f64x1 v1, _simd_f64x1 w1, _simd_f64x1 x1, _simd_f64x1 y1, _simd_f64x1 z1, _simd_f64x1 a2, _simd_f64x1 b2, _simd_f64x1 c2, _simd_f64x1 d2, _simd_f64x1 e2, _simd_f64x1 f2, _simd_f64x1 g2, _simd_f64x1 h2, _simd_f64x1 i2, _simd_f64x1 j2, _simd_f64x1 k2, _simd_f64x1 l2) {
	_simd_f64x64 tmp;
	reinterpret_cast<_simd_f64x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[7] = h0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[8] = i0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[9] = j0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[10] = k0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[11] = l0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[12] = m0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[13] = n0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[14] = o0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[15] = p0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[16] = q0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[17] = r0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[18] = s0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[19] = t0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[20] = u0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[21] = v0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[22] = w0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[23] = x0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[24] = y0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[25] = z0;
	reinterpret_cast<_simd_f64x1*>(&tmp)[26] = a1;
	reinterpret_cast<_simd_f64x1*>(&tmp)[27] = b1;
	reinterpret_cast<_simd_f64x1*>(&tmp)[28] = c1;
	reinterpret_cast<_simd_f64x1*>(&tmp)[29] = d1;
	reinterpret_cast<_simd_f64x1*>(&tmp)[30] = e1;
	reinterpret_cast<_simd_f64x1*>(&tmp)[31] = f1;
	reinterpret_cast<_simd_f64x1*>(&tmp)[32] = g1;
	reinterpret_cast<_simd_f64x1*>(&tmp)[33] = h1;
	reinterpret_cast<_simd_f64x1*>(&tmp)[34] = i1;
	reinterpret_cast<_simd_f64x1*>(&tmp)[35] = j1;
	reinterpret_cast<_simd_f64x1*>(&tmp)[36] = k1;
	reinterpret_cast<_simd_f64x1*>(&tmp)[37] = l1;
	reinterpret_cast<_simd_f64x1*>(&tmp)[38] = m1;
	reinterpret_cast<_simd_f64x1*>(&tmp)[39] = n1;
	reinterpret_cast<_simd_f64x1*>(&tmp)[40] = o1;
	reinterpret_cast<_simd_f64x1*>(&tmp)[41] = p1;
	reinterpret_cast<_simd_f64x1*>(&tmp)[42] = q1;
	reinterpret_cast<_simd_f64x1*>(&tmp)[43] = r1;
	reinterpret_cast<_simd_f64x1*>(&tmp)[44] = s1;
	reinterpret_cast<_simd_f64x1*>(&tmp)[45] = t1;
	reinterpret_cast<_simd_f64x1*>(&tmp)[46] = u1;
	reinterpret_cast<_simd_f64x1*>(&tmp)[47] = v1;
	reinterpret_cast<_simd_f64x1*>(&tmp)[48] = w1;
	reinterpret_cast<_simd_f64x1*>(&tmp)[49] = x1;
	reinterpret_cast<_simd_f64x1*>(&tmp)[50] = y1;
	reinterpret_cast<_simd_f64x1*>(&tmp)[51] = z1;
	reinterpret_cast<_simd_f64x1*>(&tmp)[52] = a2;
	reinterpret_cast<_simd_f64x1*>(&tmp)[53] = b2;
	reinterpret_cast<_simd_f64x1*>(&tmp)[54] = c2;
	reinterpret_cast<_simd_f64x1*>(&tmp)[55] = d2;
	reinterpret_cast<_simd_f64x1*>(&tmp)[56] = e2;
	reinterpret_cast<_simd_f64x1*>(&tmp)[57] = f2;
	reinterpret_cast<_simd_f64x1*>(&tmp)[58] = g2;
	reinterpret_cast<_simd_f64x1*>(&tmp)[59] = h2;
	reinterpret_cast<_simd_f64x1*>(&tmp)[60] = i2;
	reinterpret_cast<_simd_f64x1*>(&tmp)[61] = j2;
	reinterpret_cast<_simd_f64x1*>(&tmp)[62] = k2;
	reinterpret_cast<_simd_f64x1*>(&tmp)[63] = l2;
	return tmp;
}
#ifdef _simd_f64x64_set_
	#define _simd_f64x64_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_f64x64_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2)
	#define _simd_f64x64_set_enable() anvil::simd::IsInstructionSetSupported<_simd_f64x64_set_instruction_set>()
#elif defined(_simd_f64x32_set_)
	#define _simd_f64x64_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_f64x64_combine(\
		_simd_f64x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1),\
		_simd_f64x32_set_(g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2));
	#define _simd_f64x64_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_f64x64_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2)
	#define _simd_f64x64_set_enable() (_simd_f64x32_set_enable() && _simd_f64x64_combine_enable())
#else
	#define _simd_f64x64_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_f64x64_set_safe(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2)
	#define _simd_f64x64_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_f32x2 ANVIL_SIMD_CALL _simd_f32x2_set_safe(_simd_f32x1 a0, _simd_f32x1 b0) {
	_simd_f32x2 tmp;
	reinterpret_cast<_simd_f32x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[1] = b0;
	return tmp;
}
#ifdef _simd_f32x2_set_
	#define _simd_f32x2_set(a0, b0) _simd_f32x2_set_(a0, b0)
	#define _simd_f32x2_set_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x2_set_instruction_set>()
#elif defined(_simd_f32x1_set_)
	#define _simd_f32x2_set_(a0, b0) _simd_f32x2_combine(\
		_simd_f32x1_set_(a0),\
		_simd_f32x1_set_(b0));
	#define _simd_f32x2_set(a0, b0) _simd_f32x2_set_(a0, b0)
	#define _simd_f32x2_set_enable() (_simd_f32x1_set_enable() && _simd_f32x2_combine_enable())
#else
	#define _simd_f32x2_set(a0, b0) _simd_f32x2_set_safe(a0, b0)
	#define _simd_f32x2_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_f32x4 ANVIL_SIMD_CALL _simd_f32x4_set_safe(_simd_f32x1 a0, _simd_f32x1 b0, _simd_f32x1 c0, _simd_f32x1 d0) {
	_simd_f32x4 tmp;
	reinterpret_cast<_simd_f32x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[3] = d0;
	return tmp;
}
#ifdef _simd_f32x4_set_
	#define _simd_f32x4_set(a0, b0, c0, d0) _simd_f32x4_set_(a0, b0, c0, d0)
	#define _simd_f32x4_set_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x4_set_instruction_set>()
#elif defined(_simd_f32x2_set_)
	#define _simd_f32x4_set_(a0, b0, c0, d0) _simd_f32x4_combine(\
		_simd_f32x2_set_(a0, b0),\
		_simd_f32x2_set_(c0, d0));
	#define _simd_f32x4_set(a0, b0, c0, d0) _simd_f32x4_set_(a0, b0, c0, d0)
	#define _simd_f32x4_set_enable() (_simd_f32x2_set_enable() && _simd_f32x4_combine_enable())
#else
	#define _simd_f32x4_set(a0, b0, c0, d0) _simd_f32x4_set_safe(a0, b0, c0, d0)
	#define _simd_f32x4_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_f32x8 ANVIL_SIMD_CALL _simd_f32x8_set_safe(_simd_f32x1 a0, _simd_f32x1 b0, _simd_f32x1 c0, _simd_f32x1 d0, _simd_f32x1 e0, _simd_f32x1 f0, _simd_f32x1 g0, _simd_f32x1 h0) {
	_simd_f32x8 tmp;
	reinterpret_cast<_simd_f32x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[7] = h0;
	return tmp;
}
#ifdef _simd_f32x8_set_
	#define _simd_f32x8_set(a0, b0, c0, d0, e0, f0, g0, h0) _simd_f32x8_set_(a0, b0, c0, d0, e0, f0, g0, h0)
	#define _simd_f32x8_set_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x8_set_instruction_set>()
#elif defined(_simd_f32x4_set_)
	#define _simd_f32x8_set_(a0, b0, c0, d0, e0, f0, g0, h0) _simd_f32x8_combine(\
		_simd_f32x4_set_(a0, b0, c0, d0),\
		_simd_f32x4_set_(e0, f0, g0, h0));
	#define _simd_f32x8_set(a0, b0, c0, d0, e0, f0, g0, h0) _simd_f32x8_set_(a0, b0, c0, d0, e0, f0, g0, h0)
	#define _simd_f32x8_set_enable() (_simd_f32x4_set_enable() && _simd_f32x8_combine_enable())
#else
	#define _simd_f32x8_set(a0, b0, c0, d0, e0, f0, g0, h0) _simd_f32x8_set_safe(a0, b0, c0, d0, e0, f0, g0, h0)
	#define _simd_f32x8_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_f32x16 ANVIL_SIMD_CALL _simd_f32x16_set_safe(_simd_f32x1 a0, _simd_f32x1 b0, _simd_f32x1 c0, _simd_f32x1 d0, _simd_f32x1 e0, _simd_f32x1 f0, _simd_f32x1 g0, _simd_f32x1 h0, _simd_f32x1 i0, _simd_f32x1 j0, _simd_f32x1 k0, _simd_f32x1 l0, _simd_f32x1 m0, _simd_f32x1 n0, _simd_f32x1 o0, _simd_f32x1 p0) {
	_simd_f32x16 tmp;
	reinterpret_cast<_simd_f32x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[7] = h0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[8] = i0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[9] = j0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[10] = k0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[11] = l0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[12] = m0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[13] = n0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[14] = o0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[15] = p0;
	return tmp;
}
#ifdef _simd_f32x16_set_
	#define _simd_f32x16_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_f32x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0)
	#define _simd_f32x16_set_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x16_set_instruction_set>()
#elif defined(_simd_f32x8_set_)
	#define _simd_f32x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_f32x16_combine(\
		_simd_f32x8_set_(a0, b0, c0, d0, e0, f0, g0, h0),\
		_simd_f32x8_set_(i0, j0, k0, l0, m0, n0, o0, p0));
	#define _simd_f32x16_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_f32x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0)
	#define _simd_f32x16_set_enable() (_simd_f32x8_set_enable() && _simd_f32x16_combine_enable())
#else
	#define _simd_f32x16_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_f32x16_set_safe(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0)
	#define _simd_f32x16_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_f32x32 ANVIL_SIMD_CALL _simd_f32x32_set_safe(_simd_f32x1 a0, _simd_f32x1 b0, _simd_f32x1 c0, _simd_f32x1 d0, _simd_f32x1 e0, _simd_f32x1 f0, _simd_f32x1 g0, _simd_f32x1 h0, _simd_f32x1 i0, _simd_f32x1 j0, _simd_f32x1 k0, _simd_f32x1 l0, _simd_f32x1 m0, _simd_f32x1 n0, _simd_f32x1 o0, _simd_f32x1 p0, _simd_f32x1 q0, _simd_f32x1 r0, _simd_f32x1 s0, _simd_f32x1 t0, _simd_f32x1 u0, _simd_f32x1 v0, _simd_f32x1 w0, _simd_f32x1 x0, _simd_f32x1 y0, _simd_f32x1 z0, _simd_f32x1 a1, _simd_f32x1 b1, _simd_f32x1 c1, _simd_f32x1 d1, _simd_f32x1 e1, _simd_f32x1 f1) {
	_simd_f32x32 tmp;
	reinterpret_cast<_simd_f32x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[7] = h0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[8] = i0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[9] = j0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[10] = k0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[11] = l0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[12] = m0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[13] = n0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[14] = o0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[15] = p0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[16] = q0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[17] = r0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[18] = s0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[19] = t0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[20] = u0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[21] = v0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[22] = w0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[23] = x0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[24] = y0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[25] = z0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[26] = a1;
	reinterpret_cast<_simd_f32x1*>(&tmp)[27] = b1;
	reinterpret_cast<_simd_f32x1*>(&tmp)[28] = c1;
	reinterpret_cast<_simd_f32x1*>(&tmp)[29] = d1;
	reinterpret_cast<_simd_f32x1*>(&tmp)[30] = e1;
	reinterpret_cast<_simd_f32x1*>(&tmp)[31] = f1;
	return tmp;
}
#ifdef _simd_f32x32_set_
	#define _simd_f32x32_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_f32x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1)
	#define _simd_f32x32_set_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x32_set_instruction_set>()
#elif defined(_simd_f32x16_set_)
	#define _simd_f32x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_f32x32_combine(\
		_simd_f32x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0),\
		_simd_f32x16_set_(q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1));
	#define _simd_f32x32_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_f32x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1)
	#define _simd_f32x32_set_enable() (_simd_f32x16_set_enable() && _simd_f32x32_combine_enable())
#else
	#define _simd_f32x32_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_f32x32_set_safe(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1)
	#define _simd_f32x32_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_f32x64 ANVIL_SIMD_CALL _simd_f32x64_set_safe(_simd_f32x1 a0, _simd_f32x1 b0, _simd_f32x1 c0, _simd_f32x1 d0, _simd_f32x1 e0, _simd_f32x1 f0, _simd_f32x1 g0, _simd_f32x1 h0, _simd_f32x1 i0, _simd_f32x1 j0, _simd_f32x1 k0, _simd_f32x1 l0, _simd_f32x1 m0, _simd_f32x1 n0, _simd_f32x1 o0, _simd_f32x1 p0, _simd_f32x1 q0, _simd_f32x1 r0, _simd_f32x1 s0, _simd_f32x1 t0, _simd_f32x1 u0, _simd_f32x1 v0, _simd_f32x1 w0, _simd_f32x1 x0, _simd_f32x1 y0, _simd_f32x1 z0, _simd_f32x1 a1, _simd_f32x1 b1, _simd_f32x1 c1, _simd_f32x1 d1, _simd_f32x1 e1, _simd_f32x1 f1, _simd_f32x1 g1, _simd_f32x1 h1, _simd_f32x1 i1, _simd_f32x1 j1, _simd_f32x1 k1, _simd_f32x1 l1, _simd_f32x1 m1, _simd_f32x1 n1, _simd_f32x1 o1, _simd_f32x1 p1, _simd_f32x1 q1, _simd_f32x1 r1, _simd_f32x1 s1, _simd_f32x1 t1, _simd_f32x1 u1, _simd_f32x1 v1, _simd_f32x1 w1, _simd_f32x1 x1, _simd_f32x1 y1, _simd_f32x1 z1, _simd_f32x1 a2, _simd_f32x1 b2, _simd_f32x1 c2, _simd_f32x1 d2, _simd_f32x1 e2, _simd_f32x1 f2, _simd_f32x1 g2, _simd_f32x1 h2, _simd_f32x1 i2, _simd_f32x1 j2, _simd_f32x1 k2, _simd_f32x1 l2) {
	_simd_f32x64 tmp;
	reinterpret_cast<_simd_f32x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[7] = h0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[8] = i0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[9] = j0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[10] = k0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[11] = l0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[12] = m0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[13] = n0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[14] = o0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[15] = p0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[16] = q0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[17] = r0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[18] = s0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[19] = t0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[20] = u0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[21] = v0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[22] = w0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[23] = x0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[24] = y0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[25] = z0;
	reinterpret_cast<_simd_f32x1*>(&tmp)[26] = a1;
	reinterpret_cast<_simd_f32x1*>(&tmp)[27] = b1;
	reinterpret_cast<_simd_f32x1*>(&tmp)[28] = c1;
	reinterpret_cast<_simd_f32x1*>(&tmp)[29] = d1;
	reinterpret_cast<_simd_f32x1*>(&tmp)[30] = e1;
	reinterpret_cast<_simd_f32x1*>(&tmp)[31] = f1;
	reinterpret_cast<_simd_f32x1*>(&tmp)[32] = g1;
	reinterpret_cast<_simd_f32x1*>(&tmp)[33] = h1;
	reinterpret_cast<_simd_f32x1*>(&tmp)[34] = i1;
	reinterpret_cast<_simd_f32x1*>(&tmp)[35] = j1;
	reinterpret_cast<_simd_f32x1*>(&tmp)[36] = k1;
	reinterpret_cast<_simd_f32x1*>(&tmp)[37] = l1;
	reinterpret_cast<_simd_f32x1*>(&tmp)[38] = m1;
	reinterpret_cast<_simd_f32x1*>(&tmp)[39] = n1;
	reinterpret_cast<_simd_f32x1*>(&tmp)[40] = o1;
	reinterpret_cast<_simd_f32x1*>(&tmp)[41] = p1;
	reinterpret_cast<_simd_f32x1*>(&tmp)[42] = q1;
	reinterpret_cast<_simd_f32x1*>(&tmp)[43] = r1;
	reinterpret_cast<_simd_f32x1*>(&tmp)[44] = s1;
	reinterpret_cast<_simd_f32x1*>(&tmp)[45] = t1;
	reinterpret_cast<_simd_f32x1*>(&tmp)[46] = u1;
	reinterpret_cast<_simd_f32x1*>(&tmp)[47] = v1;
	reinterpret_cast<_simd_f32x1*>(&tmp)[48] = w1;
	reinterpret_cast<_simd_f32x1*>(&tmp)[49] = x1;
	reinterpret_cast<_simd_f32x1*>(&tmp)[50] = y1;
	reinterpret_cast<_simd_f32x1*>(&tmp)[51] = z1;
	reinterpret_cast<_simd_f32x1*>(&tmp)[52] = a2;
	reinterpret_cast<_simd_f32x1*>(&tmp)[53] = b2;
	reinterpret_cast<_simd_f32x1*>(&tmp)[54] = c2;
	reinterpret_cast<_simd_f32x1*>(&tmp)[55] = d2;
	reinterpret_cast<_simd_f32x1*>(&tmp)[56] = e2;
	reinterpret_cast<_simd_f32x1*>(&tmp)[57] = f2;
	reinterpret_cast<_simd_f32x1*>(&tmp)[58] = g2;
	reinterpret_cast<_simd_f32x1*>(&tmp)[59] = h2;
	reinterpret_cast<_simd_f32x1*>(&tmp)[60] = i2;
	reinterpret_cast<_simd_f32x1*>(&tmp)[61] = j2;
	reinterpret_cast<_simd_f32x1*>(&tmp)[62] = k2;
	reinterpret_cast<_simd_f32x1*>(&tmp)[63] = l2;
	return tmp;
}
#ifdef _simd_f32x64_set_
	#define _simd_f32x64_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_f32x64_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2)
	#define _simd_f32x64_set_enable() anvil::simd::IsInstructionSetSupported<_simd_f32x64_set_instruction_set>()
#elif defined(_simd_f32x32_set_)
	#define _simd_f32x64_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_f32x64_combine(\
		_simd_f32x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1),\
		_simd_f32x32_set_(g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2));
	#define _simd_f32x64_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_f32x64_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2)
	#define _simd_f32x64_set_enable() (_simd_f32x32_set_enable() && _simd_f32x64_combine_enable())
#else
	#define _simd_f32x64_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_f32x64_set_safe(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2)
	#define _simd_f32x64_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s64x2 ANVIL_SIMD_CALL _simd_s64x2_set_safe(_simd_s64x1 a0, _simd_s64x1 b0) {
	_simd_s64x2 tmp;
	reinterpret_cast<_simd_s64x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[1] = b0;
	return tmp;
}
#ifdef _simd_s64x2_set_
	#define _simd_s64x2_set(a0, b0) _simd_s64x2_set_(a0, b0)
	#define _simd_s64x2_set_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x2_set_instruction_set>()
#elif defined(_simd_s64x1_set_)
	#define _simd_s64x2_set_(a0, b0) _simd_s64x2_combine(\
		_simd_s64x1_set_(a0),\
		_simd_s64x1_set_(b0));
	#define _simd_s64x2_set(a0, b0) _simd_s64x2_set_(a0, b0)
	#define _simd_s64x2_set_enable() (_simd_s64x1_set_enable() && _simd_s64x2_combine_enable())
#else
	#define _simd_s64x2_set(a0, b0) _simd_s64x2_set_safe(a0, b0)
	#define _simd_s64x2_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s64x4 ANVIL_SIMD_CALL _simd_s64x4_set_safe(_simd_s64x1 a0, _simd_s64x1 b0, _simd_s64x1 c0, _simd_s64x1 d0) {
	_simd_s64x4 tmp;
	reinterpret_cast<_simd_s64x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[3] = d0;
	return tmp;
}
#ifdef _simd_s64x4_set_
	#define _simd_s64x4_set(a0, b0, c0, d0) _simd_s64x4_set_(a0, b0, c0, d0)
	#define _simd_s64x4_set_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x4_set_instruction_set>()
#elif defined(_simd_s64x2_set_)
	#define _simd_s64x4_set_(a0, b0, c0, d0) _simd_s64x4_combine(\
		_simd_s64x2_set_(a0, b0),\
		_simd_s64x2_set_(c0, d0));
	#define _simd_s64x4_set(a0, b0, c0, d0) _simd_s64x4_set_(a0, b0, c0, d0)
	#define _simd_s64x4_set_enable() (_simd_s64x2_set_enable() && _simd_s64x4_combine_enable())
#else
	#define _simd_s64x4_set(a0, b0, c0, d0) _simd_s64x4_set_safe(a0, b0, c0, d0)
	#define _simd_s64x4_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s64x8 ANVIL_SIMD_CALL _simd_s64x8_set_safe(_simd_s64x1 a0, _simd_s64x1 b0, _simd_s64x1 c0, _simd_s64x1 d0, _simd_s64x1 e0, _simd_s64x1 f0, _simd_s64x1 g0, _simd_s64x1 h0) {
	_simd_s64x8 tmp;
	reinterpret_cast<_simd_s64x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[7] = h0;
	return tmp;
}
#ifdef _simd_s64x8_set_
	#define _simd_s64x8_set(a0, b0, c0, d0, e0, f0, g0, h0) _simd_s64x8_set_(a0, b0, c0, d0, e0, f0, g0, h0)
	#define _simd_s64x8_set_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x8_set_instruction_set>()
#elif defined(_simd_s64x4_set_)
	#define _simd_s64x8_set_(a0, b0, c0, d0, e0, f0, g0, h0) _simd_s64x8_combine(\
		_simd_s64x4_set_(a0, b0, c0, d0),\
		_simd_s64x4_set_(e0, f0, g0, h0));
	#define _simd_s64x8_set(a0, b0, c0, d0, e0, f0, g0, h0) _simd_s64x8_set_(a0, b0, c0, d0, e0, f0, g0, h0)
	#define _simd_s64x8_set_enable() (_simd_s64x4_set_enable() && _simd_s64x8_combine_enable())
#else
	#define _simd_s64x8_set(a0, b0, c0, d0, e0, f0, g0, h0) _simd_s64x8_set_safe(a0, b0, c0, d0, e0, f0, g0, h0)
	#define _simd_s64x8_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s64x16 ANVIL_SIMD_CALL _simd_s64x16_set_safe(_simd_s64x1 a0, _simd_s64x1 b0, _simd_s64x1 c0, _simd_s64x1 d0, _simd_s64x1 e0, _simd_s64x1 f0, _simd_s64x1 g0, _simd_s64x1 h0, _simd_s64x1 i0, _simd_s64x1 j0, _simd_s64x1 k0, _simd_s64x1 l0, _simd_s64x1 m0, _simd_s64x1 n0, _simd_s64x1 o0, _simd_s64x1 p0) {
	_simd_s64x16 tmp;
	reinterpret_cast<_simd_s64x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[7] = h0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[8] = i0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[9] = j0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[10] = k0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[11] = l0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[12] = m0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[13] = n0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[14] = o0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[15] = p0;
	return tmp;
}
#ifdef _simd_s64x16_set_
	#define _simd_s64x16_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_s64x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0)
	#define _simd_s64x16_set_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x16_set_instruction_set>()
#elif defined(_simd_s64x8_set_)
	#define _simd_s64x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_s64x16_combine(\
		_simd_s64x8_set_(a0, b0, c0, d0, e0, f0, g0, h0),\
		_simd_s64x8_set_(i0, j0, k0, l0, m0, n0, o0, p0));
	#define _simd_s64x16_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_s64x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0)
	#define _simd_s64x16_set_enable() (_simd_s64x8_set_enable() && _simd_s64x16_combine_enable())
#else
	#define _simd_s64x16_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_s64x16_set_safe(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0)
	#define _simd_s64x16_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s64x32 ANVIL_SIMD_CALL _simd_s64x32_set_safe(_simd_s64x1 a0, _simd_s64x1 b0, _simd_s64x1 c0, _simd_s64x1 d0, _simd_s64x1 e0, _simd_s64x1 f0, _simd_s64x1 g0, _simd_s64x1 h0, _simd_s64x1 i0, _simd_s64x1 j0, _simd_s64x1 k0, _simd_s64x1 l0, _simd_s64x1 m0, _simd_s64x1 n0, _simd_s64x1 o0, _simd_s64x1 p0, _simd_s64x1 q0, _simd_s64x1 r0, _simd_s64x1 s0, _simd_s64x1 t0, _simd_s64x1 u0, _simd_s64x1 v0, _simd_s64x1 w0, _simd_s64x1 x0, _simd_s64x1 y0, _simd_s64x1 z0, _simd_s64x1 a1, _simd_s64x1 b1, _simd_s64x1 c1, _simd_s64x1 d1, _simd_s64x1 e1, _simd_s64x1 f1) {
	_simd_s64x32 tmp;
	reinterpret_cast<_simd_s64x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[7] = h0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[8] = i0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[9] = j0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[10] = k0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[11] = l0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[12] = m0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[13] = n0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[14] = o0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[15] = p0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[16] = q0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[17] = r0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[18] = s0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[19] = t0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[20] = u0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[21] = v0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[22] = w0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[23] = x0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[24] = y0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[25] = z0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[26] = a1;
	reinterpret_cast<_simd_s64x1*>(&tmp)[27] = b1;
	reinterpret_cast<_simd_s64x1*>(&tmp)[28] = c1;
	reinterpret_cast<_simd_s64x1*>(&tmp)[29] = d1;
	reinterpret_cast<_simd_s64x1*>(&tmp)[30] = e1;
	reinterpret_cast<_simd_s64x1*>(&tmp)[31] = f1;
	return tmp;
}
#ifdef _simd_s64x32_set_
	#define _simd_s64x32_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_s64x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1)
	#define _simd_s64x32_set_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x32_set_instruction_set>()
#elif defined(_simd_s64x16_set_)
	#define _simd_s64x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_s64x32_combine(\
		_simd_s64x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0),\
		_simd_s64x16_set_(q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1));
	#define _simd_s64x32_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_s64x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1)
	#define _simd_s64x32_set_enable() (_simd_s64x16_set_enable() && _simd_s64x32_combine_enable())
#else
	#define _simd_s64x32_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_s64x32_set_safe(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1)
	#define _simd_s64x32_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s64x64 ANVIL_SIMD_CALL _simd_s64x64_set_safe(_simd_s64x1 a0, _simd_s64x1 b0, _simd_s64x1 c0, _simd_s64x1 d0, _simd_s64x1 e0, _simd_s64x1 f0, _simd_s64x1 g0, _simd_s64x1 h0, _simd_s64x1 i0, _simd_s64x1 j0, _simd_s64x1 k0, _simd_s64x1 l0, _simd_s64x1 m0, _simd_s64x1 n0, _simd_s64x1 o0, _simd_s64x1 p0, _simd_s64x1 q0, _simd_s64x1 r0, _simd_s64x1 s0, _simd_s64x1 t0, _simd_s64x1 u0, _simd_s64x1 v0, _simd_s64x1 w0, _simd_s64x1 x0, _simd_s64x1 y0, _simd_s64x1 z0, _simd_s64x1 a1, _simd_s64x1 b1, _simd_s64x1 c1, _simd_s64x1 d1, _simd_s64x1 e1, _simd_s64x1 f1, _simd_s64x1 g1, _simd_s64x1 h1, _simd_s64x1 i1, _simd_s64x1 j1, _simd_s64x1 k1, _simd_s64x1 l1, _simd_s64x1 m1, _simd_s64x1 n1, _simd_s64x1 o1, _simd_s64x1 p1, _simd_s64x1 q1, _simd_s64x1 r1, _simd_s64x1 s1, _simd_s64x1 t1, _simd_s64x1 u1, _simd_s64x1 v1, _simd_s64x1 w1, _simd_s64x1 x1, _simd_s64x1 y1, _simd_s64x1 z1, _simd_s64x1 a2, _simd_s64x1 b2, _simd_s64x1 c2, _simd_s64x1 d2, _simd_s64x1 e2, _simd_s64x1 f2, _simd_s64x1 g2, _simd_s64x1 h2, _simd_s64x1 i2, _simd_s64x1 j2, _simd_s64x1 k2, _simd_s64x1 l2) {
	_simd_s64x64 tmp;
	reinterpret_cast<_simd_s64x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[7] = h0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[8] = i0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[9] = j0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[10] = k0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[11] = l0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[12] = m0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[13] = n0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[14] = o0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[15] = p0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[16] = q0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[17] = r0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[18] = s0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[19] = t0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[20] = u0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[21] = v0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[22] = w0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[23] = x0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[24] = y0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[25] = z0;
	reinterpret_cast<_simd_s64x1*>(&tmp)[26] = a1;
	reinterpret_cast<_simd_s64x1*>(&tmp)[27] = b1;
	reinterpret_cast<_simd_s64x1*>(&tmp)[28] = c1;
	reinterpret_cast<_simd_s64x1*>(&tmp)[29] = d1;
	reinterpret_cast<_simd_s64x1*>(&tmp)[30] = e1;
	reinterpret_cast<_simd_s64x1*>(&tmp)[31] = f1;
	reinterpret_cast<_simd_s64x1*>(&tmp)[32] = g1;
	reinterpret_cast<_simd_s64x1*>(&tmp)[33] = h1;
	reinterpret_cast<_simd_s64x1*>(&tmp)[34] = i1;
	reinterpret_cast<_simd_s64x1*>(&tmp)[35] = j1;
	reinterpret_cast<_simd_s64x1*>(&tmp)[36] = k1;
	reinterpret_cast<_simd_s64x1*>(&tmp)[37] = l1;
	reinterpret_cast<_simd_s64x1*>(&tmp)[38] = m1;
	reinterpret_cast<_simd_s64x1*>(&tmp)[39] = n1;
	reinterpret_cast<_simd_s64x1*>(&tmp)[40] = o1;
	reinterpret_cast<_simd_s64x1*>(&tmp)[41] = p1;
	reinterpret_cast<_simd_s64x1*>(&tmp)[42] = q1;
	reinterpret_cast<_simd_s64x1*>(&tmp)[43] = r1;
	reinterpret_cast<_simd_s64x1*>(&tmp)[44] = s1;
	reinterpret_cast<_simd_s64x1*>(&tmp)[45] = t1;
	reinterpret_cast<_simd_s64x1*>(&tmp)[46] = u1;
	reinterpret_cast<_simd_s64x1*>(&tmp)[47] = v1;
	reinterpret_cast<_simd_s64x1*>(&tmp)[48] = w1;
	reinterpret_cast<_simd_s64x1*>(&tmp)[49] = x1;
	reinterpret_cast<_simd_s64x1*>(&tmp)[50] = y1;
	reinterpret_cast<_simd_s64x1*>(&tmp)[51] = z1;
	reinterpret_cast<_simd_s64x1*>(&tmp)[52] = a2;
	reinterpret_cast<_simd_s64x1*>(&tmp)[53] = b2;
	reinterpret_cast<_simd_s64x1*>(&tmp)[54] = c2;
	reinterpret_cast<_simd_s64x1*>(&tmp)[55] = d2;
	reinterpret_cast<_simd_s64x1*>(&tmp)[56] = e2;
	reinterpret_cast<_simd_s64x1*>(&tmp)[57] = f2;
	reinterpret_cast<_simd_s64x1*>(&tmp)[58] = g2;
	reinterpret_cast<_simd_s64x1*>(&tmp)[59] = h2;
	reinterpret_cast<_simd_s64x1*>(&tmp)[60] = i2;
	reinterpret_cast<_simd_s64x1*>(&tmp)[61] = j2;
	reinterpret_cast<_simd_s64x1*>(&tmp)[62] = k2;
	reinterpret_cast<_simd_s64x1*>(&tmp)[63] = l2;
	return tmp;
}
#ifdef _simd_s64x64_set_
	#define _simd_s64x64_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_s64x64_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2)
	#define _simd_s64x64_set_enable() anvil::simd::IsInstructionSetSupported<_simd_s64x64_set_instruction_set>()
#elif defined(_simd_s64x32_set_)
	#define _simd_s64x64_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_s64x64_combine(\
		_simd_s64x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1),\
		_simd_s64x32_set_(g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2));
	#define _simd_s64x64_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_s64x64_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2)
	#define _simd_s64x64_set_enable() (_simd_s64x32_set_enable() && _simd_s64x64_combine_enable())
#else
	#define _simd_s64x64_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_s64x64_set_safe(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2)
	#define _simd_s64x64_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u64x2 ANVIL_SIMD_CALL _simd_u64x2_set_safe(_simd_u64x1 a0, _simd_u64x1 b0) {
	_simd_u64x2 tmp;
	reinterpret_cast<_simd_u64x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[1] = b0;
	return tmp;
}
#ifdef _simd_u64x2_set_
	#define _simd_u64x2_set(a0, b0) _simd_u64x2_set_(a0, b0)
	#define _simd_u64x2_set_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x2_set_instruction_set>()
#elif defined(_simd_u64x1_set_)
	#define _simd_u64x2_set_(a0, b0) _simd_u64x2_combine(\
		_simd_u64x1_set_(a0),\
		_simd_u64x1_set_(b0));
	#define _simd_u64x2_set(a0, b0) _simd_u64x2_set_(a0, b0)
	#define _simd_u64x2_set_enable() (_simd_u64x1_set_enable() && _simd_u64x2_combine_enable())
#else
	#define _simd_u64x2_set(a0, b0) _simd_u64x2_set_safe(a0, b0)
	#define _simd_u64x2_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u64x4 ANVIL_SIMD_CALL _simd_u64x4_set_safe(_simd_u64x1 a0, _simd_u64x1 b0, _simd_u64x1 c0, _simd_u64x1 d0) {
	_simd_u64x4 tmp;
	reinterpret_cast<_simd_u64x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[3] = d0;
	return tmp;
}
#ifdef _simd_u64x4_set_
	#define _simd_u64x4_set(a0, b0, c0, d0) _simd_u64x4_set_(a0, b0, c0, d0)
	#define _simd_u64x4_set_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x4_set_instruction_set>()
#elif defined(_simd_u64x2_set_)
	#define _simd_u64x4_set_(a0, b0, c0, d0) _simd_u64x4_combine(\
		_simd_u64x2_set_(a0, b0),\
		_simd_u64x2_set_(c0, d0));
	#define _simd_u64x4_set(a0, b0, c0, d0) _simd_u64x4_set_(a0, b0, c0, d0)
	#define _simd_u64x4_set_enable() (_simd_u64x2_set_enable() && _simd_u64x4_combine_enable())
#else
	#define _simd_u64x4_set(a0, b0, c0, d0) _simd_u64x4_set_safe(a0, b0, c0, d0)
	#define _simd_u64x4_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u64x8 ANVIL_SIMD_CALL _simd_u64x8_set_safe(_simd_u64x1 a0, _simd_u64x1 b0, _simd_u64x1 c0, _simd_u64x1 d0, _simd_u64x1 e0, _simd_u64x1 f0, _simd_u64x1 g0, _simd_u64x1 h0) {
	_simd_u64x8 tmp;
	reinterpret_cast<_simd_u64x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[7] = h0;
	return tmp;
}
#ifdef _simd_u64x8_set_
	#define _simd_u64x8_set(a0, b0, c0, d0, e0, f0, g0, h0) _simd_u64x8_set_(a0, b0, c0, d0, e0, f0, g0, h0)
	#define _simd_u64x8_set_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x8_set_instruction_set>()
#elif defined(_simd_u64x4_set_)
	#define _simd_u64x8_set_(a0, b0, c0, d0, e0, f0, g0, h0) _simd_u64x8_combine(\
		_simd_u64x4_set_(a0, b0, c0, d0),\
		_simd_u64x4_set_(e0, f0, g0, h0));
	#define _simd_u64x8_set(a0, b0, c0, d0, e0, f0, g0, h0) _simd_u64x8_set_(a0, b0, c0, d0, e0, f0, g0, h0)
	#define _simd_u64x8_set_enable() (_simd_u64x4_set_enable() && _simd_u64x8_combine_enable())
#else
	#define _simd_u64x8_set(a0, b0, c0, d0, e0, f0, g0, h0) _simd_u64x8_set_safe(a0, b0, c0, d0, e0, f0, g0, h0)
	#define _simd_u64x8_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u64x16 ANVIL_SIMD_CALL _simd_u64x16_set_safe(_simd_u64x1 a0, _simd_u64x1 b0, _simd_u64x1 c0, _simd_u64x1 d0, _simd_u64x1 e0, _simd_u64x1 f0, _simd_u64x1 g0, _simd_u64x1 h0, _simd_u64x1 i0, _simd_u64x1 j0, _simd_u64x1 k0, _simd_u64x1 l0, _simd_u64x1 m0, _simd_u64x1 n0, _simd_u64x1 o0, _simd_u64x1 p0) {
	_simd_u64x16 tmp;
	reinterpret_cast<_simd_u64x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[7] = h0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[8] = i0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[9] = j0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[10] = k0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[11] = l0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[12] = m0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[13] = n0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[14] = o0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[15] = p0;
	return tmp;
}
#ifdef _simd_u64x16_set_
	#define _simd_u64x16_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_u64x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0)
	#define _simd_u64x16_set_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x16_set_instruction_set>()
#elif defined(_simd_u64x8_set_)
	#define _simd_u64x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_u64x16_combine(\
		_simd_u64x8_set_(a0, b0, c0, d0, e0, f0, g0, h0),\
		_simd_u64x8_set_(i0, j0, k0, l0, m0, n0, o0, p0));
	#define _simd_u64x16_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_u64x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0)
	#define _simd_u64x16_set_enable() (_simd_u64x8_set_enable() && _simd_u64x16_combine_enable())
#else
	#define _simd_u64x16_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_u64x16_set_safe(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0)
	#define _simd_u64x16_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u64x32 ANVIL_SIMD_CALL _simd_u64x32_set_safe(_simd_u64x1 a0, _simd_u64x1 b0, _simd_u64x1 c0, _simd_u64x1 d0, _simd_u64x1 e0, _simd_u64x1 f0, _simd_u64x1 g0, _simd_u64x1 h0, _simd_u64x1 i0, _simd_u64x1 j0, _simd_u64x1 k0, _simd_u64x1 l0, _simd_u64x1 m0, _simd_u64x1 n0, _simd_u64x1 o0, _simd_u64x1 p0, _simd_u64x1 q0, _simd_u64x1 r0, _simd_u64x1 s0, _simd_u64x1 t0, _simd_u64x1 u0, _simd_u64x1 v0, _simd_u64x1 w0, _simd_u64x1 x0, _simd_u64x1 y0, _simd_u64x1 z0, _simd_u64x1 a1, _simd_u64x1 b1, _simd_u64x1 c1, _simd_u64x1 d1, _simd_u64x1 e1, _simd_u64x1 f1) {
	_simd_u64x32 tmp;
	reinterpret_cast<_simd_u64x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[7] = h0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[8] = i0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[9] = j0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[10] = k0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[11] = l0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[12] = m0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[13] = n0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[14] = o0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[15] = p0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[16] = q0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[17] = r0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[18] = s0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[19] = t0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[20] = u0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[21] = v0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[22] = w0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[23] = x0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[24] = y0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[25] = z0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[26] = a1;
	reinterpret_cast<_simd_u64x1*>(&tmp)[27] = b1;
	reinterpret_cast<_simd_u64x1*>(&tmp)[28] = c1;
	reinterpret_cast<_simd_u64x1*>(&tmp)[29] = d1;
	reinterpret_cast<_simd_u64x1*>(&tmp)[30] = e1;
	reinterpret_cast<_simd_u64x1*>(&tmp)[31] = f1;
	return tmp;
}
#ifdef _simd_u64x32_set_
	#define _simd_u64x32_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_u64x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1)
	#define _simd_u64x32_set_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x32_set_instruction_set>()
#elif defined(_simd_u64x16_set_)
	#define _simd_u64x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_u64x32_combine(\
		_simd_u64x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0),\
		_simd_u64x16_set_(q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1));
	#define _simd_u64x32_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_u64x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1)
	#define _simd_u64x32_set_enable() (_simd_u64x16_set_enable() && _simd_u64x32_combine_enable())
#else
	#define _simd_u64x32_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_u64x32_set_safe(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1)
	#define _simd_u64x32_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u64x64 ANVIL_SIMD_CALL _simd_u64x64_set_safe(_simd_u64x1 a0, _simd_u64x1 b0, _simd_u64x1 c0, _simd_u64x1 d0, _simd_u64x1 e0, _simd_u64x1 f0, _simd_u64x1 g0, _simd_u64x1 h0, _simd_u64x1 i0, _simd_u64x1 j0, _simd_u64x1 k0, _simd_u64x1 l0, _simd_u64x1 m0, _simd_u64x1 n0, _simd_u64x1 o0, _simd_u64x1 p0, _simd_u64x1 q0, _simd_u64x1 r0, _simd_u64x1 s0, _simd_u64x1 t0, _simd_u64x1 u0, _simd_u64x1 v0, _simd_u64x1 w0, _simd_u64x1 x0, _simd_u64x1 y0, _simd_u64x1 z0, _simd_u64x1 a1, _simd_u64x1 b1, _simd_u64x1 c1, _simd_u64x1 d1, _simd_u64x1 e1, _simd_u64x1 f1, _simd_u64x1 g1, _simd_u64x1 h1, _simd_u64x1 i1, _simd_u64x1 j1, _simd_u64x1 k1, _simd_u64x1 l1, _simd_u64x1 m1, _simd_u64x1 n1, _simd_u64x1 o1, _simd_u64x1 p1, _simd_u64x1 q1, _simd_u64x1 r1, _simd_u64x1 s1, _simd_u64x1 t1, _simd_u64x1 u1, _simd_u64x1 v1, _simd_u64x1 w1, _simd_u64x1 x1, _simd_u64x1 y1, _simd_u64x1 z1, _simd_u64x1 a2, _simd_u64x1 b2, _simd_u64x1 c2, _simd_u64x1 d2, _simd_u64x1 e2, _simd_u64x1 f2, _simd_u64x1 g2, _simd_u64x1 h2, _simd_u64x1 i2, _simd_u64x1 j2, _simd_u64x1 k2, _simd_u64x1 l2) {
	_simd_u64x64 tmp;
	reinterpret_cast<_simd_u64x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[7] = h0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[8] = i0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[9] = j0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[10] = k0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[11] = l0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[12] = m0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[13] = n0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[14] = o0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[15] = p0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[16] = q0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[17] = r0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[18] = s0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[19] = t0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[20] = u0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[21] = v0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[22] = w0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[23] = x0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[24] = y0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[25] = z0;
	reinterpret_cast<_simd_u64x1*>(&tmp)[26] = a1;
	reinterpret_cast<_simd_u64x1*>(&tmp)[27] = b1;
	reinterpret_cast<_simd_u64x1*>(&tmp)[28] = c1;
	reinterpret_cast<_simd_u64x1*>(&tmp)[29] = d1;
	reinterpret_cast<_simd_u64x1*>(&tmp)[30] = e1;
	reinterpret_cast<_simd_u64x1*>(&tmp)[31] = f1;
	reinterpret_cast<_simd_u64x1*>(&tmp)[32] = g1;
	reinterpret_cast<_simd_u64x1*>(&tmp)[33] = h1;
	reinterpret_cast<_simd_u64x1*>(&tmp)[34] = i1;
	reinterpret_cast<_simd_u64x1*>(&tmp)[35] = j1;
	reinterpret_cast<_simd_u64x1*>(&tmp)[36] = k1;
	reinterpret_cast<_simd_u64x1*>(&tmp)[37] = l1;
	reinterpret_cast<_simd_u64x1*>(&tmp)[38] = m1;
	reinterpret_cast<_simd_u64x1*>(&tmp)[39] = n1;
	reinterpret_cast<_simd_u64x1*>(&tmp)[40] = o1;
	reinterpret_cast<_simd_u64x1*>(&tmp)[41] = p1;
	reinterpret_cast<_simd_u64x1*>(&tmp)[42] = q1;
	reinterpret_cast<_simd_u64x1*>(&tmp)[43] = r1;
	reinterpret_cast<_simd_u64x1*>(&tmp)[44] = s1;
	reinterpret_cast<_simd_u64x1*>(&tmp)[45] = t1;
	reinterpret_cast<_simd_u64x1*>(&tmp)[46] = u1;
	reinterpret_cast<_simd_u64x1*>(&tmp)[47] = v1;
	reinterpret_cast<_simd_u64x1*>(&tmp)[48] = w1;
	reinterpret_cast<_simd_u64x1*>(&tmp)[49] = x1;
	reinterpret_cast<_simd_u64x1*>(&tmp)[50] = y1;
	reinterpret_cast<_simd_u64x1*>(&tmp)[51] = z1;
	reinterpret_cast<_simd_u64x1*>(&tmp)[52] = a2;
	reinterpret_cast<_simd_u64x1*>(&tmp)[53] = b2;
	reinterpret_cast<_simd_u64x1*>(&tmp)[54] = c2;
	reinterpret_cast<_simd_u64x1*>(&tmp)[55] = d2;
	reinterpret_cast<_simd_u64x1*>(&tmp)[56] = e2;
	reinterpret_cast<_simd_u64x1*>(&tmp)[57] = f2;
	reinterpret_cast<_simd_u64x1*>(&tmp)[58] = g2;
	reinterpret_cast<_simd_u64x1*>(&tmp)[59] = h2;
	reinterpret_cast<_simd_u64x1*>(&tmp)[60] = i2;
	reinterpret_cast<_simd_u64x1*>(&tmp)[61] = j2;
	reinterpret_cast<_simd_u64x1*>(&tmp)[62] = k2;
	reinterpret_cast<_simd_u64x1*>(&tmp)[63] = l2;
	return tmp;
}
#ifdef _simd_u64x64_set_
	#define _simd_u64x64_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_u64x64_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2)
	#define _simd_u64x64_set_enable() anvil::simd::IsInstructionSetSupported<_simd_u64x64_set_instruction_set>()
#elif defined(_simd_u64x32_set_)
	#define _simd_u64x64_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_u64x64_combine(\
		_simd_u64x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1),\
		_simd_u64x32_set_(g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2));
	#define _simd_u64x64_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_u64x64_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2)
	#define _simd_u64x64_set_enable() (_simd_u64x32_set_enable() && _simd_u64x64_combine_enable())
#else
	#define _simd_u64x64_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_u64x64_set_safe(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2)
	#define _simd_u64x64_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s32x2 ANVIL_SIMD_CALL _simd_s32x2_set_safe(_simd_s32x1 a0, _simd_s32x1 b0) {
	_simd_s32x2 tmp;
	reinterpret_cast<_simd_s32x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[1] = b0;
	return tmp;
}
#ifdef _simd_s32x2_set_
	#define _simd_s32x2_set(a0, b0) _simd_s32x2_set_(a0, b0)
	#define _simd_s32x2_set_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x2_set_instruction_set>()
#elif defined(_simd_s32x1_set_)
	#define _simd_s32x2_set_(a0, b0) _simd_s32x2_combine(\
		_simd_s32x1_set_(a0),\
		_simd_s32x1_set_(b0));
	#define _simd_s32x2_set(a0, b0) _simd_s32x2_set_(a0, b0)
	#define _simd_s32x2_set_enable() (_simd_s32x1_set_enable() && _simd_s32x2_combine_enable())
#else
	#define _simd_s32x2_set(a0, b0) _simd_s32x2_set_safe(a0, b0)
	#define _simd_s32x2_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s32x4 ANVIL_SIMD_CALL _simd_s32x4_set_safe(_simd_s32x1 a0, _simd_s32x1 b0, _simd_s32x1 c0, _simd_s32x1 d0) {
	_simd_s32x4 tmp;
	reinterpret_cast<_simd_s32x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[3] = d0;
	return tmp;
}
#ifdef _simd_s32x4_set_
	#define _simd_s32x4_set(a0, b0, c0, d0) _simd_s32x4_set_(a0, b0, c0, d0)
	#define _simd_s32x4_set_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x4_set_instruction_set>()
#elif defined(_simd_s32x2_set_)
	#define _simd_s32x4_set_(a0, b0, c0, d0) _simd_s32x4_combine(\
		_simd_s32x2_set_(a0, b0),\
		_simd_s32x2_set_(c0, d0));
	#define _simd_s32x4_set(a0, b0, c0, d0) _simd_s32x4_set_(a0, b0, c0, d0)
	#define _simd_s32x4_set_enable() (_simd_s32x2_set_enable() && _simd_s32x4_combine_enable())
#else
	#define _simd_s32x4_set(a0, b0, c0, d0) _simd_s32x4_set_safe(a0, b0, c0, d0)
	#define _simd_s32x4_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s32x8 ANVIL_SIMD_CALL _simd_s32x8_set_safe(_simd_s32x1 a0, _simd_s32x1 b0, _simd_s32x1 c0, _simd_s32x1 d0, _simd_s32x1 e0, _simd_s32x1 f0, _simd_s32x1 g0, _simd_s32x1 h0) {
	_simd_s32x8 tmp;
	reinterpret_cast<_simd_s32x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[7] = h0;
	return tmp;
}
#ifdef _simd_s32x8_set_
	#define _simd_s32x8_set(a0, b0, c0, d0, e0, f0, g0, h0) _simd_s32x8_set_(a0, b0, c0, d0, e0, f0, g0, h0)
	#define _simd_s32x8_set_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x8_set_instruction_set>()
#elif defined(_simd_s32x4_set_)
	#define _simd_s32x8_set_(a0, b0, c0, d0, e0, f0, g0, h0) _simd_s32x8_combine(\
		_simd_s32x4_set_(a0, b0, c0, d0),\
		_simd_s32x4_set_(e0, f0, g0, h0));
	#define _simd_s32x8_set(a0, b0, c0, d0, e0, f0, g0, h0) _simd_s32x8_set_(a0, b0, c0, d0, e0, f0, g0, h0)
	#define _simd_s32x8_set_enable() (_simd_s32x4_set_enable() && _simd_s32x8_combine_enable())
#else
	#define _simd_s32x8_set(a0, b0, c0, d0, e0, f0, g0, h0) _simd_s32x8_set_safe(a0, b0, c0, d0, e0, f0, g0, h0)
	#define _simd_s32x8_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s32x16 ANVIL_SIMD_CALL _simd_s32x16_set_safe(_simd_s32x1 a0, _simd_s32x1 b0, _simd_s32x1 c0, _simd_s32x1 d0, _simd_s32x1 e0, _simd_s32x1 f0, _simd_s32x1 g0, _simd_s32x1 h0, _simd_s32x1 i0, _simd_s32x1 j0, _simd_s32x1 k0, _simd_s32x1 l0, _simd_s32x1 m0, _simd_s32x1 n0, _simd_s32x1 o0, _simd_s32x1 p0) {
	_simd_s32x16 tmp;
	reinterpret_cast<_simd_s32x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[7] = h0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[8] = i0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[9] = j0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[10] = k0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[11] = l0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[12] = m0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[13] = n0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[14] = o0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[15] = p0;
	return tmp;
}
#ifdef _simd_s32x16_set_
	#define _simd_s32x16_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_s32x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0)
	#define _simd_s32x16_set_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x16_set_instruction_set>()
#elif defined(_simd_s32x8_set_)
	#define _simd_s32x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_s32x16_combine(\
		_simd_s32x8_set_(a0, b0, c0, d0, e0, f0, g0, h0),\
		_simd_s32x8_set_(i0, j0, k0, l0, m0, n0, o0, p0));
	#define _simd_s32x16_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_s32x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0)
	#define _simd_s32x16_set_enable() (_simd_s32x8_set_enable() && _simd_s32x16_combine_enable())
#else
	#define _simd_s32x16_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_s32x16_set_safe(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0)
	#define _simd_s32x16_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s32x32 ANVIL_SIMD_CALL _simd_s32x32_set_safe(_simd_s32x1 a0, _simd_s32x1 b0, _simd_s32x1 c0, _simd_s32x1 d0, _simd_s32x1 e0, _simd_s32x1 f0, _simd_s32x1 g0, _simd_s32x1 h0, _simd_s32x1 i0, _simd_s32x1 j0, _simd_s32x1 k0, _simd_s32x1 l0, _simd_s32x1 m0, _simd_s32x1 n0, _simd_s32x1 o0, _simd_s32x1 p0, _simd_s32x1 q0, _simd_s32x1 r0, _simd_s32x1 s0, _simd_s32x1 t0, _simd_s32x1 u0, _simd_s32x1 v0, _simd_s32x1 w0, _simd_s32x1 x0, _simd_s32x1 y0, _simd_s32x1 z0, _simd_s32x1 a1, _simd_s32x1 b1, _simd_s32x1 c1, _simd_s32x1 d1, _simd_s32x1 e1, _simd_s32x1 f1) {
	_simd_s32x32 tmp;
	reinterpret_cast<_simd_s32x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[7] = h0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[8] = i0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[9] = j0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[10] = k0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[11] = l0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[12] = m0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[13] = n0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[14] = o0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[15] = p0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[16] = q0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[17] = r0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[18] = s0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[19] = t0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[20] = u0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[21] = v0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[22] = w0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[23] = x0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[24] = y0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[25] = z0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[26] = a1;
	reinterpret_cast<_simd_s32x1*>(&tmp)[27] = b1;
	reinterpret_cast<_simd_s32x1*>(&tmp)[28] = c1;
	reinterpret_cast<_simd_s32x1*>(&tmp)[29] = d1;
	reinterpret_cast<_simd_s32x1*>(&tmp)[30] = e1;
	reinterpret_cast<_simd_s32x1*>(&tmp)[31] = f1;
	return tmp;
}
#ifdef _simd_s32x32_set_
	#define _simd_s32x32_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_s32x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1)
	#define _simd_s32x32_set_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x32_set_instruction_set>()
#elif defined(_simd_s32x16_set_)
	#define _simd_s32x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_s32x32_combine(\
		_simd_s32x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0),\
		_simd_s32x16_set_(q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1));
	#define _simd_s32x32_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_s32x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1)
	#define _simd_s32x32_set_enable() (_simd_s32x16_set_enable() && _simd_s32x32_combine_enable())
#else
	#define _simd_s32x32_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_s32x32_set_safe(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1)
	#define _simd_s32x32_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s32x64 ANVIL_SIMD_CALL _simd_s32x64_set_safe(_simd_s32x1 a0, _simd_s32x1 b0, _simd_s32x1 c0, _simd_s32x1 d0, _simd_s32x1 e0, _simd_s32x1 f0, _simd_s32x1 g0, _simd_s32x1 h0, _simd_s32x1 i0, _simd_s32x1 j0, _simd_s32x1 k0, _simd_s32x1 l0, _simd_s32x1 m0, _simd_s32x1 n0, _simd_s32x1 o0, _simd_s32x1 p0, _simd_s32x1 q0, _simd_s32x1 r0, _simd_s32x1 s0, _simd_s32x1 t0, _simd_s32x1 u0, _simd_s32x1 v0, _simd_s32x1 w0, _simd_s32x1 x0, _simd_s32x1 y0, _simd_s32x1 z0, _simd_s32x1 a1, _simd_s32x1 b1, _simd_s32x1 c1, _simd_s32x1 d1, _simd_s32x1 e1, _simd_s32x1 f1, _simd_s32x1 g1, _simd_s32x1 h1, _simd_s32x1 i1, _simd_s32x1 j1, _simd_s32x1 k1, _simd_s32x1 l1, _simd_s32x1 m1, _simd_s32x1 n1, _simd_s32x1 o1, _simd_s32x1 p1, _simd_s32x1 q1, _simd_s32x1 r1, _simd_s32x1 s1, _simd_s32x1 t1, _simd_s32x1 u1, _simd_s32x1 v1, _simd_s32x1 w1, _simd_s32x1 x1, _simd_s32x1 y1, _simd_s32x1 z1, _simd_s32x1 a2, _simd_s32x1 b2, _simd_s32x1 c2, _simd_s32x1 d2, _simd_s32x1 e2, _simd_s32x1 f2, _simd_s32x1 g2, _simd_s32x1 h2, _simd_s32x1 i2, _simd_s32x1 j2, _simd_s32x1 k2, _simd_s32x1 l2) {
	_simd_s32x64 tmp;
	reinterpret_cast<_simd_s32x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[7] = h0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[8] = i0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[9] = j0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[10] = k0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[11] = l0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[12] = m0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[13] = n0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[14] = o0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[15] = p0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[16] = q0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[17] = r0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[18] = s0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[19] = t0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[20] = u0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[21] = v0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[22] = w0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[23] = x0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[24] = y0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[25] = z0;
	reinterpret_cast<_simd_s32x1*>(&tmp)[26] = a1;
	reinterpret_cast<_simd_s32x1*>(&tmp)[27] = b1;
	reinterpret_cast<_simd_s32x1*>(&tmp)[28] = c1;
	reinterpret_cast<_simd_s32x1*>(&tmp)[29] = d1;
	reinterpret_cast<_simd_s32x1*>(&tmp)[30] = e1;
	reinterpret_cast<_simd_s32x1*>(&tmp)[31] = f1;
	reinterpret_cast<_simd_s32x1*>(&tmp)[32] = g1;
	reinterpret_cast<_simd_s32x1*>(&tmp)[33] = h1;
	reinterpret_cast<_simd_s32x1*>(&tmp)[34] = i1;
	reinterpret_cast<_simd_s32x1*>(&tmp)[35] = j1;
	reinterpret_cast<_simd_s32x1*>(&tmp)[36] = k1;
	reinterpret_cast<_simd_s32x1*>(&tmp)[37] = l1;
	reinterpret_cast<_simd_s32x1*>(&tmp)[38] = m1;
	reinterpret_cast<_simd_s32x1*>(&tmp)[39] = n1;
	reinterpret_cast<_simd_s32x1*>(&tmp)[40] = o1;
	reinterpret_cast<_simd_s32x1*>(&tmp)[41] = p1;
	reinterpret_cast<_simd_s32x1*>(&tmp)[42] = q1;
	reinterpret_cast<_simd_s32x1*>(&tmp)[43] = r1;
	reinterpret_cast<_simd_s32x1*>(&tmp)[44] = s1;
	reinterpret_cast<_simd_s32x1*>(&tmp)[45] = t1;
	reinterpret_cast<_simd_s32x1*>(&tmp)[46] = u1;
	reinterpret_cast<_simd_s32x1*>(&tmp)[47] = v1;
	reinterpret_cast<_simd_s32x1*>(&tmp)[48] = w1;
	reinterpret_cast<_simd_s32x1*>(&tmp)[49] = x1;
	reinterpret_cast<_simd_s32x1*>(&tmp)[50] = y1;
	reinterpret_cast<_simd_s32x1*>(&tmp)[51] = z1;
	reinterpret_cast<_simd_s32x1*>(&tmp)[52] = a2;
	reinterpret_cast<_simd_s32x1*>(&tmp)[53] = b2;
	reinterpret_cast<_simd_s32x1*>(&tmp)[54] = c2;
	reinterpret_cast<_simd_s32x1*>(&tmp)[55] = d2;
	reinterpret_cast<_simd_s32x1*>(&tmp)[56] = e2;
	reinterpret_cast<_simd_s32x1*>(&tmp)[57] = f2;
	reinterpret_cast<_simd_s32x1*>(&tmp)[58] = g2;
	reinterpret_cast<_simd_s32x1*>(&tmp)[59] = h2;
	reinterpret_cast<_simd_s32x1*>(&tmp)[60] = i2;
	reinterpret_cast<_simd_s32x1*>(&tmp)[61] = j2;
	reinterpret_cast<_simd_s32x1*>(&tmp)[62] = k2;
	reinterpret_cast<_simd_s32x1*>(&tmp)[63] = l2;
	return tmp;
}
#ifdef _simd_s32x64_set_
	#define _simd_s32x64_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_s32x64_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2)
	#define _simd_s32x64_set_enable() anvil::simd::IsInstructionSetSupported<_simd_s32x64_set_instruction_set>()
#elif defined(_simd_s32x32_set_)
	#define _simd_s32x64_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_s32x64_combine(\
		_simd_s32x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1),\
		_simd_s32x32_set_(g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2));
	#define _simd_s32x64_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_s32x64_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2)
	#define _simd_s32x64_set_enable() (_simd_s32x32_set_enable() && _simd_s32x64_combine_enable())
#else
	#define _simd_s32x64_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_s32x64_set_safe(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2)
	#define _simd_s32x64_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u32x2 ANVIL_SIMD_CALL _simd_u32x2_set_safe(_simd_u32x1 a0, _simd_u32x1 b0) {
	_simd_u32x2 tmp;
	reinterpret_cast<_simd_u32x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[1] = b0;
	return tmp;
}
#ifdef _simd_u32x2_set_
	#define _simd_u32x2_set(a0, b0) _simd_u32x2_set_(a0, b0)
	#define _simd_u32x2_set_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x2_set_instruction_set>()
#elif defined(_simd_u32x1_set_)
	#define _simd_u32x2_set_(a0, b0) _simd_u32x2_combine(\
		_simd_u32x1_set_(a0),\
		_simd_u32x1_set_(b0));
	#define _simd_u32x2_set(a0, b0) _simd_u32x2_set_(a0, b0)
	#define _simd_u32x2_set_enable() (_simd_u32x1_set_enable() && _simd_u32x2_combine_enable())
#else
	#define _simd_u32x2_set(a0, b0) _simd_u32x2_set_safe(a0, b0)
	#define _simd_u32x2_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u32x4 ANVIL_SIMD_CALL _simd_u32x4_set_safe(_simd_u32x1 a0, _simd_u32x1 b0, _simd_u32x1 c0, _simd_u32x1 d0) {
	_simd_u32x4 tmp;
	reinterpret_cast<_simd_u32x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[3] = d0;
	return tmp;
}
#ifdef _simd_u32x4_set_
	#define _simd_u32x4_set(a0, b0, c0, d0) _simd_u32x4_set_(a0, b0, c0, d0)
	#define _simd_u32x4_set_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x4_set_instruction_set>()
#elif defined(_simd_u32x2_set_)
	#define _simd_u32x4_set_(a0, b0, c0, d0) _simd_u32x4_combine(\
		_simd_u32x2_set_(a0, b0),\
		_simd_u32x2_set_(c0, d0));
	#define _simd_u32x4_set(a0, b0, c0, d0) _simd_u32x4_set_(a0, b0, c0, d0)
	#define _simd_u32x4_set_enable() (_simd_u32x2_set_enable() && _simd_u32x4_combine_enable())
#else
	#define _simd_u32x4_set(a0, b0, c0, d0) _simd_u32x4_set_safe(a0, b0, c0, d0)
	#define _simd_u32x4_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u32x8 ANVIL_SIMD_CALL _simd_u32x8_set_safe(_simd_u32x1 a0, _simd_u32x1 b0, _simd_u32x1 c0, _simd_u32x1 d0, _simd_u32x1 e0, _simd_u32x1 f0, _simd_u32x1 g0, _simd_u32x1 h0) {
	_simd_u32x8 tmp;
	reinterpret_cast<_simd_u32x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[7] = h0;
	return tmp;
}
#ifdef _simd_u32x8_set_
	#define _simd_u32x8_set(a0, b0, c0, d0, e0, f0, g0, h0) _simd_u32x8_set_(a0, b0, c0, d0, e0, f0, g0, h0)
	#define _simd_u32x8_set_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x8_set_instruction_set>()
#elif defined(_simd_u32x4_set_)
	#define _simd_u32x8_set_(a0, b0, c0, d0, e0, f0, g0, h0) _simd_u32x8_combine(\
		_simd_u32x4_set_(a0, b0, c0, d0),\
		_simd_u32x4_set_(e0, f0, g0, h0));
	#define _simd_u32x8_set(a0, b0, c0, d0, e0, f0, g0, h0) _simd_u32x8_set_(a0, b0, c0, d0, e0, f0, g0, h0)
	#define _simd_u32x8_set_enable() (_simd_u32x4_set_enable() && _simd_u32x8_combine_enable())
#else
	#define _simd_u32x8_set(a0, b0, c0, d0, e0, f0, g0, h0) _simd_u32x8_set_safe(a0, b0, c0, d0, e0, f0, g0, h0)
	#define _simd_u32x8_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u32x16 ANVIL_SIMD_CALL _simd_u32x16_set_safe(_simd_u32x1 a0, _simd_u32x1 b0, _simd_u32x1 c0, _simd_u32x1 d0, _simd_u32x1 e0, _simd_u32x1 f0, _simd_u32x1 g0, _simd_u32x1 h0, _simd_u32x1 i0, _simd_u32x1 j0, _simd_u32x1 k0, _simd_u32x1 l0, _simd_u32x1 m0, _simd_u32x1 n0, _simd_u32x1 o0, _simd_u32x1 p0) {
	_simd_u32x16 tmp;
	reinterpret_cast<_simd_u32x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[7] = h0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[8] = i0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[9] = j0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[10] = k0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[11] = l0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[12] = m0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[13] = n0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[14] = o0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[15] = p0;
	return tmp;
}
#ifdef _simd_u32x16_set_
	#define _simd_u32x16_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_u32x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0)
	#define _simd_u32x16_set_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x16_set_instruction_set>()
#elif defined(_simd_u32x8_set_)
	#define _simd_u32x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_u32x16_combine(\
		_simd_u32x8_set_(a0, b0, c0, d0, e0, f0, g0, h0),\
		_simd_u32x8_set_(i0, j0, k0, l0, m0, n0, o0, p0));
	#define _simd_u32x16_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_u32x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0)
	#define _simd_u32x16_set_enable() (_simd_u32x8_set_enable() && _simd_u32x16_combine_enable())
#else
	#define _simd_u32x16_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_u32x16_set_safe(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0)
	#define _simd_u32x16_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u32x32 ANVIL_SIMD_CALL _simd_u32x32_set_safe(_simd_u32x1 a0, _simd_u32x1 b0, _simd_u32x1 c0, _simd_u32x1 d0, _simd_u32x1 e0, _simd_u32x1 f0, _simd_u32x1 g0, _simd_u32x1 h0, _simd_u32x1 i0, _simd_u32x1 j0, _simd_u32x1 k0, _simd_u32x1 l0, _simd_u32x1 m0, _simd_u32x1 n0, _simd_u32x1 o0, _simd_u32x1 p0, _simd_u32x1 q0, _simd_u32x1 r0, _simd_u32x1 s0, _simd_u32x1 t0, _simd_u32x1 u0, _simd_u32x1 v0, _simd_u32x1 w0, _simd_u32x1 x0, _simd_u32x1 y0, _simd_u32x1 z0, _simd_u32x1 a1, _simd_u32x1 b1, _simd_u32x1 c1, _simd_u32x1 d1, _simd_u32x1 e1, _simd_u32x1 f1) {
	_simd_u32x32 tmp;
	reinterpret_cast<_simd_u32x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[7] = h0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[8] = i0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[9] = j0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[10] = k0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[11] = l0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[12] = m0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[13] = n0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[14] = o0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[15] = p0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[16] = q0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[17] = r0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[18] = s0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[19] = t0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[20] = u0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[21] = v0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[22] = w0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[23] = x0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[24] = y0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[25] = z0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[26] = a1;
	reinterpret_cast<_simd_u32x1*>(&tmp)[27] = b1;
	reinterpret_cast<_simd_u32x1*>(&tmp)[28] = c1;
	reinterpret_cast<_simd_u32x1*>(&tmp)[29] = d1;
	reinterpret_cast<_simd_u32x1*>(&tmp)[30] = e1;
	reinterpret_cast<_simd_u32x1*>(&tmp)[31] = f1;
	return tmp;
}
#ifdef _simd_u32x32_set_
	#define _simd_u32x32_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_u32x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1)
	#define _simd_u32x32_set_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x32_set_instruction_set>()
#elif defined(_simd_u32x16_set_)
	#define _simd_u32x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_u32x32_combine(\
		_simd_u32x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0),\
		_simd_u32x16_set_(q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1));
	#define _simd_u32x32_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_u32x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1)
	#define _simd_u32x32_set_enable() (_simd_u32x16_set_enable() && _simd_u32x32_combine_enable())
#else
	#define _simd_u32x32_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_u32x32_set_safe(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1)
	#define _simd_u32x32_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u32x64 ANVIL_SIMD_CALL _simd_u32x64_set_safe(_simd_u32x1 a0, _simd_u32x1 b0, _simd_u32x1 c0, _simd_u32x1 d0, _simd_u32x1 e0, _simd_u32x1 f0, _simd_u32x1 g0, _simd_u32x1 h0, _simd_u32x1 i0, _simd_u32x1 j0, _simd_u32x1 k0, _simd_u32x1 l0, _simd_u32x1 m0, _simd_u32x1 n0, _simd_u32x1 o0, _simd_u32x1 p0, _simd_u32x1 q0, _simd_u32x1 r0, _simd_u32x1 s0, _simd_u32x1 t0, _simd_u32x1 u0, _simd_u32x1 v0, _simd_u32x1 w0, _simd_u32x1 x0, _simd_u32x1 y0, _simd_u32x1 z0, _simd_u32x1 a1, _simd_u32x1 b1, _simd_u32x1 c1, _simd_u32x1 d1, _simd_u32x1 e1, _simd_u32x1 f1, _simd_u32x1 g1, _simd_u32x1 h1, _simd_u32x1 i1, _simd_u32x1 j1, _simd_u32x1 k1, _simd_u32x1 l1, _simd_u32x1 m1, _simd_u32x1 n1, _simd_u32x1 o1, _simd_u32x1 p1, _simd_u32x1 q1, _simd_u32x1 r1, _simd_u32x1 s1, _simd_u32x1 t1, _simd_u32x1 u1, _simd_u32x1 v1, _simd_u32x1 w1, _simd_u32x1 x1, _simd_u32x1 y1, _simd_u32x1 z1, _simd_u32x1 a2, _simd_u32x1 b2, _simd_u32x1 c2, _simd_u32x1 d2, _simd_u32x1 e2, _simd_u32x1 f2, _simd_u32x1 g2, _simd_u32x1 h2, _simd_u32x1 i2, _simd_u32x1 j2, _simd_u32x1 k2, _simd_u32x1 l2) {
	_simd_u32x64 tmp;
	reinterpret_cast<_simd_u32x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[7] = h0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[8] = i0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[9] = j0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[10] = k0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[11] = l0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[12] = m0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[13] = n0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[14] = o0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[15] = p0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[16] = q0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[17] = r0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[18] = s0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[19] = t0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[20] = u0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[21] = v0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[22] = w0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[23] = x0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[24] = y0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[25] = z0;
	reinterpret_cast<_simd_u32x1*>(&tmp)[26] = a1;
	reinterpret_cast<_simd_u32x1*>(&tmp)[27] = b1;
	reinterpret_cast<_simd_u32x1*>(&tmp)[28] = c1;
	reinterpret_cast<_simd_u32x1*>(&tmp)[29] = d1;
	reinterpret_cast<_simd_u32x1*>(&tmp)[30] = e1;
	reinterpret_cast<_simd_u32x1*>(&tmp)[31] = f1;
	reinterpret_cast<_simd_u32x1*>(&tmp)[32] = g1;
	reinterpret_cast<_simd_u32x1*>(&tmp)[33] = h1;
	reinterpret_cast<_simd_u32x1*>(&tmp)[34] = i1;
	reinterpret_cast<_simd_u32x1*>(&tmp)[35] = j1;
	reinterpret_cast<_simd_u32x1*>(&tmp)[36] = k1;
	reinterpret_cast<_simd_u32x1*>(&tmp)[37] = l1;
	reinterpret_cast<_simd_u32x1*>(&tmp)[38] = m1;
	reinterpret_cast<_simd_u32x1*>(&tmp)[39] = n1;
	reinterpret_cast<_simd_u32x1*>(&tmp)[40] = o1;
	reinterpret_cast<_simd_u32x1*>(&tmp)[41] = p1;
	reinterpret_cast<_simd_u32x1*>(&tmp)[42] = q1;
	reinterpret_cast<_simd_u32x1*>(&tmp)[43] = r1;
	reinterpret_cast<_simd_u32x1*>(&tmp)[44] = s1;
	reinterpret_cast<_simd_u32x1*>(&tmp)[45] = t1;
	reinterpret_cast<_simd_u32x1*>(&tmp)[46] = u1;
	reinterpret_cast<_simd_u32x1*>(&tmp)[47] = v1;
	reinterpret_cast<_simd_u32x1*>(&tmp)[48] = w1;
	reinterpret_cast<_simd_u32x1*>(&tmp)[49] = x1;
	reinterpret_cast<_simd_u32x1*>(&tmp)[50] = y1;
	reinterpret_cast<_simd_u32x1*>(&tmp)[51] = z1;
	reinterpret_cast<_simd_u32x1*>(&tmp)[52] = a2;
	reinterpret_cast<_simd_u32x1*>(&tmp)[53] = b2;
	reinterpret_cast<_simd_u32x1*>(&tmp)[54] = c2;
	reinterpret_cast<_simd_u32x1*>(&tmp)[55] = d2;
	reinterpret_cast<_simd_u32x1*>(&tmp)[56] = e2;
	reinterpret_cast<_simd_u32x1*>(&tmp)[57] = f2;
	reinterpret_cast<_simd_u32x1*>(&tmp)[58] = g2;
	reinterpret_cast<_simd_u32x1*>(&tmp)[59] = h2;
	reinterpret_cast<_simd_u32x1*>(&tmp)[60] = i2;
	reinterpret_cast<_simd_u32x1*>(&tmp)[61] = j2;
	reinterpret_cast<_simd_u32x1*>(&tmp)[62] = k2;
	reinterpret_cast<_simd_u32x1*>(&tmp)[63] = l2;
	return tmp;
}
#ifdef _simd_u32x64_set_
	#define _simd_u32x64_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_u32x64_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2)
	#define _simd_u32x64_set_enable() anvil::simd::IsInstructionSetSupported<_simd_u32x64_set_instruction_set>()
#elif defined(_simd_u32x32_set_)
	#define _simd_u32x64_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_u32x64_combine(\
		_simd_u32x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1),\
		_simd_u32x32_set_(g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2));
	#define _simd_u32x64_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_u32x64_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2)
	#define _simd_u32x64_set_enable() (_simd_u32x32_set_enable() && _simd_u32x64_combine_enable())
#else
	#define _simd_u32x64_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_u32x64_set_safe(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2)
	#define _simd_u32x64_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s16x2 ANVIL_SIMD_CALL _simd_s16x2_set_safe(_simd_s16x1 a0, _simd_s16x1 b0) {
	_simd_s16x2 tmp;
	reinterpret_cast<_simd_s16x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[1] = b0;
	return tmp;
}
#ifdef _simd_s16x2_set_
	#define _simd_s16x2_set(a0, b0) _simd_s16x2_set_(a0, b0)
	#define _simd_s16x2_set_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x2_set_instruction_set>()
#elif defined(_simd_s16x1_set_)
	#define _simd_s16x2_set_(a0, b0) _simd_s16x2_combine(\
		_simd_s16x1_set_(a0),\
		_simd_s16x1_set_(b0));
	#define _simd_s16x2_set(a0, b0) _simd_s16x2_set_(a0, b0)
	#define _simd_s16x2_set_enable() (_simd_s16x1_set_enable() && _simd_s16x2_combine_enable())
#else
	#define _simd_s16x2_set(a0, b0) _simd_s16x2_set_safe(a0, b0)
	#define _simd_s16x2_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s16x4 ANVIL_SIMD_CALL _simd_s16x4_set_safe(_simd_s16x1 a0, _simd_s16x1 b0, _simd_s16x1 c0, _simd_s16x1 d0) {
	_simd_s16x4 tmp;
	reinterpret_cast<_simd_s16x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[3] = d0;
	return tmp;
}
#ifdef _simd_s16x4_set_
	#define _simd_s16x4_set(a0, b0, c0, d0) _simd_s16x4_set_(a0, b0, c0, d0)
	#define _simd_s16x4_set_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x4_set_instruction_set>()
#elif defined(_simd_s16x2_set_)
	#define _simd_s16x4_set_(a0, b0, c0, d0) _simd_s16x4_combine(\
		_simd_s16x2_set_(a0, b0),\
		_simd_s16x2_set_(c0, d0));
	#define _simd_s16x4_set(a0, b0, c0, d0) _simd_s16x4_set_(a0, b0, c0, d0)
	#define _simd_s16x4_set_enable() (_simd_s16x2_set_enable() && _simd_s16x4_combine_enable())
#else
	#define _simd_s16x4_set(a0, b0, c0, d0) _simd_s16x4_set_safe(a0, b0, c0, d0)
	#define _simd_s16x4_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s16x8 ANVIL_SIMD_CALL _simd_s16x8_set_safe(_simd_s16x1 a0, _simd_s16x1 b0, _simd_s16x1 c0, _simd_s16x1 d0, _simd_s16x1 e0, _simd_s16x1 f0, _simd_s16x1 g0, _simd_s16x1 h0) {
	_simd_s16x8 tmp;
	reinterpret_cast<_simd_s16x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[7] = h0;
	return tmp;
}
#ifdef _simd_s16x8_set_
	#define _simd_s16x8_set(a0, b0, c0, d0, e0, f0, g0, h0) _simd_s16x8_set_(a0, b0, c0, d0, e0, f0, g0, h0)
	#define _simd_s16x8_set_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x8_set_instruction_set>()
#elif defined(_simd_s16x4_set_)
	#define _simd_s16x8_set_(a0, b0, c0, d0, e0, f0, g0, h0) _simd_s16x8_combine(\
		_simd_s16x4_set_(a0, b0, c0, d0),\
		_simd_s16x4_set_(e0, f0, g0, h0));
	#define _simd_s16x8_set(a0, b0, c0, d0, e0, f0, g0, h0) _simd_s16x8_set_(a0, b0, c0, d0, e0, f0, g0, h0)
	#define _simd_s16x8_set_enable() (_simd_s16x4_set_enable() && _simd_s16x8_combine_enable())
#else
	#define _simd_s16x8_set(a0, b0, c0, d0, e0, f0, g0, h0) _simd_s16x8_set_safe(a0, b0, c0, d0, e0, f0, g0, h0)
	#define _simd_s16x8_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s16x16 ANVIL_SIMD_CALL _simd_s16x16_set_safe(_simd_s16x1 a0, _simd_s16x1 b0, _simd_s16x1 c0, _simd_s16x1 d0, _simd_s16x1 e0, _simd_s16x1 f0, _simd_s16x1 g0, _simd_s16x1 h0, _simd_s16x1 i0, _simd_s16x1 j0, _simd_s16x1 k0, _simd_s16x1 l0, _simd_s16x1 m0, _simd_s16x1 n0, _simd_s16x1 o0, _simd_s16x1 p0) {
	_simd_s16x16 tmp;
	reinterpret_cast<_simd_s16x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[7] = h0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[8] = i0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[9] = j0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[10] = k0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[11] = l0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[12] = m0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[13] = n0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[14] = o0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[15] = p0;
	return tmp;
}
#ifdef _simd_s16x16_set_
	#define _simd_s16x16_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_s16x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0)
	#define _simd_s16x16_set_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x16_set_instruction_set>()
#elif defined(_simd_s16x8_set_)
	#define _simd_s16x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_s16x16_combine(\
		_simd_s16x8_set_(a0, b0, c0, d0, e0, f0, g0, h0),\
		_simd_s16x8_set_(i0, j0, k0, l0, m0, n0, o0, p0));
	#define _simd_s16x16_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_s16x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0)
	#define _simd_s16x16_set_enable() (_simd_s16x8_set_enable() && _simd_s16x16_combine_enable())
#else
	#define _simd_s16x16_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_s16x16_set_safe(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0)
	#define _simd_s16x16_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s16x32 ANVIL_SIMD_CALL _simd_s16x32_set_safe(_simd_s16x1 a0, _simd_s16x1 b0, _simd_s16x1 c0, _simd_s16x1 d0, _simd_s16x1 e0, _simd_s16x1 f0, _simd_s16x1 g0, _simd_s16x1 h0, _simd_s16x1 i0, _simd_s16x1 j0, _simd_s16x1 k0, _simd_s16x1 l0, _simd_s16x1 m0, _simd_s16x1 n0, _simd_s16x1 o0, _simd_s16x1 p0, _simd_s16x1 q0, _simd_s16x1 r0, _simd_s16x1 s0, _simd_s16x1 t0, _simd_s16x1 u0, _simd_s16x1 v0, _simd_s16x1 w0, _simd_s16x1 x0, _simd_s16x1 y0, _simd_s16x1 z0, _simd_s16x1 a1, _simd_s16x1 b1, _simd_s16x1 c1, _simd_s16x1 d1, _simd_s16x1 e1, _simd_s16x1 f1) {
	_simd_s16x32 tmp;
	reinterpret_cast<_simd_s16x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[7] = h0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[8] = i0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[9] = j0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[10] = k0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[11] = l0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[12] = m0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[13] = n0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[14] = o0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[15] = p0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[16] = q0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[17] = r0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[18] = s0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[19] = t0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[20] = u0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[21] = v0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[22] = w0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[23] = x0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[24] = y0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[25] = z0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[26] = a1;
	reinterpret_cast<_simd_s16x1*>(&tmp)[27] = b1;
	reinterpret_cast<_simd_s16x1*>(&tmp)[28] = c1;
	reinterpret_cast<_simd_s16x1*>(&tmp)[29] = d1;
	reinterpret_cast<_simd_s16x1*>(&tmp)[30] = e1;
	reinterpret_cast<_simd_s16x1*>(&tmp)[31] = f1;
	return tmp;
}
#ifdef _simd_s16x32_set_
	#define _simd_s16x32_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_s16x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1)
	#define _simd_s16x32_set_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x32_set_instruction_set>()
#elif defined(_simd_s16x16_set_)
	#define _simd_s16x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_s16x32_combine(\
		_simd_s16x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0),\
		_simd_s16x16_set_(q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1));
	#define _simd_s16x32_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_s16x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1)
	#define _simd_s16x32_set_enable() (_simd_s16x16_set_enable() && _simd_s16x32_combine_enable())
#else
	#define _simd_s16x32_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_s16x32_set_safe(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1)
	#define _simd_s16x32_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s16x64 ANVIL_SIMD_CALL _simd_s16x64_set_safe(_simd_s16x1 a0, _simd_s16x1 b0, _simd_s16x1 c0, _simd_s16x1 d0, _simd_s16x1 e0, _simd_s16x1 f0, _simd_s16x1 g0, _simd_s16x1 h0, _simd_s16x1 i0, _simd_s16x1 j0, _simd_s16x1 k0, _simd_s16x1 l0, _simd_s16x1 m0, _simd_s16x1 n0, _simd_s16x1 o0, _simd_s16x1 p0, _simd_s16x1 q0, _simd_s16x1 r0, _simd_s16x1 s0, _simd_s16x1 t0, _simd_s16x1 u0, _simd_s16x1 v0, _simd_s16x1 w0, _simd_s16x1 x0, _simd_s16x1 y0, _simd_s16x1 z0, _simd_s16x1 a1, _simd_s16x1 b1, _simd_s16x1 c1, _simd_s16x1 d1, _simd_s16x1 e1, _simd_s16x1 f1, _simd_s16x1 g1, _simd_s16x1 h1, _simd_s16x1 i1, _simd_s16x1 j1, _simd_s16x1 k1, _simd_s16x1 l1, _simd_s16x1 m1, _simd_s16x1 n1, _simd_s16x1 o1, _simd_s16x1 p1, _simd_s16x1 q1, _simd_s16x1 r1, _simd_s16x1 s1, _simd_s16x1 t1, _simd_s16x1 u1, _simd_s16x1 v1, _simd_s16x1 w1, _simd_s16x1 x1, _simd_s16x1 y1, _simd_s16x1 z1, _simd_s16x1 a2, _simd_s16x1 b2, _simd_s16x1 c2, _simd_s16x1 d2, _simd_s16x1 e2, _simd_s16x1 f2, _simd_s16x1 g2, _simd_s16x1 h2, _simd_s16x1 i2, _simd_s16x1 j2, _simd_s16x1 k2, _simd_s16x1 l2) {
	_simd_s16x64 tmp;
	reinterpret_cast<_simd_s16x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[7] = h0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[8] = i0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[9] = j0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[10] = k0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[11] = l0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[12] = m0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[13] = n0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[14] = o0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[15] = p0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[16] = q0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[17] = r0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[18] = s0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[19] = t0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[20] = u0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[21] = v0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[22] = w0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[23] = x0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[24] = y0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[25] = z0;
	reinterpret_cast<_simd_s16x1*>(&tmp)[26] = a1;
	reinterpret_cast<_simd_s16x1*>(&tmp)[27] = b1;
	reinterpret_cast<_simd_s16x1*>(&tmp)[28] = c1;
	reinterpret_cast<_simd_s16x1*>(&tmp)[29] = d1;
	reinterpret_cast<_simd_s16x1*>(&tmp)[30] = e1;
	reinterpret_cast<_simd_s16x1*>(&tmp)[31] = f1;
	reinterpret_cast<_simd_s16x1*>(&tmp)[32] = g1;
	reinterpret_cast<_simd_s16x1*>(&tmp)[33] = h1;
	reinterpret_cast<_simd_s16x1*>(&tmp)[34] = i1;
	reinterpret_cast<_simd_s16x1*>(&tmp)[35] = j1;
	reinterpret_cast<_simd_s16x1*>(&tmp)[36] = k1;
	reinterpret_cast<_simd_s16x1*>(&tmp)[37] = l1;
	reinterpret_cast<_simd_s16x1*>(&tmp)[38] = m1;
	reinterpret_cast<_simd_s16x1*>(&tmp)[39] = n1;
	reinterpret_cast<_simd_s16x1*>(&tmp)[40] = o1;
	reinterpret_cast<_simd_s16x1*>(&tmp)[41] = p1;
	reinterpret_cast<_simd_s16x1*>(&tmp)[42] = q1;
	reinterpret_cast<_simd_s16x1*>(&tmp)[43] = r1;
	reinterpret_cast<_simd_s16x1*>(&tmp)[44] = s1;
	reinterpret_cast<_simd_s16x1*>(&tmp)[45] = t1;
	reinterpret_cast<_simd_s16x1*>(&tmp)[46] = u1;
	reinterpret_cast<_simd_s16x1*>(&tmp)[47] = v1;
	reinterpret_cast<_simd_s16x1*>(&tmp)[48] = w1;
	reinterpret_cast<_simd_s16x1*>(&tmp)[49] = x1;
	reinterpret_cast<_simd_s16x1*>(&tmp)[50] = y1;
	reinterpret_cast<_simd_s16x1*>(&tmp)[51] = z1;
	reinterpret_cast<_simd_s16x1*>(&tmp)[52] = a2;
	reinterpret_cast<_simd_s16x1*>(&tmp)[53] = b2;
	reinterpret_cast<_simd_s16x1*>(&tmp)[54] = c2;
	reinterpret_cast<_simd_s16x1*>(&tmp)[55] = d2;
	reinterpret_cast<_simd_s16x1*>(&tmp)[56] = e2;
	reinterpret_cast<_simd_s16x1*>(&tmp)[57] = f2;
	reinterpret_cast<_simd_s16x1*>(&tmp)[58] = g2;
	reinterpret_cast<_simd_s16x1*>(&tmp)[59] = h2;
	reinterpret_cast<_simd_s16x1*>(&tmp)[60] = i2;
	reinterpret_cast<_simd_s16x1*>(&tmp)[61] = j2;
	reinterpret_cast<_simd_s16x1*>(&tmp)[62] = k2;
	reinterpret_cast<_simd_s16x1*>(&tmp)[63] = l2;
	return tmp;
}
#ifdef _simd_s16x64_set_
	#define _simd_s16x64_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_s16x64_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2)
	#define _simd_s16x64_set_enable() anvil::simd::IsInstructionSetSupported<_simd_s16x64_set_instruction_set>()
#elif defined(_simd_s16x32_set_)
	#define _simd_s16x64_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_s16x64_combine(\
		_simd_s16x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1),\
		_simd_s16x32_set_(g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2));
	#define _simd_s16x64_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_s16x64_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2)
	#define _simd_s16x64_set_enable() (_simd_s16x32_set_enable() && _simd_s16x64_combine_enable())
#else
	#define _simd_s16x64_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_s16x64_set_safe(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2)
	#define _simd_s16x64_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u16x2 ANVIL_SIMD_CALL _simd_u16x2_set_safe(_simd_u16x1 a0, _simd_u16x1 b0) {
	_simd_u16x2 tmp;
	reinterpret_cast<_simd_u16x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[1] = b0;
	return tmp;
}
#ifdef _simd_u16x2_set_
	#define _simd_u16x2_set(a0, b0) _simd_u16x2_set_(a0, b0)
	#define _simd_u16x2_set_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x2_set_instruction_set>()
#elif defined(_simd_u16x1_set_)
	#define _simd_u16x2_set_(a0, b0) _simd_u16x2_combine(\
		_simd_u16x1_set_(a0),\
		_simd_u16x1_set_(b0));
	#define _simd_u16x2_set(a0, b0) _simd_u16x2_set_(a0, b0)
	#define _simd_u16x2_set_enable() (_simd_u16x1_set_enable() && _simd_u16x2_combine_enable())
#else
	#define _simd_u16x2_set(a0, b0) _simd_u16x2_set_safe(a0, b0)
	#define _simd_u16x2_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u16x4 ANVIL_SIMD_CALL _simd_u16x4_set_safe(_simd_u16x1 a0, _simd_u16x1 b0, _simd_u16x1 c0, _simd_u16x1 d0) {
	_simd_u16x4 tmp;
	reinterpret_cast<_simd_u16x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[3] = d0;
	return tmp;
}
#ifdef _simd_u16x4_set_
	#define _simd_u16x4_set(a0, b0, c0, d0) _simd_u16x4_set_(a0, b0, c0, d0)
	#define _simd_u16x4_set_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x4_set_instruction_set>()
#elif defined(_simd_u16x2_set_)
	#define _simd_u16x4_set_(a0, b0, c0, d0) _simd_u16x4_combine(\
		_simd_u16x2_set_(a0, b0),\
		_simd_u16x2_set_(c0, d0));
	#define _simd_u16x4_set(a0, b0, c0, d0) _simd_u16x4_set_(a0, b0, c0, d0)
	#define _simd_u16x4_set_enable() (_simd_u16x2_set_enable() && _simd_u16x4_combine_enable())
#else
	#define _simd_u16x4_set(a0, b0, c0, d0) _simd_u16x4_set_safe(a0, b0, c0, d0)
	#define _simd_u16x4_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u16x8 ANVIL_SIMD_CALL _simd_u16x8_set_safe(_simd_u16x1 a0, _simd_u16x1 b0, _simd_u16x1 c0, _simd_u16x1 d0, _simd_u16x1 e0, _simd_u16x1 f0, _simd_u16x1 g0, _simd_u16x1 h0) {
	_simd_u16x8 tmp;
	reinterpret_cast<_simd_u16x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[7] = h0;
	return tmp;
}
#ifdef _simd_u16x8_set_
	#define _simd_u16x8_set(a0, b0, c0, d0, e0, f0, g0, h0) _simd_u16x8_set_(a0, b0, c0, d0, e0, f0, g0, h0)
	#define _simd_u16x8_set_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x8_set_instruction_set>()
#elif defined(_simd_u16x4_set_)
	#define _simd_u16x8_set_(a0, b0, c0, d0, e0, f0, g0, h0) _simd_u16x8_combine(\
		_simd_u16x4_set_(a0, b0, c0, d0),\
		_simd_u16x4_set_(e0, f0, g0, h0));
	#define _simd_u16x8_set(a0, b0, c0, d0, e0, f0, g0, h0) _simd_u16x8_set_(a0, b0, c0, d0, e0, f0, g0, h0)
	#define _simd_u16x8_set_enable() (_simd_u16x4_set_enable() && _simd_u16x8_combine_enable())
#else
	#define _simd_u16x8_set(a0, b0, c0, d0, e0, f0, g0, h0) _simd_u16x8_set_safe(a0, b0, c0, d0, e0, f0, g0, h0)
	#define _simd_u16x8_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u16x16 ANVIL_SIMD_CALL _simd_u16x16_set_safe(_simd_u16x1 a0, _simd_u16x1 b0, _simd_u16x1 c0, _simd_u16x1 d0, _simd_u16x1 e0, _simd_u16x1 f0, _simd_u16x1 g0, _simd_u16x1 h0, _simd_u16x1 i0, _simd_u16x1 j0, _simd_u16x1 k0, _simd_u16x1 l0, _simd_u16x1 m0, _simd_u16x1 n0, _simd_u16x1 o0, _simd_u16x1 p0) {
	_simd_u16x16 tmp;
	reinterpret_cast<_simd_u16x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[7] = h0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[8] = i0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[9] = j0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[10] = k0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[11] = l0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[12] = m0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[13] = n0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[14] = o0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[15] = p0;
	return tmp;
}
#ifdef _simd_u16x16_set_
	#define _simd_u16x16_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_u16x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0)
	#define _simd_u16x16_set_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x16_set_instruction_set>()
#elif defined(_simd_u16x8_set_)
	#define _simd_u16x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_u16x16_combine(\
		_simd_u16x8_set_(a0, b0, c0, d0, e0, f0, g0, h0),\
		_simd_u16x8_set_(i0, j0, k0, l0, m0, n0, o0, p0));
	#define _simd_u16x16_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_u16x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0)
	#define _simd_u16x16_set_enable() (_simd_u16x8_set_enable() && _simd_u16x16_combine_enable())
#else
	#define _simd_u16x16_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_u16x16_set_safe(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0)
	#define _simd_u16x16_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u16x32 ANVIL_SIMD_CALL _simd_u16x32_set_safe(_simd_u16x1 a0, _simd_u16x1 b0, _simd_u16x1 c0, _simd_u16x1 d0, _simd_u16x1 e0, _simd_u16x1 f0, _simd_u16x1 g0, _simd_u16x1 h0, _simd_u16x1 i0, _simd_u16x1 j0, _simd_u16x1 k0, _simd_u16x1 l0, _simd_u16x1 m0, _simd_u16x1 n0, _simd_u16x1 o0, _simd_u16x1 p0, _simd_u16x1 q0, _simd_u16x1 r0, _simd_u16x1 s0, _simd_u16x1 t0, _simd_u16x1 u0, _simd_u16x1 v0, _simd_u16x1 w0, _simd_u16x1 x0, _simd_u16x1 y0, _simd_u16x1 z0, _simd_u16x1 a1, _simd_u16x1 b1, _simd_u16x1 c1, _simd_u16x1 d1, _simd_u16x1 e1, _simd_u16x1 f1) {
	_simd_u16x32 tmp;
	reinterpret_cast<_simd_u16x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[7] = h0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[8] = i0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[9] = j0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[10] = k0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[11] = l0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[12] = m0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[13] = n0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[14] = o0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[15] = p0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[16] = q0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[17] = r0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[18] = s0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[19] = t0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[20] = u0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[21] = v0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[22] = w0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[23] = x0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[24] = y0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[25] = z0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[26] = a1;
	reinterpret_cast<_simd_u16x1*>(&tmp)[27] = b1;
	reinterpret_cast<_simd_u16x1*>(&tmp)[28] = c1;
	reinterpret_cast<_simd_u16x1*>(&tmp)[29] = d1;
	reinterpret_cast<_simd_u16x1*>(&tmp)[30] = e1;
	reinterpret_cast<_simd_u16x1*>(&tmp)[31] = f1;
	return tmp;
}
#ifdef _simd_u16x32_set_
	#define _simd_u16x32_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_u16x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1)
	#define _simd_u16x32_set_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x32_set_instruction_set>()
#elif defined(_simd_u16x16_set_)
	#define _simd_u16x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_u16x32_combine(\
		_simd_u16x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0),\
		_simd_u16x16_set_(q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1));
	#define _simd_u16x32_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_u16x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1)
	#define _simd_u16x32_set_enable() (_simd_u16x16_set_enable() && _simd_u16x32_combine_enable())
#else
	#define _simd_u16x32_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_u16x32_set_safe(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1)
	#define _simd_u16x32_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u16x64 ANVIL_SIMD_CALL _simd_u16x64_set_safe(_simd_u16x1 a0, _simd_u16x1 b0, _simd_u16x1 c0, _simd_u16x1 d0, _simd_u16x1 e0, _simd_u16x1 f0, _simd_u16x1 g0, _simd_u16x1 h0, _simd_u16x1 i0, _simd_u16x1 j0, _simd_u16x1 k0, _simd_u16x1 l0, _simd_u16x1 m0, _simd_u16x1 n0, _simd_u16x1 o0, _simd_u16x1 p0, _simd_u16x1 q0, _simd_u16x1 r0, _simd_u16x1 s0, _simd_u16x1 t0, _simd_u16x1 u0, _simd_u16x1 v0, _simd_u16x1 w0, _simd_u16x1 x0, _simd_u16x1 y0, _simd_u16x1 z0, _simd_u16x1 a1, _simd_u16x1 b1, _simd_u16x1 c1, _simd_u16x1 d1, _simd_u16x1 e1, _simd_u16x1 f1, _simd_u16x1 g1, _simd_u16x1 h1, _simd_u16x1 i1, _simd_u16x1 j1, _simd_u16x1 k1, _simd_u16x1 l1, _simd_u16x1 m1, _simd_u16x1 n1, _simd_u16x1 o1, _simd_u16x1 p1, _simd_u16x1 q1, _simd_u16x1 r1, _simd_u16x1 s1, _simd_u16x1 t1, _simd_u16x1 u1, _simd_u16x1 v1, _simd_u16x1 w1, _simd_u16x1 x1, _simd_u16x1 y1, _simd_u16x1 z1, _simd_u16x1 a2, _simd_u16x1 b2, _simd_u16x1 c2, _simd_u16x1 d2, _simd_u16x1 e2, _simd_u16x1 f2, _simd_u16x1 g2, _simd_u16x1 h2, _simd_u16x1 i2, _simd_u16x1 j2, _simd_u16x1 k2, _simd_u16x1 l2) {
	_simd_u16x64 tmp;
	reinterpret_cast<_simd_u16x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[7] = h0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[8] = i0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[9] = j0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[10] = k0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[11] = l0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[12] = m0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[13] = n0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[14] = o0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[15] = p0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[16] = q0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[17] = r0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[18] = s0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[19] = t0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[20] = u0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[21] = v0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[22] = w0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[23] = x0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[24] = y0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[25] = z0;
	reinterpret_cast<_simd_u16x1*>(&tmp)[26] = a1;
	reinterpret_cast<_simd_u16x1*>(&tmp)[27] = b1;
	reinterpret_cast<_simd_u16x1*>(&tmp)[28] = c1;
	reinterpret_cast<_simd_u16x1*>(&tmp)[29] = d1;
	reinterpret_cast<_simd_u16x1*>(&tmp)[30] = e1;
	reinterpret_cast<_simd_u16x1*>(&tmp)[31] = f1;
	reinterpret_cast<_simd_u16x1*>(&tmp)[32] = g1;
	reinterpret_cast<_simd_u16x1*>(&tmp)[33] = h1;
	reinterpret_cast<_simd_u16x1*>(&tmp)[34] = i1;
	reinterpret_cast<_simd_u16x1*>(&tmp)[35] = j1;
	reinterpret_cast<_simd_u16x1*>(&tmp)[36] = k1;
	reinterpret_cast<_simd_u16x1*>(&tmp)[37] = l1;
	reinterpret_cast<_simd_u16x1*>(&tmp)[38] = m1;
	reinterpret_cast<_simd_u16x1*>(&tmp)[39] = n1;
	reinterpret_cast<_simd_u16x1*>(&tmp)[40] = o1;
	reinterpret_cast<_simd_u16x1*>(&tmp)[41] = p1;
	reinterpret_cast<_simd_u16x1*>(&tmp)[42] = q1;
	reinterpret_cast<_simd_u16x1*>(&tmp)[43] = r1;
	reinterpret_cast<_simd_u16x1*>(&tmp)[44] = s1;
	reinterpret_cast<_simd_u16x1*>(&tmp)[45] = t1;
	reinterpret_cast<_simd_u16x1*>(&tmp)[46] = u1;
	reinterpret_cast<_simd_u16x1*>(&tmp)[47] = v1;
	reinterpret_cast<_simd_u16x1*>(&tmp)[48] = w1;
	reinterpret_cast<_simd_u16x1*>(&tmp)[49] = x1;
	reinterpret_cast<_simd_u16x1*>(&tmp)[50] = y1;
	reinterpret_cast<_simd_u16x1*>(&tmp)[51] = z1;
	reinterpret_cast<_simd_u16x1*>(&tmp)[52] = a2;
	reinterpret_cast<_simd_u16x1*>(&tmp)[53] = b2;
	reinterpret_cast<_simd_u16x1*>(&tmp)[54] = c2;
	reinterpret_cast<_simd_u16x1*>(&tmp)[55] = d2;
	reinterpret_cast<_simd_u16x1*>(&tmp)[56] = e2;
	reinterpret_cast<_simd_u16x1*>(&tmp)[57] = f2;
	reinterpret_cast<_simd_u16x1*>(&tmp)[58] = g2;
	reinterpret_cast<_simd_u16x1*>(&tmp)[59] = h2;
	reinterpret_cast<_simd_u16x1*>(&tmp)[60] = i2;
	reinterpret_cast<_simd_u16x1*>(&tmp)[61] = j2;
	reinterpret_cast<_simd_u16x1*>(&tmp)[62] = k2;
	reinterpret_cast<_simd_u16x1*>(&tmp)[63] = l2;
	return tmp;
}
#ifdef _simd_u16x64_set_
	#define _simd_u16x64_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_u16x64_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2)
	#define _simd_u16x64_set_enable() anvil::simd::IsInstructionSetSupported<_simd_u16x64_set_instruction_set>()
#elif defined(_simd_u16x32_set_)
	#define _simd_u16x64_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_u16x64_combine(\
		_simd_u16x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1),\
		_simd_u16x32_set_(g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2));
	#define _simd_u16x64_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_u16x64_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2)
	#define _simd_u16x64_set_enable() (_simd_u16x32_set_enable() && _simd_u16x64_combine_enable())
#else
	#define _simd_u16x64_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_u16x64_set_safe(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2)
	#define _simd_u16x64_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s8x2 ANVIL_SIMD_CALL _simd_s8x2_set_safe(_simd_s8x1 a0, _simd_s8x1 b0) {
	_simd_s8x2 tmp;
	reinterpret_cast<_simd_s8x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[1] = b0;
	return tmp;
}
#ifdef _simd_s8x2_set_
	#define _simd_s8x2_set(a0, b0) _simd_s8x2_set_(a0, b0)
	#define _simd_s8x2_set_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x2_set_instruction_set>()
#elif defined(_simd_s8x1_set_)
	#define _simd_s8x2_set_(a0, b0) _simd_s8x2_combine(\
		_simd_s8x1_set_(a0),\
		_simd_s8x1_set_(b0));
	#define _simd_s8x2_set(a0, b0) _simd_s8x2_set_(a0, b0)
	#define _simd_s8x2_set_enable() (_simd_s8x1_set_enable() && _simd_s8x2_combine_enable())
#else
	#define _simd_s8x2_set(a0, b0) _simd_s8x2_set_safe(a0, b0)
	#define _simd_s8x2_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s8x4 ANVIL_SIMD_CALL _simd_s8x4_set_safe(_simd_s8x1 a0, _simd_s8x1 b0, _simd_s8x1 c0, _simd_s8x1 d0) {
	_simd_s8x4 tmp;
	reinterpret_cast<_simd_s8x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[3] = d0;
	return tmp;
}
#ifdef _simd_s8x4_set_
	#define _simd_s8x4_set(a0, b0, c0, d0) _simd_s8x4_set_(a0, b0, c0, d0)
	#define _simd_s8x4_set_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x4_set_instruction_set>()
#elif defined(_simd_s8x2_set_)
	#define _simd_s8x4_set_(a0, b0, c0, d0) _simd_s8x4_combine(\
		_simd_s8x2_set_(a0, b0),\
		_simd_s8x2_set_(c0, d0));
	#define _simd_s8x4_set(a0, b0, c0, d0) _simd_s8x4_set_(a0, b0, c0, d0)
	#define _simd_s8x4_set_enable() (_simd_s8x2_set_enable() && _simd_s8x4_combine_enable())
#else
	#define _simd_s8x4_set(a0, b0, c0, d0) _simd_s8x4_set_safe(a0, b0, c0, d0)
	#define _simd_s8x4_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s8x8 ANVIL_SIMD_CALL _simd_s8x8_set_safe(_simd_s8x1 a0, _simd_s8x1 b0, _simd_s8x1 c0, _simd_s8x1 d0, _simd_s8x1 e0, _simd_s8x1 f0, _simd_s8x1 g0, _simd_s8x1 h0) {
	_simd_s8x8 tmp;
	reinterpret_cast<_simd_s8x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[7] = h0;
	return tmp;
}
#ifdef _simd_s8x8_set_
	#define _simd_s8x8_set(a0, b0, c0, d0, e0, f0, g0, h0) _simd_s8x8_set_(a0, b0, c0, d0, e0, f0, g0, h0)
	#define _simd_s8x8_set_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x8_set_instruction_set>()
#elif defined(_simd_s8x4_set_)
	#define _simd_s8x8_set_(a0, b0, c0, d0, e0, f0, g0, h0) _simd_s8x8_combine(\
		_simd_s8x4_set_(a0, b0, c0, d0),\
		_simd_s8x4_set_(e0, f0, g0, h0));
	#define _simd_s8x8_set(a0, b0, c0, d0, e0, f0, g0, h0) _simd_s8x8_set_(a0, b0, c0, d0, e0, f0, g0, h0)
	#define _simd_s8x8_set_enable() (_simd_s8x4_set_enable() && _simd_s8x8_combine_enable())
#else
	#define _simd_s8x8_set(a0, b0, c0, d0, e0, f0, g0, h0) _simd_s8x8_set_safe(a0, b0, c0, d0, e0, f0, g0, h0)
	#define _simd_s8x8_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s8x16 ANVIL_SIMD_CALL _simd_s8x16_set_safe(_simd_s8x1 a0, _simd_s8x1 b0, _simd_s8x1 c0, _simd_s8x1 d0, _simd_s8x1 e0, _simd_s8x1 f0, _simd_s8x1 g0, _simd_s8x1 h0, _simd_s8x1 i0, _simd_s8x1 j0, _simd_s8x1 k0, _simd_s8x1 l0, _simd_s8x1 m0, _simd_s8x1 n0, _simd_s8x1 o0, _simd_s8x1 p0) {
	_simd_s8x16 tmp;
	reinterpret_cast<_simd_s8x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[7] = h0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[8] = i0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[9] = j0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[10] = k0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[11] = l0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[12] = m0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[13] = n0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[14] = o0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[15] = p0;
	return tmp;
}
#ifdef _simd_s8x16_set_
	#define _simd_s8x16_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_s8x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0)
	#define _simd_s8x16_set_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x16_set_instruction_set>()
#elif defined(_simd_s8x8_set_)
	#define _simd_s8x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_s8x16_combine(\
		_simd_s8x8_set_(a0, b0, c0, d0, e0, f0, g0, h0),\
		_simd_s8x8_set_(i0, j0, k0, l0, m0, n0, o0, p0));
	#define _simd_s8x16_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_s8x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0)
	#define _simd_s8x16_set_enable() (_simd_s8x8_set_enable() && _simd_s8x16_combine_enable())
#else
	#define _simd_s8x16_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_s8x16_set_safe(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0)
	#define _simd_s8x16_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s8x32 ANVIL_SIMD_CALL _simd_s8x32_set_safe(_simd_s8x1 a0, _simd_s8x1 b0, _simd_s8x1 c0, _simd_s8x1 d0, _simd_s8x1 e0, _simd_s8x1 f0, _simd_s8x1 g0, _simd_s8x1 h0, _simd_s8x1 i0, _simd_s8x1 j0, _simd_s8x1 k0, _simd_s8x1 l0, _simd_s8x1 m0, _simd_s8x1 n0, _simd_s8x1 o0, _simd_s8x1 p0, _simd_s8x1 q0, _simd_s8x1 r0, _simd_s8x1 s0, _simd_s8x1 t0, _simd_s8x1 u0, _simd_s8x1 v0, _simd_s8x1 w0, _simd_s8x1 x0, _simd_s8x1 y0, _simd_s8x1 z0, _simd_s8x1 a1, _simd_s8x1 b1, _simd_s8x1 c1, _simd_s8x1 d1, _simd_s8x1 e1, _simd_s8x1 f1) {
	_simd_s8x32 tmp;
	reinterpret_cast<_simd_s8x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[7] = h0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[8] = i0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[9] = j0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[10] = k0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[11] = l0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[12] = m0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[13] = n0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[14] = o0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[15] = p0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[16] = q0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[17] = r0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[18] = s0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[19] = t0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[20] = u0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[21] = v0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[22] = w0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[23] = x0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[24] = y0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[25] = z0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[26] = a1;
	reinterpret_cast<_simd_s8x1*>(&tmp)[27] = b1;
	reinterpret_cast<_simd_s8x1*>(&tmp)[28] = c1;
	reinterpret_cast<_simd_s8x1*>(&tmp)[29] = d1;
	reinterpret_cast<_simd_s8x1*>(&tmp)[30] = e1;
	reinterpret_cast<_simd_s8x1*>(&tmp)[31] = f1;
	return tmp;
}
#ifdef _simd_s8x32_set_
	#define _simd_s8x32_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_s8x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1)
	#define _simd_s8x32_set_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x32_set_instruction_set>()
#elif defined(_simd_s8x16_set_)
	#define _simd_s8x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_s8x32_combine(\
		_simd_s8x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0),\
		_simd_s8x16_set_(q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1));
	#define _simd_s8x32_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_s8x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1)
	#define _simd_s8x32_set_enable() (_simd_s8x16_set_enable() && _simd_s8x32_combine_enable())
#else
	#define _simd_s8x32_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_s8x32_set_safe(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1)
	#define _simd_s8x32_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_s8x64 ANVIL_SIMD_CALL _simd_s8x64_set_safe(_simd_s8x1 a0, _simd_s8x1 b0, _simd_s8x1 c0, _simd_s8x1 d0, _simd_s8x1 e0, _simd_s8x1 f0, _simd_s8x1 g0, _simd_s8x1 h0, _simd_s8x1 i0, _simd_s8x1 j0, _simd_s8x1 k0, _simd_s8x1 l0, _simd_s8x1 m0, _simd_s8x1 n0, _simd_s8x1 o0, _simd_s8x1 p0, _simd_s8x1 q0, _simd_s8x1 r0, _simd_s8x1 s0, _simd_s8x1 t0, _simd_s8x1 u0, _simd_s8x1 v0, _simd_s8x1 w0, _simd_s8x1 x0, _simd_s8x1 y0, _simd_s8x1 z0, _simd_s8x1 a1, _simd_s8x1 b1, _simd_s8x1 c1, _simd_s8x1 d1, _simd_s8x1 e1, _simd_s8x1 f1, _simd_s8x1 g1, _simd_s8x1 h1, _simd_s8x1 i1, _simd_s8x1 j1, _simd_s8x1 k1, _simd_s8x1 l1, _simd_s8x1 m1, _simd_s8x1 n1, _simd_s8x1 o1, _simd_s8x1 p1, _simd_s8x1 q1, _simd_s8x1 r1, _simd_s8x1 s1, _simd_s8x1 t1, _simd_s8x1 u1, _simd_s8x1 v1, _simd_s8x1 w1, _simd_s8x1 x1, _simd_s8x1 y1, _simd_s8x1 z1, _simd_s8x1 a2, _simd_s8x1 b2, _simd_s8x1 c2, _simd_s8x1 d2, _simd_s8x1 e2, _simd_s8x1 f2, _simd_s8x1 g2, _simd_s8x1 h2, _simd_s8x1 i2, _simd_s8x1 j2, _simd_s8x1 k2, _simd_s8x1 l2) {
	_simd_s8x64 tmp;
	reinterpret_cast<_simd_s8x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[7] = h0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[8] = i0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[9] = j0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[10] = k0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[11] = l0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[12] = m0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[13] = n0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[14] = o0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[15] = p0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[16] = q0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[17] = r0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[18] = s0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[19] = t0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[20] = u0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[21] = v0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[22] = w0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[23] = x0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[24] = y0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[25] = z0;
	reinterpret_cast<_simd_s8x1*>(&tmp)[26] = a1;
	reinterpret_cast<_simd_s8x1*>(&tmp)[27] = b1;
	reinterpret_cast<_simd_s8x1*>(&tmp)[28] = c1;
	reinterpret_cast<_simd_s8x1*>(&tmp)[29] = d1;
	reinterpret_cast<_simd_s8x1*>(&tmp)[30] = e1;
	reinterpret_cast<_simd_s8x1*>(&tmp)[31] = f1;
	reinterpret_cast<_simd_s8x1*>(&tmp)[32] = g1;
	reinterpret_cast<_simd_s8x1*>(&tmp)[33] = h1;
	reinterpret_cast<_simd_s8x1*>(&tmp)[34] = i1;
	reinterpret_cast<_simd_s8x1*>(&tmp)[35] = j1;
	reinterpret_cast<_simd_s8x1*>(&tmp)[36] = k1;
	reinterpret_cast<_simd_s8x1*>(&tmp)[37] = l1;
	reinterpret_cast<_simd_s8x1*>(&tmp)[38] = m1;
	reinterpret_cast<_simd_s8x1*>(&tmp)[39] = n1;
	reinterpret_cast<_simd_s8x1*>(&tmp)[40] = o1;
	reinterpret_cast<_simd_s8x1*>(&tmp)[41] = p1;
	reinterpret_cast<_simd_s8x1*>(&tmp)[42] = q1;
	reinterpret_cast<_simd_s8x1*>(&tmp)[43] = r1;
	reinterpret_cast<_simd_s8x1*>(&tmp)[44] = s1;
	reinterpret_cast<_simd_s8x1*>(&tmp)[45] = t1;
	reinterpret_cast<_simd_s8x1*>(&tmp)[46] = u1;
	reinterpret_cast<_simd_s8x1*>(&tmp)[47] = v1;
	reinterpret_cast<_simd_s8x1*>(&tmp)[48] = w1;
	reinterpret_cast<_simd_s8x1*>(&tmp)[49] = x1;
	reinterpret_cast<_simd_s8x1*>(&tmp)[50] = y1;
	reinterpret_cast<_simd_s8x1*>(&tmp)[51] = z1;
	reinterpret_cast<_simd_s8x1*>(&tmp)[52] = a2;
	reinterpret_cast<_simd_s8x1*>(&tmp)[53] = b2;
	reinterpret_cast<_simd_s8x1*>(&tmp)[54] = c2;
	reinterpret_cast<_simd_s8x1*>(&tmp)[55] = d2;
	reinterpret_cast<_simd_s8x1*>(&tmp)[56] = e2;
	reinterpret_cast<_simd_s8x1*>(&tmp)[57] = f2;
	reinterpret_cast<_simd_s8x1*>(&tmp)[58] = g2;
	reinterpret_cast<_simd_s8x1*>(&tmp)[59] = h2;
	reinterpret_cast<_simd_s8x1*>(&tmp)[60] = i2;
	reinterpret_cast<_simd_s8x1*>(&tmp)[61] = j2;
	reinterpret_cast<_simd_s8x1*>(&tmp)[62] = k2;
	reinterpret_cast<_simd_s8x1*>(&tmp)[63] = l2;
	return tmp;
}
#ifdef _simd_s8x64_set_
	#define _simd_s8x64_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_s8x64_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2)
	#define _simd_s8x64_set_enable() anvil::simd::IsInstructionSetSupported<_simd_s8x64_set_instruction_set>()
#elif defined(_simd_s8x32_set_)
	#define _simd_s8x64_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_s8x64_combine(\
		_simd_s8x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1),\
		_simd_s8x32_set_(g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2));
	#define _simd_s8x64_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_s8x64_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2)
	#define _simd_s8x64_set_enable() (_simd_s8x32_set_enable() && _simd_s8x64_combine_enable())
#else
	#define _simd_s8x64_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_s8x64_set_safe(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2)
	#define _simd_s8x64_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u8x2 ANVIL_SIMD_CALL _simd_u8x2_set_safe(_simd_u8x1 a0, _simd_u8x1 b0) {
	_simd_u8x2 tmp;
	reinterpret_cast<_simd_u8x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[1] = b0;
	return tmp;
}
#ifdef _simd_u8x2_set_
	#define _simd_u8x2_set(a0, b0) _simd_u8x2_set_(a0, b0)
	#define _simd_u8x2_set_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x2_set_instruction_set>()
#elif defined(_simd_u8x1_set_)
	#define _simd_u8x2_set_(a0, b0) _simd_u8x2_combine(\
		_simd_u8x1_set_(a0),\
		_simd_u8x1_set_(b0));
	#define _simd_u8x2_set(a0, b0) _simd_u8x2_set_(a0, b0)
	#define _simd_u8x2_set_enable() (_simd_u8x1_set_enable() && _simd_u8x2_combine_enable())
#else
	#define _simd_u8x2_set(a0, b0) _simd_u8x2_set_safe(a0, b0)
	#define _simd_u8x2_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u8x4 ANVIL_SIMD_CALL _simd_u8x4_set_safe(_simd_u8x1 a0, _simd_u8x1 b0, _simd_u8x1 c0, _simd_u8x1 d0) {
	_simd_u8x4 tmp;
	reinterpret_cast<_simd_u8x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[3] = d0;
	return tmp;
}
#ifdef _simd_u8x4_set_
	#define _simd_u8x4_set(a0, b0, c0, d0) _simd_u8x4_set_(a0, b0, c0, d0)
	#define _simd_u8x4_set_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x4_set_instruction_set>()
#elif defined(_simd_u8x2_set_)
	#define _simd_u8x4_set_(a0, b0, c0, d0) _simd_u8x4_combine(\
		_simd_u8x2_set_(a0, b0),\
		_simd_u8x2_set_(c0, d0));
	#define _simd_u8x4_set(a0, b0, c0, d0) _simd_u8x4_set_(a0, b0, c0, d0)
	#define _simd_u8x4_set_enable() (_simd_u8x2_set_enable() && _simd_u8x4_combine_enable())
#else
	#define _simd_u8x4_set(a0, b0, c0, d0) _simd_u8x4_set_safe(a0, b0, c0, d0)
	#define _simd_u8x4_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u8x8 ANVIL_SIMD_CALL _simd_u8x8_set_safe(_simd_u8x1 a0, _simd_u8x1 b0, _simd_u8x1 c0, _simd_u8x1 d0, _simd_u8x1 e0, _simd_u8x1 f0, _simd_u8x1 g0, _simd_u8x1 h0) {
	_simd_u8x8 tmp;
	reinterpret_cast<_simd_u8x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[7] = h0;
	return tmp;
}
#ifdef _simd_u8x8_set_
	#define _simd_u8x8_set(a0, b0, c0, d0, e0, f0, g0, h0) _simd_u8x8_set_(a0, b0, c0, d0, e0, f0, g0, h0)
	#define _simd_u8x8_set_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x8_set_instruction_set>()
#elif defined(_simd_u8x4_set_)
	#define _simd_u8x8_set_(a0, b0, c0, d0, e0, f0, g0, h0) _simd_u8x8_combine(\
		_simd_u8x4_set_(a0, b0, c0, d0),\
		_simd_u8x4_set_(e0, f0, g0, h0));
	#define _simd_u8x8_set(a0, b0, c0, d0, e0, f0, g0, h0) _simd_u8x8_set_(a0, b0, c0, d0, e0, f0, g0, h0)
	#define _simd_u8x8_set_enable() (_simd_u8x4_set_enable() && _simd_u8x8_combine_enable())
#else
	#define _simd_u8x8_set(a0, b0, c0, d0, e0, f0, g0, h0) _simd_u8x8_set_safe(a0, b0, c0, d0, e0, f0, g0, h0)
	#define _simd_u8x8_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u8x16 ANVIL_SIMD_CALL _simd_u8x16_set_safe(_simd_u8x1 a0, _simd_u8x1 b0, _simd_u8x1 c0, _simd_u8x1 d0, _simd_u8x1 e0, _simd_u8x1 f0, _simd_u8x1 g0, _simd_u8x1 h0, _simd_u8x1 i0, _simd_u8x1 j0, _simd_u8x1 k0, _simd_u8x1 l0, _simd_u8x1 m0, _simd_u8x1 n0, _simd_u8x1 o0, _simd_u8x1 p0) {
	_simd_u8x16 tmp;
	reinterpret_cast<_simd_u8x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[7] = h0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[8] = i0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[9] = j0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[10] = k0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[11] = l0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[12] = m0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[13] = n0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[14] = o0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[15] = p0;
	return tmp;
}
#ifdef _simd_u8x16_set_
	#define _simd_u8x16_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_u8x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0)
	#define _simd_u8x16_set_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x16_set_instruction_set>()
#elif defined(_simd_u8x8_set_)
	#define _simd_u8x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_u8x16_combine(\
		_simd_u8x8_set_(a0, b0, c0, d0, e0, f0, g0, h0),\
		_simd_u8x8_set_(i0, j0, k0, l0, m0, n0, o0, p0));
	#define _simd_u8x16_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_u8x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0)
	#define _simd_u8x16_set_enable() (_simd_u8x8_set_enable() && _simd_u8x16_combine_enable())
#else
	#define _simd_u8x16_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) _simd_u8x16_set_safe(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0)
	#define _simd_u8x16_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u8x32 ANVIL_SIMD_CALL _simd_u8x32_set_safe(_simd_u8x1 a0, _simd_u8x1 b0, _simd_u8x1 c0, _simd_u8x1 d0, _simd_u8x1 e0, _simd_u8x1 f0, _simd_u8x1 g0, _simd_u8x1 h0, _simd_u8x1 i0, _simd_u8x1 j0, _simd_u8x1 k0, _simd_u8x1 l0, _simd_u8x1 m0, _simd_u8x1 n0, _simd_u8x1 o0, _simd_u8x1 p0, _simd_u8x1 q0, _simd_u8x1 r0, _simd_u8x1 s0, _simd_u8x1 t0, _simd_u8x1 u0, _simd_u8x1 v0, _simd_u8x1 w0, _simd_u8x1 x0, _simd_u8x1 y0, _simd_u8x1 z0, _simd_u8x1 a1, _simd_u8x1 b1, _simd_u8x1 c1, _simd_u8x1 d1, _simd_u8x1 e1, _simd_u8x1 f1) {
	_simd_u8x32 tmp;
	reinterpret_cast<_simd_u8x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[7] = h0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[8] = i0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[9] = j0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[10] = k0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[11] = l0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[12] = m0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[13] = n0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[14] = o0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[15] = p0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[16] = q0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[17] = r0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[18] = s0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[19] = t0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[20] = u0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[21] = v0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[22] = w0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[23] = x0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[24] = y0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[25] = z0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[26] = a1;
	reinterpret_cast<_simd_u8x1*>(&tmp)[27] = b1;
	reinterpret_cast<_simd_u8x1*>(&tmp)[28] = c1;
	reinterpret_cast<_simd_u8x1*>(&tmp)[29] = d1;
	reinterpret_cast<_simd_u8x1*>(&tmp)[30] = e1;
	reinterpret_cast<_simd_u8x1*>(&tmp)[31] = f1;
	return tmp;
}
#ifdef _simd_u8x32_set_
	#define _simd_u8x32_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_u8x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1)
	#define _simd_u8x32_set_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x32_set_instruction_set>()
#elif defined(_simd_u8x16_set_)
	#define _simd_u8x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_u8x32_combine(\
		_simd_u8x16_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0),\
		_simd_u8x16_set_(q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1));
	#define _simd_u8x32_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_u8x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1)
	#define _simd_u8x32_set_enable() (_simd_u8x16_set_enable() && _simd_u8x32_combine_enable())
#else
	#define _simd_u8x32_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1) _simd_u8x32_set_safe(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1)
	#define _simd_u8x32_set_enable() true
#endif

static ANVIL_STRONG_INLINE _simd_u8x64 ANVIL_SIMD_CALL _simd_u8x64_set_safe(_simd_u8x1 a0, _simd_u8x1 b0, _simd_u8x1 c0, _simd_u8x1 d0, _simd_u8x1 e0, _simd_u8x1 f0, _simd_u8x1 g0, _simd_u8x1 h0, _simd_u8x1 i0, _simd_u8x1 j0, _simd_u8x1 k0, _simd_u8x1 l0, _simd_u8x1 m0, _simd_u8x1 n0, _simd_u8x1 o0, _simd_u8x1 p0, _simd_u8x1 q0, _simd_u8x1 r0, _simd_u8x1 s0, _simd_u8x1 t0, _simd_u8x1 u0, _simd_u8x1 v0, _simd_u8x1 w0, _simd_u8x1 x0, _simd_u8x1 y0, _simd_u8x1 z0, _simd_u8x1 a1, _simd_u8x1 b1, _simd_u8x1 c1, _simd_u8x1 d1, _simd_u8x1 e1, _simd_u8x1 f1, _simd_u8x1 g1, _simd_u8x1 h1, _simd_u8x1 i1, _simd_u8x1 j1, _simd_u8x1 k1, _simd_u8x1 l1, _simd_u8x1 m1, _simd_u8x1 n1, _simd_u8x1 o1, _simd_u8x1 p1, _simd_u8x1 q1, _simd_u8x1 r1, _simd_u8x1 s1, _simd_u8x1 t1, _simd_u8x1 u1, _simd_u8x1 v1, _simd_u8x1 w1, _simd_u8x1 x1, _simd_u8x1 y1, _simd_u8x1 z1, _simd_u8x1 a2, _simd_u8x1 b2, _simd_u8x1 c2, _simd_u8x1 d2, _simd_u8x1 e2, _simd_u8x1 f2, _simd_u8x1 g2, _simd_u8x1 h2, _simd_u8x1 i2, _simd_u8x1 j2, _simd_u8x1 k2, _simd_u8x1 l2) {
	_simd_u8x64 tmp;
	reinterpret_cast<_simd_u8x1*>(&tmp)[0] = a0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[1] = b0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[2] = c0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[3] = d0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[4] = e0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[5] = f0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[6] = g0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[7] = h0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[8] = i0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[9] = j0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[10] = k0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[11] = l0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[12] = m0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[13] = n0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[14] = o0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[15] = p0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[16] = q0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[17] = r0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[18] = s0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[19] = t0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[20] = u0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[21] = v0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[22] = w0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[23] = x0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[24] = y0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[25] = z0;
	reinterpret_cast<_simd_u8x1*>(&tmp)[26] = a1;
	reinterpret_cast<_simd_u8x1*>(&tmp)[27] = b1;
	reinterpret_cast<_simd_u8x1*>(&tmp)[28] = c1;
	reinterpret_cast<_simd_u8x1*>(&tmp)[29] = d1;
	reinterpret_cast<_simd_u8x1*>(&tmp)[30] = e1;
	reinterpret_cast<_simd_u8x1*>(&tmp)[31] = f1;
	reinterpret_cast<_simd_u8x1*>(&tmp)[32] = g1;
	reinterpret_cast<_simd_u8x1*>(&tmp)[33] = h1;
	reinterpret_cast<_simd_u8x1*>(&tmp)[34] = i1;
	reinterpret_cast<_simd_u8x1*>(&tmp)[35] = j1;
	reinterpret_cast<_simd_u8x1*>(&tmp)[36] = k1;
	reinterpret_cast<_simd_u8x1*>(&tmp)[37] = l1;
	reinterpret_cast<_simd_u8x1*>(&tmp)[38] = m1;
	reinterpret_cast<_simd_u8x1*>(&tmp)[39] = n1;
	reinterpret_cast<_simd_u8x1*>(&tmp)[40] = o1;
	reinterpret_cast<_simd_u8x1*>(&tmp)[41] = p1;
	reinterpret_cast<_simd_u8x1*>(&tmp)[42] = q1;
	reinterpret_cast<_simd_u8x1*>(&tmp)[43] = r1;
	reinterpret_cast<_simd_u8x1*>(&tmp)[44] = s1;
	reinterpret_cast<_simd_u8x1*>(&tmp)[45] = t1;
	reinterpret_cast<_simd_u8x1*>(&tmp)[46] = u1;
	reinterpret_cast<_simd_u8x1*>(&tmp)[47] = v1;
	reinterpret_cast<_simd_u8x1*>(&tmp)[48] = w1;
	reinterpret_cast<_simd_u8x1*>(&tmp)[49] = x1;
	reinterpret_cast<_simd_u8x1*>(&tmp)[50] = y1;
	reinterpret_cast<_simd_u8x1*>(&tmp)[51] = z1;
	reinterpret_cast<_simd_u8x1*>(&tmp)[52] = a2;
	reinterpret_cast<_simd_u8x1*>(&tmp)[53] = b2;
	reinterpret_cast<_simd_u8x1*>(&tmp)[54] = c2;
	reinterpret_cast<_simd_u8x1*>(&tmp)[55] = d2;
	reinterpret_cast<_simd_u8x1*>(&tmp)[56] = e2;
	reinterpret_cast<_simd_u8x1*>(&tmp)[57] = f2;
	reinterpret_cast<_simd_u8x1*>(&tmp)[58] = g2;
	reinterpret_cast<_simd_u8x1*>(&tmp)[59] = h2;
	reinterpret_cast<_simd_u8x1*>(&tmp)[60] = i2;
	reinterpret_cast<_simd_u8x1*>(&tmp)[61] = j2;
	reinterpret_cast<_simd_u8x1*>(&tmp)[62] = k2;
	reinterpret_cast<_simd_u8x1*>(&tmp)[63] = l2;
	return tmp;
}
#ifdef _simd_u8x64_set_
	#define _simd_u8x64_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_u8x64_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2)
	#define _simd_u8x64_set_enable() anvil::simd::IsInstructionSetSupported<_simd_u8x64_set_instruction_set>()
#elif defined(_simd_u8x32_set_)
	#define _simd_u8x64_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_u8x64_combine(\
		_simd_u8x32_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1),\
		_simd_u8x32_set_(g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2));
	#define _simd_u8x64_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_u8x64_set_(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2)
	#define _simd_u8x64_set_enable() (_simd_u8x32_set_enable() && _simd_u8x64_combine_enable())
#else
	#define _simd_u8x64_set(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2) _simd_u8x64_set_safe(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0, q0, r0, s0, t0, u0, v0, w0, x0, y0, z0, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, n1, o1, p1, q1, r1, s1, t1, u1, v1, w1, x1, y1, z1, a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2, l2)
	#define _simd_u8x64_set_enable() true
#endif

