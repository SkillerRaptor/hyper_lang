/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Declaration.hpp"
#include "Hyper/Ast/Forward.hpp"
#include "Hyper/SourceRange.hpp"
#include "Hyper/Type.hpp"

#include <string>

namespace Hyper
{
	class Expression;

	class VariableDeclaration final : public Declaration
	{
	public:
		enum class Mutable : uint8_t
		{
			No = 0,
			Yes
		};

	public:
		VariableDeclaration(
			std::string identifier,
			Mutable mutable_state,
			Type type,
			ExpressionPtr expression,
			SourceRange identifier_range,
			SourceRange type_range);

		void dump(std::string_view prefix, bool self_last) const override;
		void validate(Validator &validator) override;

		std::string identifier() const;
		Mutable is_mutable() const;
		Type type() const;
		const ExpressionPtr &expression() const;

		SourceRange identifier_range() const;
		SourceRange type_range() const;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::VariableDeclaration;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "VariableDeclaration";
		}

	private:
		std::string m_identifier;
		Mutable m_mutable = Mutable::No;
		Type m_type = {};
		ExpressionPtr m_expression = nullptr;

		SourceRange m_identifier_range = {};
		SourceRange m_type_range = {};
	};
} // namespace Hyper
