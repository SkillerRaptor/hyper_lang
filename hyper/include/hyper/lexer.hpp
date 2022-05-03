/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/token.hpp"

#include <string>
#include <vector>

namespace hyper
{
	class Diagnostics;

	class Lexer
	{
	public:
		Lexer(const Diagnostics &diagnostics, std::string_view text);

		std::vector<Token> lex();

	private:
		Token next_token();

		void advance() noexcept;
		char peek() const noexcept;

		void skip_whitespace() noexcept;
		bool has_reached_end() const noexcept;

		Token lex_comment() noexcept;
		Token lex_block_comment() noexcept;

		std::string lex_string();
		std::string lex_identifier();

		std::pair<std::string, Token::Type> lex_numeric_literal();
		std::pair<std::string, Token::Type> lex_decimal_literal();
		std::string lex_binary_literal();
		std::string lex_oct_literal();
		std::string lex_hex_literal();

		Token::Type fetch_type(std::string_view value) const noexcept;

	private:
		const Diagnostics &m_diagnostics;
		std::string_view m_text;

		char m_current_char = '\0';

		size_t m_index = 0;
		size_t m_line = 1;
		size_t m_column = 0;
	};
} // namespace hyper
