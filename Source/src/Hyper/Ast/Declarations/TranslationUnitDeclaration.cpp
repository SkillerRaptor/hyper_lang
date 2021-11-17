/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Declarations/TranslationUnitDeclaration.hpp"

#include "Hyper/Ast/AstFormatter.hpp"
#include "Hyper/Generators/Generator.hpp"
#include "Hyper/Logger.hpp"

namespace Hyper
{
	TranslationUnitDeclaration::TranslationUnitDeclaration(
		TranslationUnitDeclaration::CreateInfo create_info)
		: m_file(std::move(create_info.file))
		, m_statements(std::move(create_info.statements))
	{
	}

	void TranslationUnitDeclaration::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void TranslationUnitDeclaration::dump(
		const std::string &prefix,
		bool is_self_last) const
	{
		const std::string current_prefix =
			AstFormatter::format_prefix(*this, prefix, is_self_last);
		Logger::debug("{}", current_prefix);

		for (const StatementPtr &statement : m_statements)
		{
			const bool is_node_last = &statement == &m_statements.back();
			AstNode::dump_next_node(*statement, prefix, is_self_last, is_node_last);
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

	std::string TranslationUnitDeclaration::class_description() const
	{
		const std::string file = AstFormatter::format_member("file", m_file);

		return Formatter::format("({})", file);
	}

	std::string TranslationUnitDeclaration::file() const
	{
		return m_file;
	}

	const StatementList &TranslationUnitDeclaration::statements() const
	{
		return m_statements;
	}
} // namespace Hyper
