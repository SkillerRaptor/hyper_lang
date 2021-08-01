/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "HyperCompiler/Ast/AstNode.hpp"

namespace HyperCompiler
{
	class Statement : public AstNode
	{
	public:
		virtual ~Statement() override = default;
		
		virtual std::string class_name() const override;
	};
} // namespace HyperCompiler
