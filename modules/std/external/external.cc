/**
 * Clever programming language
 * Copyright (c) 2011-2012 Clever Team
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */


#include <iostream>
#include <cmath>
#include <cstdlib>
#include "modules/std/external/external.h"
#include "types/nativetypes.h"

namespace clever { namespace packages { namespace std {

namespace external {

/**
 * call_ext_func(..., str function_name, str library_name)
 * Returns call an external function
 */
static CLEVER_FUNCTION(call_ext_func) {
	::std::cout<<"here"<<::std::endl;
	
	size_t size = CLEVER_NUM_ARGS(); 
	::std::cout<<size<<::std::endl;
	
	
	CLEVER_RETURN_STR(CLEVER_ARG(1)->getName());
}

}

/**
 * Load module data
 */
void External::init() {
	::std::cout<<"here!"<<::std::endl;
	
	addFunction(new Function("call_ext_func",	&CLEVER_NS_FNAME(external, call_ext_func), CLEVER_STR))
		->setVariadic()
		->setMinNumArgs(2);

}


}}} // clever::packages::std
