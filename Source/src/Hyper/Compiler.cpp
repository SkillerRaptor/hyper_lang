/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Compiler.hpp"

#include "Hyper/Ast/AstNode.hpp"
#include "Hyper/Diagnostics.hpp"
#include "Hyper/Generator.hpp"
#include "Hyper/Linker.hpp"
#include "Hyper/Logger.hpp"
#include "Hyper/Parser.hpp"
#include "Hyper/Scanner.hpp"

#include <filesystem>
#include <fstream>

namespace Hyper
{
	Compiler::Compiler(const Compiler::CreateInfo &create_info)
		: m_files(create_info.files)
		, m_debug_scanner(create_info.debug_scanner)
		, m_debug_parser(create_info.debug_parser)
		, m_debug_generator(create_info.debug_generator)
		, m_debug_linker(create_info.debug_linker)
	{
	}

	bool Compiler::compile() const
	{
		std::vector<std::string> object_files = {};
		const size_t file_count = m_files.size();
		for (size_t i = 0; i < file_count; ++i)
		{
			const std::string &file = m_files[i];
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

			const Diagnostics diagnostics(file, text);

			const Scanner::CreateInfo scanner_create_info = {
				.file = file,
				.text = text,
				.diagnostics = diagnostics,
				.debug_mode = m_debug_scanner,
			};
			Scanner scanner(scanner_create_info);

			const Parser::CreateInfo parser_create_info = {
				.file = file,
				.scanner = scanner,
				.diagnostics = diagnostics,
				.debug_mode = m_debug_parser,
			};
			Parser parser(parser_create_info);

			const AstPtr tree = parser.parse_tree();
			// TODO(SkillerRaptor): Adding semantic validator and type checking

			const Generator::CreateInfo generator_create_info = {
				.file = file,
				.debug_mode = m_debug_generator,
			};
			Generator generator(generator_create_info);
			tree->accept(generator);

			if (!generator.build())
			{
				return false;
			}

			object_files.push_back(file + ".o");

			Logger::file_info(
				file,
				"compiling hyper file {}{}{} [{}/{}]\n",
				Formatter::s_color_yellow,
				file,
				Formatter::s_color_reset,
				i + 1,
				file_count);
		}

		const Linker::ObjectFormat object_format =
#if defined(WIN32)
			Linker::ObjectFormat::Coff;
#else
			Linker::ObjectFormat::Elf;
#endif

		const Linker::CreateInfo linker_create_info = {
			.object_files = object_files,
			.object_format = object_format,
			.debug_mode = m_debug_linker,
		};
		Linker linker(linker_create_info);
		if (!linker.link())
		{
			return false;
		}

		return true;
	}
} // namespace Hyper
