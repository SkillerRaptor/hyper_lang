/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/AstNode.hpp"

#include "Hyper/Logger.hpp"

namespace Hyper
{
	AstNode::AstNode(SourceRange range)
		: m_range(range)
	{
	}

	void AstNode::dump() const
	{
		dump("", true);
	}

	SourceRange AstNode::range() const noexcept
	{
		return m_range;
	}

	void AstNode::dump_self(std::string_view prefix, bool self_last) const
	{
		const std::string new_prefix =
			Formatter::format("{}{}", prefix, self_last ? "`-" : "|-");
		Logger::debug("{}{}\n", new_prefix, class_name());
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
