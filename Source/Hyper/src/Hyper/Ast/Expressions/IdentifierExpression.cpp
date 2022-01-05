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
		std::string identifier,
		SourceRange identifier_range)
		: m_identifier(std::move(identifier))
		, m_identifier_range(identifier_range)
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

	std::string IdentifierExpression::identifier() const
	{
		return m_identifier;
	}

	SourceRange IdentifierExpression::identifier_range() const
	{
		return m_identifier_range;
	}
} // namespace Hyper
