/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <memory>

namespace hyper
{
	class AstNode;
	class Declaration;
	class Expression;
	class Literal;
	class Statement;

	using AstNodePtr = std::unique_ptr<AstNode>;
	using DeclarationPtr = std::unique_ptr<Declaration>;
	using ExpressionPtr = std::unique_ptr<Expression>;
	using LiteralPtr = std::unique_ptr<Literal>;
	using StatementPtr = std::unique_ptr<Statement>;
} // namespace hyper
