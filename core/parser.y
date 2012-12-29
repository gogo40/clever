%skeleton "lalr1.cc"
%require "2.4.1"
%defines
%define namespace "clever"
%define parser_class_name "Parser"

%code requires {
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

#include <stack>
#include "core/scanner.h"
#include "core/cstring.h"
#include "core/compiler.h"

namespace clever {
class Driver;
class Compiler;
class Value;

} // clever
}

%union {
	Node node;
	ArgDeclList* arg_decl_list;
	ArgCallList* arg_call_list;
}

%type <node> IDENT NUM_INTEGER NUM_DOUBLE STR
%type <node> r_value math_expr func_call inc_dec
%type <arg_decl_list> arg_decl_list
%type <arg_call_list> non_empty_arg_list arg_list

// The parsing context.
%parse-param { Driver& driver }
%parse-param { ScannerState& state }
%parse-param { Compiler& c }
%lex-param   { Driver& driver }
%lex-param   { ScannerState& state }

%locations
%initial-action {
@$.begin.filename = @$.end.filename = driver.getFile();
};

%debug
%error-verbose

%code {
#include "core/driver.h"
}

%token END  0        "end of file"
%token VAR           "var"
%token EXIT          "exit"
%token TYPE          "type specification"
%token IDENT         "identifier"
%token NUM_INTEGER   "number"
%token NUM_DOUBLE    "float-number"
%token STR           "string"
%token FOR           "for"
%token WHILE         "while"
%token IF            "if"
%token ELSE          "else"
%token ELSEIF        "else if"
%token LESS_EQUAL    "<="
%token GREATER_EQUAL ">="
%token LESS          "<"
%token GREATER       ">"
%token RSHIFT        ">>"
%token RSHIFT_EQUAL  ">>="
%token LSHIFT        "<<"
%token LSHIFT_EQUAL  "<<="
%token BREAK         "break"
%token EQUAL         "=="
%token NOT_EQUAL     "!="
%token IMPORT        "import"
%token PLUS_EQUAL    "+="
%token MULT_EQUAL    "*="
%token DIV_EQUAL     "/="
%token MINUS_EQUAL   "-="
%token MOD_EQUAL     "%="
%token BOOLEAN_OR    "||"
%token LOGICAL_OR    "or"
%token BOOLEAN_AND   "&&"
%token LOGICAL_AND   "and"
%token BW_AND_EQUAL  "&="
%token BW_OR_EQUAL   "|="
%token BW_XOR_EQUAL  "^="
%token RETURN        "return"
%token TRUE          "true"
%token FALSE         "false"
%token CONST         "const"
%token PRINT         "print"
%token FUNC          "function"
%token THREAD        "thread"
%token INCREMENT     "++"
%token DECREMENT     "--"

%left ',';
%left LOGICAL_OR;
%left LOGICAL_AND;
%right '=' PLUS_EQUAL MINUS_EQUAL DIV_EQUAL MULT_EQUAL MOD_EQUAL BW_OR_EQUAL XOR_EQUAL BW_AND_EQUAL  RSHIFT_EQUAL LSHIFT_EQUAL;
%left ':';
%left BOOLEAN_OR;
%left BOOLEAN_AND;
%left '|';
%left '^';
%left '&';
%nonassoc EQUAL NOT_EQUAL;
%nonassoc LESS LESS_EQUAL GREATER GREATER_EQUAL;
%left LSHIFT RSHIFT;
%left '-' '+' '.';
%left '*' '/' '%';
%right '!';
%right '~' INCREMENT DECREMENT COPY DEEPCOPY;
%right '[' '{';
%left ELSEIF;
%left ELSE;
%left UMINUS;

%%

%start top_statements;

top_statements:
		{ c.init(); } statement_list { c.end(); }
;

statement_list:
		/* empty */
	|	non_empty_statement_list statement_list
;

import_stmt:
		IMPORT IDENT '.' '*'              { c.importStmt($2); }
	|	IMPORT IDENT '.' IDENT '.' '*'    { c.importStmt($2, $4); }
;

non_empty_statement_list:
		'{' { c.newScope(); } non_empty_statement_list { c.endScope(); } '}'
	|	import_stmt ';'
	|	var_declaration ';'
	|	assignment ';'
	|	func_declaration
	|	func_call ';'
    |   thread_call ';'
	|	prototype ';'
	|	return_stmt ';'
	|	if_cond
	|	while_loop
	|	inc_dec ';'
;

inc_dec:
		IDENT INCREMENT { c.incDec(OP_POS_INC, $1, $$, yyloc); }
	|	INCREMENT IDENT { c.incDec(OP_PRE_INC, $2, $$, yyloc);  }
	|	IDENT DECREMENT { c.incDec(OP_POS_DEC, $1, $$, yyloc); }
	|	DECREMENT IDENT { c.incDec(OP_PRE_DEC, $2, $$, yyloc);  }
;

while_loop:
		WHILE '(' r_value ')' { c.whileLoop($3, yyloc); } '{' statement_list '}' { c.endWhileLoop(); }
;

elseif_cond:
		/* empty */
	|	elseif_cond ELSEIF '(' r_value ')' '{' statement_list '}'
;

else_cond:
		/* empty */
	|	ELSE '{' statement_list '}'

if_cond:
		IF '(' r_value ')' '{' statement_list '}' elseif_cond else_cond
;

return_stmt:
		RETURN r_value        { c.retStmt(&$2, yyloc);  }
	|	RETURN                { c.retStmt(NULL, yyloc); }
;

prototype:
		FUNC IDENT '(' ')'
	|	FUNC IDENT '(' arg_decl_list ')'
;

var_declaration:
		VAR var_declaration_list
;

var_declaration_list:
		var_declaration_ident
	|	var_declaration_list ',' var_declaration_ident
;

var_declaration_ident:
		IDENT             { c.varDeclaration($1, NULL, yyloc); }
	|	IDENT '=' r_value { c.varDeclaration($1, &$3, yyloc);  }
;

func_declaration:
		FUNC IDENT '(' ')'               '{' { c.funcDecl($2, NULL, yyloc); } statement_list '}' { c.funcEndDecl(false); }
	|	FUNC IDENT '(' arg_decl_list ')' '{' { c.funcDecl($2, $4, yyloc);   } statement_list '}' { c.funcEndDecl(true);  }
;

arg_decl_list:
		IDENT                     { $$ = c.newArgDeclList($1.data.str); }
	|	arg_decl_list  ',' IDENT  { $1->push_back($3.data.str);         }
;

arg_list:
		/* empty */               { $$ = NULL; }
	|	non_empty_arg_list
;

non_empty_arg_list:
		r_value                         { $$ = c.addArgCall(NULL, $1, yyloc); }
	|	non_empty_arg_list ',' r_value  { c.addArgCall($1, $3, yyloc);        }
;

func_call:
		IDENT '(' arg_list ')' { c.funcCall($1, $3, $$, yyloc); }
;

thread_call:
        THREAD IDENT '(' arg_list ')' {}
;

assignment:
		IDENT '=' r_value { c.assignment($1, $3, yyloc); }
;

r_value:
		NUM_INTEGER
	|	NUM_DOUBLE
	|	STR
	|	math_expr
	|	IDENT
	|	func_call
	|	inc_dec
;

math_expr:
		r_value '+' r_value { c.binOp(OP_ADD, $1, $3, $$, yyloc); }
	|	r_value '-' r_value { c.binOp(OP_SUB, $1, $3, $$, yyloc); }
	|	r_value '*' r_value { c.binOp(OP_MUL, $1, $3, $$, yyloc); }
	|	r_value '/' r_value { c.binOp(OP_DIV, $1, $3, $$, yyloc); }
	|	r_value '%' r_value { c.binOp(OP_MOD, $1, $3, $$, yyloc); }
;

%%

namespace clever {

void Parser::error(const Parser::location_type& line, const std::string& msg)
{
	driver.error(line, msg);
}

} // clever