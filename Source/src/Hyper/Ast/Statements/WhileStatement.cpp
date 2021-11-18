/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/WhileStatement.hpp"

#include "Hyper/Ast/AstFormatter.hpp"
#include "Hyper/Ast/Expressions/Expression.hpp"
#include "Hyper/Generator.hpp"
#include "Hyper/Logger.hpp"

namespace Hyper
{
	WhileStatement::WhileStatement(WhileStatement::CreateInfo create_info)
		: m_condition(std::move(create_info.condition))
		, m_body(std::move(create_info.body))
	{
	}

	void WhileStatement::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void WhileStatement::dump(
		std::string_view file,
		const std::string &prefix,
		bool is_self_last) const
	{
		const std::string current_prefix =
			AstFormatter::format_prefix(*this, prefix, is_self_last);
		Logger::file_info(file, "{}", current_prefix);

		AstNode::dump_next_node(file, *m_condition, prefix, is_self_last, false);
		AstNode::dump_next_node(file, *m_body, prefix, is_self_last, true);
	}

	AstNode::Category WhileStatement::class_category() const noexcept
	{
		return AstNode::Category::WhileStatement;
	}

	std::string_view WhileStatement::class_name() const noexcept
	{
		return "WhileStatement";
	}

	std::string WhileStatement::class_description() const
	{
		return "";
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
