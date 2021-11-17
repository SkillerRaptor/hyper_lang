/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Literals/StringLiteral.hpp"

#include "Hyper/Ast/AstFormatter.hpp"
#include "Hyper/Generators/Generator.hpp"
#include "Hyper/Logger.hpp"

namespace Hyper
{
	StringLiteral::StringLiteral(StringLiteral::CreateInfo create_info)
		: m_value(std::move(create_info.value))
	{
	}

	void StringLiteral::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void StringLiteral::dump(const std::string &prefix, bool is_self_last) const
	{
		const std::string current_prefix =
			AstFormatter::format_prefix(*this, prefix, is_self_last);
		Logger::debug("{}", current_prefix);
	}

	AstNode::Category StringLiteral::class_category() const noexcept
	{
		return AstNode::Category::StringLiteral;
	}

	std::string_view StringLiteral::class_name() const noexcept
	{
		return "StringLiteral";
	}

	std::string StringLiteral::class_description() const
	{
		const std::string value = AstFormatter::format_member("value", m_value);

		return Formatter::format("({})", value);
	}

	std::string StringLiteral::value() const noexcept
	{
		return m_value;
	}
} // namespace Hyper
