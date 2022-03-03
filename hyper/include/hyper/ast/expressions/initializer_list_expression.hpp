/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/expressions/expression.hpp"

#include <span>
#include <vector>

namespace hyper
{
	class InitializerListExpression : public Expression
	{
	public:
		InitializerListExpression(
			SourceRange source_range,
			std::vector<Expression *> expressions);
		~InitializerListExpression() override;

		std::span<Expression *const> expressions() const;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::InitializerListExpression;
		}

		constexpr Kind class_kind() const noexcept override
		{
			return AstNode::Kind::Expression;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "InitializerListExpression";
		}

	private:
		std::vector<Expression *> m_expressions = {};
	};
} // namespace hyper
