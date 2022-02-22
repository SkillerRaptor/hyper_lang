/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/expressions/expression.hpp"
#include "hyper/identifier.hpp"
#include "hyper/source_range.hpp"

#include <span>
#include <string>
#include <vector>

namespace hyper
{
	class CallExpression final : public Expression
	{
	public:
		CallExpression(
			SourceRange source_range,
			Identifier identifier,
			std::vector<Expression *> arguments);
		~CallExpression() override;

		Identifier identifier() const;
		std::span<Expression *const> arguments() const;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::CallExpression;
		}

		constexpr Kind class_kind() const noexcept override
		{
			return AstNode::Kind::Expression;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "CallExpression";
		}

	private:
		Identifier m_identifier;
		std::vector<Expression *> m_arguments = {};
	};
} // namespace hyper
