/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/validators/type_validator.hpp"

namespace hyper
{
	TypeValidator::TypeValidator(
		const Diagnostics &diagnostics,
		const std::vector<Symbol> &symbols)
		: m_diagnostics(diagnostics)
		, m_symbols(symbols)
	{
	}

	bool TypeValidator::match_data_type(const DataType &data_type) const noexcept
	{
		if (m_current_data_type.kind() == DataType::Kind::UserDefined)
		{
			return m_current_data_type.value() == data_type.value();
		}

		return m_current_data_type.kind() == data_type.kind();
	}

	DataType TypeValidator::find_data_type(
		const Identifier &identifier) const noexcept
	{
		return find_symbol(identifier).data_type;
	}

	void TypeValidator::report_mismatch_type(
		const DataType &data_type,
		SourceRange source_range) const noexcept
	{
		m_diagnostics.error(
			source_range,
			Diagnostics::ErrorCode::E0006,
			m_current_data_type.value(),
			data_type.value());
	}

	void TypeValidator::set_current_function(
		const Identifier &identifier) noexcept
	{
		m_current_function = find_symbol(identifier);
	}

	void TypeValidator::set_current_data_type(const DataType &data_type) noexcept
	{
		m_current_data_type = data_type;
	}

	Symbol TypeValidator::find_symbol(const Identifier &identifier) const noexcept
	{
		for (const Symbol &symbol : m_symbols)
		{
			if (symbol.name == identifier.value)
			{
				return symbol;
			}
		}

		return {};
	}
} // namespace hyper
