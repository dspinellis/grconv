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
 * $Id: rtfo.h,v 1.1 2000/03/12 13:26:19 dds Exp $
 */

#ifndef RTFO_
#define RTFO_
#include "filter.h"
#include "queue.h"

#include <stdio.h>

class rtfo: public filter, public queue {
private:
	int outcount;

	inline void nqsnl(const char *s)
	{
		for (;*s; s++) {
			nq(*s);
			outcount++;
		}
		if (outcount++ >= 250) {
			outcount = 0;
			nq('\n');
		}
	}
	inline void nqnl(char c)
	{
		if (outcount++ >= 250) {
			nq('\n');
			outcount = 0;
		}
		nq(c);
	}

	void fillbuff()		 // Fill the queue buffer
	{
		int c;

		c = input->getcharacter();
		if (c == '{')
			nqsnl("\\{");
		else if (c == '}')
			nqsnl("\\}");
		else if (c == '\\')
			nqsnl("\\\\");
		else if (c == '\n')
			nqsnl("\\par ");
		else if (c == '\t')
			nqsnl("\\tab ");
		else if (c == EOF)
			nq(EOF);
		else if (c > 127 || c < 32) {
			char buff[10];

			if (c > 255)
				error("Character > 255 in RTF output\n");
			sprintf(buff, "\\'%02x", c);
			nqsnl(buff);
		} else
			nqnl(c);
	}
public:
	int getcharacter() { return (queue::getcharacter()); };
	rtfo() { outcount = 0; };

	void header()
	{
		cout << "{\\rtf1\\ansi\\ansicpg1253\\uc1 {\\lang1032 \\f62\n";
	}

	void footer()
	{
		cout << "}}\n";
	}
};
#endif
