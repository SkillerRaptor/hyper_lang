/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Statements/Statement.hpp"

namespace Hyper
{
	class IfStatement final : public Statement
	{
	public:
		IfStatement(
			ExpressionPtr condition,
			StatementPtr true_branch,
			StatementPtr false_branch);

		void accept(Generator &generator) const override;
		void dump(size_t indent) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;

		const ExpressionPtr &condition() const;
		const StatementPtr &true_branch() const;
		const StatementPtr &false_branch() const;

	private:
		ExpressionPtr m_condition = nullptr;
		StatementPtr m_true_branch = nullptr;
		StatementPtr m_false_branch = nullptr;
	};
} // namespace Hyper
