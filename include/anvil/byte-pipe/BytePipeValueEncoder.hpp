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

#ifndef ANVIL_BYTEPIPE_ENCODER_HPP
#define ANVIL_BYTEPIPE_ENCODER_HPP

#include <algorithm>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <unordered_map>
#include "anvil/byte-pipe/BytePipeObjects.hpp"

namespace anvil { namespace BytePipe {

	template<>
	struct ValueEncoder<bool> {
		typedef bool type;

		static ANVIL_STRONG_INLINE Value Encode(const type value) {
			return Value(value);
		}

		static ANVIL_STRONG_INLINE type Decode(const Value& value) {
			return value.Get<type>();
		}

	};

	template<>
	struct ValueEncoder<char> {
		typedef char type;

		static ANVIL_STRONG_INLINE Value Encode(const type value) {
			return Value(value);
		}

		static ANVIL_STRONG_INLINE type Decode(const Value& value) {
			return value.Get<type>();
		}

	};

	template<>
	struct ValueEncoder<uint8_t> {
		typedef uint8_t type;

		static ANVIL_STRONG_INLINE Value Encode(const type value) {
			return Value(value);
		}

		static ANVIL_STRONG_INLINE type Decode(const Value& value) {
			return value.Get<type>();
		}

	};

	template<>
	struct ValueEncoder<uint16_t> {
		typedef uint16_t type;

		static ANVIL_STRONG_INLINE Value Encode(const type value) {
			return Value(value);
		}

		static ANVIL_STRONG_INLINE type Decode(const Value& value) {
			return value.Get<type>();
		}

	};

	template<>
	struct ValueEncoder<uint32_t> {
		typedef uint32_t type;

		static ANVIL_STRONG_INLINE Value Encode(const type value) {
			return Value(value);
		}

		static ANVIL_STRONG_INLINE type Decode(const Value& value) {
			return value.Get<type>();
		}

	};

	template<>
	struct ValueEncoder<uint64_t> {
		typedef uint64_t type;

		static ANVIL_STRONG_INLINE Value Encode(const type value) {
			return Value(value);
		}

		static ANVIL_STRONG_INLINE type Decode(const Value& value) {
			return value.Get<type>();
		}

	};

	template<>
	struct ValueEncoder<int8_t> {
		typedef int8_t type;

		static ANVIL_STRONG_INLINE Value Encode(const type value) {
			return Value(value);
		}

		static ANVIL_STRONG_INLINE type Decode(const Value& value) {
			return value.Get<type>();
		}

	};

	template<>
	struct ValueEncoder<int16_t> {
		typedef int16_t type;

		static ANVIL_STRONG_INLINE Value Encode(const type value) {
			return Value(value);
		}

		static ANVIL_STRONG_INLINE type Decode(const Value& value) {
			return value.Get<type>();
		}

	};

	template<>
	struct ValueEncoder<int32_t> {
		typedef int32_t type;

		static ANVIL_STRONG_INLINE Value Encode(const type value) {
			return Value(value);
		}

		static ANVIL_STRONG_INLINE type Decode(const Value& value) {
			return value.Get<type>();
		}

	};

	template<>
	struct ValueEncoder<int64_t> {
		typedef int64_t type;

		static ANVIL_STRONG_INLINE Value Encode(const type value) {
			return Value(value);
		}

		static ANVIL_STRONG_INLINE type Decode(const Value& value) {
			return value.Get<type>();
		}

	};

	template<>
	struct ValueEncoder<half> {
		typedef half type;

		static ANVIL_STRONG_INLINE Value Encode(const type value) {
			return Value(value);
		}

		static ANVIL_STRONG_INLINE type Decode(const Value& value) {
			return value.Get<type>();
		}

	};

	template<>
	struct ValueEncoder<float> {
		typedef float type;

		static ANVIL_STRONG_INLINE Value Encode(const type value) {
			return Value(value);
		}

		static ANVIL_STRONG_INLINE type Decode(const Value& value) {
			return value.Get<type>();
		}

	};

	template<>
	struct ValueEncoder<double> {
		typedef float type;

		static ANVIL_STRONG_INLINE Value Encode(const type value) {
			return Value(value);
		}

		static ANVIL_STRONG_INLINE type Decode(const Value& value) {
			return value.Get<type>();
		}

	};

	template<>
	struct ValueEncoder<std::string> {
		typedef std::string type;

		static ANVIL_STRONG_INLINE Value Encode(const type value) {
			return Value(value);
		}

		static ANVIL_STRONG_INLINE type Decode(const Value& value) {
			return *value.Get<type>();
		}

	};

	namespace detail{

		template<class T>
		static Value ValueArrayEncoder(const T* src, const size_t s) {
			Value tmp;

			if ANVIL_CONSTEXPR_VAR(IsPrimitiveType<T>()) {
				Value::PrimitiveArray& a = tmp.Set<Value::PrimitiveArray>(GetTypeID<T>());
				a.resize(s * sizeof(T));
				memcpy(a.data(), src, sizeof(T) * s);

			} else {
				Value::Array& a = tmp.Set<Value::Array>();
				a.resize(s);
				for (size_t i = 0; i < s; ++i) a[i] = ValueEncoder<T>::Encode(src[i]);
			}

			return tmp;
		}

		template<class T>
		static void ValueArrayDecoder(T* dst, const Value& value) {
			const Value::Array* a = value.Get<Value::Array>();
			const Value::PrimitiveArray* pa = value.Get<Value::PrimitiveArray>();


			if (pa) {
				const size_t s = pa->size();
				if ANVIL_CONSTEXPR_VAR(IsPrimitiveType<T>()) {
					memcpy(dst, pa->data(), sizeof(T) * s);
					return;
				}

			} else if (a) {
				const size_t s = a->size();
				const Value* src = a->data();
				for (size_t i = 0u; i < s; ++i) dst[i] = ValueEncoder<T>::Decode(src[i]);
				return;
			}

			throw std::runtime_error("anvil::ValueArrayDecoderPushBack : Value is not an array");
		}

		template<class T, class IT>
		static Value ValueArrayEncoderIterator(IT begin, const IT end) {
			Value tmp;

			if ANVIL_CONSTEXPR_VAR(IsPrimitiveType<T>()) {
				size_t s = 0u;
				{
					IT i = begin;
					while (i != end) {
						++i;
						++s;
					}
				}

				Value::PrimitiveArray& a = tmp.Set<Value::PrimitiveArray>(GetTypeID<T>());
				a.resize(s * sizeof(T));
				T* dst = reinterpret_cast<T*>(a.data());
				while (begin != end) {
					*dst = *begin;
					++dst;
					++begin;
				}

			} else {
				Value::Array& a = tmp.Set<Value::Array>();
				while (begin != end) {
					a.push_back(ValueEncoder<T>::Encode(*begin));
					++begin;
				}
			}

			return tmp;
		}

		template<class T, class C>
		static void ValueArrayDecoderPushBack(C& dst, const Value& value) {
			const Value::Array* a = value.Get<Value::Array>();
			const Value::PrimitiveArray* pa = value.Get<Value::PrimitiveArray>();

			if(pa) {
				if ANVIL_CONSTEXPR_VAR(IsPrimitiveType<T>()) {
					const size_t s = pa->size();
					const T* src = reinterpret_cast<const T*>(pa->data());
					for (size_t i = 0u; i < s; ++i) dst.push_back(src[i]);
					return;

				}

			} else if (a) {
				const size_t s = a->size();
				const Value* src = a->data();
				for (size_t i = 0u; i < s; ++i) dst.push_back(ValueEncoder<T>::Decode(src[i]));
				return;
			}

			throw std::runtime_error("anvil::ValueArrayDecoderPushBack : Value is not an array");
		}
	}

	template<class T>
	struct ValueEncoder<std::vector<T>> {
		typedef std::vector<T> type;

		static ANVIL_STRONG_INLINE Value Encode(const type& value) {
			return detail::ValueArrayEncoder<T>(value.data(), value.size());
		}

		static ANVIL_STRONG_INLINE type Decode(const Value& value) {
			type tmp(Value::ArrayWrapper(const_cast<Value&>(value)).size());
			detail::ValueArrayDecoder<T>(tmp.data(), value);
			return tmp;
		}

	};

	template<class T, size_t S>
	struct ValueEncoder<std::array<T,S>> {
		typedef std::array<T, S> type;

		static ANVIL_STRONG_INLINE Value Encode(const type& value) {
			return detail::ValueArrayEncoder<T>(value.data(), S);
		}

		static ANVIL_STRONG_INLINE type Decode(const Value& value) {
			if (Value::ArrayWrapper(const_cast<Value&>(value)).size() != S) throw std::runtime_error("ValueEncoder::Decode<std::array> : Array lengths do not match");
			type tmp;
			detail::ValueArrayDecoder<T>(tmp.data(), value);
			return tmp;
		}

	};

	template<class T>
	struct ValueEncoder<std::list<T>> {
		typedef std::list<T> type;

		static ANVIL_STRONG_INLINE Value Encode(const type& value) {
			return detail::ValueArrayEncoderIterator<T, type::const_iterator>(value.begin(), value.end());
		}

		static ANVIL_STRONG_INLINE type Decode(const Value& value) {
			type tmp;
			detail::ValueArrayDecoderPushBack<T, type>(tmp, value);
			return tmp;
		}

	};

	template<class T>
	struct ValueEncoder<std::deque<T>> {
		typedef std::deque<T> type;

		static ANVIL_STRONG_INLINE Value Encode(const type& value) {
			return detail::ValueArrayEncoderIterator<T, type::const_iterator>(value.begin(), value.end());
		}

		static ANVIL_STRONG_INLINE type Decode(const Value& value) {
			type tmp;
			detail::ValueArrayDecoderPushBack<T, type>(tmp, value);
			return tmp;
		}

	};

	namespace detail {

		template<class K, class T, class type>
		struct ValueEncoderMapHelper {

			static Value Encode(const type& value) {

				std::vector<K> keys;
				std::vector<T> values;

				for (const auto& i : value) {
					keys.push_back(i.first);
					values.push_back(i.second);
				}

				Value tmp;
				Value::Object& obj = tmp.Set<Value::Object>();
				obj.emplace("keys", ValueEncoder<std::vector<K>>::Encode(keys));
				obj.emplace("values", ValueEncoder<std::vector<T>>::Encode(values));
				return tmp;
			}

			static type Decode(const Value& value) {
				const Value::Object* object = value.Get<Value::Object>();
				if (!object) throw std::runtime_error("ValueEncoder<std::map>::Decode : Value is not an object");

				auto keys_it = object->find("keys");
				auto values_it = object->find("values");

				if (keys_it == object->end()) throw std::runtime_error("ValueEncoder<std::map>::Decode : Could not find keys");
				if (values_it == object->end()) throw std::runtime_error("ValueEncoder<std::map>::Decode : Could not find values");

				std::vector<K> keys = ValueEncoder<std::vector<K>>::Decode(keys_it->second);
				std::vector<T> values = ValueEncoder<std::vector<T>>::Decode(values_it->second);

				type tmp;
				const size_t s = keys.size();
				for (size_t i = 0u; i < s; ++i) tmp.emplace(keys[i], values[i]);
				return tmp;
			}

		};
	}

	template<class K, class T>
	struct ValueEncoder<std::map<K,T>> {
		typedef std::map<K, T> type;

		static ANVIL_STRONG_INLINE Value Encode(const type& value) {
			return detail::ValueEncoderMapHelper<K, T, type>::Encode(value);
		}

		static ANVIL_STRONG_INLINE type Decode(const Value& value) {
			return detail::ValueEncoderMapHelper<K, T, type>::Decode(value);
		}

	};

	template<class K, class T>
	struct ValueEncoder<std::unordered_map<K, T>> {
		typedef std::unordered_map<K, T> type;

		static ANVIL_STRONG_INLINE Value Encode(const type& value) {
			return detail::ValueEncoderMapHelper<K, T, type>::Encode(value);
		}

		static ANVIL_STRONG_INLINE type Decode(const Value& value) {
			return detail::ValueEncoderMapHelper<K, T, type>::Decode(value);
		}

	};

	template<class A, class B>
	struct ValueEncoder<std::pair<A,B>> {
		typedef std::pair<A, B> type;

		static inline Value Encode(const type& value) {
			Value tmp;
			Value::Array& a = value.set<Value::Array>();
			a.push_back(ValueEncoder<A>::Encode(value.first));
			a.push_back(ValueEncoder<B>::Encode(value.second));
			return tmp;
		}

		static inline type Decode(const Value& value) {
			return type(
				ValueEncoder<A>::Decode(value[0u]),
				ValueEncoder<B>::Decode(value[1u])
			);
		}

	};

#if ANVIL_OPENCV_SUPPORT

	template<>
	struct ValueEncoder<cv::Mat> {
		typedef cv::Mat type;

		static inline Value Encode(const type& value, ImageFormat format = IMAGE_BIN, float quality = 100.f) {
			Value tmp;
			tmp.Set<Value::Pod>() = Value::Pod::CreatePODFromCVMat(value, format, quality);
			
			return tmp;
		}

		static inline type Decode(const Value& value) {
			if (!value.IsPod()) throw std::runtime_error("ValueEncoder<cv::Mat>::Decode : Value is not a POD");
			const Value::Pod* pod= value.Get<Value::Pod>();
			if (pod == nullptr || pod->type != POD_OPENCV_IMAGE) throw std::runtime_error("ValueEncoder<cv::Mat>::Decode : POD is not an image");
			return Value::Pod::CreateOpenCVMatFromPOD(pod->data.data(), pod->data.size());
		}

	};

#endif

}}

#endif
