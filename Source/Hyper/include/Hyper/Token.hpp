/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <fmt/ostream.h>

#include <string>

namespace Hyper
{
	struct Token
	{
	public:
		enum class Type
		{
			Eof = 0,

			Plus,
			Minus,
			Star,
			Slash,

			NumericLiteral
		};

	public:
		Type type{ Type::Eof };
		std::string value;
	};

	auto operator<<(std::ostream& ostream, const Token::Type& token_type) -> std::ostream&;
} // namespace Hyper
