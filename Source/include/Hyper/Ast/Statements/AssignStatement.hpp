/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Forward.hpp"
#include "Hyper/Ast/Statements/Statement.hpp"

#include <string>

namespace Hyper
{
	class AssignStatement final : public Statement
	{
	public:
		struct CreateInfo
		{
			std::string identifier;
			ExpressionPtr expression = nullptr;
		};

	public:
		explicit AssignStatement(CreateInfo create_info);

		void accept(Generator &generator) const override;
		void dump(
			std::string_view file,
			const std::string &prefix,
			bool is_self_last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;
		std::string class_description() const override;

		std::string identifier() const;
		const ExpressionPtr &expression() const;

	private:
		std::string m_identifier;
		ExpressionPtr m_expression = nullptr;
	};
} // namespace Hyper
