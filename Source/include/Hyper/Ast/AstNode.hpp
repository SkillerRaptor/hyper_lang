/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <string>
#include <string_view>

namespace Hyper
{
	class Generator;

	class AstNode
	{
	public:
		enum class Category : unsigned char
		{
			None = 0,

			FunctionDeclaration,
			TranslationUnitDeclaration,
			VariableDeclaration,

			BinaryExpression,
			CallExpression,
			IdentifierExpression,

			NumericLiteral,
			StringLiteral,

			AssignStatement,
			CompoundStatement,
			ExpressionStatement,
			ForStatement,
			IfStatement,
			PrintStatement,
			ReturnStatement,
			WhileStatement
		};

	public:
		virtual ~AstNode() = default;

		void dump_tree() const;

		virtual void accept(Generator &generator) const = 0;

		virtual Category class_category() const noexcept = 0;
		virtual std::string_view class_name() const noexcept = 0;
		virtual std::string class_description() const = 0;

	protected:
		virtual void dump(const std::string &prefix, bool is_self_last) const = 0;

		void dump_next_node(
			const AstNode &node,
			const std::string &prefix,
			bool is_self_last,
			bool is_node_last) const;
	};
} // namespace Hyper
