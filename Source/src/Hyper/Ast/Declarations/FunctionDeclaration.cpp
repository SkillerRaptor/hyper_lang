/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Declarations/FunctionDeclaration.hpp"

#include "Hyper/Generators/Generator.hpp"

#include <iostream>

namespace Hyper
{
	FunctionDeclaration::FunctionDeclaration(
		std::string identifier,
		Type return_type,
		std::unique_ptr<Statement> body)
		: m_identifier(std::move(identifier))
		, m_return_type(return_type)
		, m_body(std::move(body))
	{
	}

	void FunctionDeclaration::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void FunctionDeclaration::dump(size_t indent) const
	{
		AstNode::dump(indent);

		std::cout << "identifier = " << m_identifier << ", ";
		std::cout << "return type = " << m_return_type;
		std::cout << '\n';
		
		m_body->dump(indent + 1);
	}

	const char *FunctionDeclaration::node_name() const noexcept
	{
		return "FunctionDeclaration";
	}

	AstNode::Category FunctionDeclaration::node_category() const noexcept
	{
		return Category::FunctionDeclaration;
	}

	std::string FunctionDeclaration::identifier() const
	{
		return m_identifier;
	}

	Type FunctionDeclaration::return_type() const noexcept
	{
		return m_return_type;
	}

	const std::unique_ptr<Statement> &FunctionDeclaration::body() const
	{
		return m_body;
	}
} // namespace Hyper
