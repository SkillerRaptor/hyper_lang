/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "HyperCompiler/Ast/Literals.hpp"

#include "HyperCompiler/Logger.hpp"

namespace HyperCompiler
{
	std::string Literal::class_name() const
	{
		return "Literal";
	}
	
	BoolLiteral::BoolLiteral(bool value)
		: m_value(value)
	{
	}
	
	Value BoolLiteral::execute() const
	{
		return Value(m_value);
	}
	
	std::string BoolLiteral::class_name() const
	{
		return "BoolLiteral";
	}
	
	void BoolLiteral::dump(unsigned int indent) const
	{
		AstNode::dump(indent++);
		Logger::info_indent(indent, "Value: {}\n", m_value);
	}

	NumericLiteral::NumericLiteral(int8_t value)
		: m_value(value)
	{
	}

	NumericLiteral::NumericLiteral(int16_t value)
		: m_value(value)
	{
	}

	NumericLiteral::NumericLiteral(int32_t value)
		: m_value(value)
	{
	}

	NumericLiteral::NumericLiteral(int64_t value)
		: m_value(value)
	{
	}

	NumericLiteral::NumericLiteral(uint8_t value)
		: m_value(value)
	{
	}

	NumericLiteral::NumericLiteral(uint16_t value)
		: m_value(value)
	{
	}

	NumericLiteral::NumericLiteral(uint32_t value)
		: m_value(value)
	{
	}

	NumericLiteral::NumericLiteral(uint64_t value)
		: m_value(value)
	{
	}

	Value NumericLiteral::execute() const
	{
		return m_value;
	}
	
	void NumericLiteral::dump(unsigned int indent) const
	{
		AstNode::dump(indent++);
		Logger::info_indent(indent, "Value: {}\n", m_value);
	}

	std::string NumericLiteral::class_name() const
	{
		return "NumericLiteral";
	}
} // namespace HyperCompiler
