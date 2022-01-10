/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Expression.hpp"
#include "Hyper/Ast/Forward.hpp"
#include "Hyper/Type.hpp"

namespace Hyper
{
	class CastExpression : public Expression
	{
	public:
		CastExpression(
			SourceRange range,
			ExpressionPtr expression,
			Type type);

		void dump(std::string_view prefix, bool self_last) const override;
		void validate(Validator &validator) override;

		const ExpressionPtr &expression() const;
		Type type() const;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::ImplicitCastExpression;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "CastExpression";
		}

	private:
		ExpressionPtr m_expression = nullptr;
		Type m_type = {};
	};
} // namespace Hyper
