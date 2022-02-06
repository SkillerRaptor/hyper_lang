/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/source_range.hpp"
#include "hyper/symbol.hpp"

#include <string_view>
#include <vector>

namespace hyper
{
	class ScopeValidator;
	class TypeValidator;

	class AstNode
	{
	public:
		enum class Category : uint8_t
		{
			// NOTE: Declarations
			FunctionDeclaration,
			TranslationUnitDeclaration,
			VariableDeclaration,

			// NOTE: Expressions
			BinaryExpression,
			CallExpression,
			ConditionalExpression,
			IdentifierExpression,
			ImplicitCastExpression,
			UnaryExpression,

			// NOTE: Literals
			BoolLiteral,
			FloatingLiteral,
			IntegerLiteral,
			StringLiteral,

			// NOTE: Statements
			AssignStatement,
			CompoundStatement,
			ExpressionStatement,
			IfStatement,
			CompoundAssignStatement,
			ReturnStatement,
			WhileStatement,
		};

	public:
		virtual ~AstNode() = default;

		Position start_position() const noexcept;
		Position end_position() const noexcept;

		SourceRange source_range() const noexcept;

		virtual void collect_symbols(std::vector<Symbol> &symbols) const = 0;

		virtual void validate_scope(
			const ScopeValidator &scope_validator) const = 0;
		virtual void validate_type(TypeValidator &type_validator) const = 0;

		constexpr virtual Category class_category() const noexcept = 0;
		constexpr virtual std::string_view class_name() const noexcept = 0;

	protected:
		explicit AstNode(SourceRange source_range);

	protected:
		SourceRange m_source_range = {};
	};
} // namespace hyper
