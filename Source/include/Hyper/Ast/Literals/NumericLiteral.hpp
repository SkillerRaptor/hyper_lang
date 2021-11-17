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
		struct CreateInfo
		{
			uint64_t value = 0;
			bool is_signed = true;
		};

	public:
		explicit NumericLiteral(CreateInfo create_info);

		void accept(Generator &generator) const override;
		void dump(const std::string &prefix, bool is_self_last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;
		std::string class_description() const override;

		uint64_t value() const noexcept;
		bool is_signed() const noexcept;

	private:
		uint64_t m_value = 0;
		bool m_is_signed = true;
	};
} // namespace Hyper
