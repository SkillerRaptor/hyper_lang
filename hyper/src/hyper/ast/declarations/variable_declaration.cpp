/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/declarations/variable_declaration.hpp"

#include "hyper/ast/expressions/expression.hpp"

namespace hyper
{
	VariableDeclaration::VariableDeclaration(
		SourceRange source_range,
		Identifier identifier,
		VariableDeclaration::MutableState mutable_state,
		DataType type,
		Expression *expression)
		: Declaration(source_range)
		, m_identifier(std::move(identifier))
		, m_mutable_state(mutable_state)
		, m_type(std::move(type))
		, m_expression(std::move(expression))
	{
	}

	VariableDeclaration::~VariableDeclaration()
	{
		delete m_expression;
	}

	Identifier VariableDeclaration::identifier() const
	{
		return m_identifier;
	}

	VariableDeclaration::MutableState VariableDeclaration::mutable_state() const
	{
		return m_mutable_state;
	}

	DataType VariableDeclaration::type() const
	{
		return m_type;
	}

	const Expression *VariableDeclaration::expression() const
	{
		return m_expression;
	}
} // namespace hyper
