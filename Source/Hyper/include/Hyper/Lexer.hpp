/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Token.hpp"

#include <cstddef>
#include <cstdint>
#include <string>

namespace Hyper
{
	class Lexer
	{
	public:
		explicit Lexer(std::string t_file);

		auto initialize() -> bool;

		auto next_token() -> Token;

	private:
		auto next_character() -> char;
		auto skip_next_whitespace() -> void;

		auto scan_numeric_literal(char character) -> int64_t;
		auto character_to_number(const std::string& source, char character) -> int64_t;

	private:
		std::string m_file;
		std::string m_text;

		size_t m_position{ 0 };

		size_t m_line{ 1 };
		size_t m_column{ 1 };
	};
} // namespace Hyper
