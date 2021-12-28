/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Compiler.hpp"

#include "Hyper/Lexer.hpp"
#include "Hyper/Logger.hpp"

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

			Lexer lexer(file, text);

			Token token = lexer.next_token();
			while (token.type != Token::Type::Eof)
			{
				Logger::file_info(
					file, "'{}' at {}:{}\n", token.value, token.line, token.column);
				token = lexer.next_token();
			}
		}

		return EXIT_SUCCESS;
	}
} // namespace Hyper
