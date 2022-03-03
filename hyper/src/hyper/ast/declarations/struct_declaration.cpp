/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/declarations/struct_declaration.hpp"

namespace hyper
{
	StructDeclaration::StructDeclaration(
		SourceRange source_range,
		Identifier identifier,
		std::vector<Declaration *> declarations)
		: Declaration(source_range)
		, m_identifier(identifier)
		, m_declarations(declarations)
	{
	}

	StructDeclaration::~StructDeclaration()
	{
		for (const Declaration *declaration : m_declarations)
		{
			delete declaration;
		}
	}

	Identifier StructDeclaration::identifier() const
	{
		return m_identifier;
	}

	std::span<Declaration *const> StructDeclaration::declarations() const
	{
		return m_declarations;
	}
} // namespace hyper
