/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/statements/if_statement.hpp"

#include "hyper/ast/expression.hpp"

namespace hyper
{
	IfStatement::IfStatement(
		SourceRange source_range,
		ExpressionPtr condition,
		StatementPtr true_body,
		StatementPtr false_body)
		: Statement(source_range)
		, m_condition(std::move(condition))
		, m_true_body(std::move(true_body))
		, m_false_body(std::move(false_body))
	{
	}

	void IfStatement::collect_symbols(std::vector<Symbol> &symbol) const
	{
		m_condition->collect_symbols(symbol);
		m_true_body->collect_symbols(symbol);

		if (m_false_body)
		{
			m_false_body->collect_symbols(symbol);
		}
	}

	void IfStatement::validate_scope(const ScopeValidator &scope_validator) const
	{
		m_condition->validate_scope(scope_validator);
		m_true_body->validate_scope(scope_validator);

		if (m_false_body)
		{
			m_false_body->validate_scope(scope_validator);
		}
	}

	void IfStatement::validate_type(TypeValidator &type_validator) const
	{
		m_condition->validate_type(type_validator);
		m_true_body->validate_type(type_validator);

		if (m_false_body)
		{
			m_false_body->validate_type(type_validator);
		}
	}
} // namespace hyper
