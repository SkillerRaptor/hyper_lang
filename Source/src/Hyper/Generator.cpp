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
	}

	void Generator::visit(const AstNode &node)
	{
		HYPER_UNUSED_VARIABLE(node);
		HYPER_UNREACHABLE();
	}

	void Generator::visit(const FunctionDeclaration &function_declaration)
	{
		debug_visit(function_declaration);
	}

	void Generator::visit(
		const TranslationUnitDeclaration &translation_unit_declaration)
	{
		debug_visit(translation_unit_declaration);
	}

	void Generator::visit(const VariableDeclaration &variable_declaration)
	{
		debug_visit(variable_declaration);
	}

	void Generator::visit(const BinaryExpression &binary_expression)
	{
		debug_visit(binary_expression);
	}

	void Generator::visit(const CallExpression &call_expression)
	{
		debug_visit(call_expression);
	}

	void Generator::visit(const IdentifierExpression &identifier_expression)
	{
		debug_visit(identifier_expression);
	}

	void Generator::visit(const NumericLiteral &numeric_literal)
	{
		debug_visit(numeric_literal);
	}

	void Generator::visit(const StringLiteral &string_literal)
	{
		debug_visit(string_literal);
	}

	void Generator::visit(const AssignStatement &assign_statement)
	{
		debug_visit(assign_statement);
	}

	void Generator::visit(const CompoundStatement &compound_statement)
	{
		debug_visit(compound_statement);
	}

	void Generator::visit(const ExpressionStatement &expression_statement)
	{
		debug_visit(expression_statement);
	}

	void Generator::visit(const ForStatement &for_statement)
	{
		debug_visit(for_statement);
	}

	void Generator::visit(const IfStatement &if_statement)
	{
		debug_visit(if_statement);
	}

	void Generator::visit(const PrintStatement &print_statement)
	{
		debug_visit(print_statement);
	}

	void Generator::visit(const ReturnStatement &return_statement)
	{
		debug_visit(return_statement);
	}

	void Generator::visit(const WhileStatement &while_statement)
	{
		debug_visit(while_statement);
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
} // namespace Hyper
