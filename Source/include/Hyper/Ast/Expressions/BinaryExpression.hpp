/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Expressions/Expression.hpp"
#include "Hyper/Ast/Forward.hpp"

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
			Division,

			Equal,
			NotEqual,
			LessThan,
			GreaterThan,
			LessEqual,
			GreaterEqual,
		};

		struct CreateInfo
		{
			Operation operation = Operation::None;
			ExpressionPtr left = nullptr;
			ExpressionPtr right = nullptr;
		};

	public:
		explicit BinaryExpression(CreateInfo create_info);

		void accept(Generator &generator) const override;
		void dump(
			std::string_view file,
			const std::string &prefix,
			bool is_self_last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;
		std::string class_description() const override;

		Operation operation() const noexcept;
		const ExpressionPtr &left() const;
		const ExpressionPtr &right() const;

	private:
		Operation m_operation = Operation::None;
		ExpressionPtr m_left = nullptr;
		ExpressionPtr m_right = nullptr;
	};

	std::ostream &operator<<(
		std::ostream &ostream,
		const BinaryExpression::Operation &operation);
} // namespace Hyper
