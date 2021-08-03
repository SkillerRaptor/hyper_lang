/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "HyperCompiler/Linker.hpp"

#include "HyperCompiler/Logger.hpp"

#include <llvm/ADT/ArrayRef.h>
#include <llvm/Support/raw_ostream.h>

namespace lld
{
	namespace coff
	{
		bool link(llvm::ArrayRef<const char*> args, bool canExitEarly, llvm::raw_ostream& stdoutOS, llvm::raw_ostream& stderrOS);
	}

	namespace mingw
	{
		bool link(llvm::ArrayRef<const char*> args, bool canExitEarly, llvm::raw_ostream& stdoutOS, llvm::raw_ostream& stderrOS);
	}

	namespace elf
	{
		bool link(llvm::ArrayRef<const char*> args, bool canExitEarly, llvm::raw_ostream& stdoutOS, llvm::raw_ostream& stderrOS);
	}

	namespace mach_o
	{
		bool link(llvm::ArrayRef<const char*> args, bool canExitEarly, llvm::raw_ostream& stdoutOS, llvm::raw_ostream& stderrOS);
	}

	namespace macho
	{
		bool link(llvm::ArrayRef<const char*> args, bool canExitEarly, llvm::raw_ostream& stdoutOS, llvm::raw_ostream& stderrOS);
	}

	namespace wasm
	{
		bool link(llvm::ArrayRef<const char*> args, bool canExitEarly, llvm::raw_ostream& stdoutOS, llvm::raw_ostream& stderrOS);
	}
} // namespace lld

namespace HyperCompiler
{
	void Linker::link(const std::string& output_file, const std::vector<std::string>& object_files)
	{
		std::vector<const char*> args(16 + object_files.size() + 1);

		args.push_back("-o");
		args.push_back(output_file.c_str());
		args.push_back("-m");
		args.push_back("elf_x86_64");
		args.push_back("/usr/lib/x86_64-linux-gnu/Scrt1.o");
		args.push_back("/usr/lib/gcc/x86_64-linux-gnu/9/crtbegin.o");

		for (const std::string& object_file : object_files)
		{
			args.push_back(object_file.c_str());
		}

		args.push_back("-lc");
		args.push_back("-lm");
		args.push_back("/usr/lib/x86_64-linux-gnu/crti.o");
		args.push_back("/usr/lib/gcc/x86_64-linux-gnu/9/crtend.o");
		args.push_back("-no-pie");
		args.push_back("/usr/lib/x86_64-linux-gnu/crtn.o");
		args.push_back("-L/usr/lib/x86_64-linux-gnu/");
		args.push_back("--dynamic-linker=/lib64/ld-linux-x86-64.so.2");
		args.push_back("-L/usr/lib/");
		args.push_back("-L/lib/");
		
		if (lld::elf::link(args, false, llvm::outs(), llvm::errs()))
		{
			Logger::info("elf linking successfully!\n");
			return;
		}

		if (lld::mach_o::link(args, false, llvm::outs(), llvm::errs()))
			return;

		if (lld::wasm::link(args, false, llvm::outs(), llvm::errs()))
			return;

		if (lld::coff::link(args, false, llvm::outs(), llvm::errs()))
			return;

		if (lld::mingw::link(args, false, llvm::outs(), llvm::errs()))
			return;
	}
} // namespace HyperCompiler
