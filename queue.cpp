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
 * $Id: queue.cpp,v 1.2 2006/09/10 14:30:00 dds Exp $
 */

#include <iostream>
using namespace std;

#include "queue.h"

queue::queue(int qlen)
{
	q = new int[qlen];
	qhead = qtail = 0;
	queue::qlen = qlen;
}

void
queue::nq(int c)
{
	q[qtail++] = c;
	if (qtail == qlen)
		qtail = 0;
}

int
queue::getcharacter()
{
	int c;

	while (qtail == qhead)
		fillbuff();
	c = q[qhead++];
	if (qhead == qlen)
		qhead = 0;
	return c;
}
