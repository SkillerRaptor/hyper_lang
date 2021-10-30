/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Types.hpp"
#include "Hyper/Generators/Generator.hpp"

#include <fstream>
#include <vector>

namespace Hyper
{
	class CGenerator : public Generator
	{
	public:
		explicit CGenerator(std::string file);

		void generate_pre() override;
		void generate_post() override;

		void visit(const AstNode &ast_node) override;

		void visit(const FunctionDeclaration &function_declaration) override;
		void visit(const VariableDeclaration &variable_declaration) override;

		void visit(const BinaryExpression &binary_expression) override;
		void visit(const IdentifierExpression &identifier_expression) override;

		void visit(const NumericLiteral &numeric_literal) override;

		void visit(const AssignStatement &assign_statement) override;
		void visit(const CompoundStatement &compound_statement) override;
		void visit(const ForStatement &for_statement) override;
		void visit(const IfStatement &if_statement) override;
		void visit(const PrintStatement &print_statement) override;
		void visit(const WhileStatement &while_statement) override;

	private:
		void enter_scope();
		void leave_scope();
		
		std::string match_type(Type type) const;

	private:
		std::ofstream m_output_file;
		std::string m_indent;

		std::vector<std::string> m_symbols;
	};
} // namespace Hyper
