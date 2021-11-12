/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/WhileStatement.hpp"

#include "Hyper/Ast/Expressions/Expression.hpp"
#include "Hyper/Generators/Generator.hpp"
#include "Hyper/Logger.hpp"

namespace Hyper
{
	WhileStatement::WhileStatement(ExpressionPtr condition, StatementPtr body)
		: m_condition(std::move(condition))
		, m_body(std::move(body))
	{
	}

	void WhileStatement::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void WhileStatement::dump(size_t indent) const
	{
		AstNode::indent(indent);
		Logger::raw("{}\n", class_name());

		m_condition->dump(indent + 1);
		m_body->dump(indent + 1);
	}

	AstNode::Category WhileStatement::class_category() const noexcept
	{
		return AstNode::Category::WhileStatement;
	}

	std::string_view WhileStatement::class_name() const noexcept
	{
		return "WhileStatement";
	}

	const ExpressionPtr &WhileStatement::condition() const
	{
		return m_condition;
	}

	const StatementPtr &WhileStatement::body() const
	{
		return m_body;
	}
} // namespace Hyper
