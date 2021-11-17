/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Expressions/IdentifierExpression.hpp"

#include "Hyper/Ast/AstFormatter.hpp"
#include "Hyper/Generators/Generator.hpp"
#include "Hyper/Logger.hpp"

namespace Hyper
{
	IdentifierExpression::IdentifierExpression(
		IdentifierExpression::CreateInfo create_info)
		: m_identifier(std::move(create_info.identifier))
	{
	}

	void IdentifierExpression::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void IdentifierExpression::dump(const std::string &prefix, bool is_self_last)
		const
	{
		const std::string current_prefix =
			AstFormatter::format_prefix(*this, prefix, is_self_last);
		Logger::debug("{}", current_prefix);
	}

	AstNode::Category IdentifierExpression::class_category() const noexcept
	{
		return AstNode::Category::IdentifierExpression;
	}

	std::string IdentifierExpression::class_description() const
	{
		const std::string identifier =
			AstFormatter::format_member("identifier", m_identifier);

		return Formatter::format("({})", identifier);
	}

	std::string_view IdentifierExpression::class_name() const noexcept
	{
		return "IdentifierExpression";
	}

	std::string IdentifierExpression::identifier() const
	{
		return m_identifier;
	}
} // namespace Hyper
