/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/ForStatement.hpp"

#include "Hyper/Ast/Expressions/Expression.hpp"
#include "Hyper/Generators/Generator.hpp"
#include "Hyper/Logger.hpp"

namespace Hyper
{
	ForStatement::ForStatement(
		StatementPtr pre_operation,
		ExpressionPtr condition,
		StatementPtr post_operation,
		StatementPtr body)
		: m_pre_operation(std::move(pre_operation))
		, m_condition(std::move(condition))
		, m_post_operation(std::move(post_operation))
		, m_body(std::move(body))
	{
	}

	void ForStatement::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void ForStatement::dump(size_t indent) const
	{
		AstNode::indent(indent);
		Logger::raw("{}\n", class_name());

		m_pre_operation->dump(indent + 1);
		m_condition->dump(indent + 1);
		m_post_operation->dump(indent + 1);
		m_body->dump(indent + 1);
	}

	AstNode::Category ForStatement::class_category() const noexcept
	{
		return AstNode::Category::ForStatement;
	}

	std::string_view ForStatement::class_name() const noexcept
	{
		return "ForStatement";
	}

	const StatementPtr &ForStatement::pre_operation() const
	{
		return m_pre_operation;
	}

	const ExpressionPtr &ForStatement::condition() const
	{
		return m_condition;
	}

	const StatementPtr &ForStatement::post_operation() const
	{
		return m_post_operation;
	}

	const StatementPtr &ForStatement::body() const
	{
		return m_body;
	}
} // namespace Hyper
