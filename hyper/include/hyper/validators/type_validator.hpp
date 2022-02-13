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

		bool visit_function_declaration(
			const FunctionDeclaration *function_declaration);
		bool visit_variable_declaration(
			const VariableDeclaration *variable_declaration);

		bool visit_call_expression(const CallExpression *call_expression);
		bool visit_cast_expression(const CastExpression *cast_expression);

		bool visit_bool_literal(const BoolLiteral *bool_literal);
		bool visit_floating_literal(const FloatingLiteral *floating_literal);
		bool visit_integer_literal(const IntegerLiteral *integer_literal);
		bool visit_string_literal(const StringLiteral *string_literal);

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
