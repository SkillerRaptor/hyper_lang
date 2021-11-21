/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/DataType.hpp"
#include "Hyper/Prerequisites.hpp"

HYPER_DISABLE_WARNINGS()
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/NoFolder.h>
#include <llvm/IR/Value.h>
HYPER_RESTORE_WARNINGS()

#include <memory>
#include <stack>
#include <string>
#include <unordered_map>

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

		llvm::Value *next_value();
		llvm::Type *to_type(DataType data_type) const;

	private:
		std::string m_file;
		bool m_debug_mode = false;

		std::unique_ptr<llvm::LLVMContext> m_context = nullptr;
		std::unique_ptr<llvm::Module> m_module = nullptr;
		std::unique_ptr<llvm::IRBuilder<llvm::NoFolder>> m_builder = nullptr;
		std::stack<llvm::Value *> m_values = {};
		std::unordered_map<std::string, llvm::AllocaInst *> m_variables = {};
	};
} // namespace Hyper
