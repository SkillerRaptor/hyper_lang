/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/statements/assign_statement.hpp"

#include "hyper/ast/expression.hpp"

namespace hyper
{
	AssignStatement::AssignStatement(
		SourceRange source_range,
		Identifier identifier,
		ExpressionPtr expression)
		: Statement(source_range)
		, m_identifier(std::move(identifier))
		, m_expression(std::move(expression))
	{
	}

	void AssignStatement::validate_scope(
		const ScopeValidator &scope_validator) const
	{
		(void) scope_validator;
	}

	void AssignStatement::validate_type(const TypeValidator &type_validator) const
	{
		(void) type_validator;
	}
} // namespace hyper
