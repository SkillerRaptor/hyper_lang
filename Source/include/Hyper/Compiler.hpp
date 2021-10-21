/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstddef>

namespace Hyper
{
	class Compiler
	{
	public:
		Compiler(size_t file_count, const char **files);

		Compiler(const Compiler &other) = delete;

		void compile();

	private:
		size_t m_file_count = { 0 };
		const char **m_files = { nullptr };
	};
} // namespace Hyper
