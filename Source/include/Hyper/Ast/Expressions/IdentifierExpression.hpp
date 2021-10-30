/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Expressions/Expression.hpp"

#include <string>

namespace Hyper
{
	class IdentifierExpression final : public Expression
	{
	public:
		IdentifierExpression(std::string identifier);

		void accept(Generator &generator) const override;
		void dump(size_t indent) const override;

		const char *class_name() const noexcept override;

		std::string identifier() const;

	private:
		std::string m_identifier;
	};
} // namespace Hyper
