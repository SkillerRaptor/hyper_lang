/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Literal.hpp"

#include <string>

namespace Hyper
{
	class StringLiteral : public Literal
	{
	public:
		explicit StringLiteral(std::string string);

		void dump(std::string_view prefix, bool self_last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;

	private:
		std::string m_string;
	};
} // namespace Hyper
