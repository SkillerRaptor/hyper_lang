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

	class IfStatement final : public Statement
	{
	public:
		IfStatement(
			SourceRange source_range,
			Expression *condition,
			Statement *true_body,
			Statement *false_body);
		~IfStatement() override;

		const Expression *condition() const;
		const Statement *true_body() const;
		const Statement *false_body() const;

		constexpr Category class_category() const override
		{
			return AstNode::Category::IfStatement;
		}

		constexpr Kind class_kind() const override
		{
			return AstNode::Kind::Statement;
		}

		constexpr std::string_view class_name() const override
		{
			return "IfStatement";
		}

	private:
		Expression *m_condition = nullptr;
		Statement *m_true_body = nullptr;
		Statement *m_false_body = nullptr;
	};
} // namespace hyper
