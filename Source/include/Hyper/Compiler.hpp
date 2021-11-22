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
	class Compiler
	{
	public:
		struct CreateInfo
		{
			std::vector<std::string> files = {};
			Target target = Target::None;
			bool debug_scanner = false;
			bool debug_parser = false;
			bool debug_generator = false;
			bool debug_linker = false;
		};

	public:
		explicit Compiler(const CreateInfo &create_info);

		bool compile() const;

	private:
		std::vector<std::string> m_files = {};
		Target m_target = Target::None;
		bool m_debug_scanner = false;
		bool m_debug_parser = false;
		bool m_debug_generator = false;
		bool m_debug_linker = false;
	};
} // namespace Hyper
