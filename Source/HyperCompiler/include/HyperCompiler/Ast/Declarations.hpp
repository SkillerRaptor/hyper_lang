/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "HyperCompiler/Ast/AstNode.hpp"

namespace HyperCompiler
{
	class Declaration : public AstNode
	{
	public:
		virtual ~Declaration() override = default;
		
		virtual std::string class_name() const override;
	};
} // namespace HyperCompiler
