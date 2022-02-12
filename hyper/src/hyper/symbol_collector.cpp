/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/symbol_collector.hpp"

namespace hyper
{
	void SymbolCollector::visit_function_declaration(
		const FunctionDeclaration *function_declaration)
	{
		const Symbol symbol = {
			.name = function_declaration->identifier().value,
			.file = "",
			.kind = Symbol::Kind::Function,
			.data_type = function_declaration->return_type(),
			.source_range = function_declaration->identifier().source_range,
		};

		m_symbols.emplace_back(symbol);
	}

	void SymbolCollector::visit_variable_declaration(
		const VariableDeclaration *variable_declaration)
	{
		const Symbol symbol = {
			.name = variable_declaration->identifier().value,
			.file = "",
			.kind = Symbol::Kind::Variable,
			.data_type = variable_declaration->type(),
			.source_range = variable_declaration->identifier().source_range,
		};

		m_symbols.emplace_back(symbol);
	}

	std::vector<Symbol> SymbolCollector::symbols() const
	{
		return m_symbols;
	}
} // namespace hyper
