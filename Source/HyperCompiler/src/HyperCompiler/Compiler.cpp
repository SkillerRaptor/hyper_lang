/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "HyperCompiler/Compiler.hpp"

#include "HyperCompiler/Lexer.hpp"
#include "HyperCompiler/Linker.hpp"
#include "HyperCompiler/LLVMGenerator.hpp"
#include "HyperCompiler/Parser.hpp"
#include "HyperCompiler/Utils/Utilities.hpp"

#include <chrono>
#include <fstream>
#include <thread>

namespace HyperCompiler
{
	BuildOptions Compiler::s_build_options{};

	void Compiler::compile(const BuildOptions& build_options)
	{
		s_build_options = build_options;

		std::chrono::time_point<std::chrono::system_clock> start_compiling = std::chrono::system_clock::now();

		if (s_build_options.jobs < 1)
		{
			s_build_options.jobs = 1;
		}

		if (s_build_options.source_files.size() < s_build_options.jobs)
		{
			s_build_options.jobs -= s_build_options.jobs - static_cast<unsigned int>(s_build_options.source_files.size());
		}

		std::vector<std::thread> job_pool;

		const size_t size = s_build_options.source_files.size() / s_build_options.jobs;
		for (size_t i = 0; i < s_build_options.jobs; ++i)
		{
			const long start = static_cast<long>(i * size);
			const long end = static_cast<long>((i + 1) * size);

			const std::vector<std::string> job_files(
				s_build_options.source_files.begin() + start,
				s_build_options.source_files.begin() + end);

			std::thread thread(Compiler::compiler_job, job_files);
			job_pool.push_back(std::move(thread));
		}

		for (std::thread& job : job_pool)
		{
			if (!job.joinable())
			{
				continue;
			}

			job.join();
		}

		std::vector<std::string> object_files;
		for (const std::string& source_file : s_build_options.source_files)
		{
			object_files.push_back(source_file + ".o");
		}
		
		Linker::link(s_build_options.output_file, object_files);
		Logger::info("Linking executable {}\n", s_build_options.output_file);

		std::chrono::time_point<std::chrono::system_clock> end_compiling = std::chrono::system_clock::now();
		std::chrono::duration<float> seconds = end_compiling - start_compiling;

		Logger::info("Compiled successfully in {}s\n", seconds.count());
	}

	void Compiler::compiler_job(const std::vector<std::string>& files)
	{
		Lexer lexer{};
		Parser parser{};
		LLVMGenerator llvm_generator{};

		for (const std::string& file : files)
		{
			std::ifstream file_stream(file);
			if (!file_stream.is_open())
			{
				Utils::fatal_exit("Failed to open input file '{}'\n", file);
				return;
			}

			std::string source;
			source.assign(
				std::istreambuf_iterator<char>(file_stream),
				std::istreambuf_iterator<char>());

			file_stream.close();

			lexer.initialize(file, source);
			lexer.next_token();

			parser.initialize(&lexer);

			llvm_generator.initialize(s_build_options, file);

			AstNode* ast_node = parser.parse();
			ast_node->dump(0);

			llvm_generator.generate_object(ast_node);

			delete ast_node;

			llvm_generator.shutdown();

			Logger::info("Building object {}.o\n", file);
		}
	}
} // namespace HyperCompiler
