/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Compiler.hpp"

#include "Hyper/Ast/AstNode.hpp"
#include "Hyper/Diagnostics.hpp"
#include "Hyper/Lexer.hpp"
#include "Hyper/Logger.hpp"
#include "Hyper/Parser.hpp"
#include "Hyper/Validators/ScopeValidator.hpp"
#include "Hyper/Validators/TypeValidator.hpp"

#include <fstream>

namespace Hyper
{
	Compiler::Compiler(int argc, char **argv)
		: m_files(argv + 1, argv + argc)
	{
	}

	int Compiler::compile() const
	{
		for (const std::string &file : m_files)
		{
			// TODO: Check if file exists and if file is a directory

			const std::string text = [&file]()
			{
				std::ifstream file_stream(file);
				std::stringstream content;
				content << file_stream.rdbuf();
				return content.str();
			}();

			// TODO: Check if `text` is empty

			Diagnostics diagnostics(file, text);

			Lexer lexer(diagnostics, text);
			Parser parser(diagnostics, lexer, file);

			std::unique_ptr<AstNode> ast = parser.parse_tree();
			ast->dump();

			ScopeValidator scope_validator(diagnostics, ast);
			scope_validator.validate();

			TypeValidator type_validator(diagnostics, ast, scope_validator.symbols());
			type_validator.validate();
		}

		return EXIT_SUCCESS;
	}
} // namespace Hyper
