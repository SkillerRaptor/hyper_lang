/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/validators/scope_validator.hpp"

#include "hyper_utilities/profiler.hpp"

namespace hyper
{
	ScopeValidator::ScopeValidator(
		const Diagnostics &diagnostics,
		const std::vector<Symbol> &symbols)
		: m_diagnostics(diagnostics)
		, m_symbols(symbols)
	{
	}

	bool ScopeValidator::visit_function_declaration(
		const FunctionDeclaration *function_declaration) const
	{
		HYPER_PROFILE_FUNCTION();

		const Identifier &identifier = function_declaration->identifier();
		if (is_symbol_present(identifier) && !is_symbol_unique(identifier))
		{
			m_diagnostics.error(
				identifier.source_range,
				Diagnostics::ErrorCode::E0005,
				identifier.value);
		}

		return true;
	}

	bool ScopeValidator::visit_translation_unit_declaration(
		const TranslationUnitDeclaration *translation_unit_declaration)
	{
		HYPER_PROFILE_FUNCTION();

		m_current_file = translation_unit_declaration->file();

		return true;
	}

	bool ScopeValidator::visit_variable_declaration(
		const VariableDeclaration *variable_declaration) const
	{
		HYPER_PROFILE_FUNCTION();

		const Identifier &identifier = variable_declaration->identifier();
		if (is_symbol_present(identifier) && !is_symbol_unique(identifier))
		{
			m_diagnostics.error(
				identifier.source_range,
				Diagnostics::ErrorCode::E0005,
				identifier.value);
		}

		return true;
	}

	bool ScopeValidator::visit_call_expression(
		const CallExpression *call_expression) const
	{
		HYPER_PROFILE_FUNCTION();

		const Identifier &identifier = call_expression->identifier();
		if (!is_symbol_present(identifier))
		{
			m_diagnostics.error(
				identifier.source_range,
				Diagnostics::ErrorCode::E0004,
				identifier.value);
		}

		return true;
	}

	bool ScopeValidator::visit_identifier_expression(
		const IdentifierExpression *identifier_expression) const
	{
		HYPER_PROFILE_FUNCTION();

		const Identifier &identifier = identifier_expression->identifier();
		if (!is_symbol_present(identifier))
		{
			m_diagnostics.error(
				identifier.source_range,
				Diagnostics::ErrorCode::E0004,
				identifier.value);
		}

		return true;
	}

	bool ScopeValidator::visit_assign_statement(
		const AssignStatement *assign_statement) const
	{
		HYPER_PROFILE_FUNCTION();

		const Identifier &identifier = assign_statement->identifier();
		if (!is_symbol_present(identifier))
		{
			m_diagnostics.error(
				identifier.source_range,
				Diagnostics::ErrorCode::E0004,
				identifier.value);
		}

		return true;
	}

	bool ScopeValidator::visit_compound_assign_statement(
		const CompoundAssignStatement *compound_assign_statement) const
	{
		HYPER_PROFILE_FUNCTION();

		const Identifier &identifier = compound_assign_statement->identifier();
		if (!is_symbol_present(identifier))
		{
			m_diagnostics.error(
				identifier.source_range,
				Diagnostics::ErrorCode::E0004,
				identifier.value);
		}

		return true;
	}

	bool ScopeValidator::is_symbol_present(
		const Identifier &identifier) const noexcept
	{
		for (const Symbol &symbol : m_symbols)
		{
			if (symbol.name == identifier.value)
			{
				return true;
			}
		}

		return false;
	}

	bool ScopeValidator::is_symbol_unique(
		const Identifier &identifier) const noexcept
	{
		size_t count = 0;
		for (const Symbol &symbol : m_symbols)
		{
			if (symbol.name == identifier.value)
			{
				++count;
			}
		}

		return count == 1;
	}
} // namespace hyper
