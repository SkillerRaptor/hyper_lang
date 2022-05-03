/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/literals/literal.hpp"

#include <string>

namespace hyper
{
	class StringLiteral final : public Literal
	{
	public:
		StringLiteral(SourceRange source_range, std::string string);

		std::string_view string() const;

		constexpr Category class_category() const override
		{
			return AstNode::Category::StringLiteral;
		}

		constexpr Kind class_kind() const override
		{
			return AstNode::Kind::Literal;
		}

		constexpr std::string_view class_name() const override
		{
			return "StringLiteral";
		}

	private:
		std::string m_string;
	};
} // namespace hyper
