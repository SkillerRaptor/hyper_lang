/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/PrintStatement.hpp"

#include "Hyper/Ast/Expressions/Expression.hpp"
#include "Hyper/Generators/Generator.hpp"
#include "Hyper/Logger.hpp"

namespace Hyper
{
	PrintStatement::PrintStatement(ExpressionPtr expression)
		: m_expression(std::move(expression))
	{
	}

	void PrintStatement::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void PrintStatement::dump(const std::string &prefix, bool last) const
	{
		AstNode::print_prefix(prefix, last);

		Logger::raw("\n");

		AstNode::print_next_node(*m_expression, prefix, last, true);
	}

	AstNode::Category PrintStatement::class_category() const noexcept
	{
		return AstNode::Category::PrintStatement;
	}

	std::string_view PrintStatement::class_name() const noexcept
	{
		return "PrintStatement";
	}

	const ExpressionPtr &PrintStatement::expression() const
	{
		return m_expression;
	}
} // namespace Hyper
