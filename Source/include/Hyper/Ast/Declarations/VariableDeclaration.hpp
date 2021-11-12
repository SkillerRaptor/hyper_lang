/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Declarations/Declaration.hpp"
#include "Hyper/Type.hpp"

namespace Hyper
{
	class VariableDeclaration final : public Declaration
	{
	public:
		enum class Immutable
		{
			No = 0,
			Yes
		};

	public:
		VariableDeclaration(std::string name, Type type, Immutable immutable);

		void accept(Generator &generator) const override;
		void dump(size_t indent) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;

		std::string name() const;
		Type type() const noexcept;
		Immutable immutable() const noexcept;

	private:
		std::string m_name;
		Type m_type = {};
		Immutable m_immutable = Immutable::Yes;
	};

	std::ostream &operator<<(
		std::ostream &ostream,
		const VariableDeclaration::Immutable &immutable);
} // namespace Hyper
