/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper_utilities/assertions.hpp"

#include <algorithm>
#include <utility>

namespace hyper
{
	template <typename T>
	class NonNullUniquePtr
	{
	public:
		using ValueType = T;

	public:
		NonNullUniquePtr(T &ptr)
			: m_ptr(&ptr)
		{
		}

		NonNullUniquePtr(const NonNullUniquePtr &) = delete;
		NonNullUniquePtr &operator=(const NonNullUniquePtr &) = delete;

		NonNullUniquePtr(NonNullUniquePtr &&other)
			: m_ptr(other.keak_ptr())
		{
			ASSERT(m_ptr != nullptr);
		}

		NonNullUniquePtr &operator=(NonNullUniquePtr &&other)
		{
			NonNullUniquePtr ptr(std::move(other));
			swap(ptr);
			return *this;
		}

		~NonNullUniquePtr()
		{
			if (!m_ptr)
			{
				return;
			}

			delete m_ptr;
			m_ptr = nullptr;
		}

		void swap(NonNullUniquePtr &other)
		{
			std::swap(m_ptr, other.m_ptr);
		}

		T *leak_ptr() noexcept
		{
			return std::exchange(m_ptr, nullptr);
		}

		T *ptr()
		{
			ASSERT(m_ptr != nullptr);
			return m_ptr;
		}

		const T *ptr() const
		{
			ASSERT(m_ptr != nullptr);
			return m_ptr;
		}

		T *operator->()
		{
			ASSERT(m_ptr != nullptr);
			return m_ptr;
		}

		const T *operator->() const
		{
			ASSERT(m_ptr != nullptr);
			return m_ptr;
		}

		T &operator*()
		{
			ASSERT(m_ptr != nullptr);
			return m_ptr;
		}

		const T &operator*() const
		{
			ASSERT(m_ptr != nullptr);
			return m_ptr;
		}

		operator const T *() const
		{
			ASSERT(m_ptr != nullptr);
			return m_ptr;
		}

		operator T *()
		{
			ASSERT(m_ptr != nullptr);
			return m_ptr;
		}

		operator bool() const = delete;
		bool operator!() const = delete;

	private:
		T *m_ptr = nullptr;
	};

	template <class T, class... Args>
	NonNullUniquePtr<T> make_non_null_unqiue(Args &&...args)
	{
		return NonNullUniquePtr<T>(*new T{ std::forward<Args>(args)... });
	}
} // namespace hyper
