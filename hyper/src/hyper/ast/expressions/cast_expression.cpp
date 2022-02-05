/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/expressions/cast_expression.hpp"

namespace hyper
{
	CastExpression::CastExpression(
		SourceRange source_range,
		ExpressionPtr expression,
		DataType type)
		: Expression(source_range)
		, m_expression(std::move(expression))
		, m_type(type)
	{
	}

	void CastExpression::validate_scope(
		const ScopeValidator &scope_validator) const
	{
		(void) scope_validator;
	}

	void CastExpression::validate_type(const TypeValidator &type_validator) const
	{
		(void) type_validator;
	}
} // namespace hyper
