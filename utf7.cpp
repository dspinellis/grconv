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
 * $Id: utf7.cpp,v 1.1 2000/03/12 13:26:19 dds Exp $
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

#include <string.h>
#include "utf7.h"

char utf7::base64[] =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
short utf7::invbase64[128];
char utf7::direct[] =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789'(),-./:?";
char utf7::optional[] = "!\"#$%&*;<=>@[]^_`{|}";
char utf7::spaces[] = " \011\015\012";		/* space, tab, return, line feed */
char utf7::mustshiftsafe[128];
char utf7::mustshiftopt[128];

const int utf7::SHIFT_IN = '+';
const int utf7::SHIFT_OUT = '-';

// Initialize tables
utf7::utf7()
{
	int i, limit;

	for (i = 0; i < 128; ++i) {
		mustshiftopt[i] = mustshiftsafe[i] = 1;
		invbase64[i] = -1;
	}
	limit = strlen(direct);
	for (i = 0; i < limit; ++i)
		mustshiftopt[direct[i]] = mustshiftsafe[direct[i]] = 0;
	limit = strlen(spaces);
	for (i = 0; i < limit; ++i)
		mustshiftopt[spaces[i]] = mustshiftsafe[spaces[i]] = 0;
	limit = strlen(optional);
	for (i = 0; i < limit; ++i)
		mustshiftopt[optional[i]] = 0;
	limit = strlen(base64);
	for (i = 0; i < limit; ++i)
		invbase64[base64[i]] = i;



	BITbuffer = 0;
	buffertemp = 0;
	bufferbits = 0;
}
