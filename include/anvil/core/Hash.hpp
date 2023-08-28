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

#ifndef ANVIL_CORE_HASH_HPP
#define ANVIL_CORE_HASH_HPP

#include "Keywords.hpp"

namespace anvil {

	class ANVIL_DLL_EXPORT Hash {
	public:
		Hash();
		virtual ~Hash();

		virtual void Reset() = 0;
	};

	template<class HASH>
	class ANVIL_DLL_EXPORT HashTemplate : public Hash {
	public:
		typedef HASH hash_t;

		HashTemplate() {

		}

		virtual ~HashTemplate() {

		}

		virtual hash_t Hash(const void* src, size_t bytes) = 0;

		ANVIL_STRONG_INLINE hash_t operator()(const void* src, size_t bytes) {
			return Hash(src, bytes);
		}
	};

	namespace hash {

		class ANVIL_DLL_EXPORT DJB2 : public HashTemplate<uint32_t> {
		protected:
			hash_t _hash;
		public:
			DJB2();
			virtual ~DJB2();

			virtual hash_t Hash(const void* src, size_t bytes);
			virtual void Reset() final;
		};

		class ANVIL_DLL_EXPORT DJB2a final : public DJB2 {
		public:
			DJB2a();
			virtual ~DJB2a();

			virtual hash_t Hash(const void* src, size_t bytes) final;
		};

		class ANVIL_DLL_EXPORT SDBM : public HashTemplate<uint32_t> {
		protected:
			hash_t _hash;
		public:
			SDBM();
			virtual ~SDBM();

			virtual hash_t Hash(const void* src, size_t bytes);
			virtual void Reset() final;
		};

		/*!
		*	\brief Faster approximation SDBM
		*/
		class ANVIL_DLL_EXPORT FastSDBM final : public SDBM {
		public:
			FastSDBM();
			virtual ~FastSDBM();

			virtual hash_t Hash(const void* src, size_t bytes);
		};

		class ANVIL_DLL_EXPORT LoseLose final : public HashTemplate<uint32_t> {
		private:
			hash_t _hash;
		public:
			LoseLose();
			virtual ~LoseLose();

			virtual hash_t Hash(const void* src, size_t bytes);
			virtual void Reset() final;
		};

		class ANVIL_DLL_EXPORT Murmur3_32 final : public HashTemplate<uint32_t> {
		protected:
			hash_t _hash;
		public:
			Murmur3_32();
			virtual ~Murmur3_32();

			virtual hash_t Hash(const void* src, size_t bytes);
			virtual void Reset() final;
		};
	}
}

#endif