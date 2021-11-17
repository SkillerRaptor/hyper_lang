/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/CompoundStatement.hpp"

#include "Hyper/Ast/AstFormatter.hpp"
#include "Hyper/Generators/Generator.hpp"
#include "Hyper/Logger.hpp"

namespace Hyper
{
	CompoundStatement::CompoundStatement(
		CompoundStatement::CreateInfo create_info)
		: m_statements(std::move(create_info.statements))
	{
	}

	void CompoundStatement::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void CompoundStatement::dump(const std::string &prefix, bool is_self_last)
		const
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

	AstNode::Category CompoundStatement::class_category() const noexcept
	{
		return AstNode::Category::CompoundStatement;
	}

	std::string CompoundStatement::class_description() const
	{
		return "";
	}

	std::string_view CompoundStatement::class_name() const noexcept
	{
		return "CompoundStatement";
	}

	const StatementList &CompoundStatement::statements() const
	{
		return m_statements;
	}
} // namespace Hyper
