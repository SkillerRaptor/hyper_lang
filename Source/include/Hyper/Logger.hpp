/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <fmt/format.h>

#include <string_view>
#include <utility>

namespace Hyper
{
	class Logger
	{
	private:
		enum class Level
		{
			None = 0,
			Info,
			Warning,
			Error,
			Fatal
		};

	public:
		template <class... Args>
		static auto log(std::string_view format, Args&&... args) -> void
		{
			log(Level::None, "", format, std::forward<Args>(args)...);
		}

		template <class... Args>
		static auto info(std::string_view prefix, std::string_view format, Args&&... args) -> void
		{
			log(Level::Info, prefix, format, std::forward<Args>(args)...);
		}

		template <class... Args>
		static auto warning(std::string_view prefix, std::string_view format, Args&&... args) -> void
		{
			log(Level::Warning, prefix, format, std::forward<Args>(args)...);
		}

		template <class... Args>
		static auto error(std::string_view prefix, std::string_view format, Args&&... args) -> void
		{
			log(Level::Error, prefix, format, std::forward<Args>(args)...);
		}

		template <class... Args>
		static auto fatal(std::string_view prefix, std::string_view format, Args&&... args) -> void
		{
			log(Level::Fatal, prefix, format, std::forward<Args>(args)...);
		}

		template <class... Args>
		static auto hyper_info(std::string_view format, Args&&... args) -> void
		{
			info("hyper", format, std::forward<Args>(args)...);
		}

		template <class... Args>
		static auto hyper_warning(std::string_view format, Args&&... args) -> void
		{
			warning("hyper", format, std::forward<Args>(args)...);
		}

		template <class... Args>
		static auto hyper_error(std::string_view format, Args&&... args) -> void
		{
			error("hyper", format, std::forward<Args>(args)...);
		}

		template <class... Args>
		static auto hyper_fatal(std::string_view format, Args&&... args) -> void
		{
			fatal("hyper", format, std::forward<Args>(args)...);
		}

	private:
		static auto internal_log(const Level level, std::string_view prefix, std::string_view string) -> void;

		template <class... Args>
		static auto log(const Level log_level, std::string_view prefix, std::string_view format, Args&&... args) -> void
		{
			if (format.empty())
			{
				internal_log(log_level, prefix, format);
				return;
			}

			constexpr size_t args_count = sizeof...(Args);
			if constexpr (args_count == 0)
			{
				internal_log(log_level, prefix, format);
			}
			else
			{
				internal_log(log_level, prefix, fmt::format(format, std::forward<Args>(args)...));
			}
		}
	};
} // namespace Hyper
