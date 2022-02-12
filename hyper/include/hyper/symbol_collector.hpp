/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/ast_visitor.hpp"
#include "hyper/symbol.hpp"

#include <vector>

namespace hyper
{
	class SymbolCollector : public AstVisitor<SymbolCollector>
	{
	public:
		void visit_function_declaration(
			const FunctionDeclaration *function_declaration);
		void visit_variable_declaration(
			const VariableDeclaration *variable_declaration);

		std::vector<Symbol> symbols() const;

	private:
		std::vector<Symbol> m_symbols = {};
	};
} // namespace hyper
