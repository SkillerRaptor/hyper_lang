/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/PrintStatement.hpp"

#include "Hyper/Ast/AstFormatter.hpp"
#include "Hyper/Ast/Expressions/Expression.hpp"
#include "Hyper/Generators/Generator.hpp"
#include "Hyper/Logger.hpp"

namespace Hyper
{
	PrintStatement::PrintStatement(PrintStatement::CreateInfo create_info)
		: m_expression(std::move(create_info.expression))
	{
	}

	void PrintStatement::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void PrintStatement::dump(const std::string &prefix, bool is_self_last) const
	{
		const std::string current_prefix =
			AstFormatter::format_prefix(*this, prefix, is_self_last);
		Logger::debug("{}", current_prefix);

		AstNode::dump_next_node(*m_expression, prefix, is_self_last, true);
	}

	AstNode::Category PrintStatement::class_category() const noexcept
	{
		return AstNode::Category::PrintStatement;
	}

	std::string_view PrintStatement::class_name() const noexcept
	{
		return "PrintStatement";
	}

	std::string PrintStatement::class_description() const
	{
		return "";
	}

	const ExpressionPtr &PrintStatement::expression() const
	{
		return m_expression;
	}
} // namespace Hyper
