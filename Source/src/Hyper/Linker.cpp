/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Linker.hpp"

#include "Hyper/LinkerFinder.hpp"
#include "Hyper/Logger.hpp"
#include "Hyper/Prerequisites.hpp"

#include <filesystem>
#include <numeric>

namespace Hyper
{
	Linker::Linker(const Linker::CreateInfo &create_info)
		: m_object_files(create_info.object_files)
		, m_target(create_info.target)
		, m_debug_mode(create_info.debug_mode)
	{
		assert(!m_object_files.empty());
		assert(m_target != Target::None);
	}

	bool Linker::link() const
	{
		if (m_debug_mode)
		{
			std::string object_files;
			for (const std::string &object_file : m_object_files)
			{
				object_files += object_file;
				object_files += ' ';
			}

			Logger::info("Linking {}\n", object_files);
		}

		std::vector<std::string> args = {};
		switch (m_target)
		{
		case Target::Linux:
		{
			args.emplace_back("-o ./a.out");
			args.emplace_back("-no-pie");
			args.insert(args.end(), m_object_files.begin(), m_object_files.end());

			std::string args_string;
			for (const std::string &argument : args)
			{
				args_string += argument;
				args_string += ' ';
			}

			const std::optional<std::string> gcc = LinkerFinder::find_gcc();
			if (gcc.has_value())
			{
				const std::string command =
					Formatter::format("{} {}> /dev/null", gcc.value(), args_string);
				int error_code = std::system(command.c_str());
				if (error_code != 0)
				{
					Logger::error("failed to link executable\n");
					break;
				}

				break;
			}

			const std::optional<std::string> clang = LinkerFinder::find_clang();
			if (clang.has_value())
			{
				const std::string command =
					Formatter::format("{} {}> /dev/null", clang.value(), args_string);
				int error_code = std::system(command.c_str());
				if (error_code != 0)
				{
					Logger::error("failed to link executable\n");
					break;
				}

				break;
			}

			Logger::error("failed to find GCC or Clang on the system as linker\n");
			break;
		}
		case Target::Windows:
		{
			const std::optional<std::string> msvc = LinkerFinder::find_msvc();
			if (!msvc.has_value())
			{
				Logger::error("failed to find MSVC on the system as linker\n");
				break;
			}

			args.emplace_back("/libpath:\"\""); // VS lib x64
			args.emplace_back("/libpath:\"\""); // VS atlmfc lib x64
			args.emplace_back("/libpath:\"\""); // VS ucrt lib x64
			args.emplace_back("/libpath:\"\""); // VS um lib x64
			args.emplace_back("/out:a.exe");
			args.emplace_back("/machine:x64");
			args.emplace_back("-defaultlib:libcmt");
			args.emplace_back("-nologo");
			args.insert(args.end(), m_object_files.begin(), m_object_files.end());

			std::string args_string;
			for (const std::string &argument : args)
			{
				args_string += argument;
				args_string += ' ';
			}

			const std::string command =
				Formatter::format("\"{} {}\"", msvc.value(), args_string);
			int error_code = std::system(command.c_str());
			if (error_code != 0)
			{
				Logger::error("failed to link executable\n");
				break;
			}

			break;
		}
		default:
			HYPER_UNREACHABLE();
		}

		for (const std::string &object_file : m_object_files)
		{
			std::filesystem::remove(object_file);
		}

		return true;
	}
} // namespace Hyper
