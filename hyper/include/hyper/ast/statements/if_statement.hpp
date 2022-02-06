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

	class IfStatement final : public Statement
	{
	public:
		IfStatement(
			SourceRange source_range,
			ExpressionPtr condition,
			StatementPtr true_body,
			StatementPtr false_body);

		void collect_symbols(std::vector<Symbol> &symbols) const override;

		void validate_scope(const ScopeValidator &scope_validator) const override;
		void validate_type(TypeValidator &type_validator) const override;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::IfStatement;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "IfStatement";
		}

	private:
		ExpressionPtr m_condition = nullptr;
		StatementPtr m_true_body = nullptr;
		StatementPtr m_false_body = nullptr;
	};
} // namespace hyper
