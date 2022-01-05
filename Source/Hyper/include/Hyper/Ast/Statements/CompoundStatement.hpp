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
	class CompoundStatement final : public Statement
	{
	public:
		explicit CompoundStatement(StatementList statements);

		void dump(std::string_view prefix, bool self_last) const override;
		void validate(Validator &validator) override;

		const StatementList &statements() const;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::CompoundStatement;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "CompoundStatement";
		}

	private:
		StatementList m_statements = {};
	};
} // namespace Hyper
