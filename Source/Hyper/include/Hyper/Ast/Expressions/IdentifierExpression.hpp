/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Expression.hpp"
#include "Hyper/SourceRange.hpp"

#include <string>

namespace Hyper
{
	class IdentifierExpression final : public Expression
	{
	public:
		IdentifierExpression(std::string identifier, SourceRange identifier_range);

		void dump(std::string_view prefix, bool self_last) const override;
		void validate(Validator &validator) override;

		std::string identifier() const;

		SourceRange identifier_range() const;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::IdentifierExpression;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "IdentifierExpression";
		}

	private:
		std::string m_identifier;

		SourceRange m_identifier_range = {};
	};
} // namespace Hyper
