/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#define NON_COPYABLE(class_name) \
	class_name(const class_name&) = delete;  \
	class_name& operator=(const class_name&) = delete

#define NON_MOVEABLE(class_name)    \
	class_name(class_name&&) noexcept = delete; \
	class_name& operator=(class_name&&) noexcept = delete

#define STRINGIFY_HELPER(x) #x
#define STRINGIFY(x) STRINGIFY_HELPER(x)
