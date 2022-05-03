/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/declarations/declaration.hpp"
#include "hyper/data_type.hpp"
#include "hyper/identifier.hpp"

namespace hyper
{
	class Expression;

	class FieldDeclaration : public Declaration
	{
	public:
		FieldDeclaration(
			SourceRange source_range,
			DataType data_type,
			Identifier identifier,
			Expression *expression);
		~FieldDeclaration() override;

		DataType data_type() const;
		Identifier identifier() const;
		const Expression *expression() const;

		constexpr Category class_category() const override
		{
			return AstNode::Category::FieldDeclaration;
		}

		constexpr Kind class_kind() const override
		{
			return AstNode::Kind::Declaration;
		}

		constexpr std::string_view class_name() const override
		{
			return "FieldDeclaration";
		}

	private:
		DataType m_data_type = {};
		Identifier m_identifier = {};
		Expression *m_expression = nullptr;
	};
} // namespace hyper
