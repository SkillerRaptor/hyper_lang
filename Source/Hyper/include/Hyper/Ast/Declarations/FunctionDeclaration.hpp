/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Declaration.hpp"
#include "Hyper/Ast/Forward.hpp"
#include "Hyper/Identifier.hpp"
#include "Hyper/SourceRange.hpp"
#include "Hyper/Type.hpp"

#include <string>

namespace Hyper
{
	class FunctionDeclaration final : public Declaration
	{
	public:
		FunctionDeclaration(
			SourceRange range,
			Identifier identifier,
			DeclarationList arguments,
			Type return_type,
			StatementPtr body);

		void dump(std::string_view prefix, bool self_last) const override;
		void validate(Validator &validator) override;

		Identifier identifier() const;
		const DeclarationList &arguments() const;
		Type return_type() const;
		const StatementPtr &body() const;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::FunctionDeclaration;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "FunctionDeclaration";
		}

	private:
		Identifier m_identifier;
		DeclarationList m_arguments = {};
		Type m_return_type = {};
		StatementPtr m_body = nullptr;
	};
} // namespace Hyper
