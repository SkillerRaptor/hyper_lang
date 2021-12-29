/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/AstNode.hpp"

#include "Hyper/Logger.hpp"

namespace Hyper
{
	void AstNode::dump() const
	{
		dump("", true);
	}

	void AstNode::dump_self(std::string_view prefix, bool self_last) const
	{
		const std::string new_prefix =
			Formatter::format("{}{}", prefix, self_last ? "`-" : "|-");
		Logger::debug("{}{}\n", new_prefix, class_name());
	}

	std::string_view AstNode::class_name() const noexcept
	{
		return "Declaration";
	}

	void AstNode::dump_node(
		const AstNode &node,
		std::string_view prefix,
		bool self_last,
		bool node_last) const
	{
		const std::string new_prefix =
			Formatter::format("{}{}", prefix, self_last ? "  " : "| ");
		node.dump(new_prefix, node_last);
	}
} // namespace Hyper
