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
 * $Id: htmlo.h,v 1.1 2000/03/12 13:26:19 dds Exp $
 */

#ifndef HTMLO_
#define HTMLO_
#include "filter.h"
#include "queue.h"

#include <stdio.h>

// See RFC 2070
class htmlo: public filter, public queue {
private:
	void fillbuff()		 // Fill the queue buffer
	{
		int c;
		char buff[10];

		c = input->getcharacter();
		if (c == EOF)
			nq(EOF);
		// This test might not be valid for some HTML contexts
		else if (c < 0x80 && c != '&' && c != '<') 
			nq(c);
		else {
			sprintf(buff, "&#%d;", c);
			for (char *s = buff; *s; s++)
				nq(*s);
		}
	}
public:
	int getcharacter() { return (queue::getcharacter()); };

	void header()
	{
		cout <<
			"<head>\n"
			"<META HTTP-EQUIV=\"Content-type\" CONTENT=\"text/html; charset="
			<< input->outputcs() << "\">\n"
			"</head>\n"
			"<body>\n"
			"<pre>\n";
	}

	void footer()
	{
		cout << "\n</pre>\n</body>\n";
	}
};
#endif
