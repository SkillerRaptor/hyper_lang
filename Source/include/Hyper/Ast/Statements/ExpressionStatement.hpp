/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Statements/Statement.hpp"

namespace Hyper
{
	class ExpressionStatement final : public Statement
	{
	public:
		explicit ExpressionStatement(ExpressionPtr expression);

		void accept(Generator &generator) const override;
		void dump(size_t indent) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;

		const ExpressionPtr &expression() const;

	private:
		ExpressionPtr m_expression = nullptr;
	};
} // namespace Hyper
