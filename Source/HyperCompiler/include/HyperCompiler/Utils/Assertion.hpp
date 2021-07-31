/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "HyperCompiler/Logger.hpp"
#include "HyperCompiler/Utils/Prerequisites.hpp"

#include <cstdlib>

#ifndef NDEBUG
#	define ASSERT(expression)                                                \
		do                                                                    \
		{                                                                     \
			if (!(expression))                                                \
			{                                                                 \
				Logger::fatal("Assertion failed: {}", STRINGIFY(expression)); \
				Logger::fatal(                                                \
					"{}:{} in {}",                                            \
					__builtin_FILE(),                                         \
					__builtin_LINE(),                                         \
					__builtin_FUNCTION());                                    \
				std::abort();                                                 \
			}                                                                 \
		} while (0)
#	define ASSERT_WITH_MESSAGE(expression, message)            \
		do                                                      \
		{                                                       \
			if (!(expression))                                  \
			{                                                   \
				Logger::fatal("Assertion failed: {}", message); \
				Logger::fatal(                                  \
					"{}:{} in {}",                              \
					__builtin_FILE(),                           \
					__builtin_LINE(),                           \
					__builtin_FUNCTION());                      \
				std::abort();                                   \
			}                                                   \
		} while (0)
#	define ASSERT_NOT_REACHED() ASSERT(false)
#else
#	define ASSERT(expression)
#	define ASSERT_WITH_MESSAGE(expression, message)
#	define ASSERT_NOT_REACHED() std::abort()
#endif
