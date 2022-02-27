/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#if !defined(_DEBUG) && !defined(ADEBUG) && !defined(NDEBUG)
#	define NDEBUG
#endif

#ifndef NDEBUG
#	define HYPER_DEBUG 1
#else
#	define HYPER_DEBUG 0
#endif

namespace hyper
{
	bool is_debugger_present() noexcept;

	void break_point() noexcept;
} // namespace hyper
