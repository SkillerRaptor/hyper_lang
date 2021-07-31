/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "HyperCompiler/Token.hpp"

#include <fstream>
#include <string>

namespace HyperCompiler
{
	class Lexer
	{
	public:
		void initialize(const std::string& file_name, const std::string& source);

		Token next_token();

	private:
		char next_character();
		void skip_whitespace();

		int64_t scan_int(char character);
		std::string scan_string();
		std::string scan_identifier(char character);
		
		static Token::Type get_keyword(const std::string& keyword);

	private:
		std::string s_file_name;
		std::string s_source;
		size_t s_line{ 1 };
		size_t s_line_position{ 0 };
		size_t s_current_position{ 0 };
	};
} // namespace HyperCompiler
