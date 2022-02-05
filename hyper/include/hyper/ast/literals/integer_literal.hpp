/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/literal.hpp"

#include <string>

namespace hyper
{
	class IntegerLiteral final : public Literal
	{
	public:
		IntegerLiteral(SourceRange source_range, std::string integer);

		void validate_scope(const ScopeValidator &scope_validator) const override;
		void validate_type(const TypeValidator &type_validator) const override;

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
} // namespace hyper
