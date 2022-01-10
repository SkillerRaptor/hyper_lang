/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Declaration.hpp"
#include "Hyper/Ast/Forward.hpp"

#include <string>

namespace Hyper
{
	class TranslationUnitDeclaration final : public Declaration
	{
	public:
		TranslationUnitDeclaration(
			SourceRange range,
			std::string file,
			DeclarationList declarations);

		void dump(std::string_view prefix, bool self_last) const override;
		void validate(Validator &validator) override;

		std::string file() const;
		const DeclarationList &declarations() const;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::TranslationUnitDeclaration;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "TranslationUnitDeclaration";
		}

	private:
		std::string m_file;
		DeclarationList m_declarations = {};
	};
} // namespace Hyper
