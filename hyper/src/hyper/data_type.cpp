/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/data_type.hpp"

namespace hyper
{
	DataType::DataType(
		std::string value,
		DataType::Kind kind,
		bool pointer,
		SourceRange source_range)
		: m_value(value)
		, m_kind(kind)
		, m_pointer(pointer)
		, m_source_range(source_range)
	{
	}

	size_t DataType::line_number() const noexcept
	{
		return m_source_range.start.line;
	}

	size_t DataType::line_column() const noexcept
	{
		return m_source_range.start.column;
	}

	size_t DataType::length() const noexcept
	{
		return m_value.length();
	}

	Position DataType::start_position() const noexcept
	{
		return m_source_range.start;
	}

	Position DataType::end_position() const noexcept
	{
		return m_source_range.end;
	}

	std::string DataType::value() const
	{
		return m_value;
	}

	DataType::Kind DataType::kind() const noexcept
	{
		return m_kind;
	}

	SourceRange DataType::source_range() const noexcept
	{
		return m_source_range;
	}
} // namespace hyper
