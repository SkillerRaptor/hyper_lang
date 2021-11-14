/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Literals/StringLiteral.hpp"

#include "Hyper/Generators/Generator.hpp"
#include "Hyper/Logger.hpp"

namespace Hyper
{
	StringLiteral::StringLiteral(std::string value)
		: m_value(std::move(value))
	{
	}

	void StringLiteral::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void StringLiteral::dump(const std::string &prefix, bool last) const
	{
		AstNode::print_prefix(prefix, last);

		Logger::raw("({})\n", AstNode::format_member("value", m_value));
	}

	AstNode::Category StringLiteral::class_category() const noexcept
	{
		return AstNode::Category::StringLiteral;
	}

	std::string_view StringLiteral::class_name() const noexcept
	{
		return "StringLiteral";
	}

	std::string StringLiteral::value() const noexcept
	{
		return m_value;
	}
} // namespace Hyper
