/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/source_range.hpp"

#include <cstdint>
#include <string>

namespace hyper
{
	class DataType
	{
	public:
		enum class Kind : uint8_t
		{
			Invalid = 0,

			Bool,

			Int8,
			Int16,
			Int32,
			Int64,

			Uint8,
			Uint16,
			Uint32,
			Uint64,

			ISize,
			USize,

			Float32,
			Float64,

			String,
			Void,

			UserDefined,
		};

	public:
		DataType() = default;
		DataType(
			std::string value,
			Kind kind,
			bool array,
			bool pointer,
			SourceRange source_range);

		size_t line_number() const noexcept;
		size_t line_column() const noexcept;
		size_t length() const noexcept;

		Position start_position() const noexcept;
		Position end_position() const noexcept;

		std::string value() const;
		Kind kind() const noexcept;
		bool array() const noexcept;
		bool pointer() const noexcept;
		SourceRange source_range() const noexcept;

	private:
		std::string m_value;
		Kind m_kind = Kind::Invalid;
		bool m_array = false;
		bool m_pointer = false;
		SourceRange m_source_range = {};
	};
} // namespace hyper
