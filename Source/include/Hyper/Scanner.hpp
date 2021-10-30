/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Token.hpp"

#include <optional>
#include <string>
#include <vector>

namespace Hyper
{
	class Scanner
	{
	public:
		Scanner(std::string file, std::string text);

		std::vector<Token> scan_tokens();

	private:
		char advance() noexcept;
		char peek() const noexcept;
		void revert() noexcept;

		void skip_whitespace() noexcept;
		bool has_reached_end() const noexcept;

		void add_token(
			std::vector<Token> &tokens,
			const std::string &value,
			Token::Type token_type);

		std::string scan_numeric_literal(char character);
		std::string scan_identifier(char character);
		Token::Type scan_keyword(const std::string &identifier);

	private:
		std::string m_file;
		std::string m_text;

		size_t m_position = 0;
		size_t m_line = 1;
		size_t m_column = 0;
	};
} // namespace Hyper
