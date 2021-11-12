/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Expressions/CallExpression.hpp"

#include "Hyper/Generators/Generator.hpp"
#include "Hyper/Logger.hpp"

namespace Hyper
{
	CallExpression::CallExpression(
		std::string identifier,
		std::vector<ExpressionPtr> arguments)
		: m_identifier(std::move(identifier))
		, m_arguments(std::move(arguments))
	{
	}

	void CallExpression::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void CallExpression::dump(size_t indent) const
	{
		AstNode::indent(indent);
		Logger::raw("{} (identifier={})\n", class_name(), m_identifier);

		for (const ExpressionPtr &expression : m_arguments)
		{
			expression->dump(indent + 1);
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

	std::string CallExpression::identifier() const
	{
		return m_identifier;
	}

	const std::vector<ExpressionPtr> &CallExpression::arguments() const
	{
		return m_arguments;
	}
} // namespace Hyper