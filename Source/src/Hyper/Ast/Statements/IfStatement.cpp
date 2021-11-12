/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/IfStatement.hpp"

#include "Hyper/Ast/Expressions/Expression.hpp"
#include "Hyper/Generators/Generator.hpp"
#include "Hyper/Logger.hpp"

namespace Hyper
{
	IfStatement::IfStatement(
		ExpressionPtr condition,
		StatementPtr true_branch,
		StatementPtr false_branch)
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
		AstNode::indent(indent);
		Logger::raw("{}\n", class_name());

		m_condition->dump(indent + 1);
		m_true_branch->dump(indent + 1);

		if (m_false_branch != nullptr)
		{
			m_false_branch->dump(indent + 1);
		}
	}

	AstNode::Category IfStatement::class_category() const noexcept
	{
		return AstNode::Category::IfStatement;
	}

	std::string_view IfStatement::class_name() const noexcept
	{
		return "IfStatement";
	}

	const ExpressionPtr &IfStatement::condition() const
	{
		return m_condition;
	}

	const StatementPtr &IfStatement::true_branch() const
	{
		return m_true_branch;
	}

	const StatementPtr &IfStatement::false_branch() const
	{
		return m_false_branch;
	}
} // namespace Hyper
