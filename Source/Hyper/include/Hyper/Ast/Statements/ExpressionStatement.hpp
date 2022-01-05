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

	class ExpressionStatement final : public Statement
	{
	public:
		explicit ExpressionStatement(ExpressionPtr expression);

		void dump(std::string_view prefix, bool self_last) const override;
		void validate(Validator &validator) override;

		const ExpressionPtr &expression() const;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::ExpressionStatement;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "ExpressionStatement";
		}

	private:
		ExpressionPtr m_expression = nullptr;
	};
} // namespace Hyper
