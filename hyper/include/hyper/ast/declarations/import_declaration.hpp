/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/declarations/declaration.hpp"

#include <string>

namespace hyper
{
	class ImportDeclaration : public Declaration
	{
	public:
		ImportDeclaration(SourceRange source_range, std::string module_name);

		std::string_view module_name() const;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::ImportDeclaration;
		}

		constexpr Kind class_kind() const noexcept override
		{
			return AstNode::Kind::Declaration;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "ImportDeclaration";
		}

	private:
		std::string m_module_name;
	};
} // namespace hyper
