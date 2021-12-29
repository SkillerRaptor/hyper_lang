/*
 * Copyright (c) 2020-2021, 2021 <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Expression.hpp"

#include <memory>

namespace Hyper
{
	class BinaryExpression : public Expression
	{
	public:
		enum class Operation : uint8_t
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

	public:
		BinaryExpression(
			Operation operation,
			std::unique_ptr<Expression> left,
			std::unique_ptr<Expression> right);

		void dump(std::string_view prefix, bool self_last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;

	private:
		Operation m_operation = Operation::Invalid;
		std::unique_ptr<Expression> m_left = nullptr;
		std::unique_ptr<Expression> m_right = nullptr;
	};
} // namespace Hyper
