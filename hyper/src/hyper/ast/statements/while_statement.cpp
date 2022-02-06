/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/statements/while_statement.hpp"

#include "hyper/ast/expression.hpp"

namespace hyper
{
	WhileStatement::WhileStatement(
		SourceRange source_range,
		ExpressionPtr condition,
		StatementPtr body)
		: Statement(source_range)
		, m_condition(std::move(condition))
		, m_body(std::move(body))
	{
	}

	void WhileStatement::collect_symbols(std::vector<Symbol> &symbol) const
	{
		m_condition->collect_symbols(symbol);
		m_body->collect_symbols(symbol);
	}

	void WhileStatement::validate_scope(
		const ScopeValidator &scope_validator) const
	{
		m_condition->validate_scope(scope_validator);
		m_body->validate_scope(scope_validator);
	}

	void WhileStatement::validate_type(TypeValidator &type_validator) const
	{
		m_condition->validate_type(type_validator);
		m_body->validate_type(type_validator);
	}
} // namespace hyper
