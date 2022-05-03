/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/declarations/import_declaration.hpp"

namespace hyper
{
	ImportDeclaration::ImportDeclaration(
		SourceRange source_range,
		Identifier identifier,
		std::string file_name)
		: Declaration(source_range)
		, m_identifier(identifier)
		, m_file_name(file_name)
	{
	}

	Identifier ImportDeclaration::identifier() const
	{
		return m_identifier;
	}

	std::string_view ImportDeclaration::file_name() const
	{
		return m_file_name;
	}
} // namespace hyper
