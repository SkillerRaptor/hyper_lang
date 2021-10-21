/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Diagnostics.hpp"

namespace Hyper
{
	Diagnostics::Diagnostics(
		std::string file_name,
		std::string file_text)
		: m_file_name(std::move(file_name))
		, m_file_text(std::move(file_text))
	{
		size_t line = 1;
		for (const char character : m_file_text)
		{
			if (character != '\n')
			{
				continue;
			}

			++line;
		}

		m_file_line_count = line;
		m_file_line_digit_count = get_digit_count(m_file_line_count);
	}

	void Diagnostics::report(
		const Level level,
		const SourceLocation source_location,
		const std::string_view message)
	{
		const Logger::Level report_level = [level]()
		{
			switch (level)
			{
			case Level::Warning:
				return Logger::Level::Warning;
			case Level::Error:
				return Logger::Level::Error;
			default:
				return Logger::Level::Info;
			}
		}();

		const std::string file_prefix = Logger::format(
			"{}:{}:{}",
			m_file_name,
			source_location.line,
			source_location.column);
		Logger::log(file_prefix, report_level, message);
		Logger::log_raw("\n");

		constexpr size_t line_count = 2;

		print_pre_line(source_location.line, line_count);
		print_line(source_location.line);
		print_error_line(
			source_location.line,
			source_location.column,
			source_location.length);
		print_post_line(source_location.line, line_count);
	}

	void Diagnostics::print_line(const size_t line) const
	{
		const std::string line_content = get_line_content(line);
		Logger::log_raw(
			" {:>{}} | {}\n", line, get_line_offset(line) + 1, line_content);
	}

	void Diagnostics::print_pre_line(const size_t line, const size_t line_count)
		const
	{
		for (size_t i = line_count; i > 0; --i)
		{
			print_line(line - i);
		}
	}

	void Diagnostics::print_post_line(
		const size_t line,
		const size_t line_count) const
	{
		for (size_t i = 0; i < line_count; ++i)
		{
			print_line(line + i + 1);
		}
	}

	void Diagnostics::print_error_line(
		const size_t line,
		const size_t column,
		const size_t length) const
	{
		std::string error_line = "";

		const std::string current_line_text = get_line_content(line);
		for (size_t i = 0; i < column - 1; ++i)
		{
			const char character = current_line_text[i];
			error_line += (character == '\t' ? '\t' : ' ');
		}

		error_line += '^';
		for (size_t i = 0; i < length - 1; ++i)
		{
			error_line += '~';
		}

		const size_t line_offset =
			get_line_offset(line) + get_digit_count(line);
		Logger::log_raw(" {:>{}} | {}\n", "", line_offset, error_line);
	}

	std::string Diagnostics::get_line_content(
		const size_t line) const noexcept
	{
		size_t begin = 0;
		size_t end = 0;
		bool found = false;

		size_t current_line = 1;
		for (size_t i = 0; i < m_file_text.size(); ++i)
		{
			const char character = m_file_text[i];
			if (!found && current_line == line)
			{
				begin = i;
				found = true;
			}

			if (found && current_line == line + 1)
			{
				end = i;
				break;
			}

			if (character == '\n')
			{
				++current_line;
			}
		}

		return m_file_text.substr(begin, end - begin - 1);
	}

	size_t Diagnostics::get_digit_count(const size_t number) const noexcept
	{
		size_t count = 0;
		size_t current_number = number;
		while (current_number != 0)
		{
			current_number /= 10;
			++count;
		}

		return count;
	}

	size_t Diagnostics::get_line_offset(const size_t number) const noexcept
	{
		return m_file_line_digit_count - get_digit_count(number);
	}
} // namespace Hyper
