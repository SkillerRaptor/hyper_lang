/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstdint>

#if defined(__linux__) || defined(__linux)
#	define HYPER_PLATFORM_LINUX 1
#elif defined(WIN32) || defined(WIN64)
#	define HYPER_PLATFORM_WINDOWS 1
#else
#	error Unknown target platform.
#endif

namespace hyper
{
	enum class Platform : uint8_t
	{
		Linux,
		Windows,

#if HYPER_PLATFORM_LINUX
		Current = Linux,
#elif HYPER_PLATFORM_WINDOWS
		Current = Windows,
#endif
	};
} // namespace hyper
