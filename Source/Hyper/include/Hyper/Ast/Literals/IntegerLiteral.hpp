/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Literal.hpp"

#include <string>

namespace Hyper
{
	class IntegerLiteral final : public Literal
	{
	public:
		IntegerLiteral(SourceRange range, std::string integer);

		void dump(std::string_view prefix, bool self_last) const override;
		void validate(Validator &validator) override;

		std::string integer() const;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::IntegerLiteral;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "IntegerLiteral";
		}

	private:
		std::string m_integer;
	};
} // namespace Hyper
