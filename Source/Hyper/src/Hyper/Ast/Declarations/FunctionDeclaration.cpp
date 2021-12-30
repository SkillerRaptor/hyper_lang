/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Declarations/FunctionDeclaration.hpp"

namespace Hyper
{
	FunctionDeclaration::FunctionDeclaration(
		std::string identifier,
		DeclarationList arguments,
		Type return_type,
		StatementPtr body)
		: m_identifier(std::move(identifier))
		, m_arguments(std::move(arguments))
		, m_return_type(std::move(return_type))
		, m_body(std::move(body))
	{
	}

	void FunctionDeclaration::dump(std::string_view prefix, bool self_last) const
	{
		AstNode::dump_self(prefix, self_last);

		for (const auto &argument : m_arguments)
		{
			AstNode::dump_node(*argument, prefix, self_last, false);
		}

		AstNode::dump_node(*m_body, prefix, self_last, true);
	}

	AstNode::Category FunctionDeclaration::class_category() const noexcept
	{
		return AstNode::Category::FunctionDeclaration;
	}

	std::string_view FunctionDeclaration::class_name() const noexcept
	{
		return "FunctionDeclaration";
	}
} // namespace Hyper
