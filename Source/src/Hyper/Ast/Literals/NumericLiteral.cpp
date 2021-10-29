/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Literals/NumericLiteral.hpp"

#include "Hyper/Generators/Generator.hpp"

#include <iostream>

namespace Hyper
{
	NumericLiteral::NumericLiteral(int64_t value)
		: m_value(value)
	{
	}

	void NumericLiteral::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void NumericLiteral::dump(size_t indent) const
	{
		AstNode::dump(indent);

		std::cout << "value = " << m_value;
		std::cout << '\n';
	}

	const char *NumericLiteral::class_name() const noexcept
	{
		return "NumericLiteral";
	}
	
	int64_t NumericLiteral::value() const noexcept
	{
		return m_value;
	}
} // namespace Hyper
