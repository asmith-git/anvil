//Copyright 2022 Adam G. Smith
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

#ifndef ANVIL_CORE_TZCOUNT_HPP
#define ANVIL_CORE_TZCOUNT_HPP

/*
	tzcount Count then number of trailing zero bits
*/

#include "anvil/core/Keywords.hpp"

#define ANVIL_USE_HARDWARE_TZCOUNT 1//(ANVIL_COMPILER != ANVIL_MSVC)

#if ANVIL_USE_HARDWARE_TZCOUNT && (ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64)
	#include <immintrin.h>
#endif


namespace anvil {

	namespace detail {
		ANVIL_STRONG_INLINE ANVIL_CONSTEXPR_VAR size_t ANVIL_CALL tzcount_c(uint32_t aValue) throw() {
			aValue &= 255u;

			if (aValue == 0) return 8u;

			size_t count = 0u;
			for(int i = 0; i < 8; ++i) {
				if (aValue & 128u) break;
				aValue <<= 1u;
				++count;
			}

			return count;
		}

		static ANVIL_CONSTEXPR_VAR const uint8_t g_tzcount_lut[256u] = {
			static_cast<uint8_t>(tzcount_c(0)),
			static_cast<uint8_t>(tzcount_c(1)),
			static_cast<uint8_t>(tzcount_c(2)),
			static_cast<uint8_t>(tzcount_c(3)),
			static_cast<uint8_t>(tzcount_c(4)),
			static_cast<uint8_t>(tzcount_c(5)),
			static_cast<uint8_t>(tzcount_c(6)),
			static_cast<uint8_t>(tzcount_c(7)),
			static_cast<uint8_t>(tzcount_c(8)),
			static_cast<uint8_t>(tzcount_c(9)),
			static_cast<uint8_t>(tzcount_c(10)),
			static_cast<uint8_t>(tzcount_c(11)),
			static_cast<uint8_t>(tzcount_c(12)),
			static_cast<uint8_t>(tzcount_c(13)),
			static_cast<uint8_t>(tzcount_c(14)),
			static_cast<uint8_t>(tzcount_c(15)),
			static_cast<uint8_t>(tzcount_c(16)),
			static_cast<uint8_t>(tzcount_c(17)),
			static_cast<uint8_t>(tzcount_c(18)),
			static_cast<uint8_t>(tzcount_c(19)),
			static_cast<uint8_t>(tzcount_c(20)),
			static_cast<uint8_t>(tzcount_c(21)),
			static_cast<uint8_t>(tzcount_c(22)),
			static_cast<uint8_t>(tzcount_c(23)),
			static_cast<uint8_t>(tzcount_c(24)),
			static_cast<uint8_t>(tzcount_c(25)),
			static_cast<uint8_t>(tzcount_c(26)),
			static_cast<uint8_t>(tzcount_c(27)),
			static_cast<uint8_t>(tzcount_c(28)),
			static_cast<uint8_t>(tzcount_c(29)),
			static_cast<uint8_t>(tzcount_c(30)),
			static_cast<uint8_t>(tzcount_c(31)),
			static_cast<uint8_t>(tzcount_c(32)),
			static_cast<uint8_t>(tzcount_c(33)),
			static_cast<uint8_t>(tzcount_c(34)),
			static_cast<uint8_t>(tzcount_c(35)),
			static_cast<uint8_t>(tzcount_c(36)),
			static_cast<uint8_t>(tzcount_c(37)),
			static_cast<uint8_t>(tzcount_c(38)),
			static_cast<uint8_t>(tzcount_c(39)),
			static_cast<uint8_t>(tzcount_c(40)),
			static_cast<uint8_t>(tzcount_c(41)),
			static_cast<uint8_t>(tzcount_c(42)),
			static_cast<uint8_t>(tzcount_c(43)),
			static_cast<uint8_t>(tzcount_c(44)),
			static_cast<uint8_t>(tzcount_c(45)),
			static_cast<uint8_t>(tzcount_c(46)),
			static_cast<uint8_t>(tzcount_c(47)),
			static_cast<uint8_t>(tzcount_c(48)),
			static_cast<uint8_t>(tzcount_c(49)),
			static_cast<uint8_t>(tzcount_c(50)),
			static_cast<uint8_t>(tzcount_c(51)),
			static_cast<uint8_t>(tzcount_c(52)),
			static_cast<uint8_t>(tzcount_c(53)),
			static_cast<uint8_t>(tzcount_c(54)),
			static_cast<uint8_t>(tzcount_c(55)),
			static_cast<uint8_t>(tzcount_c(56)),
			static_cast<uint8_t>(tzcount_c(57)),
			static_cast<uint8_t>(tzcount_c(58)),
			static_cast<uint8_t>(tzcount_c(59)),
			static_cast<uint8_t>(tzcount_c(60)),
			static_cast<uint8_t>(tzcount_c(61)),
			static_cast<uint8_t>(tzcount_c(62)),
			static_cast<uint8_t>(tzcount_c(63)),
			static_cast<uint8_t>(tzcount_c(64)),
			static_cast<uint8_t>(tzcount_c(65)),
			static_cast<uint8_t>(tzcount_c(66)),
			static_cast<uint8_t>(tzcount_c(67)),
			static_cast<uint8_t>(tzcount_c(68)),
			static_cast<uint8_t>(tzcount_c(69)),
			static_cast<uint8_t>(tzcount_c(70)),
			static_cast<uint8_t>(tzcount_c(71)),
			static_cast<uint8_t>(tzcount_c(72)),
			static_cast<uint8_t>(tzcount_c(73)),
			static_cast<uint8_t>(tzcount_c(74)),
			static_cast<uint8_t>(tzcount_c(75)),
			static_cast<uint8_t>(tzcount_c(76)),
			static_cast<uint8_t>(tzcount_c(77)),
			static_cast<uint8_t>(tzcount_c(78)),
			static_cast<uint8_t>(tzcount_c(79)),
			static_cast<uint8_t>(tzcount_c(80)),
			static_cast<uint8_t>(tzcount_c(81)),
			static_cast<uint8_t>(tzcount_c(82)),
			static_cast<uint8_t>(tzcount_c(83)),
			static_cast<uint8_t>(tzcount_c(84)),
			static_cast<uint8_t>(tzcount_c(85)),
			static_cast<uint8_t>(tzcount_c(86)),
			static_cast<uint8_t>(tzcount_c(87)),
			static_cast<uint8_t>(tzcount_c(88)),
			static_cast<uint8_t>(tzcount_c(89)),
			static_cast<uint8_t>(tzcount_c(90)),
			static_cast<uint8_t>(tzcount_c(91)),
			static_cast<uint8_t>(tzcount_c(92)),
			static_cast<uint8_t>(tzcount_c(93)),
			static_cast<uint8_t>(tzcount_c(94)),
			static_cast<uint8_t>(tzcount_c(95)),
			static_cast<uint8_t>(tzcount_c(96)),
			static_cast<uint8_t>(tzcount_c(97)),
			static_cast<uint8_t>(tzcount_c(98)),
			static_cast<uint8_t>(tzcount_c(99)),
			static_cast<uint8_t>(tzcount_c(100)),
			static_cast<uint8_t>(tzcount_c(101)),
			static_cast<uint8_t>(tzcount_c(102)),
			static_cast<uint8_t>(tzcount_c(103)),
			static_cast<uint8_t>(tzcount_c(104)),
			static_cast<uint8_t>(tzcount_c(105)),
			static_cast<uint8_t>(tzcount_c(106)),
			static_cast<uint8_t>(tzcount_c(107)),
			static_cast<uint8_t>(tzcount_c(108)),
			static_cast<uint8_t>(tzcount_c(109)),
			static_cast<uint8_t>(tzcount_c(110)),
			static_cast<uint8_t>(tzcount_c(111)),
			static_cast<uint8_t>(tzcount_c(112)),
			static_cast<uint8_t>(tzcount_c(113)),
			static_cast<uint8_t>(tzcount_c(114)),
			static_cast<uint8_t>(tzcount_c(115)),
			static_cast<uint8_t>(tzcount_c(116)),
			static_cast<uint8_t>(tzcount_c(117)),
			static_cast<uint8_t>(tzcount_c(118)),
			static_cast<uint8_t>(tzcount_c(119)),
			static_cast<uint8_t>(tzcount_c(120)),
			static_cast<uint8_t>(tzcount_c(121)),
			static_cast<uint8_t>(tzcount_c(122)),
			static_cast<uint8_t>(tzcount_c(123)),
			static_cast<uint8_t>(tzcount_c(124)),
			static_cast<uint8_t>(tzcount_c(125)),
			static_cast<uint8_t>(tzcount_c(126)),
			static_cast<uint8_t>(tzcount_c(127)),
			static_cast<uint8_t>(tzcount_c(128)),
			static_cast<uint8_t>(tzcount_c(129)),
			static_cast<uint8_t>(tzcount_c(130)),
			static_cast<uint8_t>(tzcount_c(131)),
			static_cast<uint8_t>(tzcount_c(132)),
			static_cast<uint8_t>(tzcount_c(133)),
			static_cast<uint8_t>(tzcount_c(134)),
			static_cast<uint8_t>(tzcount_c(135)),
			static_cast<uint8_t>(tzcount_c(136)),
			static_cast<uint8_t>(tzcount_c(137)),
			static_cast<uint8_t>(tzcount_c(138)),
			static_cast<uint8_t>(tzcount_c(139)),
			static_cast<uint8_t>(tzcount_c(140)),
			static_cast<uint8_t>(tzcount_c(141)),
			static_cast<uint8_t>(tzcount_c(142)),
			static_cast<uint8_t>(tzcount_c(143)),
			static_cast<uint8_t>(tzcount_c(144)),
			static_cast<uint8_t>(tzcount_c(145)),
			static_cast<uint8_t>(tzcount_c(146)),
			static_cast<uint8_t>(tzcount_c(147)),
			static_cast<uint8_t>(tzcount_c(148)),
			static_cast<uint8_t>(tzcount_c(149)),
			static_cast<uint8_t>(tzcount_c(150)),
			static_cast<uint8_t>(tzcount_c(151)),
			static_cast<uint8_t>(tzcount_c(152)),
			static_cast<uint8_t>(tzcount_c(153)),
			static_cast<uint8_t>(tzcount_c(154)),
			static_cast<uint8_t>(tzcount_c(155)),
			static_cast<uint8_t>(tzcount_c(156)),
			static_cast<uint8_t>(tzcount_c(157)),
			static_cast<uint8_t>(tzcount_c(158)),
			static_cast<uint8_t>(tzcount_c(159)),
			static_cast<uint8_t>(tzcount_c(160)),
			static_cast<uint8_t>(tzcount_c(161)),
			static_cast<uint8_t>(tzcount_c(162)),
			static_cast<uint8_t>(tzcount_c(163)),
			static_cast<uint8_t>(tzcount_c(164)),
			static_cast<uint8_t>(tzcount_c(165)),
			static_cast<uint8_t>(tzcount_c(166)),
			static_cast<uint8_t>(tzcount_c(167)),
			static_cast<uint8_t>(tzcount_c(168)),
			static_cast<uint8_t>(tzcount_c(169)),
			static_cast<uint8_t>(tzcount_c(170)),
			static_cast<uint8_t>(tzcount_c(171)),
			static_cast<uint8_t>(tzcount_c(172)),
			static_cast<uint8_t>(tzcount_c(173)),
			static_cast<uint8_t>(tzcount_c(174)),
			static_cast<uint8_t>(tzcount_c(175)),
			static_cast<uint8_t>(tzcount_c(176)),
			static_cast<uint8_t>(tzcount_c(177)),
			static_cast<uint8_t>(tzcount_c(178)),
			static_cast<uint8_t>(tzcount_c(179)),
			static_cast<uint8_t>(tzcount_c(180)),
			static_cast<uint8_t>(tzcount_c(181)),
			static_cast<uint8_t>(tzcount_c(182)),
			static_cast<uint8_t>(tzcount_c(183)),
			static_cast<uint8_t>(tzcount_c(184)),
			static_cast<uint8_t>(tzcount_c(185)),
			static_cast<uint8_t>(tzcount_c(186)),
			static_cast<uint8_t>(tzcount_c(187)),
			static_cast<uint8_t>(tzcount_c(188)),
			static_cast<uint8_t>(tzcount_c(189)),
			static_cast<uint8_t>(tzcount_c(190)),
			static_cast<uint8_t>(tzcount_c(191)),
			static_cast<uint8_t>(tzcount_c(192)),
			static_cast<uint8_t>(tzcount_c(193)),
			static_cast<uint8_t>(tzcount_c(194)),
			static_cast<uint8_t>(tzcount_c(195)),
			static_cast<uint8_t>(tzcount_c(196)),
			static_cast<uint8_t>(tzcount_c(197)),
			static_cast<uint8_t>(tzcount_c(198)),
			static_cast<uint8_t>(tzcount_c(199)),
			static_cast<uint8_t>(tzcount_c(200)),
			static_cast<uint8_t>(tzcount_c(201)),
			static_cast<uint8_t>(tzcount_c(202)),
			static_cast<uint8_t>(tzcount_c(203)),
			static_cast<uint8_t>(tzcount_c(204)),
			static_cast<uint8_t>(tzcount_c(205)),
			static_cast<uint8_t>(tzcount_c(206)),
			static_cast<uint8_t>(tzcount_c(207)),
			static_cast<uint8_t>(tzcount_c(208)),
			static_cast<uint8_t>(tzcount_c(209)),
			static_cast<uint8_t>(tzcount_c(210)),
			static_cast<uint8_t>(tzcount_c(211)),
			static_cast<uint8_t>(tzcount_c(212)),
			static_cast<uint8_t>(tzcount_c(213)),
			static_cast<uint8_t>(tzcount_c(214)),
			static_cast<uint8_t>(tzcount_c(215)),
			static_cast<uint8_t>(tzcount_c(216)),
			static_cast<uint8_t>(tzcount_c(217)),
			static_cast<uint8_t>(tzcount_c(218)),
			static_cast<uint8_t>(tzcount_c(219)),
			static_cast<uint8_t>(tzcount_c(220)),
			static_cast<uint8_t>(tzcount_c(221)),
			static_cast<uint8_t>(tzcount_c(222)),
			static_cast<uint8_t>(tzcount_c(223)),
			static_cast<uint8_t>(tzcount_c(224)),
			static_cast<uint8_t>(tzcount_c(225)),
			static_cast<uint8_t>(tzcount_c(226)),
			static_cast<uint8_t>(tzcount_c(227)),
			static_cast<uint8_t>(tzcount_c(228)),
			static_cast<uint8_t>(tzcount_c(229)),
			static_cast<uint8_t>(tzcount_c(230)),
			static_cast<uint8_t>(tzcount_c(231)),
			static_cast<uint8_t>(tzcount_c(232)),
			static_cast<uint8_t>(tzcount_c(233)),
			static_cast<uint8_t>(tzcount_c(234)),
			static_cast<uint8_t>(tzcount_c(235)),
			static_cast<uint8_t>(tzcount_c(236)),
			static_cast<uint8_t>(tzcount_c(237)),
			static_cast<uint8_t>(tzcount_c(238)),
			static_cast<uint8_t>(tzcount_c(239)),
			static_cast<uint8_t>(tzcount_c(240)),
			static_cast<uint8_t>(tzcount_c(241)),
			static_cast<uint8_t>(tzcount_c(242)),
			static_cast<uint8_t>(tzcount_c(243)),
			static_cast<uint8_t>(tzcount_c(244)),
			static_cast<uint8_t>(tzcount_c(245)),
			static_cast<uint8_t>(tzcount_c(246)),
			static_cast<uint8_t>(tzcount_c(247)),
			static_cast<uint8_t>(tzcount_c(248)),
			static_cast<uint8_t>(tzcount_c(249)),
			static_cast<uint8_t>(tzcount_c(250)),
			static_cast<uint8_t>(tzcount_c(251)),
			static_cast<uint8_t>(tzcount_c(252)),
			static_cast<uint8_t>(tzcount_c(253)),
			static_cast<uint8_t>(tzcount_c(254)),
			static_cast<uint8_t>(tzcount_c(255))
		};
	}

	ANVIL_STRONG_INLINE size_t ANVIL_CALL tzcount(uint8_t aValue) throw() {
#if ANVIL_USE_HARDWARE_TZCOUNT && (ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64)
		if (aValue == 0u) return 8u;
		return _mm_tzcnt_16(aValue) - 8u;
#else
		return detail::g_tzcount_lut[aValue];
#endif
	}

	ANVIL_STRONG_INLINE size_t ANVIL_CALL tzcount(uint16_t aValue) throw() {
#if ANVIL_USE_HARDWARE_TZCOUNT && (ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64)
		if (aValue == 0u) return 16u;
		return _mm_tzcnt_16(aValue);
#else
		 size_t count = detail::g_tzcount_lut[aValue & 255u];
		 if (count == 8u) count += detail::g_tzcount_lut[aValue >> 8u];
		 return count;
#endif
	}

	ANVIL_STRONG_INLINE size_t ANVIL_CALL tzcount(uint32_t aValue) throw() {
#if ANVIL_USE_HARDWARE_TZCOUNT && (ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86 || ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64)
		if (aValue == 0u) return 32u;
		return _mm_tzcnt_32(aValue);
#else
		size_t count = tzcount(static_cast<uint16_t>(aValue >> 16u));
		if (count == 16u) count += tzcount(static_cast<uint16_t>(aValue & static_cast<uint32_t>(UINT16_MAX)));
		return count;
#endif
	}

	ANVIL_STRONG_INLINE size_t ANVIL_CALL tzcount(uint64_t aValue) throw() {
#if ANVIL_USE_HARDWARE_TZCOUNT && ANVIL_CPU_ARCHITECTURE == ANVIL_CPU_X86_64
		if (aValue == 0ull) return 64u;
		return _mm_tzcnt_64(aValue);
#else
		size_t count = tzcount(static_cast<uint16_t>(aValue >> 32ull));
		if (count == 32u) count += tzcount(static_cast<uint32_t>(aValue & static_cast<uint64_t>(UINT32_MAX)));
		return count;
#endif
	}

	// signed

	ANVIL_STRONG_INLINE int8_t ANVIL_CALL tzcount(int8_t aValue) throw() {
		return tzcount(numeric_reinterpret_cast<uint8_t>(aValue));
	}

	ANVIL_STRONG_INLINE int16_t ANVIL_CALL tzcount(int16_t aValue) throw() {
		return tzcount(numeric_reinterpret_cast<uint16_t>(aValue));
	}

	ANVIL_STRONG_INLINE int32_t ANVIL_CALL tzcount(int32_t aValue) throw() {
		return tzcount(numeric_reinterpret_cast<uint32_t>(aValue));
	}

	ANVIL_STRONG_INLINE int64_t ANVIL_CALL tzcount(int64_t aValue) throw() {
		return tzcount(numeric_reinterpret_cast<uint64_t>(aValue));
	}

	// other types

	ANVIL_STRONG_INLINE float ANVIL_CALL tzcount(float aValue) throw() {
		return tzcount(numeric_reinterpret_cast<uint32_t>(aValue));
	}

	ANVIL_STRONG_INLINE double ANVIL_CALL tzcount(double aValue) throw() {
		return tzcount(numeric_reinterpret_cast<uint64_t>(aValue));
	}

}

#endif