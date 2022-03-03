/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/expressions/member_expression.hpp"

namespace hyper
{
	MemberExpression::MemberExpression(
		SourceRange source_range,
		Identifier struct_name,
		bool is_arrow,
		Identifier member_name)
		: Expression(source_range)
		, m_struct_name(struct_name)
		, m_is_arrow(is_arrow)
		, m_member_name(member_name)
	{
	}

	Identifier MemberExpression::struct_name() const
	{
		return m_struct_name;
	}

	bool MemberExpression::is_arrow() const
	{
		return m_is_arrow;
	}

	Identifier MemberExpression::member_name() const
	{
		return m_member_name;
	}
} // namespace hyper
