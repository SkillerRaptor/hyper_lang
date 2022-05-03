/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#if defined(__x86_64__) || defined(_M_X64)
#	define HYPER_ARCH_X64 1
#else
#	error Unsupported arch type
#endif

#if defined(__linux__) || defined(__linux)
#	define HYPER_PLATFORM_LINUX 1
#elif defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#	define HYPER_PLATFORM_WINDOWS 1
#else
#	error Unsupported target platform
#endif
