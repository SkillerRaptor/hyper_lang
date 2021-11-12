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
		explicit Generator(std::string file);
		virtual ~Generator() = default;

		virtual void generate_pre() = 0;
		virtual void generate_post() = 0;

		virtual void visit(const AstNode &ast) = 0;

		virtual void visit(const FunctionDeclaration &declaration) = 0;
		virtual void visit(const TranslationUnitDeclaration &declaration) = 0;
		virtual void visit(const VariableDeclaration &declaration) = 0;

		virtual void visit(const BinaryExpression &expression) = 0;
		virtual void visit(const CallExpression &expression) = 0;
		virtual void visit(const IdentifierExpression &expression) = 0;

		virtual void visit(const NumericLiteral &literal) = 0;
		virtual void visit(const StringLiteral &literal) = 0;

		virtual void visit(const AssignStatement &statement) = 0;
		virtual void visit(const CompoundStatement &statement) = 0;
		virtual void visit(const ExpressionStatement &statement) = 0;
		virtual void visit(const ForStatement &statement) = 0;
		virtual void visit(const IfStatement &statement) = 0;
		virtual void visit(const PrintStatement &statement) = 0;
		virtual void visit(const ReturnStatement &statement) = 0;
		virtual void visit(const WhileStatement &statement) = 0;

	protected:
		std::string m_file;
	};
} // namespace Hyper
