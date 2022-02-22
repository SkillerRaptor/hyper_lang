/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/c/c_compiler.hpp"

#include "hyper/logger.hpp"

#if defined(WIN32) || defined(WIN64)
#	include "hyper/c/microsoft.hpp"
#	include "hyper/utilities.hpp"

#	include <filesystem>
#endif

namespace hyper
{
	CCompiler::CCompiler(const std::vector<std::string> &output_files)
		: m_output_files(output_files)
	{
	}

	void CCompiler::compile() const
	{
		std::string files;
		for (const std::string &file : m_output_files)
		{
			files += file + ".c ";
		}

#if defined(WIN32) || defined(WIN64)
		MicrosoftCompiler microsoft_compiler = {};
		microsoft_compiler.find();

		if (microsoft_compiler.sdk_version() == 0)
		{
			Logger::error("Failed to find msvc compiler\n");
			std::exit(1);
		}

		const std::string &sdk_root = microsoft_compiler.sdk_root();
		const std::string &sdk_um_library_path =
			microsoft_compiler.sdk_um_library_path();
		const std::string &sdk_ucrt_library_path =
			microsoft_compiler.sdk_ucrt_library_path();
		const std::string &visual_studio_exe_path =
			microsoft_compiler.visual_studio_exe_path();
		const std::string &visual_studio_library_path =
			microsoft_compiler.visual_studio_library_path();

		const std::string sdk_version =
			std::filesystem::path(sdk_root).filename().string();
		const std::string sdk_include_path =
			sdk_root + "\\..\\..\\include\\" + sdk_version;

		std::string include;
		include += visual_studio_library_path + "\\..\\..\\include;";
		include += sdk_include_path + "\\ucrt;";
		include += sdk_include_path + "\\shared;";
		include += sdk_include_path + "\\um;";
		include += sdk_include_path + "\\winrt;";
		include += sdk_include_path + "\\cppwinrt;";
		SetEnvironmentVariable("INCLUDE", include.c_str());

		std::string lib;
		lib += visual_studio_library_path + ";";
		lib += sdk_um_library_path + ";";
		lib += sdk_ucrt_library_path + ";";
		SetEnvironmentVariable("LIB", lib.c_str());

		std::string lib_paths;
		lib_paths += visual_studio_library_path + ";";
		SetEnvironmentVariable("LIBPATH", lib_paths.c_str());

		std::stringstream command;
		command << "\"\"";
		command << visual_studio_exe_path;
		command << "\\cl.exe\" ";
		command << "/Fo\".\\build\\\\\" ";
		command << "/c ";
		command << files;
		command << "\" > nul 2> nul";

		const int return_code = system(command.str().c_str());
		if (return_code != 0)
		{
			Logger::error("Failed to compile c files\n");
			std::exit(1);
		}
#elif defined(__linux__) || defined(__linux)
		const int check_gcc = system("gcc --version > /dev/null");
		if (check_gcc)
		{
			Logger::error("Failed to find GCC compiler\n");
			std::exit(1);
		}

		std::string object_files;
		for (const std::string &file : m_output_files)
		{
			object_files += file + ".o ";
		}

		std::stringstream command;
		command << "gcc ";
		command << "-c ";
		command << files;
		command << "-o ";
		command << object_files;
		command << " > /dev/null 2>&1";

		const int return_code = system(command.str().c_str());
		if (return_code != 0)
		{
			Logger::error("Failed to compile c files\n");
			std::exit(1);
		}
#else
		(void) m_output_files;
#endif
	}
} // namespace hyper
