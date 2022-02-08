/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/identifier.hpp"
#include "hyper/diagnostics.hpp"
#include "hyper/symbol.hpp"

#include <vector>

namespace hyper
{
	class ScopeValidator
	{
	public:
		ScopeValidator(
			const Diagnostics &diagnostics,
			const std::vector<Symbol> &symbols);

		bool is_symbol_present(const Identifier &identifier) const noexcept;
		bool is_symbol_unique(const Identifier &identifier) const noexcept;

		void report_undeclared_identifier(
			const Identifier &identifier) const noexcept;
		void report_redefined_identifier(
			const Identifier &identifier) const noexcept;

	private:
		const Diagnostics &m_diagnostics;
		const std::vector<Symbol> &m_symbols;
	};
} // namespace hyper
