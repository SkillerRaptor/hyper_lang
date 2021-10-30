/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Types.hpp"

namespace Hyper
{
	std::ostream &operator<<(std::ostream &ostream, const Type &type)
	{
		switch (type)
		{
		case Type::Int8:
			ostream << "Int8";
			break;
		case Type::Int16:
			ostream << "Int16";
			break;
		case Type::Int32:
			ostream << "Int32";
			break;
		case Type::Int64:
			ostream << "Int64";
			break;
		case Type::Uint8:
			ostream << "Uint8";
			break;
		case Type::Uint16:
			ostream << "Uint16";
			break;
		case Type::Uint32:
			ostream << "Uint32";
			break;
		case Type::Uint64:
			ostream << "Uint64";
			break;
		case Type::Void:
			ostream << "Void";
			break;
		default:
			break;
		}

		return ostream;
	}
} // namespace Hyper
