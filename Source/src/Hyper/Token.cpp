/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Token.hpp"

namespace Hyper
{
	std::ostream &operator<<(std::ostream &ostream, const Token::Type &token_type)
	{
		switch (token_type)
		{
		case Token::Type::None:
			ostream << "None";
			break;
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

	std::ostream &operator<<(std::ostream &ostream, const Token &token)
	{
		ostream << "value = " << token.value
						<< ", type = " << token.type;
		return ostream;
	}
} // namespace Hyper
