/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/declaration.hpp"
#include "hyper/ast/forward.hpp"

#include <string>

namespace hyper
{
	class TranslationUnitDeclaration final : public Declaration
	{
	public:
		TranslationUnitDeclaration(
			SourceRange source_range,
			std::string file,
			std::vector<DeclarationPtr> declarations);

		void collect_symbols(std::vector<Symbol> &symbols) const override;

		void validate_scope(const ScopeValidator &scope_validator) const override;
		void validate_type(TypeValidator &type_validator) const override;

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
		std::vector<DeclarationPtr> m_declarations = {};
	};
} // namespace hyper
