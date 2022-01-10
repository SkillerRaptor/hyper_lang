/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Expression.hpp"
#include "Hyper/Ast/Forward.hpp"
#include "Hyper/Identifier.hpp"
#include "Hyper/SourceRange.hpp"

#include <string>

namespace Hyper
{
	class CallExpression final : public Expression
	{
	public:
		CallExpression(
			SourceRange range,
			Identifier identifier,
			ExpressionList arguments);

		void dump(std::string_view prefix, bool self_last) const override;
		void validate(Validator &validator) override;

		Identifier identifier() const;
		const ExpressionList &arguments() const;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::CallExpression;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "CallExpression";
		}

	private:
		Identifier m_identifier;
		ExpressionList m_arguments = {};
	};
} // namespace Hyper
