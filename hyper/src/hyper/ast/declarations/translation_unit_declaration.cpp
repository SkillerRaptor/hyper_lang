/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/declarations/translation_unit_declaration.hpp"

namespace hyper
{
	TranslationUnitDeclaration::TranslationUnitDeclaration(
		SourceRange source_range,
		std::string file,
		std::vector<DeclarationPtr> declarations)
		: Declaration(source_range)
		, m_file(std::move(file))
		, m_declarations(std::move(declarations))
	{
	}

	void TranslationUnitDeclaration::collect_symbols(
		std::vector<Symbol> &symbols) const
	{
		for (const DeclarationPtr &declaration : m_declarations)
		{
			declaration->collect_symbols(symbols);
		}

		for (Symbol &symbol : symbols)
		{
			symbol.file = m_file;
		}
	}

	void TranslationUnitDeclaration::validate_scope(
		const ScopeValidator &scope_validator) const
	{
		for (const DeclarationPtr &declaration : m_declarations)
		{
			declaration->validate_scope(scope_validator);
		}
	}

	void TranslationUnitDeclaration::validate_type(
		TypeValidator &type_validator) const
	{
		for (const DeclarationPtr &declaration : m_declarations)
		{
			declaration->validate_type(type_validator);
		}
	}
} // namespace hyper
