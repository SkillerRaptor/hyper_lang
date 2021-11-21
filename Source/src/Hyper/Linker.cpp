/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Linker.hpp"

#include "Hyper/Logger.hpp"
#include "Hyper/Prerequisites.hpp"

HYPER_DISABLE_WARNINGS()
#include <llvm/ADT/ArrayRef.h>
#include <llvm/Support/raw_ostream.h>
HYPER_RESTORE_WARNINGS()

namespace lld
{
	namespace coff
	{
		bool link(
			llvm::ArrayRef<const char *> args,
			bool canExitEarly,
			llvm::raw_ostream &stdoutOS,
			llvm::raw_ostream &stderrOS);
	} // namespace coff

	namespace mingw
	{
		bool link(
			llvm::ArrayRef<const char *> args,
			bool canExitEarly,
			llvm::raw_ostream &stdoutOS,
			llvm::raw_ostream &stderrOS);
	} // namespace mingw

	namespace elf
	{
		bool link(
			llvm::ArrayRef<const char *> args,
			bool canExitEarly,
			llvm::raw_ostream &stdoutOS,
			llvm::raw_ostream &stderrOS);
	} // namespace elf

	namespace wasm
	{
		bool link(
			llvm::ArrayRef<const char *> args,
			bool canExitEarly,
			llvm::raw_ostream &stdoutOS,
			llvm::raw_ostream &stderrOS);
	} // namespace wasm
} // namespace lld

namespace Hyper
{
	Linker::Linker(const Linker::CreateInfo &create_info)
		: m_object_files(create_info.object_files)
		, m_object_format(create_info.object_format)
		, m_debug_mode(create_info.debug_mode)
	{
	}

	bool Linker::link() const
	{
		if (m_debug_mode)
		{
			std::string object_files;
			for (const std::string &object_file : m_object_files)
			{
				object_files += object_file;
				object_files += ' ';
			}

			Logger::info("Linking {}\n", object_files);
		}

		std::vector<const char *> args = {};

#if defined(WIN32)
		args.emplace_back("/out:a.exe");
		args.emplace_back(
			R"(-libpath:D:\Programming\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.30.30705\lib\x64)");
		args.emplace_back(
			R"(-libpath:D:\Programming\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.30.30705\atlmfc\x64)");
		args.emplace_back(
			R"(-libpath:D:\Windows Kits\10\Lib\10.0.19041.0\ucrt\x64)");
		args.emplace_back(R"(-libpath:D:\Windows Kits\10\Lib\10.0.19041.0\um\x64)");

		args.emplace_back("-defaultlib:libcmt");
		args.emplace_back("-nologo");
#else
		args.emplace_back("-o");
		args.emplace_back("a.out");

		args.emplace_back("-m");
		args.emplace_back("elf_x86_64");

		args.emplace_back("/usr/lib/x86_64-linux-gnu/Scrt1.o");
		args.emplace_back("/usr/lib/gcc/x86_64-linux-gnu/10/crtbegin.o");
#endif

		for (const std::string &object_file : m_object_files)
		{
			args.emplace_back(object_file.c_str());
		}

#if !defined(WIN32)
		args.emplace_back("-lc");
		args.emplace_back("-lm");
		args.emplace_back("/usr/lib/x86_64-linux-gnu/crti.o");
		args.emplace_back("/usr/lib/gcc/x86_64-linux-gnu/10/crtend.o");
		args.emplace_back("-no-pie");
		args.emplace_back("/usr/lib/x86_64-linux-gnu/crtn.o");
		args.emplace_back("-L/usr/lib/x86_64-linux-gnu/");
		args.emplace_back("--dynamic-linker=/lib64/ld-linux-x86-64.so.2");
#endif

		std::string output_string;
		std::string output_error_string;
		llvm::raw_string_ostream output(output_string);
		llvm::raw_string_ostream output_error(output_error_string);
		bool successful = [&]()
		{
			switch (m_object_format)
			{
			case ObjectFormat::Coff:
				return lld::coff::link(args, false, output, output_error);
			case ObjectFormat::Elf:
				return lld::elf::link(args, false, output, output_error);
			case ObjectFormat::Mingw:
				return lld::mingw::link(args, false, output, output_error);
			case ObjectFormat::Wasm:
				return lld::wasm::link(args, false, output, output_error);
			default:
				HYPER_UNREACHABLE();
			}
		}();

		if (!successful)
		{
			Logger::error("lld::link failed: {}\n", output_error_string);
		}

		return successful;
	}
} // namespace Hyper
