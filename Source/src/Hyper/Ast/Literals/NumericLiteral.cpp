/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Literals/NumericLiteral.hpp"

#include "Hyper/Ast/AstFormatter.hpp"
#include "Hyper/Generator.hpp"
#include "Hyper/Logger.hpp"

#include <limits>

namespace Hyper
{
	NumericLiteral::NumericLiteral(NumericLiteral::CreateInfo create_info)
		: m_value(create_info.value)
	{
	}

	void NumericLiteral::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void NumericLiteral::dump(
		std::string_view file,
		const std::string &prefix,
		bool is_self_last) const
	{
		const std::string current_prefix =
			AstFormatter::format_prefix(*this, prefix, is_self_last);
		Logger::file_info(file, "{}", current_prefix);
	}

	AstNode::Category NumericLiteral::class_category() const noexcept
	{
		return AstNode::Category::NumericLiteral;
	}

	std::string_view NumericLiteral::class_name() const noexcept
	{
		return "NumericLiteral";
	}

	std::string NumericLiteral::class_description() const
	{
		const std::string value =
			AstFormatter::format_member("value", m_value);

		return Formatter::format("({})", value);
	}

	std::string NumericLiteral::value() const
	{
		return m_value;
	}
} // namespace Hyper
