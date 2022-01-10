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
	class StringLiteral final : public Literal
	{
	public:
		StringLiteral(SourceRange range, std::string string);

		void dump(std::string_view prefix, bool self_last) const override;
		void validate(Validator &validator) override;

		std::string string();

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::StringLiteral;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "StringLiteral";
		}

	private:
		std::string m_string;
	};
} // namespace Hyper
