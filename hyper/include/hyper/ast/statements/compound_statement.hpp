/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/statements/statement.hpp"

#include <span>
#include <vector>

namespace hyper
{
	class CompoundStatement final : public Statement
	{
	public:
		CompoundStatement(
			SourceRange source_range,
			std::vector<Statement *> statements);
		~CompoundStatement() override;

		std::span<Statement *const> statements() const;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::CompoundStatement;
		}

		constexpr Kind class_kind() const noexcept override
		{
			return AstNode::Kind::Statement;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "CompoundStatement";
		}

	private:
		std::vector<Statement *> m_statements = {};
	};
} // namespace hyper
