/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Expressions/Expression.hpp"

namespace Hyper
{
	class BinaryExpression final : public Expression
	{
	public:
		enum class Operation : unsigned char
		{
			Addition = 0,
			Subtraction,
			Multiplication,
			Division,

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
			ExpressionPtr left,
			ExpressionPtr right);

		void accept(Generator &generator) const override;
		void dump(size_t indent) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;

		Operation operation() const noexcept;
		const ExpressionPtr &left() const;
		const ExpressionPtr &right() const;

	private:
		Operation m_operation = {};
		ExpressionPtr m_left = nullptr;
		ExpressionPtr m_right = nullptr;
	};

	std::ostream &operator<<(
		std::ostream &ostream,
		const BinaryExpression::Operation &operation);
} // namespace Hyper
