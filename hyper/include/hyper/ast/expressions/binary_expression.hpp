/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/expressions/expression.hpp"

namespace hyper
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
			SourceRange source_range = {};
		};

	public:
		BinaryExpression(
			SourceRange source_range,
			Operation operation,
			Expression *left,
			Expression *right);
		~BinaryExpression() override;

		Operation operation() const;
		const Expression *left() const;
		const Expression *right() const;

		constexpr Category class_category() const override
		{
			return AstNode::Category::BinaryExpression;
		}

		constexpr Kind class_kind() const override
		{
			return AstNode::Kind::Expression;
		}

		constexpr std::string_view class_name() const override
		{
			return "BinaryExpression";
		}

	private:
		Operation m_operation = {};
		Expression *m_left = nullptr;
		Expression *m_right = nullptr;
	};
} // namespace hyper
