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
	class TranslationUnitDeclaration : public Declaration
	{
	public:
		TranslationUnitDeclaration(
			std::string file,
			std::vector<std::unique_ptr<Declaration>> declarations);

		void dump(std::string_view prefix, bool self_last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;

	private:
		std::string m_file;
		std::vector<std::unique_ptr<Declaration>> m_declarations = {};
	};
} // namespace Hyper
