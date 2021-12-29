/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Statement.hpp"

#include <memory>
#include <string>

namespace Hyper
{
	class Expression;

	class CompoundAssignStatement : public Statement
	{
	public:
		enum class Operation : uint8_t
		{
			Invalid = 0,

			Addition,
			Subtraction,
			Multiplication,
			Division,
			Modulo,

			BitwiseAnd,
			BitwiseOr,
			BitwiseXor,

			LeftShift,
			RightShift
		};

	public:
		CompoundAssignStatement(
			std::string name,
			Operation operation,
			std::unique_ptr<Expression> expression);

		void dump(std::string_view prefix, bool self_last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;

	private:
		std::string m_name;
		Operation m_operation = Operation::Invalid;
		std::unique_ptr<Expression> m_expression = nullptr;
	};
} // namespace Hyper
