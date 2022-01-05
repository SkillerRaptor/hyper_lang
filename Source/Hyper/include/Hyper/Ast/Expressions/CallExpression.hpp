/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Expression.hpp"
#include "Hyper/Ast/Forward.hpp"
#include "Hyper/SourceRange.hpp"

#include <string>

namespace Hyper
{
	class CallExpression final : public Expression
	{
	public:
		CallExpression(
			std::string identifier,
			ExpressionList arguments,
			SourceRange identifier_range);

		void dump(std::string_view prefix, bool self_last) const override;
		void validate(Validator &validator) override;

		std::string identifier() const;
		const ExpressionList &arguments() const;

		SourceRange identifier_range() const;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::CallExpression;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "CallExpression";
		}

	private:
		std::string m_identifier;
		ExpressionList m_arguments = {};

		SourceRange m_identifier_range = {};
	};
} // namespace Hyper
