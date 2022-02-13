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
	class CCompiler
	{
	public:
		CCompiler(const std::vector<std::string> &output_files);

		void compile() const;

	private:
		const std::vector<std::string> &m_output_files;
	};
} // namespace hyper
