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
		std::vector<DeclarationPtr> arguments,
		DataType return_type,
		StatementPtr body)
		: Declaration(source_range)
		, m_identifier(std::move(identifier))
		, m_arguments(std::move(arguments))
		, m_return_type(std::move(return_type))
		, m_body(std::move(body))
	{
	}

	void FunctionDeclaration::validate_scope(
		const ScopeValidator &scope_validator) const
	{
		(void) scope_validator;
	}

	void FunctionDeclaration::validate_type(
		const TypeValidator &type_validator) const
	{
		(void) type_validator;
	}
} // namespace hyper
