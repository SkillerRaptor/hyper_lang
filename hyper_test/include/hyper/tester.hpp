/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <string>

namespace hyper
{
	class Tester
	{
	public:
		explicit Tester(std::string compiler);

		int test() const;

	private:
		std::string m_compiler;
	};
} // namespace hyper
