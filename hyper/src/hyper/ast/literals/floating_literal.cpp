/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/literals/floating_literal.hpp"

#include "hyper/validators/type_validator.hpp"

namespace hyper
{
	FloatingLiteral::FloatingLiteral(
		SourceRange source_range,
		std::string floating)
		: Literal(source_range)
		, m_floating(std::move(floating))
	{
	}

	void FloatingLiteral::collect_symbols(std::vector<Symbol> &) const
	{
	}

	void FloatingLiteral::validate_scope(const ScopeValidator &) const
	{
	}

	void FloatingLiteral::validate_type(TypeValidator &type_validator) const
	{
		const DataType data_type("f32", DataType::Kind::Float32, m_source_range);
		type_validator.set_current_data_type(data_type);
	}
} // namespace hyper
