/* 
 * (C) Copyright 2001 Diomidis Spinellis.
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
 * $Id: betao.h,v 1.1 2001/02/13 10:50:05 dds Exp $
 */

#ifndef BETAO_
#define BETAO_
#include "filter.h"
#include "queue.h"

class betao: public filter, public queue {
private:
	void fillbuff();		 // Fill the queue buffer
public:
	int getcharacter() { return (queue::getcharacter()); };
};
#endif
