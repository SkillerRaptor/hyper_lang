/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/c/c_linker.hpp"

#include "hyper/logger.hpp"

#if defined(WIN32) || defined(WIN64)
#	include "hyper/c/microsoft.hpp"
#	include "hyper/utilities.hpp"
#endif

namespace hyper
{
	CLinker::CLinker(const std::vector<std::string> &output_files)
		: m_output_files(output_files)
	{
	}

	void CLinker::link() const
	{
#if defined(WIN32) || defined(WIN64)
		MicrosoftCompiler microsoft_compiler = {};
		microsoft_compiler.find();

		if (microsoft_compiler.sdk_version() == 0)
		{
			Logger::error("failed to find msvc compiler");
			std::exit(1);
		}

		const std::string &visual_studio_exe_path =
			microsoft_compiler.visual_studio_exe_path();

		std::string files;
		for (const std::string &file : m_output_files)
		{
			files += file + ".obj ";
		}

		std::stringstream command;
		command << "\"\"";
		command << visual_studio_exe_path;
		command << "\\link.exe\" ";
		command << "/nologo ";
		command << "/machine:amd64 ";
		command << "/subsystem:console ";
		command << "/out:.\\build\\a.exe ";
		command << files;
		command << "\" > nul 2> nul";

		const int return_code = system(command.str().c_str());
		if (return_code != 0)
		{
			Logger::error("failed to link c object files");
			std::exit(1);
		}
#elif defined(__linux__) || defined(__linux)
		const int check_gcc = system("gcc --version > /dev/null");
		if (check_gcc)
		{
			Logger::error("failed to find GCC compiler");
			std::exit(1);
		}

		std::string object_files;
		for (const std::string &file : m_output_files)
		{
			object_files += file + ".o ";
		}

		std::stringstream command;
		command << "gcc ";
		command << object_files;
		command << "-o ";
		command << "./build/a.out";
		command << " > /dev/null 2>&1";

		const int return_code = system(command.str().c_str());
		if (return_code != 0)
		{
			Logger::error("failed to compile c files");
			std::exit(1);
		}
#else
		(void) m_output_files;
#endif
	}
} // namespace hyper
