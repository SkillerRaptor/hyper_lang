/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "HyperCompiler/Ast/Value.hpp"

#include <string>

namespace HyperCompiler
{
	class AstNode
	{
	public:
		virtual ~AstNode() = default;
	
		virtual Value execute() const = 0;
		virtual void dump(unsigned int indent) const;
		
		virtual std::string class_name() const;
	};
} // namespace HyperCompiler
