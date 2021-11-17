/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Forward.hpp"
#include "Hyper/Ast/Statements/Statement.hpp"

namespace Hyper
{
	class ForStatement final : public Statement
	{
	public:
		struct CreateInfo
		{
			StatementPtr pre_operation = nullptr;
			ExpressionPtr condition = nullptr;
			StatementPtr post_operation = nullptr;
			StatementPtr body = nullptr;
		};

	public:
		explicit ForStatement(CreateInfo create_info);

		void accept(Generator &generator) const override;
		void dump(const std::string &prefix, bool is_self_last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;
		std::string class_description() const override;

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
