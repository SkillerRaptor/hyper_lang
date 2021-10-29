/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/AssignStatement.hpp"

#include "Hyper/Generators/Generator.hpp"

namespace Hyper
{
	void AssignStatement::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void AssignStatement::dump(size_t indent) const
	{
		AstNode::dump(indent);
	}

	const char *AssignStatement::class_name() const noexcept
	{
		return "AssignStatement";
	}
} // namespace Hyper
