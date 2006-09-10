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
 * $Id: utf7i.cpp,v 1.2 2006/09/10 14:40:23 dds Exp $
 */

/*
 * This C++ code is based on C code containing the copyright message
 * that follows.  Converted to C++ classes by D. Spinellis.
 */

/*
File:   ConvertUTF7.c
Author: David B. Goldsmith
Copyright (C) 1994, 1996 Taligent, Inc. All rights reserved.

This code is copyrighted. Under the copyright laws, this code may not
be copied, in whole or part, without prior written consent of Taligent. 

Taligent grants the right to use this code as long as this ENTIRE
copyright notice is reproduced in the code.  The code is provided
AS-IS, AND TALIGENT DISCLAIMS ALL WARRANTIES, EITHER EXPRESS OR
IMPLIED, INCLUDING, BUT NOT LIMITED TO IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT
WILL TALIGENT BE LIABLE FOR ANY DAMAGES WHATSOEVER (INCLUDING,
WITHOUT LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS
INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY
LOSS) ARISING OUT OF THE USE OR INABILITY TO USE THIS CODE, EVEN
IF TALIGENT HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
BECAUSE SOME STATES DO NOT ALLOW THE EXCLUSION OR LIMITATION OF
LIABILITY FOR CONSEQUENTIAL OR INCIDENTAL DAMAGES, THE ABOVE
LIMITATION MAY NOT APPLY TO YOU.

RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the
government is subject to restrictions as set forth in subparagraph
(c)(l)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 252.227-7013 and FAR 52.227-19.

This code may be protected by one or more U.S. and International
Patents.

TRADEMARKS: Taligent and the Taligent Design Mark are registered
trademarks of Taligent, Inc.
*/

#include <iostream>

using namespace std;

#include "error.h"
#include "filter.h"
#include "utf7.h"
#include "utf7i.h"

void
utf7i::fillbuff()		 // Fill the queue buffer
{
	int base64EOF, base64value, done;
	unsigned int c, prevc;
	unsigned long junk;

	/* read an ASCII character c */
	c = input->getcharacter();
	done = (c == EOF);
	if (shifted) {
		/* We're done with a base64 string if we hit EOF, it's not a valid
		   ASCII character, or it's not in the base64 set.
		 */
		base64EOF = done || (c > 0x7f) || (base64value = invbase64[c]) < 0;
		if (base64EOF) {
			shifted = 0;
			/* If the character causing us to drop out was SHIFT_IN or
			   SHIFT_OUT, it may be a special escape for SHIFT_IN. The
			   test for SHIFT_IN is not necessary, but allows an alternate
			   form of UTF-7 where SHIFT_IN is escaped by SHIFT_IN. This
			   only works for some values of SHIFT_IN.
			 */
			if (!done && (c == SHIFT_IN || c == SHIFT_OUT)) {
				/* get another character c */
				prevc = c;
				c = input->getcharacter();
				done = (c == EOF);
				/* If no base64 characters were encountered, and the
				   character terminating the shift sequence was
				   SHIFT_OUT, then it's a special escape for SHIFT_IN.
				 */
				if (first && prevc == SHIFT_OUT)
					/* write SHIFT_IN unicode */
					nq(SHIFT_IN);
				else if (!wroteone)
					fatal("UTF-7: empty sequence near in input\n");
			} else if (!wroteone)
				fatal("UTF-7: empty sequence near in input\n");
		} else {
			/* Add another 6 bits of base64 to the bit buffer. */
			write_n_bits(base64value, 6);
			first = 0;
		}

		/* Extract as many full 16 bit characters as possible from the
		   bit buffer.
		 */
		while (bufferbits >= 16) {
			/* write a unicode */
			nq(read_n_bits(16));
			wroteone = 1;
		}

		if (base64EOF) {
			junk = read_n_bits(bufferbits);
			if (junk)
				fatal("UTF-7: non-zero pad bits in input\n");
		}
	}

	if (!shifted && !done) {
		if (c == SHIFT_IN) {
			shifted = 1;
			first = 1;
			wroteone = 0;
		} else {
			/* It must be a directly encoded character. */
			if (c > 0x7f)
				fatal("UTF-7: non-ASCII character in input\n");
			nq(c);
		}
	}
	if (done)
		nq(EOF);
}
