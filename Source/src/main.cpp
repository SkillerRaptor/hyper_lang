/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Scanner.hpp"
#include "Hyper/Parser.hpp"
#include "Hyper/Ast/AstNode.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "hyper: no input files\n";
		return 1;
	}

	// TODO(SkillerRaptor): Adding Options Parser

	for (size_t i = 1; i < static_cast<size_t>(argc); ++i)
	{
		const char *path = argv[i];
		if (!std::filesystem::exists(path))
		{
			std::cerr << "hyper: " << path << ": no such file or directory\n";
			continue;
		}

		if (std::filesystem::is_directory(path))
		{
			std::cerr << "hyper: " << path << ": can not compile folder\n";
			continue;
		}

		const std::ifstream file(path);
		if (!file.is_open())
		{
			std::cerr << "hyper: " << path << ": failed to open file\n";
			continue;
		}

		const std::string text = [&file]()
		{
			std::stringstream file_string;
			file_string << file.rdbuf();
			return file_string.str();
		}();

		Hyper::Scanner scanner(text);
		scanner.scan_tokens();

		Hyper::Parser parser(scanner.tokens());

		const Hyper::AstNode *ast = parser.parse_tree();
		ast->dump(0);
		// TODO(SkillerRaptor): Using ast to generate code
	}

	return 0;
}
