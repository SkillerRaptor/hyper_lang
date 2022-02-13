/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/declarations/declaration.hpp"
#include "hyper/data_type.hpp"
#include "hyper/identifier.hpp"

namespace hyper
{
	class ParameterDeclaration : public Declaration
	{
	public:
		enum class MutableState : uint8_t
		{
			No = 0,
			Yes,
		};

	public:
		ParameterDeclaration(
			SourceRange source_range,
			Identifier identifier,
			MutableState mutable_state,
			DataType type);

		Identifier identifier() const;
		MutableState mutable_state() const;
		DataType type() const;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::ParameterDeclaration;
		}

		constexpr Kind class_kind() const noexcept override
		{
			return AstNode::Kind::Declaration;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "ParameterDeclaration";
		}

	private:
		Identifier m_identifier;
		MutableState m_mutable_state = {};
		DataType m_type = {};
	};
} // namespace hyper
