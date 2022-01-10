/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Diagnostics.hpp"

#include "Hyper/Logger.hpp"

namespace Hyper
{
	Diagnostics::Diagnostics(std::string file, std::string text)
		: m_file(std::move(file))
		, m_text(std::move(text))
	{
	}

	void Diagnostics::info(
		const SourceRange &source_range,
		std::string_view message) const
	{
		report(Level::Info, source_range, message);
	}

	void Diagnostics::warn(
		const SourceRange &source_range,
		std::string_view message) const
	{
		report(Level::Warning, source_range, message);
	}

	void Diagnostics::error(
		const SourceRange &source_range,
		std::string_view message) const
	{
		report(Level::Error, source_range, message);
		std::exit(1);
	}

	void Diagnostics::report(
		Diagnostics::Level level,
		const SourceRange &source_range,
		std::string_view message) const
	{
		switch (level)
		{
		case Level::Info:
			Logger::info("{}\n", message);
			break;
		case Level::Warning:
			Logger::warn("{}\n", message);
			break;
		case Level::Error:
			Logger::error("{}\n", message);
			break;
		}

		const Position &start = source_range.start;
		const Position &end = source_range.end;

		const size_t digit_count = get_digit_count(end.line);
		const std::string spaces(digit_count, ' ');
		const std::string extra_spaces(
			digit_count - get_digit_count(start.line), ' ');

		Logger::log("{}--> {}:{}:{}\n", spaces, m_file, start.line, start.column);
		Logger::log("{} |\n", spaces);

		if (start.line == end.line)
		{
			const std::string start_spaces(start.column - 1, ' ');
			const std::string tilde_pointers(end.column - start.column, '~');

			Logger::log(
				"{}{} | {}\n", extra_spaces, start.line, get_line_content(start.line));
			Logger::log("{} | {}^{}\n", spaces, start_spaces, tilde_pointers);
		}
		else
		{
			const std::string start_underscore(start.column, '_');
			const std::string end_underscore(end.column, '_');

			Logger::log(
				"{}{} |   {}\n",
				extra_spaces,
				start.line,
				get_line_content(start.line));
			Logger::log("{} |  {}^\n", spaces, start_underscore);
			Logger::log("{} | | {}\n", end.line, get_line_content(end.line));
			Logger::log("{} | |{}^\n", spaces, end_underscore);
		}

		Logger::log("{} |\n", spaces);
	}

	std::string Diagnostics::get_line_content(size_t line) const
	{
		std::string content;

		size_t current_line = 1;
		for (const char character : m_text)
		{
			if (current_line == line)
			{
				if (character == '\t')
				{
					content += "  ";
					continue;
				}

				if (character != '\n')
				{
					content += character;
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

		return content;
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
