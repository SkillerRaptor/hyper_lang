/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/expressions/call_expression.hpp"

#include "hyper/scope_validator.hpp"
#include "hyper/type_validator.hpp"

namespace hyper
{
	CallExpression::CallExpression(
		SourceRange source_range,
		Identifier identifier,
		std::vector<ExpressionPtr> arguments)
		: Expression(source_range)
		, m_identifier(std::move(identifier))
		, m_arguments(std::move(arguments))
	{
	}

	void CallExpression::collect_symbols(std::vector<Symbol> &symbols) const
	{
		for (const ExpressionPtr &argument : m_arguments)
		{
			argument->collect_symbols(symbols);
		}
	}

	void CallExpression::validate_scope(
		const ScopeValidator &scope_validator) const
	{
		if (!scope_validator.is_symbol_present(m_identifier))
		{
			scope_validator.report_undeclared_identifier(m_identifier);
		}

		for (const ExpressionPtr &argument : m_arguments)
		{
			argument->validate_scope(scope_validator);
		}
	}

	void CallExpression::validate_type(TypeValidator &type_validator) const
	{
		for (const ExpressionPtr &argument : m_arguments)
		{
			argument->validate_type(type_validator);
		}

		type_validator.set_current_data_type(
			type_validator.find_data_type(m_identifier));
	}
} // namespace hyper
