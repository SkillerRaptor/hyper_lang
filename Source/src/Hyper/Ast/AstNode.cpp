/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/AstNode.hpp"

namespace Hyper
{
	void AstNode::print_prefix(std::string_view prefix, bool is_last) const
	{
		Logger::raw(
			"{}{}{}{}{} ",
			prefix,
			is_last ? "`-" : "|-",
			s_color_blue,
			class_name(),
			s_color_reset);
	}

	void AstNode::print_next_node(
		const AstNode &node,
		std::string_view prefix,
		bool is_last,
		bool next_last) const
	{
		const std::string next_prefix =
			Formatter::format("{}{}", prefix, is_last ? "  " : "| ");
		node.dump(next_prefix, next_last);
	}
} // namespace Hyper
