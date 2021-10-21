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

		[[nodiscard]] Token scan_next_token();

	private:
		void skip_whitespace() noexcept;

		void revert() noexcept;
		char advance() noexcept;
		[[nodiscard]] char peek() const noexcept;

		[[nodiscard]] SourceLocation current_location(
			size_t length) const noexcept;

	private:
		std::string m_file_name = {};
		std::string m_file_text = {};

		size_t m_position = { 0 };
		size_t m_line = { 1 };
		size_t m_column = { 1 };
	};
} // namespace Hyper
