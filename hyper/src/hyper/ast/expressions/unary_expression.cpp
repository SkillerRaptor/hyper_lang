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

	void UnaryExpression::collect_symbols(std::vector<Symbol> &symbols) const
	{
		m_expression->collect_symbols(symbols);
	}

	void UnaryExpression::validate_scope(
		const ScopeValidator &scope_validator) const
	{
		m_expression->validate_scope(scope_validator);
	}

	void UnaryExpression::validate_type(TypeValidator &type_validator) const
	{
		m_expression->validate_type(type_validator);
	}
} // namespace hyper
