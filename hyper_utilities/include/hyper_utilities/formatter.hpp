/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper_utilities/profiler.hpp"

#include <sstream>
#include <string>
#include <string_view>

namespace hyper
{
	class Formatter
	{
	public:
		template <typename... Args>
		static std::string format(std::string_view format, Args &&...args)
		{
			HYPER_PROFILE_FUNCTION();

			size_t position = 0;
			std::ostringstream format_stream;
			(format_helper(format_stream, format, position, args), ...);
			format_stream << format.substr(position);

			return format_stream.str();
		}

	private:
		template <typename T>
		static void format_helper(
			std::ostringstream &format_stream,
			std::string_view format,
			size_t &position,
			T &&value)
		{
			HYPER_PROFILE_FUNCTION();

			const size_t open_position = format.find('{', position);
			if (open_position == std::string::npos)
			{
				return;
			}

			const size_t close_position = format.find('}', open_position + 1);
			if (close_position == std::string::npos)
			{
				return;
			}

			format_stream << format.substr(position, open_position - position);
			format_stream << value;
			position = close_position + 1;
		}
	};
} // namespace hyper
