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
 * $Id: betao.cpp,v 1.1 2001/02/13 10:50:05 dds Exp $
 */

#include "filter.h"
#include "queue.h"
#include "betao.h"

void
betao::fillbuff()
{
	unsigned int c;
	char *out;

	switch (c = input->getcharacter()) {
	case 162: out = "*/A"; break;
	case 184: out = "*/E"; break;
	case 185: out = "*/H"; break;
	case 186: out = "*/I"; break;
	case 188: out = "*/O"; break;
	case 190: out = "*/U"; break;
	case 191: out = "*/W"; break;
	case 192: out = "I/+"; break;
	case 193: out = "*A"; break;
	case 194: out = "*B"; break;
	case 195: out = "*G"; break;
	case 196: out = "*D"; break;
	case 197: out = "*E"; break;
	case 198: out = "*Z"; break;
	case 199: out = "*H"; break;
	case 200: out = "*Q"; break;
	case 201: out = "*I"; break;
	case 202: out = "*K"; break;
	case 203: out = "*L"; break;
	case 204: out = "*M"; break;
	case 205: out = "*N"; break;
	case 206: out = "*C"; break;
	case 207: out = "*O"; break;
	case 208: out = "*P"; break;
	case 209: out = "*R"; break;
	case 211: out = "*S"; break;
	case 212: out = "*T"; break;
	case 213: out = "*U"; break;
	case 214: out = "*F"; break;
	case 215: out = "*X"; break;
	case 216: out = "*Y"; break;
	case 217: out = "*W"; break;
	case 218: out = "*+I"; break;
	case 219: out = "*+U"; break;
	case 220: out = "A/"; break;
	case 221: out = "E/"; break;
	case 222: out = "H/"; break;
	case 223: out = "I/"; break;
	case 224: out = "U/+"; break;
	case 225: out = "A"; break;
	case 226: out = "B"; break;
	case 227: out = "G"; break;
	case 228: out = "D"; break;
	case 229: out = "E"; break;
	case 230: out = "Z"; break;
	case 231: out = "H"; break;
	case 232: out = "Q"; break;
	case 233: out = "I"; break;
	case 234: out = "K"; break;
	case 235: out = "L"; break;
	case 236: out = "M"; break;
	case 237: out = "N"; break;
	case 238: out = "C"; break;
	case 239: out = "O"; break;
	case 240: out = "P"; break;
	case 241: out = "R"; break;
	case 242: out = "S"; break;
	case 243: out = "S"; break;
	case 244: out = "T"; break;
	case 245: out = "U"; break;
	case 246: out = "F"; break;
	case 247: out = "X"; break;
	case 248: out = "Y"; break;
	case 249: out = "W"; break;
	case 250: out = "I+"; break;
	case 251: out = "U+"; break;
	case 252: out = "O/"; break;
	case 253: out = "U/"; break;
	case 254: out = "W/"; break;
	default: nq(c); return;
	}
	for (char *s = out; *s; s++)
		nq(*s);
}
