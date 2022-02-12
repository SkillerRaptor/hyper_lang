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
		std::vector<Statement *> statements)
		: Statement(source_range)
		, m_statements(std::move(statements))
	{
	}

	CompoundStatement::~CompoundStatement()
	{
		for (const Statement *statement : m_statements)
		{
			delete statement;
		}
	}

	std::span<const Statement *const> CompoundStatement::statements() const
	{
		return m_statements;
	}
} // namespace hyper
