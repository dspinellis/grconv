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
 * $Id: ubeta.l,v 1.1 2001/02/13 08:18:54 dds Exp $
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

STRESS		(\/|\\|=|\(\/|\(\\|\(=|\)\/|\)\\|\)=|=\||\/\|\\\|)
NOSTRESS	(\(|\)|\|)?


%%

\*A{STRESS}	{ l->nq((unsigned char)'¢'); return; }
\*A{NOSTRESS}	{ l->nq((unsigned char)'Á'); return; }
\*B		{ l->nq((unsigned char)'Â'); return; }
\*C		{ l->nq((unsigned char)'Î'); return; }
\*D		{ l->nq((unsigned char)'Ä'); return; }
\*E{STRESS}	{ l->nq((unsigned char)'¸'); return; }
\*E{NOSTRESS}	{ l->nq((unsigned char)'Å'); return; }
\*F		{ l->nq((unsigned char)'Ö'); return; }
\*G		{ l->nq((unsigned char)'Ã'); return; }
\*H{STRESS}	{ l->nq((unsigned char)'¹'); return; }
\*H{NOSTRESS}	{ l->nq((unsigned char)'Ç'); return; }
\*I{STRESS}\+	{ l->nq((unsigned char)'º'); return; }
\*I{STRESS}	{ l->nq((unsigned char)'º'); return; }
\*I{NOSTRESS}\+	{ l->nq((unsigned char)'Ú'); return; }
\*I{NOSTRESS}	{ l->nq((unsigned char)'É'); return; }
\*K		{ l->nq((unsigned char)'Ê'); return; }
\*L		{ l->nq((unsigned char)'Ë'); return; }
\*M		{ l->nq((unsigned char)'Ì'); return; }
\*N		{ l->nq((unsigned char)'Í'); return; }
\*O{STRESS}	{ l->nq((unsigned char)'¼'); return; }
\*O{NOSTRESS}	{ l->nq((unsigned char)'Ï'); return; }
\*P		{ l->nq((unsigned char)'Ğ'); return; }
\*Q		{ l->nq((unsigned char)'È'); return; }
\*R		{ l->nq((unsigned char)'Ñ'); return; }
\*S		{ l->nq((unsigned char)'Ó'); return; }
\*T		{ l->nq((unsigned char)'Ô'); return; }
\*U{STRESS}\+	{ l->nq((unsigned char)'¾'); return; }
\*U{STRESS}	{ l->nq((unsigned char)'¾'); return; }
\*U{NOSTRESS}\+	{ l->nq((unsigned char)'Û'); return; }
\*U{NOSTRESS}	{ l->nq((unsigned char)'Õ'); return; }
\*W{STRESS}	{ l->nq((unsigned char)'¿'); return; }
\*W{NOSTRESS}	{ l->nq((unsigned char)'Ù'); return; }
\*X		{ l->nq((unsigned char)'×'); return; }
\*Y		{ l->nq((unsigned char)'Ø'); return; }
\*Z		{ l->nq((unsigned char)'Æ'); return; }

A{STRESS}	{ l->nq((unsigned char)'Ü'); return; }
A{NOSTRESS}	{ l->nq((unsigned char)'á'); return; }
B		{ l->nq((unsigned char)'â'); return; }
C		{ l->nq((unsigned char)'î'); return; }
D		{ l->nq((unsigned char)'ä'); return; }
E{STRESS}	{ l->nq((unsigned char)'İ'); return; }
E{NOSTRESS}	{ l->nq((unsigned char)'å'); return; }
F		{ l->nq((unsigned char)'ö'); return; }
G		{ l->nq((unsigned char)'ã'); return; }
H{STRESS}	{ l->nq((unsigned char)'Ş'); return; }
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
P		{ l->nq((unsigned char)'ğ'); return; }
Q		{ l->nq((unsigned char)'è'); return; }
R		{ l->nq((unsigned char)'ñ'); return; }
S/[^A-Za-z*]	{ l->nq((unsigned char)'ò'); return; }
S$		{ l->nq((unsigned char)'ò'); return; }
S		{ l->nq((unsigned char)'ó'); return; }
T		{ l->nq((unsigned char)'ô'); return; }
U{STRESS}\+	{ l->nq((unsigned char)'à'); return; }
U{STRESS}	{ l->nq((unsigned char)'ı'); return; }
U{NOSTRESS}\+	{ l->nq((unsigned char)'û'); return; }
U{NOSTRESS}	{ l->nq((unsigned char)'õ'); return; }
W{STRESS}	{ l->nq((unsigned char)'ş'); return; }
W{NOSTRESS}	{ l->nq((unsigned char)'ù'); return; }
X		{ l->nq((unsigned char)'÷'); return; }
Y		{ l->nq((unsigned char)'ø'); return; }
Z		{ l->nq((unsigned char)'æ'); return; }

.		{ l->nq(*yytext); return; }
\n		{ l->nq('\n'); return; }

<<EOF>>		{ l->nq(EOF); return; }

%%

int
yywrap(void)
{
	return (1);
}
