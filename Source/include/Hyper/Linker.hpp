/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <string>
#include <vector>

namespace Hyper
{
	class Linker
	{
	public:
		struct CreateInfo
		{
			std::vector<std::string> object_files;
			bool debug_mode;
		};

	public:
		explicit Linker(const CreateInfo &create_info);

		bool link() const;

	private:
		std::vector<std::string> m_object_files;
		bool m_debug_mode = false;
	};
} // namespace Hyper
