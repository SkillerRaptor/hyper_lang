/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <sstream>
#include <string>

namespace Hyper
{
	class Formatter
	{
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
			(void) string_stream;
			(void) index;
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
				string_stream << argument;
				return;
			}

			format(string_stream, index - 1, std::forward<Args>(args)...);
		}
	};
} // namespace Hyper
