/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/diagnostics.hpp"

namespace hyper
{
	Diagnostics::Diagnostics(std::string_view file, std::string text)
		: m_file(file)
		, m_text(std::move(text))
	{
	}
} // namespace hyper
