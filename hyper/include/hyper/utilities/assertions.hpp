/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/utilities/debugging.hpp"
#include "hyper/utilities/source_location.hpp"

#if HYPER_DEBUG
#	define VERIFY(expression)                            \
		do                                                  \
		{                                                   \
			if (!static_cast<bool>(expression))               \
			{                                                 \
				::hyper::detail::assertion_failed(#expression); \
			}                                                 \
		} while (0)
#	define TODO(message)               \
		do                                \
		{                                 \
			::hyper::detail::todo(message); \
		} while (0)
#else
#	define VERIFY(expression)
#	define TODO(message)
#endif

namespace hyper::detail
{
	[[noreturn]] void assertion_failed(
		std::string_view message,
		SourceLocation source_location = SourceLocation::current());

	void todo(
		std::string_view message,
		SourceLocation source_location = SourceLocation::current());
} // namespace hyper::detail
