/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/WhileStatement.hpp"

#include "Hyper/Ast/Expressions/Expression.hpp"
#include "Hyper/Generators/Generator.hpp"

#include <iostream>

namespace Hyper
{
	WhileStatement::WhileStatement(
		std::unique_ptr<Expression> condition,
		std::unique_ptr<Statement> body)
		: m_condition(std::move(condition))
		, m_body(std::move(body))
	{
	}

	void WhileStatement::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void WhileStatement::dump(size_t indent) const
	{
		AstNode::dump(indent);

		std::cout << '\n';

		m_condition->dump(indent + 1);
		m_body->dump(indent + 1);
	}

	const char *WhileStatement::class_name() const noexcept
	{
		return "WhileStatement";
	}

	const std::unique_ptr<Expression> &WhileStatement::condition() const
	{
		return m_condition;
	}

	const std::unique_ptr<Statement> &WhileStatement::body() const
	{
		return m_body;
	}
} // namespace Hyper
