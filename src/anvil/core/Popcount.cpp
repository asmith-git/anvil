//Copyright 2023 Adam G. Smith
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

#include "anvil/core/Popcount.hpp"

namespace anvil 
{
	namespace detail
	{
		#define POP_LUT(X) static_cast<uint8_t>(PopcountHelper<uint8_t, POPCOUNT_CONSTEXPR>::Execute(X))

		static ANVIL_ALIGN(64) ANVIL_CONSTEXPR_VAR const uint8_t g_popcount_table[256] =
		{
			POP_LUT(0u), POP_LUT(1u), POP_LUT(2u), POP_LUT(3u), POP_LUT(4u), POP_LUT(5u), POP_LUT(6u), POP_LUT(7u), POP_LUT(8u), POP_LUT(9u),
			POP_LUT(10u), POP_LUT(11u), POP_LUT(12u), POP_LUT(13u), POP_LUT(14u), POP_LUT(15u), POP_LUT(16u), POP_LUT(17u), POP_LUT(18u), POP_LUT(19u),
			POP_LUT(20u), POP_LUT(21u), POP_LUT(22u), POP_LUT(23u), POP_LUT(24u), POP_LUT(25u), POP_LUT(26u), POP_LUT(27u), POP_LUT(28u), POP_LUT(29u),
			POP_LUT(30u), POP_LUT(31u), POP_LUT(32u), POP_LUT(33u), POP_LUT(34u), POP_LUT(35u), POP_LUT(36u), POP_LUT(37u), POP_LUT(38u), POP_LUT(39u),
			POP_LUT(40u), POP_LUT(41u), POP_LUT(42u), POP_LUT(43u), POP_LUT(44u), POP_LUT(45u), POP_LUT(46u), POP_LUT(47u), POP_LUT(48u), POP_LUT(49u),
			POP_LUT(50u), POP_LUT(51u), POP_LUT(52u), POP_LUT(53u), POP_LUT(54u), POP_LUT(55u), POP_LUT(56u), POP_LUT(57u), POP_LUT(58u), POP_LUT(59u),
			POP_LUT(60u), POP_LUT(61u), POP_LUT(62u), POP_LUT(63u), POP_LUT(64u), POP_LUT(65u), POP_LUT(66u), POP_LUT(67u), POP_LUT(68u), POP_LUT(69u),
			POP_LUT(70u), POP_LUT(71u), POP_LUT(72u), POP_LUT(73u), POP_LUT(74u), POP_LUT(75u), POP_LUT(76u), POP_LUT(77u), POP_LUT(78u), POP_LUT(79u),
			POP_LUT(80u), POP_LUT(81u), POP_LUT(82u), POP_LUT(83u), POP_LUT(84u), POP_LUT(85u), POP_LUT(86u), POP_LUT(87u), POP_LUT(88u), POP_LUT(89u),
			POP_LUT(90u), POP_LUT(91u), POP_LUT(92u), POP_LUT(93u), POP_LUT(94u), POP_LUT(95u), POP_LUT(96u), POP_LUT(97u), POP_LUT(98u), POP_LUT(99u),
			POP_LUT(100u), POP_LUT(101u), POP_LUT(102u), POP_LUT(103u), POP_LUT(104u), POP_LUT(105u), POP_LUT(106u), POP_LUT(107u), POP_LUT(108u), POP_LUT(109u),
			POP_LUT(110u), POP_LUT(111u), POP_LUT(112u), POP_LUT(113u), POP_LUT(114u), POP_LUT(115u), POP_LUT(116u), POP_LUT(117u), POP_LUT(118u), POP_LUT(119u),
			POP_LUT(120u), POP_LUT(121u), POP_LUT(122u), POP_LUT(123u), POP_LUT(124u), POP_LUT(125u), POP_LUT(126u), POP_LUT(127u), POP_LUT(128u), POP_LUT(129u),
			POP_LUT(130u), POP_LUT(131u), POP_LUT(132u), POP_LUT(133u), POP_LUT(134u), POP_LUT(135u), POP_LUT(136u), POP_LUT(137u), POP_LUT(138u), POP_LUT(139u),
			POP_LUT(140u), POP_LUT(141u), POP_LUT(142u), POP_LUT(143u), POP_LUT(144u), POP_LUT(145u), POP_LUT(146u), POP_LUT(147u), POP_LUT(148u), POP_LUT(149u),
			POP_LUT(150u), POP_LUT(151u), POP_LUT(152u), POP_LUT(153u), POP_LUT(154u), POP_LUT(155u), POP_LUT(156u), POP_LUT(157u), POP_LUT(158u), POP_LUT(159u),
			POP_LUT(160u), POP_LUT(161u), POP_LUT(162u), POP_LUT(163u), POP_LUT(164u), POP_LUT(165u), POP_LUT(166u), POP_LUT(167u), POP_LUT(168u), POP_LUT(169u),
			POP_LUT(170u), POP_LUT(171u), POP_LUT(172u), POP_LUT(173u), POP_LUT(174u), POP_LUT(175u), POP_LUT(176u), POP_LUT(177u), POP_LUT(178u), POP_LUT(179u),
			POP_LUT(180u), POP_LUT(181u), POP_LUT(182u), POP_LUT(183u), POP_LUT(184u), POP_LUT(185u), POP_LUT(186u), POP_LUT(187u), POP_LUT(188u), POP_LUT(189u),
			POP_LUT(190u), POP_LUT(191u), POP_LUT(192u), POP_LUT(193u), POP_LUT(194u), POP_LUT(195u), POP_LUT(196u), POP_LUT(197u), POP_LUT(198u), POP_LUT(199u),
			POP_LUT(200u), POP_LUT(201u), POP_LUT(202u), POP_LUT(203u), POP_LUT(204u), POP_LUT(205u), POP_LUT(206u), POP_LUT(207u), POP_LUT(208u), POP_LUT(209u),
			POP_LUT(210u), POP_LUT(211u), POP_LUT(212u), POP_LUT(213u), POP_LUT(214u), POP_LUT(215u), POP_LUT(216u), POP_LUT(217u), POP_LUT(218u), POP_LUT(219u),
			POP_LUT(220u), POP_LUT(221u), POP_LUT(222u), POP_LUT(223u), POP_LUT(224u), POP_LUT(225u), POP_LUT(226u), POP_LUT(227u), POP_LUT(228u), POP_LUT(229u),
			POP_LUT(230u), POP_LUT(231u), POP_LUT(232u), POP_LUT(233u), POP_LUT(234u), POP_LUT(235u), POP_LUT(236u), POP_LUT(237u), POP_LUT(238u), POP_LUT(239u),
			POP_LUT(240u), POP_LUT(241u), POP_LUT(242u), POP_LUT(243u), POP_LUT(244u), POP_LUT(245u), POP_LUT(246u), POP_LUT(247u), POP_LUT(248u), POP_LUT(249u),
			POP_LUT(250u), POP_LUT(251u), POP_LUT(252u), POP_LUT(253u), POP_LUT(254u), POP_LUT(255u)
		};

		const uint8_t* ANVIL_CALL GetPopcountLUT() throw()
		{
			return g_popcount_table;
		}
	}
}