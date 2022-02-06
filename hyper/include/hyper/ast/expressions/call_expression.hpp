/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/expression.hpp"
#include "hyper/ast/forward.hpp"
#include "hyper/ast/identifier.hpp"
#include "hyper/source_range.hpp"

#include <string>

namespace hyper
{
	class CallExpression final : public Expression
	{
	public:
		CallExpression(
			SourceRange source_range,
			Identifier identifier,
			std::vector<ExpressionPtr> arguments);

		void collect_symbols(std::vector<Symbol> &symbols) const override;

		void validate_scope(const ScopeValidator &scope_validator) const override;
		void validate_type(TypeValidator &type_validator) const override;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::CallExpression;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "CallExpression";
		}

	private:
		Identifier m_identifier;
		std::vector<ExpressionPtr> m_arguments = {};
	};
} // namespace hyper
