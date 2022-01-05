/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Expressions/CallExpression.hpp"

#include "Hyper/Validator.hpp"

namespace Hyper
{
	CallExpression::CallExpression(
		std::string identifier,
		ExpressionList arguments,
		SourceRange identifier_range)
		: m_identifier(std::move(identifier))
		, m_arguments(std::move(arguments))
		, m_identifier_range(identifier_range)
	{
	}

	void CallExpression::dump(std::string_view prefix, bool self_last) const
	{
		AstNode::dump_self(prefix, self_last);

		for (const auto &argument : m_arguments)
		{
			const bool node_last = &argument == &m_arguments.back();
			AstNode::dump_node(*argument, prefix, self_last, node_last);
		}
	}

	void CallExpression::validate(Validator &validator)
	{
		validator.accept(*this);
	}

	std::string CallExpression::identifier() const
	{
		return m_identifier;
	}

	const ExpressionList &CallExpression::arguments() const
	{
		return m_arguments;
	}

	SourceRange CallExpression::identifier_range() const
	{
		return m_identifier_range;
	}
} // namespace Hyper
