/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "HyperCompiler/Compiler.hpp"
#include "HyperCompiler/Utils/Prerequisites.hpp"

#include <fmt/format.h>

#include <utility>

namespace HyperCompiler
{
	class Logger
	{
	public:
		NON_COPYABLE(Logger);
		NON_MOVEABLE(Logger);

	private:
		enum class Level
		{
			Info,
			Warning,
			Error,
			Fatal,
			Debug
		};

	public:
		Logger() = delete;
		~Logger() = delete;

		template <typename... Args>
		static void info(std::string_view format, Args&&... args) noexcept
		{
			Logger::log(Level::Info, format, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void warning(std::string_view format, Args&&... args) noexcept
		{
			Logger::log(Level::Warning, format, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void error(std::string_view format, Args&&... args) noexcept
		{
			Logger::log(Level::Error, format, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void fatal(std::string_view format, Args&&... args) noexcept
		{
			Logger::log(Level::Fatal, format, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void debug(std::string_view format, Args&&... args) noexcept
		{
#ifdef NDEBUG
			UNUSED_VARIABLE(format);
			UNUSED_VARIADIC_VARIABLE(args);
#else
			Logger::log(Level::Debug, format, std::forward<Args>(args)...);
#endif
		}

	private:
		static void internal_log(Level level, std::string_view string) noexcept;

		template <typename... Args>
		static void log(Level level, std::string_view format, Args&&... args) noexcept
		{
			if (format.empty())
			{
				Logger::internal_log(level, format);
				return;
			}

			constexpr const size_t args_count = sizeof...(Args);
			if constexpr (args_count == 0)
			{
				Logger::internal_log(level, format);
				return;
			}

			Logger::internal_log(level, fmt::format(format, std::forward<Args>(args)...));
		}
	};
} // namespace HyperCompiler
