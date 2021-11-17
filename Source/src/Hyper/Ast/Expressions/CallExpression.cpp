/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Expressions/CallExpression.hpp"

#include "Hyper/Ast/AstFormatter.hpp"
#include "Hyper/Generators/Generator.hpp"
#include "Hyper/Logger.hpp"

namespace Hyper
{
	CallExpression::CallExpression(CallExpression::CreateInfo create_info)
		: m_function(std::move(create_info.function))
		, m_arguments(std::move(create_info.arguments))
	{
	}

	void CallExpression::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void CallExpression::dump(const std::string &prefix, bool is_self_last) const
	{
		const std::string current_prefix =
			AstFormatter::format_prefix(*this, prefix, is_self_last);
		Logger::debug("{}", current_prefix);

		for (const ExpressionPtr &argument : m_arguments)
		{
			const bool is_node_last = &argument == &m_arguments.back();
			AstNode::dump_next_node(*argument, prefix, is_self_last, is_node_last);
		}
	}

	AstNode::Category CallExpression::class_category() const noexcept
	{
		return AstNode::Category::CallExpression;
	}

	std::string_view CallExpression::class_name() const noexcept
	{
		return "CallExpression";
	}

	std::string CallExpression::class_description() const
	{
		const std::string identifier =
			AstFormatter::format_member("function", m_function);

		return Formatter::format("({})", identifier);
	}

	std::string CallExpression::function() const
	{
		return m_function;
	}

	const ExpressionList &CallExpression::arguments() const
	{
		return m_arguments;
	}
} // namespace Hyper
