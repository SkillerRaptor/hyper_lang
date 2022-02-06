/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/literals/integer_literal.hpp"

#include "hyper/type_validator.hpp"

namespace hyper
{
	IntegerLiteral::IntegerLiteral(SourceRange source_range, std::string integer)
		: Literal(source_range)
		, m_integer(std::move(integer))
	{
	}

	void IntegerLiteral::collect_symbols(std::vector<Symbol> &) const
	{
	}

	void IntegerLiteral::validate_scope(const ScopeValidator &) const
	{
	}

	void IntegerLiteral::validate_type(TypeValidator &type_validator) const
	{
		const DataType data_type("i32", DataType::Kind::Int32, m_source_range);
		type_validator.set_current_data_type(data_type);
	}
} // namespace hyper
