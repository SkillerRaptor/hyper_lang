/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Statements/Statement.hpp"

namespace Hyper
{
	class ForStatement final : public Statement
	{
	public:
		ForStatement(
			StatementPtr pre_operation,
			ExpressionPtr condition,
			StatementPtr post_operation,
			StatementPtr body);

		void accept(Generator &generator) const override;
		void dump(size_t indent) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;

		const StatementPtr &pre_operation() const;
		const ExpressionPtr &condition() const;
		const StatementPtr &post_operation() const;
		const StatementPtr &body() const;

	private:
		StatementPtr m_pre_operation = nullptr;
		ExpressionPtr m_condition = nullptr;
		StatementPtr m_post_operation = nullptr;
		StatementPtr m_body = nullptr;
	};
} // namespace Hyper
