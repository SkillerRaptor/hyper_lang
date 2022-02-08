/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/literals/string_literal.hpp"

#include "hyper/validators/type_validator.hpp"

namespace hyper
{
	StringLiteral::StringLiteral(SourceRange source_range, std::string string)
		: Literal(source_range)
		, m_string(std::move(string))
	{
	}

	void StringLiteral::collect_symbols(std::vector<Symbol> &) const
	{
	}

	void StringLiteral::validate_scope(const ScopeValidator &) const
	{
	}

	void StringLiteral::validate_type(TypeValidator &type_validator) const
	{
		const DataType data_type("string", DataType::Kind::String, m_source_range);
		type_validator.set_current_data_type(data_type);
	}
} // namespace hyper
