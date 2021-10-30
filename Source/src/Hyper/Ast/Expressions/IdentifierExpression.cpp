/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Expressions/IdentifierExpression.hpp"

#include "Hyper/Generators/Generator.hpp"

#include <iostream>

namespace Hyper
{
	IdentifierExpression::IdentifierExpression(std::string identifier)
		: m_identifier(std::move(identifier))
	{
	}

	void IdentifierExpression::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void IdentifierExpression::dump(size_t indent) const
	{
		AstNode::dump(indent);

		std::cout << "identifier = " << m_identifier;
		std::cout << '\n';
	}
	
	const char *IdentifierExpression::node_name() const noexcept
	{
		return "IdentifierExpression";
	}

	AstNode::Category IdentifierExpression::node_category() const noexcept
	{
		return Category::IdentifierExpression;
	}

	std::string IdentifierExpression::identifier() const
	{
		return m_identifier;
	}
} // namespace Hyper
