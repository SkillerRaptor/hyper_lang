/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Statements/Statement.hpp"

#include <vector>

namespace Hyper
{
	class CompoundStatement final : public Statement
	{
	public:
		explicit CompoundStatement(std::vector<StatementPtr> statements);

		void accept(Generator &generator) const override;
		void dump(const std::string &prefix, bool last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;

		const std::vector<StatementPtr> &statements() const;

	private:
		std::vector<StatementPtr> m_statements = {};
	};
} // namespace Hyper
