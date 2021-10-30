/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/CompoundStatement.hpp"

#include "Hyper/Generators/Generator.hpp"

#include <iostream>

namespace Hyper
{
	CompoundStatement::CompoundStatement(
		std::unique_ptr<Statement> left,
		std::unique_ptr<Statement> right)
		: m_left(std::move(left))
		, m_right(std::move(right))
	{
	}

	void CompoundStatement::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void CompoundStatement::dump(size_t indent) const
	{
		AstNode::dump(indent);

		std::cout << '\n';

		m_left->dump(indent + 1);
		m_right->dump(indent + 1);
	}
	
	const char *CompoundStatement::node_name() const noexcept
	{
		return "CompoundStatement";
	}

	AstNode::Category CompoundStatement::node_category() const noexcept
	{
		return Category::CompoundStatement;
	}

	const std::unique_ptr<Statement> &CompoundStatement::left() const
	{
		return m_left;
	}

	const std::unique_ptr<Statement> &CompoundStatement::right() const
	{
		return m_right;
	}
} // namespace Hyper
