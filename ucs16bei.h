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
 * $Id: ucs16bei.h,v 1.1 2000/07/14 13:04:18 dds Exp $
 */

#ifndef UCS16BEI_
#define UCS16BEI_
#include "filter.h"

class ucs16bei: public filter {
public:
	virtual int owidth() { return (16); };		// Output char width
	int getcharacter()
	{
		int c1, c2, r;

		c1 = input->getcharacter();
		if (c1 == EOF)
			return (EOF);
		c2 = input->getcharacter();
		if (c2 == EOF)
			fatal("EOF within a UCS-2 pair\n");
		r =  (c1 << 8) | c2;
		if (r == 0xfffe)
			fatal("Invalid byte ordering signature in UCS-16BE input\n");
		return (r);
	}
};
#endif
