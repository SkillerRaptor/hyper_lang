/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Formatter.hpp"

#include <string>
#include <string_view>

namespace Hyper::Logger
{
	namespace Detail
	{
		enum class Level
		{
			None = 0,
			Info,
			Warning,
			Error,
			Debug
		};

		template <typename... Args>
		void log(
			std::string_view prefix,
			Level level,
			std::string_view format,
			Args &&...args)
		{
			const std::string_view color_string = [level]()
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
					std::abort();
				}
			}();

			const std::string_view level_string = [level]()
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
					std::abort();
				}
			}();

			const std::string format_string =
				Formatter::format(format, std::forward<Args>(args)...);
			const std::string string = [&]()
			{
				std::stringstream string_stream;
				if (!prefix.empty())
				{
					string_stream << "\033[37m";
					string_stream << prefix;
					string_stream << "\033[0m: ";
				}
				if (level != Level::None)
				{
					string_stream << color_string;
					string_stream << level_string;
					string_stream << "\033[0m: ";
				}
				string_stream << format_string;
				return string_stream.str();
			}();

			fwrite(string.c_str(), string.length(), 1, stdout);
		}
	} // namespace Detail

	template <typename... Args>
	void log(std::string_view format, Args &&...args)
	{
		Detail::log("", Detail::Level::None, format, std::forward<Args>(args)...);
	}

	template <typename... Args>
	void info(std::string_view format, Args &&...args)
	{
		Detail::log(
			"hyper", Detail::Level::Info, format, std::forward<Args>(args)...);
	}

	template <typename... Args>
	void warning(std::string_view format, Args &&...args)
	{
		Detail::log(
			"hyper", Detail::Level::Warning, format, std::forward<Args>(args)...);
	}

	template <typename... Args>
	void error(std::string_view format, Args &&...args)
	{
		Detail::log(
			"hyper", Detail::Level::Error, format, std::forward<Args>(args)...);
	}

	template <typename... Args>
	void debug(std::string_view format, Args &&...args)
	{
		Detail::log(
			"hyper", Detail::Level::Debug, format, std::forward<Args>(args)...);
	}

	template <typename... Args>
	void file_info(
		std::string_view prefix,
		std::string_view format,
		Args &&...args)
	{
		Detail::log(
			prefix, Detail::Level::Info, format, std::forward<Args>(args)...);
	}

	template <typename... Args>
	void file_warning(
		std::string_view prefix,
		std::string_view format,
		Args &&...args)
	{
		Detail::log(
			prefix, Detail::Level::Warning, format, std::forward<Args>(args)...);
	}

	template <typename... Args>
	void file_error(
		std::string_view prefix,
		std::string_view format,
		Args &&...args)
	{
		Detail::log(
			prefix, Detail::Level::Error, format, std::forward<Args>(args)...);
	}

	template <typename... Args>
	void file_debug(
		std::string_view prefix,
		std::string_view format,
		Args &&...args)
	{
		Detail::log(
			prefix, Detail::Level::Debug, format, std::forward<Args>(args)...);
	}
} // namespace Hyper::Logger
