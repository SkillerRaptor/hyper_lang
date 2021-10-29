/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/Statement.hpp"

namespace Hyper
{
	class AssignStatement final : public Statement
	{
	public:
		void accept(Generator &generator) const override;
		void dump(size_t indent) const override;

		const char *class_name() const noexcept override;
	};
} // namespace Hyper
