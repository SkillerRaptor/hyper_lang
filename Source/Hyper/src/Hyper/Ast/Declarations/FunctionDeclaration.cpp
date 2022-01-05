/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Declarations/FunctionDeclaration.hpp"

#include "Hyper/Validator.hpp"

namespace Hyper
{
	FunctionDeclaration::FunctionDeclaration(
		std::string identifier,
		DeclarationList arguments,
		Type return_type,
		StatementPtr body,
		SourceRange identifier_range,
		SourceRange return_type_range)
		: m_identifier(std::move(identifier))
		, m_arguments(std::move(arguments))
		, m_return_type(std::move(return_type))
		, m_body(std::move(body))
		, m_identifier_range(identifier_range)
		, m_return_type_range(return_type_range)
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

	void FunctionDeclaration::validate(Validator &validator)
	{
		validator.accept(*this);
	}

	std::string FunctionDeclaration::identifier() const
	{
		return m_identifier;
	}

	const DeclarationList &FunctionDeclaration::arguments() const
	{
		return m_arguments;
	}

	Type FunctionDeclaration::return_type() const
	{
		return m_return_type;
	}

	const StatementPtr &FunctionDeclaration::body() const
	{
		return m_body;
	}

	SourceRange FunctionDeclaration::identifier_range() const
	{
		return m_identifier_range;
	}

	SourceRange FunctionDeclaration::return_type_range() const
	{
		return m_return_type_range;
	}
} // namespace Hyper
