/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/expression.hpp"
#include "hyper/ast/identifier.hpp"
#include "hyper/source_range.hpp"

#include <string>

namespace hyper
{
	class IdentifierExpression final : public Expression
	{
	public:
		IdentifierExpression(SourceRange source_range, Identifier identifier);

		void validate_scope(const ScopeValidator &scope_validator) const override;
		void validate_type(const TypeValidator &type_validator) const override;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::IdentifierExpression;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "IdentifierExpression";
		}

	private:
		Identifier m_identifier;
	};
} // namespace hyper
