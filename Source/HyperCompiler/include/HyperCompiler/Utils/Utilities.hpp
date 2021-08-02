/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "HyperCompiler/Logger.hpp"

#include <string>

namespace HyperCompiler::Utils
{
	char* duplicate_string(const char* source);

	int64_t get_character_position(const std::string& source, char character);
	
	template <typename... Args>
	void fatal_exit(const std::string& format, Args&&... args)
	{
		Logger::fatal(format, std::forward<Args>(args)...);
		Logger::fatal("compilation failed\n");
		std::abort();
	}
} // namespace HyperCompiler::Utils
