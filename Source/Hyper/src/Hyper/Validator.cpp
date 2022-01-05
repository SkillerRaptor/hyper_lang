/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Validator.hpp"

#include "Hyper/Ast/AstNode.hpp"

namespace Hyper
{
	Validator::Validator(Diagnostics &diagnostics, AstPtr &ast)
		: m_diagnostics(diagnostics)
		, m_ast(ast)
	{
	}

	void Validator::validate()
	{
		m_ast->validate(*this);
	}
} // namespace Hyper
