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
		CLinker(const std::vector<std::string> &output_files);

		void link() const;

	private:
		const std::vector<std::string> &m_output_files;
	};
} // namespace hyper
