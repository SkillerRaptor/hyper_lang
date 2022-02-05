/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/statements/compound_assign_statement.hpp"

#include "hyper/ast/expression.hpp"

namespace hyper
{
	CompoundAssignStatement::CompoundAssignStatement(
		SourceRange source_range,
		Identifier identifier,
		CompoundAssignStatement::Operation operation,
		ExpressionPtr expression)
		: Statement(source_range)
		, m_identifier(std::move(identifier))
		, m_operation(operation)
		, m_expression(std::move(expression))
	{
	}

	void CompoundAssignStatement::validate_scope(
		const ScopeValidator &scope_validator) const
	{
		(void) scope_validator;
	}

	void CompoundAssignStatement::validate_type(
		const TypeValidator &type_validator) const
	{
		(void) type_validator;
	}
} // namespace hyper
