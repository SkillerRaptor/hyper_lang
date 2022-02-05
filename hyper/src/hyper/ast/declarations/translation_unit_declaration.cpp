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

	void TranslationUnitDeclaration::validate_scope(
		const ScopeValidator &scope_validator) const
	{
		(void) scope_validator;
	}

	void TranslationUnitDeclaration::validate_type(
		const TypeValidator &type_validator) const
	{
		(void) type_validator;
	}
} // namespace hyper
