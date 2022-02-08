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
#include "hyper/validators/scope_validator.hpp"
#include "hyper/validators/type_validator.hpp"

#include <csignal>
#include <filesystem>
#include <fstream>
#include <string>

namespace hyper
{
	Compiler::Compiler(const std::vector<std::string> &files)
		: m_files(files)
	{
		std::signal(
			SIGSEGV,
			[](int)
			{
				Logger::error("Internal compiler error - Segmentation fault");
				std::exit(1);
			});
	}

	int Compiler::compile() const
	{
		std::vector<Symbol> symbols = {};

		size_t current_file = 1;
		std::vector<CompilationUnit> trees = {};
		for (const std::string &file : m_files)
		{
			Logger::log(
				"[{}/{}] Building Hyper file {}", current_file++, m_files.size(), file);

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

			ScopeValidator scope_validator(diagnostics, symbols);
			ast->validate_scope(scope_validator);

			TypeValidator type_validator(diagnostics, symbols);
			ast->validate_type(type_validator);
		}

		return EXIT_SUCCESS;
	}

	Compiler::CompilationUnit Compiler::parse_file(const std::string &file) const
	{
		if (!std::filesystem::exists(file))
		{
			Logger::error("the file '{}' does not exists", file);
			return {};
		}

		if (std::filesystem::is_directory(file))
		{
			Logger::error("the file '{}' can't be a directory", file);
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
			Logger::error("the file '{}' does not contain any code", file);
			return {};
		}

		const Diagnostics diagnostics(file, text);

		Lexer lexer(diagnostics, text);
		const std::vector<Token> tokens = lexer.lex();

		Parser parser(diagnostics, tokens, file);
		std::unique_ptr<AstNode> ast = parser.parse();

		return { std::move(ast), diagnostics };
	}

	std::vector<Symbol> Compiler::parse_symbols(const AstNodePtr &ast) const
	{
		std::vector<Symbol> symbols = {};
		ast->collect_symbols(symbols);
		return symbols;
	}
} // namespace hyper
