/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <sstream>
#include <string>
#include <string_view>

namespace Hyper::Formatter
{
	namespace Detail
	{
		inline void format(std::stringstream &, size_t)
		{
		}

		template <typename T, typename... Args>
		void format(
			std::stringstream &stream,
			size_t argument_index,
			T &&argument,
			Args &&...args)
		{
			if (argument_index != 0)
			{
				format(stream, argument_index - 1, std::forward<Args>(args)...);
				return;
			}

			stream << argument;
		}
	} // namespace Detail

	template <typename... Args>
	std::string format(std::string_view format, Args &&...args)
	{
		std::stringstream stream;

		size_t argument_index = 0;
		constexpr size_t argument_count = sizeof...(args);
		for (auto it = format.cbegin(); it != format.cend(); ++it)
		{
			if (*it != '{')
			{
				stream << *it;
				continue;
			}

			++it;

			if (*it != '}')
			{
				// NOTE: Format bracket is unclosed
				std::abort();
			}

			if (argument_index >= argument_count)
			{
				// NOTE: Format argument index is out of bounds
				std::abort();
			}

			Detail::format(stream, argument_index++, std::forward<Args>(args)...);
		}

		return stream.str();
	}
} // namespace Hyper::Formatter
