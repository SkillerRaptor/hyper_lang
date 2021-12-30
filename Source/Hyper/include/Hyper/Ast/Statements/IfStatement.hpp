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

	class IfStatement : public Statement
	{
	public:
		IfStatement(
			ExpressionPtr condition,
			StatementPtr true_body,
			StatementPtr false_body);

		void dump(std::string_view prefix, bool self_last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;

	private:
		ExpressionPtr m_condition = nullptr;
		StatementPtr m_true_body = nullptr;
		StatementPtr m_false_body = nullptr;
	};
} // namespace Hyper
