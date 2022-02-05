/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/statements/expression_statement.hpp"

#include "hyper/ast/expression.hpp"

namespace hyper
{
	ExpressionStatement::ExpressionStatement(
		SourceRange source_range,
		ExpressionPtr expression)
		: Statement(source_range)
		, m_expression(std::move(expression))
	{
	}

	void ExpressionStatement::validate_scope(
		const ScopeValidator &scope_validator) const
	{
		(void) scope_validator;
	}

	void ExpressionStatement::validate_type(
		const TypeValidator &type_validator) const
	{
		(void) type_validator;
	}
} // namespace hyper
