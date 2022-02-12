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
	class TypeValidator : public AstVisitor<TypeValidator>
	{
	public:
		TypeValidator(
			const Diagnostics &diagnostics,
			const std::vector<Symbol> &symbols);

		void visit_function_declaration(
			const FunctionDeclaration *function_declaration);
		void visit_variable_declaration_post(
			const VariableDeclaration *variable_declaration);

		void visit_bool_literal(const BoolLiteral *bool_literal);
		void visit_floating_literal(const FloatingLiteral *floating_literal);
		void visit_integer_literal(const IntegerLiteral *integer_literal);
		void visit_string_literal(const StringLiteral *string_literal);

		void visit_call_expression_post(const CallExpression *call_expression);
		void visit_cast_expression_post(const CastExpression *cast_expression);

	private:
		bool match_data_type(const DataType &data_type) const noexcept;

		DataType find_data_type(const Identifier &identifier) const noexcept;

		Symbol find_symbol(const Identifier &identifier) const noexcept;

	private:
		const Diagnostics &m_diagnostics;
		const std::vector<Symbol> &m_symbols;

		Symbol m_current_function = {};
		DataType m_current_data_type = {};
	};
} // namespace hyper
