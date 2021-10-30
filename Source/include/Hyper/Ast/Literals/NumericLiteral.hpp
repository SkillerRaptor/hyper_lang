/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Literals/Literal.hpp"

#include <cstdint>

namespace Hyper
{
	class NumericLiteral final : public Literal
	{
	public:
		NumericLiteral(int64_t value);

		void accept(Generator &generator) const override;
		void dump(size_t indent) const override;

		const char *node_name() const noexcept override;
		Category node_category() const noexcept override;

		int64_t value() const noexcept;

	private:
		int64_t m_value = 0;
	};
} // namespace Hyper
