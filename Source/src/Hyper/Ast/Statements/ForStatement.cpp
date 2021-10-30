/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/ForStatement.hpp"

#include "Hyper/Ast/Expressions/Expression.hpp"
#include "Hyper/Generators/Generator.hpp"

#include <iostream>

namespace Hyper
{
	ForStatement::ForStatement(
		std::unique_ptr<Statement> pre_operation,
		std::unique_ptr<Expression> condition,
		std::unique_ptr<Statement> post_operation,
		std::unique_ptr<Statement> body)
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
		AstNode::dump(indent);

		std::cout << '\n';

		m_pre_operation->dump(indent + 1);
		m_condition->dump(indent + 1);
		m_post_operation->dump(indent + 1);
		m_body->dump(indent + 1);
	}

	const char *ForStatement::class_name() const noexcept
	{
		return "ForStatement";
	}

	const std::unique_ptr<Statement> &ForStatement::pre_operation() const
	{
		return m_pre_operation;
	}

	const std::unique_ptr<Expression> &ForStatement::condition() const
	{
		return m_condition;
	}

	const std::unique_ptr<Statement> &ForStatement::post_operation() const
	{
		return m_post_operation;
	}

	const std::unique_ptr<Statement> &ForStatement::body() const
	{
		return m_body;
	}
} // namespace Hyper
