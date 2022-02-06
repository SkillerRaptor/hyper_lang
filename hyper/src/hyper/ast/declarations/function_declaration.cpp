/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/declarations/function_declaration.hpp"

#include "hyper/logger.hpp"
#include "hyper/scope_validator.hpp"
#include "hyper/type_validator.hpp"

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

	void FunctionDeclaration::collect_symbols(std::vector<Symbol> &symbols) const
	{
		const Symbol symbol = {
			.name = m_identifier.value,
			.file = "",
			.kind = Symbol::Kind::Function,
			.data_type = m_return_type,
			.source_range = m_identifier.source_range,
		};

		symbols.emplace_back(symbol);

		for (const DeclarationPtr &argument : m_arguments)
		{
			argument->collect_symbols(symbols);
		}

		m_body->collect_symbols(symbols);
	}

	void FunctionDeclaration::validate_scope(
		const ScopeValidator &scope_validator) const
	{
		if (
			scope_validator.is_symbol_present(m_identifier) &&
			!scope_validator.is_symbol_unique(m_identifier))
		{
			scope_validator.report_redefined_identifier(m_identifier);
		}

		for (const DeclarationPtr &argument : m_arguments)
		{
			argument->validate_scope(scope_validator);
		}

		m_body->validate_scope(scope_validator);
	}

	void FunctionDeclaration::validate_type(TypeValidator &type_validator) const
	{
		type_validator.set_current_function(m_identifier);

		for (const DeclarationPtr &argument : m_arguments)
		{
			argument->validate_type(type_validator);
		}

		m_body->validate_type(type_validator);
	}
} // namespace hyper
