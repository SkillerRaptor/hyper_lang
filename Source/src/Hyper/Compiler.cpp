/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Compiler.hpp"

#include "Hyper/Lexer.hpp"
#include "Hyper/Logger.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>

namespace Hyper
{
	Compiler::Compiler(const size_t file_count, const char **files)
		: m_file_count(file_count)
		, m_files(files)
	{
	}

	void Compiler::compile()
	{
		for (size_t i = 1; i < m_file_count; ++i)
		{
			const std::string file = m_files[i];

			if (!std::filesystem::exists(file))
			{
				Logger::log(
					"hyper",
					Logger::Level::Error,
					"{}: no such file or directory\n",
					file);

				continue;
			}

			const std::ifstream file_stream(file.c_str());
			if (!file_stream.is_open())
			{
				Logger::log(
					"hyper",
					Logger::Level::Error,
					"{}: no such file or directory\n",
					file);

				continue;
			}

			std::stringstream file_text_stream;
			file_text_stream << file_stream.rdbuf();

			Lexer lexer(file, file_text_stream.str());

			Token token = lexer.scan_next_token();
			while (token.type != Token::Type::Eof)
			{
				Logger::log(
					"hyper",
					Logger::Level::Info,
					"{}: value - {}, type - {}\n",
					file,
					token.value,
					static_cast<uint8_t>(token.type));

				token = lexer.scan_next_token();
			}
		}
	}
} // namespace Hyper
