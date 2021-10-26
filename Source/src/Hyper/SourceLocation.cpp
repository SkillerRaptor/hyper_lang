/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/SourceLocation.hpp"

namespace Hyper
{
	std::ostream &operator<<(
		std::ostream &ostream,
		const SourceLocation &source_location)
	{
		ostream << "line = " << source_location.line
						<< ", column = " << source_location.column
						<< ", length = " << source_location.length
						<< ", start = " << source_location.start;
		return ostream;
	}
} // namespace Hyper
