/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/IfStatement.hpp"

#include "Hyper/Generators/Generator.hpp"
#include "Hyper/Ast/Expressions/Expression.hpp"

#include <iostream>

namespace Hyper
{
	IfStatement::IfStatement(
		std::unique_ptr<Expression> condition,
		std::unique_ptr<Statement> true_branch,
		std::unique_ptr<Statement> false_branch)
		: m_condition(std::move(condition))
		, m_true_branch(std::move(true_branch))
		, m_false_branch(std::move(false_branch))
	{
	}

	void IfStatement::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void IfStatement::dump(size_t indent) const
	{
		AstNode::dump(indent);

		std::cout << '\n';

		m_condition->dump(indent + 1);
		m_true_branch->dump(indent + 1);

		if (m_false_branch != nullptr)
		{
			m_false_branch->dump(indent + 1);
		}
	}
	
	const char *IfStatement::node_name() const noexcept
	{
		return "IfStatement";
	}

	AstNode::Category IfStatement::node_category() const noexcept
	{
		return Category::IfStatement;
	}

	const std::unique_ptr<Expression> &IfStatement::condition() const
	{
		return m_condition;
	}

	const std::unique_ptr<Statement> &IfStatement::true_branch() const
	{
		return m_true_branch;
	}

	const std::unique_ptr<Statement> &IfStatement::false_branch() const
	{
		return m_false_branch;
	}
} // namespace Hyper
