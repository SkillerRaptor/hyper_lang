/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Expression.hpp"
#include "Hyper/Ast/Forward.hpp"

#include <string>

namespace Hyper
{
	class CallExpression : public Expression
	{
	public:
		CallExpression(std::string name, ExpressionList arguments);

		void dump(std::string_view prefix, bool self_last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;

	private:
		std::string m_name;
		ExpressionList m_arguments = {};
	};
} // namespace Hyper
