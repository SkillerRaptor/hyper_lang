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
	class PostSymbolCollector : public AstVisitor<PostSymbolCollector>
	{
	public:
		explicit PostSymbolCollector(const std::vector<Symbol> &all_symbols);

		bool visit_import_declaration(const ImportDeclaration *import_declaration);

		std::vector<Symbol> symbols() const;

	private:
		const std::vector<Symbol> &m_all_symbols;

		std::vector<Symbol> m_symbols = {};
	};
} // namespace hyper
