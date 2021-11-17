/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/DataType.hpp"

#include <cassert>

namespace Hyper
{
	std::ostream &operator<<(std::ostream &ostream, const DataType &type)
	{
		assert(type != DataType::None);

		switch (type)
		{
		case DataType::None:
			ostream << "None";
			break;
		case DataType::Bool:
			ostream << "Bool";
			break;
		case DataType::Int8:
			ostream << "Int8";
			break;
		case DataType::Int16:
			ostream << "Int16";
			break;
		case DataType::Int32:
			ostream << "Int32";
			break;
		case DataType::Int64:
			ostream << "Int64";
			break;
		case DataType::Uint8:
			ostream << "Uint8";
			break;
		case DataType::Uint16:
			ostream << "Uint16";
			break;
		case DataType::Uint32:
			ostream << "Uint32";
			break;
		case DataType::Uint64:
			ostream << "Uint64";
			break;
		case DataType::ISize:
			ostream << "ISize";
			break;
		case DataType::USize:
			ostream << "USize";
			break;
		case DataType::Void:
			ostream << "Void";
			break;
		default:
			break;
		}

		return ostream;
	}
} // namespace Hyper
