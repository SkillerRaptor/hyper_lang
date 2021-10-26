/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Literals/NumericLiteral.hpp"

#include <iostream>

namespace Hyper
{
	NumericLiteral::NumericLiteral(int64_t value)
		: m_value(value)
	{
	}
	
	void NumericLiteral::dump(size_t indent) const
	{
		AstNode::dump(indent);
		
		std::cout << "value = " << m_value
							<< '\n';
	}
	
	const char *NumericLiteral::name() const noexcept
	{
		return "NumericLiteral";
	}
} // namespace Hyper
