/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/declarations/variable_declaration.hpp"

#include "hyper/ast/expression.hpp"

namespace hyper
{
	VariableDeclaration::VariableDeclaration(
		SourceRange source_range,
		Identifier identifier,
		VariableDeclaration::MutableState mutable_state,
		DataType type,
		ExpressionPtr expression)
		: Declaration(source_range)
		, m_identifier(std::move(identifier))
		, m_mutable_state(mutable_state)
		, m_type(std::move(type))
		, m_expression(std::move(expression))
	{
		(void) m_mutable_state;
	}

	void VariableDeclaration::validate_scope(
		const ScopeValidator &scope_validator) const
	{
		(void) scope_validator;
	}

	void VariableDeclaration::validate_type(
		const TypeValidator &type_validator) const
	{
		(void) type_validator;
	}
} // namespace hyper
