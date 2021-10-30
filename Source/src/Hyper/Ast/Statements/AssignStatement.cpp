/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/AssignStatement.hpp"

#include "Hyper/Ast/Expressions/Expression.hpp"
#include "Hyper/Generators/Generator.hpp"

#include <iostream>

namespace Hyper
{
	AssignStatement::AssignStatement(
		std::string identifier,
		std::unique_ptr<Expression> expression)
		: m_identifier(std::move(identifier))
		, m_expression(std::move(expression))
	{
	}

	void AssignStatement::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void AssignStatement::dump(size_t indent) const
	{
		AstNode::dump(indent);

		std::cout << "identifier = " << m_identifier;
		std::cout << '\n';

		m_expression->dump(indent + 1);
	}

	const char *AssignStatement::class_name() const noexcept
	{
		return "AssignStatement";
	}

	std::string AssignStatement::identifier() const
	{
		return m_identifier;
	}

	const std::unique_ptr<Expression> &AssignStatement::expression() const
	{
		return m_expression;
	}
} // namespace Hyper
