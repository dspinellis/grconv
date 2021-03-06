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
 * $Id: filter.h,v 1.3 2012/04/25 10:08:54 dds Exp $
 */

#ifndef FILTER_
#define FILTER_

class filter {
protected:
	filter *input;
public:
	virtual int getcharacter() = 0;
	virtual void header() {};
	virtual void footer() {};
	virtual int iwidth() { return (8); };		// Input char width
	virtual int owidth() { return (8); };		// Output char width
	void setinput(filter *i) {input = i;};
	virtual const char *outputcs() { return "X-Unknown"; };	// Output character set
};
#endif
