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
 * $Id: ucs16beo.h,v 1.1 2000/07/14 13:04:18 dds Exp $
 */

#ifndef UCS16BEO_
#define UCS16BEO_
#include "filter.h"
#include "queue.h"

class ucs16beo: public filter, public queue {
private:
	void fillbuff()		 // Fill the queue buffer
	{
		int c;

		c = input->getcharacter();
		if (c != EOF) {
			nq(c >> 8);
			nq(c & 0xff);
		} else
			nq(EOF);
	}
public:
	virtual int iwidth() { return (16); };		// Input char width
	int getcharacter() { return (queue::getcharacter()); };
	void header() { nq(0xfe); nq(0xff); };
};
#endif
