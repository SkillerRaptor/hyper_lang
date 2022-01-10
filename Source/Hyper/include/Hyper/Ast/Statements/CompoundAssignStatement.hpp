/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Forward.hpp"
#include "Hyper/Ast/Statement.hpp"
#include "Hyper/Identifier.hpp"
#include "Hyper/SourceRange.hpp"

namespace Hyper
{
	class Expression;

	class CompoundAssignStatement final : public Statement
	{
	public:
		enum class Operation : uint8_t
		{
			Invalid = 0,

			Addition,
			Subtraction,
			Multiplication,
			Division,
			Modulo,

			BitwiseAnd,
			BitwiseOr,
			BitwiseXor,

			LeftShift,
			RightShift
		};

	public:
		CompoundAssignStatement(
			SourceRange range,
			Identifier identifier,
			Operation operation,
			ExpressionPtr expression);

		void dump(std::string_view prefix, bool self_last) const override;
		void validate(Validator &validator) override;

		Identifier identifier() const;
		Operation operation() const;
		const ExpressionPtr &expression() const;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::CompoundAssignStatement;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "CompoundAssignStatement";
		}

	private:
		Identifier m_identifier;
		Operation m_operation = Operation::Invalid;
		ExpressionPtr m_expression = nullptr;
	};
} // namespace Hyper
