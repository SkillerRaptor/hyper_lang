/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/forward.hpp"
#include "hyper/ast/identifier.hpp"
#include "hyper/ast/statement.hpp"
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
			ExpressionPtr expression);

		void collect_symbols(std::vector<Symbol> &symbols) const override;

		void validate_scope(const ScopeValidator &scope_validator) const override;
		void validate_type(TypeValidator &type_validator) const override;

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
} // namespace hyper
