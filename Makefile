# 
# (C) Copyright 2000 Diomidis Spinellis
# 
# Permission to use, copy, and distribute this software and its
# documentation for any purpose and without fee is hereby granted,
# provided that the above copyright notice appear in all copies and that
# both that copyright notice and this permission notice appear in
# supporting documentation.
# 
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
# WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
# MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#
# $Id: Makefile,v 1.6 2000/03/13 17:54:16 dds Exp $
#

VERSION=1.0
RELEASE=1
NAME=grconv-$(VERSION)

OBJ=lexi843.$(O) grconv.$(O) queue.$(O) charset.$(O) chartbl.$(O) getopt.$(O) \
	map.$(O) translit.$(O) lexut843.$(O) error.$(O) utf7o.$(O) utf7i.$(O) \
	utf7.$(O) htmll1o.$(O) lexuhtmll1.$(O)

SRC=base64i.h base64o.h charset.h error.cpp error.h filter.h getopt.cpp \
	getopt.h grconv.1 grconv.cpp htmli.h htmll1o.cpp htmll1o.h htmlo.h \
	javai.h javao.h lex.h map.cpp map.h queue.cpp queue.h quotei.h \
	quoteo.h rtfi.h rtfo.h stdinput.h transcribe.l translit.cpp \
	translit.h ucs2i.h ucs2o.h uhtmll1.l unistd.h untranslit.l utf7.cpp \
	utf7.h utf7i.cpp utf7i.h utf7o.cpp utf7o.h utf8i.h utf8o.h \
	mkc.pl rfc1345.txt defacto.txt Makefile grconv.spec

DOC=grconv.txt grconv.ps grconv.pdf grconv.html


## Unix START
EXE=
O=o
CC=g++
# Development
#CFLAGS=-g
#CFLAGS=-O
# RPM
CFLAGS=$(RPM_OPT_FLAGS)
## Unix END

## Windows START
#EXE=.exe
#O=obj
#CC=cl
##CFLAGS=-Zi
#CFLAGS=-Ox
## Windows END

all: grconv$(EXE)

everything: grconv$(EXE) grconv.tar.gz doc rpm

doc: $(DOC)

grconv$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o grconv $(OBJ)

win32exe: Makefile.msc
	nmake -f makefile.msc

Makefile.msc: Makefile
	sed "/^## Unix START/,/^## Unix END/d;/^## Windows START/,/^## Windows END/s/#//" Makefile >Makefile.msc

lexi843.cpp: transcribe.l
	flex -w -Pi843 transcribe.l
	mv lex.i843.c lexi843.cpp

lexi843.$(O): lexi843.cpp
	$(CC) $(CFLAGS) -c -I. lexi843.cpp

grconv.$(O): grconv.cpp
	$(CC) -DVERNAME="\"$(VERSION)-$(RELEASE)\"" $(CFLAGS) -c grconv.cpp

charset.$(O): charset.cpp
	$(CC) $(CFLAGS) -c charset.cpp

chartbl.$(O): chartbl.cpp
	$(CC) $(CFLAGS) -c chartbl.cpp

map.$(O): map.cpp
	$(CC) $(CFLAGS) -c map.cpp

htmll1o.$(O): htmll1o.cpp
	$(CC) $(CFLAGS) -c htmll1o.cpp

translit.$(O): translit.cpp
	$(CC) $(CFLAGS) -c translit.cpp

lexut843.cpp: untranslit.l
	flex -w -Put843 untranslit.l
	mv lex.ut843.c lexut843.cpp

lexut843.$(O): lexut843.cpp
	$(CC) $(CFLAGS) -c -I. lexut843.cpp

lexuhtmll1.cpp: uhtmll1.l
	flex -w -Puhtmll1 uhtmll1.l
	mv lex.uhtmll1.c lexuhtmll1.cpp

lexuhtmll1.$(O): lexuhtmll1.cpp
	$(CC) $(CFLAGS) -c -I. lexuhtmll1.cpp

chartbl.cpp charset.cpp: defacto.txt mkc.pl
	perl mkc.pl rfc1345.txt defacto.txt

grconv.ps: grconv.1
	groff -man -Tps grconv.1 >grconv.ps

grconv.txt: grconv.1
	groff -man -Tascii grconv.1 | sed 's/.//g' >grconv.txt

grconv.pdf: grconv.ps
	ps2pdf grconv.ps grconv.pdf

grconv.html: grconv.1
	man2html grconv.1 | sed '1d;s,<A HREF="http.*</A>,,;s/^,$$/man2html,/' >grconv.html

clean:
	rm -f lexi843.cpp lexuhtmll1.cpp lexut843.cpp
	rm -f charset.cpp chartbl.cpp chartbl.h
	rm -f *.o *.obj grconv.exe grconv
	rm -f $(DOC)
	rm -f *.pdb
	rm -f *.rpm
	rm -f grconv.tar.gz
	rm -f Makefile.msc

clobber: clean
	rm -f $(SRC)

grconv.tar.gz: $(SRC)
	tar cvfz grconv.tar.gz $(SRC)
	rm -rf $(NAME)
	mkdir $(NAME)
	tar -C $(NAME) -xvz -f grconv.tar.gz
	tar cvfz grconv.tar.gz $(NAME)
	rm -rf $(NAME)

rpm: grconv.tar.gz
	cp grconv.tar.gz /usr/src/redhat/SOURCES
	cp grconv.spec $(NAME)-$(RELEASE).spec
	rpm -ba $(NAME)-$(RELEASE).spec
	cp /usr/src/redhat/SRPMS/$(NAME)-$(RELEASE).src.rpm .
	cp /usr/src/redhat/RPMS/i386/$(NAME)-$(RELEASE).i386.rpm .

lf:
	perl -pi -e 's/\r//' $(SRC)

ci:
	ci -u $(SRC)

WEBTARGET=\dds\pubs\web\sw\greek\grconv

webpage:
	copy grconv.tar.gz $(WEBTARGET)\$(NAME)-$(RELEASE).tar.gz
	copy grconv.html $(WEBTARGET)
	copy grconv.exe $(WEBTARGET)
	copy grconv-$(VERSION)-$(RELEASE).i386.rpm $(WEBTARGET)
	copy grconv-$(VERSION)-$(RELEASE).src.rpm $(WEBTARGET)
	copy grconv.txt $(WEBTARGET)\grconv.txt
	copy grconv.pdf $(WEBTARGET)\grconv.pdf
	copy grconv.ps $(WEBTARGET)\grconv.ps
	copy grconv.jpg $(WEBTARGET)
	sed "s/VER-REL/$(VERSION)-$(RELEASE)/g" <index.html >$(WEBTARGET)\index.html
