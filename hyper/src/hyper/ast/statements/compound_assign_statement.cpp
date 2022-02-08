/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/statements/compound_assign_statement.hpp"

#include "hyper/ast/expression.hpp"
#include "hyper/validators/scope_validator.hpp"

namespace hyper
{
	CompoundAssignStatement::CompoundAssignStatement(
		SourceRange source_range,
		Identifier identifier,
		CompoundAssignStatement::Operation operation,
		ExpressionPtr expression)
		: Statement(source_range)
		, m_identifier(std::move(identifier))
		, m_operation(operation)
		, m_expression(std::move(expression))
	{
		(void) m_operation;
	}

	void CompoundAssignStatement::collect_symbols(
		std::vector<Symbol> &symbols) const
	{
		m_expression->collect_symbols(symbols);
	}

	void CompoundAssignStatement::validate_scope(
		const ScopeValidator &scope_validator) const
	{
		if (!scope_validator.is_symbol_present(m_identifier))
		{
			scope_validator.report_undeclared_identifier(m_identifier);
		}

		m_expression->validate_scope(scope_validator);
	}

	void CompoundAssignStatement::validate_type(
		TypeValidator &type_validator) const
	{
		m_expression->validate_type(type_validator);
	}
} // namespace hyper
