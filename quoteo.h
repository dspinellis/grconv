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
 * $Id: quoteo.h,v 1.1 2000/03/12 13:26:19 dds Exp $
 */

#ifndef QUOTEO_
#define QUOTEO_
#include "filter.h"
#include "queue.h"

#include <stdio.h>

// See RFC 1521
class quoteo: public filter, public queue {
private:
	int outcount;
	int lastchar;

	inline void softbreak()
	{
		nq('=');		// Soft line break
		nq('\n');
		outcount = 0;
	}

	inline void nqnl(char c)
	{
		if (outcount++ >= 76 - 4)
			softbreak();
		nq(c);
	}

	void fillbuff()		 // Fill the queue buffer
	{
		int c;

		c = input->getcharacter();
		if ((c >= 33 && c <= 60) || (c >= 62 && c <= 126)) {
			nqnl(c);
		} else if (c == EOF) {
			nq(EOF);
		} else if (c == '\n') {
			// Make sure space does not apper at the end of a line
			if (lastchar == ' ' || lastchar == '\t')
				softbreak();
			nq(c);
		} else if (c == ' ' || c == '\t') {
			nqnl(c);
		} else {
			char buff[10];

			if (c > 255)
				error("Character > 255 in quoted printable output\n");
			sprintf(buff, "=%02X", c);
			for (char *s = buff; *s; s++)
				nq(*s);
			if ((outcount += 3) >= 76 - 4)
				softbreak();
		}
		lastchar = c;
	}
public:
	int getcharacter() { return (queue::getcharacter()); };
	quoteo() { lastchar = outcount = 0; };

	void header()
	{
		cout << "Content-Type: Text/plain; charset=" << input->outputcs() << "\n";
		cout << "Content-transfer-encoding: Quoted-Printable\n\n";
	}
};
#endif
