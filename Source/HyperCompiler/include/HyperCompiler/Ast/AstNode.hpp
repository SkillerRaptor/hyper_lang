/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "HyperCompiler/LLVMGenerator.hpp"
#include "HyperCompiler/Ast/Value.hpp"

#include <string>

namespace HyperCompiler
{
	class AstNode
	{
	public:
		virtual ~AstNode() = default;
	
		virtual void generate(LLVMGenerator& llvm_generator) const;
		virtual void dump(unsigned int indent) const;
		
		virtual std::string class_name() const;
	};
} // namespace HyperCompiler
