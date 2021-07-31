/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64)
#	define HYPERCOMPILER_ARCH_X86_64 1
#elif defined(__i386) || defined(__i386__) || defined(_M_IX86)
#	define HYPERCOMPILER_ARCH_X86 1
#else
#	error Unknown architecture.
#endif

#if defined(_WIN32) || defined(_WIN64)
#	define HYPERCOMPILER_PLATFORM_WINDOWS 1
#elif defined(__linux__) || defined(__linux)
#	define HYPERCOMPILER_PLATFORM_LINUX 1
#else
#	error Unknown platform.
#endif
