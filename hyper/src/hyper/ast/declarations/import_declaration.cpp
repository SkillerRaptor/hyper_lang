/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/declarations/import_declaration.hpp"

namespace hyper
{
	ImportDeclaration::ImportDeclaration(
		SourceRange source_range,
		std::string module_name)
		: Declaration(source_range)
		, m_module_name(std::move(module_name))
	{
	}

	std::string_view ImportDeclaration::module_name() const
	{
		return m_module_name;
	}
} // namespace hyper
