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

	void CompoundStatement::dump(size_t indent) const
	{
		AstNode::indent(indent);
		Logger::raw("{}\n", class_name());

		for (const StatementPtr &statement : m_statements)
		{
			statement->dump(indent + 1);
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
