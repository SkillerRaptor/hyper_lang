/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/literals/integer_literal.hpp"

namespace hyper
{
	IntegerLiteral::IntegerLiteral(SourceRange source_range, std::string integer)
		: Literal(source_range)
		, m_integer(std::move(integer))
	{
	}

	void IntegerLiteral::validate_scope(
		const ScopeValidator &scope_validator) const
	{
		(void) scope_validator;
	}

	void IntegerLiteral::validate_type(const TypeValidator &type_validator) const
	{
		(void) type_validator;
	}
} // namespace hyper
