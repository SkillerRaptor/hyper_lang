/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/CompoundStatement.hpp"

namespace Hyper
{
	CompoundStatement::CompoundStatement(
		std::vector<std::unique_ptr<Statement>> statements)
		: m_statements(std::move(statements))
	{
	}

	void CompoundStatement::dump(std::string_view prefix, bool self_last) const
	{
		AstNode::dump_self(prefix, self_last);

		for (const auto &statement : m_statements)
		{
			const bool node_last = &statement == &m_statements.back();
			AstNode::dump_node(*statement, prefix, self_last, node_last);
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
} // namespace Hyper
