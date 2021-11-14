/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <memory>
#include <string>
#include <string_view>

namespace Hyper
{
	class Declaration;
	using DeclarationPtr = std::unique_ptr<Declaration>;

	class Expression;
	using ExpressionPtr = std::unique_ptr<Expression>;

	class Literal;
	using LiteralPtr = std::unique_ptr<Literal>;

	class Statement;
	using StatementPtr = std::unique_ptr<Statement>;

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

		virtual void accept(Generator &generator) const = 0;
		virtual void dump(const std::string &prefix, bool is_last) const = 0;

		virtual std::string_view class_name() const noexcept = 0;
		virtual Category class_category() const noexcept = 0;

	protected:
		void print_prefix(const std::string &prefix, bool is_last) const;
		void print_next_node(
			const AstNode &node,
			const std::string &prefix,
			bool is_last,
			bool next_last) const;
	};
} // namespace Hyper
