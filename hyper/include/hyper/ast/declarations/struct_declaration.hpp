/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/declarations/declaration.hpp"
#include "hyper/identifier.hpp"

#include <span>
#include <vector>

namespace hyper
{
	class StructDeclaration : public Declaration
	{
	public:
		StructDeclaration(
			SourceRange source_range,
			Identifier identifier,
			std::vector<Declaration *> declarations);
		~StructDeclaration() override;

		Identifier identifier() const;
		std::span<Declaration *const> declarations() const;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::StructDeclaration;
		}

		constexpr Kind class_kind() const noexcept override
		{
			return AstNode::Kind::Declaration;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "StructDeclaration";
		}

	private:
		Identifier m_identifier = {};
		std::vector<Declaration *> m_declarations = {};
	};
} // namespace hyper
