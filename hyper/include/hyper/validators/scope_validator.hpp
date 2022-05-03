/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/ast_visitor.hpp"
#include "hyper/diagnostics.hpp"
#include "hyper/symbol.hpp"

namespace hyper
{
	class ScopeValidator : public AstVisitor<ScopeValidator>
	{
	public:
		ScopeValidator(
			const Diagnostics &diagnostics,
			const std::vector<Symbol> &symbols);

		bool visit_function_declaration(
			const FunctionDeclaration *function_declaration) const;
		bool visit_translation_unit_declaration(
			const TranslationUnitDeclaration *translation_unit_declaration);
		bool visit_variable_declaration(
			const VariableDeclaration *variable_declaration) const;

		bool visit_call_expression(const CallExpression *call_expression) const;
		bool visit_identifier_expression(
			const IdentifierExpression *identifier_expression) const;

		bool visit_assign_statement(const AssignStatement *assign_statement) const;
		bool visit_compound_assign_statement(
			const CompoundAssignStatement *compound_assign_statement) const;

	private:
		bool is_symbol_present(const Identifier &identifier) const noexcept;
		bool is_symbol_unique(const Identifier &identifier) const noexcept;

	private:
		const Diagnostics &m_diagnostics;
		const std::vector<Symbol> &m_symbols;

		std::string m_current_file;
	};
} // namespace hyper
