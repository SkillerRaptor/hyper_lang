/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/expressions/unary_expression.hpp"

namespace hyper
{
	UnaryExpression::UnaryExpression(
		SourceRange source_range,
		UnaryExpression::Operation operation,
		ExpressionPtr expression)
		: Expression(source_range)
		, m_operation(operation)
		, m_expression(std::move(expression))
	{
	}

	void UnaryExpression::validate_scope(
		const ScopeValidator &scope_validator) const
	{
		(void) scope_validator;
	}

	void UnaryExpression::validate_type(const TypeValidator &type_validator) const
	{
		(void) type_validator;
	}
} // namespace hyper
