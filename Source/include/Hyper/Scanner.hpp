/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Token.hpp"

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace Hyper
{
	class Scanner
	{
	public:
		Scanner(std::string file, std::string text, bool debug_mode);

		Token next_token();

	private:
		void debug_scan(const Token &token) const;

		void register_keywords();
		void register_single_char_tokens();
		void register_two_char_tokens();

		void consume();

		Token::Type scan_identifier(size_t start, size_t &length);
		Token::Type scan_number(size_t &length);
		Token::Type scan_string(size_t &length);
		Token::Type scan_short_tokens(size_t start, size_t &length);

	private:
		std::string m_file;
		std::string m_text;
		bool m_debug_mode = false;

		size_t m_position = 0;
		size_t m_line_number = 1;
		size_t m_line_column = 0;

		char m_current_character = '\0';
		Token m_current_token = {};

		std::unordered_map<std::string_view, Token::Type> m_keywords;
		std::unordered_map<std::string_view, Token::Type> m_single_char_tokens;
		std::unordered_map<std::string_view, Token::Type> m_two_char_tokens;
	};
} // namespace Hyper
