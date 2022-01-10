/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/SourceRange.hpp"

#include <string_view>

namespace Hyper
{
	class Validator;

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
		explicit AstNode(SourceRange range);
		virtual ~AstNode() = default;

		void dump() const;

		virtual void validate(Validator &validator) = 0;

		SourceRange range() const noexcept;

		constexpr virtual Category class_category() const noexcept = 0;
		constexpr virtual std::string_view class_name() const noexcept = 0;

	protected:
		virtual void dump(std::string_view prefix, bool self_last) const = 0;

		void dump_self(std::string_view prefix, bool self_last) const;
		void dump_node(
			const AstNode &node,
			std::string_view prefix,
			bool self_last,
			bool node_last) const;

	protected:
		SourceRange m_range = {};
	};
} // namespace Hyper
