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
 * $Id: ubeta.l,v 1.5 2006/09/10 14:30:00 dds Exp $
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

\*{STRESS}A	{ l->nq((unsigned char)'�'); return; }
\*{NOSTRESS}A	{ l->nq((unsigned char)'�'); return; }
\*B		{ l->nq((unsigned char)'�'); return; }
\*C		{ l->nq((unsigned char)'�'); return; }
\*D		{ l->nq((unsigned char)'�'); return; }
\*{STRESS}E	{ l->nq((unsigned char)'�'); return; }
\*{NOSTRESS}E	{ l->nq((unsigned char)'�'); return; }
\*F		{ l->nq((unsigned char)'�'); return; }
\*G		{ l->nq((unsigned char)'�'); return; }
\*{STRESS}H	{ l->nq((unsigned char)'�'); return; }
\*{NOSTRESS}H	{ l->nq((unsigned char)'�'); return; }
\*{STRESS}\+I	{ l->nq((unsigned char)'�'); return; }
\*{STRESS}I	{ l->nq((unsigned char)'�'); return; }
\*{NOSTRESS}\+I	{ l->nq((unsigned char)'�'); return; }
\*{NOSTRESS}I	{ l->nq((unsigned char)'�'); return; }
\*K		{ l->nq((unsigned char)'�'); return; }
\*L		{ l->nq((unsigned char)'�'); return; }
\*M		{ l->nq((unsigned char)'�'); return; }
\*N		{ l->nq((unsigned char)'�'); return; }
\*{STRESS}O	{ l->nq((unsigned char)'�'); return; }
\*{NOSTRESS}O	{ l->nq((unsigned char)'�'); return; }
\*P		{ l->nq((unsigned char)'�'); return; }
\*Q		{ l->nq((unsigned char)'�'); return; }
\*R\(		{ l->nq((unsigned char)'�'); return; }
\*R		{ l->nq((unsigned char)'�'); return; }
\*S		{ l->nq((unsigned char)'�'); return; }
\*T		{ l->nq((unsigned char)'�'); return; }
\*{STRESS}\+U	{ l->nq((unsigned char)'�'); return; }
\*{STRESS}U	{ l->nq((unsigned char)'�'); return; }
\*{NOSTRESS}\+U	{ l->nq((unsigned char)'�'); return; }
\*{NOSTRESS}U	{ l->nq((unsigned char)'�'); return; }
\*{STRESS}W	{ l->nq((unsigned char)'�'); return; }
\*{NOSTRESS}W	{ l->nq((unsigned char)'�'); return; }
\*X		{ l->nq((unsigned char)'�'); return; }
\*Y		{ l->nq((unsigned char)'�'); return; }
\*Z		{ l->nq((unsigned char)'�'); return; }

A{STRESS}	{ l->nq((unsigned char)'�'); return; }
A{NOSTRESS}	{ l->nq((unsigned char)'�'); return; }
B		{ l->nq((unsigned char)'�'); return; }
C		{ l->nq((unsigned char)'�'); return; }
D		{ l->nq((unsigned char)'�'); return; }
E{STRESS}	{ l->nq((unsigned char)'�'); return; }
E{NOSTRESS}	{ l->nq((unsigned char)'�'); return; }
F		{ l->nq((unsigned char)'�'); return; }
G		{ l->nq((unsigned char)'�'); return; }
H{STRESS}	{ l->nq((unsigned char)'�'); return; }
H{NOSTRESS}	{ l->nq((unsigned char)'�'); return; }
I{STRESS}\+	{ l->nq((unsigned char)'�'); return; }
I{STRESS}	{ l->nq((unsigned char)'�'); return; }
I{NOSTRESS}\+	{ l->nq((unsigned char)'�'); return; }
I{NOSTRESS}	{ l->nq((unsigned char)'�'); return; }
K		{ l->nq((unsigned char)'�'); return; }
L		{ l->nq((unsigned char)'�'); return; }
M		{ l->nq((unsigned char)'�'); return; }
N		{ l->nq((unsigned char)'�'); return; }
O{STRESS}	{ l->nq((unsigned char)'�'); return; }
O{NOSTRESS}	{ l->nq((unsigned char)'�'); return; }
P		{ l->nq((unsigned char)'�'); return; }
Q		{ l->nq((unsigned char)'�'); return; }
R\(		{ l->nq((unsigned char)'�'); return; }
R		{ l->nq((unsigned char)'�'); return; }
S/[^A-Za-z*]	{ l->nq((unsigned char)'�'); return; }
S$		{ l->nq((unsigned char)'�'); return; }
S		{ l->nq((unsigned char)'�'); return; }
T		{ l->nq((unsigned char)'�'); return; }
U{STRESS}\+	{ l->nq((unsigned char)'�'); return; }
U{STRESS}	{ l->nq((unsigned char)'�'); return; }
U{NOSTRESS}\+	{ l->nq((unsigned char)'�'); return; }
U{NOSTRESS}	{ l->nq((unsigned char)'�'); return; }
W{STRESS}	{ l->nq((unsigned char)'�'); return; }
W{NOSTRESS}	{ l->nq((unsigned char)'�'); return; }
X		{ l->nq((unsigned char)'�'); return; }
Y		{ l->nq((unsigned char)'�'); return; }
Z		{ l->nq((unsigned char)'�'); return; }
}

\$[0-9]*	{ BEGIN(INITIAL); }	/* Switch to Greek font */
&[0-9]*		{ BEGIN(ROMAN); }	/* Switch to Roman font */

.		{ l->nq((unsigned char)*yytext); return; }
\n		{ l->nq('\n'); return; }

<<EOF>>		{ l->nq(EOF); return; }

%%

int
yywrap(void)
{
	return (1);
}
