/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Declarations/VariableDeclaration.hpp"

#include "Hyper/Generators/Generator.hpp"
#include "Hyper/Logger.hpp"

namespace Hyper
{
	VariableDeclaration::VariableDeclaration(
		std::string name,
		Type type,
		VariableDeclaration::Immutable immutable)
		: m_name(std::move(name))
		, m_type(type)
		, m_immutable(immutable)
	{
	}

	void VariableDeclaration::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void VariableDeclaration::dump(const std::string &prefix, bool last) const
	{
		AstNode::print_prefix(prefix, last);

		Logger::raw(
			"(name={}, type={}, immutable={})\n", m_name, m_type, m_immutable);
	}

	std::string VariableDeclaration::name() const
	{
		return m_name;
	}

	Type VariableDeclaration::type() const noexcept
	{
		return m_type;
	}

	VariableDeclaration::Immutable VariableDeclaration::immutable() const noexcept
	{
		return m_immutable;
	}

	AstNode::Category VariableDeclaration::class_category() const noexcept
	{
		return AstNode::Category::VariableDeclaration;
	}

	std::string_view VariableDeclaration::class_name() const noexcept
	{
		return "VariableDeclaration";
	}

	std::ostream &operator<<(
		std::ostream &ostream,
		const VariableDeclaration::Immutable &immutable)
	{
		switch (immutable)
		{
		case VariableDeclaration::Immutable::No:
			ostream << "No";
			break;
		case VariableDeclaration::Immutable::Yes:
			ostream << "Yes";
			break;
		default:
			break;
		}

		return ostream;
	}
} // namespace Hyper
