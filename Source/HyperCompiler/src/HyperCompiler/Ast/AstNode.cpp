/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "HyperCompiler/Ast/AstNode.hpp"

#include "HyperCompiler/Logger.hpp"

namespace HyperCompiler
{
	std::string AstNode::class_name() const
	{
		return "AstNode";
	}
	
	void AstNode::dump(unsigned int indent) const
	{
		Logger::info_indent(indent, "{}:\n", class_name());
	}
}
