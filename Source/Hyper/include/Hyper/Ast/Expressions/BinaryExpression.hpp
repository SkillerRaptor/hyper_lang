/*
 * Copyright (c) 2020-2021, 2021 <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Expression.hpp"
#include "Hyper/Ast/Forward.hpp"

namespace Hyper
{
	class BinaryExpression final : public Expression
	{
	public:
		struct Operation
		{
			enum class Kind : uint8_t
			{
				Invalid = 0,

				Addition,
				Subtraction,
				Multiplication,
				Division,
				Modulo,

				BitwiseAnd,
				BitwiseOr,
				BitwiseXor,

				LeftShift,
				RightShift,

				LogicalAnd,
				LogicalOr,

				Equal,
				NotEqual,
				LessThan,
				GreaterThan,
				LessEqual,
				GreaterEqual,
			};

			Kind kind = Kind::Invalid;
			SourceRange range = {};
		};

	public:
		BinaryExpression(
			SourceRange range,
			Operation operation,
			ExpressionPtr left,
			ExpressionPtr right);

		void dump(std::string_view prefix, bool self_last) const override;
		void validate(Validator &validator) override;

		Operation operation() const;
		const ExpressionPtr &left() const;
		const ExpressionPtr &right() const;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::BinaryExpression;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "BinaryExpression";
		}

	private:
		Operation m_operation = {};
		ExpressionPtr m_left = nullptr;
		ExpressionPtr m_right = nullptr;
	};
} // namespace Hyper
