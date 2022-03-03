/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/declarations/attribute_declaration.hpp"

namespace hyper
{
	AttributeDeclaration::AttributeDeclaration(
		SourceRange source_range,
		std::string attribute,
		std::string value)
		: Declaration(source_range)
		, m_attribute(attribute)
		, m_value(value)
	{
	}

	std::string_view AttributeDeclaration::attribute() const
	{
		return m_attribute;
	}

	std::string_view AttributeDeclaration::value() const
	{
		return m_value;
	}
} // namespace hyper
