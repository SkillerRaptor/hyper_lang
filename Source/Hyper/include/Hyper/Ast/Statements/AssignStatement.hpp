/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Forward.hpp"
#include "Hyper/Ast/Statement.hpp"
#include "Hyper/Identifier.hpp"
#include "Hyper/SourceRange.hpp"

namespace Hyper
{
	class Expression;

	class AssignStatement final : public Statement
	{
	public:
		AssignStatement(
			SourceRange range,
			Identifier identifier,
			ExpressionPtr expression);

		void dump(std::string_view prefix, bool self_last) const override;
		void validate(Validator &validator) override;

		Identifier identifier() const;
		const ExpressionPtr &expression() const;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::AssignStatement;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "AssignStatement";
		}

	private:
		Identifier m_identifier;
		ExpressionPtr m_expression = nullptr;
	};
} // namespace Hyper
