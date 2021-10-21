/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Logger.hpp"
#include "Hyper/SourceLocation.hpp"

#include <string>

namespace Hyper
{
	class Diagnostics
	{
	public:
		enum class Level
		{
			Warning = 0,
			Error
		};

	public:
		Diagnostics(std::string file_name, std::string file_text);

		void report(
			Level level,
			SourceLocation source_location,
			std::string_view message);

	private:
		void print_line(size_t line) const;
		void print_pre_line(size_t line, size_t line_count) const;
		void print_post_line(size_t line, size_t line_count) const;
		void print_error_line(size_t line, size_t column, size_t length) const;

		[[nodiscard]] std::string get_line_content(
			size_t line) const noexcept;
		[[nodiscard]] size_t get_digit_count(size_t number) const noexcept;
		[[nodiscard]] size_t get_line_offset(size_t number) const noexcept;

	private:
		std::string m_file_name = {};
		std::string m_file_text = {};

		size_t m_file_line_count = { 1 };
		size_t m_file_line_digit_count = { 1 };
	};
} // namespace Hyper
