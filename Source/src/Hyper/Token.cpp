/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Token.hpp"

namespace Hyper
{
	std::ostream &operator<<(std::ostream &ostream, const Token::Type &type)
	{
		switch (type)
		{
		case Token::Type::Eof:
			ostream << "Eof";
			break;
		case Token::Type::Assign:
			ostream << "Assign";
			break;
		case Token::Type::Identifier:
			ostream << "Identifier";
			break;
		case Token::Type::Colon:
			ostream << "Colon";
			break;
		case Token::Type::Semicolon:
			ostream << "Semicolon";
			break;
		case Token::Type::Plus:
			ostream << "Plus";
			break;
		case Token::Type::PlusEqual:
			ostream << "Plus Equal";
			break;
		case Token::Type::Minus:
			ostream << "Minus";
			break;
		case Token::Type::MinusEqual:
			ostream << "Minus Equal";
			break;
		case Token::Type::Star:
			ostream << "Star";
			break;
		case Token::Type::StarEqual:
			ostream << "Star Equal";
			break;
		case Token::Type::Slash:
			ostream << "Slash";
			break;
		case Token::Type::SlashEqual:
			ostream << "Slash Equal";
			break;
		case Token::Type::Equal:
			ostream << "Equal";
			break;
		case Token::Type::NotEqual:
			ostream << "Not Equal";
			break;
		case Token::Type::LessThan:
			ostream << "Less Than";
			break;
		case Token::Type::GreaterThan:
			ostream << "Greater Than";
			break;
		case Token::Type::LessEqual:
			ostream << "Less Equal";
			break;
		case Token::Type::GreaterEqual:
			ostream << "Greater Equal";
			break;
		case Token::Type::LeftArrow:
			ostream << "Left Arrow";
			break;
		case Token::Type::RightArrow:
			ostream << "Right Arrow";
			break;
		case Token::Type::LeftCurlyBracket:
			ostream << "Left Curly Bracket";
			break;
		case Token::Type::RightCurlyBracket:
			ostream << "Right Curly Bracket";
			break;
		case Token::Type::LeftSquareBracket:
			ostream << "Left Square Bracket";
			break;
		case Token::Type::RightSquareBracket:
			ostream << "Right Square Bracket";
			break;
		case Token::Type::LeftRoundBracket:
			ostream << "Left Round Bracket";
			break;
		case Token::Type::RightRoundBracket:
			ostream << "Right Round Bracket";
			break;
		case Token::Type::Else:
			ostream << "Else";
			break;
		case Token::Type::For:
			ostream << "For";
			break;
		case Token::Type::Function:
			ostream << "Function";
			break;
		case Token::Type::If:
			ostream << "If";
			break;
		case Token::Type::Let:
			ostream << "Let";
			break;
		case Token::Type::Mutable:
			ostream << "Mutable";
			break;
		case Token::Type::Print:
			ostream << "Print";
			break;
		case Token::Type::Return:
			ostream << "Return";
			break;
		case Token::Type::While:
			ostream << "While";
			break;
		case Token::Type::Bool:
			ostream << "Bool";
			break;
		case Token::Type::Int8:
			ostream << "Int8";
			break;
		case Token::Type::Int16:
			ostream << "Int16";
			break;
		case Token::Type::Int32:
			ostream << "Int32";
			break;
		case Token::Type::Int64:
			ostream << "Int64";
			break;
		case Token::Type::Uint8:
			ostream << "Uint8";
			break;
		case Token::Type::Uint16:
			ostream << "Uint16";
			break;
		case Token::Type::Uint32:
			ostream << "Uint32";
			break;
		case Token::Type::Uint64:
			ostream << "Uint64";
			break;
		case Token::Type::ISize:
			ostream << "ISize";
			break;
		case Token::Type::USize:
			ostream << "USize";
			break;
		case Token::Type::Void:
			ostream << "Void";
			break;
		case Token::Type::NumericLiteral:
			ostream << "Numeric Literal";
			break;
		case Token::Type::StringLiteral:
			ostream << "String Literal";
			break;
		default:
			break;
		}

		return ostream;
	}
} // namespace Hyper
