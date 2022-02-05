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
			ExpressionPtr left,
			ExpressionPtr right);

		void validate_scope(const ScopeValidator &scope_validator) const override;
		void validate_type(const TypeValidator &type_validator) const override;

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
} // namespace hyper
