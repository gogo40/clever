/*
 * Clever programming language
 * Copyright (c) 2011 Clever Team
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
 * $Id$
 */

#ifndef CLEVER_COMPILER_H
#define CLEVER_COMPILER_H

#include <stack>
#include "value.h"
#include "module.h"
#include "pkgmanager.h"
#include "vm.h"
#include "ssa.h"
#include "opcode.h"

namespace clever { namespace ast {

class Node;
class ASTVisitor;

}} // clever::ast

namespace clever {

class Compiler {
public:
	Compiler()
		: m_ast(NULL), m_visitor(NULL) { }

	~Compiler();

	/**
	 * Initializes compiler data
	 */
	void Init(ast::Node*) throw();
	/**
	 * Loads primitive data types
	 */
	void loadTypes() throw();
	/**
	 * Generates the intermediate representation
	 */
	void buildIR() throw();

	static void error(std::string) throw();
	static bool checkCompatibleTypes(Value*, Value*) throw();
	static ConstantValue* constantFolding(int, Value*, Value*) throw();
	/**
	 * Returns the opcode list
	 */
	OpcodeList& getOpcodes() throw();
	/**
	 * Import a package
	 */
	static void import(const CString* package) throw() {
		s_pkgmanager.loadPackage(package);
	}
	/**
	 * Import a package module
	 */
	static void import(const CString* package, const CString* module) throw() {
		s_pkgmanager.loadModule(package, module);
	}
	/**
	 * Returns the reference to static member function table
	 */
	static FunctionTable& get_functions() throw() {
		return s_func_table;
	}
	/**
	 * Checks if a function exists
	 */
	static bool functionExists(const std::string& name) throw() {
		return s_func_table.find(name) != s_func_table.end();
	}
	/**
	 * Returns the a Function pointer
	 */
	static FunctionPtr getFunction(const std::string& name) throw() {
		FunctionTable::const_iterator it = s_func_table.find(name);

		if (it != s_func_table.end()) {
			return it->second;
		} else {
			return NULL;
		}
	}
private:
	ast::Node* m_ast;
	ast::ASTVisitor* m_visitor;

	static PackageManager s_pkgmanager;
	static FunctionTable s_func_table;

	DISALLOW_COPY_AND_ASSIGN(Compiler);
};

} // clever

#endif // CLEVER_COMPILER_H
