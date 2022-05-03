/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper_utilities/utilities.hpp"

#include "hyper_utilities/platform_detection.hpp"
#include "hyper_utilities/profiler.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>

#if HYPER_PLATFORM_WINDOWS
#	define WIN32_LEAN_AND_MEAN
#	define NOMINMAX
#	include <Windows.h>
#endif

namespace hyper::utilities
{
	Expected<std::string, FileError> read_file(std::string_view file)
	{
		HYPER_PROFILE_FUNCTION();

		ASSERT(!file.empty());

		if (!std::filesystem::exists(file))
		{
			return FileError::FileNotFound;
		}

		if (std::filesystem::is_directory(file))
		{
			return FileError::FileIsDirectory;
		}

		std::ifstream file_stream(file.data());
		if (!file_stream.is_open())
		{
			return FileError::FileNotReadable;
		}

		std::stringstream content = {};
		content << file_stream.rdbuf();

		return content.str();
	}

	Expected<std::string_view, StringError> find_line(
		std::string_view text,
		size_t line)
	{
		HYPER_PROFILE_FUNCTION();

		ASSERT(!text.empty());
		ASSERT(line != 0);

		size_t start = text.length();
		size_t length = 0;
		size_t current_line = 1;
		for (size_t i = 0; i < text.length(); ++i)
		{
			if (text[i] == '\n')
			{
				++current_line;
				continue;
			}

			if (current_line == line)
			{
				if (start == text.length())
				{
					start = i;
				}

				++length;
			}
		}

		if (start == text.length())
		{
			return StringError::OutOfRange;
		}

		return text.substr(start, length);
	}

	Expected<std::string, StringError> convert_wstring(std::wstring_view wstring)
	{
		HYPER_PROFILE_FUNCTION();

		ASSERT(!wstring.empty());

		std::string string;

#if HYPER_PLATFORM_WINDOWS
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

			string.append(converted);
			string.append({ 0 });
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

			string.append(converted);
		}
#elif HYPER_PLATFORM_LINUX
		size_t size = 0;
		size_t begin = 0;
		size_t position = wstring.find(static_cast<wchar_t>(0), begin);
		while (position != std::wstring::npos && begin < wstring.length())
		{
			std::wstring segment(&wstring[begin], position - begin);
			size = wcstombs(nullptr, segment.c_str(), 0);
			std::string converted(size, 0);
			wcstombs(&converted[0], segment.c_str(), converted.size());

			string.append(converted);
			string.append({ 0 });
			begin = position + 1;
			position = wstring.find(static_cast<wchar_t>(0), begin);
		}

		if (begin <= wstring.length())
		{
			std::wstring segment(&wstring[begin], wstring.length() - begin);
			size = wcstombs(nullptr, segment.c_str(), 0);

			std::string converted(size, 0);
			wcstombs(&converted[0], segment.c_str(), converted.size());

			string.append(converted);
		}
#endif

		return string;
	}

	void replace_string(
		std::string &string,
		std::string_view search,
		std::string_view replacement)
	{
		HYPER_PROFILE_FUNCTION();

		size_t position = string.find(search);
		while (position != std::string::npos)
		{
			string.replace(position, search.length(), replacement);
			position = string.find(search, position + replacement.length());
		}
	}
} // namespace hyper::utilities
