/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/statements/if_statement.hpp"

#include "hyper/ast/expressions/expression.hpp"

namespace hyper
{
	IfStatement::IfStatement(
		SourceRange source_range,
		Expression *condition,
		Statement *true_body,
		Statement *false_body)
		: Statement(source_range)
		, m_condition(std::move(condition))
		, m_true_body(std::move(true_body))
		, m_false_body(std::move(false_body))
	{
	}

	IfStatement::~IfStatement()
	{
		delete m_condition;
		delete m_true_body;
		delete m_false_body;
	}

	const Expression *IfStatement::condition() const
	{
		return m_condition;
	}

	const Statement *IfStatement::true_body() const
	{
		return m_true_body;
	}

	const Statement *IfStatement::false_body() const
	{
		return m_false_body;
	}
} // namespace hyper
