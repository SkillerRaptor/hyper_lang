/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/Statement.hpp"

#include <memory>
#include <string>

namespace Hyper
{
	class Expression;

	class AssignStatement final : public Statement
	{
	public:
		AssignStatement(
			std::string identifier,
			std::unique_ptr<Expression> expression);

		void accept(Generator &generator) const override;
		void dump(size_t indent) const override;

		const char *class_name() const noexcept override;

		std::string identifier() const;
		const std::unique_ptr<Expression> &expression() const;

	private:
		std::string m_identifier;
		std::unique_ptr<Expression> m_expression = nullptr;
	};
} // namespace Hyper
