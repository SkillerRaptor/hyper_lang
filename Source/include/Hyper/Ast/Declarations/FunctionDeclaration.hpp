/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Declarations/Declaration.hpp"
#include "Hyper/Ast/Expressions/Expression.hpp"
#include "Hyper/Type.hpp"

#include <vector>

namespace Hyper
{
	class FunctionDeclaration final : public Declaration
	{
	public:
		FunctionDeclaration(
			std::string name,
			std::vector<DeclarationPtr> arguments,
			Type return_type,
			StatementPtr body);

		void accept(Generator &generator) const override;
		void dump(const std::string &prefix, bool last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;

		std::string name() const;
		const std::vector<DeclarationPtr> &arguments() const;
		Type return_type() const noexcept;
		const StatementPtr &body() const;

	private:
		std::string m_name;
		std::vector<DeclarationPtr> m_arguments = {};
		Type m_return_type = {};
		StatementPtr m_body = nullptr;
	};
} // namespace Hyper
