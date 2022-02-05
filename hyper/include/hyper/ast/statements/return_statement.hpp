/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/forward.hpp"
#include "hyper/ast/statement.hpp"

namespace hyper
{
	class Expression;

	class ReturnStatement final : public Statement
	{
	public:
		ReturnStatement(SourceRange source_range, ExpressionPtr expression);

		void validate_scope(const ScopeValidator &scope_validator) const override;
		void validate_type(const TypeValidator &type_validator) const override;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::ReturnStatement;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "ReturnStatement";
		}

	private:
		ExpressionPtr m_expression = nullptr;
	};
} // namespace hyper
