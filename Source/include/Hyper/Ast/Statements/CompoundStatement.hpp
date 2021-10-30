/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/Statement.hpp"

#include <memory>

namespace Hyper
{
	class CompoundStatement final : public Statement
	{
	public:
		CompoundStatement(
			std::unique_ptr<Statement> left,
			std::unique_ptr<Statement> right);

		void accept(Generator &generator) const override;
		void dump(size_t indent) const override;
		
		const char *node_name() const noexcept override;
		Category node_category() const noexcept override;

		const std::unique_ptr<Statement> &left() const;
		const std::unique_ptr<Statement> &right() const;

	private:
		std::unique_ptr<Statement> m_left = nullptr;
		std::unique_ptr<Statement> m_right = nullptr;
	};
} // namespace Hyper
