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
 * $Id: map.h,v 1.1 2000/03/12 13:26:19 dds Exp $
 */

#ifndef MAP_
#define MAP_
#include "filter.h"

class map: public filter {
private:
	int mapsize;			// Size of character map
	int *charmap;			// Map from source to target
	char default_char;		// Default map character
	bool identity;			// True if map is the identity function
	char *ocs;			// Output character set
public:
	map(char *source, char *target, char dflt);
	int getcharacter();
	char *outputcs();
};
#endif
