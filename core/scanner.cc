/* Generated by re2c 0.13.5 */
/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <cstdio>
#include "core/scanner.h"
#include "core/parser.hh"
#include "core/ast.h"
#include "core/value.h"
#include "types/native_types.h"

namespace clever {

typedef Parser::token token;

Parser::token_type yylex(Parser::semantic_type* yylval,
	Parser::location_type* yyloc, Driver& driver, ScannerState& s) {
	const unsigned char* cursor = s.cur;
	int yylen;

next_token:
	if (YYCURSOR >= YYLIMIT) {
		RET(token::END);
	}

	s.yylex = cursor;


{
	YYCTYPE yych;
	unsigned int yyaccept = 0;
	if (YYGETCONDITION() < 1) {
		goto yyc_INITIAL;
	} else {
		if (YYGETCONDITION() < 2) {
			goto yyc_ST_COMMENT;
		} else {
			goto yyc_ST_MULTILINE_COMMENT;
		}
	}
/* *********************************** */
yyc_INITIAL:
	{
		static const unsigned char yybm[] = {
			/* table 1 .. 8: 0 */
			 40,  40,  40,  40,  40,  40,  40,  40, 
			 40, 168, 104, 168,  40, 168,  40,  40, 
			 40,  40,  40,  40,  40,  40,  40,  40, 
			 40,  40,  40,  40,  40,  40,  40,  40, 
			168,  40,   8,  40,  40,  40,  40,  32, 
			 40,  40,  40,  40,  40,  40,  40,  40, 
			 47,  47,  47,  47,  47,  47,  47,  47, 
			 45,  45,  40,  40,  40,  40,  40,  40, 
			 40,  44,  44,  44,  44,  44,  44,  44, 
			 44,  44,  44,  44,  44,  44,  44,  44, 
			 44,  44,  44,  44,  44,  44,  44,  44, 
			 44,  44,  44,  40,  16,  40,  40,  40, 
			 40,  44,  44,  44,  44,  44,  44,  44, 
			 44,  44,  44,  44,  44,  44,  44,  44, 
			 44,  44,  44,  44,  44,  44,  44,  44, 
			 44,  44,  44,  40,  40,  40,  40,  40, 
			 40,  40,  40,  40,  40,  40,  40,  40, 
			 40,  40,  40,  40,  40,  40,  40,  40, 
			 40,  40,  40,  40,  40,  40,  40,  40, 
			 40,  40,  40,  40,  40,  40,  40,  40, 
			 40,  40,  40,  40,  40,  40,  40,  40, 
			 40,  40,  40,  40,  40,  40,  40,  40, 
			 40,  40,  40,  40,  40,  40,  40,  40, 
			 40,  40,  40,  40,  40,  40,  40,  40, 
			 40,  40,  40,  40,  40,  40,  40,  40, 
			 40,  40,  40,  40,  40,  40,  40,  40, 
			 40,  40,  40,  40,  40,  40,  40,  40, 
			 40,  40,  40,  40,  40,  40,  40,  40, 
			 40,  40,  40,  40,  40,  40,  40,  40, 
			 40,  40,  40,  40,  40,  40,  40,  40, 
			 40,  40,  40,  40,  40,  40,  40,  40, 
			 40,  40,  40,  40,  40,  40,  40,  40, 
			/* table 9 .. 10: 256 */
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			192, 192, 192, 192, 192, 192, 192, 192, 
			192, 192,   0,   0,   0,   0,   0,   0, 
			  0, 192, 192, 192, 192, 192, 192, 192, 
			192, 192, 192, 192, 192, 192, 192, 192, 
			192, 192, 192, 192, 192, 192, 192, 192, 
			192, 192, 192,   0,   0,   0,   0, 192, 
			  0,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
		};

		yych = *YYCURSOR;
		switch (yych) {
		case 0x00:	goto yy2;
		case '\t':
		case '\v':
		case '\r':
		case ' ':	goto yy5;
		case '\n':	goto yy7;
		case '!':	goto yy9;
		case '"':	goto yy10;
		case '#':	goto yy11;
		case '%':	goto yy13;
		case '&':	goto yy14;
		case '\'':	goto yy16;
		case '(':
		case ')':
		case ',':
		case ';':
		case '{':
		case '}':
		case '~':	goto yy17;
		case '*':	goto yy18;
		case '+':	goto yy19;
		case '-':	goto yy20;
		case '.':	goto yy21;
		case '/':	goto yy22;
		case '0':	goto yy23;
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':	goto yy25;
		case '<':	goto yy26;
		case '=':	goto yy28;
		case '>':	goto yy29;
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':	goto yy31;
		case '^':	goto yy33;
		case 'a':	goto yy34;
		case 'b':	goto yy36;
		case 'c':	goto yy37;
		case 'd':
		case 'g':
		case 'h':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'p':
		case 'q':
		case 'u':
		case 'x':
		case 'y':
		case 'z':	goto yy38;
		case 'e':	goto yy39;
		case 'f':	goto yy40;
		case 'i':	goto yy41;
		case 'n':	goto yy42;
		case 'o':	goto yy43;
		case 'r':	goto yy44;
		case 's':	goto yy45;
		case 't':	goto yy46;
		case 'v':	goto yy47;
		case 'w':	goto yy48;
		case '|':	goto yy49;
		default:	goto yy4;
		}
yy2:
		++YYCURSOR;
yy3:
		{ yylen = cursor - s.yylex; }
		{ RET(Parser::token_type(s.yylex[0])); }
yy4:
		yych = *++YYCURSOR;
		goto yy3;
yy5:
		++YYCURSOR;
		yych = *YYCURSOR;
		goto yy254;
yy6:
		{ yylen = cursor - s.yylex; }
		{ yyloc->step(); SKIP(); }
yy7:
		++YYCURSOR;
		yych = *YYCURSOR;
		goto yy252;
yy8:
		{ yylen = cursor - s.yylex; }
		{
		if (YYGETCONDITION() == yycST_COMMENT) {
			YYSETCONDITION(INITIAL);
		}
		yyloc->lines(yylen);
		yyloc->step();
		SKIP();
	}
yy9:
		yych = *++YYCURSOR;
		if (yych == '=') goto yy249;
		goto yy3;
yy10:
		yyaccept = 0;
		yych = *(YYMARKER = ++YYCURSOR);
		goto yy245;
yy11:
		++YYCURSOR;
		{ yylen = cursor - s.yylex; }
		{
		YYSETCONDITION(ST_COMMENT);
		SKIP();
	}
yy13:
		yych = *++YYCURSOR;
		if (yych == '=') goto yy242;
		goto yy3;
yy14:
		++YYCURSOR;
		if ((yych = *YYCURSOR) == '&') goto yy240;
		if (yych == '=') goto yy238;
yy15:
		{ yylen = cursor - s.yylex; }
		{ RET(Parser::token_type(s.yylex[0])); }
yy16:
		yyaccept = 0;
		yych = *(YYMARKER = ++YYCURSOR);
		goto yy232;
yy17:
		yych = *++YYCURSOR;
		goto yy15;
yy18:
		yych = *++YYCURSOR;
		if (yych == '=') goto yy229;
		goto yy15;
yy19:
		yych = *++YYCURSOR;
		if (yych == '+') goto yy227;
		if (yych == '=') goto yy225;
		goto yy15;
yy20:
		yyaccept = 1;
		yych = *(YYMARKER = ++YYCURSOR);
		if (yych <= '/') {
			if (yych <= ',') goto yy15;
			if (yych <= '-') goto yy223;
			if (yych <= '.') goto yy220;
			goto yy15;
		} else {
			if (yych <= '9') goto yy218;
			if (yych == '=') goto yy221;
			goto yy15;
		}
yy21:
		yych = *++YYCURSOR;
		if (yych <= '/') goto yy3;
		if (yych <= '9') goto yy216;
		goto yy3;
yy22:
		yych = *++YYCURSOR;
		if (yych <= '.') {
			if (yych == '*') goto yy210;
			goto yy15;
		} else {
			if (yych <= '/') goto yy212;
			if (yych == '=') goto yy214;
			goto yy15;
		}
yy23:
		yyaccept = 2;
		yych = *(YYMARKER = ++YYCURSOR);
		if (yych == 'x') goto yy206;
		goto yy205;
yy24:
		{ yylen = cursor - s.yylex; }
		{
		const char* nstr = reinterpret_cast<const char*>(s.yylex);
		int64_t n = 0;

		for (int i = 0; i < yylen; ++i) {
			n = n * 10 + (nstr[i] - '0');
		}

        yylval->intlit = new ast::IntLit(n, *yyloc);

		RET(token::NUM_INTEGER);
	}
yy25:
		yyaccept = 2;
		yych = *(YYMARKER = ++YYCURSOR);
		goto yy196;
yy26:
		++YYCURSOR;
		if ((yych = *YYCURSOR) <= ';') goto yy27;
		if (yych <= '<') goto yy188;
		if (yych <= '=') goto yy190;
yy27:
		{ yylen = cursor - s.yylex; }
		{ RET(token::LESS); }
yy28:
		yych = *++YYCURSOR;
		if (yych == '=') goto yy186;
		goto yy15;
yy29:
		++YYCURSOR;
		if ((yych = *YYCURSOR) <= '<') goto yy30;
		if (yych <= '=') goto yy182;
		if (yych <= '>') goto yy180;
yy30:
		{ yylen = cursor - s.yylex; }
		{ RET(token::GREATER); }
yy31:
		++YYCURSOR;
		if (yybm[256+(yych = *YYCURSOR)] & 128) {
			goto yy175;
		}
		if (yych <= '`') goto yy32;
		if (yych <= 'z') goto yy178;
yy32:
		{ yylen = cursor - s.yylex; }
		{
		yylval->type = new ast::Type(
			CSTRING(std::string(reinterpret_cast<const char*>(s.yylex), yylen)), *yyloc);
		RET(token::TYPE);
	}
yy33:
		yych = *++YYCURSOR;
		if (yych == '=') goto yy173;
		goto yy15;
yy34:
		++YYCURSOR;
		if ((yych = *YYCURSOR) == 'n') goto yy170;
		goto yy55;
yy35:
		{ yylen = cursor - s.yylex; }
		{
		yylval->ident = new ast::Ident(
			CSTRING(std::string(reinterpret_cast<const char*>(s.yylex), yylen)), *yyloc);

		RET(token::IDENT);
	}
yy36:
		yych = *++YYCURSOR;
		if (yych == 'r') goto yy165;
		goto yy55;
yy37:
		yych = *++YYCURSOR;
		if (yych <= 'n') {
			if (yych == 'a') goto yy141;
			goto yy55;
		} else {
			if (yych <= 'o') goto yy142;
			if (yych == 'r') goto yy143;
			goto yy55;
		}
yy38:
		yych = *++YYCURSOR;
		goto yy55;
yy39:
		yych = *++YYCURSOR;
		if (yych == 'l') goto yy130;
		goto yy55;
yy40:
		yych = *++YYCURSOR;
		if (yych <= 'i') {
			if (yych == 'a') goto yy107;
			if (yych <= 'h') goto yy55;
			goto yy108;
		} else {
			if (yych <= 'o') {
				if (yych <= 'n') goto yy55;
				goto yy109;
			} else {
				if (yych == 'u') goto yy110;
				goto yy55;
			}
		}
yy41:
		yych = *++YYCURSOR;
		if (yych == 'f') goto yy99;
		if (yych == 'm') goto yy101;
		goto yy55;
yy42:
		yych = *++YYCURSOR;
		if (yych == 'e') goto yy92;
		if (yych == 'u') goto yy93;
		goto yy55;
yy43:
		yych = *++YYCURSOR;
		if (yych == 'r') goto yy90;
		goto yy55;
yy44:
		yych = *++YYCURSOR;
		if (yych == 'e') goto yy84;
		goto yy55;
yy45:
		yych = *++YYCURSOR;
		if (yych == 'p') goto yy79;
		goto yy55;
yy46:
		yych = *++YYCURSOR;
		if (yych == 'h') goto yy68;
		if (yych == 'r') goto yy69;
		goto yy55;
yy47:
		yych = *++YYCURSOR;
		if (yych == 'a') goto yy65;
		goto yy55;
yy48:
		yych = *++YYCURSOR;
		if (yych == 'a') goto yy56;
		if (yych == 'h') goto yy57;
		goto yy55;
yy49:
		yych = *++YYCURSOR;
		if (yych == '=') goto yy50;
		if (yych == '|') goto yy52;
		goto yy15;
yy50:
		++YYCURSOR;
		{ yylen = cursor - s.yylex; }
		{ RET(token::BW_OR_EQUAL); }
yy52:
		++YYCURSOR;
		{ yylen = cursor - s.yylex; }
		{ RET(token::BOOLEAN_OR); }
yy54:
		++YYCURSOR;
		yych = *YYCURSOR;
yy55:
		if (yybm[256+yych] & 64) {
			goto yy54;
		}
		goto yy35;
yy56:
		yych = *++YYCURSOR;
		if (yych == 'i') goto yy62;
		goto yy55;
yy57:
		yych = *++YYCURSOR;
		if (yych != 'i') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 'l') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 'e') goto yy55;
		++YYCURSOR;
		if (yybm[256+(yych = *YYCURSOR)] & 64) {
			goto yy54;
		}
		{ yylen = cursor - s.yylex; }
		{
		RET(token::WHILE);
	}
yy62:
		yych = *++YYCURSOR;
		if (yych != 't') goto yy55;
		++YYCURSOR;
		if (yybm[256+(yych = *YYCURSOR)] & 64) {
			goto yy54;
		}
		{ yylen = cursor - s.yylex; }
		{
		RET(token::WAIT);
	}
yy65:
		yych = *++YYCURSOR;
		if (yych != 'r') goto yy55;
		++YYCURSOR;
		if (yybm[256+(yych = *YYCURSOR)] & 64) {
			goto yy54;
		}
		{ yylen = cursor - s.yylex; }
		{ RET(token::VAR); }
yy68:
		yych = *++YYCURSOR;
		if (yych == 'r') goto yy75;
		goto yy55;
yy69:
		yych = *++YYCURSOR;
		if (yych == 'u') goto yy72;
		if (yych != 'y') goto yy55;
		++YYCURSOR;
		if (yybm[256+(yych = *YYCURSOR)] & 64) {
			goto yy54;
		}
		{ yylen = cursor - s.yylex; }
		{ RET(token::TRY); }
yy72:
		yych = *++YYCURSOR;
		if (yych != 'e') goto yy55;
		++YYCURSOR;
		if (yybm[256+(yych = *YYCURSOR)] & 64) {
			goto yy54;
		}
		{ yylen = cursor - s.yylex; }
		{
		yylval->true_ = new ast::TrueLit(*yyloc);
		RET(token::TRUE);
	}
yy75:
		yych = *++YYCURSOR;
		if (yych != 'o') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 'w') goto yy55;
		++YYCURSOR;
		if (yybm[256+(yych = *YYCURSOR)] & 64) {
			goto yy54;
		}
		{ yylen = cursor - s.yylex; }
		{ RET(token::THROW); }
yy79:
		yych = *++YYCURSOR;
		if (yych != 'a') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 'w') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 'n') goto yy55;
		++YYCURSOR;
		if (yybm[256+(yych = *YYCURSOR)] & 64) {
			goto yy54;
		}
		{ yylen = cursor - s.yylex; }
		{
		RET(token::THREAD);
	}
yy84:
		yych = *++YYCURSOR;
		if (yych != 't') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 'u') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 'r') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 'n') goto yy55;
		++YYCURSOR;
		if (yybm[256+(yych = *YYCURSOR)] & 64) {
			goto yy54;
		}
		{ yylen = cursor - s.yylex; }
		{
		RET(token::RETURN);
	}
yy90:
		++YYCURSOR;
		if (yybm[256+(yych = *YYCURSOR)] & 64) {
			goto yy54;
		}
		{ yylen = cursor - s.yylex; }
		{ RET(token::LOGICAL_OR); }
yy92:
		yych = *++YYCURSOR;
		if (yych == 'w') goto yy97;
		goto yy55;
yy93:
		yych = *++YYCURSOR;
		if (yych != 'l') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 'l') goto yy55;
		++YYCURSOR;
		if (yybm[256+(yych = *YYCURSOR)] & 64) {
			goto yy54;
		}
		{ yylen = cursor - s.yylex; }
		{
		yylval->nillit = new ast::NullLit(*yyloc);
		RET(token::NIL);
	}
yy97:
		++YYCURSOR;
		if (yybm[256+(yych = *YYCURSOR)] & 64) {
			goto yy54;
		}
		{ yylen = cursor - s.yylex; }
		{
		RET(token::NEW);
	}
yy99:
		++YYCURSOR;
		if (yybm[256+(yych = *YYCURSOR)] & 64) {
			goto yy54;
		}
		{ yylen = cursor - s.yylex; }
		{
		RET(token::IF);
	}
yy101:
		yych = *++YYCURSOR;
		if (yych != 'p') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 'o') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 'r') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 't') goto yy55;
		++YYCURSOR;
		if (yybm[256+(yych = *YYCURSOR)] & 64) {
			goto yy54;
		}
		{ yylen = cursor - s.yylex; }
		{
		RET(token::IMPORT);
	}
yy107:
		yych = *++YYCURSOR;
		if (yych == 'l') goto yy126;
		goto yy55;
yy108:
		yych = *++YYCURSOR;
		if (yych == 'n') goto yy120;
		goto yy55;
yy109:
		yych = *++YYCURSOR;
		if (yych == 'r') goto yy118;
		goto yy55;
yy110:
		yych = *++YYCURSOR;
		if (yych != 'n') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 'c') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 't') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 'i') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 'o') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 'n') goto yy55;
		++YYCURSOR;
		if (yybm[256+(yych = *YYCURSOR)] & 64) {
			goto yy54;
		}
		{ yylen = cursor - s.yylex; }
		{
		RET(token::FUNC);
	}
yy118:
		++YYCURSOR;
		if (yybm[256+(yych = *YYCURSOR)] & 64) {
			goto yy54;
		}
		{ yylen = cursor - s.yylex; }
		{
		RET(token::FOR);
	}
yy120:
		yych = *++YYCURSOR;
		if (yych != 'a') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 'l') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 'l') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 'y') goto yy55;
		++YYCURSOR;
		if (yybm[256+(yych = *YYCURSOR)] & 64) {
			goto yy54;
		}
		{ yylen = cursor - s.yylex; }
		{ RET(token::FINALLY); }
yy126:
		yych = *++YYCURSOR;
		if (yych != 's') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 'e') goto yy55;
		++YYCURSOR;
		if (yybm[256+(yych = *YYCURSOR)] & 64) {
			goto yy54;
		}
		{ yylen = cursor - s.yylex; }
		{
		yylval->false_ = new ast::FalseLit(*yyloc);
		RET(token::FALSE);
	}
yy130:
		yych = *++YYCURSOR;
		if (yych != 's') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 'e') goto yy55;
		yyaccept = 3;
		yych = *(YYMARKER = ++YYCURSOR);
		if (yych <= 'Z') {
			if (yych <= '/') {
				if (yych == ' ') goto yy135;
			} else {
				if (yych <= '9') goto yy54;
				if (yych >= 'A') goto yy54;
			}
		} else {
			if (yych <= '`') {
				if (yych == '_') goto yy54;
			} else {
				if (yych == 'i') goto yy134;
				if (yych <= 'z') goto yy54;
			}
		}
yy133:
		{ yylen = cursor - s.yylex; }
		{
		RET(token::ELSE);
	}
yy134:
		yych = *++YYCURSOR;
		if (yych == 'f') goto yy140;
		goto yy55;
yy135:
		yych = *++YYCURSOR;
		if (yych == 'i') goto yy137;
yy136:
		YYCURSOR = YYMARKER;
		if (yyaccept <= 2) {
			if (yyaccept <= 1) {
				if (yyaccept <= 0) {
					goto yy3;
				} else {
					goto yy15;
				}
			} else {
				goto yy24;
			}
		} else {
			if (yyaccept <= 4) {
				if (yyaccept <= 3) {
					goto yy133;
				} else {
					goto yy201;
				}
			} else {
				goto yy234;
			}
		}
yy137:
		yych = *++YYCURSOR;
		if (yych != 'f') goto yy136;
		++YYCURSOR;
yy139:
		{ yylen = cursor - s.yylex; }
		{
		RET(token::ELSEIF);
	}
yy140:
		yych = *++YYCURSOR;
		if (yybm[256+yych] & 64) {
			goto yy54;
		}
		goto yy139;
yy141:
		yych = *++YYCURSOR;
		if (yych == 't') goto yy161;
		goto yy55;
yy142:
		yych = *++YYCURSOR;
		if (yych == 'n') goto yy151;
		goto yy55;
yy143:
		yych = *++YYCURSOR;
		if (yych != 'i') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 't') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 'i') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 'c') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 'a') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 'l') goto yy55;
		++YYCURSOR;
		if (yybm[256+(yych = *YYCURSOR)] & 64) {
			goto yy54;
		}
		{ yylen = cursor - s.yylex; }
		{
		RET(token::CRITICAL);
	}
yy151:
		yych = *++YYCURSOR;
		if (yych <= 'r') goto yy55;
		if (yych <= 's') goto yy152;
		if (yych <= 't') goto yy153;
		goto yy55;
yy152:
		yych = *++YYCURSOR;
		if (yych == 't') goto yy159;
		goto yy55;
yy153:
		yych = *++YYCURSOR;
		if (yych != 'i') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 'n') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 'u') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 'e') goto yy55;
		++YYCURSOR;
		if (yybm[256+(yych = *YYCURSOR)] & 64) {
			goto yy54;
		}
		{ yylen = cursor - s.yylex; }
		{ RET(token::CONTINUE); }
yy159:
		++YYCURSOR;
		if (yybm[256+(yych = *YYCURSOR)] & 64) {
			goto yy54;
		}
		{ yylen = cursor - s.yylex; }
		{ RET(token::CONST); }
yy161:
		yych = *++YYCURSOR;
		if (yych != 'c') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 'h') goto yy55;
		++YYCURSOR;
		if (yybm[256+(yych = *YYCURSOR)] & 64) {
			goto yy54;
		}
		{ yylen = cursor - s.yylex; }
		{ RET(token::CATCH); }
yy165:
		yych = *++YYCURSOR;
		if (yych != 'e') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 'a') goto yy55;
		yych = *++YYCURSOR;
		if (yych != 'k') goto yy55;
		++YYCURSOR;
		if (yybm[256+(yych = *YYCURSOR)] & 64) {
			goto yy54;
		}
		{ yylen = cursor - s.yylex; }
		{
		RET(token::BREAK);
	}
yy170:
		yych = *++YYCURSOR;
		if (yych != 'd') goto yy55;
		++YYCURSOR;
		if (yybm[256+(yych = *YYCURSOR)] & 64) {
			goto yy54;
		}
		{ yylen = cursor - s.yylex; }
		{ RET(token::LOGICAL_AND); }
yy173:
		++YYCURSOR;
		{ yylen = cursor - s.yylex; }
		{ RET(token::XOR_EQUAL); }
yy175:
		++YYCURSOR;
		yych = *YYCURSOR;
		if (yybm[256+yych] & 128) {
			goto yy175;
		}
		if (yych <= '`') goto yy177;
		if (yych <= 'z') goto yy178;
yy177:
		{ yylen = cursor - s.yylex; }
		{
		yylval->ident = new ast::Ident(
			CSTRING(std::string(reinterpret_cast<const char*>(s.yylex), yylen)), *yyloc);

		RET(token::CONSTANT);
	}
yy178:
		++YYCURSOR;
		yych = *YYCURSOR;
		if (yych <= 'Z') {
			if (yych <= '/') goto yy32;
			if (yych <= '9') goto yy178;
			if (yych <= '@') goto yy32;
			goto yy178;
		} else {
			if (yych <= '_') {
				if (yych <= '^') goto yy32;
				goto yy178;
			} else {
				if (yych <= '`') goto yy32;
				if (yych <= 'z') goto yy178;
				goto yy32;
			}
		}
yy180:
		++YYCURSOR;
		if ((yych = *YYCURSOR) == '=') goto yy184;
		{ yylen = cursor - s.yylex; }
		{ RET(token::RSHIFT); }
yy182:
		++YYCURSOR;
		{ yylen = cursor - s.yylex; }
		{ RET(token::GREATER_EQUAL); }
yy184:
		++YYCURSOR;
		{ yylen = cursor - s.yylex; }
		{ RET(token::RSHIFT_EQUAL); }
yy186:
		++YYCURSOR;
		{ yylen = cursor - s.yylex; }
		{ RET(token::EQUAL); }
yy188:
		++YYCURSOR;
		if ((yych = *YYCURSOR) == '=') goto yy192;
		{ yylen = cursor - s.yylex; }
		{ RET(token::LSHIFT); }
yy190:
		++YYCURSOR;
		{ yylen = cursor - s.yylex; }
		{ RET(token::LESS_EQUAL); }
yy192:
		++YYCURSOR;
		{ yylen = cursor - s.yylex; }
		{ RET(token::LSHIFT_EQUAL); }
yy194:
		yych = *++YYCURSOR;
		if (yych <= '/') goto yy136;
		if (yych <= '9') goto yy202;
		goto yy136;
yy195:
		yyaccept = 2;
		YYMARKER = ++YYCURSOR;
		yych = *YYCURSOR;
yy196:
		if (yybm[0+yych] & 1) {
			goto yy195;
		}
		if (yych <= 'D') {
			if (yych == '.') goto yy194;
			goto yy24;
		} else {
			if (yych <= 'E') goto yy197;
			if (yych != 'e') goto yy24;
		}
yy197:
		yych = *++YYCURSOR;
		if (yych <= ',') {
			if (yych != '+') goto yy136;
		} else {
			if (yych <= '-') goto yy198;
			if (yych <= '/') goto yy136;
			if (yych <= '9') goto yy199;
			goto yy136;
		}
yy198:
		yych = *++YYCURSOR;
		if (yych <= '/') goto yy136;
		if (yych >= ':') goto yy136;
yy199:
		++YYCURSOR;
		yych = *YYCURSOR;
		if (yych <= '/') goto yy201;
		if (yych <= '9') goto yy199;
yy201:
		{ yylen = cursor - s.yylex; }
		{
		double n = strtod(
			std::string(reinterpret_cast<const char*>(s.yylex), yylen).c_str(), NULL);

        yylval->dbllit = new ast::DoubleLit(n, *yyloc);

		RET(token::NUM_DOUBLE);
	}
yy202:
		yyaccept = 4;
		YYMARKER = ++YYCURSOR;
		yych = *YYCURSOR;
		if (yych <= 'D') {
			if (yych <= '/') goto yy201;
			if (yych <= '9') goto yy202;
			goto yy201;
		} else {
			if (yych <= 'E') goto yy197;
			if (yych == 'e') goto yy197;
			goto yy201;
		}
yy204:
		yyaccept = 2;
		YYMARKER = ++YYCURSOR;
		yych = *YYCURSOR;
yy205:
		if (yybm[0+yych] & 2) {
			goto yy204;
		}
		if (yych <= '9') {
			if (yych == '.') goto yy194;
			if (yych <= '/') goto yy24;
			goto yy195;
		} else {
			if (yych <= 'E') {
				if (yych <= 'D') goto yy24;
				goto yy197;
			} else {
				if (yych == 'e') goto yy197;
				goto yy24;
			}
		}
yy206:
		yych = *++YYCURSOR;
		if (yybm[0+yych] & 4) {
			goto yy207;
		}
		goto yy136;
yy207:
		++YYCURSOR;
		yych = *YYCURSOR;
		if (yybm[0+yych] & 4) {
			goto yy207;
		}
		{ yylen = cursor - s.yylex; }
		{
		const char* nstr = reinterpret_cast<const char*>(s.yylex + 2);
		int64_t n = 0;

		for (int i = 0; i < yylen - 2; ++i) {
			n <<= 4;
			if (isdigit(nstr[i])) {
				n += nstr[i] - '0';
			}
			else {
				n += toupper(nstr[i]) - 'A' + 10;
			}
		}

        yylval->intlit = new ast::IntLit(n, *yyloc);

		RET(token::NUM_INTEGER);
	}
yy210:
		++YYCURSOR;
		{ yylen = cursor - s.yylex; }
		{
		YYSETCONDITION(ST_MULTILINE_COMMENT);
		SKIP();
	}
yy212:
		++YYCURSOR;
		{ yylen = cursor - s.yylex; }
		{
		YYSETCONDITION(ST_COMMENT);
		SKIP();
	}
yy214:
		++YYCURSOR;
		{ yylen = cursor - s.yylex; }
		{ RET(token::DIV_EQUAL); }
yy216:
		yyaccept = 4;
		YYMARKER = ++YYCURSOR;
		yych = *YYCURSOR;
		if (yych <= 'D') {
			if (yych <= '/') goto yy201;
			if (yych <= '9') goto yy216;
			goto yy201;
		} else {
			if (yych <= 'E') goto yy197;
			if (yych == 'e') goto yy197;
			goto yy201;
		}
yy218:
		++YYCURSOR;
		yych = *YYCURSOR;
		if (yych == '.') goto yy194;
		if (yych <= '/') goto yy136;
		if (yych <= '9') goto yy218;
		goto yy136;
yy220:
		yych = *++YYCURSOR;
		if (yych <= '/') goto yy136;
		if (yych <= '9') goto yy216;
		goto yy136;
yy221:
		++YYCURSOR;
		{ yylen = cursor - s.yylex; }
		{ RET(token::MINUS_EQUAL); }
yy223:
		++YYCURSOR;
		{ yylen = cursor - s.yylex; }
		{ RET(token::DEC); }
yy225:
		++YYCURSOR;
		{ yylen = cursor - s.yylex; }
		{ RET(token::PLUS_EQUAL); }
yy227:
		++YYCURSOR;
		{ yylen = cursor - s.yylex; }
		{ RET(token::INC); }
yy229:
		++YYCURSOR;
		{ yylen = cursor - s.yylex; }
		{ RET(token::MULT_EQUAL); }
yy231:
		++YYCURSOR;
		yych = *YYCURSOR;
yy232:
		if (yybm[0+yych] & 8) {
			goto yy231;
		}
		if (yych >= '\\') goto yy235;
yy233:
		++YYCURSOR;
yy234:
		{ yylen = cursor - s.yylex; }
		{
		std::string strtext(reinterpret_cast<const char*>(s.yylex+1), yylen-2);
		size_t found = 0;

		// Handle sequence char
		while (1) {
			found = strtext.find('\\', found);
			if (found == std::string::npos) {
				break;
			}
			if (s.yylex[0] == '"') {
				switch (strtext[found+1]) {
					case 'n': strtext.replace(found, 2, 1, '\n'); break;
					case 'r': strtext.replace(found, 2, 1, '\r'); break;
					case 't': strtext.replace(found, 2, 1, '\t'); break;
					case 'v': strtext.replace(found, 2, 1, '\v'); break;
					case '"': strtext.replace(found, 2, 1, '"'); break;
					case '\\': strtext.replace(found, 2, 1, '\\'); ++found; break;
					default: ++found; break;
				}
			} else {
				switch (strtext[found+1]) {
					case '\'': strtext.replace(found, 2, 1, '\''); break;
					default: ++found; break;
				}
			}
		}

        yylval->strlit = new ast::StringLit(CSTRING(strtext), *yyloc);

		RET(token::STR);
	}
yy235:
		++YYCURSOR;
		yych = *YYCURSOR;
		if (yybm[0+yych] & 8) {
			goto yy231;
		}
		if (yych >= '\\') goto yy235;
		yyaccept = 5;
		YYMARKER = ++YYCURSOR;
		yych = *YYCURSOR;
		if (yybm[0+yych] & 8) {
			goto yy231;
		}
		if (yych <= '[') goto yy233;
		goto yy235;
yy238:
		++YYCURSOR;
		{ yylen = cursor - s.yylex; }
		{ RET(token::BW_AND_EQUAL); }
yy240:
		++YYCURSOR;
		{ yylen = cursor - s.yylex; }
		{ RET(token::BOOLEAN_AND); }
yy242:
		++YYCURSOR;
		{ yylen = cursor - s.yylex; }
		{ RET(token::MOD_EQUAL); }
yy244:
		++YYCURSOR;
		yych = *YYCURSOR;
yy245:
		if (yybm[0+yych] & 32) {
			goto yy244;
		}
		if (yych <= '[') goto yy233;
yy246:
		++YYCURSOR;
		yych = *YYCURSOR;
		if (yybm[0+yych] & 32) {
			goto yy244;
		}
		if (yych >= '\\') goto yy246;
		yyaccept = 5;
		YYMARKER = ++YYCURSOR;
		yych = *YYCURSOR;
		if (yybm[0+yych] & 32) {
			goto yy244;
		}
		if (yych <= '[') goto yy233;
		goto yy246;
yy249:
		++YYCURSOR;
		{ yylen = cursor - s.yylex; }
		{ RET(token::NOT_EQUAL); }
yy251:
		++YYCURSOR;
		yych = *YYCURSOR;
yy252:
		if (yybm[0+yych] & 64) {
			goto yy251;
		}
		goto yy8;
yy253:
		++YYCURSOR;
		yych = *YYCURSOR;
yy254:
		if (yybm[0+yych] & 128) {
			goto yy253;
		}
		goto yy6;
	}
/* *********************************** */
yyc_ST_COMMENT:
	{
		static const unsigned char yybm[] = {
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64, 192,  32, 192,  64, 192,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			192,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
			 64,  64,  64,  64,  64,  64,  64,  64, 
		};
		yych = *YYCURSOR;
		if (yych <= '\v') {
			if (yych <= 0x08) {
				if (yych <= 0x00) goto yy258;
				goto yy259;
			} else {
				if (yych == '\n') goto yy261;
				goto yy260;
			}
		} else {
			if (yych <= '\r') {
				if (yych <= '\f') goto yy259;
				goto yy260;
			} else {
				if (yych == ' ') goto yy260;
				goto yy259;
			}
		}
yy257:
		{ yylen = cursor - s.yylex; }
		{
		YYSETCONDITION(INITIAL);
		SKIP();
	}
yy258:
		yych = *++YYCURSOR;
		goto yy266;
yy259:
		yych = *++YYCURSOR;
		goto yy266;
yy260:
		yych = *++YYCURSOR;
		if (yybm[0+yych] & 128) {
			goto yy267;
		}
		if (yych == '\n') goto yy257;
		goto yy265;
yy261:
		++YYCURSOR;
		yych = *YYCURSOR;
		goto yy264;
yy262:
		{ yylen = cursor - s.yylex; }
		{
		if (YYGETCONDITION() == yycST_COMMENT) {
			YYSETCONDITION(INITIAL);
		}
		yyloc->lines(yylen);
		yyloc->step();
		SKIP();
	}
yy263:
		++YYCURSOR;
		yych = *YYCURSOR;
yy264:
		if (yybm[0+yych] & 32) {
			goto yy263;
		}
		goto yy262;
yy265:
		++YYCURSOR;
		yych = *YYCURSOR;
yy266:
		if (yybm[0+yych] & 64) {
			goto yy265;
		}
		goto yy257;
yy267:
		++YYCURSOR;
		yych = *YYCURSOR;
		if (yybm[0+yych] & 128) {
			goto yy267;
		}
		if (yych == '\n') goto yy257;
		goto yy265;
	}
/* *********************************** */
yyc_ST_MULTILINE_COMMENT:
	{
		static const unsigned char yybm[] = {
			 32,  32,  32,  32,  32,  32,  32,  32, 
			 32, 160,  96, 160,  32, 160,  32,  32, 
			 32,  32,  32,  32,  32,  32,  32,  32, 
			 32,  32,  32,  32,  32,  32,  32,  32, 
			160,  32,  32,  32,  32,  32,  32,  32, 
			 32,  32,   0,  32,  32,  32,  32,  32, 
			 32,  32,  32,  32,  32,  32,  32,  32, 
			 32,  32,  32,  32,  32,  32,  32,  32, 
			 32,  32,  32,  32,  32,  32,  32,  32, 
			 32,  32,  32,  32,  32,  32,  32,  32, 
			 32,  32,  32,  32,  32,  32,  32,  32, 
			 32,  32,  32,  32,  32,  32,  32,  32, 
			 32,  32,  32,  32,  32,  32,  32,  32, 
			 32,  32,  32,  32,  32,  32,  32,  32, 
			 32,  32,  32,  32,  32,  32,  32,  32, 
			 32,  32,  32,  32,  32,  32,  32,  32, 
			 32,  32,  32,  32,  32,  32,  32,  32, 
			 32,  32,  32,  32,  32,  32,  32,  32, 
			 32,  32,  32,  32,  32,  32,  32,  32, 
			 32,  32,  32,  32,  32,  32,  32,  32, 
			 32,  32,  32,  32,  32,  32,  32,  32, 
			 32,  32,  32,  32,  32,  32,  32,  32, 
			 32,  32,  32,  32,  32,  32,  32,  32, 
			 32,  32,  32,  32,  32,  32,  32,  32, 
			 32,  32,  32,  32,  32,  32,  32,  32, 
			 32,  32,  32,  32,  32,  32,  32,  32, 
			 32,  32,  32,  32,  32,  32,  32,  32, 
			 32,  32,  32,  32,  32,  32,  32,  32, 
			 32,  32,  32,  32,  32,  32,  32,  32, 
			 32,  32,  32,  32,  32,  32,  32,  32, 
			 32,  32,  32,  32,  32,  32,  32,  32, 
			 32,  32,  32,  32,  32,  32,  32,  32, 
		};
		yych = *YYCURSOR;
		if (yych <= '\f') {
			if (yych <= '\t') {
				if (yych <= 0x00) goto yy271;
				if (yych <= 0x08) goto yy273;
				goto yy274;
			} else {
				if (yych <= '\n') goto yy275;
				if (yych <= '\v') goto yy274;
				goto yy273;
			}
		} else {
			if (yych <= ' ') {
				if (yych <= '\r') goto yy274;
				if (yych <= 0x1F) goto yy273;
				goto yy274;
			} else {
				if (yych == '*') goto yy276;
				goto yy273;
			}
		}
yy271:
		++YYCURSOR;
		yych = *YYCURSOR;
		goto yy281;
yy272:
		{ yylen = cursor - s.yylex; }
		{ SKIP(); }
yy273:
		yych = *++YYCURSOR;
		goto yy281;
yy274:
		yych = *++YYCURSOR;
		if (yybm[0+yych] & 128) {
			goto yy284;
		}
		goto yy281;
yy275:
		yych = *++YYCURSOR;
		if (yybm[0+yych] & 64) {
			goto yy282;
		}
		goto yy281;
yy276:
		++YYCURSOR;
		if ((yych = *YYCURSOR) == '/') goto yy278;
		{ yylen = cursor - s.yylex; }
		{ SKIP(); }
yy278:
		++YYCURSOR;
		{ yylen = cursor - s.yylex; }
		{
		YYSETCONDITION(INITIAL);
		SKIP();
	}
yy280:
		++YYCURSOR;
		yych = *YYCURSOR;
yy281:
		if (yybm[0+yych] & 32) {
			goto yy280;
		}
		goto yy272;
yy282:
		++YYCURSOR;
		yych = *YYCURSOR;
		if (yybm[0+yych] & 64) {
			goto yy282;
		}
		if (yych == '*') goto yy272;
		goto yy280;
yy284:
		++YYCURSOR;
		yych = *YYCURSOR;
		if (yybm[0+yych] & 128) {
			goto yy284;
		}
		if (yych == '*') goto yy272;
		goto yy280;
	}
}

}

} // clever
