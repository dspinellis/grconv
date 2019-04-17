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
 * $Id: htmll1o.cpp,v 1.1 2000/03/12 13:26:19 dds Exp $
 */

#include "filter.h"
#include "queue.h"
#include "htmll1o.h"

void
htmll1o::fillbuff()
{
	unsigned int c;
	const char *out;

	// See RFC2070
	switch (c = input->getcharacter()) {
	case 160: out = "nbsp"; break;
	case 161: out = "iexcl"; break;
	case 162: out = "cent"; break;
	case 163: out = "pound"; break;
	case 164: out = "curren"; break;
	case 165: out = "yen"; break;
	case 166: out = "brvbar"; break;
	case 167: out = "sect"; break;
	case 168: out = "uml"; break;
	case 169: out = "copy"; break;
	case 170: out = "ordf"; break;
	case 171: out = "laquo"; break;
	case 172: out = "not"; break;
	case 173: out = "shy"; break;
	case 174: out = "reg"; break;
	case 175: out = "macr"; break;
	case 176: out = "deg"; break;
	case 177: out = "plusmn"; break;
	case 178: out = "sup2"; break;
	case 179: out = "sup3"; break;
	case 180: out = "acute"; break;
	case 181: out = "micro"; break;
	case 182: out = "para"; break;
	case 183: out = "middot"; break;
	case 184: out = "cedil"; break;
	case 185: out = "sup1"; break;
	case 186: out = "ordm"; break;
	case 187: out = "raquo"; break;
	case 188: out = "frac14"; break;
	case 189: out = "frac12"; break;
	case 190: out = "frac34"; break;
	case 191: out = "iquest"; break;
	case 192: out = "Agrave"; break;
	case 193: out = "Aacute"; break;
	case 194: out = "Acirc"; break;
	case 195: out = "Atilde"; break;
	case 196: out = "Auml"; break;
	case 197: out = "Aring"; break;
	case 198: out = "AElig"; break;
	case 199: out = "Ccedil"; break;
	case 200: out = "Egrave"; break;
	case 201: out = "Eacute"; break;
	case 202: out = "Ecirc"; break;
	case 203: out = "Euml"; break;
	case 204: out = "Igrave"; break;
	case 205: out = "Iacute"; break;
	case 206: out = "Icirc"; break;
	case 207: out = "Iuml"; break;
	case 208: out = "ETH"; break;
	case 209: out = "Ntilde"; break;
	case 210: out = "Ograve"; break;
	case 211: out = "Oacute"; break;
	case 212: out = "Ocirc"; break;
	case 213: out = "Otilde"; break;
	case 214: out = "Ouml"; break;
	case 215: out = "times"; break;
	case 216: out = "Oslash"; break;
	case 217: out = "Ugrave"; break;
	case 218: out = "Uacute"; break;
	case 219: out = "Ucirc"; break;
	case 220: out = "Uuml"; break;
	case 221: out = "Yacute"; break;
	case 222: out = "THORN"; break;
	case 223: out = "szlig"; break;
	case 224: out = "agrave"; break;
	case 225: out = "aacute"; break;
	case 226: out = "acirc"; break;
	case 227: out = "atilde"; break;
	case 228: out = "auml"; break;
	case 229: out = "aring"; break;
	case 230: out = "aelig"; break;
	case 231: out = "ccedil"; break;
	case 232: out = "egrave"; break;
	case 233: out = "eacute"; break;
	case 234: out = "ecirc"; break;
	case 235: out = "euml"; break;
	case 236: out = "igrave"; break;
	case 237: out = "iacute"; break;
	case 238: out = "icirc"; break;
	case 239: out = "iuml"; break;
	case 240: out = "eth"; break;
	case 241: out = "ntilde"; break;
	case 242: out = "ograve"; break;
	case 243: out = "oacute"; break;
	case 244: out = "ocirc"; break;
	case 245: out = "otilde"; break;
	case 246: out = "ouml"; break;
	case 247: out = "divide"; break;
	case 248: out = "oslash"; break;
	case 249: out = "ugrave"; break;
	case 250: out = "uacute"; break;
	case 251: out = "ucirc"; break;
	case 252: out = "uuml"; break;
	case 253: out = "yacute"; break;
	case 254: out = "thorn"; break;
	case 255: out = "yuml"; break;
	default: nq(c); return;
	}
	nq('&');
	for (const char *s = out; *s; s++)
		nq(*s);
	nq(';');
}
