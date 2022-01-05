/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Forward.hpp"
#include "Hyper/Ast/Statement.hpp"
#include "Hyper/SourceRange.hpp"

#include <string>

namespace Hyper
{
	class Expression;

	class AssignStatement final : public Statement
	{
	public:
		AssignStatement(
			std::string identifier,
			ExpressionPtr expression,
			SourceRange identifier_range);

		void dump(std::string_view prefix, bool self_last) const override;
		void validate(Validator &validator) override;

		std::string identifier() const;
		const ExpressionPtr &expression() const;

		SourceRange identifier_range() const;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::AssignStatement;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "AssignStatement";
		}

	private:
		std::string m_identifier;
		ExpressionPtr m_expression = nullptr;

		SourceRange m_identifier_range = {};
	};
} // namespace Hyper
