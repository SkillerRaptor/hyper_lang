/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/compiler.hpp"

#include "hyper/ast/ast.hpp"
#include "hyper/diagnostics.hpp"
#include "hyper/lexer.hpp"
#include "hyper/logger.hpp"
#include "hyper/parser.hpp"
#include "hyper/scope_validator.hpp"
#include "hyper/type_validator.hpp"

#include <filesystem>
#include <fstream>
#include <string>

namespace hyper
{
	Compiler::Compiler(const std::vector<std::string> &files)
		: m_files(files)
	{
	}

	int Compiler::compile() const
	{
		std::vector<Symbol> symbols = {};

		std::vector<CompilationUnit> trees = {};
		for (const std::string &file : m_files)
		{
			CompilationUnit compilation_unit = parse_file(file);
			if (compilation_unit.ast == nullptr)
			{
				continue;
			}

			const std::vector<Symbol> ast_symbols =
				parse_symbols(compilation_unit.ast);
			symbols.insert(symbols.end(), ast_symbols.begin(), ast_symbols.end());
			trees.push_back(std::move(compilation_unit));
		}

		for (const CompilationUnit &compilation_unit : trees)
		{
			const AstNodePtr &ast = compilation_unit.ast;
			const Diagnostics &diagnostics = compilation_unit.diagnostics;

			hyper::ScopeValidator scope_validator(diagnostics, symbols);
			ast->validate_scope(scope_validator);

			hyper::TypeValidator type_validator(diagnostics, symbols);
			ast->validate_type(type_validator);
		}

		// TODO: Implementing IR Module & Builder

		return EXIT_SUCCESS;
	}

	Compiler::CompilationUnit Compiler::parse_file(const std::string &file) const
	{
		if (!std::filesystem::exists(file))
		{
			hyper::Logger::error("the file '{}' does not exists", file);
			return {};
		}

		if (std::filesystem::is_directory(file))
		{
			hyper::Logger::error("the file '{}' can't be a directory", file);
			return {};
		}

		const std::string text = [&file]()
		{
			std::ifstream stream(file);
			std::stringstream content;
			content << stream.rdbuf();
			return content.str();
		}();

		if (text.empty())
		{
			hyper::Logger::error("the file '{}' does not contain any code", file);
			return {};
		}

		const hyper::Diagnostics diagnostics(file, text);

		hyper::Lexer lexer(diagnostics, text);
		const std::vector<hyper::Token> tokens = lexer.lex();

		hyper::Parser parser(diagnostics, tokens, file);
		std::unique_ptr<hyper::AstNode> ast = parser.parse();

		return { std::move(ast), diagnostics };
	}

	std::vector<Symbol> Compiler::parse_symbols(const AstNodePtr &ast) const
	{
		std::vector<Symbol> symbols = {};
		ast->collect_symbols(symbols);
		return symbols;
	}
} // namespace hyper
