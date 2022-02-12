/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/statements/while_statement.hpp"

#include "hyper/ast/expressions/expression.hpp"

namespace hyper
{
	WhileStatement::WhileStatement(
		SourceRange source_range,
		Expression *condition,
		Statement *body)
		: Statement(source_range)
		, m_condition(std::move(condition))
		, m_body(std::move(body))
	{
	}

	WhileStatement::~WhileStatement()
	{
		delete m_condition;
		delete m_body;
	}

	const Expression *WhileStatement::condition() const
	{
		return m_condition;
	}

	const Statement *WhileStatement::body() const
	{
		return m_body;
	}
} // namespace hyper
