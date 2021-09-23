/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Token.hpp"

namespace Hyper
{
	auto operator<<(std::ostream& ostream, const Hyper::Token::Type& token_type) -> std::ostream&
	{
		switch (token_type)
		{
		case Token::Type::Eof:
			ostream << "Eof";
			break;
		case Token::Type::Plus:
			ostream << "Plus";
			break;
		case Token::Type::Minus:
			ostream << "Minus";
			break;
		case Token::Type::Star:
			ostream << "Star";
			break;
		case Token::Type::Slash:
			ostream << "Slash";
			break;
		case Token::Type::NumericLiteral:
			ostream << "Numeric Literal";
			break;
		default:
			break;
		}

		return ostream;
	}
} // namespace Hyper
