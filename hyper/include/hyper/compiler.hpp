/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/forward.hpp"

#include <string>
#include <vector>

namespace hyper
{
	class Compiler
	{
	public:
		explicit Compiler(const std::vector<std::string> &files);

		int compile() const;

	private:
		AstNodePtr parse_file(const std::string &file) const;

	private:
		std::vector<std::string> m_files = {};
	};
} // namespace hyper
