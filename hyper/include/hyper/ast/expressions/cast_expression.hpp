/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/expression.hpp"
#include "hyper/ast/forward.hpp"
#include "hyper/data_type.hpp"

namespace hyper
{
	class CastExpression : public Expression
	{
	public:
		CastExpression(
			SourceRange source_range,
			ExpressionPtr expression,
			DataType type);

		void validate_scope(const ScopeValidator &scope_validator) const override;
		void validate_type(const TypeValidator &type_validator) const override;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::ImplicitCastExpression;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "CastExpression";
		}

	private:
		ExpressionPtr m_expression = nullptr;
		DataType m_type = {};
	};
} // namespace hyper
