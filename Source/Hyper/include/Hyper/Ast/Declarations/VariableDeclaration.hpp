/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Declaration.hpp"

#include <memory>
#include <string>

namespace Hyper
{
	class Expression;

	class VariableDeclaration : public Declaration
	{
	public:
		enum class Mutable : uint8_t
		{
			No = 0,
			Yes
		};

	public:
		VariableDeclaration(
			std::string name,
			Mutable mutable_state,
			std::string type,
			std::unique_ptr<Expression> expression);

		void dump(std::string_view prefix, bool self_last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;

	private:
		std::string m_name;
		Mutable m_mutable = Mutable::No;
		std::string m_type;
		std::unique_ptr<Expression> m_expression = nullptr;
	};
} // namespace Hyper
