/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Compiler.hpp"

#include "Hyper/Lexer.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>

namespace Hyper
{
	Compiler::Compiler(std::vector<const char *> files)
		: m_files(std::move(files))
	{
	}

	void Compiler::compile()
	{
		for (const char *file : m_files)
		{
			const std::ifstream file_stream(file);
			if (!file_stream.is_open())
			{
				std::cerr << "hyper: " << file << ": no such file or directory\n";
				continue;
			}

			const std::string file_text = [&file_stream]()
			{
				std::stringstream file_text_stream;
				file_text_stream << file_stream.rdbuf();
				return file_text_stream.str();
			}();

			Lexer lexer(file, file_text);

			Token token = lexer.next_token();
			while (token.type != Token::Type::Eof)
			{
				std::cout << "hyper: " << file
					<< ": " << token
					<< '\n';

				token = lexer.next_token();
			}
		}
	}
} // namespace Hyper
