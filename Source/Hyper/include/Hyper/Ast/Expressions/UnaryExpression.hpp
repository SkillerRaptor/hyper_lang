/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Expression.hpp"
#include "Hyper/Ast/Forward.hpp"

namespace Hyper
{
	class UnaryExpression : public Expression
	{
	public:
		enum class Kind
		{
			Invalid = 0,

			Not,
			Negative,
			Inverse,

			PreIncrement,
			PreDecrement,

			PostIncrement,
			PostDecrement,
		};

	public:
		UnaryExpression(Kind kind, ExpressionPtr expression);

		void dump(std::string_view prefix, bool self_last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;

	private:
		Kind m_kind = Kind::Invalid;
		ExpressionPtr m_expression = nullptr;
	};
} // namespace Hyper
