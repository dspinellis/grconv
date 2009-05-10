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
 * $Id: urlo.h,v 1.1 2009/05/10 19:13:31 dds Exp $
 */

#ifndef URLO_
#define URLO_
#include "filter.h"
#include "queue.h"
#include "utf8o.h"

#include <stdio.h>

// See RFC 1521
class urlo: public filter, public queue {
private:
	void fillbuff()		 // Fill the queue buffer
	{
		int c;

		c = input->getcharacter();
		if (c < 128)
			nq(c);
		else {
			char buff[10];

			if (c > 255)
				error("Character > 255 in URL output\n");
			sprintf(buff, "%%%02X", c);
			for (char *s = buff; *s; s++)
				nq(*s);
		}
	}
public:
	virtual int iwidth() { return (16); };		// Input char width
	int getcharacter() { return (queue::getcharacter()); };
};
#endif
