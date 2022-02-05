/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/forward.hpp"
#include "hyper/ast/identifier.hpp"
#include "hyper/ast/statement.hpp"
#include "hyper/source_range.hpp"

namespace hyper
{
	class Expression;

	class AssignStatement final : public Statement
	{
	public:
		AssignStatement(
			SourceRange source_range,
			Identifier identifier,
			ExpressionPtr expression);

		void validate_scope(const ScopeValidator &scope_validator) const override;
		void validate_type(const TypeValidator &type_validator) const override;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::AssignStatement;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "AssignStatement";
		}

	private:
		Identifier m_identifier;
		ExpressionPtr m_expression = nullptr;
	};
} // namespace hyper
