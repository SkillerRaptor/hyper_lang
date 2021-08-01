/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "HyperCompiler/Token.hpp"

namespace HyperCompiler
{
	std::ostream& operator<<(std::ostream& ostream, const Token::Type& token_type)
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
		case Token::Type::PlusEqual:
			ostream << "PlusEqual";
			break;
		case Token::Type::MinusEqual:
			ostream << "MinusEqual";
			break;
		case Token::Type::StarEqual:
			ostream << "StarEqual";
			break;
		case Token::Type::SlashEqual:
			ostream << "SlashEqual";
			break;
		case Token::Type::Modular:
			ostream << "Modular";
			break;
		case Token::Type::ModularEqual:
			ostream << "ModularEqual";
			break;
		case Token::Type::Equal:
			ostream << "Equal";
			break;
		case Token::Type::NotEqual:
			ostream << "NotEqual";
			break;
		case Token::Type::LessThan:
			ostream << "LessThan";
			break;
		case Token::Type::GreaterThan:
			ostream << "GreaterThan";
			break;
		case Token::Type::LessEqual:
			ostream << "LessEqual";
			break;
		case Token::Type::GreaterEqual:
			ostream << "GreaterEqual";
			break;
		case Token::Type::LogicalAnd:
			ostream << "LogicalAnd";
			break;
		case Token::Type::LogicalOr:
			ostream << "LogicalOr";
			break;
		case Token::Type::LogicalNot:
			ostream << "LogicalNot";
			break;
		case Token::Type::Increment:
			ostream << "Increment";
			break;
		case Token::Type::Decrement:
			ostream << "Decrement";
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
			ostream << "LeftArrow";
			break;
		case Token::Type::RightArrow:
			ostream << "RightArrow";
			break;
		case Token::Type::LeftBrace:
			ostream << "LeftBrace";
			break;
		case Token::Type::RightBrace:
			ostream << "RightBrace";
			break;
		case Token::Type::LeftParenthesis:
			ostream << "LeftParenthesis";
			break;
		case Token::Type::RightParenthesis:
			ostream << "RightParenthesis";
			break;
		case Token::Type::LeftBracket:
			ostream << "LeftBracket";
			break;
		case Token::Type::RightBracket:
			ostream << "RightBracket";
			break;
		case Token::Type::LeftShift:
			ostream << "LeftShift";
			break;
		case Token::Type::RightShift:
			ostream << "RightShift";
			break;
		case Token::Type::BitwiseAnd:
			ostream << "BitwiseAnd";
			break;
		case Token::Type::BitwiseOr:
			ostream << "BitwiseOr";
			break;
		case Token::Type::BitwiseXor:
			ostream << "BitwiseXor";
			break;
		case Token::Type::BitwiseNot:
			ostream << "BitwiseNot";
			break;
		case Token::Type::BitwiseAndEqual:
			ostream << "BitwiseAndEqual";
			break;
		case Token::Type::BitwiseOrEqual:
			ostream << "BitwiseOrEqual";
			break;
		case Token::Type::BitwiseXorEqual:
			ostream << "BitwiseXorEqual";
			break;
		case Token::Type::Function:
			ostream << "Function";
			break;
		case Token::Type::Override:
			ostream << "Override";
			break;
		case Token::Type::Virtual:
			ostream << "Virtual";
			break;
		case Token::Type::If:
			ostream << "If";
			break;
		case Token::Type::Else:
			ostream << "Else";
			break;
		case Token::Type::Do:
			ostream << "Do";
			break;
		case Token::Type::While:
			ostream << "While";
			break;
		case Token::Type::For:
			ostream << "For";
			break;
		case Token::Type::Of:
			ostream << "Of";
			break;
		case Token::Type::Return:
			ostream << "Return";
			break;
		case Token::Type::Break:
			ostream << "Break";
			break;
		case Token::Type::Breakall:
			ostream << "Breakall";
			break;
		case Token::Type::Continue:
			ostream << "Continue";
			break;
		case Token::Type::Import:
			ostream << "Import";
			break;
		case Token::Type::Export:
			ostream << "Export";
			break;
		case Token::Type::Package:
			ostream << "Package";
			break;
		case Token::Type::Mutable:
			ostream << "Mutable";
			break;
		case Token::Type::Enum:
			ostream << "Enum";
			break;
		case Token::Type::Union:
			ostream << "Union";
			break;
		case Token::Type::Struct:
			ostream << "Struct";
			break;
		case Token::Type::Void:
			ostream << "Void";
			break;
		case Token::Type::Bool:
			ostream << "Bool";
			break;
		case Token::Type::Char:
			ostream << "Char";
			break;
		case Token::Type::Float:
			ostream << "Float";
			break;
		case Token::Type::Double:
			ostream << "Double";
			break;
		case Token::Type::Int:
			ostream << "Int";
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
		case Token::Type::Uint:
			ostream << "Uint";
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
		case Token::Type::String:
			ostream << "String";
			break;
		case Token::Type::IntLiteral:
			ostream << "IntLiteral";
			break;
		case Token::Type::StringLiteral:
			ostream << "StringLiteral";
			break;
		case Token::Type::Print:
			ostream << "Print";
			break;
		default:
			break;
		}

		return ostream;
	}
} // namespace HyperCompiler
