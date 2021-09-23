/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Token.hpp"

namespace Hyper
{
	auto operator<<(std::ostream& ostream, const Token::Type& token_type) -> std::ostream&
	{
		switch (token_type)
		{
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
		case Token::Type::Modular:
			ostream << "Modular";
			break;
		case Token::Type::ModularEqual:
			ostream << "Modular Equal";
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
		case Token::Type::Assign:
			ostream << "Assign";
			break;
		case Token::Type::Identifier:
			ostream << "Identifier";
			break;
		case Token::Type::Semicolon:
			ostream << "Semicolon";
			break;
		case Token::Type::Colon:
			ostream << "Colon";
			break;
		case Token::Type::Comma:
			ostream << "Comma";
			break;
		case Token::Type::Dot:
			ostream << "Dot";
			break;
		case Token::Type::LeftArrow:
			ostream << "Left Arrow";
			break;
		case Token::Type::RightArrow:
			ostream << "Right Arrow";
			break;
		case Token::Type::LeftBrace:
			ostream << "Left Brace";
			break;
		case Token::Type::RightBrace:
			ostream << "Right Brace";
			break;
		case Token::Type::LeftParenthesis:
			ostream << "Left Parenthesis";
			break;
		case Token::Type::RightParenthesis:
			ostream << "Right Parenthesis";
			break;
		case Token::Type::LeftBracket:
			ostream << "Left Bracket";
			break;
		case Token::Type::RightBracket:
			ostream << "Right Bracket";
			break;
		case Token::Type::LeftShift:
			ostream << "Left Shift";
			break;
		case Token::Type::RightShift:
			ostream << "Right Shift";
			break;
		case Token::Type::Increment:
			ostream << "Increment";
			break;
		case Token::Type::Decrement:
			ostream << "Decrement";
			break;
		case Token::Type::BitwiseAnd:
			ostream << "Bitwise And";
			break;
		case Token::Type::BitwiseOr:
			ostream << "Bitwise Or";
			break;
		case Token::Type::BitwiseXor:
			ostream << "Bitwise Xor";
			break;
		case Token::Type::BitwiseNot:
			ostream << "Bitwise Not";
			break;
		case Token::Type::BitwiseAndEqual:
			ostream << "Bitwise And Equal";
			break;
		case Token::Type::BitwiseOrEqual:
			ostream << "Bitwise Or Equal";
			break;
		case Token::Type::BitwiseXorEqual:
			ostream << "Bitwise Xor Equal";
			break;
		case Token::Type::LogicalAnd:
			ostream << "Logical And";
			break;
		case Token::Type::LogicalOr:
			ostream << "Logical Or";
			break;
		case Token::Type::LogicalNot:
			ostream << "Logical Not";
			break;
		case Token::Type::Function:
			ostream << "Function";
			break;
		case Token::Type::Return:
			ostream << "Return";
			break;
		case Token::Type::Void:
			ostream << "Void";
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
