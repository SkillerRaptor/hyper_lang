/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Declaration.hpp"
#include "Hyper/Ast/Forward.hpp"
#include "Hyper/SourceRange.hpp"
#include "Hyper/Type.hpp"

#include <string>

namespace Hyper
{
	class FunctionDeclaration final : public Declaration
	{
	public:
		FunctionDeclaration(
			std::string identifier,
			DeclarationList arguments,
			Type return_type,
			StatementPtr body,
			SourceRange identifier_range,
			SourceRange return_type_range);

		void dump(std::string_view prefix, bool self_last) const override;
		void validate(Validator &validator) override;

		std::string identifier() const;
		const DeclarationList &arguments() const;
		Type return_type() const;
		const StatementPtr &body() const;

		SourceRange identifier_range() const;
		SourceRange return_type_range() const;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::FunctionDeclaration;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "FunctionDeclaration";
		}

	private:
		std::string m_identifier;
		DeclarationList m_arguments = {};
		Type m_return_type = {};
		StatementPtr m_body = nullptr;

		SourceRange m_identifier_range = {};
		SourceRange m_return_type_range = {};
	};
} // namespace Hyper
