/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "HyperCompiler/Ast/Value.hpp"

#include "HyperCompiler/Utils/Assertion.hpp"

namespace HyperCompiler
{
	Value::Value(Value::Type type)
		: m_type(type)
	{
	}

	Value::Value(bool bool_value)
		: m_type(Type::Bool)
	{
		m_value.as_bool = bool_value;
	}

	Value::Value(char char_value)
		: m_type(Type::Char)
	{
		m_value.as_char = char_value;
	}

	Value::Value(float float_value)
		: m_type(Type::Float)
	{
		m_value.as_float = float_value;
	}

	Value::Value(double double_value)
		: m_type(Type::Double)
	{
		m_value.as_double = double_value;
	}

	Value::Value(int8_t int8_value)
		: m_type(Type::Int8)
	{
		m_value.as_int8 = int8_value;
	}

	Value::Value(int16_t int16_value)
		: m_type(Type::Int16)
	{
		m_value.as_int16 = int16_value;
	}

	Value::Value(int32_t int32_value)
		: m_type(Type::Int32)
	{
		m_value.as_int32 = int32_value;
	}

	Value::Value(int64_t int64_value)
		: m_type(Type::Int64)
	{
		m_value.as_int64 = int64_value;
	}

	Value::Value(uint8_t uint8_value)
		: m_type(Type::Uint8)
	{
		m_value.as_uint8 = uint8_value;
	}

	Value::Value(uint16_t uint16_value)
		: m_type(Type::Uint16)
	{
		m_value.as_uint16 = uint16_value;
	}

	Value::Value(uint32_t uint32_value)
		: m_type(Type::Uint32)
	{
		m_value.as_uint32 = uint32_value;
	}

	Value::Value(uint64_t uint64_value)
		: m_type(Type::Uint64)
	{
		m_value.as_uint64 = uint64_value;
	}

	Value::Value(const char* string_value)
		: m_type(Type::String)
	{
		m_value.as_string = string_value;
	}

	Value::Type Value::type() const
	{
		return m_type;
	}

	bool Value::is_undefined() const
	{
		return m_type == Type::Undefined;
	}

	bool Value::is_bool() const
	{
		return m_type == Type::Bool;
	}

	bool Value::is_char() const
	{
		return m_type == Type::Char;
	}

	bool Value::is_float() const
	{
		return m_type == Type::Float;
	}

	bool Value::is_double() const
	{
		return m_type == Type::Double;
	}

	bool Value::is_int8() const
	{
		return m_type == Type::Int8;
	}

	bool Value::is_int16() const
	{
		return m_type == Type::Int16;
	}

	bool Value::is_int32() const
	{
		return m_type == Type::Int32;
	}

	bool Value::is_int64() const
	{
		return m_type == Type::Int64;
	}

	bool Value::is_uint8() const
	{
		return m_type == Type::Uint8;
	}

	bool Value::is_uint16() const
	{
		return m_type == Type::Uint16;
	}

	bool Value::is_uint32() const
	{
		return m_type == Type::Uint32;
	}

	bool Value::is_uint64() const
	{
		return m_type == Type::Uint64;
	}

	bool Value::is_string() const
	{
		return m_type == Type::String;
	}

	bool Value::is_int() const
	{
		return is_int8() || is_int16() || is_int32() || is_int64();
	}

	bool Value::is_uint() const
	{
		return is_uint8() || is_uint16() || is_uint32() || is_uint64();
	}

	bool Value::is_numeric() const
	{
		return is_int() || is_uint();
	}

	bool Value::as_bool() const
	{
		ASSERT(is_bool());
		return m_value.as_bool;
	}

	char Value::as_char() const
	{
		ASSERT(is_char());
		return m_value.as_char;
	}

	float Value::as_float() const
	{
		ASSERT(is_float());
		return m_value.as_float;
	}

	double Value::as_double() const
	{
		ASSERT(is_double());
		return m_value.as_double;
	}

	int8_t Value::as_int8() const
	{
		ASSERT(is_int8());
		return m_value.as_int8;
	}

	int16_t Value::as_int16() const
	{
		ASSERT(is_int16());
		return m_value.as_int16;
	}

	int32_t Value::as_int32() const
	{
		ASSERT(is_int32());
		return m_value.as_int32;
	}

	int64_t Value::as_int64() const
	{
		ASSERT(is_int64());
		return m_value.as_int64;
	}

	uint8_t Value::as_uint8() const
	{
		ASSERT(is_uint8());
		return m_value.as_uint8;
	}

	uint16_t Value::as_uint16() const
	{
		ASSERT(is_uint16());
		return m_value.as_uint16;
	}

	uint32_t Value::as_uint32() const
	{
		ASSERT(is_uint32());
		return m_value.as_uint32;
	}

	uint64_t Value::as_uint64() const
	{
		ASSERT(is_uint64());
		return m_value.as_uint64;
	}

	const char* Value::as_string() const
	{
		ASSERT(is_string());
		return m_value.as_string;
	}

	Value Value::add(const Value& left, const Value& right)
	{
		if (left.is_undefined() || right.is_undefined())
		{
			return {};
		}

		if (!left.is_numeric() || !right.is_numeric())
		{
			return {};
		}
		
		// TODO: Type checking

		return Value(left.as_int64() + right.as_int64());
	}

	Value Value::subtract(const Value& left, const Value& right)
	{
		if (left.is_undefined() || right.is_undefined())
		{
			return {};
		}

		if (!left.is_numeric() || !right.is_numeric())
		{
			return {};
		}

		return Value(left.as_int64() - right.as_int64());
	}

	Value Value::multiply(const Value& left, const Value& right)
	{
		if (left.is_undefined() || right.is_undefined())
		{
			return {};
		}

		if (!left.is_numeric() || !right.is_numeric())
		{
			return {};
		}

		return Value(left.as_int64() * right.as_int64());
	}

	Value Value::divide(const Value& left, const Value& right)
	{
		if (left.is_undefined() || right.is_undefined())
		{
			return {};
		}

		if (!left.is_numeric() || !right.is_numeric())
		{
			return {};
		}

		return Value(left.as_int64() / right.as_int64());
	}

	std::ostream& operator<<(std::ostream& ostream, const Value& value)
	{
		switch (value.type())
		{
		case Value::Type::Undefined:
			break;
		case Value::Type::Bool:
			ostream << value.as_bool();
			break;
		case Value::Type::Char:
			ostream << value.as_char();
			break;
		case Value::Type::Float:
			ostream << value.as_float();
			break;
		case Value::Type::Double:
			ostream << value.as_double();
			break;
		case Value::Type::Int8:
			ostream << value.as_int8();
			break;
		case Value::Type::Int16:
			ostream << value.as_int16();
			break;
		case Value::Type::Int32:
			ostream << value.as_int32();
			break;
		case Value::Type::Int64:
			ostream << value.as_int64();
			break;
		case Value::Type::Uint8:
			ostream << value.as_uint8();
			break;
		case Value::Type::Uint16:
			ostream << value.as_uint16();
			break;
		case Value::Type::Uint32:
			ostream << value.as_uint32();
			break;
		case Value::Type::Uint64:
			ostream << value.as_uint64();
			break;
		case Value::Type::String:
			ostream << value.as_string();
			break;
		}

		return ostream;
	}
} // namespace HyperCompiler
