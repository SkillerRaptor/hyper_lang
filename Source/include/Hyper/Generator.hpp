/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Operators.hpp"

#include <fstream>
#include <string>

namespace Hyper
{
	class AstNode;

	class Generator
	{
	public:
		Generator(const std::string &file, AstNode *ast);

		void generate();

		void generate_operator(Operator op);
		void generate_number(int64_t value);
		
		void generate_open();
		void generate_close();
		
	private:
		void generate_header();
		void generate_footer();
		
		void increase_indent();
		void decrease_indent();

	private:
		std::ofstream m_file;
		AstNode *m_ast = nullptr;
		
		std::string m_indent;
	};
} // namespace Hyper
