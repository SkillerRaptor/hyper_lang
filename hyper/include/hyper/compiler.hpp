/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/ast_node.hpp"
#include "hyper/diagnostics.hpp"
#include "hyper/symbol.hpp"

#include <string>
#include <vector>

namespace hyper
{
	class Compiler
	{
	private:
		struct CompilationUnit
		{
			AstNode *ast = nullptr;
			Diagnostics diagnostics = {};
			std::string file;
		};

	public:
		explicit Compiler(const std::vector<std::string> &files);

		int compile() const;

	private:
		CompilationUnit parse_file(const std::string &file) const;

	private:
		std::vector<std::string> m_files = {};
	};
} // namespace hyper
