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
 * $Id: utf8o.h,v 1.1 2000/03/12 13:26:19 dds Exp $
 */

#ifndef UTF8O_
#define UTF8O_
#include "filter.h"
#include "queue.h"

class utf8o: public filter, public queue {
private:
	void fillbuff()		 // Fill the queue buffer
	{
		unsigned int c;

		c = input->getcharacter();
		if (c == EOF) {
			nq(EOF);
			return;
		}
		if (c < 0x80) {
			nq(c);
		} else if (c < 0x800) {			// bbb bbbb bbbb
			nq(0xC0 | c>>6);		// 110b bbbb
			nq(0x80 | c & 0x3F);		// 10bb bbbb
		} else if (c < 0x10000) {		// bbbb bbbb bbbb bbbb
			nq(0xE0 | c>>12);		// 1110 bbbb
			nq(0x80 | c>>6 & 0x3F);		// 10bb bbbb
			nq(0x80 | c & 0x3F);		// 10bb bbbb
		} else {
			error("UCS characters above 0xffff are not supported\n");
		}
	}
public:
	int getcharacter() { return (queue::getcharacter()); };

	void header()
	{
		cout << "Content-Type: Text/plain; charset=UNICODE-1-1-UTF-8\n";
		cout << "Content-transfer-encoding: 8BIT\n\n";
	}
};
#endif
