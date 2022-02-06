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

	class ExpressionStatement final : public Statement
	{
	public:
		ExpressionStatement(SourceRange source_range, ExpressionPtr expression);

		void collect_symbols(std::vector<Symbol> &symbols) const override;

		void validate_scope(const ScopeValidator &scope_validator) const override;
		void validate_type(TypeValidator &type_validator) const override;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::ExpressionStatement;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "ExpressionStatement";
		}

	private:
		ExpressionPtr m_expression = nullptr;
	};
} // namespace hyper
