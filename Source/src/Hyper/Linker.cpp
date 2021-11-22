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
		, m_debug_mode(create_info.debug_mode)
	{
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

		// TODO(SkillerRaptor): Invoking system linker

		return true;
	}
} // namespace Hyper
