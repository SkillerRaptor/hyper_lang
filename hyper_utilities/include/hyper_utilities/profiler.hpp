/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <chrono>
#include <sstream>
#include <string>
#include <string_view>
#include <thread>

#if HYPER_PROFILING
#	define HYPER_PROFILE_BEGIN(file_name) ::hyper::Profiler::begin(file_name)
#	define HYPER_PROFILE_END() ::hyper::Profiler::end()
#	define HYPER_PROFILE_SCOPE_LINE_HELPER(name, line) \
		[[maybe_unused]] ::hyper::Profiler::Timer timer##line(name)
#	define HYPER_PROFILE_SCOPE_LINE(name, line) \
		HYPER_PROFILE_SCOPE_LINE_HELPER(name, line)
#	define HYPER_PROFILE_SCOPE(name) HYPER_PROFILE_SCOPE_LINE(name, __LINE__)
#	define HYPER_PROFILE_FUNCTION() HYPER_PROFILE_SCOPE(__FUNCTION__)
#else
#	define HYPER_PROFILE_BEGIN(file_name) (static_cast<void>(0))
#	define HYPER_PROFILE_END() (static_cast<void>(0))
#	define HYPER_PROFILE_SCOPE(name) (static_cast<void>(0))
#	define HYPER_PROFILE_FUNCTION() (static_cast<void>(0))
#endif

namespace hyper
{
	class Profiler
	{
	public:
		class Timer
		{
		public:
			explicit Timer(std::string_view name);
			~Timer();

		private:
			std::string_view m_name;
			std::chrono::time_point<std::chrono::steady_clock> m_start_point = {};
		};

	private:
		struct Profile
		{
			std::string_view name;
			std::chrono::duration<double, std::micro> start;
			std::chrono::microseconds duration;
			std::thread::id thread_id;
		};

	public:
		Profiler(const Profiler &) = delete;
		Profiler &operator=(const Profiler &) = delete;

		Profiler(Profiler &&) = delete;
		Profiler &operator=(Profiler &&) = delete;

		static void begin(std::string_view file_name);
		static void end();

		static void push_profile(const Profile &profile);

	private:
		static inline size_t s_profile_count = 0;
		static inline std::string s_file;
		static inline std::stringstream s_record_stream;
	};
} // namespace hyper
