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
 * $Id: base64i.h,v 1.1 2000/03/12 13:26:19 dds Exp $
 */

#ifndef BASE64I_
#define BASE64I_
#include "filter.h"
#include "utf7.h"

// See RFC 1521
class base64i: public filter, public utf7 {
public:
	int getcharacter()
	{
		int c;
		int bv;

		for (;;) {
			c = input->getcharacter();
			if (c == EOF)
				return (EOF);
			if (c > 127 || (bv = invbase64[c]) == -1)
				continue;		// Ignore non-base64 characters
			write_n_bits(bv, 6);
			if (bufferbits >= 8)
				return (read_n_bits(8));
		}
	}
};
#endif
