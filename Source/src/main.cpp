/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Scanner.hpp"
#include "Hyper/Parser.hpp"
#include "Hyper/Ast/AstNode.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "hyper: no input files\n";
		return 1;
	}

	for (size_t i = 1; i < static_cast<size_t>(argc); ++i)
	{
		const char *file = argv[i];

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

		Hyper::Scanner scanner(file_text);
		scanner.scan_tokens();
		
		Hyper::Parser parser(scanner.tokens());
		const std::unique_ptr<Hyper::AstNode> ast_tree = parser.parse();
		ast_tree->dump(0);
	}

	return 0;
}
