/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Declaration.hpp"
#include "Hyper/Ast/Forward.hpp"

#include <string>

namespace Hyper
{
	class TranslationUnitDeclaration : public Declaration
	{
	public:
		TranslationUnitDeclaration(
			std::string translation_unit,
			DeclarationList declarations);

		void dump(std::string_view prefix, bool self_last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;

	private:
		std::string m_translation_unit;
		DeclarationList m_declarations = {};
	};
} // namespace Hyper
