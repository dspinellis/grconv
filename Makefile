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
# $Id: Makefile,v 1.8 2000/03/18 18:22:24 dds Exp $
#
# Major clean-up by Alexis Zavras
#

VERSION=1.1
RELEASE=1
NAME=grconv-$(VERSION)
SPEC=$(NAME)-$(RELEASE).spec

OBJ=i843.$(O) grconv.$(O) queue.$(O) charset.$(O) chartbl.$(O) getopt.$(O) \
	map.$(O) translit.$(O) ut843.$(O) error.$(O) utf7o.$(O) utf7i.$(O) \
	utf7.$(O) htmll1o.$(O) uhtmll1.$(O)

SRC=base64i.h base64o.h charset.h error.cpp error.h filter.h getopt.cpp \
	getopt.h grconv.1 grconv.cpp htmli.h htmll1o.cpp htmll1o.h htmlo.h \
	javai.h javao.h lex.h map.cpp map.h queue.cpp queue.h quotei.h \
	quoteo.h rtfi.h rtfo.h stdinput.h translit.cpp \
	translit.h ucs2i.h ucs2o.h unistd.h utf7.cpp \
	utf7.h utf7i.cpp utf7i.h utf7o.cpp utf7o.h utf8i.h utf8o.h \
	i843.l uhtmll1.l ut843.l \
	mkc.pl rfc1345.txt defacto.txt Makefile grconv.spec index.html

DOC=grconv.txt grconv.ps grconv.pdf grconv.html

## Unix START
EXE=
O=o
CC=g++
# Development
#FLAGS=-g
#FLAGS=-O
# RPM
FLAGS=$(RPM_OPT_FLAGS)
## Unix END

## Windows START
#EXE=.exe
#O=obj
#CC=cl
##FLAGS=-Zi
#FLAGS=-Ox
## Windows END

CFLAGS = $(FLAGS) -I. -DVERNAME="\"$(VERSION)-$(RELEASE)\"" 

.SUFFIXES: .l .cpp .$(O)

.l.$(O):
	flex -w -P$* $?
	mv lex.$*.c $*.cpp
	$(CC) $(CFLAGS) -c $*.cpp

.l.cpp:
	flex -w -P$* $?
	mv lex.$*.c $*.cpp

.cpp.$(O):
	$(CC) $(CFLAGS) -c $?

all: grconv$(EXE)

everything: grconv$(EXE) grconv.tar.gz doc rpm

doc: $(DOC)

grconv$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o grconv $(OBJ)

win32exe: Makefile.msc
	nmake -f makefile.msc

Makefile.msc: Makefile
	sed "/^## Unix START/,/^## Unix END/d;/^## Windows START/,/^## Windows END/s/#//" Makefile >Makefile.msc


chartbl.cpp charset.cpp: defacto.txt mkc.pl
	perl mkc.pl rfc1345.txt defacto.txt

# Does not yet work
depend:
	makedepend -Y -o'.$$(O)' -- $(CFLAGS) -- `ls *.cpp`
	ls *.cpp | sed 's/\(.*\).cpp/\1.$$(O): \1.cpp/' >>Makefile

grconv.ps: grconv.1
	groff -man -Tps $^ > $@

grconv.txt: grconv.1
	groff -man -Tascii $^ | col -b > $@

grconv.pdf: grconv.ps
	ps2pdf $^ $@

grconv.html: grconv.1
	man2html $^ | sed '1d;s,<A HREF="http.*</A>,,;s/^,$$/man2html,/' > $@

clean:
	rm -f i843.cpp uhtmll1.cpp ut843.cpp
	rm -f charset.cpp chartbl.cpp chartbl.h
	rm -f *.o *.obj grconv.exe grconv
	rm -f $(DOC)
	rm -f *.pdb
	rm -f *.rpm
	rm -f grconv.tar.gz
	rm -f Makefile.msc
	rm -f $(SPEC)

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
	sed "s/^Version:.*/Version: $(VERSION)/; \
	     s/^Release:.*/Release: $(RELEASE)/" \
		grconv.spec >$(SPEC)
	rpm -ba $(SPEC)
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

DOSDIR=/dos/dds/src/grconv

dosfs:
	tar cvfz $(DOSDIR)/RCS.tgz RCS
	cp $(SRC) $(DOSDIR)
	cp *.rpm $(DOSDIR)
	cp grconv.{tar.gz,html,txt,pdf,ps} $(DOSDIR)
