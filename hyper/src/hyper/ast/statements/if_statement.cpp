/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/statements/if_statement.hpp"

#include "hyper/ast/expression.hpp"

namespace hyper
{
	IfStatement::IfStatement(
		SourceRange source_range,
		ExpressionPtr condition,
		StatementPtr true_body,
		StatementPtr false_body)
		: Statement(source_range)
		, m_condition(std::move(condition))
		, m_true_body(std::move(true_body))
		, m_false_body(std::move(false_body))
	{
	}

	void IfStatement::validate_scope(const ScopeValidator &scope_validator) const
	{
		(void) scope_validator;
	}

	void IfStatement::validate_type(const TypeValidator &type_validator) const
	{
		(void) type_validator;
	}
} // namespace hyper
