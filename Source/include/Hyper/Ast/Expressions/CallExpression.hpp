/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Expressions/Expression.hpp"
#include "Hyper/Ast/Forward.hpp"

#include <string>

namespace Hyper
{
	class CallExpression final : public Expression
	{
	public:
		struct CreateInfo
		{
			std::string function;
			ExpressionList arguments = {};
		};

	public:
		explicit CallExpression(CreateInfo create_info);

		void accept(Generator &generator) const override;
		void dump(const std::string &prefix, bool is_self_last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;
		std::string class_description() const override;

		std::string function() const;
		const ExpressionList &arguments() const;

	private:
		std::string m_function;
		ExpressionList m_arguments = {};
	};
} // namespace Hyper
