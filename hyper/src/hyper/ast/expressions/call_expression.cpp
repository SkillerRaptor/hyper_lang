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
		std::vector<ExpressionPtr> arguments)
		: Expression(source_range)
		, m_identifier(std::move(identifier))
		, m_arguments(std::move(arguments))
	{
	}

	void CallExpression::validate_scope(
		const ScopeValidator &scope_validator) const
	{
		(void) scope_validator;
	}

	void CallExpression::validate_type(const TypeValidator &type_validator) const
	{
		(void) type_validator;
	}
} // namespace hyper
