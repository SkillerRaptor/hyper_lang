/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/declarations/declaration.hpp"
#include "hyper/data_type.hpp"
#include "hyper/identifier.hpp"
#include "hyper/source_range.hpp"

#include <string>

namespace hyper
{
	class Expression;

	class VariableDeclaration final : public Declaration
	{
	public:
		enum class MutableState : uint8_t
		{
			No = 0,
			Yes,
		};

	public:
		VariableDeclaration(
			SourceRange source_range,
			Identifier identifier,
			MutableState mutable_state,
			DataType type,
			Expression *expression);
		~VariableDeclaration() override;

		Identifier identifier() const;
		MutableState mutable_state() const;
		DataType type() const;
		const Expression *expression() const;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::VariableDeclaration;
		}

		constexpr Kind class_kind() const noexcept override
		{
			return AstNode::Kind::Declaration;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "VariableDeclaration";
		}

	private:
		Identifier m_identifier;
		MutableState m_mutable_state = {};
		DataType m_type = {};
		Expression *m_expression = nullptr;
	};
} // namespace hyper
