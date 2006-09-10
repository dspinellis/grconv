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
 * $Id: utf7o.cpp,v 1.2 2006/09/10 14:40:23 dds Exp $
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

#include "utf7.h"
#include "utf7o.h"

void
utf7o::fillbuff()		 // Fill the queue buffer
{
	int r;

	r = input->getcharacter();
	done = (r == EOF);
	needshift = (!done && ((r > 0x7f) || mustshift[r]));

	if (needshift && !shifted) {
		nq(SHIFT_IN);
		/* Special case handling of the SHIFT_IN character */
		if (r == SHIFT_IN)
			nq(SHIFT_OUT);
		else
			shifted = 1;
	}
	if (shifted) {
		/* Either write the character to the bit buffer, or pad
		   the bit buffer out to a full base64 character.
		 */
		if (needshift)
			write_n_bits(r, 16);
		else
			write_n_bits(0, (6 - (bufferbits % 6))%6);

		/* Flush out as many full base64 characters as possible
		   from the bit buffer.
		 */
		while (bufferbits >= 6)
			nq(base64[read_n_bits(6)]);

		if (!needshift) {
			/* Write the explicit shift out character if
			   1) The caller has requested we always do it, or
			   2) The directly encoded character is in the
			   base64 set, or
			   3) The directly encoded character is SHIFT_OUT.
			 */
			if (((!done) && (invbase64[r] >=0 || r == SHIFT_OUT)))
				nq(SHIFT_OUT);
			shifted = 0;
		}
	}

	/* The character can be directly encoded as ASCII. */
	if (!needshift && !done)
		nq((char) r);
	if (done)
		nq(EOF);
}

void
utf7o::optional(bool opt)
{
	if (opt)
		mustshift = mustshiftopt;
	else
		mustshift = mustshiftsafe;
}

