/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/statements/statement.hpp"
#include "hyper/identifier.hpp"
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
			Expression *expression);
		~AssignStatement() override;

		Identifier identifier() const;
		const Expression *expression() const;

		constexpr Category class_category() const override
		{
			return AstNode::Category::AssignStatement;
		}

		constexpr Kind class_kind() const override
		{
			return AstNode::Kind::Statement;
		}

		constexpr std::string_view class_name() const override
		{
			return "AssignStatement";
		}

	private:
		Identifier m_identifier;
		Expression *m_expression = nullptr;
	};
} // namespace hyper
