/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/statements/return_statement.hpp"

#include "hyper/ast/expression.hpp"

namespace hyper
{
	ReturnStatement::ReturnStatement(
		SourceRange source_range,
		ExpressionPtr expression)
		: Statement(source_range)
		, m_expression(std::move(expression))
	{
	}

	void ReturnStatement::validate_scope(
		const ScopeValidator &scope_validator) const
	{
		(void) scope_validator;
	}

	void ReturnStatement::validate_type(const TypeValidator &type_validator) const
	{
		(void) type_validator;
	}
} // namespace hyper
