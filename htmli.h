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
 * $Id: htmli.h,v 1.1 2000/03/12 13:26:19 dds Exp $
 */

#ifndef HTMLI_
#define HTMLI_
#include "filter.h"

#include <ctype.h>

// See RFC 2070
class htmli: public filter {
private:
	int pushed_char;
public:
	htmli() { pushed_char = EOF; }

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
		// See if HTML escape
		if (c != '&')
			return (c);			// Includes EOF

		c = input->getcharacter();
		// See if numeric character reference
		if (c != '#') {
			pushed_char = c;
			return ('&');
		}

		// Numeric character reference
		int i = 0;
		int n = 0;

		for (;;) {
			c = input->getcharacter();
			if (c == ';') {
				if (i == 0)
					fatal("Empty HTML numeric character reference");
				return (n);
			}
			i++;
			n *= 10;
			if (!isdigit(c))
				fatal("Non-digit in HTML numeric character reference");
			n += c - '0';
		}
	}
};
#endif
