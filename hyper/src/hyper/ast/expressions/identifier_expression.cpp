/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/expressions/identifier_expression.hpp"

#include "hyper/scope_validator.hpp"

namespace hyper
{
	IdentifierExpression::IdentifierExpression(
		SourceRange source_range,
		Identifier identifier)
		: Expression(source_range)
		, m_identifier(std::move(identifier))
	{
	}

	void IdentifierExpression::collect_symbols(std::vector<Symbol> &) const
	{
	}

	void IdentifierExpression::validate_scope(
		const ScopeValidator &scope_validator) const
	{
		if (!scope_validator.is_symbol_present(m_identifier))
		{
			scope_validator.report_undeclared_identifier(m_identifier);
		}
	}

	void IdentifierExpression::validate_type(TypeValidator &) const
	{
	}
} // namespace hyper
