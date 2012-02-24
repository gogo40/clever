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
 */

#include <iostream>
#include "vm/vm.h"
#include "vm/opcode.h"
#include "compiler/compiler.h"
#include "compiler/scope.h"

namespace clever {

CallStack VM::s_call;
ValueVStack VM::s_arg_vars;
ValueVStack VM::s_arg_values;

static CLEVER_FORCE_INLINE const CallableValue*
	_get_op1_callable(const Opcode& opcode) {
	return static_cast<CallableValue*>(opcode.getOp1Value());
}

/**
 * Destroy the opcodes data
 */
VM::~VM() {
	OpcodeList::const_iterator it = m_opcodes.begin(),
		end(m_opcodes.end());

	while (it != end) {
		delete *it;
		++it;
	}
}

/**
 * Update the Value* ptr of variables in the function scope
 */
void VM::update_vars(Scope* scope, const FunctionArgs& fargs,
	const ValueVector* args) {
	ValueVector* vec = new ValueVector;
	ValueVector* vec_copy = new ValueVector;
	ValueVector* vec_curr = NULL;
	size_t i = 0;

	if (!s_arg_vars.empty()) {
		vec_curr = s_arg_values.top();
	}

	FunctionArgs::const_iterator it(fargs.begin()), end(fargs.end());

	vec->reserve(args->size());
	vec_copy->reserve(args->size());

	/* TODO: Find a better way to do this */
	while (it != end) {
		Value* val = scope->getValue(CSTRING((*it).first));
		Value* tmp = new Value;

		val->copy(args->at(i++));
		vec->push_back(val);

		tmp->copy(val);
		vec_copy->push_back(tmp);

		++it;
	}
	i = args->size();

	// Make the copy in the scopes level
	if (EXPECTED(scope->hasChildren())) {
		const ScopeVector& scopes = scope->getChildren();
		ScopeVector::const_iterator scope_it(scopes.begin()),
			scope_end(scopes.end());

		while (EXPECTED(scope_it != scope_end)) {
			const SymbolMap& symbols = (*scope_it)->getSymbols();
			SymbolMap::const_iterator sym(symbols.begin()),
				last_sym(symbols.end());

			while (EXPECTED(sym != last_sym)) {
				Symbol* symbol = sym->second;

				if (EXPECTED(symbol->isValue())) {
					Value* val = symbol->getValue();

					if (val->isCallable()) {
						continue;
					}

					Value* tmp = new Value;

					tmp->copy(val);

					if (vec_curr) {
						vec_curr->at(i++)->copy(tmp);
						tmp->addRef();
					}

					vec_copy->push_back(tmp);
					vec->push_back(val);
					val->initialize();
				}
				++sym;
			}
			++scope_it;
		}
	}

	s_arg_vars.push(vec);
	s_arg_values.push(vec_copy);
}

/**
 * Pop arguments onto the call stack
 */
void VM::pop_args(const Opcode* const op) {
	// Check if the function has arguments
	if (op->getOp2Value() == NULL) {
		return;
	}

	ValueVector* vec_copy = s_arg_values.top();

	for (size_t i = 0, j = vec_copy->size(); i < j; ++i) {
		delete vec_copy->at(i);
	}
	delete vec_copy;

	s_arg_values.pop();

	delete s_arg_vars.top();
	s_arg_vars.pop();

	if (!s_arg_vars.empty()) {
		restore_args();
	}
}

/**
 * Restore the parameter argument values from the previous stack frame
 */
void VM::restore_args() {
	ValueVector* vec = s_arg_vars.top();
	ValueVector* vec_copy = s_arg_values.top();

	for (size_t i = 0, j = vec->size(); i < j; ++i) {
		vec->at(i)->copy(vec_copy->at(i));
	}
}

/**
 * Execute the collected opcodes
 */
void VM::run() {
	long last_op = m_opcodes.size();

	for (long next_op = 0; next_op < last_op && next_op >= 0; ++next_op) {
		const Opcode& opcode = *m_opcodes[next_op];

		// opcode.dump();

		/* Invoke the opcode handler */
		opcode.getHandler()(opcode, next_op);
	}
}

/**
 * JMPZ - Jump if zero
 */
CLEVER_VM_HANDLER(VM::jmpz_handler) {
	const Value* const value = opcode.getOp1Value();
	Value* result = opcode.getResultValue();

	if (!value->getValueAsBool()) {
		if (result) {
			result->setBoolean(false);
		}
		CLEVER_VM_GOTO(opcode.getJmpAddr2());
	}

	if (result) {
		result->setBoolean(true);
	}
}

/**
 * JMPNZ - Jump if non-zero
 */
CLEVER_VM_HANDLER(VM::jmpnz_handler) {
	const Value* const value = opcode.getOp1Value();
	Value* result = opcode.getResultValue();

	if (value->getValueAsBool()) {
		if (result) {
			result->setBoolean(true);
		}
		CLEVER_VM_GOTO(opcode.getJmpAddr2());
	}

	if (result) {
		result->setBoolean(false);
	}
}

/**
 * JMP - Performs a jump to another code
 */
CLEVER_VM_HANDLER(VM::jmp_handler) {
	CLEVER_VM_GOTO(opcode.getJmpAddr1());
}

/**
 * Performs a function call
 */
CLEVER_VM_HANDLER(VM::fcall_handler) {
	const CallableValue* const func = _get_op1_callable(opcode);
	const ValueVector* const args = opcode.getOp2Vector();
	Value* result = opcode.getResultValue();

	// Check if it's an user function
	if (func->isNearCall()) {
		s_call.push(&opcode);

		if (args) {
			update_vars(func->getScope(), func->getFunction()->getArgs(), args);
		}

		func->call(next_op);
	} else {
		func->call(result, args);
	}
}

/**
 * Performs a method call (directly or via operators)
 */
CLEVER_VM_HANDLER(VM::mcall_handler) {
	const CallableValue* const var = _get_op1_callable(opcode);
	const ValueVector* const args = opcode.getOp2Vector();
	Value* result = opcode.getResultValue();

	var->call(result, args);
}

/**
 * Marks the end of a function
 */
CLEVER_VM_HANDLER(VM::end_func_handler) {
	const Opcode* const op = s_call.top();

	/**
	 * pop + restore arguments from stack
	 */
	pop_args(op);

	s_call.pop();

	/**
	 * Go to after the caller command
	 */
	CLEVER_VM_GOTO(op->getOpNum());
}

/**
 * Returns to the caller or terminates the execution
 */
CLEVER_VM_HANDLER(VM::return_handler) {
	if (!s_call.empty()) {
		const Value* const value = opcode.getOp1Value();
		const Opcode* call = s_call.top();

		if (value) {
			call->getResultValue()->copy(value);
		}
		// pop + restore arguments from stack
		pop_args(call);

		s_call.pop();

		// Go back to the caller
		CLEVER_VM_GOTO(call->getOpNum());
	} else {
		// Terminates the execution
		CLEVER_VM_GOTO(-2);
	}
}

/**
 * Add arithmetic operation
 */
CLEVER_VM_HANDLER(VM::plus_handler) {
	const CallableValue* const var = _get_op1_callable(opcode);
	const ValueVector* const args = opcode.getOp2Vector();
	Value* result = opcode.getResultValue();

	var->call(result, args);
}

/**
 * Minus arithmetic operation
 */
CLEVER_VM_HANDLER(VM::minus_handler) {
	const CallableValue* const var = _get_op1_callable(opcode);
	const ValueVector* const args = opcode.getOp2Vector();
	Value* result = opcode.getResultValue();

	var->call(result, args);
}

/**
 * Div arithmetic operation
 */
CLEVER_VM_HANDLER(VM::div_handler) {
	const CallableValue* const var = _get_op1_callable(opcode);
	const ValueVector* const args = opcode.getOp2Vector();
	Value* result = opcode.getResultValue();

	var->call(result, args);
}

/**
 * Mult arithmetic operation
 */
CLEVER_VM_HANDLER(VM::mult_handler) {
	const CallableValue* const var = _get_op1_callable(opcode);
	const ValueVector* const args = opcode.getOp2Vector();
	Value* result = opcode.getResultValue();

	var->call(result, args);
}

/**
 * Mod arithmetic operation
 */
CLEVER_VM_HANDLER(VM::mod_handler) {
	const CallableValue* const var = _get_op1_callable(opcode);
	const ValueVector* const args = opcode.getOp2Vector();
	Value* result = opcode.getResultValue();

	var->call(result, args);
}

/**
 * Inc operation (x++, ++x)
 */
CLEVER_VM_HANDLER(VM::inc_handler) {
	const CallableValue* const var = _get_op1_callable(opcode);
	const ValueVector* const args = opcode.getOp2Vector();
	Value* result = opcode.getResultValue();

	var->call(result, args);
}

/**
 * Dec arithmetic operation (x--, --x)
 */
CLEVER_VM_HANDLER(VM::dec_handler) {
	const CallableValue* const var = _get_op1_callable(opcode);
	const ValueVector* const args = opcode.getOp2Vector();
	Value* result = opcode.getResultValue();

	var->call(result, args);
}

/**
 * Xor bit-wise operation
 */
CLEVER_VM_HANDLER(VM::xor_handler) {
	const CallableValue* const var = _get_op1_callable(opcode);
	const ValueVector* const args = opcode.getOp2Vector();
	Value* result = opcode.getResultValue();

	var->call(result, args);
}

/**
 * OR bit-wise operation
 */
CLEVER_VM_HANDLER(VM::bw_or_handler) {
	const CallableValue* const var = _get_op1_callable(opcode);
	const ValueVector* const args = opcode.getOp2Vector();
	Value* result = opcode.getResultValue();

	var->call(result, args);
}

/**
 * AND bit-wise operation
 */
CLEVER_VM_HANDLER(VM::bw_and_handler) {
	const CallableValue* const var = _get_op1_callable(opcode);
	const ValueVector* const args = opcode.getOp2Vector();
	Value* result = opcode.getResultValue();

	var->call(result, args);
}

/**
 * NOT bit-wise operation
 */
CLEVER_VM_HANDLER(VM::bw_not_handler) {
	const CallableValue* const var = _get_op1_callable(opcode);
	const ValueVector* const args = opcode.getOp2Vector();
	Value* result = opcode.getResultValue();

	var->call(result, args);
}

/**
 * Greater logical operation (x > y)
 */
CLEVER_VM_HANDLER(VM::greater_handler) {
	const CallableValue* const var = _get_op1_callable(opcode);
	const ValueVector* const args = opcode.getOp2Vector();
	Value* result = opcode.getResultValue();

	var->call(result, args);
}

/**
 * Less logical operation (x < y)
 */
CLEVER_VM_HANDLER(VM::less_handler) {
	const CallableValue* const var = _get_op1_callable(opcode);
	const ValueVector* const args = opcode.getOp2Vector();
	Value* result = opcode.getResultValue();

	var->call(result, args);
}

/**
 * Greater or equal logical operation (x >= y)
 */
CLEVER_VM_HANDLER(VM::ge_handler) {
	const CallableValue* const var = _get_op1_callable(opcode);
	const ValueVector* const args = opcode.getOp2Vector();
	Value* result = opcode.getResultValue();

	var->call(result, args);
}

/**
 * Less or equal logical operation (x <= y)
 */
CLEVER_VM_HANDLER(VM::le_handler) {
	const CallableValue* const var = _get_op1_callable(opcode);
	const ValueVector* const args = opcode.getOp2Vector();
	Value* result = opcode.getResultValue();

	var->call(result, args);
}

/**
 * Equal logical operation (x == y)
 */
CLEVER_VM_HANDLER(VM::equal_handler) {
	const CallableValue* const var = _get_op1_callable(opcode);
	const ValueVector* const args = opcode.getOp2Vector();
	Value* result = opcode.getResultValue();

	var->call(result, args);
}

/**
 * Not equal logical operation (x != y)
 */
CLEVER_VM_HANDLER(VM::ne_handler) {
	const CallableValue* const var = _get_op1_callable(opcode);
	const ValueVector* const args = opcode.getOp2Vector();
	Value* result = opcode.getResultValue();

	var->call(result, args);
}

/**
 * Left shift logical operation (x << y)
 */
CLEVER_VM_HANDLER(VM::lshift_handler) {
	const CallableValue* const var = _get_op1_callable(opcode);
	const ValueVector* const args = opcode.getOp2Vector();
	Value* result = opcode.getResultValue();

	var->call(result, args);
}

/**
 * Right shift logical operation (x >> y)
 */
CLEVER_VM_HANDLER(VM::rshift_handler) {
	const CallableValue* const var = _get_op1_callable(opcode);
	const ValueVector* const args = opcode.getOp2Vector();
	Value* result = opcode.getResultValue();

	var->call(result, args);
}

/**
 * NOT logical operation (x >> y)
 */
CLEVER_VM_HANDLER(VM::not_handler) {
	const CallableValue* const var = _get_op1_callable(opcode);
	const ValueVector* const args = opcode.getOp2Vector();
	Value* result = opcode.getResultValue();

	var->call(result, args);
}

} // clever
