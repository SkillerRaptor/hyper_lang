/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/post_symbol_collector.hpp"

namespace hyper
{
	PostSymbolCollector::PostSymbolCollector(
		const std::vector<Symbol> &all_symbols)
		: m_all_symbols(all_symbols)
	{
	}

	bool PostSymbolCollector::visit_import_declaration(
		const ImportDeclaration *import_declaration)
	{
		// FIXME: This only imports the first iteration
		// 				If you import a file which imports another file, then
		//				the symbol collector will not import the symbol of that

		for (const Symbol &symbol : m_all_symbols)
		{
			if (symbol.file == import_declaration->module_name())
			{
				m_symbols.emplace_back(symbol);
			}
		}

		return true;
	}

	std::vector<Symbol> PostSymbolCollector::symbols() const
	{
		return m_symbols;
	}
} // namespace hyper
