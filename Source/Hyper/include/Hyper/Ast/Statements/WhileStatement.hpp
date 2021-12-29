/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Statement.hpp"

#include <memory>

namespace Hyper
{
	class Expression;

	class WhileStatement : public Statement
	{
	public:
		WhileStatement(
			std::unique_ptr<Expression> condition,
			std::unique_ptr<Statement> body);

		void dump(std::string_view prefix, bool self_last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;

	private:
		std::unique_ptr<Expression> m_condition = nullptr;
		std::unique_ptr<Statement> m_body = nullptr;
	};
} // namespace Hyper
