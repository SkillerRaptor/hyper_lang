/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Generators/Generator.hpp"

namespace Hyper
{
	Generator::Generator(std::string file)
		: m_file(std::move(file))
	{
	}
} // namespace Hyper
