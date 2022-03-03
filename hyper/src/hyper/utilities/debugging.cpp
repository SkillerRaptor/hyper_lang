/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/utilities/debugging.hpp"

#include "hyper/utilities/platform_detection.hpp"

#if HYPER_PLATFORM_LINUX
#	include <atomic>
#	include <fstream>
#	include <signal.h>
#	include <string>
#elif HYPER_PLATFORM_WINDOWS
#	define NOMINMAX
#	define WIN32_LEAN_AND_MEAN
#	include <Windows.h>
#endif

namespace hyper
{
	bool is_debugger_present() noexcept
	{
#if HYPER_PLATFORM_LINUX
		std::ifstream self_proc("/proc/self/status");
		if (!self_proc)
		{
			return false;
		}

		std::string buffer(256, '\0');
		self_proc.read(&buffer[0], 256);

		const size_t position = buffer.find("TracerPid:\t");
		if (position == buffer.npos)
		{
			return false;
		}

		return buffer[position + 11] != '0';
#elif HYPER_PLATFORM_WINDOWS
		return ::IsDebuggerPresent();
#endif
	}

	void break_point() noexcept
	{
		if (!is_debugger_present())
		{
			return;
		}

#if HYPER_PLATFORM_LINUX
#	if defined(SIGTRAP)
		raise(SIGTRAP);
#	else
		raise(SIGABRT);
#	endif
#elif HYPER_PLATFORM_WINDOWS
		__debugbreak();
#endif
	}
} // namespace hyper
