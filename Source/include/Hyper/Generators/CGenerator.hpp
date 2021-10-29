/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

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

		void visit(const VariableDeclaration &variable_declaration) override;
		void visit(const BinaryExpression &binary_expression) override;
		void visit(const NumericLiteral &numeric_literal) override;

	private:
		void enter_scope();
		void leave_scope();

	private:
		std::ofstream m_output_file;
		std::string m_indent;

		std::vector<std::string> m_symbols;
	};
} // namespace Hyper
