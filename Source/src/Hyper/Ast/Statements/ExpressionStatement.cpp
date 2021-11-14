/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/ExpressionStatement.hpp"

#include "Hyper/Ast/Expressions/Expression.hpp"
#include "Hyper/Generators/Generator.hpp"
#include "Hyper/Logger.hpp"

namespace Hyper
{
	ExpressionStatement::ExpressionStatement(ExpressionPtr expression)
		: m_expression(std::move(expression))
	{
	}

	void ExpressionStatement::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void ExpressionStatement::dump(const std::string &prefix, bool last) const
	{
		AstNode::print_prefix(prefix, last);

		Logger::raw("\n");

		AstNode::print_next_node(*m_expression, prefix, last, true);
	}

	AstNode::Category ExpressionStatement::class_category() const noexcept
	{
		return AstNode::Category::ExpressionStatement;
	}

	std::string_view ExpressionStatement::class_name() const noexcept
	{
		return "ExpressionStatement";
	}

	const ExpressionPtr &ExpressionStatement::expression() const
	{
		return m_expression;
	}
} // namespace Hyper
