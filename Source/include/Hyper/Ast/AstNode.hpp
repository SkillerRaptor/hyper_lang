/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstddef>

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
			VariableDeclaration,
			
			BinaryExpression,
			CallExpression,
			IdentifierExpression,
			
			NumericLiteral,
			
			AssignStatement,
			CompoundStatement,
			ForStatement,
			IfStatement,
			PrintStatement,
			ReturnStatement,
			WhileStatement
		};
		
	public:
		virtual ~AstNode() = default;

		virtual void accept(Generator &generator) const = 0;
		virtual void dump(size_t indent) const;

		virtual const char *node_name() const noexcept = 0;
		virtual Category node_category() const noexcept = 0;
	};
} // namespace Hyper
