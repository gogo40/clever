/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_GUI_NCURSES_H
#define CLEVER_GUI_NCURSES_H

#include <iostream>
#include "core/cstring.h"
#include "core/value.h"
#include "core/type.h"
#include "modules/gui/ncurses/cncurses.h"

namespace clever { namespace modules { namespace gui {

class NCursesObject : public TypeObject {
public:
	NCursesObject(int m_sleep_time = 0, CNCurses* father = NULL, bool m_enable_colors = false,
				  int w = 0, int h = 0, int x = 0, int y = 0)
		: m_ncurses_obj(m_sleep_time, father->getWindow(), m_enable_colors, w, h, x, y) {}

	~NCursesObject() {}

private:
	CNCurses m_ncurses_obj;
	DISALLOW_COPY_AND_ASSIGN(NCursesObject);
};

class NCurses : public Type {
public:
	NCurses()
		: Type("NCurses") {}

	~NCurses() {}

	void init();

	virtual TypeObject* allocData(CLEVER_TYPE_CTOR_ARGS) const;

	void dump(TypeObject*, std::ostream&) const;

	CLEVER_METHOD(ctor);

private:
	DISALLOW_COPY_AND_ASSIGN(NCurses);
};

}}} // clever::modules::gui

#endif // CLEVER_GUI_NCURSES_H

