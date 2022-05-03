/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/compiler.hpp"

#include "hyper/ast/ast_node.hpp"
#include "hyper/backends/c/c_compiler.hpp"
#include "hyper/backends/c/c_generator.hpp"
#include "hyper/backends/c/c_linker.hpp"
#include "hyper/diagnostics.hpp"
#include "hyper/lexer.hpp"
#include "hyper/parser.hpp"
#include "hyper/symbol_collector.hpp"
#include "hyper/validators/scope_validator.hpp"
#include "hyper/validators/type_validator.hpp"
#include "hyper_utilities/args_parser.hpp"
#include "hyper_utilities/assertions.hpp"
#include "hyper_utilities/logger.hpp"
#include "hyper_utilities/profiler.hpp"
#include "hyper_utilities/utilities.hpp"

#include <csignal>
#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_map>

namespace hyper
{
	Compiler::Compiler(const Options &options)
		: m_freestanding(options.freestanding)
		, m_linker_script(options.linker_script)
		, m_output_directory(options.output_directory)
		, m_output_executable(options.output_executable)
		, m_include_directories(options.include_directories)
		, m_source_files(options.source_files)
	{
		install_signal_handlers();
	}

	int Compiler::compile() const
	{
		HYPER_PROFILE_FUNCTION();

		const std::string_view output_directory =
			m_output_directory.empty() ? "./build/" : m_output_directory;
		std::filesystem::create_directory(output_directory);

		std::vector<std::string> output_files = {};
		for (size_t i = 0; i < m_source_files.size(); ++i)
		{
			const std::string_view file = m_source_files[i];

			Logger::info(
				"Compiling {} ({}/{})\n", file, i + 1, m_source_files.size());

			const Expected<std::string, utilities::FileError> text =
				utilities::read_file(file);
			if (text.is_error())
			{
				Logger::error("Failed to read file: '{}'\n", file);
				continue;
			}

			const std::string_view file_text = text.value();
			if (file_text.empty())
			{
				Logger::error("Failed to process empty file: '{}'\n", file);
				continue;
			}

			const Diagnostics diagnostics(file, file_text);

			const AstNode *ast = parse_file(diagnostics, file, file_text);
			if (ast == nullptr)
			{
				Logger::error("Failed to parse file: '{}'\n", file);
				continue;
			}

			validate_ast(diagnostics, ast);

			const std::filesystem::path path = file;
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
			output_files,
			m_freestanding,
			m_linker_script,
			m_output_executable);
		c_linker.link();

		return EXIT_SUCCESS;
	}

	void Compiler::install_signal_handlers() const
	{
		std::signal(
			SIGABRT,
			[](int)
			{
				Logger::error("An internal compiler error occured: Aborted\n");
				std::exit(1);
			});

		std::signal(
			SIGSEGV,
			[](int)
			{
				Logger::error(
					"An internal compiler error occured: Segmentation fault\n");
				std::exit(1);
			});
	}

	AstNode *Compiler::parse_file(
		const Diagnostics &diagnostics,
		std::string_view file,
		std::string_view text) const
	{
		HYPER_PROFILE_FUNCTION();

		Lexer lexer(diagnostics, text);
		const std::vector<Token> tokens = lexer.lex();

		Parser parser(diagnostics, tokens, file);
		return parser.parse();
	}

	void Compiler::validate_ast(
		const Diagnostics &diagnostics,
		const AstNode *ast) const
	{
		HYPER_PROFILE_FUNCTION();

		SymbolCollector symbol_collector = {};
		symbol_collector.traverse(ast);

		const std::vector<Symbol> symbols = symbol_collector.symbols();

		ScopeValidator scope_validator(diagnostics, symbols);
		scope_validator.traverse(ast);

		TypeValidator type_validator(diagnostics, symbols);
		type_validator.traverse(ast);
	}
} // namespace hyper
