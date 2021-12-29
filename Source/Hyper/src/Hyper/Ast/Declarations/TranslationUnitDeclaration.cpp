/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Declarations/TranslationUnitDeclaration.hpp"

#include "Hyper/Logger.hpp"

namespace Hyper
{
	TranslationUnitDeclaration::TranslationUnitDeclaration(
		std::string file,
		std::vector<std::unique_ptr<Declaration>> declarations)
		: m_file(std::move(file))
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

	AstNode::Category TranslationUnitDeclaration::class_category() const noexcept
	{
		return AstNode::Category::TranslationUnitDeclaration;
	}

	std::string_view TranslationUnitDeclaration::class_name() const noexcept
	{
		return "TranslationUnitDeclaration";
	}
} // namespace Hyper
