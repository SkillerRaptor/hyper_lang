/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/declarations/translation_unit_declaration.hpp"

namespace hyper
{
	TranslationUnitDeclaration::TranslationUnitDeclaration(
		SourceRange source_range,
		std::string file,
		std::vector<Declaration *> declarations)
		: Declaration(source_range)
		, m_file(std::move(file))
		, m_declarations(std::move(declarations))
	{
	}

	TranslationUnitDeclaration::~TranslationUnitDeclaration()
	{
		for (const Declaration *declaration : m_declarations)
		{
			delete declaration;
		}
	}

	std::string_view TranslationUnitDeclaration::file() const
	{
		return m_file;
	}

	std::span<Declaration *const> TranslationUnitDeclaration::declarations()
		const
	{
		return m_declarations;
	}
} // namespace hyper
