/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Expressions/Expression.hpp"

#include <memory>
#include <ostream>

namespace Hyper
{
	class BinaryExpression final : public Expression
	{
	public:
		enum class Operation : unsigned char
		{
			None = 0,

			Addition,
			Subtraction,
			Multiplication,
			Division
		};

	public:
		BinaryExpression(
			Operation operation,
			std::unique_ptr<Expression> left,
			std::unique_ptr<Expression> right);

		void accept(Generator &generator) const override;
		void dump(size_t indent) const override;

		const char *class_name() const noexcept override;

		Operation operation() const noexcept;

	private:
		Operation m_operation = Operation::None;
		std::unique_ptr<Expression> m_left = nullptr;
		std::unique_ptr<Expression> m_right = nullptr;
	};

	std::ostream &operator<<(
		std::ostream &ostream,
		const BinaryExpression::Operation &operation);
} // namespace Hyper
