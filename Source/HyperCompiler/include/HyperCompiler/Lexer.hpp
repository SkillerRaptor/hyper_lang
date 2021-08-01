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
		Token current_token() const;

	private:
		char next_character();
		void skip_whitespace();

		int64_t scan_int(char character);
		std::string scan_string();
		std::string scan_identifier(char character);
		
		static Token::Type get_keyword(const std::string& keyword);

	private:
		std::string m_file_name;
		std::string m_source;
		size_t m_line{ 1 };
		size_t m_line_position{ 0 };
		size_t m_current_position{ 0 };
		Token m_current_token{};
	};
} // namespace HyperCompiler
