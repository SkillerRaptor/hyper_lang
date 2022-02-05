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
	Tester::Tester(std::string compiler)
		: m_compiler(std::move(compiler))
	{
	}

	int Tester::test() const
	{
		size_t file_count = 0;
		size_t success_count = 0;
		size_t failure_count = 0;

		const auto program_begin = std::chrono::high_resolution_clock::now();
		for (const std::filesystem::directory_entry &entry :
				 std::filesystem::recursive_directory_iterator("tests"))
		{
			if (entry.is_directory())
			{
				continue;
			}

			const std::string file = entry.path().string();
			++file_count;

			std::stringstream command_stream;
			command_stream << m_compiler;
			command_stream << " " << file;

			hyper::Logger::log("\033[0m  START   {}", entry.path().string());

			const auto test_begin = std::chrono::high_resolution_clock::now();
			const int return_code = system(command_stream.str().c_str());
			const auto test_end = std::chrono::high_resolution_clock::now();
			const auto duration =
				std::chrono::duration_cast<std::chrono::milliseconds>(
					test_end - test_begin)
					.count();
			if (return_code == 0)
			{
				hyper::Logger::log(
					"\033[30;102m SUCCESS \033[0m {} ({}ms)", file, duration);
				++success_count;
			}
			else
			{
				hyper::Logger::log(
					"\033[30;101m FAILURE \033[0m {} ({}ms)", file, duration);
				++failure_count;
			}
		}

		const auto program_end = std::chrono::high_resolution_clock::now();
		const auto program_duration =
			std::chrono::duration_cast<std::chrono::milliseconds>(
				program_end - program_begin)
				.count();

		hyper::Logger::log("");
		hyper::Logger::log(
			"\033[1mTests:\033[0m \033[92m{} success\033[0m, \033[91m{} failed\033[0m, {} total",
			success_count,
			failure_count,
			success_count + failure_count);
		hyper::Logger::log("\033[1mFiles:\033[0m \033[93m{} total\033[0m", file_count);
		hyper::Logger::log("\033[1mTime:\033[0m  \033[93m{}ms\033[0m", program_duration);

		return failure_count == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
	}
} // namespace hyper
