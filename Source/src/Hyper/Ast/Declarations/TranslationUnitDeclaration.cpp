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

	void TranslationUnitDeclaration::dump(const std::string &prefix, bool last)
		const
	{
		AstNode::print_prefix(prefix, last);

		Logger::raw("(file={})\n", m_file);

		for (size_t i = 0; i < m_statements.size(); ++i)
		{
			const StatementPtr &statement = m_statements[i];
			AstNode::print_next_node(
				*statement, prefix, last, i == m_statements.size() - 1);
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
