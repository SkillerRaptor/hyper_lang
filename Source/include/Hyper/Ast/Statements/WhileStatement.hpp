/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Statements/Statement.hpp"

namespace Hyper
{
	class WhileStatement final : public Statement
	{
	public:
		WhileStatement(ExpressionPtr condition, StatementPtr body);

		void accept(Generator &generator) const override;
		void dump(size_t indent) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;

		const ExpressionPtr &condition() const;
		const StatementPtr &body() const;

	private:
		ExpressionPtr m_condition = nullptr;
		StatementPtr m_body = nullptr;
	};
} // namespace Hyper
