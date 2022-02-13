/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/ast_visitor.hpp"

#include <sstream>

namespace hyper
{
	class CGenerator : public AstVisitor<CGenerator>
	{
	public:
		explicit CGenerator(std::string output_file);

		bool visit_export_declaration(const ExportDeclaration *export_declaration);
		bool visit_function_declaration(
			const FunctionDeclaration *function_declaration);
		bool visit_import_declaration(const ImportDeclaration *import_declaration);
		bool visit_translation_unit_declaration(
			const TranslationUnitDeclaration *translation_unit_declaration);
		bool visit_variable_declaration(
			const VariableDeclaration *variable_declaration);

		bool visit_binary_expression(const BinaryExpression *binary_expression);
		bool visit_call_expression(const CallExpression *call_expression);
		bool visit_cast_expression(const CastExpression *cast_expression);
		bool visit_conditional_expression(
			const ConditionalExpression *conditional_expression);
		bool visit_identifier_expression(
			const IdentifierExpression *identifier_expression);
		bool visit_unary_expression(const UnaryExpression *unary_expression);

		bool visit_bool_literal(const BoolLiteral *bool_literal);
		bool visit_floating_literal(const FloatingLiteral *floating_literal);
		bool visit_integer_literal(const IntegerLiteral *integer_literal);
		bool visit_string_literal(const StringLiteral *string_literal);

		bool visit_assign_statement(const AssignStatement *assign_statement);
		bool visit_compound_assign_statement(
			const CompoundAssignStatement *compound_assign_statement);
		bool visit_expression_statement(
			const ExpressionStatement *expression_statement);
		bool visit_if_statement(const IfStatement *if_statement);
		bool visit_print_statement(const PrintStatement *print_statement);
		bool visit_return_statement(const ReturnStatement *return_statement);
		bool visit_while_statement(const WhileStatement *while_statement);

	private:
		void start_scope();
		void end_scope();

		std::string map_data_type(const DataType &data_type) const;

	private:
		std::string m_output_file;

		std::stringstream m_source;
		std::stringstream m_header;

		std::string m_indention;
	};
} // namespace hyper
