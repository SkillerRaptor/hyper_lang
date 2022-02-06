/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/expressions/conditional_expression.hpp"

namespace hyper
{
	ConditionalExpression::ConditionalExpression(
		SourceRange source_range,
		ExpressionPtr condition,
		ExpressionPtr true_expression,
		ExpressionPtr false_expression)
		: Expression(source_range)
		, m_condition(std::move(condition))
		, m_true_expression(std::move(true_expression))
		, m_false_expression(std::move(false_expression))
	{
	}

	void ConditionalExpression::collect_symbols(
		std::vector<Symbol> &symbols) const
	{
		m_condition->collect_symbols(symbols);
		m_true_expression->collect_symbols(symbols);
		m_false_expression->collect_symbols(symbols);
	}

	void ConditionalExpression::validate_scope(
		const ScopeValidator &scope_validator) const
	{
		m_condition->validate_scope(scope_validator);
		m_true_expression->validate_scope(scope_validator);
		m_false_expression->validate_scope(scope_validator);
	}

	void ConditionalExpression::validate_type(TypeValidator &type_validator) const
	{
		m_condition->validate_type(type_validator);
		m_true_expression->validate_type(type_validator);
		m_false_expression->validate_type(type_validator);
	}
} // namespace hyper
