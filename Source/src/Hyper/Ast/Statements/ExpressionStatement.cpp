/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/ExpressionStatement.hpp"

#include "Hyper/Ast/AstFormatter.hpp"
#include "Hyper/Ast/Expressions/Expression.hpp"
#include "Hyper/Generators/Generator.hpp"
#include "Hyper/Logger.hpp"

namespace Hyper
{
	ExpressionStatement::ExpressionStatement(
		ExpressionStatement::CreateInfo create_info)
		: m_expression(std::move(create_info.expression))
	{
	}

	void ExpressionStatement::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void ExpressionStatement::dump(const std::string &prefix, bool is_self_last)
		const
	{
		const std::string current_prefix =
			AstFormatter::format_prefix(*this, prefix, is_self_last);
		Logger::debug("{}", current_prefix);

		AstNode::dump_next_node(*m_expression, prefix, is_self_last, true);
	}

	AstNode::Category ExpressionStatement::class_category() const noexcept
	{
		return AstNode::Category::ExpressionStatement;
	}

	std::string_view ExpressionStatement::class_name() const noexcept
	{
		return "ExpressionStatement";
	}

	std::string ExpressionStatement::class_description() const
	{
		return "";
	}

	const ExpressionPtr &ExpressionStatement::expression() const
	{
		return m_expression;
	}
} // namespace Hyper
