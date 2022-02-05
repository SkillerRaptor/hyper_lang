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
	class StringLiteral final : public Literal
	{
	public:
		StringLiteral(SourceRange source_range, std::string string);

		void validate_scope(const ScopeValidator &scope_validator) const override;
		void validate_type(const TypeValidator &type_validator) const override;

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
} // namespace hyper
