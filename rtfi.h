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
 * $Id: rtfi.h,v 1.1 2000/03/12 13:26:19 dds Exp $
 */

#ifndef RTFI_
#define RTFI_
#include "filter.h"

#include <ctype.h>

class rtfi: public filter {
private:
	int pushed_char;
	inline int hexval(char c)
	{
		char *hex = "0123456789abcdef";
		char *s;

		if ((s = strchr(hex, c)) == NULL)
			fatal("Non-hex digit in RTF escape\n");
		return (s - hex);
	}
public:
	rtfi() { pushed_char = EOF; }

	int getcharacter()
	{
		int c;

		// See if we owe a character
		if (pushed_char != EOF) {
			int r = pushed_char;
			pushed_char = EOF;
			return (r);
		}

		c = input->getcharacter();
		// See if RTF escape
		if (c != '\\')
			return (c);			// Includes EOF

		c = input->getcharacter();
		// See if numeric character reference
		if (c != '\'') {
			pushed_char = c;
			return ('\\');
		}

		int c1, c2;
		c1 = input->getcharacter();
		c2 = input->getcharacter();
		if (c1 == EOF || c2 == EOF)
			fatal("EOF within quoted RTF character\n");
		return (hexval(c1) << 4 | hexval(c2));
	}
};
#endif
