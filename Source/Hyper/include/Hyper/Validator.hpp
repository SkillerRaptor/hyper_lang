/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Forward.hpp"

namespace Hyper
{
	class Diagnostics;

	class FunctionDeclaration;
	class TranslationUnitDeclaration;
	class VariableDeclaration;

	class BinaryExpression;
	class CallExpression;
	class ConditionalExpression;
	class IdentifierExpression;
	class CastExpression;
	class UnaryExpression;

	class BoolLiteral;
	class IntegerLiteral;
	class StringLiteral;

	class AssignStatement;
	class CompoundAssignStatement;
	class CompoundStatement;
	class ExpressionStatement;
	class IfStatement;
	class ReturnStatement;
	class WhileStatement;

	class Validator
	{
	public:
		Validator(Diagnostics &diagnostics, AstPtr &ast);
		virtual ~Validator() = default;

		void validate();

		virtual void accept(FunctionDeclaration &declaration) = 0;
		virtual void accept(TranslationUnitDeclaration &declaration) = 0;
		virtual void accept(VariableDeclaration &declaration) = 0;

		virtual void accept(BinaryExpression &expression) = 0;
		virtual void accept(CallExpression &expression) = 0;
		virtual void accept(ConditionalExpression &expression) = 0;
		virtual void accept(IdentifierExpression &expression) = 0;
		virtual void accept(CastExpression &expression) = 0;
		virtual void accept(UnaryExpression &expression) = 0;

		virtual void accept(BoolLiteral &literal) = 0;
		virtual void accept(IntegerLiteral &literal) = 0;
		virtual void accept(StringLiteral &literal) = 0;

		virtual void accept(AssignStatement &statement) = 0;
		virtual void accept(CompoundAssignStatement &statement) = 0;
		virtual void accept(CompoundStatement &statement) = 0;
		virtual void accept(ExpressionStatement &statement) = 0;
		virtual void accept(IfStatement &statement) = 0;
		virtual void accept(ReturnStatement &statement) = 0;
		virtual void accept(WhileStatement &statement) = 0;

	protected:
		Diagnostics &m_diagnostics;
		AstPtr &m_ast;
	};
} // namespace Hyper
