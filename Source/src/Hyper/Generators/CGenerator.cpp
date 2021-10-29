/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Generators/CGenerator.hpp"

#include "Hyper/Ast/Expressions/BinaryExpression.hpp"
#include "Hyper/Ast/Literals/NumericLiteral.hpp"

#include <iostream>

namespace Hyper
{
	CGenerator::CGenerator(std::string file)
		: Generator(std::move(file))
		, m_output_file(m_file + ".c")
	{
	}

	void CGenerator::generate_pre()
	{
		m_output_file << "#include <stdio.h>\n";
		m_output_file << "\n";
		m_output_file << "int main()\n";

		enter_scope();
		
		m_output_file << m_indent << R"(println("%d\n", )"; // NOTE(SkillerRaptor): Temporary
	}

	void CGenerator::generate_post()
	{
		m_output_file << ");\n"; // NOTE(SkillerRaptor): Temporary
		
		leave_scope();
	}

	void CGenerator::visit(const AstNode &ast_node)
	{
		std::cerr << "Visit for " << ast_node.class_name() << "not implemented!";
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
			default:
				// TODO(SkillerRaptor): Error handling
				std::abort();
			}
		}();

		m_output_file << " " << operation << " ";
	}

	void CGenerator::visit(const NumericLiteral &numeric_literal)
	{
		m_output_file << numeric_literal.value();
	}

	void CGenerator::enter_scope()
	{
		m_output_file << m_indent << "{\n";
		m_indent += '\t';
	}

	void CGenerator::leave_scope()
	{
		m_indent.pop_back();
		m_output_file << m_indent << "}\n";
	}
} // namespace Hyper
