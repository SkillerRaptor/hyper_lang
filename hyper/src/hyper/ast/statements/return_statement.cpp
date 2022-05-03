/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/statements/return_statement.hpp"

#include "hyper/ast/expressions/expression.hpp"

namespace hyper
{
	ReturnStatement::ReturnStatement(
		SourceRange source_range,
		Expression *expression)
		: Statement(source_range)
		, m_expression(std::move(expression))
	{
	}

	ReturnStatement::~ReturnStatement()
	{
		delete m_expression;
	}

	const Expression *ReturnStatement::expression() const
	{
		return m_expression;
	}
} // namespace hyper
