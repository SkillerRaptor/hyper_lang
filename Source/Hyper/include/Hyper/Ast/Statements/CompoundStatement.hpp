/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Statement.hpp"

#include <memory>
#include <vector>

namespace Hyper
{
	class CompoundStatement : public Statement
	{
	public:
		explicit CompoundStatement(
			std::vector<std::unique_ptr<Statement>> statements);

		void dump(std::string_view prefix, bool self_last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;

	private:
		std::vector<std::unique_ptr<Statement>> m_statements = {};
	};
} // namespace Hyper
