/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/expressions/expression.hpp"
#include "hyper/data_type.hpp"

namespace hyper
{
	class CastExpression : public Expression
	{
	public:
		CastExpression(
			SourceRange source_range,
			Expression *expression,
			DataType type);
		~CastExpression() override;

		const Expression *expression() const;
		DataType type() const;

		constexpr Category class_category() const override
		{
			return AstNode::Category::CastExpression;
		}

		constexpr Kind class_kind() const override
		{
			return AstNode::Kind::Expression;
		}

		constexpr std::string_view class_name() const override
		{
			return "CastExpression";
		}

	private:
		Expression *m_expression = nullptr;
		DataType m_type = {};
	};
} // namespace hyper
