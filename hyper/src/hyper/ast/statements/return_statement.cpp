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

	void ReturnStatement::collect_symbols(std::vector<Symbol> &symbol) const
	{
		if (m_expression)
		{
			m_expression->collect_symbols(symbol);
		}
	}

	void ReturnStatement::validate_scope(
		const ScopeValidator &scope_validator) const
	{
		if (m_expression)
		{
			m_expression->validate_scope(scope_validator);
		}
	}

	void ReturnStatement::validate_type(TypeValidator &type_validator) const
	{
		if (m_expression)
		{
			m_expression->validate_type(type_validator);
		}
	}
} // namespace hyper
