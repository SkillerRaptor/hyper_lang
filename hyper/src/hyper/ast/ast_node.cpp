/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/ast_node.hpp"

namespace hyper
{
	AstNode::AstNode(SourceRange source_range)
		: m_source_range(source_range)
	{
	}

	Position AstNode::start_position() const noexcept
	{
		return m_source_range.start;
	}

	Position AstNode::end_position() const noexcept
	{
		return m_source_range.end;
	}

	SourceRange AstNode::source_range() const noexcept
	{
		return m_source_range;
	}
} // namespace hyper
