/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/tester.hpp"

#include "hyper/logger.hpp"

#include <chrono>
#include <filesystem>
#include <sstream>

namespace hyper
{
	Tester::Tester(std::string executable_path, std::string compiler)
		: m_executable_path(std::move(executable_path))
		, m_compiler(std::move(compiler))
	{
	}

	int Tester::test() const
	{
		size_t file_count = 0;
		size_t success_count = 0;
		size_t failure_count = 0;
		int64_t duration = 0;

		const std::string tests_folder =
			std::filesystem::path(m_executable_path).parent_path().string() +
			"/tests";

		for (const std::filesystem::directory_entry &entry :
				 std::filesystem::recursive_directory_iterator(tests_folder))
		{
			if (entry.is_directory())
			{
				continue;
			}

#if defined(WIN32) || defined(WIN64)
			const char *null = " > nul 2> nul";
#else
			const char *null = " > /dev/null 2>&1";
#endif

			const std::string real_file = entry.path().string();
			const std::string discarded_file =
				real_file.substr(tests_folder.length() + 1, real_file.length());
			const std::string command = m_compiler + " " + real_file + null;

			hyper::Logger::log("\033[0m  START   {}", discarded_file);

			const auto test_begin = std::chrono::high_resolution_clock::now();
			const int return_code = system(command.c_str());
			const auto test_end = std::chrono::high_resolution_clock::now();
			const auto test_duration =
				std::chrono::duration_cast<std::chrono::milliseconds>(
					test_end - test_begin)
					.count();
			if (return_code == 0)
			{
				hyper::Logger::log(
					"\033[30;102m SUCCESS \033[0m {} ({}ms)", discarded_file, test_duration);
				++success_count;
			}
			else
			{
				hyper::Logger::log(
					"\033[30;101m FAILURE \033[0m {} ({}ms)", discarded_file, test_duration);
				++failure_count;
			}

			++file_count;
			duration += test_duration;
		}

		hyper::Logger::log("");
		hyper::Logger::log(
			"\033[1mTests:\033[0m \033[92m{} success\033[0m, \033[91m{} "
			"failed\033[0m, {} total",
			success_count,
			failure_count,
			success_count + failure_count);
		hyper::Logger::log(
			"\033[1mFiles:\033[0m \033[93m{} total\033[0m", file_count);
		hyper::Logger::log("\033[1mTime:\033[0m  \033[93m{}s ({}ms)\033[0m", duration / 1000, duration);

		return failure_count == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
	}
} // namespace hyper
