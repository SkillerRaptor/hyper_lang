/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <string>
#include <vector>

namespace hyper
{
	class CLinker
	{
	public:
		CLinker(
			const std::vector<std::string> &output_files,
			bool freestanding,
			std::string_view linker_script,
			std::string_view output_file);

		void link() const;

	private:
		const std::vector<std::string> &m_output_files;
		bool m_freestanding = false;
		std::string_view m_linker_script;
		std::string_view m_output_file;
	};
} // namespace hyper
