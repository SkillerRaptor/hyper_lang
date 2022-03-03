/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/expressions/expression.hpp"
#include "hyper/identifier.hpp"

namespace hyper
{
	class MemberExpression : public Expression
	{
	public:
		MemberExpression(
			SourceRange source_range,
			Identifier struct_name,
			bool is_arrow,
			Identifier member_name);

		Identifier struct_name() const;
		bool is_arrow() const;
		Identifier member_name() const;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::MemberExpression;
		}

		constexpr Kind class_kind() const noexcept override
		{
			return AstNode::Kind::Expression;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "MemberExpression";
		}

	private:
		Identifier m_struct_name = {};
		bool m_is_arrow = false;
		Identifier m_member_name = {};
	};
} // namespace hyper
