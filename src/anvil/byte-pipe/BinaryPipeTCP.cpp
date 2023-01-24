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

#include "anvil/byte-pipe/BytePipeTCP.hpp"
#include "anvil/core/OperatingSystem.hpp"

#if ANVIL_OS == ANVIL_WINDOWS
	#define WIN32_MEAN_AND_LEAN
	#include <windows.h>
#endif

namespace anvil { namespace BytePipe {
	

}}