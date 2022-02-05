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

	void CompoundStatement::validate_scope(
		const ScopeValidator &scope_validator) const
	{
		(void) scope_validator;
	}

	void CompoundStatement::validate_type(
		const TypeValidator &type_validator) const
	{
		(void) type_validator;
	}
} // namespace hyper
