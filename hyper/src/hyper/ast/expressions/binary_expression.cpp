/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/expressions/binary_expression.hpp"

namespace hyper
{
	BinaryExpression::BinaryExpression(
		SourceRange source_range,
		Operation operation,
		ExpressionPtr left,
		ExpressionPtr right)
		: Expression(source_range)
		, m_operation(operation)
		, m_left(std::move(left))
		, m_right(std::move(right))
	{
	}

	void BinaryExpression::collect_symbols(std::vector<Symbol> &symbols) const
	{
		m_left->collect_symbols(symbols);
		m_right->collect_symbols(symbols);
	}

	void BinaryExpression::validate_scope(
		const ScopeValidator &scope_validator) const
	{
		m_left->validate_scope(scope_validator);
		m_right->validate_scope(scope_validator);
	}

	void BinaryExpression::validate_type(TypeValidator &type_validator) const
	{
		m_left->validate_type(type_validator);
		m_right->validate_type(type_validator);
	}
} // namespace hyper
