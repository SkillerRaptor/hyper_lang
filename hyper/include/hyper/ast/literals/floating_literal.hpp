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
	class FloatingLiteral final : public Literal
	{
	public:
		FloatingLiteral(SourceRange source_range, std::string floating);

		std::string_view floating() const;

		constexpr Category class_category() const override
		{
			return AstNode::Category::FloatingLiteral;
		}

		constexpr Kind class_kind() const override
		{
			return AstNode::Kind::Literal;
		}

		constexpr std::string_view class_name() const override
		{
			return "FloatingLiteral";
		}

	private:
		std::string m_floating;
	};
} // namespace hyper
