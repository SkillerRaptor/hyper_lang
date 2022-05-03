/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper_utilities/assertions.hpp"

#include <concepts>
#include <optional>
#include <utility>

namespace hyper
{
	template <typename T, typename E>
	requires(!std::same_as<T, E>) class Expected
	{
	public:
		using ValueType = T;
		using ErrorType = E;

	public:
		Expected(const ValueType &value) noexcept
			: m_value(value)
		{
		}

		Expected(ValueType &&value) noexcept
			: m_value(std::move(value))
		{
		}

		Expected(const ErrorType &error) noexcept
			: m_error(error)
		{
		}

		Expected(ErrorType &&error) noexcept
			: m_error(std::move(error))
		{
		}

		ValueType &value()
		{
			ASSERT(m_value.has_value());
			return m_value.value();
		}

		const ValueType &value() const
		{
			ASSERT(m_value.has_value());
			return m_value.value();
		}

		ErrorType &error()
		{
			ASSERT(m_error.has_value());
			return m_error.value();
		}

		const ErrorType &error() const
		{
			ASSERT(m_error.has_value());
			return m_error.value();
		}

		bool is_error() const noexcept
		{
			return m_error.has_value();
		}

	private:
		std::optional<ValueType> m_value = std::nullopt;
		std::optional<ErrorType> m_error = std::nullopt;
	};

	template <typename E>
	class Expected<void, E>
	{
	public:
		using ErrorType = E;

	public:
		Expected(const ErrorType &error)
			: m_error(error)
		{
		}

		Expected(ErrorType &&error)
			: m_error(std::move(error))
		{
		}

		ErrorType &error()
		{
			ASSERT(m_error.has_value());
			return m_error.value();
		}

		const ErrorType &error() const
		{
			ASSERT(m_error.has_value());
			return m_error.value();
		}

		bool is_error() const noexcept
		{
			return m_error.has_value();
		}

	private:
		std::optional<ErrorType> m_error = std::nullopt;
	};
} // namespace hyper
