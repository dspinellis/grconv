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
 * $Id: queue.h,v 1.1 2000/03/12 13:26:19 dds Exp $
 */

#ifndef QUEUE_
#define QUEUE_
#include "filter.h"

class queue {
private:
	int *q;			// Output queue
	int qlen;		// Characters in output queue
	int qhead;
	int qtail;
	virtual void fillbuff() = 0;	// Fill the queue buffer
public:
	void nq(int c);		// Add a character to the output queue
	unsigned int getcharacter();	// Get a character from the output queue
	queue(const int qlen = 100);
	~queue() { delete[] q; };
};
#endif
