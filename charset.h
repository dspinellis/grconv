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
 * $Id: charset.h,v 1.1 2000/03/12 13:26:19 dds Exp $
 */

struct s_charentry {
	int unicode;			// Unicode value
	int charval;			// Character-set specific value
};

struct s_charset {
	char *name;			// Character set name
	int count;			// Number of characters
	struct s_charentry *ce;		// Entries sorted by Unicode value
};

extern struct s_charset charsets[];
