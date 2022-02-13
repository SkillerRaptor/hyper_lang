/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/symbol_collector.hpp"

namespace hyper
{
	bool SymbolCollector::visit_function_declaration(
		const FunctionDeclaration *function_declaration)
	{
		const Symbol symbol = {
			.name = function_declaration->identifier().value,
			.file = m_current_file,
			.kind = Symbol::Kind::Function,
			.data_type = function_declaration->return_type(),
			.exported = m_capture_symbol,
			.source_range = function_declaration->identifier().source_range,
		};

		m_symbols.emplace_back(symbol);

		return true;
	}

	bool SymbolCollector::visit_export_declaration(
		const ExportDeclaration *export_declaration)
	{
		m_capture_symbol = true;

		traverse_statement(export_declaration->statement());

		m_capture_symbol = false;

		return false;
	}

	bool SymbolCollector::visit_translation_unit_declaration(
		const TranslationUnitDeclaration *translation_unit_declaration)
	{
		m_current_file = translation_unit_declaration->file();

		return true;
	}

	bool SymbolCollector::visit_variable_declaration(
		const VariableDeclaration *variable_declaration)
	{
		const Symbol symbol = {
			.name = variable_declaration->identifier().value,
			.file = m_current_file,
			.kind = Symbol::Kind::Variable,
			.data_type = variable_declaration->type(),
			.exported = false,
			.source_range = variable_declaration->identifier().source_range,
		};

		m_symbols.emplace_back(symbol);

		return true;
	}

	std::vector<Symbol> SymbolCollector::symbols() const
	{
		return m_symbols;
	}
} // namespace hyper
