/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Generator.hpp"

#include "Hyper/Ast/Declarations/FunctionDeclaration.hpp"
#include "Hyper/Ast/Declarations/TranslationUnitDeclaration.hpp"
#include "Hyper/Ast/Declarations/VariableDeclaration.hpp"
#include "Hyper/Ast/Expressions/BinaryExpression.hpp"
#include "Hyper/Ast/Expressions/CallExpression.hpp"
#include "Hyper/Ast/Expressions/IdentifierExpression.hpp"
#include "Hyper/Ast/Literals/NumericLiteral.hpp"
#include "Hyper/Ast/Literals/StringLiteral.hpp"
#include "Hyper/Ast/Statements/AssignStatement.hpp"
#include "Hyper/Ast/Statements/CompoundStatement.hpp"
#include "Hyper/Ast/Statements/ExpressionStatement.hpp"
#include "Hyper/Ast/Statements/ForStatement.hpp"
#include "Hyper/Ast/Statements/IfStatement.hpp"
#include "Hyper/Ast/Statements/PrintStatement.hpp"
#include "Hyper/Ast/Statements/ReturnStatement.hpp"
#include "Hyper/Ast/Statements/WhileStatement.hpp"
#include "Hyper/Logger.hpp"
#include "Hyper/Prerequisites.hpp"

namespace Hyper
{
	Generator::Generator(std::string file, bool debug_mode)
		: m_file(std::move(file))
		, m_debug_mode(debug_mode)
	{
	}

	void Generator::build() const
	{
		Logger::raw("\n");
		m_module->print(llvm::outs(), nullptr);
		Logger::raw("\n");
	}

	void Generator::visit(const AstNode &node)
	{
		HYPER_UNUSED_VARIABLE(node);
		HYPER_UNREACHABLE();
	}

	void Generator::visit(const FunctionDeclaration &function_declaration)
	{
		debug_visit(function_declaration);

		for (const DeclarationPtr &declaration : function_declaration.arguments())
		{
			// TODO(SkillerRaptor): Handle arguments
			declaration->accept(*this);
		}

		llvm::Type *return_type = to_type(function_declaration.return_type());
		llvm::FunctionType *function_type =
			llvm::FunctionType::get(return_type, false);
		llvm::Function *function = llvm::Function::Create(
			function_type,
			llvm::Function::ExternalLinkage,
			function_declaration.name(),
			m_module.get());
		llvm::BasicBlock *entry_block =
			llvm::BasicBlock::Create(*m_context, "", function);
		m_builder->SetInsertPoint(entry_block);

		function_declaration.body()->accept(*this);
	}

	void Generator::visit(
		const TranslationUnitDeclaration &translation_unit_declaration)
	{
		debug_visit(translation_unit_declaration);

		m_context = std::make_unique<llvm::LLVMContext>();
		m_module = std::make_unique<llvm::Module>(
			translation_unit_declaration.file(), *m_context);
		m_builder = std::make_unique<llvm::IRBuilder<llvm::NoFolder>>(*m_context);

		for (const StatementPtr &statement :
				 translation_unit_declaration.statements())
		{
			statement->accept(*this);
		}
	}

	void Generator::visit(const VariableDeclaration &variable_declaration)
	{
		debug_visit(variable_declaration);

		// TODO(SkillerRaptor): Handle other types
		llvm::Type *variable_type = to_type(variable_declaration.type());
		llvm::AllocaInst *allocation =
			m_builder->CreateAlloca(variable_type, nullptr, "");
		llvm::Value *value = llvm::ConstantInt::get(
			*m_context, llvm::APInt(variable_type->getIntegerBitWidth(), 0, true));
		m_builder->CreateStore(value, allocation);

		m_variables[variable_declaration.name()] = allocation;
	}

	void Generator::visit(const BinaryExpression &binary_expression)
	{
		debug_visit(binary_expression);

		binary_expression.left()->accept(*this);
		llvm::Value *left = next_value();

		binary_expression.right()->accept(*this);
		llvm::Value *right = next_value();

		// TODO(SkillerRaptor): Adding floating point & signed values
		llvm::Value *result = [&]()
		{
			switch (binary_expression.operation())
			{
			case BinaryExpression::Operation::Addition:
				return m_builder->CreateAdd(left, right);
			case BinaryExpression::Operation::Subtraction:
				return m_builder->CreateSub(left, right);
			case BinaryExpression::Operation::Multiplication:
				return m_builder->CreateMul(left, right);
			case BinaryExpression::Operation::Division:
				return m_builder->CreateSDiv(left, right);
			case BinaryExpression::Operation::Equal:
				return m_builder->CreateICmpEQ(left, right);
			case BinaryExpression::Operation::NotEqual:
				return m_builder->CreateICmpNE(left, right);
			case BinaryExpression::Operation::LessThan:
				return m_builder->CreateICmpSLT(left, right);
			case BinaryExpression::Operation::GreaterThan:
				return m_builder->CreateICmpSGT(left, right);
			case BinaryExpression::Operation::LessEqual:
				return m_builder->CreateICmpSLE(left, right);
			case BinaryExpression::Operation::GreaterEqual:
				return m_builder->CreateICmpSGE(left, right);
			default:
				HYPER_UNREACHABLE();
			}
		}();

		m_values.push(result);
	}

	void Generator::visit(const CallExpression &call_expression)
	{
		debug_visit(call_expression);

		for (const ExpressionPtr &expression : call_expression.arguments())
		{
			// TODO(SkillerRaptor): Handle arguments
			expression->accept(*this);
		}

		llvm::Function *function =
			m_module->getFunction(call_expression.function());
		assert(function != nullptr);

		llvm::Value *result = m_builder->CreateCall(function);

		m_values.push(result);
	}

	void Generator::visit(const IdentifierExpression &identifier_expression)
	{
		debug_visit(identifier_expression);

		// TODO(SkillerRaptor): Adding scopes
		llvm::AllocaInst *allocation =
			m_variables[identifier_expression.identifier()];
		assert(allocation != nullptr);

		llvm::Value *result =
			m_builder->CreateLoad(allocation->getAllocatedType(), allocation);

		m_values.push(result);
	}

	void Generator::visit(const NumericLiteral &numeric_literal)
	{
		debug_visit(numeric_literal);

		// TODO(SkillerRaptor): Adding other types & sizes
		llvm::APInt integer =
			llvm::APInt(32, std::stoull(numeric_literal.value()), true);
		llvm::Value *value = llvm::ConstantInt::get(*m_context, integer);

		m_values.push(value);
	}

	void Generator::visit(const StringLiteral &string_literal)
	{
		debug_visit(string_literal);

		// TODO(SkillerRaptor): Implement StringLiteral
		m_values.push(nullptr);
	}

	void Generator::visit(const AssignStatement &assign_statement)
	{
		debug_visit(assign_statement);

		// TODO(SkillerRaptor): Adding scopes
		assign_statement.expression()->accept(*this);
		llvm::Value *result = next_value();

		llvm::AllocaInst *allocation = m_variables[assign_statement.identifier()];
		assert(allocation != nullptr);

		m_builder->CreateStore(result, allocation);
	}

	void Generator::visit(const CompoundStatement &compound_statement)
	{
		debug_visit(compound_statement);

		for (const StatementPtr &statement : compound_statement.statements())
		{
			statement->accept(*this);
		}
	}

	void Generator::visit(const ExpressionStatement &expression_statement)
	{
		debug_visit(expression_statement);

		expression_statement.expression()->accept(*this);
		next_value();
	}

	void Generator::visit(const ForStatement &for_statement)
	{
		debug_visit(for_statement);

		llvm::Function *function = m_builder->GetInsertBlock()->getParent();
		llvm::BasicBlock *condition_block =
			llvm::BasicBlock::Create(*m_context, "", function);
		llvm::BasicBlock *body_block =
			llvm::BasicBlock::Create(*m_context, "", function);
		llvm::BasicBlock *post_block =
			llvm::BasicBlock::Create(*m_context, "", function);
		llvm::BasicBlock *end_block =
			llvm::BasicBlock::Create(*m_context, "", function);

		for_statement.pre_operation()->accept(*this);
		m_builder->CreateBr(condition_block);

		m_builder->SetInsertPoint(condition_block);
		for_statement.condition()->accept(*this);
		llvm::Value *condition = next_value();
		m_builder->CreateCondBr(condition, body_block, end_block);

		m_builder->SetInsertPoint(body_block);
		for_statement.body()->accept(*this);
		m_builder->CreateBr(post_block);

		m_builder->SetInsertPoint(post_block);
		for_statement.post_operation()->accept(*this);
		m_builder->CreateBr(condition_block);

		m_builder->SetInsertPoint(end_block);
	}

	void Generator::visit(const IfStatement &if_statement)
	{
		debug_visit(if_statement);

		llvm::Function *function = m_builder->GetInsertBlock()->getParent();
		llvm::BasicBlock *true_block =
			llvm::BasicBlock::Create(*m_context, "", function);
		llvm::BasicBlock *false_block =
			llvm::BasicBlock::Create(*m_context, "", function);
		llvm::BasicBlock *end_block =
			llvm::BasicBlock::Create(*m_context, "", function);

		if_statement.condition()->accept(*this);
		llvm::Value *condition = next_value();
		m_builder->CreateCondBr(condition, true_block, false_block);

		m_builder->SetInsertPoint(true_block);
		if_statement.true_body()->accept(*this);
		m_builder->CreateBr(end_block);

		m_builder->SetInsertPoint(false_block);
		if_statement.false_body()->accept(*this);
		m_builder->CreateBr(end_block);

		m_builder->SetInsertPoint(end_block);
	}

	void Generator::visit(const PrintStatement &print_statement)
	{
		debug_visit(print_statement);

		// TODO(SkillerRaptor): Implement PrintStatement
		print_statement.expression()->accept(*this);
		llvm::Value *result = next_value();

		HYPER_UNUSED_VARIABLE(result);
	}

	void Generator::visit(const ReturnStatement &return_statement)
	{
		debug_visit(return_statement);

		return_statement.expression()->accept(*this);
		llvm::Value *value = next_value();

		m_builder->CreateRet(value);
	}

	void Generator::visit(const WhileStatement &while_statement)
	{
		debug_visit(while_statement);

		llvm::Function *function = m_builder->GetInsertBlock()->getParent();
		llvm::BasicBlock *condition_block =
			llvm::BasicBlock::Create(*m_context, "", function);
		llvm::BasicBlock *body_block =
			llvm::BasicBlock::Create(*m_context, "", function);
		llvm::BasicBlock *end_block =
			llvm::BasicBlock::Create(*m_context, "", function);

		m_builder->CreateBr(condition_block);

		m_builder->SetInsertPoint(condition_block);
		while_statement.condition()->accept(*this);
		llvm::Value *condition = next_value();
		m_builder->CreateCondBr(condition, body_block, end_block);

		m_builder->SetInsertPoint(body_block);
		while_statement.body()->accept(*this);
		m_builder->CreateBr(condition_block);

		m_builder->SetInsertPoint(end_block);
	}

	llvm::Value *Generator::next_value()
	{
		llvm::Value *value = m_values.top();
		assert(value != nullptr);

		m_values.pop();

		return value;
	}

	void Generator::debug_visit(const AstNode &node) const
	{
		if (!m_debug_mode)
		{
			return;
		}

		Logger::file_info(
			m_file,
			"Generating {} {}\n",
			node.class_name(),
			node.class_description());
	}

	llvm::Type *Generator::to_type(DataType data_type) const
	{
		assert(data_type != DataType::None);

		switch (data_type)
		{
		case DataType::Bool:
			return llvm::Type::getInt1Ty(*m_context);
		case DataType::Int8:
		case DataType::Uint8:
			return llvm::Type::getInt8Ty(*m_context);
		case DataType::Int16:
		case DataType::Uint16:
			return llvm::Type::getInt16Ty(*m_context);
		case DataType::Int32:
		case DataType::Uint32:
			return llvm::Type::getInt32Ty(*m_context);
		case DataType::Int64:
		case DataType::Uint64:
		case DataType::ISize:
		case DataType::USize:
			return llvm::Type::getInt64Ty(*m_context);
		case DataType::Void:
			return llvm::Type::getVoidTy(*m_context);
		default:
			HYPER_UNREACHABLE();
		}
	}
} // namespace Hyper
