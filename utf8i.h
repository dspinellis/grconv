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
 * $Id: utf8i.h,v 1.1 2000/03/12 13:26:19 dds Exp $
 */

#ifndef UTF8I_
#define UTF8I_
#include "filter.h"

class utf8i: public filter {
public:
	int getcharacter()
	{
		int c1, c2, c3, c4;
		int cout;

		c1 = input->getcharacter();
		if (c1 == EOF)
			return (EOF);
		if ((c1 & 0x80) == 0) {
			cout = c1;
		} else if ((c1 & 0xe0) == 0xc0) {
			c2 = input->getcharacter();
			cout = (c2 & 0x3f) | ((c1 & 0x1f) << 6);
		} else if ((c1 & 0xf0) == 0xe0) {
			c2 = input->getcharacter();
			c3 = input->getcharacter();
			cout = ((c1 & 0xf) << 12) |
			       ((c2 & 0x3f) << 6) |
			       (c3 & 0x3f);
		} else {
			error("UTF-8 input: UCS characters above 0xffff are not supported\n");
		}
		return (cout);
	}
};
#endif
