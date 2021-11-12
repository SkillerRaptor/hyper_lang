/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/AstNode.hpp"

#include "Hyper/Logger.hpp"

namespace Hyper
{
	void AstNode::indent(size_t indention)
	{
		std::string indent_string;
		for (size_t i = 0; i < indention; ++i)
		{
			indent_string += '\t';
		}

		Logger::info(indent_string);
	}
} // namespace Hyper
