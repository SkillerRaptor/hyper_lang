/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/IfStatement.hpp"

#include "Hyper/Ast/AstFormatter.hpp"
#include "Hyper/Ast/Expressions/Expression.hpp"
#include "Hyper/Generators/Generator.hpp"
#include "Hyper/Logger.hpp"

namespace Hyper
{
	IfStatement::IfStatement(IfStatement::CreateInfo create_info)
		: m_condition(std::move(create_info.condition))
		, m_true_branch(std::move(create_info.true_branch))
		, m_false_branch(std::move(create_info.false_branch))
	{
	}

	void IfStatement::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void IfStatement::dump(const std::string &prefix, bool is_self_last) const
	{
		const std::string current_prefix =
			AstFormatter::format_prefix(*this, prefix, is_self_last);
		Logger::debug("{}", current_prefix);

		AstNode::dump_next_node(*m_condition, prefix, is_self_last, false);
		AstNode::dump_next_node(
			*m_true_branch, prefix, is_self_last, m_false_branch == nullptr);

		if (m_false_branch != nullptr)
		{
			AstNode::dump_next_node(*m_false_branch, prefix, is_self_last, true);
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

	std::string IfStatement::class_description() const
	{
		return "";
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
