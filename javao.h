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
 * $Id: javao.h,v 1.2 2000/05/06 19:27:11 dds Exp $
 */

#ifndef JAVAO_
#define JAVAO_
#include "filter.h"
#include "queue.h"

#include <stdio.h>

// Java and C++ (2.2. Basic source character set) Unicode encodings
class javao: public filter, public queue {
private:
	void fillbuff()		 // Fill the queue buffer
	{
		int c;

		c = input->getcharacter();
		if (c == EOF)
			nq(EOF);
		else if (c < 0x80)
			nq(c);
		else {
			char buff[10];

			sprintf(buff, "\\u%04x", c);
			for (char *s = buff; *s; s++)
				nq(*s);
		}
	}
public:
	virtual int iwidth() { return (16); };		// Input char width
	int getcharacter() { return (queue::getcharacter()); };
};
#endif
