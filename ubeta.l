%{
/* 
 * (C) Copyright 2001 Diomidis Spinellis.
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
 * $Id: ubeta.l,v 1.4 2001/02/13 09:39:32 dds Exp $
 */


#include "filter.h"
#include "queue.h"
#include "lex.h"

// This makes the lexer non-reentrant
// It is needed by YY_INPUT which is not called from yylex
static lex *thislex;

#define YY_DECL void lexubeta(lex *l)
#define YY_USER_INIT thislex = l;

#define YY_INPUT(buf,result,max_size) \
{ \
	int c = thislex->getinputcharacter(); \
	result = (c == EOF) ? YY_NULL : (buf[0] = c, 1); \
}

#define yyterminate() return 

%}

STRESS		(\/|\\|=|\(\/|\(\\|\(=|\)\/|\)\\|\)=|=\||\/\||\\\|)
NOSTRESS	(\(|\)|\|)?

%s	ROMAN

%%

<INITIAL>{

\*{STRESS}A	{ l->nq((unsigned char)'¢'); return; }
\*{NOSTRESS}A	{ l->nq((unsigned char)'Á'); return; }
\*B		{ l->nq((unsigned char)'Â'); return; }
\*C		{ l->nq((unsigned char)'Î'); return; }
\*D		{ l->nq((unsigned char)'Ä'); return; }
\*{STRESS}E	{ l->nq((unsigned char)'¸'); return; }
\*{NOSTRESS}E	{ l->nq((unsigned char)'Å'); return; }
\*F		{ l->nq((unsigned char)'Ö'); return; }
\*G		{ l->nq((unsigned char)'Ã'); return; }
\*{STRESS}H	{ l->nq((unsigned char)'¹'); return; }
\*{NOSTRESS}H	{ l->nq((unsigned char)'Ç'); return; }
\*{STRESS}\+I	{ l->nq((unsigned char)'º'); return; }
\*{STRESS}I	{ l->nq((unsigned char)'º'); return; }
\*{NOSTRESS}\+I	{ l->nq((unsigned char)'Ú'); return; }
\*{NOSTRESS}I	{ l->nq((unsigned char)'É'); return; }
\*K		{ l->nq((unsigned char)'Ê'); return; }
\*L		{ l->nq((unsigned char)'Ë'); return; }
\*M		{ l->nq((unsigned char)'Ì'); return; }
\*N		{ l->nq((unsigned char)'Í'); return; }
\*{STRESS}O	{ l->nq((unsigned char)'¼'); return; }
\*{NOSTRESS}O	{ l->nq((unsigned char)'Ï'); return; }
\*P		{ l->nq((unsigned char)'Ð'); return; }
\*Q		{ l->nq((unsigned char)'È'); return; }
\*R\(		{ l->nq((unsigned char)'Ñ'); return; }
\*R		{ l->nq((unsigned char)'Ñ'); return; }
\*S		{ l->nq((unsigned char)'Ó'); return; }
\*T		{ l->nq((unsigned char)'Ô'); return; }
\*{STRESS}\+U	{ l->nq((unsigned char)'¾'); return; }
\*{STRESS}U	{ l->nq((unsigned char)'¾'); return; }
\*{NOSTRESS}\+U	{ l->nq((unsigned char)'Û'); return; }
\*{NOSTRESS}U	{ l->nq((unsigned char)'Õ'); return; }
\*{STRESS}W	{ l->nq((unsigned char)'¿'); return; }
\*{NOSTRESS}W	{ l->nq((unsigned char)'Ù'); return; }
\*X		{ l->nq((unsigned char)'×'); return; }
\*Y		{ l->nq((unsigned char)'Ø'); return; }
\*Z		{ l->nq((unsigned char)'Æ'); return; }

A{STRESS}	{ l->nq((unsigned char)'Ü'); return; }
A{NOSTRESS}	{ l->nq((unsigned char)'á'); return; }
B		{ l->nq((unsigned char)'â'); return; }
C		{ l->nq((unsigned char)'î'); return; }
D		{ l->nq((unsigned char)'ä'); return; }
E{STRESS}	{ l->nq((unsigned char)'Ý'); return; }
E{NOSTRESS}	{ l->nq((unsigned char)'å'); return; }
F		{ l->nq((unsigned char)'ö'); return; }
G		{ l->nq((unsigned char)'ã'); return; }
H{STRESS}	{ l->nq((unsigned char)'Þ'); return; }
H{NOSTRESS}	{ l->nq((unsigned char)'ç'); return; }
I{STRESS}\+	{ l->nq((unsigned char)'À'); return; }
I{STRESS}	{ l->nq((unsigned char)'ß'); return; }
I{NOSTRESS}\+	{ l->nq((unsigned char)'ú'); return; }
I{NOSTRESS}	{ l->nq((unsigned char)'é'); return; }
K		{ l->nq((unsigned char)'ê'); return; }
L		{ l->nq((unsigned char)'ë'); return; }
M		{ l->nq((unsigned char)'ì'); return; }
N		{ l->nq((unsigned char)'í'); return; }
O{STRESS}	{ l->nq((unsigned char)'ü'); return; }
O{NOSTRESS}	{ l->nq((unsigned char)'ï'); return; }
P		{ l->nq((unsigned char)'ð'); return; }
Q		{ l->nq((unsigned char)'è'); return; }
R\(		{ l->nq((unsigned char)'ñ'); return; }
R		{ l->nq((unsigned char)'ñ'); return; }
S/[^A-Za-z*]	{ l->nq((unsigned char)'ò'); return; }
S$		{ l->nq((unsigned char)'ò'); return; }
S		{ l->nq((unsigned char)'ó'); return; }
T		{ l->nq((unsigned char)'ô'); return; }
U{STRESS}\+	{ l->nq((unsigned char)'à'); return; }
U{STRESS}	{ l->nq((unsigned char)'ý'); return; }
U{NOSTRESS}\+	{ l->nq((unsigned char)'û'); return; }
U{NOSTRESS}	{ l->nq((unsigned char)'õ'); return; }
W{STRESS}	{ l->nq((unsigned char)'þ'); return; }
W{NOSTRESS}	{ l->nq((unsigned char)'ù'); return; }
X		{ l->nq((unsigned char)'÷'); return; }
Y		{ l->nq((unsigned char)'ø'); return; }
Z		{ l->nq((unsigned char)'æ'); return; }
}

\$[0-9]*	{ BEGIN(INITIAL); }	/* Switch to Greek font */
&[0-9]*		{ BEGIN(ROMAN); }	/* Switch to Roman font */

.		{ l->nq(*yytext); return; }
\n		{ l->nq('\n'); return; }

<<EOF>>		{ l->nq(EOF); return; }

%%

int
yywrap(void)
{
	return (1);
}
