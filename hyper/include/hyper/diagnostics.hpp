/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/logger.hpp"
#include "hyper/source_range.hpp"
#include "hyper/utilities.hpp"

#include <string>
#include <string_view>

namespace hyper
{
	class Diagnostics
	{
	public:
		enum class ErrorCode : uint8_t
		{
			E0001,
			E0002,
			E0003,
			E0004,
			E0005,
			E0006,
			E0007,
			E0008,
		};

	public:
		Diagnostics() = default;
		Diagnostics(std::string file, std::string text);

		template <typename... Args>
		void info(SourceRange source_range, ErrorCode error_code, Args &&...args)
			const
		{
			(void) source_range;
			Logger::info(fetch_message(error_code), std::forward<Args>(args)...);

			// FIXME: Implement this function
		}

		template <typename... Args>
		void warn(SourceRange source_range, ErrorCode error_code, Args &&...args)
			const
		{
			(void) source_range;
			Logger::warn(fetch_message(error_code), std::forward<Args>(args)...);

			// FIXME: Implement this function
		}

		template <typename... Args>
		[[noreturn]] void error(
			SourceRange source_range,
			ErrorCode error_code,
			Args &&...args) const
		{
			Logger::error(fetch_message(error_code), std::forward<Args>(args)...);

			Position start = source_range.start;
			Position end = source_range.end;

			const size_t digit_count = Utilities::count_digits(end.line);
			const std::string spaces(digit_count, ' ');
			const std::string extra_spaces(
				digit_count - Utilities::count_digits(start.line), ' ');

			Logger::log("{}--> {}:{}:{}", spaces, m_file, start.line, start.column);
			Logger::log("{} |", spaces);

			if (start.line == end.line)
			{
				const std::string start_spaces(start.column - 1, ' ');
				const std::string tilde_pointers(end.column - start.column, '~');

				Logger::log(
					"{}{} | {}",
					extra_spaces,
					start.line,
					Utilities::read_line(m_text, start.line));
				Logger::log("{} | {}^{}", spaces, start_spaces, tilde_pointers);
			}
			else
			{
				const std::string start_underscore(start.column, '_');
				const std::string end_underscore(end.column, '_');

				Logger::log(
					"{}{} |   {}",
					extra_spaces,
					start.line,
					Utilities::read_line(m_text, start.line));
				Logger::log("{} |  {}^", spaces, start_underscore);
				Logger::log(
					"{} | | {}", end.line, Utilities::read_line(m_text, end.line));
				Logger::log("{} | |{}^", spaces, end_underscore);
			}

			Logger::log("{} |", spaces);

			std::exit(1);
		}

	private:
		static constexpr std::string_view fetch_message(
			ErrorCode error_code) noexcept
		{
			switch (error_code)
			{
			case ErrorCode::E0001:
				return "unterminated block comment";
			case ErrorCode::E0002:
				return "unterminated double quote string";
			case ErrorCode::E0003:
				return "expected '{}', found '{}'";
			case ErrorCode::E0004:
				return "use of undeclared identifier '{}'";
			case ErrorCode::E0005:
				return "redefinition of identifier '{}'";
			case ErrorCode::E0006:
				return "assigning '{}' to a variable with incompatible type '{}'";
			case ErrorCode::E0007:
				return "cannot export '{}'";
			case ErrorCode::E0008:
				return "cannot extern '{}'";
			}

			std::abort();
		}

	private:
		std::string m_file;
		std::string m_text;
	};
} // namespace hyper
