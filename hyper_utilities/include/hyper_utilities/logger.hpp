/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper_utilities/formatter.hpp"
#include "hyper_utilities/profiler.hpp"

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
			Debug,
		};

	public:
		template <typename... Args>
		static void log(std::string_view format, Args &&...args)
		{
			HYPER_PROFILE_FUNCTION();

			log_helper(Level::None, format, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void info(std::string_view format, Args &&...args)
		{
			HYPER_PROFILE_FUNCTION();

			log_helper(Level::Info, format, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void warn(std::string_view format, Args &&...args)
		{
			HYPER_PROFILE_FUNCTION();

			log_helper(Level::Warning, format, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void error(std::string_view format, Args &&...args)
		{
			HYPER_PROFILE_FUNCTION();

			log_helper(Level::Error, format, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void debug(std::string_view format, Args &&...args)
		{
			HYPER_PROFILE_FUNCTION();

			log_helper(Level::Debug, format, std::forward<Args>(args)...);
		}

	private:
		template <typename... Args>
		static void log_helper(Level level, std::string_view format, Args &&...args)
		{
			HYPER_PROFILE_FUNCTION();

			const std::string_view level_color = [level]()
			{
				switch (level)
				{
				case Level::Info:
					return "\033[32m";
				case Level::Warning:
					return "\033[33m";
				case Level::Error:
					return "\033[31m";
				case Level::Debug:
					return "\033[36m";
				case Level::None:
				default:
					return "";
				}
			}();

			const std::string_view level_name = [level]()
			{
				switch (level)
				{
				case Level::Info:
					return "info";
				case Level::Warning:
					return "warning";
				case Level::Error:
					return "error";
				case Level::Debug:
					return "debug";
				case Level::None:
				default:
					return "";
				}
			}();

			const std::string string = [&]()
			{
				const std::string formatted_string =
					Formatter::format(format, std::forward<Args>(args)...);
				if (level == Level::None)
				{
					return formatted_string;
				}

				std::ostringstream format_stream;
				format_stream << "\033[37m";
				format_stream << "hyper";
				format_stream << "\033[0m: ";
				format_stream << level_color;
				format_stream << level_name;
				format_stream << "\033[0m: ";
				format_stream << formatted_string;
				return format_stream.str();
			}();

			fwrite(string.c_str(), string.length(), 1, stdout);
		}
	};
} // namespace hyper
