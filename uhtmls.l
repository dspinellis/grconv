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
 * $Id: uhtmls.l,v 1.1 2000/04/19 10:54:10 dds Exp $
 */


#include "filter.h"
#include "queue.h"
#include "lex.h"

// This makes the lexer non-reentrant
// It is needed by YY_INPUT which is not called from yylex
static lex *thislex;

#define YY_DECL void lexuhtmls(lex *l)
#define YY_USER_INIT thislex = l;

#define YY_INPUT(buf,result,max_size) \
{ \
	int c = thislex->getinputcharacter(); \
	result = (c == EOF) ? YY_NULL : (buf[0] = c, 1); \
}

#define yyterminate() return 

%}

%%

&Alpha;		{ l->nq(193); return; } 
&Beta;		{ l->nq(194); return; } 
&Gamma;		{ l->nq(195); return; } 
&Delta;		{ l->nq(196); return; } 
&Epsilon;	{ l->nq(197); return; } 
&Zeta;		{ l->nq(198); return; } 
&Eta;		{ l->nq(199); return; } 
&Theta;		{ l->nq(200); return; } 
&Iota;		{ l->nq(201); return; } 
&Kappa;		{ l->nq(202); return; } 
&Lambda;	{ l->nq(203); return; } 
&Mu;		{ l->nq(204); return; } 
&Nu;		{ l->nq(205); return; } 
&Xi;		{ l->nq(206); return; } 
&Omicron;	{ l->nq(207); return; } 
&Pi;		{ l->nq(208); return; } 
&Rho;		{ l->nq(209); return; } 
&Sigma;		{ l->nq(211); return; } 
&Tau;		{ l->nq(212); return; } 
&Upsilon;	{ l->nq(213); return; } 
&Phi;		{ l->nq(214); return; } 
&Chi;		{ l->nq(215); return; } 
&Psi;		{ l->nq(216); return; } 
&Omega;		{ l->nq(217); return; } 
&alpha;		{ l->nq(225); return; } 
&beta;		{ l->nq(226); return; } 
&gamma;		{ l->nq(227); return; } 
&delta;		{ l->nq(228); return; } 
&epsilon;	{ l->nq(229); return; } 
&zeta;		{ l->nq(230); return; } 
&eta;		{ l->nq(231); return; } 
&theta;		{ l->nq(232); return; } 
&thetasym;	{ l->nq(232); return; }
&iota;		{ l->nq(233); return; } 
&kappa;		{ l->nq(234); return; } 
&lambda;	{ l->nq(235); return; } 
&mu;		{ l->nq(236); return; } 
&nu;		{ l->nq(237); return; } 
&xi;		{ l->nq(238); return; } 
&omicron;	{ l->nq(239); return; }  
&pi;		{ l->nq(240); return; } 
&piv;		{ l->nq(240); return; }
&rho;		{ l->nq(241); return; } 
&sigmaf;	{ l->nq(242); return; } 
&sigma;		{ l->nq(243); return; } 
&tau;		{ l->nq(244); return; } 
&upsilon;	{ l->nq(245); return; } 
&phi;		{ l->nq(246); return; } 
&chi;		{ l->nq(247); return; } 
&psi;		{ l->nq(248); return; } 
&omega;		{ l->nq(249); return; } 
.		{ l->nq(*yytext); return; }
\n		{ l->nq('\n'); return; }

<<EOF>>		{ l->nq(EOF); return; }

%%

int
yywrap(void)
{
	return (1);
}
