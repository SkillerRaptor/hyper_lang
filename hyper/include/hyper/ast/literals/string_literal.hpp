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

		void collect_symbols(std::vector<Symbol> &) const override;

		void validate_scope(const ScopeValidator &) const override;
		void validate_type(TypeValidator &type_validator) const override;

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
