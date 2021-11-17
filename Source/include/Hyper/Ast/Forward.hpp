/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <memory>
#include <vector>

namespace Hyper
{
	class AstNode;
	class Declaration;
	class Expression;
	class Literal;
	class Statement;

	using AstPtr = std::unique_ptr<AstNode>;
	using DeclarationPtr = std::unique_ptr<Declaration>;
	using ExpressionPtr = std::unique_ptr<Expression>;
	using LiteralPtr = std::unique_ptr<Literal>;
	using StatementPtr = std::unique_ptr<Statement>;

	using DeclarationList = std::vector<DeclarationPtr>;
	using ExpressionList = std::vector<ExpressionPtr>;
	using LiteralList = std::vector<LiteralPtr>;
	using StatementList = std::vector<StatementPtr>;
} // namespace Hyper
