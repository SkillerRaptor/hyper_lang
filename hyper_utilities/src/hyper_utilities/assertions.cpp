/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper_utilities/assertions.hpp"

#include "hyper_utilities/logger.hpp"

#include <filesystem>

namespace hyper::detail
{
	void assertion_failed(
		std::string_view expression,
		const SourceLocation &source_location)
	{
		const std::string file_name =
			std::filesystem::path(source_location.file_name()).filename().string();
		Logger::error(
			"Assertion failed at {}:{}: {}",
			file_name,
			source_location.line(),
			expression);

		std::abort();
	}
} // namespace hyper::detail
