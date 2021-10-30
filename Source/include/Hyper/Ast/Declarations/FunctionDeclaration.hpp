/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Declarations/Declaration.hpp"

#include "Hyper/Types.hpp"

#include <memory>

namespace Hyper
{
	class FunctionDeclaration final : public Declaration
	{
	public:
		FunctionDeclaration(
			std::string identifier,
			Type return_type,
			std::unique_ptr<Statement> body);

		void accept(Generator &generator) const override;
		void dump(size_t indent) const override;

		const char *node_name() const noexcept override;
		Category node_category() const noexcept override;

		std::string identifier() const;
		Type return_type() const noexcept;
		const std::unique_ptr<Statement>& body() const;

	private:
		std::string m_identifier;
		Type m_return_type = Type::None;
		std::unique_ptr<Statement> m_body = nullptr;
	};
} // namespace Hyper
