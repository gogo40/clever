/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/astvisitor.h"

namespace clever { namespace ast {

void Visitor::visit(NodeArray* node)
{
	std::vector<Node*> nodes = node->getNodes();
	std::vector<Node*>::const_iterator it = nodes.begin(), end = nodes.end();
	while (it != end) {
		(*it)->accept(*this);
		++it;
	}
}

void Visitor::visit(Block* node)
{
	Visitor::visit(static_cast<NodeArray*>(node));
}



void Visitor::visit(CriticalBlock* node)
{
	node->getBlock()->accept(*this);
}


void Visitor::visit(Assignment* node)
{
	node->getLhs()->accept(*this);
	if (node->getRhs()) {
		node->getRhs()->accept(*this);
	}
}

void Visitor::visit(VariableDecl* node)
{
	node->getIdent()->accept(*this);
	if (node->hasAssignment()) {
		node->getAssignment()->accept(*this);
	}
}

void Visitor::visit(Arithmetic* node)
{
	node->getLhs()->accept(*this);
	node->getRhs()->accept(*this);
}

void Visitor::visit(FunctionDecl* node)
{
	if (node->hasIdent()) {
		node->getIdent()->accept(*this);
	}

	if (node->hasArgs()) {
		node->getArgs()->accept(*this);
	}

	node->getBlock()->accept(*this);
}

void Visitor::visit(FunctionCall* node)
{
	node->getCallee()->accept(*this);

	if (node->hasArgs()) {
		node->getArgs()->accept(*this);
	}
}

void Visitor::visit(MethodCall* node)
{
	node->getCallee()->accept(*this);

	if (node->hasArgs()) {
		node->getArgs()->accept(*this);
	}
}

void Visitor::visit(While* node)
{
	node->getCondition()->accept(*this);
	node->getBlock()->accept(*this);
}

void Visitor::visit(For* node)
{
	node->getCondition()->accept(*this);
	node->getBlock()->accept(*this);
}

void Visitor::visit(If* node)
{
	std::vector<std::pair<Node*, Node*> > cond = node->getConditionals();
	std::vector<std::pair<Node*, Node*> >::iterator cur(cond.begin()), end(cond.end());

	while (cur != end) {
		(*cur).first->accept(*this);
		(*cur).second->accept(*this);
		++cur;
	}
	if (node->getElseNode()) {
		node->getElseNode()->accept(*this);
	}
}

void Visitor::visit(Return* node)
{
	if (node->hasValue()) {
		node->getValue()->accept(*this);
	}
}

void Visitor::visit(Logic* node)
{
	node->getLhs()->accept(*this);
	node->getRhs()->accept(*this);
}

void Visitor::visit(Bitwise* node)
{
	node->getLhs()->accept(*this);
	node->getRhs()->accept(*this);
}

void Visitor::visit(Boolean* node)
{
	node->getLhs()->accept(*this);
	if (node->getRhs()) {
		node->getRhs()->accept(*this);
	}
}

void Visitor::visit(Comparison* node)
{
	node->getLhs()->accept(*this);
	node->getRhs()->accept(*this);
}

void Visitor::visit(Import* node)
{
	if (node->hasModule()) {
		node->getModule()->accept(*this);
	}
}

void Visitor::visit(IncDec* node)
{
	node->getVar()->accept(*this);
}

void Visitor::visit(Instantiation* node)
{
	node->getType()->accept(*this);

	if (node->hasArgs()) {
		node->getArgs()->accept(*this);
	}
}

void Visitor::visit(Property* node)
{
	node->getCallee()->accept(*this);
}

void Visitor::visit(Try* node)
{
	node->getBlock()->accept(*this);

	node->getCatches()->accept(*this);

	if (node->hasFinally()) {
		node->getFinally()->accept(*this);
	}
}

void Visitor::visit(Catch* node) {
	node->getVar()->accept(*this);
	node->getBlock()->accept(*this);
}

void Visitor::visit(Throw* node)
{
	node->getExpr()->accept(*this);
}

void Visitor::visit(AttrDecl* node)
{
	node->getIdent()->accept(*this);

	if (node->hasValue()) {
		node->getValue()->accept(*this);
	}
}

void Visitor::visit(ClassDef* node)
{
	if (node->hasAttrs()) {
		node->getAttrs()->accept(*this);
	}
}

void Visitor::visit(Subscript* node)
{
	node->getVar()->accept(*this);
	node->getIndex()->accept(*this);
}

void Visitor::visit(Switch* node)
{
	node->getExpr()->accept(*this);

	std::vector<std::pair<Node*, Node*> >& vec = node->getCases();
	std::vector<std::pair<Node*, Node*> >::const_iterator it(vec.begin()),
		end(vec.end());

	for (; it != end; ++it) {
		if (it->first) {
			it->first->accept(*this);
		}
		it->second->accept(*this);
	}
}

}} // clever::ast
