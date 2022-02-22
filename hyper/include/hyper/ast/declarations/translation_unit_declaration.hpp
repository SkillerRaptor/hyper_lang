/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/declarations/declaration.hpp"

#include <span>
#include <string>
#include <vector>

namespace hyper
{
	class TranslationUnitDeclaration final : public Declaration
	{
	public:
		TranslationUnitDeclaration(
			SourceRange source_range,
			std::string file,
			std::vector<Declaration *> declarations);
		~TranslationUnitDeclaration() override;

		std::string_view file() const;
		std::span<Declaration *const> declarations() const;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::TranslationUnitDeclaration;
		}

		constexpr Kind class_kind() const noexcept override
		{
			return AstNode::Kind::Declaration;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "TranslationUnitDeclaration";
		}

	private:
		std::string m_file;
		std::vector<Declaration *> m_declarations = {};
	};
} // namespace hyper
