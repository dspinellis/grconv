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
 * $Id: utf7o.h,v 1.2 2000/05/06 19:27:11 dds Exp $
 */

#ifndef UTF7O_
#define UTF7O_
#include "filter.h"
#include "queue.h"
#include "utf7.h"

// See RFC 1642
class utf7o: public filter, public queue, public utf7 {
private:
	char *mustshift;
	int shifted, needshift, done;

	void fillbuff();
public:
	int getcharacter() { return (queue::getcharacter()); };
	virtual int iwidth() { return (16); };		// Input char width
	void optional(bool opt);
	utf7o()
	{ 
		mustshift = mustshiftopt;
		shifted = needshift = done = 0;
	}

	void header()
	{
		cout << "Content-Type: Text/plain; charset=UNICODE-1-1-UTF-7\n";
		cout << "Content-transfer-encoding: 7BIT\n\n";
	}
};
#endif
