/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Generators/CGenerator.hpp"

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

#include <filesystem>
#include <fstream>

namespace Hyper
{
	CGenerator::CGenerator(std::string file)
		: Generator(std::move(file))
	{
	}

	void CGenerator::generate() const
	{
		std::ofstream header_file(m_file + ".h");
		header_file << m_header.str();

		std::ofstream source_file(m_file + ".c");
		source_file << m_source.str();
	}

	void CGenerator::visit(const AstNode &ast)
	{
		Logger::error("CGenerator visit for {} not implemented!", ast.class_name());
		std::abort();
	}

	void CGenerator::visit(const FunctionDeclaration &function_declaration)
	{
		print(
			m_header,
			"{} {}(",
			map_type(function_declaration.return_type()),
			function_declaration.name());
		print(
			m_source,
			"{} {}(",
			map_type(function_declaration.return_type()),
			function_declaration.name());

		for (size_t i = 0; i < function_declaration.arguments().size(); ++i)
		{
			function_declaration.arguments()[i]->accept(*this);

			if (i >= function_declaration.arguments().size() - 1)
			{
				continue;
			}

			print(m_header, ", ");
			print(m_source, ", ");
		}

		print(m_header, ");\n");
		print(m_source, ")\n");

		enter_scope();
		function_declaration.body()->accept(*this);
		leave_scope();
	}

	void CGenerator::visit(
		const TranslationUnitDeclaration &translation_unit_declaration)
	{
		print(m_header, "/*\n");
		print(m_header, " * This file was generated by the C transpiler\n");
		print(m_header, " */\n");
		print(m_header, "\n");
		print(m_header, "#include <stdbool.h>\n");
		print(m_header, "#include <stddef.h>\n");
		print(m_header, "#include <stdint.h>\n");
		print(m_header, "#include <stdio.h>\n");
		print(m_header, "#include <stdlib.h>\n");
		print(m_header, "#include <string.h>\n");
		print(m_header, "\n");

		print(m_source, "/*\n");
		print(m_source, " * This file was generated by the C transpiler\n");
		print(m_source, " */\n");
		print(m_source, "\n");
		print(
			m_source,
			"#include \"{}.h\"\n",
			std::filesystem::path(m_file).filename().string());
		print(m_source, "\n");

		for (const StatementPtr &statement :
				 translation_unit_declaration.statements())
		{
			statement->accept(*this);
		}
	}

	void CGenerator::visit(const VariableDeclaration &variable_declaration)
	{
		const std::string immutable =
			variable_declaration.immutable() == VariableDeclaration::Immutable::Yes
				? "const "
				: "";
		print(
			m_source,
			"{}{}{} {};\n",
			m_indent,
			immutable,
			map_type(variable_declaration.type()),
			variable_declaration.name());
	}

	void CGenerator::visit(const BinaryExpression &binary_expression)
	{
		const std::string operation = [&binary_expression]()
		{
			switch (binary_expression.operation())
			{
			case BinaryExpression::Operation::Addition:
				return "+";
			case BinaryExpression::Operation::Subtraction:
				return "-";
			case BinaryExpression::Operation::Multiplication:
				return "*";
			case BinaryExpression::Operation::Division:
				return "/";
			case BinaryExpression::Operation::Equal:
				return "==";
			case BinaryExpression::Operation::NotEqual:
				return "!=";
			case BinaryExpression::Operation::LessThan:
				return ">";
			case BinaryExpression::Operation::GreaterThan:
				return "<";
			case BinaryExpression::Operation::LessEqual:
				return ">=";
			case BinaryExpression::Operation::GreaterEqual:
				return "<=";
			default:
				std::abort();
			}
		}();

		binary_expression.left()->accept(*this);
		print(m_source, " {} ", operation);
		binary_expression.right()->accept(*this);
	}

	void CGenerator::visit(const CallExpression &call_expression)
	{
		print(m_source, "{}(", call_expression.identifier());

		for (size_t i = 0; i < call_expression.arguments().size(); ++i)
		{
			call_expression.arguments()[i]->accept(*this);

			if (i >= call_expression.arguments().size() - 1)
			{
				continue;
			}

			print(m_source, ", ");
		}

		print(m_source, ")");
	}

	void CGenerator::visit(const IdentifierExpression &identifier_expression)
	{
		m_source << identifier_expression.identifier();
	}

	void CGenerator::visit(const NumericLiteral &numeric_literal)
	{
		m_source << numeric_literal.value();
	}

	void CGenerator::visit(const StringLiteral &string_literal)
	{
		m_source << string_literal.value();
	}

	void CGenerator::visit(const AssignStatement &assign_statement)
	{
		print(m_source, "{}{} = ", m_indent, assign_statement.identifier());
		assign_statement.expression()->accept(*this);
		print(m_source, ";\n");
	}

	void CGenerator::visit(const CompoundStatement &compound_statement)
	{
		for (const StatementPtr &statement : compound_statement.statements())
		{
			statement->accept(*this);
		}
	}

	void CGenerator::visit(const ExpressionStatement &expression_statement)
	{
		print(m_source, "{}", m_indent);
		expression_statement.expression()->accept(*this);
		print(m_source, ";\n");
	}

	void CGenerator::visit(const ForStatement &for_statement)
	{
		for_statement.pre_operation()->accept(*this);
		print(m_source, "{}while (", m_indent);
		for_statement.condition()->accept(*this);
		print(m_source, ")\n");

		enter_scope();
		for_statement.body()->accept(*this);
		for_statement.post_operation()->accept(*this);
		leave_scope();
	}

	void CGenerator::visit(const IfStatement &if_statement)
	{
		print(m_source, "{}if (", m_indent);
		if_statement.condition()->accept(*this);
		print(m_source, ")\n");

		enter_scope();
		if_statement.true_branch()->accept(*this);
		leave_scope();

		if (if_statement.false_branch() != nullptr)
		{
			enter_scope();
			if_statement.false_branch()->accept(*this);
			leave_scope();
		}
	}

	void CGenerator::visit(const PrintStatement &print_statement)
	{
		print(m_source, R"({}printf("%d\n", )", m_indent);
		print_statement.expression()->accept(*this);
		print(m_source, ");\n");
	}

	void CGenerator::visit(const ReturnStatement &return_statement)
	{
		print(m_source, "{}return ", m_indent);
		return_statement.expression()->accept(*this);
		print(m_source, ";\n");
	}

	void CGenerator::visit(const WhileStatement &while_statement)
	{
		print(m_source, "{}while (", m_indent);
		while_statement.condition()->accept(*this);
		print(m_source, ")\n");

		enter_scope();
		while_statement.body()->accept(*this);
		leave_scope();
	}

	void CGenerator::enter_scope()
	{
		print(m_source, "{}{{\n", m_indent);
		m_indent += '\t';
	}

	void CGenerator::leave_scope()
	{
		m_indent.pop_back();
		print(m_source, "{}}\n", m_indent);
	}

	std::string CGenerator::map_type(Type type) const
	{
		switch (type)
		{
		case Type::Bool:
			return "bool";
		case Type::Int8:
			return "int8_t";
		case Type::Int16:
			return "int16_t";
		case Type::Int32:
			return "int32_t";
		case Type::Int64:
			return "int64_t";
		case Type::Uint8:
			return "uint8_t";
		case Type::Uint16:
			return "uint16_t";
		case Type::Uint32:
			return "uint32_t";
		case Type::Uint64:
			return "uint64_t";
		case Type::ISize:
			return "size_t";
		case Type::USize:
			return "int64_t";
		case Type::Void:
			return "void";
		default:
			break;
		}

		return "";
	}
} // namespace Hyper
