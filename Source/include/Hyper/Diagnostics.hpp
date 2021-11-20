/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Logger.hpp"
#include "Hyper/Token.hpp"

#include <string>

namespace Hyper
{
	class Diagnostics
	{
	public:
		Diagnostics(std::string file, std::string text);

		[[noreturn]] void info(
			Token::SourceLocation source_location,
			std::string_view message) const;
		[[noreturn]] void warning(
			 Token::SourceLocation source_location,
			std::string_view message) const;
		[[noreturn]] void error(
			 Token::SourceLocation source_location,
			std::string_view message) const;

	private:
		[[noreturn]] void report(
			Logger::Level level,
			Token::SourceLocation source_location,
			std::string_view message) const;

		std::string get_line_content(size_t line) const;
		size_t get_digit_count(size_t number) const noexcept;

	private:
		std::string m_file;
		std::string m_text;
	};
} // namespace Hyper
