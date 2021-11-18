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

#ifndef ANVIL_COMPUTE_INC_HPP
#define ANVIL_COMPUTE_INC_HPP

#include "anvil/compute/Arithmetic.hpp"
#include "anvil/compute/Type.hpp"
#include "anvil/compute/Scalar.hpp"
#include "anvil/compute/Vector.hpp"

#include "anvil/compute/simd/Blend.hpp"
#include "anvil/compute/simd/Add.hpp"
#include "anvil/compute/simd/Sub.hpp"
#include "anvil/compute/simd/CmpEq.hpp"
#include "anvil/compute/simd/Div.hpp"
#include "anvil/compute/simd/Fma.hpp"
#include "anvil/compute/simd/And.hpp"
#include "anvil/compute/simd/Or.hpp"
#include "anvil/compute/simd/Xor.hpp"
#include "anvil/compute/simd/lshift.hpp"
#include "anvil/compute/simd/rshift.hpp"
#include "anvil/compute/simd/cmpeq.hpp"
#include "anvil/compute/simd/cmpne.hpp"
#include "anvil/compute/simd/cmpgt.hpp"
#include "anvil/compute/simd/cmplt.hpp"
#include "anvil/compute/simd/cmpge.hpp"
#include "anvil/compute/simd/cmple.hpp"
#include "anvil/compute/simd/not.hpp"

#endif