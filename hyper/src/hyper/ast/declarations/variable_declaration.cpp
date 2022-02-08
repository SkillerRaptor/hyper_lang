/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/declarations/variable_declaration.hpp"

#include "hyper/ast/expression.hpp"
#include "hyper/validators/scope_validator.hpp"
#include "hyper/validators/type_validator.hpp"

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

	void VariableDeclaration::collect_symbols(std::vector<Symbol> &symbols) const
	{
		const Symbol symbol = {
			.name = m_identifier.value,
			.file = "",
			.kind = Symbol::Kind::Variable,
			.data_type = m_type,
			.source_range = m_identifier.source_range,
		};

		symbols.emplace_back(symbol);

		m_expression->collect_symbols(symbols);
	}

	void VariableDeclaration::validate_scope(
		const ScopeValidator &scope_validator) const
	{
		if (
			scope_validator.is_symbol_present(m_identifier) &&
			!scope_validator.is_symbol_unique(m_identifier))
		{
			scope_validator.report_redefined_identifier(m_identifier);
		}

		if (m_expression)
		{
			m_expression->validate_scope(scope_validator);
		}
	}

	void VariableDeclaration::validate_type(TypeValidator &type_validator) const
	{
		if (m_expression)
		{
			m_expression->validate_type(type_validator);

			if (!type_validator.match_data_type(m_type))
			{
				type_validator.report_mismatch_type(
					m_type, m_expression->source_range());
			}
		}
	}
} // namespace hyper
