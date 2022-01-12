/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Formatter.hpp"
#include "Hyper/SourceRange.hpp"

#include <string>
#include <string_view>

namespace Hyper
{
	class Diagnostics
	{
	public:
		enum class Level : uint8_t
		{
			Info = 0,
			Warning,
			Error,
		};

	public:
		Diagnostics(std::string file, std::string text);

		template <typename... Args>
		void info(
			const SourceRange &source_range,
			std::string_view format,
			Args &&...args) const
		{
			if constexpr (sizeof...(Args) == 0)
			{
				report(Level::Info, source_range, format);
				return;
			}
			else
			{
				report(
					Level::Info,
					source_range,
					Formatter::format(format, std::forward<Args>(args)...));
			}
		}

		template <typename... Args>
		void warn(
			const SourceRange &source_range,
			std::string_view format,
			Args &&...args) const
		{
			if constexpr (sizeof...(Args) == 0)
			{
				report(Level::Info, source_range, format);
				return;
			}
			else
			{
				report(
					Level::Warning,
					source_range,
					Formatter::format(format, std::forward<Args>(args)...));
			}
		}

		template <typename... Args>
		[[noreturn]] void error(
			const SourceRange &source_range,
			std::string_view format,
			Args &&...args) const
		{
			if constexpr (sizeof...(Args) == 0)
			{
				report(Level::Error, source_range, format);
			}
			else
			{
				report(
					Level::Error,
					source_range,
					Formatter::format(format, std::forward<Args>(args)...));
			}

			std::exit(1);
		}

	private:
		void report(
			Level level,
			const SourceRange &source_range,
			std::string_view message) const;

		std::string get_line_content(size_t line) const;
		size_t get_digit_count(size_t number) const noexcept;

	private:
		std::string m_file;
		std::string m_text;
	};
} // namespace Hyper
