/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "HyperCompiler/Lexer.hpp"
#include "HyperCompiler/Ast/AstNode.hpp"
#include "HyperCompiler/Ast/Declarations.hpp"
#include "HyperCompiler/Ast/Expressions.hpp"
#include "HyperCompiler/Ast/Literals.hpp"
#include "HyperCompiler/Ast/Statements.hpp"

namespace HyperCompiler
{
	class Parser
	{
	public:
		void initialize(Lexer* lexer);
		
		AstNode* parse();
		
	private:
		Expression* parse_binary_expression();
		Expression* parse_primary_expression();
		
		Expression* parse_numeric_literal();

	private:
		Lexer* m_lexer{};
	};
} // namespace HyperCompiler
