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
	class NumericLiteral : public Literal
	{
	public:
		NumericLiteral(int64_t value);

		void generate() const override;
		void dump(size_t indent) const override;

		const char *class_name() const noexcept override;

	private:
		int64_t m_value = 0;
	};
} // namespace Hyper
