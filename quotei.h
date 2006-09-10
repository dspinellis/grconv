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
 * $Id: quotei.h,v 1.3 2006/09/10 14:36:31 dds Exp $
 */

#ifndef QUOTEI_
#define QUOTEI_
#include "filter.h"
#include <string.h>

// See RFC 1521
class quotei: public filter {
private:
	bool eatnl;
	inline int hexval(char c)
	{
		char *hex = "0123456789ABCDEF";
		char *s;

		if ((s = strchr(hex, c)) == NULL)
			fatal("Non-hex digit in quoted escape\n");
		return (s - hex);
	}
public:
	int getcharacter()
	{
		int c;
		int c1, c2;

	again:
		c = input->getcharacter();
		if (eatnl && c == '\n') {
			eatnl = false;
			goto again;
		}
		// See if quoted escape
		if (c != '=')
			return (c);			// Includes EOF

		c1 = input->getcharacter();
		if (c1 == '\r') {
			eatnl = true;
			goto again;			// Soft break
		}
		if (c1 == '\n')
			goto again;			// Soft break
		c2 = input->getcharacter();
		if (c1 == EOF || c2 == EOF)
			fatal("EOF within quoted escape character\n");
		return (hexval(c1) << 4 | hexval(c2));
        }
};
#endif
