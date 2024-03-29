%{
/* 
 * (C) Copyright 2000 Diomidis Spinellis.
 * 
 * Permission to use, copy, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appear in all copies and that
 * both that copyright notice and this permission notice appear in
 * supporting documentation.
 * 
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $Id: i843.l,v 1.5 2007/03/01 17:46:01 dds Exp $
 */

/* Redefine these values for stressed output */
	char stress_a = 'a';
	char stress_A = 'A';
	char stress_e = 'e';
	char stress_E = 'E';
	char stress_i = 'i';
	char stress_I = 'I';
	char stress_o = 'o';
	char stress_O = 'O';
	char stress_u = 'u';
	char stress_U = 'U';
	char stress_y = 'y';
	char stress_Y = 'Y';

	char diair_i = 'i';
	char diair_I = 'I';
	char diair_y = 'y';
	char diair_Y = 'Y';

#include "filter.h"
#include "queue.h"
#include "lex.h"

// This makes the lexer non-reentrant
// It is needed by YY_INPUT which is not called from yylex
static lex *thislex;

#define YY_DECL void lexi843(lex *l)
#define YY_USER_INIT thislex = l;

#define YY_INPUT(buf,result,max_size) \
{ \
	int c = thislex->getinputcharacter(); \
	result = (c == EOF) ? YY_NULL : (buf[0] = c, 1); \
}

#define yyterminate() return 

%}

NOTE3	[������������������������������������Ÿǹɺ�ϼվ�ٿ]
NOTE4	[^������������������������������������Ÿǹɺ�ϼվ�ٿ]
GRLCASE	[�����������������������������������]
GRUCASE	[�����Ÿ�ǹ�ɺ������ϼ����վ����ٿ]
NOGREEK	[^����������������������������������������Ÿ�ǹ�ɺ������ϼ����վ����ٿ]


%%

�		{ l->nq('a'); return; }
�		{ l->nq(stress_a); return; }
�		{ l->nq('A'); return; }
�		{ l->nq(stress_A); return; }

��/{NOTE3}	{ l->nq('a'); l->nq('v'); return; }
��/{NOTE3}	{ l->nq('A'); l->nq('v'); return; }
��/{NOTE3}	{ l->nq('A'); l->nq('V'); return; }
��/{NOTE3}	{ l->nq('a'); l->nq('V'); return; }
��/{NOTE4}	{ l->nq('a'); l->nq('f'); return; }
��/{NOTE4}	{ l->nq('A'); l->nq('f'); return; }
��/{NOTE4}	{ l->nq('A'); l->nq('F'); return; }
��/{NOTE4}	{ l->nq('a'); l->nq('F'); return; }

��/{NOTE3}	{ l->nq(stress_a); l->nq('v'); return; /* Note 10 */ }
��/{NOTE3}	{ l->nq(stress_A); l->nq('v'); return; }
��/{NOTE3}	{ l->nq(stress_A); l->nq('V'); return; }
�/{NOTE3}	{ l->nq(stress_a); l->nq('V'); return; }
��/{NOTE4}	{ l->nq(stress_a); l->nq('f'); return; }
��/{NOTE4}	{ l->nq(stress_A); l->nq('f'); return; }
��/{NOTE4}	{ l->nq(stress_A); l->nq('F'); return; }
�/{NOTE4}	{ l->nq(stress_a); l->nq('f'); return; }

�		{ l->nq('v'); return; }
�		{ l->nq('V'); return; }

�		{ l->nq('g'); return; }
�		{ l->nq('G'); return; }

��		{ l->nq('n'); l->nq('g'); return; }
��		{ l->nq('n'); l->nq('G'); return; }
��		{ l->nq('N'); l->nq('g'); return; }
��		{ l->nq('N'); l->nq('G'); return; }

��		{ l->nq('n'); l->nq('x'); return; }
��		{ l->nq('n'); l->nq('X'); return; }
��		{ l->nq('N'); l->nq('x'); return; }
��		{ l->nq('N'); l->nq('X'); return; }

��		{ l->nq('n'); l->nq('c'); l->nq('h'); return; }
��		{ l->nq('n'); l->nq('C'); l->nq('H'); return; }
��		{ l->nq('N'); l->nq('c'); l->nq('h'); return; }
��		{ l->nq('N'); l->nq('C'); l->nq('H'); return; }

�		{ l->nq('d'); return; }
�		{ l->nq('D'); return; }

�		{ l->nq('e'); return; }
�		{ l->nq('E'); return; }
�		{ l->nq(stress_e); return; }
�		{ l->nq(stress_E); return; }

��/{NOTE3}	{ l->nq('e'); l->nq('v'); return; }
��/{NOTE3}	{ l->nq('E'); l->nq('v'); return; }
��/{NOTE3}	{ l->nq('E'); l->nq('V'); return; }
��/{NOTE3}	{ l->nq('e'); l->nq('V'); return; }
��/{NOTE4}	{ l->nq('e'); l->nq('f'); return; }
��/{NOTE4}	{ l->nq('E'); l->nq('f'); return; }
��/{NOTE4}	{ l->nq('E'); l->nq('F'); return; }
��/{NOTE4}	{ l->nq('e'); l->nq('F'); return; }

��/{NOTE3}	{ l->nq(stress_e); l->nq('v'); return; /* Note 10 */ }
��/{NOTE3}	{ l->nq(stress_E); l->nq('v'); return; }
ž/{NOTE3}	{ l->nq(stress_E); l->nq('V'); return; }
�/{NOTE3}	{ l->nq(stress_e); l->nq('V'); return; }
��/{NOTE4}	{ l->nq(stress_e); l->nq('f'); return; }
��/{NOTE4}	{ l->nq(stress_E); l->nq('f'); return; }
ž/{NOTE4}	{ l->nq(stress_E); l->nq('F'); return; }
�/{NOTE4}	{ l->nq(stress_e); l->nq('f'); return; }

�		{ l->nq('z'); return; }
�		{ l->nq('Z'); return; }

�		{ l->nq('i'); return; }
�		{ l->nq('I'); return; }
�		{ l->nq(stress_i); return; }
�		{ l->nq(stress_I); return; }

��/{NOTE3}	{ l->nq('i'); l->nq('v'); return; }
��/{NOTE3}	{ l->nq('I'); l->nq('v'); return; }
��/{NOTE3}	{ l->nq('I'); l->nq('V'); return; }
��/{NOTE3}	{ l->nq('i'); l->nq('V'); return; }
��/{NOTE4}	{ l->nq('i'); l->nq('f'); return; }
��/{NOTE4}	{ l->nq('I'); l->nq('f'); return; }
��/{NOTE4}	{ l->nq('I'); l->nq('F'); return; }
��/{NOTE4}	{ l->nq('i'); l->nq('F'); return; }

��/{NOTE3}	{ l->nq(stress_i); l->nq('v'); return; /* Note 10 */ }
��/{NOTE3}	{ l->nq(stress_I); l->nq('v'); return; }
Ǿ/{NOTE3}	{ l->nq(stress_I); l->nq('V'); return; }
�/{NOTE3}	{ l->nq(stress_i); l->nq('V'); return; }
��/{NOTE4}	{ l->nq(stress_i); l->nq('f'); return; }
��/{NOTE4}	{ l->nq(stress_I); l->nq('f'); return; }
Ǿ/{NOTE4}	{ l->nq(stress_I); l->nq('F'); return; }
�/{NOTE4}	{ l->nq(stress_i); l->nq('F'); return; }

�		{ l->nq('T'); l->nq('H'); return; }
�		{ l->nq('t'); l->nq('h'); return; }
�/{GRLCASE}	{ l->nq('T'); l->nq('h'); return; /* Note 11 */}

�		{ l->nq('i'); return; }
�		{ l->nq(stress_i); return; }
�		{ l->nq(diair_i); return; }
�		{ l->nq(stress_i); return; }
�		{ l->nq('I'); return; }
�		{ l->nq(stress_I); return; }
�		{ l->nq(diair_I); return; }

�		{ l->nq('k'); return; }
�		{ l->nq('K'); return; }

�		{ l->nq('l'); return; }
�		{ l->nq('L'); return; }

�		{ l->nq('m'); return; }
�		{ l->nq('M'); return; }

{NOGREEK}��	{ l->nq(*yytext); l->nq('b'); return; /* Note 5 */ }
{NOGREEK}��	{ l->nq(*yytext); l->nq('B'); return; }
{NOGREEK}��	{ l->nq(*yytext); l->nq('b'); return; }
{NOGREEK}��	{ l->nq(*yytext); l->nq('B'); return; }
^��		{ l->nq('b'); return; }
^��		{ l->nq('B'); return; }
^��		{ l->nq('b'); return; }
^��		{ l->nq('B'); return; }

��/{NOGREEK}	{ l->nq('b'); return; /* Note 7 */ }
��/{NOGREEK}	{ l->nq('B'); return; }
��/{NOGREEK}	{ l->nq('b'); return; }
��/{NOGREEK}	{ l->nq('B'); return; }

�		{ l->nq('n'); return; }
�		{ l->nq('N'); return; }

�		{ l->nq('X'); return; }
�		{ l->nq('x'); return; }


�		{ l->nq('o'); return; }
�		{ l->nq('O'); return; }
�		{ l->nq(stress_o); return; }
�		{ l->nq(stress_O); return; }

��		{ l->nq('o'); l->nq('u'); return; }
��		{ l->nq('O'); l->nq('u'); return; }
��		{ l->nq('o'); l->nq('U'); return; }
��		{ l->nq('O'); l->nq('U'); return; }

��		{ l->nq('o'); l->nq(stress_u); return; }
��		{ l->nq('O'); l->nq(stress_u); return; }
�		{ l->nq('o'); l->nq(stress_U); return; }
Ͼ		{ l->nq('O'); l->nq(stress_U); return; }

�		{ l->nq('p'); return; }
�		{ l->nq('P'); return; }

�		{ l->nq('r'); return; }
�		{ l->nq('R'); return; }

�		{ l->nq('s'); return; }
�		{ l->nq('s'); return; }
�		{ l->nq('S'); return; }

�		{ l->nq('t'); return; }
�		{ l->nq('T'); return; }

�		{ l->nq('y'); return; }
�		{ l->nq('Y'); return; }
�		{ l->nq(stress_y); return; }
�		{ l->nq(diair_y); return; }
�		{ l->nq(stress_y); return; }
�		{ l->nq(stress_Y); return; }
�		{ l->nq(diair_Y); return; }

�		{ l->nq('f'); return; }
�		{ l->nq('F'); return; }

�		{ l->nq('c'); l->nq('h'); return; }
�		{ l->nq('C'); l->nq('H'); return; }
�/{GRLCASE}	{ l->nq('C'); l->nq('h'); return; /* Note 11 */}

�		{ l->nq('p'); l->nq('s'); return; }
�		{ l->nq('P'); l->nq('S'); return; }
�/{GRLCASE}	{ l->nq('P'); l->nq('s'); return; /* Note 11 */}

�		{ l->nq('o'); return; }
�		{ l->nq('O'); return; }
�		{ l->nq(stress_o); return; }
�		{ l->nq(stress_O); return; }

.		{ l->nq(*yytext); return; }
\n		{ l->nq('\n'); return; }

<<EOF>>		{ l->nq(EOF); return; }

%%

int
yywrap(void)
{
	return (1);
}
