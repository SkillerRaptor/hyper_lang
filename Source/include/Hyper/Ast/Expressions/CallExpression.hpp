/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Expressions/Expression.hpp"

#include <string>
#include <vector>

namespace Hyper
{
	class CallExpression final : public Expression
	{
	public:
		CallExpression(std::string function, std::vector<ExpressionPtr> arguments);

		void accept(Generator &generator) const override;
		void dump(const std::string &prefix, bool last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;

		std::string identifier() const;
		const std::vector<ExpressionPtr> &arguments() const;

	private:
		std::string m_identifier;
		std::vector<ExpressionPtr> m_arguments = {};
	};
} // namespace Hyper
