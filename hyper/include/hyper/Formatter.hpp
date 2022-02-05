/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <sstream>
#include <string>

namespace hyper
{
	class Formatter
	{
	public:
		template <typename... Args>
		static std::string format(
			std::string_view format,
			Args &&...args)
		{
			size_t index = 0;
			std::stringstream stream;

			const char *string = format.data();
			while (*string != '\0')
			{
				if (*string == '{' && *(string + 1) == '}')
				{
					internal_format(index++, stream, std::forward<Args>(args)...);
					++string;
				}
				else
				{
					stream << *string;
				}

				++string;
			}

			return stream.str();
		}

	private:
		static void internal_format(size_t, std::stringstream &);

		template <typename t, typename... args>
		static void internal_format(
			size_t index,
			std::stringstream &stream,
			t &&argument,
			args &&...arguments)
		{
			if (index == 0)
			{
				stream << argument;
				return;
			}

			internal_format(index - 1, stream, std::forward<args>(arguments)...);
		}
	};
} // namespace hyper
