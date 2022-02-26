/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/declarations/declaration.hpp"
#include "hyper/identifier.hpp"

namespace hyper
{
	class ImportDeclaration : public Declaration
	{
	public:
		ImportDeclaration(
			SourceRange source_range,
			Identifier identifier,
			std::string file_name);

		Identifier identifier() const;
		std::string_view file_name() const;

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
		Identifier m_identifier = {};
		std::string_view m_file_name = {};
	};
} // namespace hyper
