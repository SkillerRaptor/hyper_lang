/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Literals/StringLiteral.hpp"

#include "Hyper/Validator.hpp"

namespace Hyper
{
	StringLiteral::StringLiteral(std::string string)
		: m_string(std::move(string))
	{
	}

	void StringLiteral::dump(std::string_view prefix, bool self_last) const
	{
		AstNode::dump_self(prefix, self_last);
	}

	void StringLiteral::validate(Validator &validator)
	{
		validator.accept(*this);
	}

	std::string StringLiteral::string()
	{
		return m_string;
	}
} // namespace Hyper
