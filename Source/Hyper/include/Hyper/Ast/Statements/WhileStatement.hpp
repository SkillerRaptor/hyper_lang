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

	class WhileStatement : public Statement
	{
	public:
		WhileStatement(ExpressionPtr condition, StatementPtr body);

		void dump(std::string_view prefix, bool self_last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;

	private:
		ExpressionPtr m_condition = nullptr;
		StatementPtr m_body = nullptr;
	};
} // namespace Hyper
