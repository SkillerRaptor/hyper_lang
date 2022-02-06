/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/literal.hpp"

namespace hyper
{
	class BoolLiteral final : public Literal
	{
	public:
		BoolLiteral(SourceRange source_range, bool boolean);

		void collect_symbols(std::vector<Symbol> &) const override;

		void validate_scope(const ScopeValidator &) const override;
		void validate_type(TypeValidator &type_validator) const override;

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
} // namespace hyper
