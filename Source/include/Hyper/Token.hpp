/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/SourceLocation.hpp"

#include <ostream>
#include <string>

namespace Hyper
{
	struct Token
	{
		enum class Type : unsigned char
		{
			None = 0,

			Eof,

			Plus,
			Minus,
			Star,
			Slash
		};

		std::string value;
		Type type = Type::None;
		SourceLocation source_location = {};
	};

	std::ostream &operator<<(
		std::ostream &ostream,
		const Token::Type &token_type);
	std::ostream &operator<<(std::ostream &ostream, const Token &token);
} // namespace Hyper
