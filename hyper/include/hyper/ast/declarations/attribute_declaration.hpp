/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/declarations/declaration.hpp"

#include <string>
#include <string_view>

namespace hyper
{
	class AttributeDeclaration : public Declaration
	{
	public:
		AttributeDeclaration(
			SourceRange source_range,
			std::string attribute,
			std::string value);

		std::string_view attribute() const;
		std::string_view value() const;

		constexpr Category class_category() const override
		{
			return AstNode::Category::AttributeDeclaration;
		}

		constexpr Kind class_kind() const override
		{
			return AstNode::Kind::Declaration;
		}

		constexpr std::string_view class_name() const override
		{
			return "AttributeDeclaration";
		}

	private:
		std::string m_attribute;
		std::string m_value;
	};
} // namespace hyper
