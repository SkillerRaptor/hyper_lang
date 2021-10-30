/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Declarations/Declaration.hpp"

#include "Hyper/Types.hpp"

namespace Hyper
{
	class VariableDeclaration final : public Declaration
	{
	public:
		VariableDeclaration(std::string identifier, Type type, bool mut);

		void accept(Generator &generator) const override;
		void dump(size_t indent) const override;

		const char *node_name() const noexcept override;
		Category node_category() const noexcept override;

		std::string identifier() const;
		Type type() const noexcept;
		bool mut() const noexcept;

	private:
		std::string m_identifier;
		Type m_type = Type::None;
		bool m_mut = false;
	};
} // namespace Hyper
