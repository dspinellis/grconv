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
 * $Id: javai.h,v 1.1 2000/03/12 13:26:19 dds Exp $
 */

#ifndef JAVAI_
#define JAVAI_
#include "filter.h"

#include <ctype.h>
#include <string.h>

// Unicode characters as coded as \uxxxx

class javai: public filter {
private:
	int pushed_char;
public:
	javai() { pushed_char = EOF; }

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
		// See if escape
		if (c != '\\')
			return (c);			// Includes EOF

		c = input->getcharacter();
		// See if universal character reference
		if (c != 'u') {
			pushed_char = c;
			return ('\\');
		}

		// Universal character reference
		char buff[5];

		for (int i = 0; i < 4; i++) {

			c = input->getcharacter();
			if (c == EOF)
				fatal("EOF in universal character sequence");
			buff[i] = c;
		}
		buff[4] = '\0';

		char *s;
		int r = strtol(buff, &s, 16);
		if (s != buff + 4)
			fatal("Invalid characters in universal character sequence");
		return (r);
	}
};
#endif
