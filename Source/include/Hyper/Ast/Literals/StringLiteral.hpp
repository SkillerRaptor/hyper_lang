/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Literals/Literal.hpp"

#include <string>

namespace Hyper
{
	class StringLiteral final : public Literal
	{
	public:
		explicit StringLiteral(std::string value);

		void accept(Generator &generator) const override;
		void dump(size_t indent) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;

		std::string value() const noexcept;

	private:
		std::string m_value;
	};
} // namespace Hyper
