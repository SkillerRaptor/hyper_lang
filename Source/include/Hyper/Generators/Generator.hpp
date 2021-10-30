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

	class VariableDeclaration;

	class BinaryExpression;
	class IdentifierExpression;

	class NumericLiteral;

	class AssignStatement;
	class CompoundStatement;
	class IfStatement;
	class PrintStatement;
	class WhileStatement;

	class Generator
	{
	public:
		explicit Generator(std::string file);
		virtual ~Generator() = default;

		virtual void generate_pre() = 0;
		virtual void generate_post() = 0;

		virtual void visit(const AstNode &ast_node) = 0;

		virtual void visit(const VariableDeclaration &variable_declaration) = 0;

		virtual void visit(const BinaryExpression &binary_expression) = 0;
		virtual void visit(const IdentifierExpression &identifier_expression) = 0;

		virtual void visit(const NumericLiteral &numeric_literal) = 0;

		virtual void visit(const AssignStatement &assign_statement) = 0;
		virtual void visit(const CompoundStatement &compound_statement) = 0;
		virtual void visit(const IfStatement &if_statement) = 0;
		virtual void visit(const PrintStatement &print_statement) = 0;
		virtual void visit(const WhileStatement &while_statement) = 0;

	protected:
		std::string m_file;
	};
} // namespace Hyper
