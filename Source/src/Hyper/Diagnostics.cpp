/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Diagnostics.hpp"

namespace Hyper
{
	Diagnostics::Diagnostics(std::string file, std::string text)
		: m_file(std::move(file))
		, m_text(std::move(text))
	{
	}

	void Diagnostics::info(
		Token::SourceLocation source_location,
		std::string_view message) const
	{
		report(Logger::Level::Info, source_location, message);
	}

	void Diagnostics::warning(
		Token::SourceLocation source_location,
		std::string_view message) const
	{
		report(Logger::Level::Warning, source_location, message);
	}

	void Diagnostics::error(
		Token::SourceLocation source_location,
		std::string_view message) const
	{
		report(Logger::Level::Error, source_location, message);
	}

	void Diagnostics::report(
		Logger::Level level,
		Token::SourceLocation source_location,
		std::string_view message) const
	{
		const std::string file = Formatter::format(
			"{}:{}:{}", m_file, source_location.line, source_location.column);
		Logger::file_log(level, file, message);

		const std::string line_content = get_line_content(source_location.line);
		Logger::raw("{} | {}\n", source_location.line, line_content);

		std::string line_spaces;
		for (size_t i = 0; i < get_digit_count(source_location.line) - 1; ++i)
		{
			line_spaces += ' ';
		}

		std::string error_line;
		for (size_t i = 0; i < source_location.column - 1; ++i)
		{
			const char character = line_content[i];
			error_line += (character == '\t' ? '\t' : ' ');
		}

		error_line += '^';
		for (size_t i = 0; i < source_location.length - 1; ++i)
		{
			error_line += '~';
		}

		Logger::raw(" {} | {}\n", line_spaces, error_line);
		std::abort();
	}

	std::string Diagnostics::get_line_content(size_t line) const
	{
		std::string line_content;

		size_t current_line = 1;
		for (const char character : m_text)
		{
			if (current_line == line)
			{
				if (character != '\n')
				{
					line_content += character;
				}
			}

			if (character == '\n')
			{
				if (++current_line == (line + 1))
				{
					break;
				}
			}
		}

		return line_content;
	}

	size_t Diagnostics::get_digit_count(size_t number) const noexcept
	{
		size_t count = 0;
		while (number != 0)
		{
			number /= 10;
			++count;
		}

		return count;
	}
} // namespace Hyper
