/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Statements/Statement.hpp"

#include <string>

namespace Hyper
{
	class AssignStatement final : public Statement
	{
	public:
		AssignStatement(std::string identifier, ExpressionPtr expression);

		void accept(Generator &generator) const override;
		void dump(const std::string &prefix, bool last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;

		std::string identifier() const;
		const ExpressionPtr &expression() const;

	private:
		std::string m_identifier;
		ExpressionPtr m_expression = nullptr;
	};
} // namespace Hyper
