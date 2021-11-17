/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Expressions/Expression.hpp"

#include <string>

namespace Hyper
{
	class IdentifierExpression final : public Expression
	{
	public:
		struct CreateInfo
		{
			std::string identifier;
		};

	public:
		explicit IdentifierExpression(CreateInfo create_info);

		void accept(Generator &generator) const override;
		void dump(const std::string &prefix, bool is_self_last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;
		std::string class_description() const override;

		std::string identifier() const;

	private:
		std::string m_identifier;
	};
} // namespace Hyper
