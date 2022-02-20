/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/declarations/public_declaration.hpp"

namespace hyper
{
	PublicDeclaration::PublicDeclaration(
		SourceRange source_range,
		Statement *statement)
		: Declaration(source_range)
		, m_statement(statement)
	{
	}

	PublicDeclaration::~PublicDeclaration()
	{
		delete m_statement;
	}

	const Statement *PublicDeclaration::statement() const
	{
		return m_statement;
	}
} // namespace hyper
