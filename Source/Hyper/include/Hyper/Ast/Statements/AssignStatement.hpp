/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Forward.hpp"
#include "Hyper/Ast/Statement.hpp"

#include <string>

namespace Hyper
{
	class Expression;

	class AssignStatement : public Statement
	{
	public:
		AssignStatement(std::string name, ExpressionPtr expression);

		void dump(std::string_view prefix, bool self_last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;

	private:
		std::string m_name;
		ExpressionPtr m_expression = nullptr;
	};
} // namespace Hyper
