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
		explicit Scanner(std::string file_text);

		void scan_tokens();

		std::vector<Token> tokens() const;
		
	private:
		std::optional<char> advance() noexcept;

		std::string scan_numeric_literal(char character);

		void add_token(const std::string &value, Token::Type token_type);

		void skip_whitespace() noexcept;
		bool has_reached_end() const noexcept;

	private:
		std::string m_file_text;

		size_t m_position = 0;
		size_t m_line = 1;
		size_t m_column = 1;

		std::vector<Token> m_tokens = {};
	};
} // namespace Hyper
