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
		// TODO: Adding symbol table
		for (const std::string &file : m_files)
		{
			const AstNodePtr ast = parse_file(file);
			// TODO: Parse symbols from ast
		}

		// TODO: Implementing validators
		// TODO: Implementing IR Module & Builder

		return EXIT_SUCCESS;
	}

	AstNodePtr Compiler::parse_file(const std::string &file) const
	{
		if (!std::filesystem::exists(file))
		{
			hyper::Logger::error("the file '{}' does not exists", file);
			return nullptr;
		}

		if (std::filesystem::is_directory(file))
		{
			hyper::Logger::error("the file '{}' can't be a directory", file);
			return nullptr;
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
			return nullptr;
		}

		hyper::Diagnostics diagnostics(file, text);

		hyper::Lexer lexer(diagnostics, text);
		const std::vector<hyper::Token> tokens = lexer.lex();

		hyper::Parser parser(diagnostics, tokens, file);
		std::unique_ptr<hyper::AstNode> ast = parser.parse();

		return ast;
	}
} // namespace hyper
