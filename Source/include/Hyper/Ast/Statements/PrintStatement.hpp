/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Statements/Statement.hpp"

namespace Hyper
{
	class PrintStatement final : public Statement
	{
	public:
		explicit PrintStatement(ExpressionPtr expression);

		void accept(Generator &generator) const override;
		void dump(const std::string &prefix, bool last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;

		const ExpressionPtr &expression() const;

	private:
		ExpressionPtr m_expression = nullptr;
	};
} // namespace Hyper
