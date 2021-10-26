/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#if defined(__GNUC__) || defined(__GNUG__) || defined(__clang__)
#	define HYPER_UNREACHABLE() __builtin_unreachable()
#elif defined(_MSC_VER)
#	define HYPER_UNREACHABLE() __assume(false)
#else
#	define HYPER_UNREACHABLE()
#endif
