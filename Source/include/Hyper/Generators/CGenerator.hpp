/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/DataType.hpp"
#include "Hyper/Formatter.hpp"
#include "Hyper/Generators/Generator.hpp"

#include <sstream>

namespace Hyper
{
	class CGenerator : public Generator
	{
	public:
		explicit CGenerator(std::string file);

		void generate() const override;

		void visit(const AstNode &ast) override;

		void visit(const FunctionDeclaration &function_declaration) override;
		void visit(
			const TranslationUnitDeclaration &translation_unit_declaration) override;
		void visit(const VariableDeclaration &variable_declaration) override;

		void visit(const BinaryExpression &binary_expression) override;
		void visit(const CallExpression &call_expression) override;
		void visit(const IdentifierExpression &identifier_expression) override;

		void visit(const NumericLiteral &numeric_literal) override;
		void visit(const StringLiteral &string_literal) override;

		void visit(const AssignStatement &assign_statement) override;
		void visit(const CompoundStatement &compound_statement) override;
		void visit(const ExpressionStatement &expression_statement) override;
		void visit(const ForStatement &for_statement) override;
		void visit(const IfStatement &if_statement) override;
		void visit(const PrintStatement &print_statement) override;
		void visit(const ReturnStatement &return_statement) override;
		void visit(const WhileStatement &while_statement) override;

	private:
		template <typename... Args>
		void print(
			std::stringstream &string_stream,
			const std::string &string,
			Args &&...args)
		{
			string_stream << Formatter::format(string, std::forward<Args>(args)...);
		}

		void enter_scope();
		void leave_scope();

		std::string map_type(DataType type) const;

	private:
		std::stringstream m_source;
		std::stringstream m_header;

		std::string m_indent;
	};
} // namespace Hyper
