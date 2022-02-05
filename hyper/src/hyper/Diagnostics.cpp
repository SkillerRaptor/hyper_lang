/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/diagnostics.hpp"

#include "hyper/logger.hpp"

namespace hyper
{
	Diagnostics::Diagnostics(std::string file, std::string text)
		: m_file(std::move(file))
		, m_text(std::move(text))
	{
	}
} // namespace hyper
