/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/compiler.hpp"

#include "hyper/backends/c/c_compiler.hpp"
#include "hyper/backends/c/c_generator.hpp"
#include "hyper/backends/c/c_linker.hpp"
#include "hyper/diagnostics.hpp"
#include "hyper/lexer.hpp"
#include "hyper/logger.hpp"
#include "hyper/parser.hpp"
#include "hyper/symbol_collector.hpp"
#include "hyper/utilities/assertions.hpp"
#include "hyper/validators/scope_validator.hpp"
#include "hyper/validators/type_validator.hpp"

#include <csignal>
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
		(void) m_includes;
		install_signals();
	}

	int Compiler::compile() const
	{
		size_t current_file = 1;
		std::vector<AstNode *> trees = {};
		for (std::string_view file : m_files)
		{
			Logger::info(
				"Building hyper file {} ({}/{})\n",
				file,
				current_file++,
				m_files.size());

			const std::optional<std::string> text = read_file(file);
			if (!text.has_value())
			{
				Logger::error("Failed to compile non-existing file: '{}'", file);
				continue;
			}

			std::string_view file_text = text.value();
			if (file_text.empty())
			{
				Logger::error("Failed to compile empty file: '{}'\n", file);
				continue;
			}

			const Diagnostics diagnostics(file, file_text);
			AstNode *ast = parse_file(diagnostics, file, file_text);
			if (ast == nullptr)
			{
				Logger::error("Failed to parse file: '{}'\n", file);
				continue;
			}

			trees.push_back(ast);
		}

		std::filesystem::create_directory("./build");

		std::vector<std::string> output_files = {};
		for (size_t i = 0; i < trees.size(); ++i)
		{
			std::string_view file = m_files[i];
			const Diagnostics diagnostics(file, read_file(file).value());

			AstNode *ast = trees[i];

			SymbolCollector symbol_collector = {};
			symbol_collector.traverse(ast);

			const std::vector<Symbol> symbols = symbol_collector.symbols();
			TODO("Changing `std::vector<Symbol>` to `std::span<Symbol>`");

			ScopeValidator scope_validator(diagnostics, symbols);
			scope_validator.traverse(ast);

			TypeValidator type_validator(diagnostics, symbols);
			type_validator.traverse(ast);

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
			output_files, m_freestanding, m_linker_script, m_output_file);
		c_linker.link();

		return EXIT_SUCCESS;
	}

	void Compiler::install_signals() const
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

	std::optional<std::string> Compiler::read_file(std::string_view file) const
	{
		if (!std::filesystem::exists(file))
		{
			Logger::error("Failed to open non-existing file: '{}'\n", file);
			return std::nullopt;
		}

		if (std::filesystem::is_directory(file))
		{
			Logger::error("Failed to read directory: '{}'\n", file);
			return std::nullopt;
		}

		const std::string text = [&file]()
		{
			std::ifstream stream(file.data());
			std::stringstream content;
			content << stream.rdbuf();
			return content.str();
		}();

		return text;
	}

	AstNode *Compiler::parse_file(
		const Diagnostics &diagnostics,
		std::string_view file,
		std::string_view text) const
	{
		Lexer lexer(diagnostics, text);
		const std::vector<Token> tokens = lexer.lex();

		Parser parser(diagnostics, tokens, file);
		return parser.parse();
	}
} // namespace hyper
