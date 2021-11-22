/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Linker.hpp"

#include "Hyper/Logger.hpp"
#include "Hyper/Prerequisites.hpp"

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

		switch (m_target)
		{
		case Target::Linux:
		{
			std::string args;
			args += "-o ./a.out ";
			args += "-no-pie ";

			for (const std::string &object_file : m_object_files)
			{
				args += object_file + " ";
			}

			bool is_gcc_available = std::system("which gcc > /dev/null") == 0;
			if (is_gcc_available)
			{
				std::string gcc_command;
				gcc_command += "gcc ";
				gcc_command += args;
				gcc_command += "> /dev/null";

				int error_code = std::system(gcc_command.c_str());
				if (error_code != 0)
				{
					Logger::error("failed to link executable\n");
				}
				break;
			}

			bool is_clang_available = std::system("which clang > /dev/null") == 0;
			if (is_clang_available)
			{
				std::string clang_command;
				clang_command += "clang ";
				clang_command += args;
				clang_command += "> /dev/null";

				int error_code = std::system(clang_command.c_str());
				if (error_code != 0)
				{
					Logger::error("failed to link executable\n");
				}
				break;
			}

			Logger::error("failed to find gcc or clang as system linker\n");
			break;
		}
		case Target::Windows:
		{
			// TODO(SkillerRaptor): Adding windows linker support
			Logger::error("windows linker is not implemented yet\n");
			break;
		}
		default:
			HYPER_UNREACHABLE();
		}

		return true;
	}
} // namespace Hyper
