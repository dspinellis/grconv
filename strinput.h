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
 * $Id: strinput.h,v 1.1 2000/05/06 15:05:17 dds Exp $
 */

#ifndef STRINPUT_
#define STRINPUT_
#include "filter.h"
#include <fstream.h>
#include <errno.h>

class strinput: public filter {
private:
	char *string;
	unsigned char *p;		// Pointer in the string
public:
	void rewind()
	{
		p = (unsigned char *)string;
	}
	strinput(const char *s)
	{
		string = new char[strlen(s) + 1];
		strcpy(string, s);
		rewind();
	}
	int getcharacter()
	{
		if (*p)
			return (*p++);
		else
			return (EOF);
	};
};
#endif
