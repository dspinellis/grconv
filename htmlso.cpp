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
 * $Id: htmlso.cpp,v 1.1 2000/04/19 10:54:10 dds Exp $
 */

#include "filter.h"
#include "queue.h"
#include "htmlso.h"

void
htmlso::fillbuff()
{
	unsigned int c;
	char *out;

	// See http://www.w3.org/TR/html4/sgml/entities.html
	switch (c = input->getcharacter()) {
	case 193: out = "Alpha"; break; 
	case 194: out = "Beta"; break; 
	case 195: out = "Gamma"; break; 
	case 196: out = "Delta"; break; 
	case 197: out = "Epsilon"; break; 
	case 198: out = "Zeta"; break; 
	case 199: out = "Eta"; break; 
	case 200: out = "Theta"; break; 
	case 201: out = "Iota"; break; 
	case 202: out = "Kappa"; break; 
	case 203: out = "Lambda"; break; 
	case 204: out = "Mu"; break; 
	case 205: out = "Nu"; break; 
	case 206: out = "Xi"; break; 
	case 207: out = "Omicron"; break; 
	case 208: out = "Pi"; break; 
	case 209: out = "Rho"; break; 
	case 211: out = "Sigma"; break; 
	case 212: out = "Tau"; break; 
	case 213: out = "Upsilon"; break; 
	case 214: out = "Phi"; break; 
	case 215: out = "Chi"; break; 
	case 216: out = "Psi"; break; 
	case 217: out = "Omega"; break; 
	case 225: out = "alpha"; break; 
	case 226: out = "beta"; break; 
	case 227: out = "gamma"; break; 
	case 228: out = "delta"; break; 
	case 229: out = "epsilon"; break; 
	case 230: out = "zeta"; break; 
	case 231: out = "eta"; break; 
	case 232: out = "theta"; break; 
	case 233: out = "iota"; break; 
	case 234: out = "kappa"; break; 
	case 235: out = "lambda"; break; 
	case 236: out = "mu"; break; 
	case 237: out = "nu"; break; 
	case 238: out = "xi"; break; 
	case 239: out = "omicron"; break;  
	case 240: out = "pi"; break; 
	case 241: out = "rho"; break; 
	case 242: out = "sigmaf"; break; 
	case 243: out = "sigma"; break; 
	case 244: out = "tau"; break; 
	case 245: out = "upsilon"; break; 
	case 246: out = "phi"; break; 
	case 247: out = "chi"; break; 
	case 248: out = "psi"; break; 
	case 249: out = "omega"; break; 
	default: nq(c); return;
	}
	nq('&');
	for (char *s = out; *s; s++)
		nq(*s);
	nq(';');
}
