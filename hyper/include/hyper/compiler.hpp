/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/ast_node.hpp"
#include "hyper/diagnostics.hpp"
#include "hyper/symbol.hpp"

#include <optional>
#include <string>
#include <vector>

namespace hyper
{
	class Compiler
	{
	public:
		struct Arguments
		{
			bool freestanding = false;
			std::string_view linker_script = "";
			std::string_view output_file = "";
			std::vector<std::string_view> includes = {};
			std::vector<std::string_view> files = {};
		};

	public:
		explicit Compiler(const Arguments &arguments);

		int compile() const;

	private:
		void install_signals() const;

		std::optional<std::string> read_file(std::string_view file) const;
		AstNode *parse_file(
			const Diagnostics &diagnostics,
			std::string_view file,
			std::string_view text) const;

	private:
		bool m_freestanding = false;
		std::string_view m_linker_script = "";
		std::string_view m_output_file = "";
		std::vector<std::string_view> m_includes = {};
		std::vector<std::string_view> m_files = {};
	};
} // namespace hyper
