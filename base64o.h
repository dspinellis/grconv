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
 * $Id: base64o.h,v 1.1 2000/03/12 13:26:19 dds Exp $
 */

#ifndef BASE64O_
#define BASE64O_
#include "filter.h"
#include "queue.h"
#include "utf7.h"

// See RFC 1521
class base64o: public filter, public utf7, public queue {
private:
	int outcount;

	inline void nqnl(char c)
	{
		if (outcount++ == 76) {
			nq('\n');
			outcount = 0;
		}
		nq(c);
	}

	void fillbuff()
	{
		int c, pad;

		c = input->getcharacter();
		if (c > 255)
			error("Character > 255 in base64 output\n");
		if (c == EOF) {
			switch (bufferbits) {
			case 0: pad = 0; break;
			case 2: pad = 2; break;
			case 4: pad = 1; break;
			}
			if (bufferbits % 6)
				write_n_bits(0, 6 - (bufferbits % 6));
			while (bufferbits >= 6)
				nqnl(base64[read_n_bits(6)]);
			for (int i = 0; i < pad; i++)
				nq('=');
			nq(EOF);
			return;
		}
		write_n_bits(c, 8);
		while (bufferbits >= 6)
			nqnl(base64[read_n_bits(6)]);
	}
public:
	base64o() { outcount = 0; };
	int getcharacter() { return (queue::getcharacter()); };

	void header()
	{
		cout << "Content-Type: Text/plain; charset=" << input->outputcs() << "\n";
		cout << "Content-transfer-encoding: BASE64\n\n";
	}
};
#endif
