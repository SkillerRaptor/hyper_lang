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

HYPER_DISABLE_WARNINGS()
#include <llvm/ADT/Triple.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetOptions.h>
HYPER_RESTORE_WARNINGS()

#include <filesystem>
#include <fstream>

namespace Hyper
{
	Compiler::Compiler(const Compiler::CreateInfo &create_info)
		: m_files(create_info.files)
		, m_target(create_info.target)
		, m_debug_scanner(create_info.debug_scanner)
		, m_debug_parser(create_info.debug_parser)
		, m_debug_generator(create_info.debug_generator)
		, m_debug_linker(create_info.debug_linker)
	{
		assert(!m_files.empty());
		assert(m_target != Target::None);
	}

	bool Compiler::compile() const
	{
		llvm::InitializeAllTargetInfos();
		llvm::InitializeAllTargets();
		llvm::InitializeAllTargetMCs();
		llvm::InitializeAllAsmParsers();
		llvm::InitializeAllAsmPrinters();

		const std::string target_triple = [&]()
		{
			switch (m_target)
			{
			case Target::Linux:
				return "x86_64-pc-linux-gnu";
			case Target::Windows:
				return "x86_64-pc-windows-msvc";
			default:
				HYPER_UNREACHABLE();
			}
		}();

		std::string error;
		const llvm::Target *target =
			llvm::TargetRegistry::lookupTarget(target_triple, error);
		if (target == nullptr)
		{
			Logger::error("failed to lookup target in registry: {}\n", error);
			return false;
		}

		const std::string cpu = "generic";
		const std::string features = "";
		const llvm::TargetOptions options = {};
		const llvm::Optional<llvm::Reloc::Model> relocation_model;
		llvm::TargetMachine *target_machine = target->createTargetMachine(
			target_triple, cpu, features, options, relocation_model);

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

			const std::string object_file = [&]()
			{
				switch (m_target)
				{
				case Target::Linux:
					return file + ".o";
				case Target::Windows:
					return file + ".obj";
				default:
					HYPER_UNREACHABLE();
				}
			}();

			if (!generator.build(object_file, target_machine))
			{
				Logger::file_error(file, "failed compiling to object file\n");
				return false;
			}

			object_files.push_back(object_file);

			Logger::file_info(
				file,
				"compiling hyper file {}{}{} [{}/{}]\n",
				Formatter::s_color_yellow,
				file,
				Formatter::s_color_reset,
				i + 1,
				file_count);
		}

		const Linker::CreateInfo linker_create_info = {
			.object_files = object_files,
			.target = m_target,
			.debug_mode = m_debug_linker,
		};
		Linker linker(linker_create_info);
		if (!linker.link())
		{
			return false;
		}

		return true;
	} // namespace Hyper
} // namespace Hyper
