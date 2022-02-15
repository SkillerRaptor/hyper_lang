/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/declarations/extern_declaration.hpp"

namespace hyper
{
	ExternDeclaration::ExternDeclaration(
		SourceRange source_range,
		Statement *statement)
		: Declaration(source_range)
		, m_statement(statement)
	{
	}

	ExternDeclaration::~ExternDeclaration()
	{
		delete m_statement;
	}

	const Statement *ExternDeclaration::statement() const
	{
		return m_statement;
	}
} // namespace hyper
