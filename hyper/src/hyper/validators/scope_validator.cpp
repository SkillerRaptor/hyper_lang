/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/validators/scope_validator.hpp"

namespace hyper
{
	ScopeValidator::ScopeValidator(
		const Diagnostics &diagnostics,
		const std::vector<Symbol> &symbols)
		: m_diagnostics(diagnostics)
		, m_symbols(symbols)
	{
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

	void ScopeValidator::report_undeclared_identifier(
		const Identifier &identifier) const noexcept
	{
		m_diagnostics.error(
			identifier.source_range, Diagnostics::ErrorCode::E0004, identifier.value);
	}

	void ScopeValidator::report_redefined_identifier(
		const Identifier &identifier) const noexcept
	{
		m_diagnostics.error(
			identifier.source_range, Diagnostics::ErrorCode::E0005, identifier.value);
	}
} // namespace hyper
