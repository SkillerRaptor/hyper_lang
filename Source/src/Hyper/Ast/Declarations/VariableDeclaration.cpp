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
	VariableDeclaration::VariableDeclaration(std::string identifier, Type type)
		: m_identifier(std::move(identifier))
		, m_type(type)
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
		std::cout << "type = " << m_type;
		std::cout << '\n';
	}

	const char *VariableDeclaration::class_name() const noexcept
	{
		return "VariableDeclaration";
	}

	std::string VariableDeclaration::identifier() const
	{
		return m_identifier;
	}

	VariableDeclaration::Type VariableDeclaration::type() const noexcept
	{
		return m_type;
	}

	std::ostream &operator<<(
		std::ostream &ostream,
		const VariableDeclaration::Type &type)
	{
		switch (type)
		{
		case VariableDeclaration::Type::Int8:
			ostream << "Int8";
			break;
		case VariableDeclaration::Type::Int16:
			ostream << "Int16";
			break;
		case VariableDeclaration::Type::Int32:
			ostream << "Int32";
			break;
		case VariableDeclaration::Type::Int64:
			ostream << "Int64";
			break;
		case VariableDeclaration::Type::Uint8:
			ostream << "Uint8";
			break;
		case VariableDeclaration::Type::Uint16:
			ostream << "Uint16";
			break;
		case VariableDeclaration::Type::Uint32:
			ostream << "Uint32";
			break;
		case VariableDeclaration::Type::Uint64:
			ostream << "Uint64";
			break;
		default:
			break;
		}

		return ostream;
	}
} // namespace Hyper
