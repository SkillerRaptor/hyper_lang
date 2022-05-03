/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/statements/print_statement.hpp"

#include "hyper/ast/expressions/expression.hpp"

namespace hyper
{
	PrintStatement::PrintStatement(
		SourceRange source_range,
		Expression *expression)
		: Statement(source_range)
		, m_expression(std::move(expression))
	{
	}

	PrintStatement::~PrintStatement()
	{
		delete m_expression;
	}

	const Expression *PrintStatement::expression() const
	{
		return m_expression;
	}
} // namespace hyper
