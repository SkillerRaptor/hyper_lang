/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Declarations/TranslationUnitDeclaration.hpp"

#include "Hyper/Validator.hpp"

namespace Hyper
{
	TranslationUnitDeclaration::TranslationUnitDeclaration(
		std::string translation_unit,
		DeclarationList declarations)
		: m_translation_unit(std::move(translation_unit))
		, m_declarations(std::move(declarations))
	{
	}

	void TranslationUnitDeclaration::dump(std::string_view prefix, bool self_last)
		const
	{
		AstNode::dump_self(prefix, self_last);

		for (const auto &declaration : m_declarations)
		{
			const bool node_last = &declaration == &m_declarations.back();
			AstNode::dump_node(*declaration, prefix, self_last, node_last);
		}
	}

	void TranslationUnitDeclaration::validate(Validator &validator)
	{
		validator.accept(*this);
	}

	std::string TranslationUnitDeclaration::translation_unit() const
	{
		return m_translation_unit;
	}

	const DeclarationList &TranslationUnitDeclaration::declarations() const
	{
		return m_declarations;
	}
} // namespace Hyper
