/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <vector>

namespace Hyper
{
	class Compiler
	{
	public:
		explicit Compiler(std::vector<const char *> files);

		void compile();

	private:
		std::vector<const char *> m_files = {};
	};
} // namespace Hyper
