/* 
 * (C) Copyright 2000-2009 Diomidis Spinellis.
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
 * $Id: grconv.cpp,v 1.17 2009/05/10 19:19:04 dds Exp $
 */

#include <cstdlib>
#include <cstring>

using namespace std;

// To set binary I/O
#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#endif

#include "error.h"

#include "filter.h"
#include "queue.h"

#include "stdinput.h"
#include "strinput.h"
#include "lex.h"
#include "map.h"
#include "translit.h"

// Output encodings
#include "ucs16beo.h"
#include "ucs16leo.h"
#include "utf8o.h"
#include "utf7o.h"
#include "htmll1o.h"
#include "htmlso.h"
#include "betao.h"
#include "htmlo.h"
#include "javao.h"
#include "base64o.h"
#include "quoteo.h"
#include "rtfo.h"
#include "urlo.h"

// Input encodings
#include "ucs2i.h"
#include "ucs16bei.h"
#include "ucs16lei.h"
#include "utf8i.h"
#include "utf7i.h"
#include "htmli.h"
#include "javai.h"
#include "base64i.h"
#include "quotei.h"
#include "rtfi.h"
#include "urli.h"

#include "getopt.h"
#include "charset.h"

void lexi843(lex *l);
void lexut843(lex *l);
void lexuhtmll1(lex *l);
void lexuhtmls(lex *l);
void lexubeta(lex *l);

void
usage()
{
	error("usage:\n");
	cerr <<
	"grconv [-S enc] [-s cs] [-t cs] [-T enc] [-h] [-d c] [file...]\n"
	"grconv [-S enc] [-s cs] -x xl [-d c] [file...]\n"
	"grconv -r [-t cs] [-T enc] [-h] [-d c] [file...]\n"
	"grconv -v|-L|-R\n"
	"\t-S enc\tSpecify source encoding (default to 8bit or UCS-16)\n"
	"\t-s cs\tSpecify source character set (default to ISO-8859-7)\n"
	"\t-T enc\tSpecify target encoding (default to 8bit or UCS-16)\n"
	"\t-t cs\tSpecify target character set (default to ISO-8859-7)\n"
	"\t-x xl\tSpecify one of transcribe or transliterate (ISO 843:1997)\n"
	"\t-r\tPerform reverse transliteration\n"
	"\t-h\tCreate header for the output encoding\n"
	"\t-d char\tSpecify character for unknown mappings (default to space)\n"
	"\t-v\tDisplay program version and copyright\n"
	"\t-L\tList supported character sets and encodings\n"
	"\t-R\tPrint a \"Rosetta stone\" of a phrase in all character sets\n";
	exit(1);
}

int
byname(const void *a, const void *b)
{
	return strcasecmp(((struct s_charset *)a)->name, ((struct s_charset *)b)->name);
}

void
encodings()
{
	cout << "Valid input/output encodings are:\n"
		"\tFor Unicode data: HTML Java UCS-16 UCS-16BE UCS-16LE UCS-2 UTF-7 UTF-8\n"
		"\tFor 8-bit data: 8bit Base64 Beta HTML HTML-Lat HTML-Symbol Quoted RTF\n"
		"\tFor any data: URL\n"
	"Valid character sets are:\n";
	int margin=0;
	int ncharset = 0;
	for (struct s_charset *cp = charsets; cp->name; cp++)
		ncharset++;
	qsort(charsets, ncharset, sizeof(*charsets), byname);
	for (struct s_charset *cp = charsets; cp->name; cp++) {
		cout << cp->name;
		if (cp[1].name)
			cout << ", ";
		if ((margin += strlen(cp->name) + 2) > 65) {
			margin = 0;
			cout << "\n";
		}
	}
	cout << "\nMany of the character set names and encodings are aliases.\n";
	cout << "Transcription/transliteration are performed only to plain ASCII.\n";
}

static void
version()
{
	cout <<
	"Universal Greek character code converter.  Version " VERNAME "\n"
	"(C) Copyright 2000-2009 Diomidis Spinelllis.  All rights reserved.\n\n"

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
	else if (strcmp(name, "UCS-16") == 0)
		return new ucs2i;
	else if (strcmp(name, "UCS-16LE") == 0)
		return new ucs16lei;
	else if (strcmp(name, "UCS-16BE") == 0)
		return new ucs16bei;
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
	else if (strcmp(name, "URL") == 0)
		return new urli;
	else if (strcmp(name, "HTML-Symbol") == 0)
		return new lex(lexuhtmls);
	else if (strcmp(name, "HTML-Lat") == 0)
		return new lex(lexuhtmll1);
	else if (strcmp(name, "Beta") == 0)
		return new lex(lexubeta);
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
		return new ucs16beo;
	else if (strcmp(name, "UCS-16") == 0)
		return new ucs16beo;
	else if (strcmp(name, "UCS-16BE") == 0)
		return new ucs16beo;
	else if (strcmp(name, "UCS-16LE") == 0)
		return new ucs16leo;
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
	else if (strcmp(name, "Beta") == 0)
		return new betao;
	else if (strcmp(name, "URL") == 0)
		return new urlo;
	else {
		error("Unknown -T target encoding ");
		cerr << name << "\n";
		usage();
		return NULL;
	}
}

static void
copyout(filter *f)
{
	int rc;

	while ((rc = f->getcharacter()) != EOF)
		cout << (unsigned char)rc;
}

static void
rosetta()
{
	// CP-1253
	strinput in(
	// Alfa, to proto gramma tou ellinikou alfabitou.
	"¢ëöá, ôï ðñþôï ãñÜììá ôïõ åëëçíéêïý áëöáâÞôïõ.  "
	"Á¢ÂÃÄÅ¸ÆÇ¹ÈÉºÚÊËÌÍÎÏ¼ÐÑÓÔÕ¾ÛÖ×ØÙ¿áÜâãäåÝæçÞèéßúÀêëìíîïüðñòóôõýûàö÷øùþ"
	);
	filter *f;			// Current pipeline input
	char *enc8[] = {
		"8bit", "Base64", "Quoted", "RTF", "HTML", "HTML-Symbol",
		"HTML-Lat", "Beta", "URL",
	};
	char *enc16[] = {
		"UCS-16", "UCS-16LE", "UTF-8", "UTF-7", "Java", "HTML",
	};
	int i;

	// Transliterate
	f = &in;
	translit *t = new translit;
	t->setinput(f);
	f = t;
	cout << "-x transliterate\n";
	copyout(f);
	cout << "\n";
	in.rewind();
	delete t;

	// Transcribe
	f = &in;
	lex *l = new lex(lexi843);
	l->setinput(f);
	f = l;
	cout << "-x transcribe\n";
	copyout(f);
	cout << "\n";
	in.rewind();
	delete l;

	// 8 bit character sets with all 8 bit encodings
	for (i = 0; i < sizeof(enc8) / sizeof(char *); i++) {
		filter *oenc = output_encoding(enc8[i]);
		for (struct s_charset *cp = charsets; cp->name; cp++) {
			if (cp->alias || is_unicode(cs_find(cp->name)))
				continue;

			f = &in;
			map *m = new map("cp1253", cp->name, '?');
			m->setinput(f);
			f = m;

			if (oenc) {
				oenc->setinput(f);
				f = oenc;
			}

			cout << "-t " << cp->name << " -T " << enc8[i] << ":\n";
			copyout(f);
			cout << "\n";
			in.rewind();
			delete m;
		}
		if (oenc) delete oenc;
	}

	// Unicode with all 16 bit encodings
	map *m = new map("cp1253", "Unicode", '?');
	for (i = 0; i < sizeof(enc16) / sizeof(char *); i++) {
		f = &in;
		m->setinput(f);
		f = m;

		filter *oenc = output_encoding(enc16[i]);
		if (oenc) {
			oenc->setinput(f);
			f = oenc;
		}

		cout << "-t Unicode -T " << enc16[i] << ":\n";
		copyout(f);
		cout << "\n";

		in.rewind();
		if (oenc) delete oenc;
	}
	delete m;
}

int
main(int argc, char *argv[])
{
	stdinput in;
	filter *f = &in;			// Current pipeline input
	char defchar = ' ';
	char *sourcecs = NULL;
	char *targetcs = NULL;
	char *oenc_name = "";
	char *ienc_name = "";
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
			ienc = input_encoding(ienc_name = optarg);
			break;
		case 'T':
			if (!optarg) {
				error("No target encoding was specified with -T\n");
				usage();
			}
			oenc = output_encoding(oenc_name = optarg);
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
		sourcecs = (char*)((ienc && ienc->owidth() == 16) ? "Unicode" : "ISO-8859-7");
	if (!targetcs)
		targetcs = (char*)((oenc && oenc->iwidth() == 16) ? "Unicode" : "ISO-8859-7");

	if (strcmp(ienc_name, "URL") == 0) {
		ienc->setinput(f);
		// Post-process with UTF-8
		f = new utf8i;
		f->setinput(ienc);
	} else if (ienc) {
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

	if (strcmp(oenc_name, "URL") == 0) {
		// Pre-process with UTF-8
		filter *f2 = new utf8o;
		f2->setinput(f);
		oenc->setinput(f2);
		f = oenc;
	} else if (oenc) {
		oenc->setinput(f);
		f = oenc;
	} else if (is_unicode(cs_find(targetcs))) {
		oenc = new ucs16beo;		// Default Unicode encoding
		oenc->setinput(f);
		f = oenc;
	}

#ifdef _WIN32
	// The library cr-lf translation messes up Unicode I/O
	_setmode(_fileno(stdin), O_BINARY);
	_setmode(_fileno(stdout), O_BINARY);
#endif

	if (oenc && hflag)
		oenc->header();

	copyout(f);

	if (oenc && hflag)
		oenc->footer();
	return (0);
}
