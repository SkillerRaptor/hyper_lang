/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Target.hpp"

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
			Target target = Target::None;
			bool debug_mode;
		};

	public:
		explicit Linker(const CreateInfo &create_info);

		bool link() const;

	private:
		std::vector<std::string> m_object_files;
		Target m_target = Target::None;
		bool m_debug_mode = false;
	};
} // namespace Hyper
