/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/literals/string_literal.hpp"

namespace hyper
{
	StringLiteral::StringLiteral(SourceRange source_range, std::string string)
		: Literal(source_range)
		, m_string(std::move(string))
	{
	}

	void StringLiteral::validate_scope(
		const ScopeValidator &scope_validator) const
	{
		(void) scope_validator;
	}

	void StringLiteral::validate_type(const TypeValidator &type_validator) const
	{
		(void) type_validator;
	}
} // namespace hyper
