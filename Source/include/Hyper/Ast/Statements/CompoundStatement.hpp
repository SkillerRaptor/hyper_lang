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
	class CompoundStatement final : public Statement
	{
	public:
		struct CreateInfo
		{
			StatementList statements = {};
		};

	public:
		explicit CompoundStatement(CreateInfo create_info);

		void accept(Generator &generator) const override;
		void dump(const std::string &prefix, bool is_self_last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;
		std::string class_description() const override;

		const StatementList &statements() const;

	private:
		StatementList m_statements = {};
	};
} // namespace Hyper
