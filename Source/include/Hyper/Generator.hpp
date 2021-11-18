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

	class FunctionDeclaration;
	class TranslationUnitDeclaration;
	class VariableDeclaration;

	class BinaryExpression;
	class CallExpression;
	class IdentifierExpression;

	class NumericLiteral;
	class StringLiteral;

	class AssignStatement;
	class CompoundStatement;
	class ExpressionStatement;
	class ForStatement;
	class IfStatement;
	class PrintStatement;
	class ReturnStatement;
	class WhileStatement;

	class Generator
	{
	public:
		Generator(std::string file, bool debug_mode);

		void build() const;

		void visit(const AstNode &node);

		void visit(const FunctionDeclaration &function_declaration);
		void visit(const TranslationUnitDeclaration &translation_unit_declaration);
		void visit(const VariableDeclaration &variable_declaration);

		void visit(const BinaryExpression &binary_expression);
		void visit(const CallExpression &call_expression);
		void visit(const IdentifierExpression &identifier_expression);

		void visit(const NumericLiteral &numeric_literal);
		void visit(const StringLiteral &string_literal);

		void visit(const AssignStatement &assign_statement);
		void visit(const CompoundStatement &compound_statement);
		void visit(const ExpressionStatement &expression_statement);
		void visit(const ForStatement &for_statement);
		void visit(const IfStatement &if_statement);
		void visit(const PrintStatement &print_statement);
		void visit(const ReturnStatement &return_statement);
		void visit(const WhileStatement &while_statement);

	private:
		void debug_visit(const AstNode &node) const;

	private:
		std::string m_file;
		bool m_debug_mode = false;
	};
} // namespace Hyper
