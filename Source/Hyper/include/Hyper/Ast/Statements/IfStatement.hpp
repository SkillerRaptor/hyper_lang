/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Forward.hpp"
#include "Hyper/Ast/Statement.hpp"

namespace Hyper
{
	class Expression;

	class IfStatement final : public Statement
	{
	public:
		IfStatement(
			SourceRange range,
			ExpressionPtr condition,
			StatementPtr true_body,
			StatementPtr false_body);

		void dump(std::string_view prefix, bool self_last) const override;
		void validate(Validator &validator) override;

		const ExpressionPtr &condition() const;
		const StatementPtr &true_body() const;
		const StatementPtr &false_body() const;

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
} // namespace Hyper
