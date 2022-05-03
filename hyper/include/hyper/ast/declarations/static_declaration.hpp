/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/declarations/declaration.hpp"

namespace hyper
{
	class StaticDeclaration : public Declaration
	{
	public:
		StaticDeclaration(SourceRange source_range, Declaration *declaration);
		~StaticDeclaration() override;

		const Declaration *declaration() const;

		constexpr Category class_category() const override
		{
			return AstNode::Category::StaticDeclaration;
		}

		constexpr Kind class_kind() const override
		{
			return AstNode::Kind::Declaration;
		}

		constexpr std::string_view class_name() const override
		{
			return "StaticDeclaration";
		}

	private:
		Declaration *m_declaration = nullptr;
	};
} // namespace hyper
