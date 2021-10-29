/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Generator.hpp"

#include "Hyper/Ast/AstNode.hpp"

#include <iostream>

namespace Hyper
{
	Generator::Generator(const std::string &file, AstNode *ast)
		: m_file(file + ".c")
		, m_ast(ast)
	{
	}

	void Generator::generate()
	{
		generate_header();

		m_ast->generate(*this);

		generate_footer();
	}

	void Generator::generate_operator(Operator op)
	{
		const std::string operator_string = [&op]()
		{
			switch (op)
			{
			case Operator::Plus:
				return "+";
			case Operator::Minus:
				return "-";
			case Operator::Star:
				return "*";
			case Operator::Slash:
				return "/";
			default:
				return "";
			}
		}();

		m_file << " " << operator_string << " ";
	}

	void Generator::generate_number(int64_t value)
	{
		m_file << value;
	}
	
	void Generator::generate_open()
	{
		m_file << m_indent << "{\n";
		increase_indent();
	}
	
	void Generator::generate_close()
	{
		decrease_indent();
		m_file << "}\n";
	}
	
	void Generator::generate_header()
	{
		m_file << "#include <stdio.h>\n";
		m_file << '\n';
		m_file << "int main()\n";
		generate_open();
		
		m_file << m_indent << R"(println("%d\n", )"; // NOTE(SkillerRaptor): Temporary
	}

	void Generator::generate_footer()
	{
		m_file << ");\n"; // NOTE(SkillerRaptor): Temporary
		
		generate_close();
	}

	void Generator::increase_indent()
	{
		m_indent += '\t';
	}
	
	void Generator::decrease_indent()
	{
		m_indent.pop_back();
	}
} // namespace Hyper
