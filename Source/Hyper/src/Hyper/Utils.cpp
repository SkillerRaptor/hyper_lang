/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Utils.hpp"

#include "Hyper/Logger.hpp"

namespace Hyper::Utils
{
	auto terminate_compilation() -> void
	{
		Logger::log("compilation terminated.");
		std::terminate();
	}
} // namespace Hyper::Utils
