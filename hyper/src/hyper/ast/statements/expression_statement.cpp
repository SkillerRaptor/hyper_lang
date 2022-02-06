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

	void ExpressionStatement::collect_symbols(std::vector<Symbol> &symbol) const
	{
		m_expression->collect_symbols(symbol);
	}

	void ExpressionStatement::validate_scope(
		const ScopeValidator &scope_validator) const
	{
		m_expression->validate_scope(scope_validator);
	}

	void ExpressionStatement::validate_type(TypeValidator &type_validator) const
	{
		m_expression->validate_type(type_validator);
	}
} // namespace hyper
