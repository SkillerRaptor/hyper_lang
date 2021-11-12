/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Declarations/TranslationUnitDeclaration.hpp"

#include "Hyper/Generators/Generator.hpp"
#include "Hyper/Logger.hpp"

namespace Hyper
{
	TranslationUnitDeclaration::TranslationUnitDeclaration(
		std::string file,
		std::vector<StatementPtr> statements)
		: m_file(std::move(file))
		, m_statements(std::move(statements))
	{
	}

	void TranslationUnitDeclaration::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void TranslationUnitDeclaration::dump(size_t indent) const
	{
		AstNode::indent(indent);
		Logger::raw("{} (file={})\n", class_name(), m_file);

		for (const StatementPtr &statement : m_statements)
		{
			statement->dump(indent + 1);
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

	std::string TranslationUnitDeclaration::file() const
	{
		return m_file;
	}

	const std::vector<StatementPtr> &TranslationUnitDeclaration::statements()
		const
	{
		return m_statements;
	}
} // namespace Hyper
