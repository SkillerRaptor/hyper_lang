/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/literals/literal.hpp"

namespace hyper
{
	class BoolLiteral final : public Literal
	{
	public:
		BoolLiteral(SourceRange source_range, bool boolean);

		bool boolean() const;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::BoolLiteral;
		}

		constexpr Kind class_kind() const noexcept override
		{
			return AstNode::Kind::Literal;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "BoolLiteral";
		}

	private:
		bool m_boolean = false;
	};
} // namespace hyper
