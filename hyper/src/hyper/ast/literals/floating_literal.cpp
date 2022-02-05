/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/literals/floating_literal.hpp"

namespace hyper
{
	FloatingLiteral::FloatingLiteral(
		SourceRange source_range,
		std::string floating)
		: Literal(source_range)
		, m_floating(std::move(floating))
	{
	}

	void FloatingLiteral::validate_scope(
		const ScopeValidator &scope_validator) const
	{
		(void) scope_validator;
	}

	void FloatingLiteral::validate_type(const TypeValidator &type_validator) const
	{
		(void) type_validator;
	}
} // namespace hyper
