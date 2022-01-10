/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Expression.hpp"
#include "Hyper/Identifier.hpp"
#include "Hyper/SourceRange.hpp"

#include <string>

namespace Hyper
{
	class IdentifierExpression final : public Expression
	{
	public:
		IdentifierExpression(SourceRange range, Identifier identifier);

		void dump(std::string_view prefix, bool self_last) const override;
		void validate(Validator &validator) override;

		Identifier identifier() const;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::IdentifierExpression;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "IdentifierExpression";
		}

	private:
		Identifier m_identifier;
	};
} // namespace Hyper
