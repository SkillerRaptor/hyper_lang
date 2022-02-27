/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/utilities/assertions.hpp"

#include "hyper/logger.hpp"
#include "hyper/utilities/debugging.hpp"

#include <filesystem>

namespace hyper::detail
{
	void assertion_failed(
		std::string_view message,
		SourceLocation source_location)
	{
		Logger::error(
			"Assertion failed at {}:{}: {}\n",
			std::filesystem::path(source_location.file_name()).filename().string(),
			source_location.line(),
			message);

		hyper::break_point();
		std::exit(1);
	}

	void todo(std::string_view message, SourceLocation source_location)
	{
		Logger::warn(
			"TODO at {}:{}: {}\n",
			std::filesystem::path(source_location.file_name()).filename().string(),
			source_location.line(),
			message);
	}
} // namespace hyper::detail
