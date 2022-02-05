/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/literals/bool_literal.hpp"

namespace hyper
{
	BoolLiteral::BoolLiteral(SourceRange source_range, bool boolean)
		: Literal(source_range)
		, m_boolean(boolean)
	{
	}

	void BoolLiteral::validate_scope(const ScopeValidator &scope_validator) const
	{
		(void) scope_validator;
	}

	void BoolLiteral::validate_type(const TypeValidator &type_validator) const
	{
		(void) type_validator;
	}
} // namespace hyper
