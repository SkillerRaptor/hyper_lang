/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Declarations/FunctionDeclaration.hpp"

#include "Hyper/Ast/AstFormatter.hpp"
#include "Hyper/Generator.hpp"
#include "Hyper/Logger.hpp"

namespace Hyper
{
	FunctionDeclaration::FunctionDeclaration(
		FunctionDeclaration::CreateInfo create_info)
		: m_name(std::move(create_info.name))
		, m_arguments(std::move(create_info.arguments))
		, m_return_type(create_info.return_type)
		, m_body(std::move(create_info.body))
	{
	}

	void FunctionDeclaration::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void FunctionDeclaration::dump(
		std::string_view file,
		const std::string &prefix,
		bool is_self_last) const
	{
		const std::string current_prefix =
			AstFormatter::format_prefix(*this, prefix, is_self_last);
		Logger::file_info(file, "{}", current_prefix);

		for (const DeclarationPtr &argument : m_arguments)
		{
			AstNode::dump_next_node(file, *argument, prefix, is_self_last, false);
		}

		AstNode::dump_next_node(file, *m_body, prefix, is_self_last, true);
	}

	AstNode::Category FunctionDeclaration::class_category() const noexcept
	{
		return AstNode::Category::FunctionDeclaration;
	}

	std::string_view FunctionDeclaration::class_name() const noexcept
	{
		return "FunctionDeclaration";
	}

	std::string FunctionDeclaration::class_description() const
	{
		const std::string name = AstFormatter::format_member("name", m_name);
		const std::string return_type =
			AstFormatter::format_member("return_type", m_return_type);

		return Formatter::format("({}, {})", name, return_type);
	}

	std::string FunctionDeclaration::name() const
	{
		return m_name;
	}

	const DeclarationList &FunctionDeclaration::arguments() const
	{
		return m_arguments;
	}

	DataType FunctionDeclaration::return_type() const noexcept
	{
		return m_return_type;
	}

	const StatementPtr &FunctionDeclaration::body() const
	{
		return m_body;
	}
} // namespace Hyper
