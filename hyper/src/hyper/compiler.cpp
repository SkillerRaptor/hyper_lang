/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/compiler.hpp"

#include "hyper/c_generator.hpp"
#include "hyper/diagnostics.hpp"
#include "hyper/lexer.hpp"
#include "hyper/logger.hpp"
#include "hyper/parser.hpp"
#include "hyper/post_symbol_collector.hpp"
#include "hyper/symbol_collector.hpp"
#include "hyper/validators/scope_validator.hpp"
#include "hyper/validators/type_validator.hpp"

#include <csignal>
#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_map>

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
		std::unordered_map<std::string, std::vector<Symbol>> ast_symbols = {};

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

			SymbolCollector symbol_collector = {};
			symbol_collector.traverse(compilation_unit.ast);

			const std::vector<Symbol> symbols = symbol_collector.symbols();
			ast_symbols[file] = symbols;

			trees.push_back(std::move(compilation_unit));
		}

		{
			std::vector<Symbol> all_symbols = {};
			for (auto [file, current_symbols] : ast_symbols)
			{
				all_symbols.insert(
					all_symbols.end(), current_symbols.begin(), current_symbols.end());
			}

			for (const CompilationUnit &compilation_unit : trees)
			{
				PostSymbolCollector post_symbol_collector(all_symbols);
				post_symbol_collector.traverse(compilation_unit.ast);

				const std::vector<Symbol> post_symbols =
					post_symbol_collector.symbols();

				std::vector<Symbol> &symbols = ast_symbols[compilation_unit.file];
				symbols.insert(symbols.end(), post_symbols.begin(), post_symbols.end());
			}
		}

		for (const CompilationUnit &compilation_unit : trees)
		{
			const AstNode *ast = compilation_unit.ast;
			const Diagnostics &diagnostics = compilation_unit.diagnostics;
			const std::vector<Symbol> &symbols = ast_symbols[compilation_unit.file];

			ScopeValidator scope_validator(diagnostics, symbols);
			scope_validator.traverse(ast);

			TypeValidator type_validator(diagnostics, symbols);
			type_validator.traverse(ast);

			CGenerator c_generator;
			c_generator.traverse(ast);

			delete ast;
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
		AstNode *ast = parser.parse();

		return { ast, diagnostics, file };
	}
} // namespace hyper
