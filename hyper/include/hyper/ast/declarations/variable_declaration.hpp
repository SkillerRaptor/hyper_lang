/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/declaration.hpp"
#include "hyper/ast/forward.hpp"
#include "hyper/ast/identifier.hpp"
#include "hyper/data_type.hpp"
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
			ExpressionPtr expression);

		void validate_scope(const ScopeValidator &scope_validator) const override;
		void validate_type(const TypeValidator &type_validator) const override;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::VariableDeclaration;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "VariableDeclaration";
		}

	private:
		Identifier m_identifier;
		MutableState m_mutable_state = {};
		DataType m_type = {};
		ExpressionPtr m_expression = nullptr;
	};
} // namespace hyper
