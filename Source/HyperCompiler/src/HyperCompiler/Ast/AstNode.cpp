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

	void AstNode::generate(LLVMGenerator&) const
	{
		Logger::warning("TODO: Implement generate(LLVMGenerator&) for {}!\n", class_name());
	}

	void AstNode::dump(unsigned int indent) const
	{
		Logger::debug_indent(indent, "{}:\n", class_name());
	}
}
