/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Expressions/IdentifierExpression.hpp"

#include "Hyper/Validator.hpp"

namespace Hyper
{
	IdentifierExpression::IdentifierExpression(
		SourceRange range,
		Identifier identifier)
		: Expression(range)
		, m_identifier(std::move(identifier))
	{
	}

	void IdentifierExpression::dump(std::string_view prefix, bool self_last) const
	{
		AstNode::dump_self(prefix, self_last);
	}

	void IdentifierExpression::validate(Validator &validator)
	{
		validator.accept(*this);
	}

	Identifier IdentifierExpression::identifier() const
	{
		return m_identifier;
	}
} // namespace Hyper
