/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/declarations/export_declaration.hpp"

namespace hyper
{
	ExportDeclaration::ExportDeclaration(
		SourceRange source_range,
		Statement *statement)
		: Declaration(source_range)
		, m_statement(statement)
	{
	}

	ExportDeclaration::~ExportDeclaration()
	{
		delete m_statement;
	}

	const Statement *ExportDeclaration::statement() const
	{
		return m_statement;
	}
} // namespace hyper
