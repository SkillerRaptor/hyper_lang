/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Compiler.hpp"

#include "Hyper/Ast/AstNode.hpp"
#include "Hyper/Generators/CGenerator.hpp"
#include "Hyper/Logger.hpp"
#include "Hyper/Parser.hpp"
#include "Hyper/Scanner.hpp"

#include <chrono>
#include <filesystem>
#include <fstream>

namespace Hyper
{
	Compiler::Compiler(std::vector<std::string> files)
		: m_files(std::move(files))
	{
	}

	bool Compiler::compile() const
	{
		for (const std::string &file : m_files)
		{
			if (!std::filesystem::exists(file))
			{
				Logger::file_error(file, "no such file or directory\n");
				return false;
			}

			if (std::filesystem::is_directory(file))
			{
				Logger::file_error(file, "unable to compile directory\n");
				return false;
			}

			const std::ifstream file_stream(file);
			if (!file_stream.is_open())
			{
				Logger::file_error(file, "failed to open file\n");
				return false;
			}

			const std::string text = [&file_stream]()
			{
				std::stringstream file_string;
				file_string << file_stream.rdbuf();
				return file_string.str();
			}();

			if (text.empty())
			{
				Logger::file_error(file, "unable to compile empty file\n");
				return false;
			}

			Scanner scanner(file, text);
			Parser parser(file, scanner);

			const std::unique_ptr<AstNode> tree = parser.parse_tree();
			tree->dump(0);

			std::unique_ptr<Generator> generator = std::make_unique<CGenerator>(file);
			tree->accept(*generator);
			generator->generate();

			Logger::file_info(file, "compiling hyper file\n");
		}

		return true;
	}
} // namespace Hyper
