/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/identifier.hpp"
#include "hyper/data_type.hpp"
#include "hyper/diagnostics.hpp"
#include "hyper/symbol.hpp"

#include <vector>

namespace hyper
{
	class TypeValidator
	{
	public:
		TypeValidator(
			const Diagnostics &diagnostics,
			const std::vector<Symbol> &symbols);

		bool match_data_type(const DataType &data_type) const noexcept;

		DataType find_data_type(const Identifier &identifier) const noexcept;

		void report_mismatch_type(
			const DataType &data_type,
			SourceRange source_range) const noexcept;

		void set_current_function(const Identifier &identifier) noexcept;
		void set_current_data_type(const DataType &data_type) noexcept;

	private:
		Symbol find_symbol(const Identifier &identifier) const noexcept;

	private:
		const Diagnostics &m_diagnostics;
		const std::vector<Symbol> &m_symbols;

		Symbol m_current_function = {};
		DataType m_current_data_type = {};
	};
} // namespace hyper
