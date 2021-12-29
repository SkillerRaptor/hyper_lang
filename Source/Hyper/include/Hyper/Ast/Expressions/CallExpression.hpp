/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Expression.hpp"

#include <memory>
#include <string>
#include <vector>

namespace Hyper
{
	class CallExpression : public Expression
	{
	public:
		CallExpression(
			std::string name,
			std::vector<std::unique_ptr<Expression>> arguments);

		void dump(std::string_view prefix, bool self_last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;

	private:
		std::string m_name;
		std::vector<std::unique_ptr<Expression>> m_arguments = {};
	};
} // namespace Hyper
