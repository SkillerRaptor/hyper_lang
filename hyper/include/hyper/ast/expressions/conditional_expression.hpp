/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/expressions/expression.hpp"

namespace hyper
{
	class ConditionalExpression final : public Expression
	{
	public:
		ConditionalExpression(
			SourceRange source_range,
			Expression *condition,
			Expression *true_expression,
			Expression *false_expression);
		~ConditionalExpression() override;

		const Expression *condition() const;
		const Expression *true_expression() const;
		const Expression *false_expression() const;

		constexpr Category class_category() const override
		{
			return AstNode::Category::ConditionalExpression;
		}

		constexpr Kind class_kind() const override
		{
			return AstNode::Kind::Expression;
		}

		constexpr std::string_view class_name() const override
		{
			return "ConditionalExpression";
		}

	private:
		Expression *m_condition = nullptr;
		Expression *m_true_expression = nullptr;
		Expression *m_false_expression = nullptr;
	};
} // namespace hyper
