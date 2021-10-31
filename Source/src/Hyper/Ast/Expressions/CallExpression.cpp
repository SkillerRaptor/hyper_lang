/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Expressions/CallExpression.hpp"

#include "Hyper/Generators/Generator.hpp"

#include <iostream>

namespace Hyper
{
	CallExpression::CallExpression(
		std::string identifier,
		std::unique_ptr<Expression> expression)
		: m_identifier(std::move(identifier))
		, m_expression(std::move(expression))
	{
	}

	void CallExpression::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void CallExpression::dump(size_t indent) const
	{
		AstNode::dump(indent);

		std::cout << "identifier = " << m_identifier;
		std::cout << '\n';

		m_expression->dump(indent + 1);
	}

	const char *CallExpression::node_name() const noexcept
	{
		return "CallExpression";
	}

	AstNode::Category CallExpression::node_category() const noexcept
	{
		return Category::CallExpression;
	}

	std::string CallExpression::identifier() const
	{
		return m_identifier;
	}

	const std::unique_ptr<Expression> &CallExpression::expression() const
	{
		return m_expression;
	}
} // namespace Hyper
