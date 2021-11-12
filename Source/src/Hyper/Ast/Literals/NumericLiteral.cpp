/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Literals/NumericLiteral.hpp"

#include "Hyper/Generators/Generator.hpp"
#include "Hyper/Logger.hpp"

namespace Hyper
{
	NumericLiteral::NumericLiteral(Type type, uint64_t value)
		: m_type(type)
		, m_value(value)
	{
	}

	void NumericLiteral::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void NumericLiteral::dump(size_t indent) const
	{
		AstNode::indent(indent);
		Logger::raw("{} (type={}, value={})\n", class_name(), m_type, m_value);
	}

	AstNode::Category NumericLiteral::class_category() const noexcept
	{
		return AstNode::Category::NumericLiteral;
	}

	std::string_view NumericLiteral::class_name() const noexcept
	{
		return "NumericLiteral";
	}

	NumericLiteral::Type NumericLiteral::type() const noexcept
	{
		return m_type;
	}

	uint64_t NumericLiteral::value() const noexcept
	{
		return m_value;
	}

	std::ostream &operator<<(
		std::ostream &ostream,
		const NumericLiteral::Type &type)
	{
		switch (type)
		{
		case NumericLiteral::Type::Signed:
			ostream << "Signed";
			break;
		case NumericLiteral::Type::Unsigned:
			ostream << "Unsigned";
			break;
		default:
			break;
		}

		return ostream;
	}
} // namespace Hyper
