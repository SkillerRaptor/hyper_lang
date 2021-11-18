/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Declarations/VariableDeclaration.hpp"

#include "Hyper/Ast/AstFormatter.hpp"
#include "Hyper/Generator.hpp"
#include "Hyper/Logger.hpp"

namespace Hyper
{
	VariableDeclaration::VariableDeclaration(
		VariableDeclaration::CreateInfo create_info)
		: m_name(std::move(create_info.name))
		, m_type(create_info.type)
		, m_is_immutable(create_info.is_immutable)
	{
	}

	void VariableDeclaration::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void VariableDeclaration::dump(
		std::string_view file,
		const std::string &prefix,
		bool is_self_last) const
	{
		const std::string current_prefix =
			AstFormatter::format_prefix(*this, prefix, is_self_last);
		Logger::file_info(file, "{}", current_prefix);
	}

	AstNode::Category VariableDeclaration::class_category() const noexcept
	{
		return AstNode::Category::VariableDeclaration;
	}

	std::string_view VariableDeclaration::class_name() const noexcept
	{
		return "VariableDeclaration";
	}

	std::string VariableDeclaration::class_description() const
	{
		const std::string name = AstFormatter::format_member("name", m_name);
		const std::string type = AstFormatter::format_member("type", m_type);
		const std::string is_immutable =
			AstFormatter::format_member("is_immutable", m_is_immutable);

		return Formatter::format("({}, {}, {})", name, type, is_immutable);
	}

	std::string VariableDeclaration::name() const
	{
		return m_name;
	}

	DataType VariableDeclaration::type() const noexcept
	{
		return m_type;
	}

	bool VariableDeclaration::is_immutable() const noexcept
	{
		return m_is_immutable;
	}
} // namespace Hyper
