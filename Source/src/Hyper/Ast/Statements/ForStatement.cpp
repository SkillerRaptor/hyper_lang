/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/ForStatement.hpp"

#include "Hyper/Ast/AstFormatter.hpp"
#include "Hyper/Ast/Expressions/Expression.hpp"
#include "Hyper/Generators/Generator.hpp"
#include "Hyper/Logger.hpp"

namespace Hyper
{
	ForStatement::ForStatement(ForStatement::CreateInfo create_info)
		: m_pre_operation(std::move(create_info.pre_operation))
		, m_condition(std::move(create_info.condition))
		, m_post_operation(std::move(create_info.post_operation))
		, m_body(std::move(create_info.body))
	{
	}

	void ForStatement::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void ForStatement::dump(const std::string &prefix, bool is_self_last) const
	{
		const std::string current_prefix =
			AstFormatter::format_prefix(*this, prefix, is_self_last);
		Logger::debug("{}", current_prefix);

		AstNode::dump_next_node(*m_pre_operation, prefix, is_self_last, false);
		AstNode::dump_next_node(*m_condition, prefix, is_self_last, false);
		AstNode::dump_next_node(*m_post_operation, prefix, is_self_last, false);
		AstNode::dump_next_node(*m_body, prefix, is_self_last, true);
	}

	AstNode::Category ForStatement::class_category() const noexcept
	{
		return AstNode::Category::ForStatement;
	}

	std::string_view ForStatement::class_name() const noexcept
	{
		return "ForStatement";
	}

	std::string ForStatement::class_description() const
	{
		return "";
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
