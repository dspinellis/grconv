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

NOTE3	[âãäæëìíñáÜåİçŞéßúÀïüõıûàùşÂÃÄÆËÌÍÑÁ¢Å¸Ç¹ÉºÏ¼Õ¾Ù¿]
NOTE4	[^âãäæëìíñáÜåİçŞéßúÀïüõıûàùşÂÃÄÆËÌÍÑÁ¢Å¸Ç¹ÉºÏ¼Õ¾Ù¿]
GRLCASE	[áÜâãäåİæçŞèéßúÀêëìíîïüğñóôõıûàö÷øùş]
GRUCASE	[Á¢ÂÃÄÅ¸ÆÇ¹ÈÉºÚÊËÌÍÎÏ¼ĞÑÓÔÕ¾ÛÖ×ØÙ¿]
NOGREEK	[^áÜâãäåİæçŞèéßúÀêëìíîïüğñóôõıûàö÷øùşÁ¢ÂÃÄÅ¸ÆÇ¹ÈÉºÚÊËÌÍÎÏ¼ĞÑÓÔÕ¾ÛÖ×ØÙ¿]


%%

á		{ l->nq('a'); return; }
Ü		{ l->nq(stress_a); return; }
Á		{ l->nq('A'); return; }
¢		{ l->nq(stress_A); return; }

áõ/{NOTE3}	{ l->nq('a'); l->nq('v'); return; }
Áõ/{NOTE3}	{ l->nq('A'); l->nq('v'); return; }
ÁÕ/{NOTE3}	{ l->nq('A'); l->nq('V'); return; }
áÕ/{NOTE3}	{ l->nq('a'); l->nq('V'); return; }
áõ/{NOTE4}	{ l->nq('a'); l->nq('f'); return; }
Áõ/{NOTE4}	{ l->nq('A'); l->nq('f'); return; }
ÁÕ/{NOTE4}	{ l->nq('A'); l->nq('F'); return; }
áÕ/{NOTE4}	{ l->nq('a'); l->nq('F'); return; }

áı/{NOTE3}	{ l->nq(stress_a); l->nq('v'); return; /* Note 10 */ }
Áı/{NOTE3}	{ l->nq(stress_A); l->nq('v'); return; }
Á¾/{NOTE3}	{ l->nq(stress_A); l->nq('V'); return; }
á¾/{NOTE3}	{ l->nq(stress_a); l->nq('V'); return; }
áı/{NOTE4}	{ l->nq(stress_a); l->nq('f'); return; }
Áı/{NOTE4}	{ l->nq(stress_A); l->nq('f'); return; }
Á¾/{NOTE4}	{ l->nq(stress_A); l->nq('F'); return; }
á¾/{NOTE4}	{ l->nq(stress_a); l->nq('f'); return; }

â		{ l->nq('v'); return; }
Â		{ l->nq('V'); return; }

ã		{ l->nq('g'); return; }
Ã		{ l->nq('G'); return; }

ãã		{ l->nq('n'); l->nq('g'); return; }
ãÃ		{ l->nq('n'); l->nq('G'); return; }
Ãã		{ l->nq('N'); l->nq('g'); return; }
ÃÃ		{ l->nq('N'); l->nq('G'); return; }

ãî		{ l->nq('n'); l->nq('x'); return; }
ãÎ		{ l->nq('n'); l->nq('X'); return; }
Ãî		{ l->nq('N'); l->nq('x'); return; }
ÃÎ		{ l->nq('N'); l->nq('X'); return; }

ã÷		{ l->nq('n'); l->nq('c'); l->nq('h'); return; }
ã×		{ l->nq('n'); l->nq('C'); l->nq('H'); return; }
Ã÷		{ l->nq('N'); l->nq('c'); l->nq('h'); return; }
Ã×		{ l->nq('N'); l->nq('C'); l->nq('H'); return; }

ä		{ l->nq('d'); return; }
Ä		{ l->nq('D'); return; }

å		{ l->nq('e'); return; }
Å		{ l->nq('E'); return; }
İ		{ l->nq(stress_e); return; }
¸		{ l->nq(stress_E); return; }

åõ/{NOTE3}	{ l->nq('e'); l->nq('v'); return; }
Åõ/{NOTE3}	{ l->nq('E'); l->nq('v'); return; }
ÅÕ/{NOTE3}	{ l->nq('E'); l->nq('V'); return; }
åÕ/{NOTE3}	{ l->nq('e'); l->nq('V'); return; }
åõ/{NOTE4}	{ l->nq('e'); l->nq('f'); return; }
Åõ/{NOTE4}	{ l->nq('E'); l->nq('f'); return; }
ÅÕ/{NOTE4}	{ l->nq('E'); l->nq('F'); return; }
åÕ/{NOTE4}	{ l->nq('e'); l->nq('F'); return; }

åı/{NOTE3}	{ l->nq(stress_e); l->nq('v'); return; /* Note 10 */ }
Åı/{NOTE3}	{ l->nq(stress_E); l->nq('v'); return; }
Å¾/{NOTE3}	{ l->nq(stress_E); l->nq('V'); return; }
å¾/{NOTE3}	{ l->nq(stress_e); l->nq('V'); return; }
åı/{NOTE4}	{ l->nq(stress_e); l->nq('f'); return; }
Åı/{NOTE4}	{ l->nq(stress_E); l->nq('f'); return; }
Å¾/{NOTE4}	{ l->nq(stress_E); l->nq('F'); return; }
å¾/{NOTE4}	{ l->nq(stress_e); l->nq('f'); return; }

æ		{ l->nq('z'); return; }
Æ		{ l->nq('Z'); return; }

ç		{ l->nq('i'); return; }
Ç		{ l->nq('I'); return; }
Ş		{ l->nq(stress_i); return; }
¹		{ l->nq(stress_I); return; }

çõ/{NOTE3}	{ l->nq('i'); l->nq('v'); return; }
Çõ/{NOTE3}	{ l->nq('E'); l->nq('v'); return; }
ÇÕ/{NOTE3}	{ l->nq('E'); l->nq('V'); return; }
çÕ/{NOTE3}	{ l->nq('i'); l->nq('V'); return; }
çõ/{NOTE4}	{ l->nq('i'); l->nq('f'); return; }
Çõ/{NOTE4}	{ l->nq('E'); l->nq('f'); return; }
ÇÕ/{NOTE4}	{ l->nq('E'); l->nq('F'); return; }
çÕ/{NOTE4}	{ l->nq('i'); l->nq('F'); return; }

çı/{NOTE3}	{ l->nq(stress_i); l->nq('v'); return; /* Note 10 */ }
Çı/{NOTE3}	{ l->nq(stress_I); l->nq('v'); return; }
Ç¾/{NOTE3}	{ l->nq(stress_I); l->nq('V'); return; }
ç¾/{NOTE3}	{ l->nq(stress_i); l->nq('V'); return; }
çı/{NOTE4}	{ l->nq(stress_i); l->nq('f'); return; }
Çı/{NOTE4}	{ l->nq(stress_I); l->nq('f'); return; }
Ç¾/{NOTE4}	{ l->nq(stress_I); l->nq('F'); return; }
ç¾/{NOTE4}	{ l->nq(stress_i); l->nq('F'); return; }

È		{ l->nq('T'); l->nq('H'); return; }
è		{ l->nq('t'); l->nq('h'); return; }
È/{GRLCASE}	{ l->nq('T'); l->nq('h'); return; /* Note 11 */}

é		{ l->nq('i'); return; }
ß		{ l->nq(stress_i); return; }
ú		{ l->nq(diair_i); return; }
À		{ l->nq(stress_i); return; }
É		{ l->nq('I'); return; }
º		{ l->nq(stress_I); return; }
Ú		{ l->nq(diair_I); return; }

ê		{ l->nq('k'); return; }
Ê		{ l->nq('K'); return; }

ë		{ l->nq('l'); return; }
Ë		{ l->nq('L'); return; }

ì		{ l->nq('m'); return; }
Ì		{ l->nq('M'); return; }

{NOGREEK}ìğ	{ l->nq(*yytext); l->nq('b'); return; /* Note 5 */ }
{NOGREEK}Ìğ	{ l->nq(*yytext); l->nq('B'); return; }
{NOGREEK}ìĞ	{ l->nq(*yytext); l->nq('b'); return; }
{NOGREEK}ÌĞ	{ l->nq(*yytext); l->nq('B'); return; }
^ìğ		{ l->nq('b'); return; }
^Ìğ		{ l->nq('B'); return; }
^ìĞ		{ l->nq('b'); return; }
^ÌĞ		{ l->nq('B'); return; }

ìğ/{NOGREEK}	{ l->nq('b'); return; /* Note 7 */ }
Ìğ/{NOGREEK}	{ l->nq('B'); return; }
ìĞ/{NOGREEK}	{ l->nq('b'); return; }
ÌĞ/{NOGREEK}	{ l->nq('B'); return; }

í		{ l->nq('n'); return; }
Í		{ l->nq('N'); return; }

Î		{ l->nq('X'); return; }
î		{ l->nq('x'); return; }


ï		{ l->nq('o'); return; }
Ï		{ l->nq('O'); return; }
ü		{ l->nq(stress_o); return; }
¼		{ l->nq(stress_O); return; }

ïõ		{ l->nq('o'); l->nq('u'); return; }
Ïõ		{ l->nq('O'); l->nq('u'); return; }
ïÕ		{ l->nq('o'); l->nq('U'); return; }
ÏÕ		{ l->nq('O'); l->nq('U'); return; }

ïı		{ l->nq('o'); l->nq(stress_u); return; }
Ïı		{ l->nq('O'); l->nq(stress_u); return; }
ï¾		{ l->nq('o'); l->nq(stress_U); return; }
Ï¾		{ l->nq('O'); l->nq(stress_U); return; }

ğ		{ l->nq('p'); return; }
Ğ		{ l->nq('P'); return; }

ñ		{ l->nq('r'); return; }
Ñ		{ l->nq('R'); return; }

ó		{ l->nq('s'); return; }
ò		{ l->nq('s'); return; }
Ó		{ l->nq('S'); return; }

ô		{ l->nq('t'); return; }
Ô		{ l->nq('T'); return; }

õ		{ l->nq('y'); return; }
Õ		{ l->nq('Y'); return; }
ı		{ l->nq(stress_y); return; }
û		{ l->nq(diair_y); return; }
à		{ l->nq(stress_y); return; }
¾		{ l->nq(stress_Y); return; }
Û		{ l->nq(diair_Y); return; }

ö		{ l->nq('f'); return; }
Ö		{ l->nq('F'); return; }

÷		{ l->nq('c'); l->nq('h'); return; }
×		{ l->nq('C'); l->nq('H'); return; }
×/{GRLCASE}	{ l->nq('C'); l->nq('h'); return; /* Note 11 */}

ø		{ l->nq('p'); l->nq('s'); return; }
Ø		{ l->nq('P'); l->nq('S'); return; }
Ø/{GRLCASE}	{ l->nq('P'); l->nq('s'); return; /* Note 11 */}

ù		{ l->nq('o'); return; }
Ù		{ l->nq('O'); return; }
ş		{ l->nq(stress_o); return; }
¿		{ l->nq(stress_O); return; }

.		{ l->nq(*yytext); return; }
\n		{ l->nq('\n'); return; }

<<EOF>>		{ l->nq(EOF); return; }

%%

int
yywrap(void)
{
	return (1);
}
