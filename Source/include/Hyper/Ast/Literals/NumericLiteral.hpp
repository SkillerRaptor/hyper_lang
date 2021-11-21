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
			std::string value;
		};

	public:
		explicit NumericLiteral(CreateInfo create_info);

		void accept(Generator &generator) const override;
		void dump(
			std::string_view file,
			const std::string &prefix,
			bool is_self_last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;
		std::string class_description() const override;

		std::string value() const;

	private:
		std::string m_value;
	};
} // namespace Hyper
