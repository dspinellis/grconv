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
 * $Id: ucs2i.h,v 1.4 2000/07/14 13:10:57 dds Exp $
 */

#ifndef UCS2I_
#define UCS2I_
#include "filter.h"

class ucs2i: public filter {
private:
	bool bof;		// At beginning of file
	enum {BIG, LITTLE} endian;
public:
	virtual int owidth() { return (16); };		// Output char width
	ucs2i()
	{
		bof = true;
		endian = BIG;
	};

	int getcharacter()
	{
		int c1, c2, r;
	again:
		c1 = input->getcharacter();
		if (c1 == EOF)
			return (EOF);
		c2 = input->getcharacter();
		if (c2 == EOF)
			fatal("EOF within a UCS-16 pair\n");
		switch (endian) {
			case BIG: r =  (c1 << 8) | c2; break;
			case LITTLE: r =  (c2 << 8) | c1; break;
		}
		if (bof)
			if (r == 0xfffe) {
				endian = LITTLE;
				bof = false;
				goto again;
			} else if (r == 0xfeff) {
				endian = BIG;
				bof = false;
				goto again;
			}
		if (r == 0xfffe)
			fatal("Invalid byte ordering signature in UCS-16 input\n");
		return (r);
	}
};
#endif
