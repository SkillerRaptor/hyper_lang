/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/declarations/module_declaration.hpp"

namespace hyper
{
	ModuleDeclaration::ModuleDeclaration(
		SourceRange source_range,
		Identifier identifier,
		std::vector<Declaration *> declarations)
		: Declaration(source_range)
		, m_identifier(identifier)
		, m_declarations(declarations)
	{
	}

	ModuleDeclaration::~ModuleDeclaration()
	{
		for (const Declaration *declaration : m_declarations)
		{
			delete declaration;
		}
	}

	Identifier ModuleDeclaration::identifier() const
	{
		return m_identifier;
	}

	std::span<Declaration *const> ModuleDeclaration::declarations() const
	{
		return m_declarations;
	}
} // namespace hyper
