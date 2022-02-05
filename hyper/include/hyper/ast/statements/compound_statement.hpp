/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/forward.hpp"
#include "hyper/ast/statement.hpp"

#include <vector>

namespace hyper
{
	class CompoundStatement final : public Statement
	{
	public:
		CompoundStatement(
			SourceRange source_range,
			std::vector<StatementPtr> statements);

		void validate_scope(const ScopeValidator &scope_validator) const override;
		void validate_type(const TypeValidator &type_validator) const override;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::CompoundStatement;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "CompoundStatement";
		}

	private:
		std::vector<StatementPtr> m_statements = {};
	};
} // namespace hyper
