/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Literals/Literal.hpp"

namespace Hyper
{
	class NumericLiteral final : public Literal
	{
	public:
		enum class Type : unsigned char
		{
			Signed = 0,
			Unsigned
		};

	public:
		NumericLiteral(Type type, uint64_t value);

		void accept(Generator &generator) const override;
		void dump(size_t indent) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;

		Type type() const noexcept;
		uint64_t value() const noexcept;

	private:
		Type m_type = {};
		uint64_t m_value = 0;
	};

	std::ostream &operator<<(
		std::ostream &ostream,
		const NumericLiteral::Type &type);
} // namespace Hyper
