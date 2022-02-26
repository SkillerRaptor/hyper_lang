/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/compiler.hpp"

#include "hyper/c/c_compiler.hpp"
#include "hyper/c/c_generator.hpp"
#include "hyper/c/c_linker.hpp"
#include "hyper/diagnostics.hpp"
#include "hyper/lexer.hpp"
#include "hyper/logger.hpp"
#include "hyper/parser.hpp"
#include "hyper/symbol_collector.hpp"
#include "hyper/validators/scope_validator.hpp"
#include "hyper/validators/type_validator.hpp"

#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_map>

namespace hyper
{
	Compiler::Compiler(const Arguments &arguments)
		: m_freestanding(arguments.freestanding)
		, m_linker_script(arguments.linker_script)
		, m_output_file(arguments.output_file)
		, m_includes(arguments.includes)
		, m_files(arguments.files)
	{
		// TODO: Adding includes
		(void) m_includes;
	}

	int Compiler::compile() const
	{
		std::unordered_map<std::string_view, std::vector<Symbol>> ast_symbols = {};

		size_t current_file = 1;
		std::vector<CompilationUnit> trees = {};
		for (std::string_view file : m_files)
		{
			Logger::info(
				"Building hyper file {} ({}/{})\n",
				file,
				current_file++,
				m_files.size());

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

		std::filesystem::create_directory("./build");

		std::vector<std::string> output_files = {};
		for (const CompilationUnit &compilation_unit : trees)
		{
			const AstNode *ast = compilation_unit.ast;
			const Diagnostics &diagnostics = compilation_unit.diagnostics;
			const std::vector<Symbol> &symbols = ast_symbols[compilation_unit.file];

			ScopeValidator scope_validator(diagnostics, symbols);
			scope_validator.traverse(ast);

			TypeValidator type_validator(diagnostics, symbols);
			type_validator.traverse(ast);

			const std::filesystem::path path = compilation_unit.file;
			const std::string file_name = path.filename().string();
			const std::string output_file = "./build/" + file_name;

			CGenerator c_generator(output_file);
			c_generator.traverse(ast);

			output_files.emplace_back(output_file);

			delete ast;
		}

		const CCompiler c_compiler(output_files, m_freestanding);
		c_compiler.compile();

		const CLinker c_linker(
			output_files, m_freestanding, m_linker_script, m_output_file);
		c_linker.link();

		return EXIT_SUCCESS;
	}

	Compiler::CompilationUnit Compiler::parse_file(std::string_view file) const
	{
		if (!std::filesystem::exists(file))
		{
			Logger::error("The file '{}' does not exists\n", file);
			return {};
		}

		if (std::filesystem::is_directory(file))
		{
			Logger::error("The file '{}' can't be a directory\n", file);
			return {};
		}

		const std::string text = [&file]()
		{
			std::ifstream stream(file.data());
			std::stringstream content;
			content << stream.rdbuf();
			return content.str();
		}();

		if (text.empty())
		{
			Logger::error("The file '{}' does not contain any code\n", file);
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
