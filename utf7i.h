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
 * $Id: utf7i.h,v 1.1 2000/03/12 13:26:19 dds Exp $
 */

#ifndef UTF7I_
#define UTF7I_
#include "filter.h"
#include "queue.h"
#include "utf7.h"

// See RFC 1642
class utf7i: public filter, public queue, public utf7 {
private:
	void fillbuff();
	int shifted, first, wroteone;
public:
	utf7i() { shifted = first = wroteone = 0; };
	int getcharacter() { return (queue::getcharacter()); };
};
#endif
