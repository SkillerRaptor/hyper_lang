/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/expressions/expression.hpp"

namespace hyper
{
	class UnaryExpression final : public Expression
	{
	public:
		struct Operation
		{
			enum class Kind
			{
				Invalid = 0,

				Not,
				Negative,
				Inverse,

				PreIncrement,
				PreDecrement,

				PostIncrement,
				PostDecrement,
			};

			Kind kind = Kind::Invalid;
			SourceRange source_range = {};
		};

	public:
		UnaryExpression(
			SourceRange source_range,
			Operation operation,
			Expression *expression);
		~UnaryExpression() override;

		Operation operation() const;
		const Expression *expression() const;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::UnaryExpression;
		}

		constexpr Kind class_kind() const noexcept override
		{
			return AstNode::Kind::Expression;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "UnaryExpression";
		}

	private:
		Operation m_operation = {};
		Expression *m_expression = nullptr;
	};
} // namespace hyper
