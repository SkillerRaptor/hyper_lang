/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/declarations/static_declaration.hpp"

namespace hyper
{
	StaticDeclaration::StaticDeclaration(
		SourceRange source_range,
		Declaration *declaration)
		: Declaration(source_range)
		, m_declaration(declaration)
	{
	}

	StaticDeclaration::~StaticDeclaration()
	{
		delete m_declaration;
	}

	const Declaration *StaticDeclaration::declaration() const
	{
		return m_declaration;
	}
} // namespace hyper
