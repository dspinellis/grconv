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
 * $Id: uhtmll1.l,v 1.2 2000/03/18 17:20:23 dds Exp $
 */


#include "filter.h"
#include "queue.h"
#include "lex.h"

// This makes the lexer non-reentrant
// It is needed by YY_INPUT which is not called from yylex
static lex *thislex;

#define YY_DECL void lexuhtmll1(lex *l)
#define YY_USER_INIT thislex = l;

#define YY_INPUT(buf,result,max_size) \
{ \
	int c = thislex->getinputcharacter(); \
	result = (c == EOF) ? YY_NULL : (buf[0] = c, 1); \
}

#define yyterminate() return 

%}

%%

&nbsp;		{ l->nq(160); return; }
&iexcl;		{ l->nq(161); return; }
&cent;		{ l->nq(162); return; }
&pound;		{ l->nq(163); return; }
&curren;	{ l->nq(164); return; }
&yen;		{ l->nq(165); return; }
&brvbar;	{ l->nq(166); return; }
&sect;		{ l->nq(167); return; }
&uml;		{ l->nq(168); return; }
&copy;		{ l->nq(169); return; }
&ordf;		{ l->nq(170); return; }
&laquo;		{ l->nq(171); return; }
&not;		{ l->nq(172); return; }
&shy;		{ l->nq(173); return; }
&reg;		{ l->nq(174); return; }
&macr;		{ l->nq(175); return; }
&deg;		{ l->nq(176); return; }
&plusmn;	{ l->nq(177); return; }
&sup2;		{ l->nq(178); return; }
&sup3;		{ l->nq(179); return; }
&acute;		{ l->nq(180); return; }
&micro;		{ l->nq(181); return; }
&para;		{ l->nq(182); return; }
&middot;	{ l->nq(183); return; }
&cedil;		{ l->nq(184); return; }
&sup1;		{ l->nq(185); return; }
&ordm;		{ l->nq(186); return; }
&raquo;		{ l->nq(187); return; }
&frac14;	{ l->nq(188); return; }
&frac12;	{ l->nq(189); return; }
&frac34;	{ l->nq(190); return; }
&iquest;	{ l->nq(191); return; }
&Agrave;	{ l->nq(192); return; }
&Aacute;	{ l->nq(193); return; }
&Acirc;		{ l->nq(194); return; }
&Atilde;	{ l->nq(195); return; }
&Auml;		{ l->nq(196); return; }
&Aring;		{ l->nq(197); return; }
&AElig;		{ l->nq(198); return; }
&Ccedil;	{ l->nq(199); return; }
&Egrave;	{ l->nq(200); return; }
&Eacute;	{ l->nq(201); return; }
&Ecirc;		{ l->nq(202); return; }
&Euml;		{ l->nq(203); return; }
&Igrave;	{ l->nq(204); return; }
&Iacute;	{ l->nq(205); return; }
&Icirc;		{ l->nq(206); return; }
&Iuml;		{ l->nq(207); return; }
&ETH;		{ l->nq(208); return; }
&Ntilde;	{ l->nq(209); return; }
&Ograve;	{ l->nq(210); return; }
&Oacute;	{ l->nq(211); return; }
&Ocirc;		{ l->nq(212); return; }
&Otilde;	{ l->nq(213); return; }
&Ouml;		{ l->nq(214); return; }
&times;		{ l->nq(215); return; }
&Oslash;	{ l->nq(216); return; }
&Ugrave;	{ l->nq(217); return; }
&Uacute;	{ l->nq(218); return; }
&Ucirc;		{ l->nq(219); return; }
&Uuml;		{ l->nq(220); return; }
&Yacute;	{ l->nq(221); return; }
&THORN;		{ l->nq(222); return; }
&szlig;		{ l->nq(223); return; }
&agrave;	{ l->nq(224); return; }
&aacute;	{ l->nq(225); return; }
&acirc;		{ l->nq(226); return; }
&atilde;	{ l->nq(227); return; }
&auml;		{ l->nq(228); return; }
&aring;		{ l->nq(229); return; }
&aelig;		{ l->nq(230); return; }
&ccedil;	{ l->nq(231); return; }
&egrave;	{ l->nq(232); return; }
&eacute;	{ l->nq(233); return; }
&ecirc;		{ l->nq(234); return; }
&euml;		{ l->nq(235); return; }
&igrave;	{ l->nq(236); return; }
&iacute;	{ l->nq(237); return; }
&icirc;		{ l->nq(238); return; }
&iuml;		{ l->nq(239); return; }
&eth;		{ l->nq(240); return; }
&ntilde;	{ l->nq(241); return; }
&ograve;	{ l->nq(242); return; }
&oacute;	{ l->nq(243); return; }
&ocirc;		{ l->nq(244); return; }
&otilde;	{ l->nq(245); return; }
&ouml;		{ l->nq(246); return; }
&divide;	{ l->nq(247); return; }
&oslash;	{ l->nq(248); return; }
&ugrave;	{ l->nq(249); return; }
&uacute;	{ l->nq(250); return; }
&ucirc;		{ l->nq(251); return; }
&uuml;		{ l->nq(252); return; }
&yacute;	{ l->nq(253); return; }
&thorn;		{ l->nq(254); return; }
&yuml;		{ l->nq(255); return; }
.		{ l->nq(*yytext); return; }
\n		{ l->nq('\n'); return; }

<<EOF>>		{ l->nq(EOF); return; }

%%

int
yywrap(void)
{
	return (1);
}
