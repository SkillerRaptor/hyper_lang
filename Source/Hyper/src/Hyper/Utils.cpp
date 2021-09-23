/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Utils.hpp"

#include "Hyper/Logger.hpp"

#include <cstdlib>

namespace Hyper::Utils
{
	auto terminate_compilation() -> void
	{
		Logger::log("compilation terminated.");
		std::exit(EXIT_FAILURE);
	}
} // namespace Hyper::Utils
