/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#if !defined(NDEBUG)
#	include <cassert>
#endif

#define HYPER_UNUSED_VARIABLE(x) (void) (x)
#define HYPER_UNUSED_VARIADIC(x) ((void) (x), ...)

// clang-format off
#if defined(__clang__)
# if !defined(NDEBUG)
#  define HYPER_UNREACHABLE() \
	assert(false);              \
	__builtin_unreachable()
# else
#  define HYPER_UNREACHABLE() __builtin_unreachable()
# endif

#	define HYPER_DISABLE_WARNINGS()   \
	_Pragma("clang diagnostic push")  \
	_Pragma("clang diagnostic ignored \"-Weverything\"")
#	define HYPER_RESTORE_WARNINGS() _Pragma("clang diagnostic pop")
#elif defined(__GNUC__) || defined(__GNUG__)
# if !defined(NDEBUG)
#  define HYPER_UNREACHABLE() \
	assert(false);              \
	__builtin_unreachable()
# else
#  define HYPER_UNREACHABLE() __builtin_unreachable()
# endif

#	define HYPER_DISABLE_WARNINGS()                          \
	_Pragma("GCC diagnostic push")                           \
	_Pragma("GCC diagnostic ignored \"-Wconversion\"")       \
	_Pragma("GCC diagnostic ignored \"-Wshadow\"")           \
	_Pragma("GCC diagnostic ignored \"-Wsign-conversion\"")  \
	_Pragma("GCC diagnostic ignored \"-Wold-style-cast\"")   \
	_Pragma("GCC diagnostic ignored \"-Wunused-parameter\"") \
	_Pragma("GCC diagnostic ignored \"-Wuseless-cast\"")
#	define HYPER_RESTORE_WARNINGS() _Pragma("GCC diagnostic pop")
#elif defined(_MSC_VER)
# if !defined(NDEBUG)
#  define HYPER_UNREACHABLE() \
	assert(false);              \
	__assume(false)
# else
#  define HYPER_UNREACHABLE() __assume(false)
# endif

#	define HYPER_DISABLE_WARNINGS() __pragma(warning(push, 0))
#	define HYPER_RESTORE_WARNINGS() __pragma(warning(pop))
#else
#	error Unsupported compiler was used.
#endif
// clang-format on
