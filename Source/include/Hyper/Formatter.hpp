/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Prerequisites.hpp"

#include <sstream>
#include <string>
#include <string_view>

namespace Hyper
{
	class Formatter
	{
	public:
		static constexpr std::string_view s_color_black = "\033[30m";
		static constexpr std::string_view s_color_red = "\033[31m";
		static constexpr std::string_view s_color_green = "\033[32m";
		static constexpr std::string_view s_color_yellow = "\033[33m";
		static constexpr std::string_view s_color_blue = "\033[34m";
		static constexpr std::string_view s_color_magenta = "\033[35m";
		static constexpr std::string_view s_color_cyan = "\033[36m";
		static constexpr std::string_view s_color_white = "\033[37m";
		static constexpr std::string_view s_color_reset = "\033[0m";

	public:
		template <typename... Args>
		static std::string format(const std::string &string, Args &&...args)
		{
			std::stringstream string_stream;
			size_t current_index = 0;
			for (const char *c_str = string.c_str(); *c_str != '\0'; ++c_str)
			{
				if (*c_str != '{')
				{
					string_stream << *c_str;
					continue;
				}

				++c_str;

				if (*c_str == '{')
				{
					string_stream << *c_str;
					continue;
				}

				if (*c_str != '}')
				{
					// TODO(SkillerRaptor): Print error message (unclosed {})
					std::abort();
				}

				format(string_stream, current_index++, std::forward<Args>(args)...);
			}

			return string_stream.str();
		}

	private:
		static void format(std::stringstream &string_stream, size_t index)
		{
			HYPER_UNUSED_VARIABLE(string_stream);
			HYPER_UNUSED_VARIABLE(index);
		}

		template <typename T, typename... Args>
		static void format(
			std::stringstream &string_stream,
			size_t index,
			T argument,
			Args &&...args)
		{
			if (index == 0)
			{
				if constexpr (std::is_same_v<T, bool>)
				{
					string_stream << (argument ? "true" : "false");
				}
				else
				{
					string_stream << argument;
				}
				return;
			}

			format(string_stream, index - 1, std::forward<Args>(args)...);
		}
	};
} // namespace Hyper
