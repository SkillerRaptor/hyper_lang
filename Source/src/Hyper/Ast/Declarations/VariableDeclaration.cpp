/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Declarations/VariableDeclaration.hpp"

#include "Hyper/Generators/Generator.hpp"

#include <iostream>

namespace Hyper
{
	VariableDeclaration::VariableDeclaration(
		std::string identifier,
		Type type,
		bool mut)
		: m_identifier(std::move(identifier))
		, m_type(type)
		, m_mut(mut)
	{
	}

	void VariableDeclaration::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void VariableDeclaration::dump(size_t indent) const
	{
		AstNode::dump(indent);

		std::cout << "identifier = " << m_identifier << ", ";
		std::cout << "type = " << m_type << ", ";
		std::cout << "mutable = " << m_mut;
		std::cout << '\n';
	}

	const char *VariableDeclaration::node_name() const noexcept
	{
		return "VariableDeclaration";
	}

	AstNode::Category VariableDeclaration::node_category() const noexcept
	{
		return Category::VariableDeclaration;
	}

	std::string VariableDeclaration::identifier() const
	{
		return m_identifier;
	}

	Type VariableDeclaration::type() const noexcept
	{
		return m_type;
	}

	bool VariableDeclaration::mut() const noexcept
	{
		return m_mut;
	}
} // namespace Hyper
