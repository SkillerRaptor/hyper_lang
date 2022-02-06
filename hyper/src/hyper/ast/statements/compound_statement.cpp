/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/statements/compound_statement.hpp"

namespace hyper
{
	CompoundStatement::CompoundStatement(
		SourceRange source_range,
		std::vector<StatementPtr> statements)
		: Statement(source_range)
		, m_statements(std::move(statements))
	{
	}

	void CompoundStatement::collect_symbols(std::vector<Symbol> &symbols) const
	{
		for (const StatementPtr &statement : m_statements)
		{
			statement->collect_symbols(symbols);
		}
	}

	void CompoundStatement::validate_scope(
		const ScopeValidator &scope_validator) const
	{
		for (const StatementPtr &statement : m_statements)
		{
			statement->validate_scope(scope_validator);
		}
	}

	void CompoundStatement::validate_type(TypeValidator &type_validator) const
	{
		for (const StatementPtr &statement : m_statements)
		{
			statement->validate_type(type_validator);
		}
	}
} // namespace hyper
