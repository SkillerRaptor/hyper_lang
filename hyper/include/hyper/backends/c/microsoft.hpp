/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper_utilities/platform_detection.hpp"

#if HYPER_PLATFORM_WINDOWS

#	include <functional>
#	include <string>
#	include <string_view>
#	include <Windows.h>

#	undef hyper

namespace hyper
{
	class MicrosoftCompiler
	{
	private:
		struct VersionData
		{
			std::wstring best_name;
			int32_t best_version[4] = { 0 };
		};

		using VisitFunction = std::function<
			void(std::wstring_view, std::wstring_view, VersionData &version_data)>;

	public:
		void find();

		size_t sdk_version() const;

		std::string sdk_root() const;
		std::string sdk_um_library_path() const;
		std::string sdk_ucrt_library_path() const;

		bool is_vs_2017() const;
		std::string visual_studio_exe_path() const;
		std::string visual_studio_library_path() const;

	private:
		bool os_file_exists(std::wstring_view name) const;

		bool visit_files(
			const std::wstring &directory_name,
			VersionData &version_data,
			VisitFunction visit_function);
		static void win10_visit(
			std::wstring_view short_name,
			std::wstring_view full_name,
			VersionData &version_data);
		static void win8_visit(
			std::wstring_view short_name,
			std::wstring_view full_name,
			VersionData &version_data);

		void find_windows_kit();
		std::wstring find_windows_kit_with_key(HKEY key, std::wstring_view version);

		void find_visual_studio();
		bool find_visual_studio_17();

	private:
		size_t m_sdk_version = 0;

		std::string m_sdk_root;
		std::string m_sdk_um_library_path;
		std::string m_sdk_ucrt_library_path;

		bool m_is_vs_2017 = false;
		std::string m_visual_studio_exe_path;
		std::string m_visual_studio_library_path;
	};
} // namespace hyper
#endif
