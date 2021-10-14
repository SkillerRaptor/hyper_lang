/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Logger.hpp"

#include <fmt/color.h>

namespace Hyper
{
	auto Logger::internal_log(const Logger::Level level, std::string_view prefix, std::string_view string) -> void
	{
		const auto prefix_string = [&prefix]() -> std::string
		{
			if (prefix.empty())
			{
				return "";
			}

			return fmt::format(fmt::fg(fmt::color::white) | fmt::emphasis::bold, "{}: ", prefix);
		}();

		const auto level_string = [&level]() -> std::string
		{
			if (level == Level::None)
			{
				return "";
			}

			const auto level_color = [&level]() -> fmt::color
			{
				switch (level)
				{
				case Level::Info:
					return fmt::color::light_green;
				case Level::Warning:
					return fmt::color::orange;
				case Level::Error:
					return fmt::color::red;
				case Level::Fatal:
					return fmt::color::dark_red;
				default:
					return fmt::color::white;
				}
			}();

			const auto level_name = [&level]() -> std::string_view
			{
				switch (level)
				{
				case Level::Info:
					return "info";
				case Level::Warning:
					return "warning";
				case Level::Error:
					return "error";
				case Level::Fatal:
					return "fatal error";
				default:
					return "";
				}
			}();

			return fmt::format(fmt::fg(level_color) | fmt::emphasis::bold, "{}: ", level_name);
		}();

		fmt::print("{}{}{}\n", prefix_string, level_string, string);
	}
} // namespace Hyper
