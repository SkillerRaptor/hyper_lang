/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "HyperCompiler/Logger.hpp"

#include <fmt/color.h>

namespace HyperCompiler
{
	void Logger::internal_log(Logger::Level level, std::string_view string) noexcept
	{
		const fmt::color level_color = [&level]()
		{
			switch (level)
			{
			case Logger::Level::Info:
				return fmt::color::light_green;
			case Logger::Level::Warning:
				return fmt::color::orange;
			case Logger::Level::Error:
				return fmt::color::red;
			case Logger::Level::Fatal:
				return fmt::color::dark_red;
			case Logger::Level::Debug:
				return fmt::color::aqua;
			default:
				return fmt::color::light_green;
			}
		}();

		const char* level_name = [&level]()
		{
			switch (level)
			{
			case Logger::Level::Info:
				return "info";
			case Logger::Level::Warning:
				return "warning";
			case Logger::Level::Error:
				return "error";
			case Logger::Level::Fatal:
				return "fatal";
			case Logger::Level::Debug:
				return "debug";
			default:
				return "undefined";
			}
		}();

		fmt::print(
			"{}: {}: {}",
			fmt::format(fmt::emphasis::bold, "hyper-compiler"),
			fmt::format(fmt::fg(level_color), level_name),
			string.data());
	}
} // namespace HyperCompiler
