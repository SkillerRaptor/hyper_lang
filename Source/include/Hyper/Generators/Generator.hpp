/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <string>

namespace Hyper
{
	class AstNode;

	class BinaryExpression;
	class NumericLiteral;

	class Generator
	{
	public:
		explicit Generator(std::string file);
		virtual ~Generator() = default;

		virtual void generate_pre() = 0;
		virtual void generate_post() = 0;

		virtual void visit(const AstNode &ast_node) = 0;

		virtual void visit(const BinaryExpression &binary_expression) = 0;
		virtual void visit(const NumericLiteral &numeric_literal) = 0;

	protected:
		std::string m_file;
	};
} // namespace Hyper
