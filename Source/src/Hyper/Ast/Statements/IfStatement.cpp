/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/IfStatement.hpp"

#include "Hyper/Ast/AstFormatter.hpp"
#include "Hyper/Ast/Expressions/Expression.hpp"
#include "Hyper/Generator.hpp"
#include "Hyper/Logger.hpp"

namespace Hyper
{
	IfStatement::IfStatement(IfStatement::CreateInfo create_info)
		: m_condition(std::move(create_info.condition))
		, m_true_body(std::move(create_info.true_body))
		, m_false_body(std::move(create_info.false_body))
	{
	}

	void IfStatement::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void IfStatement::dump(
		std::string_view file,
		const std::string &prefix,
		bool is_self_last) const
	{
		const std::string current_prefix =
			AstFormatter::format_prefix(*this, prefix, is_self_last);
		Logger::file_info(file, "{}", current_prefix);

		AstNode::dump_next_node(file, *m_condition, prefix, is_self_last, false);
		AstNode::dump_next_node(
			file, *m_true_body, prefix, is_self_last, m_false_body == nullptr);

		if (m_false_body != nullptr)
		{
			AstNode::dump_next_node(file, *m_false_body, prefix, is_self_last, true);
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

	const StatementPtr &IfStatement::true_body() const
	{
		return m_true_body;
	}

	const StatementPtr &IfStatement::false_body() const
	{
		return m_false_body;
	}
} // namespace Hyper
