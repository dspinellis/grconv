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
 * $Id: grconv.cpp,v 1.7 2000/05/06 19:27:11 dds Exp $
 */

#include <stdlib.h>
#include <string.h>

#include "error.h"

#include "filter.h"
#include "queue.h"

#include "stdinput.h"
#include "strinput.h"
#include "lex.h"
#include "map.h"
#include "translit.h"

// Output encodings
#include "ucs2o.h"
#include "utf8o.h"
#include "utf7o.h"
#include "htmll1o.h"
#include "htmlso.h"
#include "htmlo.h"
#include "javao.h"
#include "base64o.h"
#include "quoteo.h"
#include "rtfo.h"

// Input encodings
#include "ucs2i.h"
#include "utf8i.h"
#include "utf7i.h"
#include "htmli.h"
#include "javai.h"
#include "base64i.h"
#include "quotei.h"
#include "rtfi.h"

#include "getopt.h"
#include "charset.h"

void lexi843(lex *l);
void lexut843(lex *l);
void lexuhtmll1(lex *l);
void lexuhtmls(lex *l);

char *encoding_names[] = {
	"UCS-2", "UTF-8", "UTF-7", "Java", "HTML", 
	"8bit", "Base64", "Quoted", "RTF", "HTML-Symbol", "HTML-Lat",
};

void
usage()
{
	error("usage:\n");
	cerr <<
	"grconv [-S enc] [-s cs] [-t cs] [-T enc] [-h] [-d c] [file...]\n"
	"grconv [-S enc] [-s cs] -x xl [-d c] [file...]\n"
	"grconv -r [-t cs] [-T enc] [-h] [-d c] [file...]\n"
	"grconv -v|-L|-R\n"
	"\t-S enc\tSpecify source encoding (default to 8bit or UCS-2)\n"
	"\t-s cs\tSpecify source character set (default to ISO-8859-7)\n"
	"\t-T enc\tSpecify target encoding (default to 8bit or UCS-2)\n"
	"\t-t cs\tSpecify target character set (default to ISO-8859-7)\n"
	"\t-x xl\tSpecify one of transcribe or transliterate (ISO 843:1997)\n"
	"\t-r\tPerform reverse transliteration\n"
	"\t-h\tCreate header for the output encoding\n"
	"\t-d char\tSpecify character for unknown mappings (default to space)\n"
	"\t-v\tDisplay program version and copyright\n"
	"\t-L\tList supported character sets and encodings\n";
	"\t-R\tPrint a \"Rosetta stone\" of a phrase in all character sets\n";
	exit(1);
}

static void
encodings()
{
	cout << "Valid input/output encodings are:\n"
		"\tFor Unicode data: UCS-2 UTF-8 UTF-7 Java HTML\n"
		"\tFor 8-bit data: 8bit Base64 Quoted RTF HTML HTML-Symbol HTML-Lat\n"
	"Valid character sets are:\n";
	int margin=0;
	for (struct s_charset *cp = charsets; cp->name; cp++) {
		cout << cp->name;
		if (cp[1].name)
			cout << ", ";
		if ((margin += strlen(cp->name) + 2) > 65) {
			margin = 0;
			cout << "\n";
		}
	}
	cout << "\nMany of the character set names are aliases.\n";
	cout << "Transcription/transliteration are performed only to plain ASCII.\n";
}

static void
version()
{
	cout << 
	"Universal Greek character code converter.  Version " VERNAME "\n"
	"(C) Copyright 2000 Diomidis D. Spinelllis.  All rights reserved.\n\n"

	"Permission to use, copy, and distribute this software and its\n"
	"documentation for any purpose and without fee is hereby granted,\n"
	"provided that the above copyright notice appear in all copies and that\n"
	"both that copyright notice and this permission notice appear in\n"
	"supporting documentation.\n\n"

	"THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED\n"
	"WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF\n"
	"MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.\n";
}

filter *
input_encoding(char *name)
{
	if (strcmp(name, "8bit") == 0)
		return NULL;
	else if (strcmp(name, "UCS-2") == 0)
		return new ucs2i;
	else if (strcmp(name, "UTF-8") == 0)
		return new utf8i;
	else if (strcmp(name, "UTF-7") == 0)
		return new utf7i;
	else if (strcmp(name, "HTML") == 0)
		return new htmli;
	else if (strcmp(name, "Base64") == 0)
		return new base64i;
	else if (strcmp(name, "Quoted") == 0)
		return new quotei;
	else if (strcmp(name, "RTF") == 0)
		return new rtfi;
	else if (strcmp(name, "Java") == 0)
		return new javai;
	else if (strcmp(name, "HTML-Symbol") == 0)
		return new lex(lexuhtmls);
	else if (strcmp(name, "HTML-Lat") == 0)
		return new lex(lexuhtmll1);
	else {
		error("Unknown -S source encoding ");
		cerr << name << "\n";
		usage();
		return NULL;
	}
}

filter *
output_encoding(char *name)
{
	if (strcmp(name, "8bit") == 0)
		return NULL;
	else if (strcmp(name, "UCS-2") == 0)
		return new ucs2o;
	else if (strcmp(name, "UTF-8") == 0)
		return new utf8o;
	else if (strcmp(name, "UTF-7") == 0)
		return new utf7o;
	else if (strcmp(name, "HTML") == 0)
		return new htmlo;
	else if (strcmp(name, "Base64") == 0)
		return new base64o;
	else if (strcmp(name, "Quoted") == 0)
		return new quoteo;
	else if (strcmp(name, "RTF") == 0)
		return new rtfo;
	else if (strcmp(name, "Java") == 0)
		return new javao;
	else if (strcmp(name, "HTML-Symbol") == 0)
		return new htmlso;
	else if (strcmp(name, "HTML-Lat") == 0)
		return new htmll1o;
	else {
		error("Unknown -T target encoding ");
		cerr << name << "\n";
		usage();
		return NULL;
	}
}

static void
rosetta()
{
	// CP-1253
	strinput in("¢ëöá, ôï ðñþôï ãñÜììá ôïõ åëëçíéêïý áëöáâÞôïõ.  ÙÌÅÃÁ, ÔÏ ÔÅËÅÕÔÁÉÏ.");
	// Alfa, to proto gramma tou ellinikou alfabitou.  OMEGA, TO TELEFTAIO.
	filter *f;			// Current pipeline input

	map *m;
	for (struct s_charset *cp = charsets; cp->name; cp++) {
		cout << cp->name << ": ";

		f = &in;
		m = new map("cp1253", cp->name, '?');
		m->setinput(f);
		f = m;

		int rc;
		while ((rc = f->getcharacter()) != EOF)
			cout << (unsigned char)rc;
		cout << "\n";
		in.rewind();
		delete m;
	}
}

int
main(int argc, char *argv[])
{
	stdinput in;
	filter *f = &in;			// Current pipeline input
	char defchar = ' ';
	char *sourcecs = NULL;
	char *targetcs = NULL;
	char *xflag = NULL;
	filter *ienc = NULL;
	filter *oenc = NULL;
	bool hflag = false, rflag = false;
	char c;

	setname(argv[0]);
	while ((c = getopt(argc, argv, "S:s:t:T:x:rhd:vLR")) != EOF)
		switch (c) {
		case 'r': rflag = true; break;
		case 'h': hflag = true; break;
		case 'R':
			rosetta();
			exit(0);
		case 'L':
			encodings();
			exit(0);
		case 'v':
			version();
			exit(0);
		case 'd':
			if (!optarg || optarg[1]) {
				error("Exactly one character must be specified with -d");
				usage();
			}
			defchar = *optarg;
			break;
		case 'S':
			if (!optarg) {
				error("No source encoding was specified with -S\n");
				usage();
			}
			ienc = input_encoding(optarg);
			break;
		case 'T':
			if (!optarg) {
				error("No target encoding was specified with -T\n");
				usage();
			}
			oenc = output_encoding(optarg);
			break;
		case 's':
			if (!optarg) {
				error("No source character set was specified with -s\n");
				usage();
			}
			sourcecs = optarg;
			break;
		case 't':
			if (!optarg) {
				error("No target character set was specified with -t\n");
				usage();
			}
			targetcs = optarg;
			break;
		case 'x':
			if (!optarg) {
				error("Option -x specify transliterate or transcribe\n");
				usage();
			}
			xflag = optarg;
			break;
		case '?':
			usage();
		}


	in.setargs(argv + optind);

	// Test for incompatible flags
	if ((xflag && (targetcs || oenc)) ||
	    (rflag && (sourcecs || ienc)) ||
	    (xflag && rflag)) {
		error("Incompatible options were specified\n");
		usage();
	}

	// Apply defaults
	if (!sourcecs)
		sourcecs = ((ienc && ienc->owidth() == 16) ? "Unicode" : "ISO-8859-7");
	if (!targetcs)
		targetcs = ((oenc && oenc->iwidth() == 16) ? "Unicode" : "ISO-8859-7");

	if (ienc) {
		ienc->setinput(f);
		f = ienc;
	} else if (strcmp(sourcecs, "Unicode") == 0) {
		ienc = new ucs2i;		// Default Unicode encoding
		ienc->setinput(f);
		f = ienc;
	}

	if (xflag) {		// Transcription / transliteration
		/*
		 * Transcription and transliteration are written to 
		 * expect CP-1253 character set on input.
		 */
		if (strcmp(sourcecs, "MS1253") != 0) {
			map *m = new map(sourcecs, "MS1253", defchar);
			m->setinput(f);
			f = m;
		}
		if (strcmp(xflag, "transliterate") == 0) {
			translit *t = new translit;
			t->setinput(f);
			f = t;
		} else if (strcmp(xflag, "transcribe") == 0) {
			lex *l = new lex(lexi843);
			l->setinput(f);
			f = l;
		} else
			usage();
	} else if (rflag) {		// Reverse transliteration
		lex *l = new lex(lexut843);
		l->setinput(f);
		f = l;
		/*
		 * Reverse transliteration is written to 
		 * produce CP-1253 character set on output.
		 */
		if (strcmp(targetcs, l->outputcs()) != 0) {
			map *m = new map(l->outputcs(), targetcs, defchar);
			m->setinput(f);
			f = m;
		}
	} else {			// Plain map
		map *m = new map(sourcecs, targetcs, defchar);
		m->setinput(f);
		f = m;
	}

	if (oenc) {
		oenc->setinput(f);
		f = oenc;
	} else if (strcmp(targetcs, "Unicode") == 0) {
		oenc = new ucs2o;		// Default Unicode encoding
		oenc->setinput(f);
		f = oenc;
	}

	if (oenc && hflag)
		oenc->header();

	int rc;
	while ((rc = f->getcharacter()) != EOF)
		cout << (unsigned char)rc;

	if (oenc && hflag)
		oenc->footer();
	return (0);
}
