/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/AstNode.hpp"

#include "Hyper/Ast/AstFormatter.hpp"

namespace Hyper
{
	void AstNode::dump_tree() const
	{
		dump("", true);
	}

	void AstNode::dump_next_node(
		const AstNode &node,
		const std::string &prefix,
		bool is_self_last,
		bool is_node_last) const
	{
		const std::string next_prefix =
			AstFormatter::format_next_prefix(prefix, is_self_last);
		node.dump(next_prefix, is_node_last);
	}
} // namespace Hyper
