/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/CompoundStatement.hpp"

#include "Hyper/Generators/Generator.hpp"
#include "Hyper/Logger.hpp"

namespace Hyper
{
	CompoundStatement::CompoundStatement(std::vector<StatementPtr> statements)
		: m_statements(std::move(statements))
	{
	}

	void CompoundStatement::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void CompoundStatement::dump(const std::string &prefix, bool last) const
	{
		AstNode::print_prefix(prefix, last);

		Logger::raw("\n");

		for (size_t i = 0; i < m_statements.size(); ++i)
		{
			const StatementPtr &statement = m_statements[i];
			AstNode::print_next_node(
				*statement, prefix, last, i == m_statements.size() - 1);
		}
	}

	AstNode::Category CompoundStatement::class_category() const noexcept
	{
		return AstNode::Category::CompoundStatement;
	}

	std::string_view CompoundStatement::class_name() const noexcept
	{
		return "CompoundStatement";
	}

	const std::vector<StatementPtr> &CompoundStatement::statements() const
	{
		return m_statements;
	}
} // namespace Hyper
