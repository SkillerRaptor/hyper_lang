/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Declaration.hpp"
#include "Hyper/Ast/Forward.hpp"
#include "Hyper/Identifier.hpp"
#include "Hyper/SourceRange.hpp"
#include "Hyper/Type.hpp"

#include <string>

namespace Hyper
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
			SourceRange range,
			Identifier identifier,
			MutableState mutable_state,
			Type type,
			ExpressionPtr expression);

		void dump(std::string_view prefix, bool self_last) const override;
		void validate(Validator &validator) override;

		Identifier identifier() const;
		MutableState mutable_state() const;
		Type type() const;
		const ExpressionPtr &expression() const;

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
		Type m_type = {};
		ExpressionPtr m_expression = nullptr;
	};
} // namespace Hyper
