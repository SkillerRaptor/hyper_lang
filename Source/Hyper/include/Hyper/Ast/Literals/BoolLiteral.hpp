/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Literal.hpp"

namespace Hyper
{
	class BoolLiteral final : public Literal
	{
	public:
		BoolLiteral(SourceRange range, bool boolean);

		void dump(std::string_view prefix, bool self_last) const override;
		void validate(Validator &validator) override;

		bool boolean() const;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::BoolLiteral;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "BoolLiteral";
		}

	private:
		bool m_boolean = false;
	};
} // namespace Hyper
