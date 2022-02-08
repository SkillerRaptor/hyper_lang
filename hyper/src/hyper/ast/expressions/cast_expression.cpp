/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/expressions/cast_expression.hpp"

#include "hyper/validators/type_validator.hpp"

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

	void CastExpression::collect_symbols(std::vector<Symbol> &symbols) const
	{
		m_expression->collect_symbols(symbols);
	}

	void CastExpression::validate_scope(
		const ScopeValidator &scope_validator) const
	{
		m_expression->validate_scope(scope_validator);
	}

	void CastExpression::validate_type(TypeValidator &type_validator) const
	{
		m_expression->validate_type(type_validator);

		type_validator.set_current_data_type(m_type);
	}
} // namespace hyper
