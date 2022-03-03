/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/declarations/field_declaration.hpp"

#include "hyper/ast/expressions/expression.hpp"

namespace hyper
{
	FieldDeclaration::FieldDeclaration(
		SourceRange source_range,
		DataType data_type,
		Identifier identifier,
		Expression *expression)
		: Declaration(source_range)
		, m_data_type(data_type)
		, m_identifier(identifier)
		, m_expression(expression)
	{
	}

	FieldDeclaration::~FieldDeclaration()
	{
		delete m_expression;
	}

	DataType FieldDeclaration::data_type() const
	{
		return m_data_type;
	}

	Identifier FieldDeclaration::identifier() const
	{
		return m_identifier;
	}

	const Expression *FieldDeclaration::expression() const
	{
		return m_expression;
	}
} // namespace hyper
