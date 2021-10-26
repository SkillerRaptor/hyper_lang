/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/AstNode.hpp"

#include <iostream>

namespace Hyper
{
	void AstNode::dump(size_t indent) const
	{
		for (size_t i = 0; i < indent * 2; ++i)
		{
			std::cout << ' ';
		}
		
		std::cout << name() << ": ";
	}

	const char *AstNode::name() const noexcept
	{
		return "AstNode";
	}
} // namespace Hyper
