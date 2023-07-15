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

#ifndef ANVIL_CORE_LIBDETECT_HPP
#define ANVIL_CORE_LIBDETECT_HPP

// https://github.com/microsoft/GSL
#if __has_include(<gsl/gsl>) || __has_include(<gsl>)
	#define ANVIL_GSL_SUPPORT 1
#else
	#define ANVIL_GSL_SUPPORT 0
#endif

// https://opencv.org
#if __has_include(<opencv2/opencv.hpp>)
	#define ANVIL_OPENCV_SUPPORT 1
#else
	#define ANVIL_OPENCV_SUPPORT 0
#endif

// https://rapidxml.sourceforge.net
#if __has_include(<rapidxml.hpp>)
	#define ANVIL_XML_SUPPORT 1
#else
	#define ANVIL_XML_SUPPORT 0
#endif

// https://github.com/nlohmann/json
#if __has_include(<nlohmann/json.hpp>)
	#define ANVIL_JSON_SUPPORT 1
#else
	#define ANVIL_JSON_SUPPORT 0
#endif

// https://github.com/Maratyszcza/FP16
#if __has_include(<fp16.h>)
	#define ANVIL_MARATYSZCZA_FP16_SUPPORT 1
#else
	#define ANVIL_MARATYSZCZA_FP16_SUPPORT 0
#endif

#endif
