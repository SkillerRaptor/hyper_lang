/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/c/c_linker.hpp"

#include "hyper/logger.hpp"
#include "hyper/utilities/platform_detection.hpp"

#if HYPER_PLATFORM_WINDOWS
#	include "hyper/c/microsoft.hpp"
#	include "hyper/utilities.hpp"
#endif

namespace hyper
{
	CLinker::CLinker(
		const std::vector<std::string> &output_files,
		bool freestanding,
		std::string_view linker_script,
		std::string_view output_file)
		: m_output_files(output_files)
		, m_freestanding(freestanding)
		, m_linker_script(linker_script)
		, m_output_file(output_file)
	{
	}

	void CLinker::link() const
	{
#if HYPER_PLATFORM_WINDOWS
		if (m_freestanding)
		{
			Logger::error("The freestanding mode is not supported on windows!\n");
			std::exit(1);
		}

		if (!m_linker_script.empty())
		{
			Logger::error("The linker script can not be set on windows!\n");
			std::exit(1);
		}

		MicrosoftCompiler microsoft_compiler = {};
		microsoft_compiler.find();

		if (microsoft_compiler.sdk_version() == 0)
		{
			Logger::error("Failed to find msvc compiler\n");
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
		command << "/out:"
						<< (!m_output_file.empty() ? m_output_file : ".\\build\\a.exe ");
		command << files;
		command << "\" > nul 2> nul";

		const int return_code = system(command.str().c_str());
		if (return_code != 0)
		{
			Logger::error("Failed to link c object files\n");
			std::exit(1);
		}
#elif HYPER_PLATFORM_LINUX
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

		if (m_freestanding)
		{
			command << "-static ";
			command << "-nostdlib ";
			command << "-z max-page-size=0x1000 ";
		}

		if (!m_linker_script.empty())
		{
			command << "-T " << m_linker_script << " ";
		}

		command << object_files;
		command << "-o ";
		command << (!m_output_file.empty() ? m_output_file : "./build/a.out");
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
