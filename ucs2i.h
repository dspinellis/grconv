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
 * $Id: ucs2i.h,v 1.2 2000/05/06 19:27:11 dds Exp $
 */

#ifndef UCS2I_
#define UCS2I_
#include "filter.h"

class ucs2i: public filter {
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
		return ((c1 << 8) | c2);
	}
};
#endif
