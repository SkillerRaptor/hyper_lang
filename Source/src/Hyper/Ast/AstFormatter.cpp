/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/AstFormatter.hpp"

#include "Hyper/Ast/AstNode.hpp"

namespace Hyper
{
	std::string AstFormatter::format_prefix(
		const AstNode &node,
		std::string_view prefix,
		bool is_self_last)
	{
		const std::string extended_prefix =
			Formatter::format("{}{}", prefix, is_self_last ? "`-" : "|-");
		const std::string colored_name = Formatter::format(
			"{}{}{}",
			Formatter::s_color_magenta,
			node.class_name(),
			Formatter::s_color_reset);
		return Formatter::format(
			"{}{} {}\n", extended_prefix, colored_name, node.class_description());
	}

	std::string AstFormatter::format_next_prefix(
		std::string_view prefix,
		bool is_self_last)
	{
		return Formatter::format("{}{}", prefix, is_self_last ? "  " : "| ");
	}
} // namespace Hyper
