/* 
 * (C) Copyright 2009 Diomidis Spinellis.
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
 * $Id: urli.h,v 1.1 2009/05/10 19:13:31 dds Exp $
 */

#ifndef URLI_
#define URLI_
#include "filter.h"
#include "utf8i.h"
#include <string.h>

// See RFC 1521
class urli: public filter {
private:
	inline int hexval(char c)
	{
		const char *hex = "0123456789ABCDEF";
		const char *s;

		if ((s = strchr(hex, c)) == NULL)
			fatal("Non-hex digit in quoted escape\n");
		return (s - hex);
	}
public:
	virtual int owidth() { return (16); };		// Output char width
	int getcharacter()
	{
		int c;
		int c1, c2;

		c = input->getcharacter();
		// See if quoted escape
		if (c != '%')
			return (c);			// Includes EOF

		c1 = input->getcharacter();
		c2 = input->getcharacter();
		if (c1 == EOF || c2 == EOF)
			fatal("EOF within quoted escape character\n");
		return (hexval(c1) << 4 | hexval(c2));
        }
};
#endif
