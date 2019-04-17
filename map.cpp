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
 * $Id: map.cpp,v 1.8 2012/04/25 10:11:45 dds Exp $
 */

#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;

#include "error.h"
#include "filter.h"
#include "map.h"

#include "charset.h"

struct s_charset *
cs_find(const char *name) 
{
	struct s_charset *cp;

	for (cp = charsets; cp->name; cp++)
		if (strcmp(name, cp->name) == 0)
			return (cp);
	return (NULL);
}

static int
cecompare(const struct s_charentry *a, const struct s_charentry *b)
{
	return (a->unicode - b->unicode);
}

bool
is_unicode(struct s_charset *cs)
{
	return (cs->count > 1000);		// Must be Unicode
}


void encodings();

/*
 * Create a character map between the character set specified in
 * in and the character set specified in out.  Characters that can
 * not be represented in out are set to def.
 */
map::map(const char *in, const char *out, char def)
{
	int i;
	struct s_charset *inp, *outp;
	struct s_charentry *cep, ce;
	int unmap = 0;

	default_char = def;
	if ((inp = cs_find(in)) == NULL) {
		cerr << "Unknown source character set " << in << "\n";
		encodings();
		exit(1);
	}
	if ((outp = cs_find(out)) == NULL) {
		cerr << "Unknown target character set " << out << "\n";
		encodings();
		exit(1);
	}
	if (inp == outp) {
		identity = true;
		return;
	} else
		identity = false;
	mapsize = 0;
	for (i = 0; i < inp->count; i++)
		mapsize = (mapsize < inp->ce[i].charval) ? inp->ce[i].charval : mapsize;
	charmap = new int[mapsize];
	for (i = 0; i < mapsize; i++)
		charmap[i] = def;
	for (i = 0; i < inp->count; i++) {
		ce.unicode = inp->ce[i].unicode;
		if (ce.unicode == 0xffff)
			continue;			// Unknown character
		cep = (struct s_charentry *)bsearch(&ce, outp->ce, outp->count, sizeof(struct s_charentry), (int (*)(const void*, const void*))cecompare);
		if (cep)
			charmap[inp->ce[i].charval] = cep->charval;
		else
			unmap++;
	}
	if (is_unicode(outp))
		ocs = "UNICODE-1-1";
	else
		ocs = outp->name;
	/*
	if (unmap)
		cerr << unmap <<" characters could not be mapped\n";
	*/
}

int
map::getcharacter()
{
	int c = input->getcharacter();

	if (identity)
		return (c);
	if (c == EOF)
		return (EOF);
	else if (c >= mapsize)
		return (default_char);
	else
		return (charmap[c]);
}

const char *
map::outputcs()
{
	return (ocs);
}
