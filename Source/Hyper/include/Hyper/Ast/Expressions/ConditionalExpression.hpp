/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Expression.hpp"
#include "Hyper/Ast/Forward.hpp"

namespace Hyper
{
	class ConditionalExpression final : public Expression
	{
	public:
		ConditionalExpression(
			ExpressionPtr condition,
			ExpressionPtr true_expression,
			ExpressionPtr false_expression);

		void dump(std::string_view prefix, bool self_last) const override;
		void validate(Validator &validator) override;

		const ExpressionPtr &condition() const;
		const ExpressionPtr &true_expression() const;
		const ExpressionPtr &false_expression() const;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::ConditionalExpression;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "ConditionalExpression";
		}

	private:
		ExpressionPtr m_condition = nullptr;
		ExpressionPtr m_true_expression = nullptr;
		ExpressionPtr m_false_expression = nullptr;
	};
} // namespace Hyper
