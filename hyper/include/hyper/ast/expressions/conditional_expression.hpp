/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/expression.hpp"
#include "hyper/ast/forward.hpp"

namespace hyper
{
	class ConditionalExpression final : public Expression
	{
	public:
		ConditionalExpression(
			SourceRange source_range,
			ExpressionPtr condition,
			ExpressionPtr true_expression,
			ExpressionPtr false_expression);

		void validate_scope(const ScopeValidator &scope_validator) const override;
		void validate_type(const TypeValidator &type_validator) const override;

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
} // namespace hyper
