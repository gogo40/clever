/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <string>
#include <sstream>
#include "types/str.h"

namespace clever {

CLEVER_TYPE_OPERATOR(StrType::add)
{
	if (EXPECTED(rhs->getType() == this)) {
		// TODO(Felipe): Do not require CString everywhere (because it stores the
		// data in an string table)
		result->setStr(CSTRING(*lhs->getStr() + *rhs->getStr()));
	}
}

CLEVER_TYPE_OPERATOR(StrType::sub)
{
}

CLEVER_TYPE_OPERATOR(StrType::mul)
{
	if (rhs->getType() == CLEVER_INT_TYPE) {
		std::ostringstream os;

		for (long i = 0, j = rhs->getInt(); i < j; ++i) {
			os << *lhs->getStr();
		}

		result->setStr(CSTRING(os.str()));
	}
}

CLEVER_TYPE_OPERATOR(StrType::div)
{
}

CLEVER_TYPE_OPERATOR(StrType::mod)
{
}


CLEVER_TYPE_OPERATOR(StrType::greater)
{
	if (EXPECTED(rhs->getType() == this)) {
		result->setInt(lhs->getStr() > rhs->getStr());
	}
}

CLEVER_TYPE_OPERATOR(StrType::greater_equal)
{
	if (EXPECTED(rhs->getType() == this)) {
		result->setInt(lhs->getStr() >= rhs->getStr());
	}
}

CLEVER_TYPE_OPERATOR(StrType::less)
{
	if (EXPECTED(rhs->getType() == this)) {
		result->setInt(lhs->getStr() < rhs->getStr());
	}
}

CLEVER_TYPE_OPERATOR(StrType::less_equal)
{
	if (EXPECTED(rhs->getType() == this)) {
		result->setInt(lhs->getStr() <= rhs->getStr());
	}
}

CLEVER_TYPE_OPERATOR(StrType::equal)
{
	if (EXPECTED(rhs->getType() == this)) {
		result->setInt(lhs->getStr() == rhs->getStr());
	}
}

CLEVER_TYPE_OPERATOR(StrType::not_equal)
{
	if (EXPECTED(rhs->getType() == this)) {
		result->setInt(lhs->getStr() != rhs->getStr());
	}
}

} // clever
