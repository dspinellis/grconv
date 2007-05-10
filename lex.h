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
 * $Id: lex.h,v 1.3 2007/05/10 08:27:01 dds Exp $
 */

#ifndef LEX_
#define LEX_
#include "filter.h"
#include "queue.h"

#ifdef _WIN32
#define isatty(x) 0
#else
extern "C" int isatty(int);
#endif


class lex: public filter, public queue {
private:
	void (*lexfun)(lex *lf);
	void fillbuff() { lexfun(this); }; // Fill the queue buffer
public:
	lex(void (*lf)(lex *l)) { lexfun = lf; };
	inline int getinputcharacter() { return input->getcharacter(); };
	int getcharacter() { return (queue::getcharacter()); };

	// Most of our lex files are coded using this
	char *outputcs() { return ("Windows-1253"); };
};
#endif
