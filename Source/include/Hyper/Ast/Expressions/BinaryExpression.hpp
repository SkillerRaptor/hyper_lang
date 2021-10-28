/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Expressions/Expression.hpp"

#include <ostream>

namespace Hyper
{
	class BinaryExpression : public Expression
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
			Expression* left,
			Expression* right);
		~BinaryExpression() override;

		void generate() const override;
		void dump(size_t indent) const override;

		const char *class_name() const noexcept override;

	private:
		Operation m_operation = Operation::None;
		Expression* m_left = nullptr;
		Expression* m_right = nullptr;
	};

	std::ostream &operator<<(
		std::ostream &ostream,
		const BinaryExpression::Operation &operation);
} // namespace Hyper
