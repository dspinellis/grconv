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
 * $Id: stdinput.h,v 1.1 2000/03/12 12:26:19 dds Exp $
 */

#ifndef STDINPUT_
#define STDINPUT_
#include "filter.h"
#include <fstream.h>
#include <errno.h>

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
		if (in->bad()) {
			error("Unable to open input file ");
			cerr << *argv << ": " << strerror(errno) << "\n";
			exit(1);
		}
		argv++;
	}
public:
	stdinput() { in = NULL; };
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
				in->get(c);
				if (in->eof())
					if (*argv)
						openargfile();
					else
						return (EOF);
				else
					return (c);
			}
		} else {
			cin.get(c);
			return (cin.eof() ? EOF : c);
		}
	};
};
#endif
