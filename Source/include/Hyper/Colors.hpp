/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <string_view>

namespace Hyper
{
	constexpr std::string_view s_color_black = "\033[30m";
	constexpr std::string_view s_color_red = "\033[31m";
	constexpr std::string_view s_color_green = "\033[32m";
	constexpr std::string_view s_color_yellow = "\033[33m";
	constexpr std::string_view s_color_blue = "\033[34m";
	constexpr std::string_view s_color_magenta = "\033[35m";
	constexpr std::string_view s_color_cyan = "\033[36m";
	constexpr std::string_view s_color_white = "\033[37m";
	constexpr std::string_view s_color_reset = "\033[0m";
} // namespace Hyper
