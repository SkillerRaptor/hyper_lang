/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/formatter.hpp"

#include <string>
#include <string_view>

namespace hyper
{
	class Logger
	{
	private:
		enum class Level
		{
			None = 0,
			Info,
			Warning,
			Error,
			Debug
		};

	public:
		template <typename... Args>
		static void log(std::string_view format, Args &&...args)
		{
			log(Level::None, format, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void info(std::string_view format, Args &&...args)
		{
			log(Level::Info, format, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void warn(std::string_view format, Args &&...args)
		{
			log(Level::Warning, format, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void error(std::string_view format, Args &&...args)
		{
			log(Level::Error, format, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void debug(std::string_view format, Args &&...args)
		{
			log(Level::Debug, format, std::forward<Args>(args)...);
		}

	private:
		template <typename... Args>
		static void log(Level level, std::string_view format, Args &&...args)
		{
			const char *color_string = [level]()
			{
				switch (level)
				{
				case Level::None:
					return "";
				case Level::Info:
					return "\033[32m";
				case Level::Warning:
					return "\033[33m";
				case Level::Error:
					return "\033[31m";
				case Level::Debug:
					return "\033[36m";
				default:
					return "";
				}
			}();

			const char *level_string = [level]()
			{
				switch (level)
				{
				case Level::None:
					return "";
				case Level::Info:
					return "info";
				case Level::Warning:
					return "warning";
				case Level::Error:
					return "error";
				case Level::Debug:
					return "debug";
				default:
					return "";
				}
			}();

			const std::string format_string =
				Formatter::format(format, std::forward<Args>(args)...);
			const std::string string =
				[level, color_string, level_string, &format_string]()
			{
				if (level == Level::None)
				{
					return format_string;
				}

				std::stringstream stream;
				stream << "\033[37m";
				stream << "hyper";
				stream << "\033[0m: ";
				stream << color_string;
				stream << level_string;
				stream << "\033[0m: ";
				stream << format_string;
				return stream.str();
			}();

			fwrite(string.c_str(), string.length(), 1, stdout);
		}
	};
} // namespace hyper
