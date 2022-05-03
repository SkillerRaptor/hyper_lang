/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper_utilities/debugging.hpp"
#include "hyper_utilities/source_location.hpp"

#include <string_view>

#if HYPER_DEBUG
#	define ASSERT(expression)                            \
		do                                                  \
		{                                                   \
			if (!static_cast<bool>(expression))               \
			{                                                 \
				::hyper::detail::assertion_failed(#expression); \
			}                                                 \
		} while (0)
#else
#	define ASSERT(expression) (static_cast<void>(0))
#endif

namespace hyper::detail
{
	void assertion_failed(
		std::string_view expression,
		const SourceLocation &source_location = SourceLocation::current());
} // namespace hyper::detail
