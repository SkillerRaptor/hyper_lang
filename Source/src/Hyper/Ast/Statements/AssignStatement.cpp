/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/AssignStatement.hpp"

#include "Hyper/Ast/AstFormatter.hpp"
#include "Hyper/Ast/Expressions/Expression.hpp"
#include "Hyper/Generator.hpp"
#include "Hyper/Logger.hpp"

namespace Hyper
{
	AssignStatement::AssignStatement(AssignStatement::CreateInfo create_info)
		: m_identifier(std::move(create_info.identifier))
		, m_expression(std::move(create_info.expression))
	{
	}

	void AssignStatement::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void AssignStatement::dump(
		std::string_view file,
		const std::string &prefix,
		bool is_self_last) const
	{
		const std::string current_prefix =
			AstFormatter::format_prefix(*this, prefix, is_self_last);
		Logger::file_info(file, "{}", current_prefix);

		AstNode::dump_next_node(file, *m_expression, prefix, is_self_last, true);
	}

	AstNode::Category AssignStatement::class_category() const noexcept
	{
		return AstNode::Category::AssignStatement;
	}

	std::string_view AssignStatement::class_name() const noexcept
	{
		return "AssignStatement";
	}

	std::string AssignStatement::class_description() const
	{
		const std::string identifier =
			AstFormatter::format_member("identifier", m_identifier);

		return Formatter::format("({})", identifier);
	}

	std::string AssignStatement::identifier() const
	{
		return m_identifier;
	}

	const ExpressionPtr &AssignStatement::expression() const
	{
		return m_expression;
	}
} // namespace Hyper
