/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Declarations/FunctionDeclaration.hpp"

#include "Hyper/Generators/Generator.hpp"
#include "Hyper/Logger.hpp"

namespace Hyper
{
	FunctionDeclaration::FunctionDeclaration(
		std::string name,
		std::vector<DeclarationPtr> arguments,
		Type return_type,
		StatementPtr body)
		: m_name(std::move(name))
		, m_arguments(std::move(arguments))
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
		AstNode::indent(indent);
		Logger::raw(
			"{} (name={}, return_type={})\n", class_name(), m_name, m_return_type);

		for (const DeclarationPtr &expression : m_arguments)
		{
			expression->dump(indent + 1);
		}
		m_body->dump(indent + 1);
	}

	AstNode::Category FunctionDeclaration::class_category() const noexcept
	{
		return AstNode::Category::FunctionDeclaration;
	}

	std::string_view FunctionDeclaration::class_name() const noexcept
	{
		return "FunctionDeclaration";
	}

	std::string FunctionDeclaration::name() const
	{
		return m_name;
	}

	const std::vector<DeclarationPtr> &FunctionDeclaration::arguments() const
	{
		return m_arguments;
	}

	Type FunctionDeclaration::return_type() const noexcept
	{
		return m_return_type;
	}

	const StatementPtr &FunctionDeclaration::body() const
	{
		return m_body;
	}
} // namespace Hyper
