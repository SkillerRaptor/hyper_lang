/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/statements/statement.hpp"

namespace hyper
{
	class Expression;

	class PrintStatement final : public Statement
	{
	public:
		PrintStatement(SourceRange source_range, Expression *expression);
		~PrintStatement() override;

		const Expression *expression() const;

		constexpr Category class_category() const override
		{
			return AstNode::Category::PrintStatement;
		}

		constexpr Kind class_kind() const override
		{
			return AstNode::Kind::Statement;
		}

		constexpr std::string_view class_name() const override
		{
			return "PrintStatement";
		}

	private:
		Expression *m_expression = nullptr;
	};
} // namespace hyper
