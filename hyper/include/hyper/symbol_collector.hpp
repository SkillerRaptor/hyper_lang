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
		bool visit_function_declaration(
			const FunctionDeclaration *function_declaration);
		bool visit_export_declaration(const ExportDeclaration *export_declaration);
		bool visit_translation_unit_declaration(
			const TranslationUnitDeclaration *translation_unit_declaration);
		bool visit_variable_declaration(
			const VariableDeclaration *variable_declaration);

		std::vector<Symbol> symbols() const;

	private:
		bool m_capture_symbol = false;
		std::string m_current_file;
		std::vector<Symbol> m_symbols = {};
	};
} // namespace hyper
