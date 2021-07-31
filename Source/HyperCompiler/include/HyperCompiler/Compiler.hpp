/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "HyperCompiler/BuildOptions.hpp"

#include <string>
#include <vector>

namespace HyperCompiler
{
	class Lexer;
	
	class Compiler
	{
	public:
		static void compile(const BuildOptions& build_options);
		
	private:
		static void compiler_job(const std::vector<std::string>& files);
		
		static void lex_file(Lexer& lexer, const std::string& file);
		static void parse_file(Lexer& lexer, const std::string& file);
		static void compile_file(const std::string& file);
		
	private:
		static BuildOptions s_build_options;
	};
}
