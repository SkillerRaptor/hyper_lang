/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <fmt/color.h>
#include <fmt/format.h>

#include <string>
#include <string_view>

namespace Hyper
{
	class Logger
	{
	public:
		enum class Level : unsigned char
		{
			Info = 0,
			Warning,
			Error
		};

	public:
		Logger() = delete;
		~Logger() = delete;

		Logger(const Logger &other) = delete;
		Logger(Logger &&other) = delete;

		Logger &operator=(const Logger &other) = delete;
		Logger &operator=(Logger &&other) = delete;

		template <typename... Args>
		static void log(const std::string_view string, Args &&...args)
		{
			const std::string formatted_string =
				format(string, std::forward<Args>(args)...);
			fmt::print("{}", formatted_string);
		}

		template <typename... Args>
		static void log(
			const std::string_view prefix,
			const Level level,
			const std::string_view string,
			Args &&...args)
		{
			const fmt::color level_color = [level]()
			{
				switch (level)
				{
				case Level::Info:
					return fmt::color::white;
				case Level::Warning:
					return fmt::color::gold;
				case Level::Error:
					return fmt::color::crimson;
				default:
					return fmt::color::white;
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
				default:
					return "";
				}
			}();

			const std::string formatted_prefix = format(
				fmt::fg(fmt::color::white) | fmt::emphasis::bold, "{}", prefix);
			const std::string formatted_level =
				format(fmt::fg(level_color), "{}", level_name);
			const std::string formatted_string =
				format(string, std::forward<Args>(args)...);
			fmt::print(
				"{}: {}: {}",
				formatted_prefix,
				formatted_level,
				formatted_string);
		}

		template <typename... Args>
		static std::string format(const std::string_view string, Args &&...args)
		{
			return fmt::format(string, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static std::string format(
			const fmt::text_style text_style,
			const std::string_view string,
			Args &&...args)
		{
			return fmt::format(text_style, string, std::forward<Args>(args)...);
		}
	};
} // namespace Hyper
