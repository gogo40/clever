/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_ASTVISITOR_H
#define CLEVER_ASTVISITOR_H

namespace clever { namespace ast {

class Node;
class NodeArray;
class Block;
class Assignment;
class VariableDecl;
class Arithmetic;
class FunctionDecl;
class FunctionCall;
class While;
class If;
class IntLit;
class DoubleLit;
class StringLit;
class Ident;
class Return;

class Visitor {
public:
	Visitor() {}
	virtual ~Visitor() {}

	virtual void visit(Node* node) {}
	virtual void visit(NodeArray* node) {}
	virtual void visit(Block* node) {}
	virtual void visit(Assignment* node) {}
	virtual void visit(VariableDecl* node) {}
	virtual void visit(Arithmetic* node) {}
	virtual void visit(FunctionDecl* node) {}
	virtual void visit(FunctionCall* node) {}
	virtual void visit(While* node) {}
	virtual void visit(If* node) {}
	virtual void visit(IntLit* node) {}
	virtual void visit(DoubleLit* node) {}
	virtual void visit(StringLit* node) {}
	virtual void visit(Ident* node) {}
	virtual void visit(Return* node) {}
};

}} // clever::ast

#endif // CLEVER_ASTVISITOR_H