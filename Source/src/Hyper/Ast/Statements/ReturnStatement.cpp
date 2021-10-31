/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/ReturnStatement.hpp"

#include "Hyper/Ast/Expressions/Expression.hpp"
#include "Hyper/Generators/Generator.hpp"

#include <iostream>

namespace Hyper
{
	ReturnStatement::ReturnStatement(std::unique_ptr<Expression> expression)
		: m_expression(std::move(expression))
	{
	}

	void ReturnStatement::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void ReturnStatement::dump(size_t indent) const
	{
		AstNode::dump(indent);

		std::cout << '\n';

		m_expression->dump(indent + 1);
	}

	const char *ReturnStatement::node_name() const noexcept
	{
		return "ReturnStatement";
	}

	AstNode::Category ReturnStatement::node_category() const noexcept
	{
		return Category::ReturnStatement;
	}

	const std::unique_ptr<Expression> &ReturnStatement::expression() const
	{
		return m_expression;
	}
} // namespace Hyper
