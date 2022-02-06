/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/literals/bool_literal.hpp"

#include "hyper/type_validator.hpp"

namespace hyper
{
	BoolLiteral::BoolLiteral(SourceRange source_range, bool boolean)
		: Literal(source_range)
		, m_boolean(boolean)
	{
		(void) m_boolean;
	}

	void BoolLiteral::collect_symbols(std::vector<Symbol> &) const
	{
	}

	void BoolLiteral::validate_scope(const ScopeValidator &) const
	{
	}

	void BoolLiteral::validate_type(TypeValidator &type_validator) const
	{
		const DataType data_type("bool", DataType::Kind::Bool, m_source_range);
		type_validator.set_current_data_type(data_type);
	}
} // namespace hyper
