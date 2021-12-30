/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Declaration.hpp"
#include "Hyper/Ast/Forward.hpp"
#include "Hyper/Type.hpp"

#include <string>

namespace Hyper
{
	class FunctionDeclaration : public Declaration
	{
	public:
		FunctionDeclaration(
			std::string identifier,
			DeclarationList arguments,
			Type return_type,
			StatementPtr body);

		void dump(std::string_view prefix, bool self_last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;

	private:
		std::string m_identifier;
		DeclarationList m_arguments = {};
		Type m_return_type = {};
		StatementPtr m_body = nullptr;
	};
} // namespace Hyper
