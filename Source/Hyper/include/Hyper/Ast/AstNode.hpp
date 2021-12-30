/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <string_view>

namespace Hyper
{
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
		virtual ~AstNode() = default;

		void dump() const;

		virtual Category class_category() const noexcept = 0;
		virtual std::string_view class_name() const noexcept = 0;

	protected:
		virtual void dump(std::string_view prefix, bool self_last) const = 0;

		void dump_self(std::string_view prefix, bool self_last) const;
		void dump_node(
			const AstNode &node,
			std::string_view prefix,
			bool self_last,
			bool node_last) const;
	};
} // namespace Hyper
