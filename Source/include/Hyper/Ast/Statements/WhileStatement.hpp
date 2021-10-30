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

	class WhileStatement final : public Statement
	{
	public:
		WhileStatement(
			std::unique_ptr<Expression> condition,
			std::unique_ptr<Statement> body);

		void accept(Generator &generator) const override;
		void dump(size_t indent) const override;

		const char *class_name() const noexcept override;

		const std::unique_ptr<Expression>& condition() const;
		const std::unique_ptr<Statement>& body() const;

	private:
		std::unique_ptr<Expression> m_condition = nullptr;
		std::unique_ptr<Statement> m_body = nullptr;
	};
} // namespace Hyper
