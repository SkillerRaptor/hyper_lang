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
			ExpressionPtr expression);

		void collect_symbols(std::vector<Symbol> &symbols) const override;

		void validate_scope(const ScopeValidator &scope_validator) const override;
		void validate_type(TypeValidator &type_validator) const override;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::UnaryExpression;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "UnaryExpression";
		}

	private:
		Operation m_operation = {};
		ExpressionPtr m_expression = nullptr;
	};
} // namespace hyper
