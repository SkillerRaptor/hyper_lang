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
	class Compiler
	{
	public:
		Compiler(int argc, char **argv);

		int compile() const;

	private:
		std::vector<std::string> m_files = {};
	};
} // namespace Hyper
