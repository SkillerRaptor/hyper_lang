/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Token.hpp"

#include <string>

namespace Hyper
{
	class Lexer
	{
	public:
		Lexer(std::string file_name, std::string file_text);

		Token next_token();

	private:
		Token new_token(const std::string &value, Token::Type token_type);

		std::string scan_numeric_literal(char character);

		void skip_whitespace() noexcept;

		char advance() noexcept;
		char peek() const noexcept;
		void revert() noexcept;

	private:
		std::string m_file_name;
		std::string m_file_text;

		size_t m_position = 0;
		size_t m_line = 1;
		size_t m_column = 1;
	};
} // namespace Hyper
