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
 * $Id: stdinput.h,v 1.4 2012/04/25 10:11:08 dds Exp $
 */

#ifndef STDINPUT_
#define STDINPUT_
#include "filter.h"
#include <iostream>
#include <fstream>
#include <errno.h>

using namespace std;

class stdinput: public filter {
private:
	ifstream *in;
	char **argv;
	void openargfile()
	{
		if (in) {
			in->close();
			delete in;
		}
		in = new ifstream(*argv);
		if (!in->good()) {
			error("Unable to open input file ");
			cerr << *argv << ": " << strerror(errno) << "\n";
			exit(1);
		}
		argv++;
	}
public:
	stdinput() { in = NULL; };
	void
	setargs(char **a)
	{
		argv = a;
		if (*argv)
			openargfile();
	};
	int getcharacter()
	{
		unsigned char c;
		if (in) {
			for (;;) {
				c = in->get();
				if (in->eof())
					if (*argv)
						openargfile();
					else
						return (EOF);
				else
					return (c);
			}
		} else {
			c = cin.get();
			return (cin.eof() ? EOF : c);
		}
	};
};
#endif
