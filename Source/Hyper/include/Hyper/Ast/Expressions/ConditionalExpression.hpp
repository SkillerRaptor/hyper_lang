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
	class ConditionalExpression : public Expression
	{
	public:
		ConditionalExpression(
			ExpressionPtr condition,
			ExpressionPtr true_expression,
			ExpressionPtr false_expression);

		void dump(std::string_view prefix, bool self_last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;

	private:
		ExpressionPtr m_condition = nullptr;
		ExpressionPtr m_true_expression = nullptr;
		ExpressionPtr m_false_expression = nullptr;
	};
} // namespace Hyper
