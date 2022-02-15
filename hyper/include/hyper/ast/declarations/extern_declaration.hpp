/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/declarations/declaration.hpp"

namespace hyper
{
	class ExternDeclaration : public Declaration
	{
	public:
		ExternDeclaration(SourceRange source_range, Statement *statement);
		~ExternDeclaration() override;

		const Statement *statement() const;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::ExternDeclaration;
		}

		constexpr Kind class_kind() const noexcept override
		{
			return AstNode::Kind::Declaration;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "ExternDeclaration";
		}

	private:
		Statement *m_statement = nullptr;
	};
} // namespace hyper
