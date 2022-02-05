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

	void IdentifierExpression::validate_scope(
		const ScopeValidator &scope_validator) const
	{
		(void) scope_validator;
	}

	void IdentifierExpression::validate_type(
		const TypeValidator &type_validator) const
	{
		(void) type_validator;
	}
} // namespace hyper
