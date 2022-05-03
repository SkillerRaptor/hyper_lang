/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper_utilities/non_null_unique_ptr.hpp"

#include <string>
#include <vector>

namespace hyper
{
	class AstNode;
	class Diagnostics;

	class Compiler
	{
	public:
		struct Options
		{
			bool freestanding = false;
			std::string_view linker_script = "";
			std::string_view output_directory = "";
			std::string_view output_executable = "";
			std::vector<std::string_view> include_directories = {};
			std::vector<std::string_view> source_files = {};
		};

	public:
		Compiler(const Options &options);

		int compile() const;

	private:
		void install_signal_handlers() const;

		AstNode *parse_file(
			const Diagnostics &diagnostics,
			std::string_view file,
			std::string_view text) const;

		void validate_ast(const Diagnostics &diagnostics, const AstNode *ast) const;

	private:
		bool m_freestanding = false;
		std::string_view m_linker_script = "";
		std::string_view m_output_directory = "";
		std::string_view m_output_executable = "";
		std::vector<std::string_view> m_include_directories = {};
		std::vector<std::string_view> m_source_files = {};
	};
} // namespace hyper
