/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/declarations/parameter_declaration.hpp"

namespace hyper
{
	ParameterDeclaration::ParameterDeclaration(
		SourceRange source_range,
		Identifier identifier,
		ParameterDeclaration::MutableState mutable_state,
		DataType type)
		: Declaration(source_range)
		, m_identifier(identifier)
		, m_mutable_state(mutable_state)
		, m_type(type)
	{
	}

	Identifier ParameterDeclaration::identifier() const
	{
		return m_identifier;
	}

	ParameterDeclaration::MutableState ParameterDeclaration::mutable_state() const
	{
		return m_mutable_state;
	}

	DataType ParameterDeclaration::type() const
	{
		return m_type;
	}
} // namespace hyper
