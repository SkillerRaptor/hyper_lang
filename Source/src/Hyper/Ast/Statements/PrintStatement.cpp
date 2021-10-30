/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/PrintStatement.hpp"

#include "Hyper/Generators/Generator.hpp"
#include "Hyper/Ast/Expressions/Expression.hpp"

#include <iostream>

namespace Hyper
{
	PrintStatement::PrintStatement(std::unique_ptr<Expression> expression)
		: m_expression(std::move(expression))
	{
	}

	void PrintStatement::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void PrintStatement::dump(size_t indent) const
	{
		AstNode::dump(indent);

		std::cout << '\n';

		m_expression->dump(indent + 1);
	}
	
	const char *PrintStatement::node_name() const noexcept
	{
		return "FunctionDeclaration";
	}

	AstNode::Category PrintStatement::node_category() const noexcept
	{
		return Category::PrintStatement;
	}

	const std::unique_ptr<Expression> &PrintStatement::expression() const
	{
		return m_expression;
	}
} // namespace Hyper
