/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/statements/statement.hpp"
#include "hyper/identifier.hpp"
#include "hyper/source_range.hpp"

namespace hyper
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
			SourceRange source_range,
			Identifier identifier,
			Operation operation,
			Expression *expression);
		~CompoundAssignStatement() override;

		Identifier identifier() const;
		Operation operation() const;
		const Expression *expression() const;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::CompoundAssignStatement;
		}

		constexpr Kind class_kind() const noexcept override
		{
			return AstNode::Kind::Statement;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "CompoundAssignStatement";
		}

	private:
		Identifier m_identifier;
		Operation m_operation = Operation::Invalid;
		Expression *m_expression = nullptr;
	};
} // namespace hyper
