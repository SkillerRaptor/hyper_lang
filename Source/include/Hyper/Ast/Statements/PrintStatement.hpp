/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/Statement.hpp"

#include <memory>

namespace Hyper
{
	class Expression;

	class PrintStatement final : public Statement
	{
	public:
		explicit PrintStatement(std::unique_ptr<Expression> expression);

		void accept(Generator &generator) const override;
		void dump(size_t indent) const override;
		
		const char *node_name() const noexcept override;
		Category node_category() const noexcept override;

		const std::unique_ptr<Expression> &expression() const;

	private:
		std::unique_ptr<Expression> m_expression = nullptr;
	};
} // namespace Hyper
