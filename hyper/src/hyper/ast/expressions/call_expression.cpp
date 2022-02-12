/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/expressions/call_expression.hpp"

namespace hyper
{
	CallExpression::CallExpression(
		SourceRange source_range,
		Identifier identifier,
		std::vector<Expression *> arguments)
		: Expression(source_range)
		, m_identifier(std::move(identifier))
		, m_arguments(std::move(arguments))
	{
	}

	CallExpression::~CallExpression()
	{
		for (const Expression *argument : m_arguments)
		{
			delete argument;
		}
	}

	Identifier CallExpression::identifier() const
	{
		return m_identifier;
	}

	std::span<const Expression *const> CallExpression::arguments() const
	{
		return m_arguments;
	}
} // namespace hyper
