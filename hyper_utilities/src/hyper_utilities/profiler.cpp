/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper_utilities/profiler.hpp"

#include "hyper_utilities/logger.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>

namespace hyper
{
	Profiler::Timer::Timer(std::string_view name)
		: m_name(name)
		, m_start_point(std::chrono::high_resolution_clock::now())
	{
	}

	Profiler::Timer::~Timer()
	{
		const std::chrono::time_point<std::chrono::steady_clock> end_point =
			std::chrono::steady_clock::now();

		const std::chrono::duration start_point_duration =
			std::chrono::time_point_cast<std::chrono::milliseconds>(m_start_point)
				.time_since_epoch();
		const std::chrono::duration end_point_duration =
			std::chrono::time_point_cast<std::chrono::milliseconds>(end_point)
				.time_since_epoch();
		const std::chrono::duration duration =
			end_point_duration - start_point_duration;

		const std::chrono::duration<double, std::micro> start =
			m_start_point.time_since_epoch();

		const Profiler::Profile profile = {
			.name = m_name,
			.start = start,
			.duration = duration,
			.thread_id = std::this_thread::get_id(),
		};

		Profiler::push_profile(profile);
	}

	void Profiler::begin(std::string_view file)
	{
		if (!s_file.empty())
		{
			Logger::error("Failed to begin new session, while another session is "
										"already running!\n");
			return;
		}

		s_file = file;

		s_record_stream << "{";
		s_record_stream << "\"otherData\": {},";
		s_record_stream << "\"traceEvents\": [";
	}

	void Profiler::end()
	{
		if (s_file.empty())
		{
			Logger::error("Failed to end session, while no session is running\n");
			return;
		}

		s_record_stream << "]}";

		std::ofstream output_file(s_file);
		output_file << s_record_stream.str();
		output_file.close();

		s_profile_count = 0;
		s_file = "";
		s_record_stream = {};
	}

	void Profiler::push_profile(const Profile &profile)
	{
		if (s_file.empty())
		{
			return;
		}

		if (s_profile_count++ > 0)
		{
			s_record_stream << ",";
		}

		s_record_stream << std::setprecision(3) << std::fixed;
		s_record_stream << "{";
		s_record_stream << "\"cat\":\"function\",";
		s_record_stream << "\"dur\":" << profile.duration.count() << ',';
		s_record_stream << "\"name\":\"" << profile.name << "\",";
		s_record_stream << "\"ph\":\"X\",";
		s_record_stream << "\"pid\":0,";
		s_record_stream << "\"tid\":" << profile.thread_id << ",";
		s_record_stream << "\"ts\":" << profile.start.count();
		s_record_stream << "}";
	}
} // namespace hyper
