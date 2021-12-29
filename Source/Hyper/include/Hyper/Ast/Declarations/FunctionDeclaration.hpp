/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Declaration.hpp"

#include <memory>
#include <string>
#include <vector>

namespace Hyper
{
	class FunctionDeclaration : public Declaration
	{
	public:
		FunctionDeclaration(
			std::string name,
			std::vector<std::unique_ptr<Declaration>> arguments,
			std::string return_type,
			std::unique_ptr<Statement> body);

		void dump(std::string_view prefix, bool self_last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;

	private:
		std::string m_name;
		std::vector<std::unique_ptr<Declaration>> m_arguments = {};
		std::string m_return_type;
		std::unique_ptr<Statement> m_body = nullptr;
	};
} // namespace Hyper
