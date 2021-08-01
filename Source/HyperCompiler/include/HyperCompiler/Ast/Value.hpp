/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <fmt/ostream.h>

#include <string>

namespace HyperCompiler
{
	class Value
	{
	public:
		enum class Type
		{
			Undefined = 0,
			Bool,
			Char,
			Float,
			Double,
			Int8,
			Int16,
			Int32,
			Int64,
			Uint8,
			Uint16,
			Uint32,
			Uint64,
			String
		};

	public:
		Value() = default;
		explicit Value(Type type);
		explicit Value(bool bool_value);
		explicit Value(char char_value);
		explicit Value(float float_value);
		explicit Value(double double_value);
		explicit Value(int8_t int8_value);
		explicit Value(int16_t int16_value);
		explicit Value(int32_t int32_value);
		explicit Value(int64_t int64_value);
		explicit Value(uint8_t uint8_value);
		explicit Value(uint16_t uint16_value);
		explicit Value(uint32_t uint32_value);
		explicit Value(uint64_t uint64_value);
		explicit Value(const char* string_value);
		
		Type type() const;
		
		bool is_undefined() const;
		bool is_bool() const;
		bool is_char() const;
		bool is_float() const;
		bool is_double() const;
		bool is_int8() const;
		bool is_int16() const;
		bool is_int32() const;
		bool is_int64() const;
		bool is_uint8() const;
		bool is_uint16() const;
		bool is_uint32() const;
		bool is_uint64() const;
		bool is_string() const;
		
		bool is_int() const;
		bool is_uint() const;
		bool is_numeric() const;
		
		bool as_bool() const;
		char as_char() const;
		float as_float() const;
		double as_double() const;
		int8_t as_int8() const;
		int16_t as_int16() const;
		int32_t as_int32() const;
		int64_t as_int64() const;
		uint8_t as_uint8() const;
		uint16_t as_uint16() const;
		uint32_t as_uint32() const;
		uint64_t as_uint64() const;
		const char* as_string() const;
		
		static Value add(const Value& left, const Value& right);
		static Value subtract(const Value& left, const Value& right);
		static Value multiply(const Value& left, const Value& right);
		static Value divide(const Value& left, const Value& right);
		
	private:
		Type m_type{ Type::Undefined };
		
		union RealValue
		{
			bool as_bool;
			char as_char;
			float as_float;
			double as_double;
			int8_t as_int8;
			int16_t as_int16;
			int32_t as_int32;
			int64_t as_int64;
			uint8_t as_uint8;
			uint16_t as_uint16;
			uint32_t as_uint32;
			uint64_t as_uint64;
			const char* as_string;
		} m_value{};
	};
	
	std::ostream& operator<<(std::ostream& ostream, const Value& value);
} // namespace HyperCompiler
