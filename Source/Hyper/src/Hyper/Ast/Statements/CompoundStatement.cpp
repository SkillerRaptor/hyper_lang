/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/CompoundStatement.hpp"

#include "Hyper/Validator.hpp"

namespace Hyper
{
	CompoundStatement::CompoundStatement(StatementList statements)
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

	void CompoundStatement::validate(Validator &validator)
	{
		validator.accept(*this);
	}

	const StatementList &CompoundStatement::statements() const
	{
		return m_statements;
	}
} // namespace Hyper
