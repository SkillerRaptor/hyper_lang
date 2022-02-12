/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
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

		void visit_function_declaration(
			const FunctionDeclaration *function_declaration) const;
		void visit_variable_declaration(
			const VariableDeclaration *variable_declaration) const;

		void visit_call_expression(const CallExpression *call_expression) const;
		void visit_identifier_expression(
			const IdentifierExpression *identifier_expression) const;

		void visit_assign_statement(const AssignStatement *assign_statement) const;
		void visit_compound_assign_statement(
			const CompoundAssignStatement *compound_assign_statement) const;

	private:
		bool is_symbol_present(const Identifier &identifier) const noexcept;
		bool is_symbol_unique(const Identifier &identifier) const noexcept;

	private:
		const Diagnostics &m_diagnostics;
		const std::vector<Symbol> &m_symbols;
	};
} // namespace hyper
