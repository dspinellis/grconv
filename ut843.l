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
 * $Id: ut843.l,v 1.1 2000/03/12 13:26:19 dds Exp $
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

A		{ l->nq((unsigned char)'Á'); return; }
A'		{ l->nq((unsigned char)'¢'); return; }
V		{ l->nq((unsigned char)'Â'); return; }
G		{ l->nq((unsigned char)'Ã'); return; }
D		{ l->nq((unsigned char)'Ä'); return; }
E		{ l->nq((unsigned char)'Å'); return; }
E'		{ l->nq((unsigned char)'¸'); return; }
Z		{ l->nq((unsigned char)'Æ'); return; }
I_		{ l->nq((unsigned char)'Ç'); return; }
I_'		{ l->nq((unsigned char)'¹'); return; }
TH		{ l->nq((unsigned char)'È'); return; }
Th		{ l->nq((unsigned char)'È'); return; }
I		{ l->nq((unsigned char)'É'); return; }
I'		{ l->nq((unsigned char)'º'); return; }
I''		{ l->nq((unsigned char)'Ú'); return; }
K		{ l->nq((unsigned char)'Ê'); return; }
L		{ l->nq((unsigned char)'Ë'); return; }
M		{ l->nq((unsigned char)'Ì'); return; }
N		{ l->nq((unsigned char)'Í'); return; }
X		{ l->nq((unsigned char)'Î'); return; }
O		{ l->nq((unsigned char)'Ï'); return; }
O'		{ l->nq((unsigned char)'¼'); return; }
P		{ l->nq((unsigned char)'Ğ'); return; }
R		{ l->nq((unsigned char)'Ñ'); return; }
S		{ l->nq((unsigned char)'Ó'); return; }
T		{ l->nq((unsigned char)'Ô'); return; }
Y		{ l->nq((unsigned char)'Õ'); return; }
Y'		{ l->nq((unsigned char)'¾'); return; }
Y''		{ l->nq((unsigned char)'Û'); return; }
F		{ l->nq((unsigned char)'Ö'); return; }
CH		{ l->nq((unsigned char)'×'); return; }
PS		{ l->nq((unsigned char)'Ø'); return; }
Ch		{ l->nq((unsigned char)'×'); return; }
Ps		{ l->nq((unsigned char)'Ø'); return; }
O_		{ l->nq((unsigned char)'Ù'); return; }
O_'		{ l->nq((unsigned char)'¿'); return; }
a		{ l->nq((unsigned char)'á'); return; }
a'		{ l->nq((unsigned char)'Ü'); return; }
v		{ l->nq((unsigned char)'â'); return; }
g		{ l->nq((unsigned char)'ã'); return; }
d		{ l->nq((unsigned char)'ä'); return; }
e		{ l->nq((unsigned char)'å'); return; }
e'		{ l->nq((unsigned char)'İ'); return; }
z		{ l->nq((unsigned char)'æ'); return; }
i_		{ l->nq((unsigned char)'ç'); return; }
i_'		{ l->nq((unsigned char)'Ş'); return; }
th		{ l->nq((unsigned char)'è'); return; }
i		{ l->nq((unsigned char)'é'); return; }
i'		{ l->nq((unsigned char)'ß'); return; }
i''		{ l->nq((unsigned char)'ú'); return; }
i'''		{ l->nq((unsigned char)'À'); return; }
k		{ l->nq((unsigned char)'ê'); return; }
l		{ l->nq((unsigned char)'ë'); return; }
m		{ l->nq((unsigned char)'ì'); return; }
n		{ l->nq((unsigned char)'í'); return; }
x		{ l->nq((unsigned char)'î'); return; }
o		{ l->nq((unsigned char)'ï'); return; }
o'		{ l->nq((unsigned char)'ü'); return; }
p		{ l->nq((unsigned char)'ğ'); return; }
r		{ l->nq((unsigned char)'ñ'); return; }
s		{ l->nq((unsigned char)'ò'); return; }
s/[a-z\-]	{ l->nq((unsigned char)'ó'); return; /* Note 2 */ }
t		{ l->nq((unsigned char)'ô'); return; }
y		{ l->nq((unsigned char)'õ'); return; }
y'		{ l->nq((unsigned char)'ı'); return; }
y''		{ l->nq((unsigned char)'û'); return; }
y'''		{ l->nq((unsigned char)'à'); return; }
f		{ l->nq((unsigned char)'ö'); return; }
ch		{ l->nq((unsigned char)'÷'); return; }
ps		{ l->nq((unsigned char)'ø'); return; }
o_		{ l->nq((unsigned char)'ù'); return; }
o_'		{ l->nq((unsigned char)'ş'); return; }
\?		{ l->nq((unsigned char)';'); return; }

.		{ l->nq(*yytext); return; }
\n		{ l->nq('\n'); return; }

<<EOF>>		{ l->nq(EOF); return; }

%%

yywrap()
{
	return (1);
}
