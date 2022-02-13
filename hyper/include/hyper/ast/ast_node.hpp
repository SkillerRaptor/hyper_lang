/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/source_range.hpp"

#include <string_view>

namespace hyper
{
	template <typename Derived>
	class AstVisitor;

	class AstNode
	{
	public:
		enum class Category : uint8_t
		{
			ExportDeclaration,
			FunctionDeclaration,
			ImportDeclaration,
			ParameterDeclaration,
			TranslationUnitDeclaration,
			VariableDeclaration,

			BinaryExpression,
			CallExpression,
			CastExpression,
			ConditionalExpression,
			IdentifierExpression,
			UnaryExpression,

			BoolLiteral,
			FloatingLiteral,
			IntegerLiteral,
			StringLiteral,

			AssignStatement,
			CompoundAssignStatement,
			CompoundStatement,
			ExpressionStatement,
			IfStatement,
			PrintStatement,
			ReturnStatement,
			WhileStatement,
		};

		enum class Kind : uint8_t
		{
			Declaration,
			Expression,
			Literal,
			Statement,
		};

	public:
		virtual ~AstNode() = default;

		Position start_position() const noexcept;
		Position end_position() const noexcept;

		SourceRange source_range() const noexcept;

		constexpr virtual Category class_category() const noexcept = 0;
		constexpr virtual Kind class_kind() const noexcept = 0;
		constexpr virtual std::string_view class_name() const noexcept = 0;

	protected:
		explicit AstNode(SourceRange source_range);

	protected:
		SourceRange m_source_range = {};
	};
} // namespace hyper
