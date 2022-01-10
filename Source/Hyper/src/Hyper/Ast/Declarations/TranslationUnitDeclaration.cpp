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
		SourceRange range,
		std::string file,
		DeclarationList declarations)
		: Declaration(range)
		, m_file(std::move(file))
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

	std::string TranslationUnitDeclaration::file() const
	{
		return m_file;
	}

	const DeclarationList &TranslationUnitDeclaration::declarations() const
	{
		return m_declarations;
	}
} // namespace Hyper
