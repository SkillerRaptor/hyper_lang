/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/statements/while_statement.hpp"

#include "hyper/ast/expression.hpp"

namespace hyper
{
	WhileStatement::WhileStatement(
		SourceRange source_range,
		ExpressionPtr condition,
		StatementPtr body)
		: Statement(source_range)
		, m_condition(std::move(condition))
		, m_body(std::move(body))
	{
	}

	void WhileStatement::validate_scope(
		const ScopeValidator &scope_validator) const
	{
		(void) scope_validator;
	}

	void WhileStatement::validate_type(const TypeValidator &type_validator) const
	{
		(void) type_validator;
	}
} // namespace hyper
