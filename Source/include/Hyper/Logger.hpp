/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Formatter.hpp"
#include "Hyper/Prerequisites.hpp"

#include <iostream>
#include <sstream>
#include <string_view>

namespace Hyper
{
	class Logger
	{
	public:
		enum class Level
		{
			None = 0,
			Info,
			Warning,
			Error
		};

	public:
		template <typename... Args>
		static void raw(std::string_view format, Args &&...args)
		{
			log_base(Level::None, "", format, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void log(Level level, std::string_view format, Args &&...args)
		{
			log_base(level, "hyper", format, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void info(std::string_view format, Args &&...args)
		{
			log_base(Level::Info, "hyper", format, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void warning(std::string_view format, Args &&...args)
		{
			log_base(Level::Warning, "hyper", format, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void error(std::string_view format, Args &&...args)
		{
			log_base(Level::Error, "hyper", format, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void file_log(
			Level level,
			std::string_view file,
			std::string_view format,
			Args &&...args)
		{
			log_base(level, file, format, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void file_info(
			std::string_view file,
			std::string_view format,
			Args &&...args)
		{
			log_base(Level::Info, file, format, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void file_warning(
			std::string_view file,
			std::string_view format,
			Args &&...args)
		{
			log_base(Level::Warning, file, format, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void file_error(
			std::string_view file,
			std::string_view format,
			Args &&...args)
		{
			log_base(Level::Error, file, format, std::forward<Args>(args)...);
		}

	private:
		template <typename... Args>
		static void log_base(
			Level level,
			std::string_view prefix,
			std::string_view format,
			Args &&...args)
		{
			std::stringstream string_stream;
			if (!prefix.empty())
			{
				string_stream << prefix;
				string_stream << ": ";
			}

			if (level != Level::None)
			{
				const std::string_view level_color = [&level]()
				{
					switch (level)
					{
					case Level::Info:
						return Formatter::s_color_green;
					case Level::Warning:
						return Formatter::s_color_yellow;
					case Level::Error:
						return Formatter::s_color_red;
					default:
						HYPER_UNREACHABLE();
					}
				}();

				const std::string_view level_string = [&level]()
				{
					switch (level)
					{
					case Level::Info:
						return "info";
					case Level::Warning:
						return "warning";
					case Level::Error:
						return "error";
					default:
						HYPER_UNREACHABLE();
					}
				}();

				string_stream << level_color;
				string_stream << level_string;
				string_stream << Formatter::s_color_reset;
				string_stream << ": ";
			}

			const std::string string = format.data();
			string_stream << Formatter::format(string, std::forward<Args>(args)...);

			std::cout << string_stream.str();
		}
	};
} // namespace Hyper
