/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/utilities.hpp"

#if defined(WIN32) || defined(WIN64)
#	define WIN32_LEAN_AND_MEAN
#	define NOMINMAX
#	include <Windows.h>
#endif

namespace hyper
{
	std::string Utilities::replace_string(
		std::string string,
		std::string_view search,
		std::string_view replacement)
	{
		size_t position = 0;
		while ((position = string.find(search, position)) != std::string::npos)
		{
			string.replace(position, search.length(), replacement);
			position += replacement.length();
		}
		return string;
	}

	std::string Utilities::read_line(std::string_view text, size_t line) noexcept
	{
		size_t start = std::numeric_limits<size_t>::max();
		size_t length = 0;

		size_t current_line = 1;
		for (size_t i = 0; i < text.length(); ++i)
		{
			const char character = text[i];
			if (current_line == line)
			{
				if (start == std::numeric_limits<size_t>::max())
				{
					start = i;
				}

				if (character != '\n')
				{
					++length;
				}
			}

			if (character == '\n' && ++current_line == (line + 1))
			{
				break;
			}
		}

		std::string string(text.substr(start, length));
		string = replace_string(string, "\t", "  ");

		return string;
	}

	std::string Utilities::convert_wstring(const std::wstring &wstring)
	{
		if (wstring.empty())
		{
			return "";
		}

		std::string return_string;

#if defined(WIN32) || defined(WIN64)
		size_t size = 0;
		size_t begin = 0;
		size_t position = wstring.find(static_cast<wchar_t>(0), begin);
		while (position != std::wstring::npos && begin < wstring.length())
		{
			std::wstring segment(&wstring[begin], position - begin);
			size = WideCharToMultiByte(
				CP_UTF8,
				WC_ERR_INVALID_CHARS,
				&segment[0],
				static_cast<int>(segment.size()),
				nullptr,
				0,
				nullptr,
				nullptr);

			std::string converted(size, 0);
			WideCharToMultiByte(
				CP_UTF8,
				WC_ERR_INVALID_CHARS,
				&segment[0],
				static_cast<int>(segment.size()),
				&converted[0],
				static_cast<int>(converted.size()),
				nullptr,
				nullptr);

			return_string.append(converted);
			return_string.append({ 0 });
			begin = position + 1;
			position = wstring.find(static_cast<wchar_t>(0), begin);
		}

		if (begin <= wstring.length())
		{
			std::wstring segment(&wstring[begin], wstring.length() - begin);
			size = WideCharToMultiByte(
				CP_UTF8,
				WC_ERR_INVALID_CHARS,
				&segment[0],
				static_cast<int>(segment.size()),
				nullptr,
				0,
				nullptr,
				nullptr);
			std::string converted(size, 0);
			WideCharToMultiByte(
				CP_UTF8,
				WC_ERR_INVALID_CHARS,
				&segment[0],
				static_cast<int>(segment.size()),
				&converted[0],
				static_cast<int>(converted.size()),
				nullptr,
				nullptr);

			return_string.append(converted);
		}
#else
		size_t size = 0;
		size_t begin = 0;
		size_t position = wstring.find(static_cast<wchar_t>(0), begin);
		while (position != std::wstring::npos && begin < wstring.length())
		{
			std::wstring segment(&wstring[begin], position - begin);
			size = wcstombs(nullptr, segment.c_str(), 0);
			std::string converted(size, 0);
			wcstombs(&converted[0], segment.c_str(), converted.size());

			return_string.append(converted);
			return_string.append({ 0 });
			begin = position + 1;
			position = wstring.find(static_cast<wchar_t>(0), begin);
		}

		if (begin <= wstring.length())
		{
			std::wstring segment(&wstring[begin], wstring.length() - begin);
			size = wcstombs(nullptr, segment.c_str(), 0);

			std::string converted(size, 0);
			wcstombs(&converted[0], segment.c_str(), converted.size());

			return_string.append(converted);
		}
#endif

		return return_string;
	}
} // namespace hyper
