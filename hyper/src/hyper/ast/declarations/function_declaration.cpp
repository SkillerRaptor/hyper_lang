/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/declarations/function_declaration.hpp"

namespace hyper
{
	FunctionDeclaration::FunctionDeclaration(
		SourceRange source_range,
		Identifier identifier,
		std::vector<Declaration *> arguments,
		DataType return_type,
		Statement *body)
		: Declaration(source_range)
		, m_identifier(std::move(identifier))
		, m_arguments(std::move(arguments))
		, m_return_type(std::move(return_type))
		, m_body(std::move(body))
	{
	}

	FunctionDeclaration::~FunctionDeclaration()
	{
		for (const Declaration *argument : m_arguments)
		{
			delete argument;
		}

		delete m_body;
	}

	Identifier FunctionDeclaration::identifier() const
	{
		return m_identifier;
	}

	std::span<const Declaration *const> FunctionDeclaration::arguments() const
	{
		return m_arguments;
	}

	DataType FunctionDeclaration::return_type() const
	{
		return m_return_type;
	}

	const Statement *FunctionDeclaration::body() const
	{
		return m_body;
	}
} // namespace hyper
