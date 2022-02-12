/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/expressions/identifier_expression.hpp"

namespace hyper
{
	IdentifierExpression::IdentifierExpression(
		SourceRange source_range,
		Identifier identifier)
		: Expression(source_range)
		, m_identifier(std::move(identifier))
	{
	}

	Identifier IdentifierExpression::identifier() const
	{
		return m_identifier;
	}
} // namespace hyper
