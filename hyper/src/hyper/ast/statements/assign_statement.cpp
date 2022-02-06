/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/statements/assign_statement.hpp"

#include "hyper/ast/expression.hpp"
#include "hyper/scope_validator.hpp"

namespace hyper
{
	AssignStatement::AssignStatement(
		SourceRange source_range,
		Identifier identifier,
		ExpressionPtr expression)
		: Statement(source_range)
		, m_identifier(std::move(identifier))
		, m_expression(std::move(expression))
	{
	}

	void AssignStatement::collect_symbols(std::vector<Symbol> &symbols) const
	{
		m_expression->collect_symbols(symbols);
	}

	void AssignStatement::validate_scope(
		const ScopeValidator &scope_validator) const
	{
		if (!scope_validator.is_symbol_present(m_identifier))
		{
			scope_validator.report_undeclared_identifier(m_identifier);
		}

		m_expression->validate_scope(scope_validator);
	}

	void AssignStatement::validate_type(TypeValidator &type_validator) const
	{
		m_expression->validate_type(type_validator);
	}
} // namespace hyper
