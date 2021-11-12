/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Formatter.hpp"

#include <iostream>
#include <sstream>
#include <string_view>

namespace Hyper
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
		static void raw(std::string_view string, Args &&...args)
		{
			log_base(Level::None, "", string, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void info(std::string_view string, Args &&...args)
		{
			log_base(Level::Info, "hyper", string, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void warning(std::string_view string, Args &&...args)
		{
			log_base(Level::Warning, "hyper", string, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void error(std::string_view string, Args &&...args)
		{
			log_base(Level::Error, "hyper", string, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void debug(std::string_view string, Args &&...args)
		{
			log_base(Level::Debug, "hyper", string, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void file_info(
			std::string_view file,
			std::string_view string,
			Args &&...args)
		{
			log_base(Level::Info, file, string, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void file_warning(
			std::string_view file,
			std::string_view string,
			Args &&...args)
		{
			log_base(Level::Warning, file, string, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void file_error(
			std::string_view file,
			std::string_view string,
			Args &&...args)
		{
			log_base(Level::Error, file, string, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void file_debug(
			std::string_view file,
			std::string_view string,
			Args &&...args)
		{
			log_base(Level::Debug, file, string, std::forward<Args>(args)...);
		}

	private:
		template <typename... Args>
		static void log_base(
			Level level,
			std::string_view prefix,
			std::string_view string,
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
						return "\033[32m";
					case Level::Warning:
						return "\033[33m";
					case Level::Error:
						return "\033[31m";
					case Level::Debug:
						return "\033[36m";
					default:
						std::abort();
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
					case Level::Debug:
						return "debug";
					default:
						std::abort();
					}
				}();

				string_stream << level_color;
				string_stream << level_string;
				string_stream << "\033[0m";
				string_stream << ": ";
			}

			const std::string real_string = string.data();
			string_stream << Formatter::format(
				real_string, std::forward<Args>(args)...);

			std::cout << string_stream.str();
		}
	};
} // namespace Hyper
