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
 * $Id: translit.cpp,v 1.1 2000/03/12 13:26:19 dds Exp $
 */

#include "filter.h"
#include "queue.h"
#include "translit.h"

void
translit::fillbuff()
{
	int c;

	switch (c = input->getcharacter()) {
	case (unsigned char)'Á': nq('A'); break;
	case (unsigned char)'¢': nq('A'); nq('\''); break;
	case (unsigned char)'Â': nq('V'); break;
	case (unsigned char)'Ã': nq('G'); break;
	case (unsigned char)'Ä': nq('D'); break;
	case (unsigned char)'Å': nq('E'); break;
	case (unsigned char)'¸': nq('E'); nq('\''); break;
	case (unsigned char)'Æ': nq('Z'); break;
	case (unsigned char)'Ç': nq('I'); nq('_'); break;
	case (unsigned char)'¹': nq('I'); nq('_'); nq('\''); break;
	case (unsigned char)'È': nq('T'); nq('H'); break;
	case (unsigned char)'É': nq('I'); break;
	case (unsigned char)'º': nq('I'); nq('\''); break;
	case (unsigned char)'Ú': nq('I'); nq('\''); nq('\''); break;
	case (unsigned char)'Ê': nq('K'); break;
	case (unsigned char)'Ë': nq('L'); break;
	case (unsigned char)'Ì': nq('M'); break;
	case (unsigned char)'Í': nq('N'); break;
	case (unsigned char)'Î': nq('X'); break;
	case (unsigned char)'Ï': nq('O'); break;
	case (unsigned char)'¼': nq('O'); nq('\''); break;
	case (unsigned char)'Ð': nq('P'); break;
	case (unsigned char)'Ñ': nq('R'); break;
	case (unsigned char)'Ó': nq('S'); break;
	case (unsigned char)'Ô': nq('T'); break;
	case (unsigned char)'Õ': nq('Y'); break;
	case (unsigned char)'¾': nq('Y'); nq('_'); break;
	case (unsigned char)'Û': nq('Y'); nq('_'); nq('\''); break;
	case (unsigned char)'Ö': nq('F'); break;
	case (unsigned char)'×': nq('C'); nq('H'); break;
	case (unsigned char)'Ø': nq('P'); nq('S'); break;
	case (unsigned char)'Ù': nq('O'); nq('_'); break;
	case (unsigned char)'¿': nq('O'); nq('_'); nq('\''); break;
	case (unsigned char)'á': nq('a'); break;
	case (unsigned char)'Ü': nq('a'); nq('\''); break;
	case (unsigned char)'â': nq('v'); break;
	case (unsigned char)'ã': nq('g'); break;
	case (unsigned char)'ä': nq('d'); break;
	case (unsigned char)'å': nq('e'); break;
	case (unsigned char)'Ý': nq('e'); nq('\''); break;
	case (unsigned char)'æ': nq('z'); break;
	case (unsigned char)'ç': nq('i'); nq('_'); break;
	case (unsigned char)'Þ': nq('i'); nq('_'); nq('\''); break;
	case (unsigned char)'è': nq('t'); nq('h'); break;
	case (unsigned char)'é': nq('i'); break;
	case (unsigned char)'ß': nq('i'); nq('\''); break;
	case (unsigned char)'ú': nq('i'); nq('\''); nq('\''); break;
	case (unsigned char)'À': nq('i'); nq('\''); nq('\''); nq('\''); break;
	case (unsigned char)'ê': nq('k'); break;
	case (unsigned char)'ë': nq('l'); break;
	case (unsigned char)'ì': nq('m'); break;
	case (unsigned char)'í': nq('n'); break;
	case (unsigned char)'î': nq('x'); break;
	case (unsigned char)'ï': nq('o'); break;
	case (unsigned char)'ü': nq('o'); nq('\''); break;
	case (unsigned char)'ð': nq('p'); break;
	case (unsigned char)'ñ': nq('r'); break;
	case (unsigned char)'ó': nq('s'); break;
	case (unsigned char)'ò': nq('s'); break;
	case (unsigned char)'ô': nq('t'); break;
	case (unsigned char)'õ': nq('y'); break;
	case (unsigned char)'ý': nq('y'); nq('\''); break;
	case (unsigned char)'û': nq('y'); nq('\''); nq('\''); break;
	case (unsigned char)'à': nq('y'); nq('\''); nq('\''); nq('\''); break;
	case (unsigned char)'ö': nq('f'); break;
	case (unsigned char)'÷': nq('c'); nq('h'); break;
	case (unsigned char)'ø': nq('p'); nq('s'); break;
	case (unsigned char)'ù': nq('o'); nq('_'); break;
	case (unsigned char)'þ': nq('o'); nq('_'); nq('\''); break;
	case (unsigned char)';': nq('?'); break;
	default: nq(c); break;
	}
}
