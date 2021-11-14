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

	void WhileStatement::dump(const std::string &prefix, bool last) const
	{
		AstNode::print_prefix(prefix, last);
		
		Logger::raw("\n");
		
		AstNode::print_next_node(*m_condition, prefix, last, false);
		AstNode::print_next_node(*m_body, prefix, last, true);
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
