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
 * $Id: ut843.l,v 1.3 2006/09/10 14:30:30 dds Exp $
 */


#include "filter.h"
#include "queue.h"
#include "lex.h"

// This makes the lexer non-reentrant
// It is needed by YY_INPUT which is not called from yylex
static lex *thislex;

#define YY_DECL void lexut843(lex *l)
#define YY_USER_INIT thislex = l;

#define YY_INPUT(buf,result,max_size) \
{ \
	int c = thislex->getinputcharacter(); \
	result = (c == EOF) ? YY_NULL : (buf[0] = c, 1); \
}

#define yyterminate() return 

%}


%%

A		{ l->nq((unsigned char)'�'); return; }
A'		{ l->nq((unsigned char)'�'); return; }
V		{ l->nq((unsigned char)'�'); return; }
G		{ l->nq((unsigned char)'�'); return; }
D		{ l->nq((unsigned char)'�'); return; }
E		{ l->nq((unsigned char)'�'); return; }
E'		{ l->nq((unsigned char)'�'); return; }
Z		{ l->nq((unsigned char)'�'); return; }
I_		{ l->nq((unsigned char)'�'); return; }
I_'		{ l->nq((unsigned char)'�'); return; }
TH		{ l->nq((unsigned char)'�'); return; }
Th		{ l->nq((unsigned char)'�'); return; }
I		{ l->nq((unsigned char)'�'); return; }
I'		{ l->nq((unsigned char)'�'); return; }
I''		{ l->nq((unsigned char)'�'); return; }
K		{ l->nq((unsigned char)'�'); return; }
L		{ l->nq((unsigned char)'�'); return; }
M		{ l->nq((unsigned char)'�'); return; }
N		{ l->nq((unsigned char)'�'); return; }
X		{ l->nq((unsigned char)'�'); return; }
O		{ l->nq((unsigned char)'�'); return; }
O'		{ l->nq((unsigned char)'�'); return; }
P		{ l->nq((unsigned char)'�'); return; }
R		{ l->nq((unsigned char)'�'); return; }
S		{ l->nq((unsigned char)'�'); return; }
T		{ l->nq((unsigned char)'�'); return; }
Y		{ l->nq((unsigned char)'�'); return; }
Y'		{ l->nq((unsigned char)'�'); return; }
Y''		{ l->nq((unsigned char)'�'); return; }
F		{ l->nq((unsigned char)'�'); return; }
CH		{ l->nq((unsigned char)'�'); return; }
PS		{ l->nq((unsigned char)'�'); return; }
Ch		{ l->nq((unsigned char)'�'); return; }
Ps		{ l->nq((unsigned char)'�'); return; }
O_		{ l->nq((unsigned char)'�'); return; }
O_'		{ l->nq((unsigned char)'�'); return; }
a		{ l->nq((unsigned char)'�'); return; }
a'		{ l->nq((unsigned char)'�'); return; }
v		{ l->nq((unsigned char)'�'); return; }
g		{ l->nq((unsigned char)'�'); return; }
d		{ l->nq((unsigned char)'�'); return; }
e		{ l->nq((unsigned char)'�'); return; }
e'		{ l->nq((unsigned char)'�'); return; }
z		{ l->nq((unsigned char)'�'); return; }
i_		{ l->nq((unsigned char)'�'); return; }
i_'		{ l->nq((unsigned char)'�'); return; }
th		{ l->nq((unsigned char)'�'); return; }
i		{ l->nq((unsigned char)'�'); return; }
i'		{ l->nq((unsigned char)'�'); return; }
i''		{ l->nq((unsigned char)'�'); return; }
i'''		{ l->nq((unsigned char)'�'); return; }
k		{ l->nq((unsigned char)'�'); return; }
l		{ l->nq((unsigned char)'�'); return; }
m		{ l->nq((unsigned char)'�'); return; }
n		{ l->nq((unsigned char)'�'); return; }
x		{ l->nq((unsigned char)'�'); return; }
o		{ l->nq((unsigned char)'�'); return; }
o'		{ l->nq((unsigned char)'�'); return; }
p		{ l->nq((unsigned char)'�'); return; }
r		{ l->nq((unsigned char)'�'); return; }
s		{ l->nq((unsigned char)'�'); return; }
s/[a-z\-]	{ l->nq((unsigned char)'�'); return; /* Note 2 */ }
t		{ l->nq((unsigned char)'�'); return; }
y		{ l->nq((unsigned char)'�'); return; }
y'		{ l->nq((unsigned char)'�'); return; }
y''		{ l->nq((unsigned char)'�'); return; }
y'''		{ l->nq((unsigned char)'�'); return; }
f		{ l->nq((unsigned char)'�'); return; }
ch		{ l->nq((unsigned char)'�'); return; }
ps		{ l->nq((unsigned char)'�'); return; }
o_		{ l->nq((unsigned char)'�'); return; }
o_'		{ l->nq((unsigned char)'�'); return; }
\?		{ l->nq((unsigned char)';'); return; }

.		{ l->nq((unsigned char)*yytext); return; }
\n		{ l->nq('\n'); return; }

<<EOF>>		{ l->nq(EOF); return; }

%%

int
yywrap(void)
{
	return (1);
}
