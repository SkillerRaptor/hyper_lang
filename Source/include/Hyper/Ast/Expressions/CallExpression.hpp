/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Expressions/Expression.hpp"

#include <memory>
#include <string>

namespace Hyper
{
	class CallExpression final : public Expression
	{
	public:
		CallExpression(
			std::string identifier,
			std::unique_ptr<Expression> expression);

		void accept(Generator &generator) const override;
		void dump(size_t indent) const override;

		const char *node_name() const noexcept override;
		Category node_category() const noexcept override;

		std::string identifier() const;
		const std::unique_ptr<Expression> &expression() const;

	private:
		std::string m_identifier;
		std::unique_ptr<Expression> m_expression;
	};
} // namespace Hyper
