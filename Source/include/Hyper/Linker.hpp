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
		enum class ObjectFormat
		{
			Coff,
			Elf,
			Mingw,
			Wasm,
		};

	public:
		struct CreateInfo
		{
			std::vector<std::string> object_files;
			ObjectFormat object_format;
			bool debug_mode;
		};

	public:
		explicit Linker(const CreateInfo &create_info);

		bool link() const;

	private:
		std::vector<std::string> m_object_files;
		ObjectFormat m_object_format;
		bool m_debug_mode = false;
	};
} // namespace Hyper
